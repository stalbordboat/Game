# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Window subsystem.

path  = 'Window/Color.rb:'
color = nil

send_test :found_at => path, :within => :new do
  color = Color.new

  color.kind_of? Color
end

send_test :found_at => path, :within => :default_values? do
  color.r.eql?(255) &&
  color.g.eql?(255) &&
  color.b.eql?(255) &&
  color.a.eql?(255)
end

send_test :found_at => path, :within => :set_values? do
  color.r = 1
  color.g = 2
  color.b = 3
  color.a = 4

  color.r.eql?(1) &&
  color.g.eql?(2) &&
  color.b.eql?(3) &&
  color.a.eql?(4)
end

send_test :found_at => path, :within => :reset_values? do
  color = Color.new 5, 7, 8, 9

  color.r.eql?(5) &&
  color.g.eql?(7) &&
  color.b.eql?(8) &&
  color.a.eql?(9)
end
