# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Timer.rb:'

%w(ABSURD_FPS).const_defined_tests found_at, Timer

%w(
wait
ticks
counter
frequency
benchmark
).response_tests found_at, Timer

timer = Timer.new

%w(
counted_frames
counted_frames=
start_ticks
paused_ticks
start
stop
pause
resume
ticks
average_fps
).response_tests found_at, timer
