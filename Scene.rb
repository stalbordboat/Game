# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: A scene manager for scene transition handling.
#
# Scene manages the high-level flow control of the game, for example:
#
# Scene.call next_scene, with_this: data
#
# When data is being passed back to a returning scene, you can pass data back to the returning scene like this: 
#
# Scene.return from: SceneSave, with_this: data
#
# Once returning back from the scene a clone of that data can be retrieved like this:
#
# Scene.return_data
#
# In the returning scene once the data is returned, you must clear the data like this:
#
# Scene.clear_return_data
#
# This is useful for avoiding using data that may have been set previously, but isn't needed currently.

module Scene
  @scene = nil
  @stack = []
  @data  = {}

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

  def self.return(from: nil, with_this: nil)
    @scene = @stack.pop
    @data  = {from: from, with_this: with_this}
  end

  def self.return_data
    @data.clone
  end

  def self.clear_return_data
    @data.clear
  end

  def self.current
    @scene
  end

  def self.stack
    @stack
  end

  def self.empty?
    @stack.empty?
  end
end
