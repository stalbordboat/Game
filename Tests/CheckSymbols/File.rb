# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/File.rb:'

%w(
MODE_READ
MODE_WRITE
MODE_APPEND
FROM_START
FROM_CURRENT
FROM_END
).const_defined_tests found_at, File

%w(open is_archive? set_write_dir).response_tests found_at, File

file = File.open 'Test.txt', File::MODE_READ

%w(
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
).response_tests found_at, file

file.close
