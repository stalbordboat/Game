# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the Audio subsystem.

PATH = 'Audio/Location.rb:'

send_test :found_at => PATH, :within_block => :new do
  Location.new.kind_of?(Location)
end

send_test :found_at => PATH, :within_block => :attributes_defined? do
  point = Location.new

  attributes = %w(
                  x
                  y
                  z
                  x=
                  y=
                  z=
                 )

  attributes.attributes_defined? :within => point
end

send_test :found_at => PATH, :within_block => :default_values do
  point = Location.new

  point.x.eql?(0.0) &&
  point.y.eql?(0.0) &&
  point.z.eql?(0.0)
end

send_test :found_at => PATH, :within_block => :set_values do
  point = Location.new

  point.x = 1
  point.y = 2
  point.z = 3

  point.x.eql?(1.0) &&
  point.y.eql?(2.0) &&
  point.z.eql?(3.0)
end

send_test :found_at => PATH, :within_block => :reset_values do
  point = Location.new(5, 7, 8)

  point.x.eql?(5.0) &&
  point.y.eql?(7.0) &&
  point.z.eql?(8.0)
end
