# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Represents Gamepad Devices

class Gamepad
  def self.open(which)
    gamepad = self.new(which)

    if block_given?
      begin
        obj = yield(gamepad)
      ensure
        gamepad.close
        obj
      end
    else
      gamepad
    end
  end
end
