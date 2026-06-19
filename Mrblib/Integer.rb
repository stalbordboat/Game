# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Integer Class Extension

class ::Integer
  def cycle(delta, limit)
    (self + delta) % (limit + 1)
  end

  def backward(limit)
    cycle(-1, limit)
  end

  def forward(limit)
    cycle(+1, limit)
  end
end
