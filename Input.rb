# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Input Event Administration
#
# This Input module handles Keyboard and Gamepad events. It will automatically reopen any gamepad if it was unplugged.

module Input
  @prev = {}

  @held            = {}
  @repeat_delay    = 24 # frames before repeat starts
  @repeat_interval = 1  # frames between repeats

  def self.update
    update_prev

    while Event.fetching?
      update_quit
      update_gamepad
      update_keyboard
    end
  end

  def self.quit?
    @quit
  end

  def self.state(input)
    instance_variable_get("@#{input}")
  end

  def self.press?(button)
    state(button)
  end

  def self.trigger?(button)
    ivar     = :"@#{button}"
    current  = instance_variable_get(ivar)
    previous = @prev[ivar]

    current && !previous
  end

  def self.repeat?(button)
    ivar    = :"@#{button}"
    current = instance_variable_get(ivar)

    return false unless current

    held = @held[ivar] || 0

    # First press (same as trigger)
    return true if held == 1

    # After delay, repeat at interval
    return (held - @repeat_delay) % @repeat_interval == 0 if held > @repeat_delay

    false
  end

  private

  def self.update_prev
    instance_variables.each do |ivar|
      prefix_button = ivar.to_s.start_with?('@button_')
      prefix_key    = ivar.to_s.start_with?('@key_')
      next unless prefix_button || prefix_key

      current  = instance_variable_get(ivar)
      previous = @prev[ivar]

      # store previous state
      @prev[ivar] = current

      # update held duration
      if current
        @held[ivar] ||= 0
        @held[ivar] += 1
      else
        @held[ivar] = 0
      end
    end
  end

  def self.update_quit
    case Event.type
    when Event::QUIT
      @quit = true
    when Event::KEY_DOWN
      @quit = true if Event::Keyboard.key == Event::Keyboard::KEY_ESC
    end
  end

  def self.update_gamepad
    case Event.type
    when Event::GAMEPAD_BUTTON_DOWN, Event::GAMEPAD_BUTTON_UP
      @button_timestamp = Event::GamepadButton.timestamp
      @button_any       = Event::GamepadButton.down?

      case Event::GamepadButton.button
      when Event::GamepadButton::S
        @button_s           = Event::GamepadButton.down?
      when Event::GamepadButton::E
        @button_e           = Event::GamepadButton.down?
      when Event::GamepadButton::W
        @button_w           = Event::GamepadButton.down?
      when Event::GamepadButton::N
        @button_n           = Event::GamepadButton.down?
      when Event::GamepadButton::BACK
        @button_back        = Event::GamepadButton.down?
      when Event::GamepadButton::GUIDE
        @button_guide       = Event::GamepadButton.down?
      when Event::GamepadButton::START
        @button_start       = Event::GamepadButton.down?
      when Event::GamepadButton::L1
        @button_l1          = Event::GamepadButton.down?
      when Event::GamepadButton::R1
        @button_r1          = Event::GamepadButton.down?
      when Event::GamepadButton::UP
        @button_up          = Event::GamepadButton.down?
      when Event::GamepadButton::DOWN
        @button_down        = Event::GamepadButton.down?
      when Event::GamepadButton::LEFT
        @button_left        = Event::GamepadButton.down?
      when Event::GamepadButton::RIGHT
        @button_right       = Event::GamepadButton.down?
      when Event::GamepadButton::LEFT_STICK
        @button_left_stick  = Event::GamepadButton.down?
      when Event::GamepadButton::RIGHT_STICK
        @button_right_stick = Event::GamepadButton.down?
      end
    when Event::GAMEPAD_AXIS_MOTION
      @axis_value     = Event::GamepadAxis.value
      @axis_value     = 0 if Math.abs(@axis_value) < Event::GamepadAxis::DEFAULT_DEADZONE
      @axis_direction = Event::GamepadAxis.axis
    when Event::GAMEPAD_REMOVED
      @device_timestamp = Event::GamepadDevice.timestamp
      @device_which     = Event::GamepadDevice.which

      @gamepads.each { |gamepad| gamepad.close unless gamepad.connected? }
    when Event::GAMEPAD_ADDED
      @device_timestamp = Event::GamepadDevice.timestamp
      @device_which     = Event::GamepadDevice.which
      @gamepads       ||= [] 

      @gamepads.push(Gamepad.open(@device_which))
    end
  end

  def self.update_keyboard
    case Event.type
    when Event::KEY_DOWN, Event::KEY_UP
      @key_timestamp = Event::Keyboard.timestamp
      @key_repeat    = Event::Keyboard.repeat?
      @key_any       = Event::Keyboard.down?

      case Event::Keyboard.key
      when Event::Keyboard::KEY_Z
        @key_z         = Event::Keyboard.down?
      when Event::Keyboard::KEY_X
        @key_x         = Event::Keyboard.down?
      when Event::Keyboard::KEY_I
        @key_i         = Event::Keyboard.down?
      when Event::Keyboard::KEY_K
        @key_k         = Event::Keyboard.down?
      when Event::Keyboard::KEY_J
        @key_j         = Event::Keyboard.down?
      when Event::Keyboard::KEY_L
        @key_l         = Event::Keyboard.down?
      when Event::Keyboard::KEY_E
        @key_e         = Event::Keyboard.down?
      when Event::Keyboard::KEY_F
        @key_f         = Event::Keyboard.down?
      when Event::Keyboard::KEY_Q
        @key_q         = Event::Keyboard.down?
      when Event::Keyboard::KEY_C
        @key_c         = Event::Keyboard.down?
      when Event::Keyboard::KEY_W, Event::Keyboard::KEY_UP
        @key_w         = Event::Keyboard.down?
      when Event::Keyboard::KEY_S, Event::Keyboard::KEY_DOWN
        @key_s         = Event::Keyboard.down?
      when Event::Keyboard::KEY_A, Event::Keyboard::KEY_LEFT
        @key_a         = Event::Keyboard.down?
      when Event::Keyboard::KEY_D, Event::Keyboard::KEY_RIGHT
        @key_d         = Event::Keyboard.down?
      when Event::Keyboard::KEY_BACKSPACE
        @key_backspace = Event::Keyboard.down?
      end
    end
  end
end
