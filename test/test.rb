require 'test/unit'

begin
  require 'sfml/sfml.so'
rescue Exception
  begin
    require 'sfml/system.so'
  rescue Exception
  else
    puts "Loaded 'sfml/system.so'"
    $system = true
  end
  begin
    require 'sfml/window.so'
  rescue Exception
  else
    puts "Loaded 'sfml/window.so'"
    $window = true
  end
  begin
    require 'sfml/graphics.so'
  rescue Exception
  else
    puts "Loaded 'sfml/graphics.so'"
    $graphics = true
  end
  begin
    require 'sfml/audio.so'
  rescue Exception
  else
    puts "Loaded 'sfml/audio.so'"
    $audio = true
  end
else
  puts "Loaded 'sfml/sfml.so'"
  $system = true
  $window = true
  $graphics = true
  $audio = true
end

warn "Warning: Cannot load System module"   unless $system
warn "Warning: Cannot load Window module"   unless $window
warn "Warning: Cannot load Graphics module" unless $graphics
warn "Warning: Cannot load Audio module"    unless $audio

exit unless $system or $window or $graphics or $audio

if $system
  
end

if $window
  
end

if $graphics
  load "test/graphics/test_color.rb"
  load "test/graphics/test_rect.rb"
end

if $audio
  
end
