# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Window subsystem.

PATH = 'Window/Scene.rb'
DATA = 777

class SceneA
  def initialize(data)
  end

  def update
  end
end

class SceneB
  def initialize(data)
  end

  def update
  end
end

class SceneC
  def initialize(data)
  end

  def update
  end
end

send_test :found_at => PATH, :within_block => :functions_defined? do
  functions = %w(update goto call return return_data current stack empty?)

  functions.methods_defined? :within => Scene
end

send_test :found_at => PATH, :within_block => :default_state? do
  Scene.empty?
end

send_test :found_at => PATH, :within_block => :goto? do
  Scene.goto(SceneA)

  Scene.current.kind_of?(SceneA)
end

send_test :found_at => PATH, :within_block => :update? do
  count  = 0
  limit  = 64
  status = false

  simulate_main_loop do
    status = Scene.update.nil?
    break if count.eql?(limit)
    count += 1
  end

  status
end

send_test :found_at => PATH, :within_block => :call? do
  Scene.call(SceneB)

  status_b = Scene.current.kind_of?(SceneB)

  Scene.call(SceneC)

  status_c = Scene.current.kind_of?(SceneC)

  status_b && status_c
end

send_test :found_at => PATH, :within_block => :stack? do
  stack = Scene.stack

  stack.length.eql?(2)         &&
  stack.first.kind_of?(SceneA) &&
  stack.last.kind_of?(SceneB)
end

send_test :found_at => PATH, :within_block => :return_without_data? do
  Scene.return

  Scene.current.kind_of?(SceneB) && Scene.stack.length.eql?(1)
end

send_test :found_at => PATH, :within_block => :return_with_data? do
  Scene.return from: SceneB, with_this: DATA

  Scene.current.kind_of?(SceneA)           &&
  Scene.return_data[:from].eql?(SceneB)    &&
  Scene.return_data[:with_this].eql?(data) &&
  Scene.stack.length.eql?(0)
end

send_test :found_at => PATH, :within_block => :clear_return_data? do
  data_a = Scene.return_data
  Scene.clear_return_data
  data_b = Scene.return_data

  data_a.eql?({from: SceneB, with_this: DATA}) &&
  data_b.eql?({})
end
