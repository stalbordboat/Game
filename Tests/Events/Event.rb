# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Event subsystem.

PATH = 'Events/Event.rb'

send_test :found_at => PATH, :within_block => :events_constants_defined? do
  constants = %w(
                  Keyboard
                  KeyboardDevice
                  GamepadDevice
                  GamepadButton
                  GamepadAxis
                  GamepadTouchpad
                  AudioDevice
                  CameraDevice
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
                )

  constants.constants_defined? :within => Event
end

send_test :found_at => PATH, :within_block => :keyboard_constants_defined? do
  constants = %w(
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
                )

  constants.constants_defined? :within => Event::Keyboard
end

send_test :found_at => PATH, :within_block => :gamepad_axis_constants_defined? do
  constants = %w(
                  DEFAULT_DEADZONE
                  LEFTX
                  LEFTY
                  RIGHTX
                  RIGHTY
                  TRIGGER_LEFT
                  TRIGGER_RIGHT
                )

  constants.constants_defined? :within => Event::GamepadAxis
end

send_test :found_at => PATH, :within_block => :gamepad_buttons_constants_defined? do
  constants = %w(
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
                )

  constants.constants_defined? :within => Event::GamepadButton
end

send_test :found_at => PATH, :within_block => :functions_defined? do
  %w(fetching? type).methods_defined?(:within => Event)                                       &&
  %w(timestamp down? repeat? key).methods_defined?(:within => Event::Keyboard)                &&
  %w(timestamp which).methods_defined?(:within => Event::KeyboardDevice)                      &&
  %w(timestamp which).methods_defined?(:within => Event::GamepadDevice)                       &&
  %w(timestamp which button down?).methods_defined?(:within => Event::GamepadButton)          &&
  %w(timestamp which axis value).methods_defined?(:within => Event::GamepadAxis)              &&
  %w(timestamp which finger x y pressure).methods_defined?(:within => Event::GamepadTouchpad) &&
  %w(timestamp which recording?).methods_defined?(:within => Event::AudioDevice)              &&
  %w(timestamp which).methods_defined?(:within => Event::CameraDevice)
end
send_test :found_at => PATH, :within_block => :fetching? do
  status = nil

  simulate_main_loop do
    break if status = Event.fetching?
  end

  status
end

send_test :found_at => PATH, :within_block => :type? do
  status = nil

  simulate_main_loop do
    return Event.type.kind_of?(Integer) while Event.fetching?
  end
end

# The following are basically just data structures. They each just return a value of a certain type.

send_test :found_at => PATH, :within_block => :keyboard_types? do
  Event::Keyboard.timestamp.kind_of?(Integer) &&
  Event::Keyboard.key.kind_of?(Integer)       &&
  Event::Keyboard.down?.eql?(false)           &&
  Event::Keyboard.repeat?.eql?(false)
end

send_test :found_at => PATH, :within_block => :keyboard_device_types? do
  Event::Keyboard.timestamp.kind_of?(Integer) &&
  Event::Keyboard.which.kind_of?(Integer)
end

send_test :found_at => PATH, :within_block => :gamepad_device_types? do
  Event::GamepadDevice.timestamp.kind_of?(Integer) &&
  Event::GamepadDevice.which.kind_of?(Integer)
end

send_test :found_at => PATH, :within_block => :gamepad_button_types? do
  Event::GamepadButton.timestamp.kind_of?(Integer) &&
  Event::GamepadButton.which.kind_of?(Integer)     &&
  Event::GamepadButton.button.kind_of?(Integer)    &&
  Event::GamepadButton.down?.eql?(false)
end

send_test :found_at => PATH, :within_block => :gamepad_axis_types? do
  Event::GamepadAxis.timestamp.kind_of?(Integer) &&
  Event::GamepadAxis.which.kind_of?(Integer)     &&
  Event::GamepadAxis.axis.kind_of?(Integer)      &&
  Event::GamepadAxis.value.kind_of?(Integer)
end

send_test :found_at => PATH, :within_block => :gamepad_touchpad_types? do
  Event::GamepadTouchpad.timestamp.kind_of?(Integer) &&
  Event::GamepadTouchpad.finger.kind_of?(Integer)    &&
  Event::GamepadTouchpad.x.kind_of?(Float)           &&
  Event::GamepadTouchpad.y.kind_of?(Float)           &&
  Event::GamepadTouchpad.pressure.kind_of?(Float)    &&
  Event::GamepadTouchpad.which.kind_of?(Integer)
end

send_test :found_at => PATH, :within_block => :audio_device_types? do
  Event::AudioDevice.timestamp.kind_of?(Integer) &&
  Event::AudioDevice.which.kind_of?(Integer)     &&
  Event::AudioDevice.recording?.eql?(false)
end

send_test :found_at => PATH, :within_block => :camera_device_types? do
  Event::CameraDevice.timestamp.kind_of?(Integer) &&
  Event::CameraDevice.which.kind_of?(Integer)
end
