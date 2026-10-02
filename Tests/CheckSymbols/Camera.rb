# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the existence of methods and attributes.

found_at = 'CheckSymbols/Camera.rb:'

%w(
PERMISSION_DENIED
PERMISSION_PENDING
PERMISSION_APPROVED
POSITION_UNKNOWN
POSITION_FRONT_FACING
POSITION_BACK_FACING
).const_defined_tests found_at, Camera

%w(
ids
name
driver_current_name
driver_count
driver_name
open
).response_tests found_at, Camera

ids = Camera.ids

unless ids.empty?

first  = ids.first
dest   = Rect.new    0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT
camera = Camera.open first, dest

%w(
close
closed?
permission
name
save
update
position
).response_tests found_at, camera

camera.close
end
