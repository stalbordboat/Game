# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the Audio subsystem.

PATH = 'Audio/Mixer.rb:'

send_test :found_at => PATH, :within_block => :constants_defined? do
  constants = %w(
                  DEFAULT_FREQUENCY
                  DEFAULT_FORMAT
                  DEFAULT_CHANNELS
                  DEFAULT_VOLUME
                  COUNT_TRACKS
                  FORMAT_U8
                  FORMAT_S8
                  FORMAT_S16
                  FORMAT_S32
                  FORMAT_F32
                  FORMAT_S16LE
                  FORMAT_S16BE
                  FORMAT_S32LE
                  FORMAT_S32BE
                  FORMAT_F32LE
                  FORMAT_F32BE
                )

  constants.constants_defined? :within => Mixer
end

send_test :found_at => PATH, :within_block => :functions_defined? do
  functions = %w(
                  reopen
                  stop
                  fadeout
                  volume
                  volume=
                )

  functions.methods_defined? :within => Mixer
end

# A successful run of :reopen should return nil.
# A failure would raise and exception.
send_test :found_at => PATH, :within_block => :reopen? do
  Mixer.reopen.nil?
end
