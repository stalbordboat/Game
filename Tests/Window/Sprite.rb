# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Window subsystem.

PATH     = 'Window/Sprite.rb:'
FILENAME = 'Rect.bmp'

send_test :found_at => PATH, :within_block => :new do
  image = Image.new(FILENAME)

  Sprite.new(1, 1, image).kind_of?(Sprite)
end

def get_sprite
  image = Image.new(FILENAME)

  Sprite.new(1, 1, image)
end

send_test :found_at => PATH, :within_block => :instance_method_defined? do
  sprite = get_sprite

  methods = %w(
                update
                dest
                src
                color
                center
              )

  methods.methods_defined? :within => sprite
end

send_test :found_at => PATH, :within_block => :instance_method_types do
  sprite = get_sprite

  sprite.src.kind_of?(Rect)     &&
  sprite.dest.kind_of?(Rect)    &&
  sprite.color.kind_of?(Color)  &&
  sprite.center.kind_of?(Point)
end

send_test :found_at => PATH, :within_block => :attributes_defined? do
  sprite = get_sprite

  attributes = %w(
                  angle
                  flip
                  blend
                  angle=
                  flip=
                  blend=
                )

  attributes.methods_defined? :within => sprite
end

send_test :found_at => PATH, :within_block => :attributes_types do
  sprite = get_sprite

  sprite.angle.kind_of?(Float) &&
  sprite.flip.kind_of?(Integer) &&
  sprite.blend.kind_of?(Integer)
end

send_test :found_at => PATH, :within_block => :set_angle do
  sprite = get_sprite

  sprite.angle = 1.0

  sprite.angle.eql? 1.0
end

send_test :found_at => PATH, :within_block => :set_flip do
  sprite = get_sprite

  sprite.flip = Graphics::FLIP_HORZ

  sprite.flip.eql? Graphics::FLIP_HORZ
end

send_test :found_at => PATH, :within_block => :set_blend do
  sprite = get_sprite

  sprite.blend = Graphics::BLEND_ALPHA

  sprite.blend.eql? Graphics::BLEND_ALPHA
end
