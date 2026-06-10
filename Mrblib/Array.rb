# MIT LICENSE - Copyright (c) Ralph Desir 2026

class ::Array
  def limit
    size - 1
  end

  def update
    self.each { |object| object.update }
  end
end
