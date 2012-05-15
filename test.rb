require 'sfml/system'
require 'sfml/window'
require 'sfml/graphics'

window = SFML::RenderWindow.new( [ 800, 600 ], "Test" )

text = SFML::Text.new( "Hello World!" )
text.color = [ 255, 0, 255 ]
text.position = [ 10, 10 ]
texture = SFML::Texture.new( "test.pg" )
sprite = SFML::Sprite.new( texture )
sprite.origin = [ 50, 50 ]

while window.open?
  window.clear
  window.draw text
  window.draw sprite
  window.display
 
  sprite.position = SFML::Mouse.position( window )
 
  window.each_event do |event|
    if event.type == SFML::Event::Closed
      window.close
    end
  end
end