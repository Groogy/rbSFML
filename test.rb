require './lib/rbsfml.so'

SFML.blah()
puts SFML.say("Lalalal")

puts SFML::Foobar.to_s
puts SFML::Foobar.something

obj = SFML::Foobar.new()
puts obj
puts obj.somethingElse(6)
puts obj.somethingElse(8)

time = SFML::Time.new()
puts time
puts time.as_seconds
time = SFML.seconds(3.95)
puts time.as_seconds