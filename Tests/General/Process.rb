# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the General subsystem.

PATH = 'General/Process.rb'

# Class Methods

send_test :found_at => PATH, :within_block => :class_methods_defined? do
  methods = %w(open)

  methods.methods_defined? :within => Process
end

send_test :found_at => PATH, :within_block => :self_open? do
  cmd     = ['./cmd']
  process = Process.open(cmd)

  process.kind_of?(Process) && process.close.nil?
end

send_test :found_at => PATH, :within_block => :instance_methods_defined? do
  cmd     = ['./cmd']
  process = Process.open(cmd)

  methods = %w(
                close
                end
                read
                exit_code
                wait
              )

  methods.methods_defined? :within => process
end

send_test :found_at => PATH, :within_block => :self_open_without_pipe? do
  cmd     = ['./cmd']
  process = Process.open(cmd)
  status  = nil

  status = recover? { process.read }

  process.close

  status
end

send_test :found_at => PATH, :within_block => :self_open_with_pipe? do
  cmd     = ['./cmd']
  process = Process.open(cmd, true)
  status  = nil

  status = process.read.eql?("Process Test!") && process.exit_code.eql?(0)

  process.close

  status
end

# Instance Methods

send_test :found_at => PATH, :within_block => :end? do
  cmd     = ['./cmd']
  process = Process.open(cmd, true)
  status  = nil

  status = process.end.nil?

  process.close

  status
end

