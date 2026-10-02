# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Window subsystem.

path     = 'Window/Graphics.rb:'
savefile = 'Test-Save.bmp'

# The default state of the Graphics module is expected to be hidden.
send_test :found_at => path, :within => :default_hidden do
  Graphics.hidden?
end

# If the Graphics module is shown then the hidden state should be false.
send_test :found_at => path, :within => :shown do
  Graphics.show

  !Graphics.hidden?
end

# The Graphics module's should be the default size.
send_test :found_at => path, :within => :default_size do
  Graphics.width.eql?(DEFAULT_WINDOW_WIDTH) &&
  Graphics.height.eql?(DEFAULT_WINDOW_HEIGHT)
end

# The Graphics module's size should be equal to the changed size.
send_test :found_at => path, :within => :change_size do
  width  = 640
  height = 480

  Graphics.size width, height

  Graphics.width.eql?(width) &&
  Graphics.height.eql?(height)
end

# If success :title is expected to be nil.
send_test :found_at => path, :within => :title do
  Graphics.title('Test').nil?
end

# If the Graphics module is set to fullscreen, then the fullscreen state should be true.
send_test :found_at => path, :within => :fullscreen do
  Graphics.fullscreen true

  status = Graphics.fullscreen?

  Graphics.fullscreen false

  status
end

# The Graphics module's name should be the name of an underlying graphics API.
send_test :found_at => path, :within => :name do
  name = Graphics.name

  # I'm kind of just guessing with these names.
  name.eql?('opengl') ||
  name.eql?('vulkan') ||
  name.eql?('gpu')    ||
  name.eql?('direct3d')
end

# The maximum size of an image that the Graphics module can load must be more than zero.
send_test :found_at => path, :within => :max_size do
  Graphics.max_size > 0
end

# If successfully set viewport is expected to be nil.
send_test :found_at => path, :within => :viewport do
  dest = Rect.new(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT)

  Graphics.viewport(dest).nil?
end

# If vsync is turned of, then the vsync state must be false.
send_test :found_at => path, :within => :vsync do
  Graphics.vsync false

  status = Graphics.vsync?

  Graphics.vsync true

  !status
end

# If rect is filled in with a particular color, then we must be able
# to get that color from a pixel within the boundries of that rect.
send_test :found_at => path, :within => :fill_rect do
  dest      = Rect.new  0, 0, 255, 255
  color     = Color.new
  color.red = 127
  count     = 0
  status    = false

  simulate_main_loop do
    Graphics.fill_rect dest, color

    pixel  = Graphics.get_pixel dest.x, dest.y
    status = pixel.red.eql? 127

    break if count.eql? 1

    count += 1
  end

  status
end

# If point is filled in with a particular color, then we must be able
# to get that color from a pixel within the boundries of that point.
send_test :found_at => path, :within => :fill_point do
  x         = 0
  y         = 0
  color     = Color.new
  color.red = 127
  count     = 0
  status    = false

  simulate_main_loop do
    Graphics.fill_point x, y, color

    pixel  = Graphics.get_pixel x, y
    status = pixel.red.eql? 127

    break if count.eql? 1

    count += 1
  end

  status
end

# If line is filled in with a particular color, then we must be able
# to get that color from a pixel within the boundries of that line.
send_test :found_at => path, :within => :fill_line do
  x1        = 0
  y1        = 0
  x2        = 1
  y2        = 1
  color     = Color.new
  color.red = 127
  count     = 0
  status    = false

  simulate_main_loop do
    Graphics.fill_line x1, y1, x2, y2, color

    pixel  = Graphics.get_pixel x1, y2
    status = pixel.red.eql? 127

    break if count.eql? 1

    count += 1
  end

  status
end

send_test :found_at => path, :within => :screenshot do
  dest   = Rect.new 0, 0, 255, 255
  status = false

  simulate_main_loop do
    screenshot = Graphics.screenshot(dest)

    if screenshot.kind_of? Image
      status = screenshot.dest.width.eql?(dest.width) && screenshot.dest.height.eql?(dest.height)
    end

    break
  end

  status
end

# If the rendering state was successfully saved then, it's expected to be nil.
send_test :found_at => path, :within => :save do
  path   = savefile
  status = false

  simulate_main_loop do
    status = Graphics.save(path).nil?

    break
  end

  status
end

# If a sprite updates successfully then it's expected to be nil.
send_test :found_at => path, :within => :sprite do
  path   = savefile
  status = nil
  image  = Image.new path
  sprite = Sprite.new 1, 1, image

  simulate_main_loop do
    status = sprite.update.nil?
    break
  end

  status
end

# If a camera updates successfully then it's expected to be nil.
send_test :found_at => path, :within => :camera do
  ids = Camera.ids

  unless ids.empty?
    first  = ids.first
    dest   = Rect.new    0, 0, 255, 255
    camera = Camera.open first, dest
    status = nil

    simulate_main_loop do
      status = camera.update.nil?

      break
    end

    camera.close

    return status
  end

  true
end

# If the Graphics module's blend was set successfully it's expected to be equal to the value set.
send_test :found_at => path, :within => :blend do
  Graphics.blend(Graphics::BLEND_ALPHA).eql? Graphics::BLEND_ALPHA
end

# If the Graphics module's color was set successfully it's expected to be a Color.
send_test :found_at => path, :within => :color do
  Graphics.color(Color.new).kind_of? Color
end

# If the Graphics module's presentation state was set successfully it's expected to be nil.
send_test :found_at => path, :within => :presentation do
  Graphics.presentation.nil?
end
