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
  load "test/System/Clock.rb"
  load "test/System/SFML.rb"
  load "test/System/Vector2.rb"
  load "test/System/Vector3.rb"
end

if SFML.window?
  load "test/Window/Context.rb"
  load "test/Window/ContextSettings.rb"
  load "test/Window/Keyboard.rb"
  load "test/Window/Mouse.rb"
  load "test/Window/Style.rb"
  load "test/Window/VideoMode.rb"
  load "test/Window/Window.rb"
end

if SFML.graphics?
  #load "test/Graphics/Color.rb"
  #load "test/Graphics/Rect.rb"
end

if SFML.audio?
  
end
