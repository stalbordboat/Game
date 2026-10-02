# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the expected condtions of various environments.

path = 'Environments/PhysfsFileUtils.rb'

send_test :found_at => path, :within => :entries? do
  skip 'PhysfsFileUtils.entries?: Physfs only returns an empty array for some reason.'
  #entries = FileUtils.entries('.')

  #if entries.kind_of? Array
  #  entries.include? 'PhysfsFileUtils.rb'
  #else
  #  false
  #end
end

send_test :found_at => path, :within => :entries_with_ext? do
  skip 'PhysfsFileUtils.entries_with_ext?: Physfs only returns an empty array for some reason.'
  #FileUtils.entries('.', '*.txt').include? FILENAME_WRITE
end
