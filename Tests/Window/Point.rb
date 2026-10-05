# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Window subsystem.

PATH = 'Window/Point.rb:'

send_test :found_at => PATH, :within_block => :new do
  Point.new.kind_of?(Point)
end

send_test :found_at => PATH, :within_block => :attributes_defined? do
  point = Point.new

  attributes = %w(x y x= y=)

  attributes.attributes_defined? :within => point
end

send_test :found_at => PATH, :within_block => :default_values? do
  point = Point.new

  point.x.eql?(0.0) &&
  point.y.eql?(0.0)
end

send_test :found_at => PATH, :within_block => :set_values? do
  point = Point.new

  point.x = 1
  point.y = 2

  point.x.eql?(1.0) &&
  point.y.eql?(2.0)
end

send_test :found_at => PATH, :within_block => :reset_values? do
  point = Point.new(5, 7)

  point.x.eql?(5.0) &&
  point.y.eql?(7.0)
end
