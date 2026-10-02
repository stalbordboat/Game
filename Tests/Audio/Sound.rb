# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the audio subsystem.

path  = 'Audio/Sound.rb:'
sound = nil

send_test :found_at => path, :within => :new do
  sound = Sound.new 'stereo-test.wav'

  sound.kind_of? Sound
end

# The Sound object can't be cloned so calling clone or dup will
# raise an exception. Since this is expected behavior, it must
# be treated as a passing test!
send_test :found_at => path, :within => :clone do
  recover? { sound.clone }
end

send_test :found_at => path, :within => :volume do
  sound.volume = 0

  sound.volume.eql? 0.0
end

# Testing the sound is being played and stopped.
send_test :found_at => path, :within => :play_once do
  count       = 0
  max         = 1
  status_play = false
  status_stop = false

  sound.play Sound::PLAY_ONCE

  simulate_main_loop do
    status_play = sound.playing?
    count += 1
    break if count >= max
  end

  sound.stop
  status_stop = sound.playing?

  status_play && !status_stop
end

# Testing if pausing and resuming works.
send_test :found_at => path, :within => :pause do
  count         = 0
  max           = 1
  status_pause  = false
  status_resume = false

  sound.play
  sound.pause

  simulate_main_loop do
    status_pause = sound.paused?
    count += 1
    break if count >= max
  end

  sound.resume

  count = 0

  simulate_main_loop do
    status_resume = sound.playing?
    count += 1
    break if count >= max
  end

  sound.stop

  status_pause && status_resume
end

# The Sound object's track attribute must get what was set.
send_test :found_at => path, :within => :track do
  sound_vocals = Sound.new 'Vocals.wav'
  sound_drums  = Sound.new 'Drums.wav'

  sound_vocals.track = 0
  sound_drums.track  = 1

  sound_vocals.track.eql?(0) && sound_drums.track.eql?(1)
end

# Testing fade-in and fade-out playback.
send_test :found_at => path, :within => :fades do
  count          = 0
  status_fadein  = false
  status_fadeout = false

  simulate_main_loop do
    sound.fadein
    status_fadein = sound.playing?
    count += 1
    break if count >= 1
  end

  count = 0

  simulate_main_loop do
    sound.fadeout 1
    status_fadeout = sound.playing?
    count += 1
    break if count >= 2000
  end

  status_fadein && status_fadeout
end
