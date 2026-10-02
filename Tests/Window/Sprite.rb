# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Window subsystem.

path   = 'Window/Sprite.rb:'
image  = nil
sprite = nil

send_test :found_at => path, :within => :new do
  image  = Image.new 'Rect.bmp'
  sprite = Sprite.new 1, 1, image

  sprite.kind_of? Sprite
end

send_test :found_at => path, :within => :src do
  sprite.src.kind_of? Rect
end

send_test :found_at => path, :within => :dest do
  sprite.dest.kind_of? Rect
end

send_test :found_at => path, :within => :color do
  sprite.color.kind_of? Color
end

send_test :found_at => path, :within => :center do
  sprite.center.kind_of? Point
end

send_test :found_at => path, :within => :angle do
  sprite.angle.kind_of? Float
end

send_test :found_at => path, :within => :flip do
  sprite.flip.kind_of? Integer
end

send_test :found_at => path, :within => :blend do
  sprite.blend.kind_of? Integer
end

send_test :found_at => path, :within => :set_angle do
  sprite.angle = 1.0

  sprite.angle.eql? 1.0
end

send_test :found_at => path, :within => :set_flip do
  sprite.flip = Graphics::FLIP_HORZ

  sprite.flip.eql? Graphics::FLIP_HORZ
end

send_test :found_at => path, :within => :set_blend do
  sprite.blend = Graphics::BLEND_ALPHA

  sprite.blend.eql? Graphics::BLEND_ALPHA
end
