# MIT LICENSE - Copyright (c) Ralph Desir 2026
# Description: Test the API of the General subsystem.

path = 'General/Time.rb'

# Constants

send_test :found_at => path, :within => :constant_types? do
  Time::MAX.int?                  &&
  Time::MIN.int?                  &&
  Time::DATE_FORMAT_YYYYMMDD.int? &&
  Time::DATE_FORMAT_DDMMYYYY.int? &&
  Time::DATE_FORMAT_MMDDYYYY.int? &&
  Time::FORMAT_24HR.int?          &&
  Time::FORMAT_12HR.int?
end

send_test :found_at => path, :within => :constant_values? do
  Time::MAX.eql?(Math::INT_MAX)      &&
  Time::MIN.eql?(Math::INT_MIN)      &&
  Time::DATE_FORMAT_YYYYMMDD.eql?(0) &&
  Time::DATE_FORMAT_DDMMYYYY.eql?(1) &&
  Time::DATE_FORMAT_MMDDYYYY.eql?(2) &&
  Time::FORMAT_24HR.eql?(0)          &&
  Time::FORMAT_12HR.eql?(1)
end

# Methods

send_test :found_at => path, :within => :fileutils_stat_types? do
  filename = 'Time.rb'

  FileUtils::Stat.create_time(filename).int? &&
  FileUtils::Stat.modify_time(filename).int? &&
  FileUtils::Stat.access_time(filename).int?
end

def valid_time?(time)
  # Ranges taken from: https://wiki.libsdl.org/SDL3/SDL_DateTime
  years       = 1969..2030
  months      = 1..31
  hours       = 0..23
  days        = 0..31
  minutes     = 0..59
  seconds     = 0..60
  nanoseconds = 0..999999999

  if time.hash?
    years.include?(time[:year])             &&
    months.include?(time[:month])           &&
    hours.include?(time[:hour])             &&
    days.include?(time[:day])               &&
    seconds.include?(time[:second])         &&
    nanoseconds.include?(time[:nanosecond])
  else
    false
  end
end

def valid_utc?(time)
  utc_offset = time[:utc_offset]

  if time.hash?
    (-12 * 3600..14 * 3600).include?(utc_offset)
  else
    false
  end
end

send_test :found_at => path, :within => :fileutils_stat_values? do
  filename    = 'Time.rb'
  create_time = FileUtils::Stat.create_time(filename)
  modify_time = FileUtils::Stat.modify_time(filename)
  access_time = FileUtils::Stat.access_time(filename)

  valid_time?(Time.now(create_time)) &&
  valid_time?(Time.now(modify_time)) &&
  valid_time?(Time.now(access_time))
end

send_test :found_at => path, :within => :now_type? do
  access_time       = FileUtils::Stat.access_time('Time.rb')
  time_now          = Time.now
  time_access_local = Time.now(access_time)
  time_access_utc   = Time.now(access_time, false)

  time_now.hash?          &&
  time_access_local.hash? &&
  time_access_utc.hash? 
end

send_test :found_at => path, :within => :now_values? do
  access_time       = FileUtils::Stat.access_time('Time.rb')
  time_now          = Time.now
  time_access_local = Time.now(access_time)
  time_access_utc   = Time.now(access_time, false)

  valid_time?(time_now)          &&
  valid_time?(time_access_local) &&
  valid_utc?(time_access_utc) 
end

send_test :found_at => path, :within => :date_format_type? do
  Time.date_format.int?
end

send_test :found_at => path, :within => :date_format_value? do
  date_format = Time.date_format

  date_format.eql?(Time::DATE_FORMAT_YYYYMMDD) ||
  date_format.eql?(Time::DATE_FORMAT_DDMMYYYY) ||
  date_format.eql?(Time::DATE_FORMAT_MMDDYYYY)
end

send_test :found_at => path, :within => :format_types? do
  Time.format.int?
end

send_test :found_at => path, :within => :format_values? do
  format = Time.format

  format.eql?(Time::FORMAT_24HR) ||
  format.eql?(Time::FORMAT_12HR)
end

send_test :found_at => path, :within => :to_seconds_types? do
  Time.to_seconds(1000).int?
end

send_test :found_at => path, :within => :to_seconds_values? do
  Time.to_seconds(2000000000).eql?(2)
end

send_test :found_at => path, :within => :to_nanoseconds_types? do
  Time.to_nanoseconds(1).int?
end

send_test :found_at => path, :within => :to_nanoseconds_values? do
  Time.to_nanoseconds(2).eql?(2000000000)
end
