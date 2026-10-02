# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Process.rb:'

%w(open).response_tests found_at, Process

command = %w(touch Test.txt)
pipe    = true
process = Process.new command, pipe

%w(
close
end
read
exit_code
wait
).response_tests found_at, process

process.close
