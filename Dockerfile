FROM jetson-thor-ros2:jazzy

RUN apt-get update && apt-get install -y \
    libboost-all-dev \
    build-essential \
    cmake \
    vim \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /root/ros2_ws

# ── 커스텀 메시지 복사 및 빌드 ───────────────────────────────
COPY src/sentinel_interfaces/ src/sentinel_interfaces/

RUN bash -c "source /opt/ros/jazzy/setup.bash && \
             colcon build --packages-select sentinel_interfaces"

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
CMD ["bash"]