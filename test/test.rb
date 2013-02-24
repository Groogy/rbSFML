require 'test/unit'

begin
  require './lib/sfml/sfml'
  puts "Loaded 'lib/sfml/sfml'"
rescue LoadError
  ['system', 'window', 'graphics', 'audio'].each do |lib|
    begin
      require "./lib/sfml/#{lib}"
    rescue LoadError
      warn "Warning: Cannot load 'lib/sfml/#{lib}'"
    end
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
  load "test/Window/Joystick.rb"
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
  load "test/Audio/Sound.rb"
  load "test/Audio/SoundBuffer.rb"
  load "test/Audio/SoundSource.rb"
  load "test/Audio/SoundStream.rb"
end
