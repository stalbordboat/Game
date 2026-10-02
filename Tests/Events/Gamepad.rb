# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Event subsystem.

path            = 'Events/Gamepad.rb'
# Name + buttons. This part never changes.
PARTIAL_MAPPING = 'Generic Gamepad,a:b0,b:b1,x:b2,y:b3,start:b7,back:b6,leftx:a0,lefty:a1'.freeze
GUID            = '03000000abcd00001234000000000000'.freeze
MAPPING         =  GUID + ',' + PARTIAL_MAPPING

def available?
  !Gamepad.ids.empty?
end

def test_all_gamepads
  Gamepad.ids.each do |id|
    gamepad = Gamepad.open(id)

    yield(gamepad)

    gamepad.close
  end
end

send_test :found_at => path, :within => :check_ids? do
  Gamepad.ids.kind_of? Array
end

if available?

  send_test :found_at => path, :within => :check_name? do
    status = false
    ids    = Gamepad.ids

    ids.each do |id|
      if Gamepad.name(id).kind_of? String
        return false if Gamepad.name(id).empty?
      end
    end

    # This assumes that there are no gamepads available, which isn't a fail condition.
    true
  end

  send_test :found_at => path, :within => :check_mappings? do
    status_added   = Gamepad.add_mapping(MAPPING).eql? :added
    status_updated = Gamepad.add_mapping(MAPPING).eql? :updated
    status_reload  = Gamepad.reload_mappings.nil?

    status_added && status_updated && status_reload
  end

  send_test :found_at => path, :within => :opening_and_closing? do
    gamepads     = []
    status_open  = false
    status_close = false

    Gamepad.ids.each { |id| gamepads.push(Gamepad.open(id)) }

    gamepads.each do |gamepad|
      break unless status_open = gamepad.kind_of?(Gamepad)
      gamepad.close
      status_close = gamepad.closed?
    end

    status_open && status_close
  end

  send_test :found_at => path, :within => :name? do
    status = nil

    test_all_gamepads { |gamepad| status = !gamepad.name.empty? if gamepad.name.kind_of?(String) }

    status
  end

  send_test :found_at => path, :within => :rumble? do
    status = true

    test_all_gamepads { |gamepad| gamepad.rumble(Gamepad::RUMBLE_MIN, Gamepad::RUMBLE_MIN, 8).nil? if gamepad.rumble? }

    status
  end

  send_test :found_at => path, :within => :rumble_triggers? do
    status = true
    left   = Gamepad::RUMBLE_MIN
    right  = Gamepad::RUMBLE_MIN

    test_all_gamepads { |gamepad| gamepad.rumble_triggers(left, right, 8).nil? if gamepad.rumble_triggers? }

    status
  end

  send_test :found_at => path, :within => :led? do
    status = true

    test_all_gamepads { |gamepad| gamepad.led.nil? if gamepad.led? }

    status
  end

  send_test :found_at => path, :within => :power_state? do
    status = true

    test_all_gamepads do |gamepad|
      state  = gamepad.power_state
      status = state.eql?(Gamepad::POWERSTATE_UNKNOWN)    ||
               state.eql?(Gamepad::POWERSTATE_ON_BATTERY) ||
               state.eql?(Gamepad::POWERSTATE_NO_BATTERY) ||
               state.eql?(Gamepad::POWERSTATE_CHARGING)   ||
               state.eql?(Gamepad::POWERSTATE_CHARGED)
    end


    status
  end

  send_test :found_at => path, :within => :percent? do
    status  = true
    state   = Gamepad::POWERSTATE_UNKNOWN
    percent = 0

    test_all_gamepads do |gamepad|
      state   = gamepad.power_state
      percent = gamepad.percent
    end

    case state
    when Gamepad::POWERSTATE_UNKNOWN
      status = percent.eql?(-1)
    else
      status = percent > 0
    end

    status
  end

  send_test :found_at => path, :within => :connection_state? do
    status = true

    test_all_gamepads do |gamepad|
      state  = gamepad.connection_state
      status = state.eql?(Gamepad::CONNECTION_UNKNOWN)  ||
               state.eql?(Gamepad::CONNECTION_WIRED)    ||
               state.eql?(Gamepad::CONNECTION_WIRELESS)
    end

    status
  end

  send_test :found_at => path, :within => :mapping? do
    status_initial_mapping = true
    status_set_mapping     = true

    test_all_gamepads do |gamepad|
      status_initial_mapping = !gamepad.mapping.empty?
      gamepad.mapping        = MAPPING
      status_set_mapping     = gamepad.mapping.include?(PARTIAL_MAPPING)
    end

    status_initial_mapping && status_set_mapping
  end

  send_test :found_at => path, :within => :guid? do
    status = true

    test_all_gamepads do |gamepad|
      guid   = gamepad.mapping.split(',').first
      status = gamepad.guid.eql?(guid)
    end

    status
  end
end
