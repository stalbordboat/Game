# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Represents Audio Recording Devices

class AudioRecorder
  def self.open(which, format=FORMAT_S16, channels=2, freq=44100)
    recorder = self.new(which, format, channels, freq)

    if block_given?
      begin
        obj = yield(recorder)
      ensure
        recorder.close
        obj
      end
    else
      recorder
    end
  end
end
