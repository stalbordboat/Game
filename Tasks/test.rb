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
# Task::Test.new('../../game') do |spec|
#  spec.check_symbols = 'Tests/CheckSymbols'
#  spec.window        = 'Tests/Window'
# end
#
# When running environment, it expects an archive called Test.zip.

class TaskTest
  attr_accessor :check_symbols
  attr_accessor :environments
  attr_accessor :window
  attr_accessor :events
  attr_accessor :audio
  attr_accessor :general

  def initialize(bin, extra_utilities)
    @bin             = bin
    @extra_utilities = extra_utilities

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

  def run_cmd(path, env='', options: nil)
    cd(path) { sh("#{env} #{@bin} #{options}") }
  end

  def run_check_symbols
    run_cmd(@check_symbols)
  end

  def run_environments
    # Run outside Archive.
    env = 'GAME_START_PATH="Init.rb" GAME_NO_WINDOW=true GAME_NO_EVENTS=true GAME_NO_AUDIO=true'
    run_cmd(@environments, env)

    # Run inside Archive.
    env = 'GAME_START_PATH=Init.rb GAME_NO_WINDOW=true GAME_NO_EVENTS=true GAME_NO_AUDIO=true GAME_PHYSFS_ARCHIVE=Test.zip ARCHIVE_HAS_WRITE=false'
    run_cmd(@environments, env)
  end

  def run_window
    run_cmd(@window)
  end

  def run_events
    run_cmd(@events)
  end

  def run_audio
    run_cmd(@audio, 'SDL_AUDIO_DRIVER=dummy')
  end

  def run_general
    bin = 'cmd'

    build_process_test_cmd(bin) if c_compiler?

    run_cmd(@general, options: '-foo -bar')

    remove_process_test_cmd(bin) if c_compiler?
  end

  def build_process_test_cmd(bin)
    cd(@general) { sh("#{@extra_utilities[:c_compiler]} cmd.c -o #{bin}") }
  end

  def remove_process_test_cmd(bin)
    cd(@general) { rm(bin) }
  end

  def c_compiler?
    !@extra_utilities[:c_compiler].nil?
  end
end

def test(using: nil, extra_utilities: nil)
  # extra_utilities is purely optional so no raise is needed for that keyword argument.
  raise 'The test spec requires a bin, example: test :using => "game"' if using.nil?
  TaskTest.new(using, extra_utilities) { |spec| yield(spec) }
end
