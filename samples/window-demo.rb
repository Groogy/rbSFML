begin
  require 'sfml/sfml'
rescue LoadError
  require 'sfml/system'
  require 'sfml/window'
end

window = SFML::Window.new([800, 600], "My rbSFML Window")
window.framerate = 60
window.position = [300, 300]

while window.opened?
  window.each_event do |event|
    p event
    case event
    when SFML::Event::Closed
      window.close
    end
  end
  
  window.display
end
