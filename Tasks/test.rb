# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Rake Extension DSL For Test Automation
#
# This script is meant to be required into a Rakefile and configured to automate one or more standardized unit tests.
# The standardized unit tests are:
# + check_symbols - Test the existence of methods and attributes.
# + environments  - Test if the environment variables work the way they're supposed to(probably not useful for most projects).
# + window        - Test the window subsystem.
# + audio         - Test the audio subsystem.
# + events        - Test the events subsystem.
# + general       - Test the general subsystem.
#
# Each set of tests just game projects, they are in directories like 'Tests/CheckSymbols', and are run with the game,
# executable. So there must be a Start.rb or some other entry point script.
#
# Example: This example tests two cases, check_symbols and window.
# require_relative 'Tasks/test.rb'
#
# # The path here is reletive to where the testing scripts are, so '../../' for 'Tests/CheckSymbols'.
# # Each test should be a subdirectory of 'Tests'.
# # The keyword arguments are all required, because some or potentially tests may use a compiler as part of the
# # testing process.
# test :using => '../../game', :compile_using => {c_compiler: 'cc', :with_these_pkgs => 'sdl3 game-mruby'} do |spec|
#  spec.check_symbols = 'Tests/CheckSymbols'
#  spec.window        = 'Tests/Window'
# end
#
# You may need to install rubyzip because the tests require testing a zip archive, so run this command if you don't have
# rubyzip installed:
#
# bundle install
#
# You can run all tests like this:
# rake test
#
# or you can run selected tests, for example:
# rake "test[check_symbols]"

require 'zip'

class TaskTest
  attr_accessor :check_symbols
  attr_accessor :environments
  attr_accessor :window
  attr_accessor :events
  attr_accessor :audio
  attr_accessor :general

  def initialize(bin, compile_using)
    @bin           = bin
    @compile_using = compile_using

    yield self

    desc 'Run each specified test'
    task :test, [:which] do |task, args|
      which = args[:which]

      if which.nil?
        run_check_symbols if @check_symbols
        run_environments  if @environments
        run_window        if @window
        run_events        if @events
        run_audio         if @audio
        run_general       if @general
      else
        send("run_#{which}")
      end
    end
  end

  private

  def run_cmd_bin(path, env='', options: nil)
    cd(path) { sh("#{env} #{@bin} #{options}") }
  end

  def run_cmd_c_compiler(path, env='', options: nil, pkgs: @compile_using[:with_these_pkgs])
    pkg_configs = "$(pkg-config --cflags --libs #{pkgs})"

    cd(path) { sh("#{env} #{@compile_using[:c_compiler]} #{options} #{pkg_configs}") }
  end

  def c_compiler?
    !@compile_using[:c_compiler].nil?
  end

  def run_cmd_remove(path, filename)
    cd(path) { rm(filename) }
  end

  def create_archive(filename)
    cd(@environments) do
      # Keep only if files relevant to testing within archives
      filenames = Dir.entries('.').keep_if do |entry|
        !entry.include?('SDLFile') && !entry.eql?('.') && !entry.eql?('..')
      end

      Zip::File.open(filename, create: true) do |zip_file|
        filenames.each { |filename| zip_file.add(filename, filename) }
      end
    end
  end

  def run_check_symbols
    run_cmd_bin(@check_symbols)
  end

  def run_environments
    filename_src     = 'Entry.c'
    filename_output  = 'Test.so'
    filename         = 'Test.zip'
    options_build_so = "-fpic -I ../../Include #{filename_src} -shared -o #{filename_output}"

    run_cmd_c_compiler(@environments, options: options_build_so) if c_compiler?

    # Run outside Archive.
    env = 'GAME_START_PATH="Init.rb" GAME_NO_WINDOW=true GAME_NO_EVENTS=true GAME_NO_AUDIO=true'
    run_cmd_bin(@environments, env)

    create_archive(filename)

    # Run inside Archive.
    env = 'GAME_START_PATH=Init.rb GAME_NO_WINDOW=true GAME_NO_EVENTS=true GAME_NO_AUDIO=true GAME_PHYSFS_ARCHIVE=Test.zip ARCHIVE_HAS_WRITE=false'
    run_cmd_bin(@environments, env)

    run_cmd_remove(@environments, filename_output)
    run_cmd_remove(@environments, filename)
  end

  def run_window
    run_cmd_bin(@window)
  end

  def run_events
    run_cmd_bin(@events)
  end

  def run_audio
    run_cmd_bin(@audio, 'SDL_AUDIO_DRIVER=dummy')
  end

  def run_general
    bin = 'cmd'

    run_cmd_c_compiler(@general, options: "cmd.c -o #{bin}") if c_compiler?

    run_cmd_bin(@general, options: '-foo -bar')

    run_cmd_remove(@general, bin)
  end
end

def test(using: nil, compile_using: nil)
  raise 'The test spec requires a bin, example: test :using => "game"' if using.nil?
  raise 'The test spec requires a c compiler, example: :compile_using => {c_compiler: "cc", :with_these_pkgs => "sdl3"}' if compile_using.nil?

  TaskTest.new(using, compile_using) { |spec| yield(spec) }
end
