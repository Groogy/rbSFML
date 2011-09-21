require 'sfml/system'
require 'sfml/window'

app = SFML::Window.new( [800, 600], "My Ruby SFML" )
app.framerate = 100
app.position = [300, 300]

while app.open?
  while event = app.poll_event
    if event.type == SFML::Event::Closed
      app.close
    end
  end
  
  
  p [SFML::Mouse.get_position.x, SFML::Mouse.get_position.y]
  
  app.display
end
