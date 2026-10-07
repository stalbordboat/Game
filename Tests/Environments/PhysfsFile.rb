# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the expected condtions of various environments.

PATH               = 'Environments/PhysfsFile.rb'
FILENAME_READ      = 'Test_Read.txt'
FILENAME_READ16_BE = 'Test_Read_16_BE.bin'
FILENAME_READ32_BE = 'Test_Read_32_BE.bin'
FILENAME_READ64_BE = 'Test_Read_64_BE.bin'
FILENAME_READ16_LE = 'Test_Read_16_LE.bin'
FILENAME_READ32_LE = 'Test_Read_32_LE.bin'
FILENAME_READ64_LE = 'Test_Read_64_LE.bin'
FILENAME_WRITE     = 'Test_Write.txt'
FILENAME_READ      = 'Test_Read.txt'

case Env['ARCHIVE_HAS_WRITE']
when 'false'
  send_test :found_at => PATH, :within_block => :not_archive? do
    File.is_archive?
  end

  send_test :found_at => PATH, :within_block => :full_read? do
    File.open(FILENAME_READ, File::MODE_READ) { |file| file.read.eql? "Ok!Ok!\n" }
  end

  send_test :found_at => PATH, :within_block => :part_read? do
    File.open(FILENAME_READ, File::MODE_READ) { |file| file.read(2).eql? 'Ok' }
  end

  send_test :found_at => PATH, :within_block => :read_16_be? do
    value = 7
    bytes = 2

    File.open(FILENAME_READ16_BE, File::MODE_READ) do |file|
      data = file.read_16_be

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => PATH, :within_block => :read_32_be? do
      value = 7
      bytes = 4

      File.open(FILENAME_READ32_BE, File::MODE_READ) do |file|
        data = file.read_32_be

        file.position.eql?(bytes) && data.eql?(value)
      end
  end

  send_test :found_at => PATH, :within_block => :read_64_be? do
      value = 7
      bytes = 8

      File.open(FILENAME_READ64_BE, File::MODE_READ) do |file|
        data = file.read_64_be

        file.position.eql?(bytes) && data.eql?(value)
      end
  end

  send_test :found_at => PATH, :within_block => :read_16_le? do
    value = 7
    bytes = 2

    File.open(FILENAME_READ16_LE, File::MODE_READ) do |file|
      data = file.read_16_le

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => PATH, :within_block => :read_32_le? do
    value = 7
    bytes = 4

    File.open(FILENAME_READ32_LE, File::MODE_READ) do |file|
      data = file.read_32_le

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => PATH, :within_block => :read_64_le? do
    value = 7
    bytes = 8

    File.open(FILENAME_READ64_LE, File::MODE_READ) do |file|
      data = file.read_64_be

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

when 'true'

  send_test :found_at => PATH, :within_block => :full_write? do
    File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
      str = 'Ok!'
      len = str.length

      file.write str

      file.size.eql? str.length
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
    File.open(FILENAME_WRITE, File::MODE_READ) { |file| file.read.eql? 'Ok!Ok!' }
  end

  send_test :found_at => PATH, :within_block => :clear? do
    File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
      file.write('')

      file.size.eql?(0)
    end
  end

  send_test :found_at => PATH, :within_block => :part_write? do
    File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
      str = 'Ok!'
      len = 1

      file.write(str, len)

      file.size.eql?(len)
    end
  end

  send_test :found_at => PATH, :within_block => :part_append? do
    File.open(FILENAME_WRITE, File::MODE_APPEND) do |file|
      str = 'k!'
      len = 2

      file.write(str, len)

      file.size.eql?(str.length + 1)
    end
  end

  send_test :found_at => PATH, :within_block => :part_read? do
    File.open(FILENAME_WRITE, File::MODE_READ) { |file| file.read(2).eql?('Ok') }
  end

  send_test :found_at => PATH, :within_block => :write_position_test do
    str = 'ABCDEFG'

    File.open(FILENAME_WRITE, File::MODE_WRITE) { |file| file.write(str) }

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
    value = 7
    bytes = 1

    File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
      file.write_8(value)
      file.position.eql?(bytes)
    end
  end

  send_test :found_at => PATH, :within_block => :read_8? do
    value = 7
    bytes = 1

    File.open(FILENAME_WRITE, File::MODE_READ) do |file|
      data = file.read_8

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => PATH, :within_block => :write_16_be? do
    value = 7
    bytes = 2

    File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
      file.write_16_be(value)
      file.position.eql?(bytes)
    end
  end

  send_test :found_at => PATH, :within_block => :read_16_be? do
    value = 7
    bytes = 2

    File.open(FILENAME_WRITE, File::MODE_READ) do |file|
      data = file.read_16_be

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => PATH, :within_block => :write_32_be? do
    value = 7
    bytes = 4

    File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
      file.write_32_be(value)
      file.position.eql?(bytes)
    end
  end

  send_test :found_at => PATH, :within_block => :read_32_be? do
    value = 7
    bytes = 4

    File.open(FILENAME_WRITE, File::MODE_READ) do |file|
      data = file.read_32_be

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => PATH, :within_block => :write_64_be? do
    value = 7
    bytes = 8

    File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
      file.write_64_be(value)
      file.position.eql?(bytes)
    end
  end

  send_test :found_at => PATH, :within_block => :read_64_be? do
    value = 7
    bytes = 8

    File.open(FILENAME_WRITE, File::MODE_READ) do |file|
      data = file.read_64_be

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => PATH, :within_block => :write_16_le? do
    value = 7
    bytes = 2

    File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
      file.write_16_le(value)
      file.position.eql?(bytes)
    end
  end

  send_test :found_at => PATH, :within_block => :read_16_le? do
    value = 7
    bytes = 2

    File.open(FILENAME_WRITE, File::MODE_READ) do |file|
      data = file.read_16_le

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => PATH, :within_block => :write_32_le? do
    value = 7
    bytes = 4

    File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
      file.write_32_le(value)
      file.position.eql?(bytes)
    end
  end

  send_test :found_at => PATH, :within_block => :read_32_le? do
    value = 7
    bytes = 4

    File.open(FILENAME_WRITE, File::MODE_READ) do |file|
      data = file.read_32_le

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => PATH, :within_block => :write_64_le? do
    value = 7
    bytes = 8

    File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
      file.write_64_be(value)
      file.position.eql?(bytes)
    end
  end

  send_test :found_at => PATH, :within_block => :read_64_le? do
    value = 7
    bytes = 8

    File.open(FILENAME_WRITE, File::MODE_READ) do |file|
      data = file.read_64_be

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => PATH, :within_block => :flush? do
    File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
      begin
        file.flush
      rescue
        clear_error
        return false
      end
    end

    true
  end
end
