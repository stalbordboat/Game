# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Represents Camera Devices

class Camera
  def self.open(which, dest)
    camera = self.new(which, dest)

    if block_given?
      begin
        obj = yield(camera)
      ensure
        camera.close
        obj
      end
    else
      camera
    end
  end
end
