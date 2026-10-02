# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the General subsystem.

path = 'General/Timer.rb'

# Methods used in testing.

def simulate_main_loop_with_timer(timer)
  while true
    Input.update

    begin
      Graphics.update
    rescue
      break
    end

    yield

    begin
      Graphics.draw
    rescue
      break
    end

    timer.counted_frames += 1
  end
end

# Constants

send_test :found_at => path, :within => :self_constants_types? do
  Timer::ABSURD_FPS.int?
end

send_test :found_at => path, :within => :constants_values? do
  Timer::ABSURD_FPS.eql?(2000000)
end

# Class Methods

send_test :found_at => path, :within => :self_methods_types? do
  Timer.wait(0).nil?     &&
  Timer.ticks.int?       &&
  Timer.counter.int?     &&
  Timer.frequency.int?   &&
  Timer.benchmark{}.int?
end

# Timer.wait, Timer.counter, and Timer.frequency are all tested here.
send_test :found_at => path, :within => :self_benchmark_value? do
  seconds = Timer.benchmark { Timer.wait(1000) }

  seconds.eql?(1)
end

send_test :found_at => path, :within => :self_ticks_value? do
  prev   = 0
  curr   = 0
  status = nil

  simulate_main_loop do
    curr   = Timer.ticks
    status = curr.greater_than?(prev)
    break if status
    prev   = curr
  end

  status
end

# Instance Methods and Attributes

send_test :found_at => path, :within => :instance_method_types? do
  timer = Timer.new

  timer.kind_of?(Timer)     &&
  timer.start.bool?         &&
  timer.stop.bool?          &&
  timer.pause.bool?         &&
  timer.resume.bool?        &&
  timer.ticks.int?          &&
  timer.average_fps.float? || timer.average_fps.int?
end

send_test :found_at => path, :within => :attribute_types? do
  timer = Timer.new

  timer.counted_frames.int?      &&
  timer.counted_frames=(10).int? &&
  timer.start_ticks.int?         &&
  timer.paused_ticks.int?
end

send_test :found_at => path, :within => :instance_method_values? do
  timer      = Timer.new
  status     = nil
  count      = 0
  limit      = 127
  ticks_base = 1000

  Graphics.show

  # Start Timer and calculate the average fps.

  status = timer.start.eql?(true) && timer.start_ticks.greater_than?(ticks_base)

  if status
    simulate_main_loop_with_timer(timer) do
      status = timer.average_fps.to_i.greater_than?(24)
      break if count.eql?(limit)
      count += 1
    end
  end

  # Pause Timer and see if the timer is still ticking(it shouldn't be.)
  if status
    count = 0
    prev  = 0
    curr  = 0

    status = timer.pause.eql?(true) && timer.paused_ticks.greater_than?(ticks_base)

    simulate_main_loop_with_timer(timer) do
      curr   = timer.ticks
      status = curr.eql?(prev)
      break if count.eql?(limit)
      count += 1
      prev   = curr
    end
  end

  # Resume Timer, it should be ticking this time.

  if status
    count = 0
    prev  = 0
    curr  = 0

    status = timer.resume.eql?(true) && timer.paused_ticks.eql?(0)

    simulate_main_loop_with_timer(timer) do
      curr   = timer.ticks
      status = curr.greater_than?(prev)
      break if count.eql?(limit)
      count += 1
      prev   = curr
    end
  end

  # Stop Timer

  if status
    status = timer.stop.eql?(false) && timer.start_ticks.eql?(0)
  end

  Graphics.hide

  status
end
