# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the Audio subsystem.

PATH      = 'Audio/AudioRecorder.rb'
recorders = []

send_test :found_at => PATH, :within_block => :constants_defined? do
  constants = %w(
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

  constants.constants_defined? :within => AudioRecorder
end

send_test :found_at => PATH, :within_block => :class_methods_defined? do
  methods = %w(ids name open)

  methods.methods_defined? :within => AudioRecorder
end

send_test :found_at => PATH, :within_block => :constants_types? do
  AudioRecorder::FORMAT_U8.int?      &&
  AudioRecorder::FORMAT_S8.int?      &&
  AudioRecorder::FORMAT_S16.int?     &&
  AudioRecorder::FORMAT_S32.int?     &&
  AudioRecorder::FORMAT_F32.float?   &&
  AudioRecorder::FORMAT_S16LE.int?   &&
  AudioRecorder::FORMAT_S16BE.int?   &&
  AudioRecorder::FORMAT_S32BE.int?   &&
  AudioRecorder::FORMAT_F32LE.float? &&
  AudioRecorder::FORMAT_F32BE.float? 
end

send_test :found_at => PATH, :within_block => :establish_recorder? do
  ids = AudioRecorder.ids
  status = false

  if ids.kind_of?(Array)
    ids.each do |which|
      name   = AudioRecorder.name(which)
      status = name.string? && !name.empty?
    end
  end

  status
end

send_test :found_at => PATH, :within_block => :default_open? do
  ids = AudioRecorder.ids

  ids.each { |which| recorders.push(AudioRecorder.open(which)) }

  recorders.size.eql?(ids.size)
end

send_test :found_at => PATH, :within_block => :set_volume? do
  value  = 0.0
  status = false

  recorders.each do |r|
    r.volume = value

    break unless status = r.volume.eql?(value)
  end

  status
end

send_test :found_at => PATH, :within_block => :name? do
  status = false

  recorders.each { |r| break unless status = r.name.string? && !r.name.empty? }

  status
end

send_test :found_at => PATH, :within_block => :record? do
  status = false
  count  = 0
  limit  = 64

  simulate_main_loop do
    recorders.each { |r| status = r.record.string? }
    break if count.eql?(limit)
    count += 1
  end

  status
end

send_test :found_at => PATH, :within_block => :closed? do
  status = false

  recorders.each { |r| break unless status = r.close.nil? && r.closed? }

  status
end
