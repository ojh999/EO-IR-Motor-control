# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sentinel_interfaces:msg/YoloStatus.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_YoloStatus(type):
    """Metaclass of message 'YoloStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('sentinel_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'sentinel_interfaces.msg.YoloStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__yolo_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__yolo_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__yolo_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__yolo_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__yolo_status

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class YoloStatus(metaclass=Metaclass_YoloStatus):
    """Message class 'YoloStatus'."""

    __slots__ = [
        '_enabled',
        '_model_loaded',
        '_conf_threshold',
        '_last_error',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'enabled': 'boolean',
        'model_loaded': 'boolean',
        'conf_threshold': 'float',
        'last_error': 'string',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.enabled = kwargs.get('enabled', bool())
        self.model_loaded = kwargs.get('model_loaded', bool())
        self.conf_threshold = kwargs.get('conf_threshold', float())
        self.last_error = kwargs.get('last_error', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.enabled != other.enabled:
            return False
        if self.model_loaded != other.model_loaded:
            return False
        if self.conf_threshold != other.conf_threshold:
            return False
        if self.last_error != other.last_error:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def enabled(self):
        """Message field 'enabled'."""
        return self._enabled

    @enabled.setter
    def enabled(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'enabled' field must be of type 'bool'"
        self._enabled = value

    @builtins.property
    def model_loaded(self):
        """Message field 'model_loaded'."""
        return self._model_loaded

    @model_loaded.setter
    def model_loaded(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'model_loaded' field must be of type 'bool'"
        self._model_loaded = value

    @builtins.property
    def conf_threshold(self):
        """Message field 'conf_threshold'."""
        return self._conf_threshold

    @conf_threshold.setter
    def conf_threshold(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'conf_threshold' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'conf_threshold' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._conf_threshold = value

    @builtins.property
    def last_error(self):
        """Message field 'last_error'."""
        return self._last_error

    @last_error.setter
    def last_error(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'last_error' field must be of type 'str'"
        self._last_error = value
