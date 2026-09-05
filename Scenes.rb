# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Scene Transition Handling
#
# Data can be passed around to different scenes using a Hash table, for exmaple:
#
# Scene manages the high-level flow control of the game.
#
# Scene.call next_scene, with_this: data
#
# When data is being passed back to a retuning scene, the header of Hash table should be called "from",
# and "from" denotes where the data is being returned from, for example:
#
# $scene_return_table = {from: SceneSave, image: @image}
#
# In the returning scene once the $scene_return_table is no longer needed, you must clear the $scene_return_table variable:
#
# $scene_return_table.clear

$scene_return_table = {}

module Scene
  @scene = nil
  @stack = []

  def self.update
    Graphics.update
    @scene.update
    Graphics.draw
  end

  def self.goto(scene, with_this: data={})
    @scene = scene.new(with_this)
  end

  def self.call(scene, with_this: data={})
    @stack.push(@scene)

    @scene = scene.new(with_this)
  end

  def self.return
    @scene = @stack.pop
  end

  def self.stack
    @stack
  end

  def self.empty?
    @stack.empty?
  end
end
