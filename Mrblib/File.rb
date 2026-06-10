# MIT LICENSE - Copyright (c) Ralph Desir 2026

class ::File
  def self.open(path, mode)
    if block_given?
      file = self.new(path, mode)

      obj = yield(file)

      file.close

      return obj
    else
      self.new(path, mode)
    end
  end
end
