# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Sound.rb:'

%w(
PLAY_ONCE
PLAY_INFINITE
).const_defined_tests found_at, Sound

path  = 'stereo-test.wav'
sound = Sound.new path

%w(
volume
volume=
track
track=
play
fadein
fadeout
).response_tests found_at, sound
