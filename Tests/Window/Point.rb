# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Window subsystem.

path  = 'Window/Point.rb:'
point = nil

send_test :found_at => path, :within => :new do
  point = Point.new

  point.kind_of? Point
end

send_test :found_at => path, :within => :default_values? do
  point.x.eql?(0.0) &&
  point.y.eql?(0.0)
end

send_test :found_at => path, :within => :set_values? do
  point.x = 1
  point.y = 2

  point.x.eql?(1.0) &&
  point.y.eql?(2.0)
end

send_test :found_at => path, :within => :reset_values? do
  @point = Point.new 5, 7

  @point.x.eql?(5.0) &&
  @point.y.eql?(7.0)
end
