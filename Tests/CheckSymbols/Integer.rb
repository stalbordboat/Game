# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Integer.rb:'
integer  = 777

%w(cycle backward forward).response_tests found_at, integer
