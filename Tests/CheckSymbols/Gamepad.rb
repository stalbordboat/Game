# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Gamepad.rb:'

%w(
RUMBLE_MAX
RUMBLE_MIN
POWERSTATE_UNKNOWN
POWERSTATE_ON_BATTERY
POWERSTATE_NO_BATTERY
POWERSTATE_CHARGING
POWERSTATE_CHARGED
CONNECTION_UNKNOWN
CONNECTION_WIRED
CONNECTION_WIRELESS
).const_defined_tests found_at, Gamepad

%w(ids name add_mapping reload_mappings open).response_tests found_at, Gamepad

ids = Gamepad.ids

unless ids.empty?
  first   = ids.first
  gamepad = Gamepad.open first

  %w(
close
closed?
name
rumble?
rumble
rumble_triggers?
rumble_triggers
led?
led
power_state
percent
connected?
connection_state
mapping
mapping=
guid
).response_tests found_at, gamepad

  gamepad.close
end
