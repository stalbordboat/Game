# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the expected condtions of various environments.

PATH           = 'Environments/SDLFileUtilsStat.rb'
FILENAME_WRITE = 'Test_Write.txt'

send_test :found_at => PATH, :within_block => :functions_defined? do
  functions = %w(
                  exist?
                  file?
                  dir?
                  other?
                  size
                  length
                  create_time
                  modify_time
                  access_time
                )

  functions.methods_defined? :within => FileUtils::Stat
end

send_test :found_at => PATH, :within_block => :exist? do
  FileUtils::Stat.exist?(FILENAME_WRITE)
end

send_test :found_at => PATH, :within_block => :file? do
  FileUtils::Stat.file?(FILENAME_WRITE)
end

send_test :found_at => PATH, :within_block => :dir? do
  FileUtils::Stat.dir?(Env['HOME'])
end

send_test :found_at => PATH, :within_block => :size? do
  min_expected_bytes = 8

  FileUtils::Stat.size('SDLFileUtilsStat.rb') >= min_expected_bytes
end

# NOTE: The tests for create_time, modify_time, and access_time are done in: Tests/General/Time.rb.
