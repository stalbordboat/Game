# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Color.rb:'
color    = Color.new

%w(r g b a red green blue alpha).response_tests found_at, color
