require 'test/unit'

if File.exist? './sfml/sfml.so'
  require './sfml/sfml.so'
  $system = true
  $window = true
  $graphics = true
  $audio = true
else
  if File.exist? './sfml/system.so'
    require './sfml/system.so'
    $system = true
  end
  if File.exist? './sfml/window.so'
    require './sfml/window.so'
    $window = true
  end
  if File.exist? './sfml/graphics.so'
    require './sfml/graphics.so'
    $graphics = true
  end
  if File.exist? './sfml/audio.so'
    require './sfml/audio.so'
    $audio = true
  end
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
