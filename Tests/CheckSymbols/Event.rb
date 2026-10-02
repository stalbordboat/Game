# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Event.rb:'

%w(
QUIT
KEY_DOWN
KEY_UP
STATE_PRESSED
STATE_RELEASED
GAMEPAD_BUTTON_DOWN
GAMEPAD_BUTTON_UP
GAMEPAD_AXIS_MOTION
GAMEPAD_REMOVED
GAMEPAD_ADDED
GAMEPAD_TOUCHPAD_DOWN
GAMEPAD_TOUCHPAD_MOTION
GAMEPAD_TOUCHPAD_UP
GAMEPAD_SENSOR_UPDATE
KEYBOARD_ADDED
KEYBOARD_REMOVED
AUDIO_DEVICE_ADDED
AUDIO_DEVICE_REMOVED
AUDIO_DEVICE_FORMAT_CHANGED
CAMERA_DEVICE_ADDED
CAMERA_DEVICE_REMOVED
CAMERA_DEVICE_APPROVED
CAMERA_DEVICE_DENIED
SENSOR_UPDATE
Keyboard
KeyboardDevice
GamepadDevice
GamepadButton
GamepadAxis
GamepadTouchpad
GamepadSensor
AudioDevice
CameraDevice
).const_defined_tests found_at, Event

%w(
KEY_Z
KEY_X
KEY_I
KEY_J
KEY_K
KEY_L
KEY_W
KEY_S
KEY_A
KEY_D
KEY_UP
KEY_DOWN
KEY_LEFT
KEY_RIGHT
KEY_C
KEY_V
KEY_SPACE
KEY_ENTER
KEY_E
KEY_F
KEY_Q
KEY_R
KEY_LCTRL
KEY_RCTRL
KEY_LSHIFT
KEY_RSHIFT
KEY_LALT
KEY_RALT
KEY_PAD_7
KEY_PAD_8
KEY_PAD_9
KEY_PAD_4
KEY_PAD_6
KEY_PAD_1
KEY_PAD_2
KEY_PAD_3
KEY_ESC
KEY_BACKSPACE
).const_defined_tests found_at, Event::Keyboard

%w(
S
E
W
N
BACK
GUIDE
START
LEFT_STICK
RIGHT_STICK
L1
R1
UP
DOWN
LEFT
RIGHT
).const_defined_tests found_at, Event::GamepadButton

%w(
DEFAULT_DEADZONE
LEFTX
LEFTY
RIGHTX
RIGHTY
TRIGGER_LEFT
TRIGGER_RIGHT
).const_defined_tests found_at, Event::GamepadAxis

%w(fetching? type).response_tests                      found_at, Event
%w(timestamp down? repeat? key).response_tests         found_at, Event::Keyboard
%w(timestamp which).response_tests                     found_at, Event::KeyboardDevice
%w(timestamp which).response_tests                     found_at, Event::GamepadDevice
%w(timestamp which button down?).response_tests        found_at, Event::GamepadButton
%w(timestamp which axis value).response_tests          found_at, Event::GamepadAxis
%w(timestamp which finger x y pressure).response_tests found_at, Event::GamepadTouchpad
%w(timestamp which recording?).response_tests          found_at, Event::AudioDevice
%w(timestamp which).response_tests                     found_at, Event::CameraDevice
