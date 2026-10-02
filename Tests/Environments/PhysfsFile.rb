# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the expected condtions of various environments.

path               = 'Environments/PhysfsFile.rb'
filename_read      = 'Test_Read.txt'
filename_read16_be = 'Test_Read_16_BE.bin'
filename_read32_be = 'Test_Read_32_BE.bin'
filename_read64_be = 'Test_Read_64_BE.bin'
filename_read16_le = 'Test_Read_16_LE.bin'
filename_read32_le = 'Test_Read_32_LE.bin'
filename_read64_le = 'Test_Read_64_LE.bin'
filename_write     = 'Test_Write.txt'
filename_read      = 'Test_Read.txt'

case Env['ARCHIVE_HAS_WRITE']
when 'false'
  send_test :found_at => path, :within => :not_archive? do
    File.is_archive?
  end

  send_test :found_at => path, :within => :full_read? do
    File.open(filename_read, File::MODE_READ) { |file| file.read.eql? "Ok!Ok!\n" }
  end

  send_test :found_at => path, :within => :part_read? do
    File.open(filename_read, File::MODE_READ) { |file| file.read(2).eql? 'Ok' }
  end

  send_test :found_at => path, :within => :read_16_be? do
    value = 7
    bytes = 2

    File.open filename_read16_be, File::MODE_READ do |file|
      data = file.read_16_be

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => path, :within => :read_32_be? do
      value = 7
      bytes = 4

      File.open filename_read32_be, File::MODE_READ do |file|
        data = file.read_32_be

        file.position.eql?(bytes) && data.eql?(value)
      end
  end

  send_test :found_at => path, :within => :read_64_be? do
      value = 7
      bytes = 8

      File.open filename_read64_be, File::MODE_READ do |file|
        data = file.read_64_be

        file.position.eql?(bytes) && data.eql?(value)
      end
  end

  send_test :found_at => path, :within => :read_16_le? do
    value = 7
    bytes = 2

    File.open filename_read16_le, File::MODE_READ do |file|
      data = file.read_16_le

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => path, :within => :read_32_le? do
    value = 7
    bytes = 4

    File.open filename_read32_le, File::MODE_READ do |file|
      data = file.read_32_le

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => path, :within => :read_64_le? do
    value = 7
    bytes = 8

    File.open filename_read64_le, File::MODE_READ do |file|
      data = file.read_64_be

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

when 'true'

  send_test :found_at => path, :within => :full_write? do
    File.open filename_write, File::MODE_WRITE do |file|
      str = 'Ok!'
      len = str.length

      file.write str

      file.size.eql? str.length
    end
  end

  send_test :found_at => path, :within => :full_append? do
    File.open filename_write, File::MODE_APPEND do |file|
      str = 'Ok!'
      len = str.length

      file.write str

      file.size.eql? (str.length * 2)
    end
  end

  send_test :found_at => path, :within => :full_read? do
    File.open(filename_write, File::MODE_READ) { |file| file.read.eql? 'Ok!Ok!' }
  end

  send_test :found_at => path, :within => :clear? do
    File.open(FILENAME_WRITE, File::MODE_WRITE) do |file|
      file.write ''

      file.size.eql? 0
    end
  end

  send_test :found_at => path, :within => :part_write? do
    File.open(filename_write, File::MODE_WRITE) do |file|
      str = 'Ok!'
      len = 1

      file.write str, len

      file.size.eql? len
    end
  end

  send_test :found_at => path, :within => :part_append? do
    File.open filename_write, File::MODE_APPEND do |file|
      str = 'k!'
      len = 2

      file.write str, len

      file.size.eql? (str.length + 1)
    end
  end

  send_test :found_at => path, :within => :part_read? do
    File.open(filename_write, File::MODE_READ) { |file| file.read(2).eql? 'Ok' }
  end

  send_test :found_at => path, :within => :write_position_test do
    str = 'ABCDEFG'

    File.open(FILENAME_WRITE, File::MODE_WRITE) { |file| file.write str }

    true
  end

  send_test :found_at => path, :within => :start_position do
    File.open(filename_write, File::MODE_READ) do |file|
      offset = 1
      from   = File::FROM_START
      str    = 'BCDEFG'
      pos    = 7

      file.move_to offset, from

      expected_str = file.read.eql?     str
      expected_pos = file.position.eql? pos

      expected_str && expected_pos
    end
  end

  send_test :found_at => path, :within => :current_position? do
    File.open(filename_write, File::MODE_READ) do |file|
      offset = 1
      from   = File::FROM_CURRENT
      str    = 'BCDEFG'
      pos    = 7

      file.move_to offset, from

      expected_str = file.read.eql?     str
      expected_pos = file.position.eql? pos

      expected_str && expected_pos
    end
  end

  send_test :found_at => path, :within => :end_position? do
    File.open filename_write, File::MODE_READ do |file|
      offset = 1
      from   = File::FROM_END
      pos    = 8

      file.move_to offset, from

      expected_str = file.read.empty?
      expected_pos = file.position.eql? pos

      expected_str && expected_pos
    end
  end

  send_test :found_at => path, :within => :write_8? do
    value = 7
    bytes = 1

    File.open filename_write, File::MODE_WRITE do |file|
      file.write_8       value
      file.position.eql? bytes
    end
  end

  send_test :found_at => path, :within => :read_8? do
    value = 7
    bytes = 1

    File.open filename_write, File::MODE_READ do |file|
      data = file.read_8

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => path, :within => :write_16_be? do
    value = 7
    bytes = 2

    File.open filename_write, File::MODE_WRITE do |file|
      file.write_16_be   value
      file.position.eql? bytes
    end
  end

  send_test :found_at => path, :within => :read_16_be? do
    value = 7
    bytes = 2

    File.open filename_write, File::MODE_READ do |file|
      data = file.read_16_be

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => path, :within => :write_32_be? do
    value = 7
    bytes = 4

    File.open filename_write, File::MODE_WRITE do |file|
      file.write_32_be   value
      file.position.eql? bytes
    end
  end

  send_test :found_at => path, :within => :read_32_be? do
    value = 7
    bytes = 4

    File.open filename_write, File::MODE_READ do |file|
      data = file.read_32_be

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => path, :within => :write_64_be? do
    value = 7
    bytes = 8

    File.open filename_write, File::MODE_WRITE do |file|
      file.write_64_be   value
      file.position.eql? bytes
    end
  end

  send_test :found_at => path, :within => :read_64_be? do
    value = 7
    bytes = 8

    File.open filename_write, File::MODE_READ do |file|
      data = file.read_64_be

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => path, :within => :write_16_le? do
    value = 7
    bytes = 2

    File.open filename_write, File::MODE_WRITE do |file|
      file.write_16_le   value
      file.position.eql? bytes
    end
  end

  send_test :found_at => path, :within => :read_16_le? do
    value = 7
    bytes = 2

    File.open filename_write, File::MODE_READ do |file|
      data = file.read_16_le

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => path, :within => :write_32_le? do
    value = 7
    bytes = 4

    File.open filename_write, File::MODE_WRITE do |file|
      file.write_32_le   value
      file.position.eql? bytes
    end
  end

  send_test :found_at => path, :within => :read_32_le? do
    value = 7
    bytes = 4

    File.open filename_write, File::MODE_READ do |file|
      data = file.read_32_le

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => path, :within => :write_64_le? do
    value = 7
    bytes = 8

    File.open filename_write, File::MODE_WRITE do |file|
      file.write_64_be   value
      file.position.eql? bytes
    end
  end

  send_test :found_at => path, :within => :read_64_le? do
    value = 7
    bytes = 8

    File.open filename_write, File::MODE_READ do |file|
      data = file.read_64_be

      file.position.eql?(bytes) && data.eql?(value)
    end
  end

  send_test :found_at => path, :within => :flush? do
    File.open filename_write, File::MODE_WRITE do |file|
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
