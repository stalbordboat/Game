# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Entry Point

def desc(symbol)
  "#{symbol} Is Not Defined"
end

[:mrb_load, :native_load_basic].each do |symbol|
  value_a = Kernel.respond_to? symbol
  value_b = true

  assert_true desc(symbol), value_a, value_b
end

symbol  = :native_load
value_a = Object.respond_to? symbol
value_b = true

assert_true desc(symbol), value_a, value_b

mrb_load '../../Test.rb'
mrb_load '../../Scenes.rb'
mrb_load '../../Input.rb'
mrb_load 'Array.rb'
mrb_load 'Integer.rb'
mrb_load 'Kernel.rb'
mrb_load 'Math.rb'
mrb_load 'File.rb'
mrb_load 'FileUtils.rb'
mrb_load 'Env.rb'
mrb_load 'Log.rb'
mrb_load 'Timer.rb'
mrb_load 'Time.rb'
mrb_load 'Process.rb'
mrb_load 'Power.rb'
mrb_load 'Graphics.rb'
mrb_load 'Point.rb'
mrb_load 'Rect.rb'
mrb_load 'Color.rb'
mrb_load 'Image.rb'
mrb_load 'Sprite.rb'
mrb_load 'Camera.rb'
mrb_load 'AudioRecorder.rb'
mrb_load 'Mixer.rb'
mrb_load 'Sound.rb'
mrb_load 'Location.rb'
mrb_load 'Event.rb'
mrb_load 'Gamepad.rb'
mrb_load 'Scenes.rb'
mrb_load 'Input.rb'
