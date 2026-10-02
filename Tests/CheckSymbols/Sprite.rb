# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Sprite.rb:'
path     = 'Texture_1.bmp'
horz     = 1
vert     = 1
image    = Image.new  path
sprite   = Sprite.new horz, vert, image

%w(
update
dest
src
color
center
angle
flip
blend
angle=
flip=
blend=
).response_tests found_at, sprite
