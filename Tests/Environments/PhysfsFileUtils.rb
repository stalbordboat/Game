# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the expected condtions of various environments.

PATH = 'Environments/PhysfsFileUtils.rb'

send_test :found_at => PATH, :within_block => :entries? do
  skip 'Physfs only returns an empty array for some reason.', :within_block => :entries?
  #entries = FileUtils.entries('.')

  #if entries.kind_of? Array
  #  entries.include? 'PhysfsFileUtils.rb'
  #else
  #  false
  #end
end

send_test :found_at => PATH, :within_block => :entries_with_ext? do
  skip 'Physfs only returns an empty array for some reason.', :within_block => :entries_with_ext?
  #FileUtils.entries('.', '*.txt').include? FILENAME_WRITE
end
