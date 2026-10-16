# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Use the 'z' key to start recording and the 'x' key to turn off recording.
mrb_load 'Input.rb'

Graphics.show

# Open the first recording device.

which    = AudioRecorder.ids.first
recorder = AudioRecorder.open which
buffer   = []
status   = false

# Initialize an image for use as a visualizer.

image        = Image.new 'Circle.bmp'
image.dest.x = (DEFAULT_WINDOW_WIDTH - image.dest.width) / 2
image.dest.y = (DEFAULT_WINDOW_HEIGHT - image.dest.height) / 2

while true
  Input.update
  break if Input.quit?
  Graphics.update

  # Input for turning on and off the sound buffering.

  status = true  if Input.trigger? :key_z
  status = false if Input.trigger? :key_x

  # Buffer all incoming sound!

  buffer.push recorder.record if status

  # Update visualizer.

  if status
    image.color.red  += 4
    image.color.blue -= 2
  else
    image.color.red  = 255
    image.color.blue = 255
  end

  image.update
  Graphics.draw
end

# Reference for the wav file format specification:
# https://docs.fileformat.com/audio/wav/

def output_wav(file, buf)
  frequency       = Mixer::DEFAULT_FREQUENCY
  channels        = Mixer::DEFAULT_CHANNELS
  byte_rate       = frequency * channels * 2
  block_align     = channels * 2
  bits_per_sample = 16
  data_size       = buf.bytesize
  riff_size       = 36 + data_size

  file.write 'RIFF', 4
  file.write_32_le riff_size

  file.write 'WAVE', 4

  file.write 'fmt ', 4

  fmt_size     = 16
  audio_format = 1

  file.write_32_le fmt_size
  file.write_16_le audio_format
  file.write_16_le channels
  file.write_32_le frequency
  file.write_32_le byte_rate
  file.write_16_le block_align
  file.write_16_le bits_per_sample

  file.write 'data', 4
  file.write_32_le data_size

  file.write buf, buf.bytesize
end

# Output the wav file with your recording.

file       = File.open 'RecorderOutput.wav', File::MODE_WRITE
output_str = buffer.join

output_wav file, output_str

file.close
