# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Get an instance of the Process object. This launches a new process.
# Optionally io can be set to true to get I/O piping. This must be closed when no
# longer needed, because a process is a system resource.

class Process
  def self.open(cmd, io: false)
    process = self.new(cmd, io: io)

    if block_given?
      begin
        obj = yield(process)
      ensure
        process.close
        obj
      end
    else
      process
    end
  end
end
