# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Point.rb:'
point    = Point.new

%w(x y).response_tests found_at, point
