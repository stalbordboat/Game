# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/AudioRecorder.rb:'

%w(
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
).const_defined_tests found_at, AudioRecorder

%w(
ids
name
open
).response_tests found_at, AudioRecorder

ids = AudioRecorder.ids

unless ids.empty?

first    = ids.first
recorder = AudioRecorder.open first

%w(
close
closed?
name
record
volume
volume=
).response_tests found_at, recorder

recorder.close
end
