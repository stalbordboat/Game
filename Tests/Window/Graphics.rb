# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Window subsystem.

PATH     = 'Window/Graphics.rb:'
SAVEFILE = 'Test-Save.bmp'

send_test :found_at => PATH, :within_block => :default_hidden? do
  Graphics.hidden?
end

send_test :found_at => PATH, :within_block => :shown? do
  Graphics.show

  !Graphics.hidden?
end

send_test :found_at => PATH, :within_block => :default_size? do
  Graphics.width.eql?(DEFAULT_WINDOW_WIDTH) &&
  Graphics.height.eql?(DEFAULT_WINDOW_HEIGHT)
end

send_test :found_at => PATH, :within_block => :change_size? do
  width  = 640
  height = 480

  Graphics.size(width, height)

  Graphics.width.eql?(width) &&
  Graphics.height.eql?(height)
end

send_test :found_at => PATH, :within_block => :title? do
  Graphics.title('Test').nil?
end

send_test :found_at => PATH, :within_block => :fullscreen? do
  Graphics.fullscreen(true)

  status = Graphics.fullscreen?

  Graphics.fullscreen(false)

  status
end

send_test :found_at => PATH, :within_block => :name? do
  name = Graphics.name

  # I'm kind of just guessing with these names.
  name.eql?('opengl') ||
  name.eql?('vulkan') ||
  name.eql?('gpu')    ||
  name.eql?('direct3d')
end

send_test :found_at => PATH, :within_block => :max_size? do
  Graphics.max_size > 0
end

send_test :found_at => PATH, :within_block => :viewport? do
  dest = Rect.new(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT)

  Graphics.viewport(dest).nil?
end

send_test :found_at => PATH, :within_block => :vsync? do
  Graphics.vsync(false)

  status = Graphics.vsync?

  Graphics.vsync(true)

  !status
end

# If rect is filled in with a particular color, then we must be able
# to get that color from a pixel within the boundries of that rect.
send_test :found_at => PATH, :within_block => :fill_rect? do
  dest      = Rect.new(0, 0, 255, 255)
  color     = Color.new
  color.red = 127
  count     = 0
  status    = false

  simulate_main_loop do
    Graphics.fill_rect(dest, color)

    pixel  = Graphics.get_pixel(dest.x, dest.y)
    status = pixel.red.eql?(127)

    break if count.eql?(1)

    count += 1
  end

  status
end

# If point is filled in with a particular color, then we must be able
# to get that color from a pixel within the boundries of that point.
send_test :found_at => PATH, :within_block => :fill_point? do
  x         = 0
  y         = 0
  color     = Color.new
  color.red = 127
  count     = 0
  status    = false

  simulate_main_loop do
    Graphics.fill_point(x, y, color)

    pixel  = Graphics.get_pixel(x, y)
    status = pixel.red.eql?(127)

    break if count.eql?(1)

    count += 1
  end

  status
end

# If line is filled in with a particular color, then we must be able
# to get that color from a pixel within the boundries of that line.
send_test :found_at => PATH, :within_block => :fill_line? do
  x1        = 0
  y1        = 0
  x2        = 1
  y2        = 1
  color     = Color.new
  color.red = 127
  count     = 0
  status    = false

  simulate_main_loop do
    Graphics.fill_line(x1, y1, x2, y2, color)

    pixel  = Graphics.get_pixel(x1, y2)
    status = pixel.red.eql?(127)

    break if count.eql?(1)

    count += 1
  end

  status
end

send_test :found_at => PATH, :within_block => :screenshot? do
  dest   = Rect.new(0, 0, 255, 255)
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

send_test :found_at => PATH, :within_block => :save? do
  status = false

  simulate_main_loop do
    status = Graphics.save(SAVEFILE).nil?

    break
  end

  status
end

send_test :found_at => PATH, :within_block => :sprite? do
  status = nil
  image  = Image.new(SAVEFILE)
  sprite = Sprite.new(1, 1, image)

  simulate_main_loop do
    status = sprite.update.nil?
    break
  end

  status
end

send_test :found_at => PATH, :within_block => :camera? do
  ids = Camera.ids

  unless ids.empty?
    first  = ids.first
    dest   = Rect.new(0, 0, 255, 255)
    camera = Camera.open(first, dest)
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

send_test :found_at => PATH, :within_block => :blend? do
  Graphics.blend(Graphics::BLEND_ALPHA).eql?(Graphics::BLEND_ALPHA)
end

send_test :found_at => PATH, :within_block => :color? do
  Graphics.color(Color.new).kind_of?(Color)
end

send_test :found_at => PATH, :within_block => :presentation? do
  Graphics.presentation.nil?
end
