# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: 
mrb_load 'Input.rb'

Graphics.show

# Center the image.
image_a = Image.new 'SpriteA.png'

# Initialize Sprites and set their individual positions.

horz     = 3
vert     = 1
sprite_a = Sprite.new horz, vert, image_a

padding  = 8
sprite_b = Sprite.new horz, vert, image_a
sprite_b.src.x  = 64
sprite_b.dest.x = 64 + padding

sprite_c = Sprite.new horz, vert, image_a
sprite_c.src.x  = 64
sprite_c.dest.y = 64 + padding

while true
  Input.update
  break if Input.quit?
  Graphics.update
  sprite_a.update
  sprite_b.update
  sprite_c.update
  Graphics.draw
end
