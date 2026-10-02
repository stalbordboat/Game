# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Graphics.rb:'

%w(
FLIP_NONE
FLIP_HORZ
FLIP_VERT
BLEND_NONE
BLEND_ALPHA
BLEND_ADD
BLEND_MULTIPLY
PRESENTATION_DISABLED
PRESENTATION_STRETCH
PRESENTATION_LETTERBOX
PRESENTATION_OVERSCAN
PRESENTATION_INTEGER_SCALE
).const_defined_tests found_at, Graphics

%w(
show
hide
size
width
height
title
icon
fullscreen
hidden?
fullscreen?
update
draw
fill_rect
fill_point
fill_line
blend
color
vsync
vsync?
name
max_size
viewport
save
get_pixel
presentation
dest
screenshot
).response_tests found_at, Graphics
