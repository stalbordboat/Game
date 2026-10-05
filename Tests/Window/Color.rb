# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Window subsystem.

PATH = 'Window/Color.rb:'

send_test :found_at => PATH, :within_block => :new do
  Color.new.kind_of?(Color)
end

send_test :found_at => PATH, :within_block => :attributes_defined? do
  color = Color.new

  attributes = %w(
                  r
                  g
                  b
                  a
                  red
                  green
                  blue
                  alpha
                  r=
                  g=
                  b=
                  a=
                  red=
                  green=
                  blue=
                  alpha=
                 )

  attributes.attributes_defined? :within => color
end

send_test :found_at => PATH, :within_block => :default_values? do
  color = Color.new

  color.r.eql?(255) &&
  color.g.eql?(255) &&
  color.b.eql?(255) &&
  color.a.eql?(255)
end

send_test :found_at => PATH, :within_block => :set_values? do
  color = Color.new

  color.r = 1
  color.g = 2
  color.b = 3
  color.a = 4

  color.r.eql?(1) &&
  color.g.eql?(2) &&
  color.b.eql?(3) &&
  color.a.eql?(4)
end

send_test :found_at => PATH, :within_block => :reset_values? do
  color = Color.new(5, 7, 8, 9)

  color.r.eql?(5) &&
  color.g.eql?(7) &&
  color.b.eql?(8) &&
  color.a.eql?(9)
end
