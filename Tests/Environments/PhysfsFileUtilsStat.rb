# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the expected condtions of various environments.

PATH          = 'Environments/PhysfsFileUtilsStat.rb'
FILENAME_READ = 'Test_Read.txt'

send_test :found_at => PATH, :within_block => :exist? do
  FileUtils::Stat.exist?(FILENAME_READ)
end

send_test :found_at => PATH, :within_block => :file? do
  FileUtils::Stat.file?(FILENAME_READ)
end

send_test :found_at => PATH, :within_block => :dir? do
  FileUtils::Stat.dir?('Temp')
end

send_test :found_at => PATH, :within_block => :size? do
  min_expected_bytes = 8

  FileUtils::Stat.size('PhysfsFileUtilsStat.rb') >= min_expected_bytes
end
