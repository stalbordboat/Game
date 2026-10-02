# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Rect.rb:'
rect     = Rect.new

%w(x y w h width height).response_tests found_at, rect
