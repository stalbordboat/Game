# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Represent A File On A Filesystem

class ::File
  def self.open(path, mode)
    if block_given?
      file = self.new(path, mode)

      begin
        yield(file)
      ensure
        file.close
      end
    else
      self.new(path, mode)
    end
  end
end
