# MIT LICENSE - Copyright (c) Ralph Desir 2026

class ::Timer
  attr_accessor :counted_frames
  attr_reader   :start_ticks
  attr_reader   :paused_ticks

  ABSURD_FPS = 2000000

  def self.benchmark
    freq  = Timer.frequency
    start = Timer.counter

    yield

    _end = Timer.counter

    (_end - start) / freq
  end

  def initialize
    @paused         = false
    @started        = false
    @counted_frames = 0
    @start_ticks    = 0
    @paused_ticks   = 0
  end

  def start
    @started      = true
    @paused       = false
    @start_ticks  = Timer.ticks
    @paused_ticks = 0

    @started
  end

  def stop
    @started      = false
    @paused       = false
    @start_ticks  = 0
    @paused_ticks = 0

    @started
  end

  def pause
    if(@started && !@paused)
      @paused       = true
      @paused_ticks = (Timer.ticks - @start_ticks)
      @start_ticks  = 0
    end

    @paused
  end

  def resume
    if(@started && @paused)
      @paused       = false
      @start_ticks  = (Timer.ticks - @paused_ticks)
      @paused_ticks = 0
    end

    @paused
  end

  def ticks
    time = 0

    if(@started)
      if(@paused)
        time = @paused_ticks
      else
        time = (Timer.ticks - @start_ticks)
      end
    end

    time
  end

  def average_fps
    fps = (@counted_frames / (self.ticks / 1000.to_f))

    fps = 0 if fps > ABSURD_FPS

    fps
  end
end
