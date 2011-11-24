require 'sfml/system'
require 'sfml/window'

window = SFML::Window.new([800, 600], "My Ruby SFML")
#window.framerate = 60
window.position = [300, 300]

while window.open?
  window.each_event do |event|
    p event
    case event
    when SFML::Event::Closed
      window.close
    end
  end
  
  #window.display
end
