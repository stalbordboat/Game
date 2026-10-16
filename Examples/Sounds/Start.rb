# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Audio playback demonstration.
mrb_load 'Input.rb'
   
sound_a = Sound.new 'Vocals.wav', 0
sound_b = Sound.new 'Drums.wav',  1

# Play overlapping samples.
sound_a.play
sound_b.play

# Keep the program running until the sounds stop playing.
loop { break unless sound_a.playing? && sound_b.playing? }
