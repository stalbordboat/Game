# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Event subsystem.

path = 'Events/Event.rb'

send_test :found_at => path, :within => :fetching? do
  status = nil

  simulate_main_loop do
    break if status = Event.fetching?
  end

  status
end

send_test :found_at => path, :within => :type? do
  status = nil

  simulate_main_loop do
    return Event.type.kind_of? Integer while Event.fetching?
  end
end

# The following are basically just data structures. They each just return a value of a certain type.

send_test :found_at => path, :within => :keyboard_types? do
  Event::Keyboard.timestamp.kind_of?(Integer) &&
  Event::Keyboard.key.kind_of?(Integer)       &&
  Event::Keyboard.down?.eql?(false)           &&
  Event::Keyboard.repeat?.eql?(false)
end

send_test :found_at => path, :within => :keyboard_device_types? do
  Event::Keyboard.timestamp.kind_of?(Integer) &&
  Event::Keyboard.which.kind_of?(Integer)
end

send_test :found_at => path, :within => :gamepad_device_types? do
  Event::GamepadDevice.timestamp.kind_of?(Integer) &&
  Event::GamepadDevice.which.kind_of?(Integer)
end

send_test :found_at => path, :within => :gamepad_button_types? do
  Event::GamepadButton.timestamp.kind_of?(Integer) &&
  Event::GamepadButton.which.kind_of?(Integer)     &&
  Event::GamepadButton.button.kind_of?(Integer)    &&
  Event::GamepadButton.down?.eql?(false)
end

send_test :found_at => path, :within => :gamepad_axis_types? do
  Event::GamepadAxis.timestamp.kind_of?(Integer) &&
  Event::GamepadAxis.which.kind_of?(Integer)     &&
  Event::GamepadAxis.axis.kind_of?(Integer)      &&
  Event::GamepadAxis.value.kind_of?(Integer)
end

send_test :found_at => path, :within => :gamepad_touchpad_types? do
  Event::GamepadTouchpad.timestamp.kind_of?(Integer) &&
  Event::GamepadTouchpad.finger.kind_of?(Integer)    &&
  Event::GamepadTouchpad.x.kind_of?(Float)           &&
  Event::GamepadTouchpad.y.kind_of?(Float)           &&
  Event::GamepadTouchpad.pressure.kind_of?(Float)    &&
  Event::GamepadTouchpad.which.kind_of?(Integer)
end

send_test :found_at => path, :within => :audio_device_types? do
  Event::AudioDevice.timestamp.kind_of?(Integer) &&
  Event::AudioDevice.which.kind_of?(Integer)     &&
  Event::AudioDevice.recording?.eql?(false)
end

send_test :found_at => path, :within => :camera_device_types? do
  Event::CameraDevice.timestamp.kind_of?(Integer) &&
  Event::CameraDevice.which.kind_of?(Integer)
end
