require 'test/unit'

begin
  require 'sfml/sfml'
  puts "Loaded 'sfml/sfml'"
  $system = true
  $window = true
  $graphics = true
  $audio = true
rescue LoadError
  begin
    require 'sfml/system'
    puts "Loaded 'sfml/system'"
    $system = true
  rescue LoadError
  end
  begin
    require 'sfml/window'
    puts "Loaded 'sfml/window'"
    $window = true
  rescue LoadError
  end
  begin
    require 'sfml/graphics'
    puts "Loaded 'sfml/graphics'"
    $graphics = true
  rescue LoadError
  end
  begin
    require 'sfml/audio'
    puts "Loaded 'sfml/audio'"
    $audio = true
  rescue LoadError
  end
end

warn "Warning: Cannot load System module"   unless $system
warn "Warning: Cannot load Window module"   unless $window
warn "Warning: Cannot load Graphics module" unless $graphics
warn "Warning: Cannot load Audio module"    unless $audio

if $system
  load "test/system/test_clock.rb"
end

if $window
  
end

if $graphics
  load "test/graphics/test_color.rb"
  load "test/graphics/test_rect.rb"
end

if $audio
  
end
