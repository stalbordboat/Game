# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the expected condtions of various environments.

path           = 'Environments/SDLFileUtilsStat.rb'
filename_write = 'Test_Write.txt'

send_test :found_at => path, :within => :exist? do
  FileUtils::Stat.exist? filename_write
end

send_test :found_at => path, :within => :file? do
  FileUtils::Stat.file? filename_write
end

send_test :found_at => path, :within => :dir? do
  FileUtils::Stat.dir? Env['HOME']
end

send_test :found_at => path, :within => :size? do
  min_expected_bytes = 8

  FileUtils::Stat.size('SDLFileUtilsStat.rb') >= min_expected_bytes
end

# TODO: The tests for create_time, modify_time, and access_time are done in the Time module test.
