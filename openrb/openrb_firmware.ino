#include <Dynamixel2Arduino.h>

#define DXL_SERIAL   Serial1
#define DEBUG_SERIAL Serial3
#define DXL_DIR_PIN  -1

#define DEBUG_PRINT  1

// ──────────────────────────────────────────────
// 프레임 정의
// RX 11B: [AA][mode][btn][pan_L][pan_H][tilt_L][tilt_H][scan_step][manual_step][chk][55]
//          [0]  [1]  [2]   [3]   [4]    [5]     [6]       [7]         [8]       [9] [10]
// checksum = sum(frame[1..8]) = 8바이트
//
// TX 40B: [AA][mode][PAN 18B][TILT 18B][chk][55]
//          [0]  [1]  [2..19] [20..37]  [38] [39]
// checksum = sum(frame[1..37]) = 37바이트
// ──────────────────────────────────────────────
#define FRAME_START      0xAA
#define FRAME_END        0x55
#define RX_FRAME_LEN     11
#define TX_FRAME_LEN     40

// ──────────────────────────────────────────────
// 모드 정의
// ──────────────────────────────────────────────
#define MODE_SCAN        0
#define MODE_MANUAL      1
#define MODE_TRACK       2

// ──────────────────────────────────────────────
// 수동 버튼 비트마스크
// ──────────────────────────────────────────────
#define BTN_PAN_PLUS     0x01   // bit0: 팬 + (우)
#define BTN_PAN_MINUS    0x02   // bit1: 팬 - (좌)
#define BTN_TILT_PLUS    0x04   // bit2: 틸트 + (업)
#define BTN_TILT_MINUS   0x08   // bit3: 틸트 - (다운)

// ──────────────────────────────────────────────
// 모터 ID
// ──────────────────────────────────────────────
#define PAN_ID           1
#define TILT_ID          2

// ──────────────────────────────────────────────
// 위치 범위 / 중심
// ──────────────────────────────────────────────
#define POS_MIN          0
#define POS_MAX          4095
#define PAN_CENTER       2047
#define TILT_CENTER      2047

// ──────────────────────────────────────────────
// 스캔 파라미터
// ──────────────────────────────────────────────
#define SCAN_STEP_DEFAULT   5
#define SCAN_INTERVAL       20   // ms
#define MANUAL_INTERVAL     20   // ms  (BUG FIX: SCAN_INTERVAL 대신 분리)

// ──────────────────────────────────────────────
// 상태 전송 주기
// ──────────────────────────────────────────────
#define SCAN_STATUS_INTERVAL    50   // ms
#define MANUAL_STATUS_INTERVAL  20   // ms
#define TRACK_STATUS_INTERVAL   10   // ms

// ──────────────────────────────────────────────
// 스텝 범위 (BUG FIX: 상한 10)
// ──────────────────────────────────────────────
#define STEP_MIN         1
#define STEP_MAX         10

// ──────────────────────────────────────────────
// 프로파일 속도/가속도 (모드별)
// ──────────────────────────────────────────────
#define PROFILE_VEL_SCAN      50
#define PROFILE_ACC_SCAN      20
#define PROFILE_VEL_MANUAL   200
#define PROFILE_ACC_MANUAL   100
#define PROFILE_VEL_TRACK    300
#define PROFILE_ACC_TRACK    150

// ──────────────────────────────────────────────
// Dynamixel 벌크 읽기 범위
// addr 122(Moving) ~ 146(Temperature) = 25B
// ──────────────────────────────────────────────
#define DXL_READ_ADDR    122
#define DXL_READ_LEN     25

#define OFFSET_MOVING        0   // addr 122, 1B
#define OFFSET_MOVING_STATUS 1   // addr 123, 1B
#define OFFSET_PWM           2   // addr 124, 2B
#define OFFSET_CURRENT       4   // addr 126, 2B
#define OFFSET_VELOCITY      6   // addr 128, 4B
#define OFFSET_POSITION      10  // addr 132, 4B
#define OFFSET_VOLTAGE       22  // addr 144, 2B
#define OFFSET_TEMPERATURE   24  // addr 146, 1B

#if DEBUG_PRINT
  #define DBG(x)    Serial.println(x)
  #define DBGF(...) Serial.print(__VA_ARGS__)
#else
  #define DBG(x)
  #define DBGF(...)
#endif

const float DXL_PROTOCOL = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
using namespace ControlTableItem;

// ──────────────────────────────────────────────
// 전역 상태 변수
// ──────────────────────────────────────────────
uint8_t  current_mode     = MODE_SCAN;

// 스캔 모드
int32_t  scan_pos         = POS_MIN;
int8_t   scan_dir         = 1;
int32_t  scan_step        = SCAN_STEP_DEFAULT;
uint32_t last_scan_tick   = 0;

// 수동 모드
int32_t  manual_pan       = PAN_CENTER;
int32_t  manual_tilt      = TILT_CENTER;
uint8_t  manual_btn       = 0;
int32_t  manual_step      = SCAN_STEP_DEFAULT;
uint32_t last_manual_tick = 0;

// 트래킹 모드
int32_t  track_pan        = PAN_CENTER;
int32_t  track_tilt       = TILT_CENTER;
int32_t  last_pan         = -1;
int32_t  last_tilt        = -1;

// 공통
uint32_t last_status_tick = 0;

// RX 버퍼
uint8_t  rx_buf[RX_FRAME_LEN];
int      rx_idx = 0;

// ──────────────────────────────────────────────
// 체크섬: data[0..len-1] 합산
// ──────────────────────────────────────────────
uint8_t calcChecksum(uint8_t *data, uint8_t len)
{
    uint8_t sum = 0;
    for (uint8_t i = 0; i < len; i++) sum += data[i];
    return sum;
}

// ──────────────────────────────────────────────
// 모드 전환 (토크 OFF → 프로파일 재설정 → 토크 ON)
// ──────────────────────────────────────────────
void set_mode(uint8_t mode)
{
    if (current_mode == mode) return;
    current_mode = mode;

    uint16_t vel, acc;
    if      (mode == MODE_SCAN)   { vel = PROFILE_VEL_SCAN;   acc = PROFILE_ACC_SCAN;   }
    else if (mode == MODE_MANUAL) { vel = PROFILE_VEL_MANUAL; acc = PROFILE_ACC_MANUAL; }
    else                          { vel = PROFILE_VEL_TRACK;  acc = PROFILE_ACC_TRACK;  }

    dxl.torqueOff(PAN_ID);
    dxl.torqueOff(TILT_ID);

    dxl.writeControlTableItem(PROFILE_VELOCITY,     PAN_ID,  vel);
    dxl.writeControlTableItem(PROFILE_ACCELERATION, PAN_ID,  acc);
    dxl.writeControlTableItem(PROFILE_VELOCITY,     TILT_ID, vel);
    dxl.writeControlTableItem(PROFILE_ACCELERATION, TILT_ID, acc);

    // 모드 전환 시 현재 실제 위치로 상태 초기화 (급격한 움직임 방지)
    if (mode == MODE_MANUAL) {
        manual_pan  = (int32_t)dxl.getPresentPosition(PAN_ID);
        manual_tilt = (int32_t)dxl.getPresentPosition(TILT_ID);
        manual_btn  = 0;   // BUG FIX: 전환 시 버튼 상태 초기화
    }
    if (mode == MODE_TRACK) {
        last_pan  = -1;
        last_tilt = -1;
    }
    if (mode == MODE_SCAN) {
        scan_pos = constrain((int32_t)dxl.getPresentPosition(PAN_ID), POS_MIN, POS_MAX);
    }

    dxl.torqueOn(PAN_ID);
    dxl.torqueOn(TILT_ID);

    if      (mode == MODE_SCAN)   DBG("[MODE] SCAN");
    else if (mode == MODE_MANUAL) DBG("[MODE] MANUAL");
    else                          DBG("[MODE] TRACK");
}

// ──────────────────────────────────────────────
// TX 피드백 프레임 전송 (40B)
// checksum = sum(tx[1..37]) = 37바이트
// ──────────────────────────────────────────────
void send_status()
{
    uint8_t pan_data[DXL_READ_LEN]  = {0};
    uint8_t tilt_data[DXL_READ_LEN] = {0};

    dxl.read(PAN_ID,  DXL_READ_ADDR, DXL_READ_LEN, pan_data,  sizeof(pan_data));
    dxl.read(TILT_ID, DXL_READ_ADDR, DXL_READ_LEN, tilt_data, sizeof(tilt_data));

    uint8_t pan_err  = (uint8_t)dxl.readControlTableItem(HARDWARE_ERROR_STATUS, PAN_ID);
    uint8_t tilt_err = (uint8_t)dxl.readControlTableItem(HARDWARE_ERROR_STATUS, TILT_ID);

#if DEBUG_PRINT
    int32_t pan_pos  = (int32_t)((uint32_t)pan_data[OFFSET_POSITION]
                               | ((uint32_t)pan_data[OFFSET_POSITION+1] <<  8)
                               | ((uint32_t)pan_data[OFFSET_POSITION+2] << 16)
                               | ((uint32_t)pan_data[OFFSET_POSITION+3] << 24));
    int32_t tilt_pos = (int32_t)((uint32_t)tilt_data[OFFSET_POSITION]
                               | ((uint32_t)tilt_data[OFFSET_POSITION+1] <<  8)
                               | ((uint32_t)tilt_data[OFFSET_POSITION+2] << 16)
                               | ((uint32_t)tilt_data[OFFSET_POSITION+3] << 24));
    int16_t pan_cur  = (int16_t)((uint16_t)pan_data[OFFSET_CURRENT]
                               | ((uint16_t)pan_data[OFFSET_CURRENT+1] << 8));
    int16_t tilt_cur = (int16_t)((uint16_t)tilt_data[OFFSET_CURRENT]
                               | ((uint16_t)tilt_data[OFFSET_CURRENT+1] << 8));

    Serial.print("[FB] mode=");   Serial.print(current_mode);
    Serial.print(" pan_pos=");    Serial.print(pan_pos);
    Serial.print(" pan_cur=");    Serial.print(pan_cur);
    Serial.print(" pan_temp=");   Serial.print(pan_data[OFFSET_TEMPERATURE]);
    Serial.print(" pan_err=");    Serial.print(pan_err);
    Serial.print(" | tilt_pos="); Serial.print(tilt_pos);
    Serial.print(" tilt_cur=");   Serial.print(tilt_cur);
    Serial.print(" tilt_temp=");  Serial.print(tilt_data[OFFSET_TEMPERATURE]);
    Serial.print(" tilt_err=");   Serial.println(tilt_err);
#endif

    uint8_t tx[TX_FRAME_LEN];
    uint8_t i = 0;

    tx[i++] = FRAME_START;   // [0]
    tx[i++] = current_mode;  // [1]

    // PAN 18B [2..19]
    tx[i++] = pan_data[OFFSET_MOVING];
    tx[i++] = pan_data[OFFSET_MOVING_STATUS];
    tx[i++] = pan_data[OFFSET_PWM];
    tx[i++] = pan_data[OFFSET_PWM + 1];
    tx[i++] = pan_data[OFFSET_CURRENT];
    tx[i++] = pan_data[OFFSET_CURRENT + 1];
    tx[i++] = pan_data[OFFSET_VELOCITY];
    tx[i++] = pan_data[OFFSET_VELOCITY + 1];
    tx[i++] = pan_data[OFFSET_VELOCITY + 2];
    tx[i++] = pan_data[OFFSET_VELOCITY + 3];
    tx[i++] = pan_data[OFFSET_POSITION];
    tx[i++] = pan_data[OFFSET_POSITION + 1];
    tx[i++] = pan_data[OFFSET_POSITION + 2];
    tx[i++] = pan_data[OFFSET_POSITION + 3];
    tx[i++] = pan_data[OFFSET_VOLTAGE];
    tx[i++] = pan_data[OFFSET_VOLTAGE + 1];
    tx[i++] = pan_data[OFFSET_TEMPERATURE];
    tx[i++] = pan_err;

    // TILT 18B [20..37]
    tx[i++] = tilt_data[OFFSET_MOVING];
    tx[i++] = tilt_data[OFFSET_MOVING_STATUS];
    tx[i++] = tilt_data[OFFSET_PWM];
    tx[i++] = tilt_data[OFFSET_PWM + 1];
    tx[i++] = tilt_data[OFFSET_CURRENT];
    tx[i++] = tilt_data[OFFSET_CURRENT + 1];
    tx[i++] = tilt_data[OFFSET_VELOCITY];
    tx[i++] = tilt_data[OFFSET_VELOCITY + 1];
    tx[i++] = tilt_data[OFFSET_VELOCITY + 2];
    tx[i++] = tilt_data[OFFSET_VELOCITY + 3];
    tx[i++] = tilt_data[OFFSET_POSITION];
    tx[i++] = tilt_data[OFFSET_POSITION + 1];
    tx[i++] = tilt_data[OFFSET_POSITION + 2];
    tx[i++] = tilt_data[OFFSET_POSITION + 3];
    tx[i++] = tilt_data[OFFSET_VOLTAGE];
    tx[i++] = tilt_data[OFFSET_VOLTAGE + 1];
    tx[i++] = tilt_data[OFFSET_TEMPERATURE];
    tx[i++] = tilt_err;

    // [38] checksum = sum(tx[1..37])
    tx[i++] = calcChecksum(&tx[1], i - 1);
    // [39] FRAME_END
    tx[i++] = FRAME_END;

    DEBUG_SERIAL.write(tx, TX_FRAME_LEN);
}

// ──────────────────────────────────────────────
// RX 프레임 처리 (11B)
// checksum = sum(frame[1..8]) = 8바이트
// ──────────────────────────────────────────────
void frame_handle(uint8_t *frame)
{
    if (frame[0] != FRAME_START || frame[10] != FRAME_END) {
        DBG("[RX] boundary error");
        return;
    }

    uint8_t chk = calcChecksum(&frame[1], 8);
    if (frame[9] != chk) {
        DBG("[RX] checksum error");
        return;
    }

    uint8_t  mode       = frame[1];
    uint8_t  btn        = frame[2];
    int32_t  pan        = (int32_t)((uint32_t)frame[3] | ((uint32_t)frame[4] << 8));
    int32_t  tilt       = (int32_t)((uint32_t)frame[5] | ((uint32_t)frame[6] << 8));
    uint8_t  new_scan_s = frame[7];
    uint8_t  new_man_s  = frame[8];

    // 스텝 업데이트 (0이면 현재값 유지, BUG FIX: 상한 STEP_MAX=10)
    if (new_scan_s > 0) scan_step   = constrain((int32_t)new_scan_s, STEP_MIN, STEP_MAX);
    if (new_man_s  > 0) manual_step = constrain((int32_t)new_man_s,  STEP_MIN, STEP_MAX);

    if (mode == MODE_TRACK) {
        track_pan  = constrain(pan,  POS_MIN, POS_MAX);
        track_tilt = constrain(tilt, POS_MIN, POS_MAX);
        set_mode(MODE_TRACK);

    } else if (mode == MODE_MANUAL) {
        // BUG FIX: set_mode()가 already-MANUAL로 early return해도
        //          버튼 상태는 항상 갱신되어야 함 → set_mode 후에 btn 저장
        set_mode(MODE_MANUAL);
        manual_btn = btn;

    } else {
        set_mode(MODE_SCAN);
    }
}

// ──────────────────────────────────────────────
// 스캔 모드
// ──────────────────────────────────────────────
void update_scan()
{
    uint32_t now = millis();
    if (now - last_scan_tick < (uint32_t)SCAN_INTERVAL) return;
    last_scan_tick = now;

    dxl.setGoalPosition(PAN_ID,  scan_pos);
    dxl.setGoalPosition(TILT_ID, TILT_CENTER);

    scan_pos += scan_step * scan_dir;

    if (scan_pos >= POS_MAX) { scan_pos = POS_MAX; scan_dir = -1; }
    if (scan_pos <= POS_MIN) { scan_pos = POS_MIN; scan_dir =  1; }
}

// ──────────────────────────────────────────────
// 수동 모드
// 반대 방향 동시 입력 시 상쇄 (BUG FIX)
// ──────────────────────────────────────────────
void update_manual()
{
    uint32_t now = millis();
    if (now - last_manual_tick < (uint32_t)MANUAL_INTERVAL) return;  // BUG FIX
    last_manual_tick = now;

    // BUG FIX: 반대 방향 동시 입력 → delta 합산으로 상쇄
    int32_t pan_delta  = 0;
    int32_t tilt_delta = 0;

    if (manual_btn & BTN_PAN_PLUS)   pan_delta  += manual_step;
    if (manual_btn & BTN_PAN_MINUS)  pan_delta  -= manual_step;
    if (manual_btn & BTN_TILT_PLUS)  tilt_delta += manual_step;
    if (manual_btn & BTN_TILT_MINUS) tilt_delta -= manual_step;

    bool moved = false;

    if (pan_delta != 0) {
        manual_pan = constrain(manual_pan + pan_delta, POS_MIN, POS_MAX);
        moved = true;
    }
    if (tilt_delta != 0) {
        manual_tilt = constrain(manual_tilt + tilt_delta, POS_MIN, POS_MAX);
        moved = true;
    }

    if (moved) {
        dxl.setGoalPosition(PAN_ID,  manual_pan);
        dxl.setGoalPosition(TILT_ID, manual_tilt);
    }
}

// ──────────────────────────────────────────────
// 트래킹 모드
// ──────────────────────────────────────────────
void update_track()
{
    if (track_pan == last_pan && track_tilt == last_tilt) return;
    dxl.setGoalPosition(PAN_ID,  track_pan);
    dxl.setGoalPosition(TILT_ID, track_tilt);
    last_pan  = track_pan;
    last_tilt = track_tilt;
}

// ──────────────────────────────────────────────
// setup
// ──────────────────────────────────────────────
void setup()
{
#if DEBUG_PRINT
    Serial.begin(115200);
    delay(2000);
#endif
    DEBUG_SERIAL.begin(115200);

    dxl.begin(1000000);
    dxl.setPortProtocolVersion(DXL_PROTOCOL);

    if (!dxl.ping(PAN_ID))  Serial.println("Pan  실패!");
    else                     Serial.println("Pan  성공!");
    if (!dxl.ping(TILT_ID)) Serial.println("Tilt 실패!");
    else                     Serial.println("Tilt 성공!");

    dxl.torqueOff(PAN_ID);
    dxl.torqueOff(TILT_ID);
    dxl.setOperatingMode(PAN_ID,  OP_POSITION);
    dxl.setOperatingMode(TILT_ID, OP_POSITION);

    dxl.writeControlTableItem(PROFILE_VELOCITY,     PAN_ID,  PROFILE_VEL_SCAN);
    dxl.writeControlTableItem(PROFILE_ACCELERATION, PAN_ID,  PROFILE_ACC_SCAN);
    dxl.writeControlTableItem(PROFILE_VELOCITY,     TILT_ID, PROFILE_VEL_SCAN);
    dxl.writeControlTableItem(PROFILE_ACCELERATION, TILT_ID, PROFILE_ACC_SCAN);

    dxl.torqueOn(PAN_ID);
    dxl.torqueOn(TILT_ID);

    DBG("OpenRB-150 ready  |  mode: SCAN");
}

// ──────────────────────────────────────────────
// loop
// ──────────────────────────────────────────────
void loop()
{
    // ── RX 수신 ──
    while (DEBUG_SERIAL.available()) {
        uint8_t b = DEBUG_SERIAL.read();
        if (b == FRAME_START) rx_idx = 0;
        if (rx_idx < RX_FRAME_LEN) rx_buf[rx_idx++] = b;
        if (rx_idx == RX_FRAME_LEN) {
            frame_handle(rx_buf);
            rx_idx = 0;
        }
    }

    // ── 모드별 모션 ──
    switch (current_mode) {
        case MODE_SCAN:   update_scan();   break;
        case MODE_MANUAL: update_manual(); break;
        case MODE_TRACK:  update_track();  break;
    }

    // ── 주기별 피드백 전송 ──
    uint32_t interval;
    if      (current_mode == MODE_SCAN)   interval = SCAN_STATUS_INTERVAL;
    else if (current_mode == MODE_MANUAL) interval = MANUAL_STATUS_INTERVAL;
    else                                  interval = TRACK_STATUS_INTERVAL;

    uint32_t now = millis();
    if (now - last_status_tick >= interval) {
        send_status();
        last_status_tick = now;
    }
}
