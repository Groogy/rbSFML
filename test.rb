require './lib/rbsfml.so'

time1 = SFML.seconds(1.0)
time2 = SFML.milliseconds(2000)

puts time1.inspect
puts time2.inspect

puts time1.as_seconds
puts time2.as_seconds

puts (time2 - time1).inspect