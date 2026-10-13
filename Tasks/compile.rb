# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: 

class Compile
  def initialize(compiler, src, dest)
    @compiler = compiler
    @src      = src
    @dest     = dest
  end

  def bytecode_c
    desc 'Compile a Ruby file into a byte array'
    task __method__, [:filename] do |task, args|
      filename = args[:filename]
      basename = File.basename(filename, '.rb')
      path     = "#{@src}/#{filename}"

      sh("#{@compiler} -B #{basename}_symbol #{path}")

      src  = "#{@src}/#{basename}.c"
      dest = "#{@dest}/#{basename}.c"

      FileUtils.mv(src, dest, verbose: true)
    end
  end

  def bytecode_mrb
    desc 'Compile a Ruby file into a bytecode'
    task __method__, [:filename] do |task, args|
      filename = args[:filename]
      path     = "#{@src}/#{filename}"

      sh("#{@compiler} #{path}")
    end
  end
end

def compile(output_type, with_this_compiler: nil, move_output_from: nil, to: nil)
  compiler = Compile.new(with_this_compiler, move_output_from, to)

  compiler.send(output_type)
end
