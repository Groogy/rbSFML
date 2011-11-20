require 'test/unit'

begin
  require 'sfml/sfml'
  puts "Loaded 'sfml/sfml'"
rescue LoadError
  begin
    require 'sfml/system'
    puts "Loaded 'sfml/system'"
  rescue LoadError
    warn "Warning: Cannot load 'sfml/system'"
  end
  begin
    require 'sfml/window'
    puts "Loaded 'sfml/window'"
  rescue LoadError
    warn "Warning: Cannot load 'sfml/window'"
  end
  begin
    require 'sfml/graphics'
    puts "Loaded 'sfml/graphics'"
  rescue LoadError
    warn "Warning: Cannot load 'sfml/graphics'"
  end
  begin
    require 'sfml/audio'
    puts "Loaded 'sfml/audio'"
  rescue LoadError
    warn "Warning: Cannot load 'sfml/audio'"
  end
end

exit unless defined? SFML

if SFML.system?
  load "test/system/test_clock.rb"
  load "test/system/test_vector2.rb"
  load "test/system/test_vector3.rb"
end

if SFML.window?
  #load "test/window/test_videomode.rb"
end

if SFML.graphics?
  #load "test/graphics/test_color.rb"
  #load "test/graphics/test_rect.rb"
end

if SFML.audio?
  
end
