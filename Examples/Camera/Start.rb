# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Stream video from your camera, and save a frame when the 'z' key is pressed.
mrb_load 'Input.rb'

Graphics.show

which = Camera.ids.first
dest  = Rect.new(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT)
Camera.open(which, dest) do |camera|
  output_path = 'SavefileCamera.bmp'

  while true
    Input.update
    break if Input.quit?
    Graphics.update

    # Save the current frame to a bitmap image file.

    if Input.trigger?(:key_z)
      camera.save(output_path)
      Log.info('Saved!!')
    end

    # Render frames from the camera.

    camera.update
    Graphics.draw
  end
end
