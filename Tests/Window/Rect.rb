# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Window subsystem.

path = 'Window/Rect.rb:'
rect = nil

send_test :found_at => path, :within => :new do
  rect = Rect.new

  rect.kind_of? Rect
end

send_test :found_at => path, :within => :default_values? do
  rect.x.eql?(0.0) &&
  rect.y.eql?(0.0) &&
  rect.w.eql?(0.0) &&
  rect.h.eql?(0.0)
end

send_test :found_at => path, :within => :set_values? do
  rect.x = 1
  rect.y = 2
  rect.w = 3
  rect.h = 4

  rect.x.eql?(1.0) &&
  rect.y.eql?(2.0) &&
  rect.w.eql?(3.0) &&
  rect.h.eql?(4.0)
end

send_test :found_at => path, :within => :reset_values? do
  rect = Rect.new 5, 7, 8, 9

  rect.x.eql?(5.0) &&
  rect.y.eql?(7.0) &&
  rect.w.eql?(8.0) &&
  rect.h.eql?(9.0)
end
