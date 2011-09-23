require 'sfml/system'
require 'sfml/window'
require 'sfml/graphics'

app = SFML::RenderWindow.new
app.create( [800, 600], "My Ruby SFML" )
app.framerate = 100
app.position = [300, 300]

shape = SFML::Shape.rectangle( [-10, -10, 20, 20], SFML::Color::White )

image = SFML::Image.new
image.create( 100, 100, SFML::Color.new( 255, 0, 0 ) )
texture = SFML::Texture.new( image )
sprite = SFML::Sprite.new( texture )
sprite.position = [500, 500]

text = SFML::Text.new( "This is a test!" )
text.position = [ 20, 20 ]

while app.open?
  while event = app.poll_event
    if event.type == SFML::Event::Closed
      app.close
    end
  end
  
  app.clear
  shape.position = SFML::Mouse.get_position( app )
  app.draw shape
  app.draw sprite
  app.draw text
  app.display
end 
