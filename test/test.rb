require 'test/unit'

begin
  require 'sfml/sfml.so'
rescue Exception
  begin
    require 'sfml/system.so'
  rescue Exception
  else
    $system = true
  end
  begin
    require 'sfml/window.so'
  rescue Exception
  else
    $window = true
  end
  begin
    require 'sfml/graphics.so'
  rescue Exception
  else
    $graphics = true
  end
  begin
    require 'sfml/audio.so'
  rescue Exception
  else
    $audio = true
  end
else
  $system = true
  $window = true
  $graphics = true
  $audio = true
end

unless $system or $window or $graphics or $audio
  puts "Failed to load rbSFML library. Nothing to test."
  exit
end

if $system
  
end

if $window
  
end

if $graphics
  load "test/graphics/test_color.rb"
end

if $audio
  
end
