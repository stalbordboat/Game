# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Entry Point

def desc(symbol)
  "#{symbol} Is Not Defined"
end

[:mrb_load, :native_load_basic].each do |symbol|
  value_a = Kernel.respond_to?(symbol)
  value_b = true

  assert_true(desc(symbol), value_a, value_b)
end

symbol  = :native_load
value_a = Object.respond_to?(symbol)
value_b = true

assert_true(desc(symbol), value_a, value_b)

mrb_load '../../Test.rb'
mrb_load '../../Scenes.rb'
mrb_load '../../Input.rb'
mrb_load 'TopLevel.rb'
