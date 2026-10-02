# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the General subsystem.

path = 'General/Power.rb'

# Methods

send_test :found_at => path, :within => :types? do
  Power.unknown?.bool?    &&
  Power.on_battery?.bool? &&
  Power.no_battery?.bool? &&
  Power.charging?.bool?   &&
  Power.charged?.bool?    &&
  Power.seconds.int?      &&
  Power.percent.int?
end

send_test :found_at => path, :within => :values? do
  unknown        = Power.unknown?
  on_battery     = Power.on_battery?
  no_battery     = Power.no_battery?
  charging       = Power.charging?
  charged        = Power.charged?
  seconds        = Power.seconds
  percent        = Power.percent
  status_battery = false
  status_amount  = false

  status_battery = (unknown.eql?(true)    || unknown.eql?(false))    &&
                   (on_battery.eql?(true) || on_battery.eql?(false)) &&
                   (no_battery.eql?(true) || no_battery.eql?(false)) &&
                   (charging.eql?(true)   || charging.eql?(false))   &&
                   (charged.eql?(true)    || charged.eql?(false))

  if no_battery || unknown
    status_amount = (seconds.eql?(-1) || percent.eql?(-1))
  else
    status_amount = (seconds.greater_than?(0) || percent.greater_than?(0))
  end

  status_battery && status_amount
end
