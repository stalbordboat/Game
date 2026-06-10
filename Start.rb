# This file is for trying out new features.

mrb_load 'Input.rb'

Graphics.show

while true
  Input.update
  break if Input.quit?
  Graphics.update
  Graphics.draw
end
