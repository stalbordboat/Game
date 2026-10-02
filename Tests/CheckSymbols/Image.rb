# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Image.rb:'
path     = 'Texture_1.bmp'
image    = Image.new path

%w(
update
dest
color
center
angle
flip
blend
angle=
flip=
blend=
).response_tests found_at, image
