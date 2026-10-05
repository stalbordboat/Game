# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Window subsystem.

PATH     = 'Window/Image.rb:'
FILENAME = 'Rect.bmp'

send_test :found_at => PATH, :within_block => :new_default do
  Image.new(FILENAME).kind_of?(Image)
end

send_test :found_at => PATH, :within_block => :new_with_color_key do
  Image.new(FILENAME, color_key: Color.new).kind_of?(Image)
end

send_test :found_at => PATH, :within_block => :instance_methods_defined? do
  image = Image.new(FILENAME)

  methods = %w(
                update
                dest
                color
                center
              )

  methods.methods_defined? :within => image
end

send_test :found_at => PATH, :within_block => :instance_method_types? do
  image = Image.new(FILENAME)

  image.dest.kind_of?(Rect)    &&
  image.color.kind_of?(Color)  &&
  image.center.kind_of?(Point)
end

send_test :found_at => PATH, :within_block => :attributes_defined? do
  image = Image.new(FILENAME)

  attributes = %w(
                  angle
                  flip
                  blend
                  angle=
                  flip=
                  blend=
                 )

  attributes.attributes_defined? :within => image
end

send_test :found_at => PATH, :within_block => :attributes_types? do
  image = Image.new(FILENAME)

  image.angle.kind_of?(Float)   &&
  image.flip.kind_of?(Integer)  &&
  image.blend.kind_of?(Integer)
end

send_test :found_at => PATH, :within_block => :set_angle do
  image = Image.new(FILENAME)

  image.angle = 1.0

  image.angle.eql? 1.0
end

send_test :found_at => PATH, :within_block => :set_flip do
  image = Image.new(FILENAME)

  image.flip = Graphics::FLIP_HORZ

  image.flip.eql? Graphics::FLIP_HORZ
end

send_test :found_at => PATH, :within_block => :set_blend do
  image = Image.new(FILENAME)

  image.blend = Graphics::BLEND_ALPHA

  image.blend.eql? Graphics::BLEND_ALPHA
end
