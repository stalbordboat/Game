# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the audio subsystem.

path  = 'Audio/Location.rb:'
point = nil

send_test :found_at => path, :within => :new do
  point = Location.new

  point.kind_of? Location
end

send_test :found_at => path, :within => :default_values do
  point.x.eql?(0.0) &&
  point.y.eql?(0.0) &&
  point.z.eql?(0.0)
end

send_test :found_at => path, :within => :set_values do
  point.x = 1
  point.y = 2
  point.z = 3

  point.x.eql?(1.0) &&
  point.y.eql?(2.0) &&
  point.z.eql?(3.0)
end

send_test :found_at => path, :within => :reset_values do
  point = Location.new 5, 7, 8

  point.x.eql?(5.0) &&
  point.y.eql?(7.0) &&
  point.z.eql?(8.0)
end
