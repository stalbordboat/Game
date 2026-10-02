# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Window subsystem.

path  = 'Window/Image.rb:'
image = nil

send_test :found_at => path, :within => :new do
  image = Image.new 'Rect.bmp'

  image.kind_of? Image
end

send_test :found_at => path, :within => :dest do
  image.dest.kind_of? Rect
end

send_test :found_at => path, :within => :color do
  image.color.kind_of? Color
end

send_test :found_at => path, :within => :center do
  image.center.kind_of? Point
end

send_test :found_at => path, :within => :angle do
  image.angle.kind_of? Float
end

send_test :found_at => path, :within => :flip do
  image.flip.kind_of? Integer
end

send_test :found_at => path, :within => :blend do
  image.blend.kind_of? Integer
end

send_test :found_at => path, :within => :set_angle do
  image.angle = 1.0

  image.angle.eql? 1.0
end

send_test :found_at => path, :within => :set_flip do
  image.flip = Graphics::FLIP_HORZ

  image.flip.eql? Graphics::FLIP_HORZ
end

send_test :found_at => path, :within => :set_blend do
  image.blend = Graphics::BLEND_ALPHA

  image.blend.eql? Graphics::BLEND_ALPHA
end
