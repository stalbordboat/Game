# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Use the first gamepad to move a rectangle around the screen in all directions with rumble effect for gamepads
# that have rumble.
mrb_load 'Input.rb'

Graphics.show

# Create and center a rectangle.

rect        = Rect.new
rect.width  = 256
rect.height = 256
rect.x      = (Graphics.width  - rect.width) / 2
rect.y      = (Graphics.height - rect.height) / 2

color       = Color.new
color.red   = 255
color.green = 255
color.blue  = 255

# Create Gamepad

which   = Gamepad.ids.first
gamepad = Gamepad.open which

# Define methods for rect movement.

def perform_rumble(gamepad)
  gamepad.rumble 16383, 16383, 25 if gamepad.rumble?
end

def move_up(rect, gamepad)
  rect.y -= 8
  perform_rumble gamepad
end

def move_down(rect, gamepad)
  rect.y += 8
  perform_rumble gamepad
end

def move_left(rect, gamepad)
  rect.x -= 8
  perform_rumble gamepad
end

def move_right(rect, gamepad)
  rect.x += 8
  perform_rumble gamepad
end

# Main Loop

while true
  Input.update
  break if Input.quit?
  Graphics.update

  # Perform Movement

  move_up    rect, gamepad if Input.press? :button_up
  move_down  rect, gamepad if Input.press? :button_down
  move_left  rect, gamepad if Input.press? :button_left
  move_right rect, gamepad if Input.press? :button_right

  # Render Rect

  Graphics.fill_rect rect, color
  Graphics.draw
end

gamepad.close
