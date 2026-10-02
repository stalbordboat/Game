# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Input.rb:'

%w(update quit? state press? trigger? repeat?).response_tests found_at, Input
