# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the Window subsystem.

path    = 'Window/Camera.rb:'
cameras = []

send_test :found_at => path, :within => :ids? do
  Camera.ids.kind_of? Array
end

# Each camera device is expected to have a name.
send_test :found_at => path, :within => :self_name do
  id = Camera.ids.first

  return !Camera.name(id).empty? unless id.nil?

  true
end

# The underlying camera device driver that's being used is expected to have a name.
send_test :found_at => path, :within => :driver_current_name do
  driver_name = Camera.driver_current_name

  !driver_name.empty? if driver_name.kind_of? String
end

# If there's a camera driver then we should expect there to be at least one driver, right? Lol.
send_test :found_at => path, :within => :driver_count do
  count = Camera.driver_count

  count >= 0 if count.kind_of? Integer
end

# If successful camera devices are opened without an exception being raised.
# Each opened camera must return an instance of the Camera object.
send_test :found_at => path, :within => :open do
  dest   = Rect.new 0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT
  status = false

  Camera.ids.each { |id| cameras.push Camera.open id, dest }

  unless cameras.empty?
    cameras.each do |camera|
      if camera.kind_of? Camera
        status = true
      else
        break
      end
    end
  else
    status = true
  end

  status
end

send_test :found_at => path, :within => :permission do
  unless cameras.empty?
    permission = cameras.first.permission

    permission.eql?(Camera::PERMISSION_DENIED)  ||
    permission.eql?(Camera::PERMISSION_PENDING) ||
    permission.eql?(Camera::PERMISSION_APPROVED)
  else
    true
  end
end

# The specific Camera instance is expected to have a name.
send_test :found_at => path, :within => :name do
  unless cameras.empty?
    name = cameras.first.name

    if name.kind_of? String
      !name.empty?
    else
      false
    end
  else
    true
  end
end

# The position method is expected to return its position status.
send_test :found_at => path, :within => :position do
  unless cameras.empty?
    position = cameras.first.position

    position.eql?(Camera::POSITION_UNKNOWN)      ||
    position.eql?(Camera::POSITION_FRONT_FACING) ||
    position.eql?(Camera::POSITION_BACK_FACING)
  else
    true
  end
end

# If successful Camera's closed? method must return true.
send_test :found_at => path, :within => :close do
  status = true

  unless cameras.empty?
    cameras.each do |camera|
      camera.close

      unless camera.closed?
        status = false
        break
      end
    end
  end

  status
end
