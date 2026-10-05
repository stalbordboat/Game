# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the expected condtions of various environments.

PATH           = 'Environments/SDLFile.rb'
FILENAME_WRITE = 'Test_Write.txt'

send_test :found_at => PATH, :within_block => :constants_defined? do
  constants = %w(
                  MODE_READ
                  MODE_WRITE
                  MODE_APPEND
                  FROM_START
                  FROM_CURRENT
                  FROM_END
                )

  constants.constants_defined? :within => File
end

send_test :found_at => PATH, :within_block => :constant_types? do
  File::MODE_READ.int?    &&
  File::MODE_WRITE.int?   &&
  File::MODE_APPEND.int?  &&
  File::FROM_START.int?   &&
  File::FROM_CURRENT.int? &&
  File::FROM_END.int?
end

send_test :found_at => PATH, :within_block => :class_methods_defined? do
  methods = %w(
                open
                is_archive?
                set_write_dir
              )

  methods.methods_defined? :within => File
end

send_test :found_at => PATH, :within_block => :open_without_block? do
  file         = File.open(FILENAME_WRITE, File::MODE_WRITE)
  status_kind  = file.kind_of?(File)
  status_close = file.close.nil?

  status_close && status_kind
end

send_test :found_at => PATH, :within_block => :open_with_block? do
  status_brackets = File.open(FILENAME_WRITE, File::MODE_WRITE) { |file| file.kind_of?(File) }
  status_do_end   = File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
    file.kind_of?(File)
  end

  status_brackets && status_do_end
end

send_test :found_at => PATH, :within_block => :not_archive? do
  !File.is_archive?
end

send_test :found_at => PATH, :within_block => :instance_methods_defined? do
  file = File.open(FILENAME_WRITE, File::MODE_WRITE)

  methods = %w(
                close
                size
                read
                write
                flush
                move_to
                position
                read_8
                read_16_be
                read_16_le
                read_32_be
                read_32_le
                read_64_be
                read_64_le
                write_8
                write_16_be
                write_16_le
                write_32_be
                write_32_le
                write_64_be
                write_64_le
                size
                length
              )

  methods.methods_defined? :within => file
end

send_test :found_at => PATH, :within_block => :full_write? do
  File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
    str = 'Ok!'
    len = str.length

    file.write(str)

    file.size.eql?(len)
  end
end

send_test :found_at => PATH, :within_block => :full_append? do
  File.open(FILENAME_WRITE, File::MODE_APPEND) do |file|
    str = 'Ok!'
    len = str.length

    file.write(str)

    file.size.eql?(str.length * 2)
  end
end

send_test :found_at => PATH, :within_block => :full_read? do
  File.open FILENAME_WRITE, File::MODE_READ do |file|
    file.read.eql?('Ok!Ok!')
  end
end

send_test :found_at => PATH, :within_block => :clear? do
  str            = ''
  expected_value = 0

  File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
    file.write(str)

    file.size.eql?(expected_value)
  end
end

send_test :found_at => PATH, :within_block => :part_write? do
  File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
    expected_len = 1

    file.write('Ok!', expected_len)

    file.size.eql?(expected_len)
  end
end

send_test :found_at => PATH, :within_block => :part_append? do
  File.open(FILENAME_WRITE, File::MODE_APPEND) do |file|
    str = 'k!'
    len = 2

    file.write(str, len)

    file.size.eql?(len + 1)
  end
end

send_test :found_at => PATH, :within_block => :part_read? do
  # The full read would be "Ok!".
  File.open FILENAME_WRITE, File::MODE_READ do |file|
    expected_str = 'Ok'
    desired_len  = 2

    file.read(desired_len).eql?(expected_str)
  end
end

send_test :found_at => PATH, :within_block => :write_position_test do
  str = 'ABCDEFG'

  File.open FILENAME_WRITE, File::MODE_WRITE do |file|
    file.write str
  end

  true
end

send_test :found_at => PATH, :within_block => :start_position do
  File.open(FILENAME_WRITE, File::MODE_READ) do |file|
    offset = 1
    from   = File::FROM_START
    str    = 'BCDEFG'
    pos    = 7

    file.move_to(offset, from)

    expected_str = file.read.eql?(str)
    expected_pos = file.position.eql?(pos)

    expected_str && expected_pos
  end
end

send_test :found_at => PATH, :within_block => :current_position? do
  File.open(FILENAME_WRITE, File::MODE_READ) do |file|
    offset = 1
    from   = File::FROM_CURRENT
    str    = 'BCDEFG'
    pos    = 7

    file.move_to(offset, from)

    expected_str = file.read.eql?(str)
    expected_pos = file.position.eql?(pos)

    expected_str && expected_pos
  end
end

send_test :found_at => PATH, :within_block => :end_position? do
  File.open(FILENAME_WRITE, File::MODE_READ) do |file|
    offset = 1
    from   = File::FROM_END
    pos    = 8

    file.move_to(offset, from)

    expected_str = file.read.empty?
    expected_pos = file.position.eql?(pos)

    expected_str && expected_pos
  end
end

send_test :found_at => PATH, :within_block => :write_8? do
  File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
    value = 7
    bytes = 1

    file.write_8(value)
    file.position.eql?(bytes)
  end
end

send_test :found_at => PATH, :within_block => :read_8? do
  File.open(FILENAME_WRITE, File::MODE_READ) do |file|
    value       = 7
    bytes       = 1
    data        = file.read_8
    position    = file.position
    status_pos  = position.eql?(bytes)
    status_data = data.eql?(value)

    status_pos && status_data
  end
end

send_test :found_at => PATH, :within_block => :write_16_be? do
  File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
    value = 7
    bytes = 2

    file.write_16_be(value)
    file.position.eql?(bytes)
  end
end

send_test :found_at => PATH, :within_block => :read_16_be? do
  File.open(FILENAME_WRITE, File::MODE_READ) do |file|
    value = 7
    bytes = 2
    data  = file.read_16_be

    file.position.eql?(bytes) && data.eql?(value)
  end
end

send_test :found_at => PATH, :within_block => :write_32_be? do
  File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
    value = 7
    bytes = 4

    file.write_32_be(value)
    file.position.eql?(bytes)
  end
end

send_test :found_at => PATH, :within_block => :read_32_be? do

  File.open(FILENAME_WRITE, File::MODE_READ) do |file|
    value = 7
    bytes = 4
    data  = file.read_32_be

    file.position.eql?(bytes) && data.eql?(value)
  end
end

send_test :found_at => PATH, :within_block => :write_64_be? do
  File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
    value = 7
    bytes = 8

    file.write_64_be(value)

    file.position.eql?(bytes)
  end
end

send_test :found_at => PATH, :within_block => :read_64_be? do
  File.open(FILENAME_WRITE, File::MODE_READ) do |file|
    value = 7
    bytes = 8
    data  = file.read_64_be

    file.position.eql?(bytes) && data.eql?(value)
  end
end

send_test :found_at => PATH, :within_block => :write_16_le? do
  File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
    value = 7
    bytes = 2

    file.write_16_le(value)

    file.position.eql?(bytes)
  end
end

send_test :found_at => PATH, :within_block => :read_16_le? do
  File.open(FILENAME_WRITE, File::MODE_READ) do |file|
    value = 7
    bytes = 2
    data  = file.read_16_le

    file.position.eql?(bytes) && data.eql?(value)
  end
end

send_test :found_at => PATH, :within_block => :write_32_le? do
  File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
    value = 7
    bytes = 4

    file.write_32_le(value)

    file.position.eql?(bytes)
  end
end

send_test :found_at => PATH, :within_block => :read_32_le? do
  File.open(FILENAME_WRITE, File::MODE_READ) do |file|
    value = 7
    bytes = 4
    data  = file.read_32_le

    file.position.eql?(bytes) && data.eql?(value)
  end
end

send_test :found_at => PATH, :within_block => :write_64_le? do
  File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
    value = 7
    bytes = 8

    file.write_64_le(value)

    file.position.eql?(bytes)
  end
end

send_test :found_at => PATH, :within_block => :read_64_le? do
  File.open(FILENAME_WRITE, File::MODE_READ) do |file|
    value = 7
    bytes = 8
    data  = file.read_64_le

    file.position.eql?(bytes) && data.eql?(value)
  end
end

send_test :found_at => PATH, :within_block => :flush? do
  File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
    file.flush.nil?
  end
end
