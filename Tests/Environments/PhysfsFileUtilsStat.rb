# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the expected condtions of various environments.

path          = 'Environments/PhysfsFileUtilsStat.rb'
filename_read = 'Test_Read.txt'

send_test :found_at => path, :within => :exist? do
  FileUtils::Stat.exist? filename_read
end

send_test :found_at => path, :within => :file? do
  FileUtils::Stat.file? filename_read
end

send_test :found_at => path, :within => :dir? do
  FileUtils::Stat.dir? 'Temp'
end

send_test :found_at => path, :within => :size? do
  min_expected_bytes = 8

  FileUtils::Stat.size('PhysfsFileUtilsStat.rb') >= min_expected_bytes
end
