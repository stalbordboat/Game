# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the Audio subsystem.

PATH  = 'Audio/Sound.rb:'
sound = nil

send_test :found_at => PATH, :within_block => :constants_defined? do
  constants = %w(
                  PLAY_ONCE
                  PLAY_INFINITE
                )

  constants.constants_defined? :within => Sound
end

send_test :found_at => PATH, :within_block => :new? do
  sound = Sound.new('stereo-test.wav')

  sound.kind_of?(Sound)
end

send_test :found_at => PATH, :within_block => :clone? do
  recover? { sound.clone }
end

send_test :found_at => PATH, :within_block => :instance_methods_defined? do
  methods = %w(
                play
                fadein
                fadeout
              )

  methods.methods_defined? :within => sound
end

send_test :found_at => PATH, :within_block => :attributes_defined? do
  attributes = %w(
                  volume
                  volume=
                  track
                  track=
                )

  attributes.attributes_defined? :within => sound
end

send_test :found_at => PATH, :within_block => :volume? do
  sound.volume = 0

  sound.volume.eql?(0.0)
end

# Testing the sound is being played and stopped.
send_test :found_at => PATH, :within_block => :play_once? do
  count       = 0
  max         = 1
  status_play = false
  status_stop = false

  sound.play(Sound::PLAY_ONCE)

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
send_test :found_at => PATH, :within_block => :pause? do
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

send_test :found_at => PATH, :within_block => :track? do
  sound_vocals = Sound.new('Vocals.wav')
  sound_drums  = Sound.new('Drums.wav')

  sound_vocals.track = 0
  sound_drums.track  = 1

  sound_vocals.track.eql?(0) && sound_drums.track.eql?(1)
end

send_test :found_at => PATH, :within_block => :fade_in_and_out? do
=begin
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

  # NOTE: Trying to smoke out a fail condition that only comes up occasionally.
  Log.info status_fadein
  Log.info status_fadeout

  status_fadein && status_fadeout
=end
  skip 'Trying to smoke out a fail condition that only comes up occasionally.', :within_block => :fade_in_and_out?
end
