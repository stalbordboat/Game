# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Window subsystem.

PATH = 'Window/Rect.rb:'

send_test :found_at => PATH, :within_block => :new do
  Rect.new.kind_of?(Rect)
end

send_test :found_at => PATH, :within_block => :attributes_defined? do
  rect = Rect.new

  attributes = %w(
                    x
                    y
                    w
                    h
                    width
                    height
                    x=
                    y=
                    w=
                    h=
                    width=
                    height=
                 )

  attributes.attributes_defined? :within => rect
end

send_test :found_at => PATH, :within_block => :default_values? do
  rect = Rect.new

  rect.x.eql?(0.0) &&
  rect.y.eql?(0.0) &&
  rect.w.eql?(0.0) &&
  rect.h.eql?(0.0)
end

send_test :found_at => PATH, :within_block => :set_values? do
  rect = Rect.new

  rect.x = 1
  rect.y = 2
  rect.w = 3
  rect.h = 4

  rect.x.eql?(1.0) &&
  rect.y.eql?(2.0) &&
  rect.w.eql?(3.0) &&
  rect.h.eql?(4.0)
end

send_test :found_at => PATH, :within_block => :reset_values? do
  rect = Rect.new(5, 7, 8, 9)

  rect.x.eql?(5.0) &&
  rect.y.eql?(7.0) &&
  rect.w.eql?(8.0) &&
  rect.h.eql?(9.0)
end
