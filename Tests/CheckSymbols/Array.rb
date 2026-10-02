# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Array.rb:'
array    = []

%w(limit update).response_tests found_at, array
