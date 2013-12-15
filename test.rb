require 'sfml/extra'

window = SFML::RenderWindow.new([1024, 768, 32], "Hello world!")

SFML.load_opengl()

effect = SFML::Effect.new()
effect.load_from_file("test.shader")
effect.set_parameter "color", 1.0, 0.0, 1.0, 1.0

layout = SFML::VertexLayout.new()
layout << {:size => 4, :type => Float, :stride => 0, :offset => 0}

vbo = SFML::VertexBufferObject.new(layout)
vbo.primitive = SFML::TrianglesStrip
vbo.effect = effect
vbo << [ -1.0, -1.0, 0.0, 1.0 ]
vbo << [ -1.0, 0.5, 0.0, 1.0 ]
vbo << [ 0.5, -1.0, 0.0, 1.0 ]
vbo << [ 0.5, 0.5, 0.0, 1.0 ]
puts "Hello world!"
puts vbo.inspect

shape = SFML::CircleShape.new()
shape.radius = 50
shape.position = [100, 100]

while window.open?
	window.each_event do |event|
    window.close() if event.type == SFML::Event::Closed
	end
	
	window.clear(SFML::Color::Red)
	window.draw(vbo)
  window.draw(shape)
	window.display()
end

puts "Bai bai!"
