# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: 

#desc 'Moves install files to the install path'
#task :install do |task|
#  verbose = !task.application.options.silent

#  FileUtils.install(BIN, BIN_PREFIX, verbose: verbose)

#  FileUtils.cp_r(NATIVE_PATH, INC_PREFIX, verbose: verbose)
#end

class Installer
  attr_accessor :filename_bin
  attr_accessor :path_includes

  def initialize(prefix_bin, prefix_includes)
    @prefix_bin      = prefix_bin
    @prefix_includes = prefix_includes
  end

  def install
    desc 'Moves install files to the install path'
    task :install do |task|
      verbose = !task.application.options.silent

      FileUtils.install(@filename_bin, @prefix_bin, verbose: verbose)

      FileUtils.cp_r(@path_includes, @prefix_includes, verbose: verbose)
    end
  end

  def uninstall
    desc 'Removes install files from the install path'
    task :uninstall do |task|
      verbose = !task.application.options.silent

      cd(@prefix_bin, verbose: verbose) { remove_bin(verbose) }

      cd(@prefix_includes, verbose: verbose) { remove_includes(verbose) }
    end
  end

  private

  def remove_includes(verbose)
    FileUtils.rm_rf(@path_includes, verbose: verbose)
  end

  def remove_bin(verbose)
    FileUtils.rm_f(@filename_bin, verbose: verbose)
  end
end

def installer(install_bin_to: nil, copy_includes_to: nil, remove_bin_from: nil, remove_includes_from: nil)
  unless install_bin_to.nil? && copy_includes_to.nil?
    installer = Installer.new(install_bin_to, copy_includes_to)
    mode      = :install
  end

  unless remove_bin_from.nil? && remove_includes_from.nil?
    installer = Installer.new(remove_bin_from, remove_includes_from)
    mode      = :uninstall
  end

  unless mode.nil?
    yield(installer)

    installer.send(mode)
  end
end
