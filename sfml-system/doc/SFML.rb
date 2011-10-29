# @note This code doesn't works yet.
# @example
#   require "sfml/audio"
#   require "sfml/graphics"
#   include SFML
#   
#   # Create the main window
#   window = RenderWindow.new(VideoMode.new(800, 600), "SFML window")
#   
#   # Load a sprite to display
#   texture = Texture.new("cute_image.jpg")
#   sprite = Sprite.new(texture)
#   
#   # Create a graphical text to display
#   font = Font.new("arial.ttf")
#   text = Text.new("Hello SFML", font, 50)
#   
#   # Load a music to play
#   music = Music.new("nice_music.ogg")
#   music.play
#   
#   # Start the game loop
#   while window.opened?
#     # Process events
#     window.each_event do |event|
#       case event
#       when Event::Closed
#         window.close
#       end
#     end
#     
#     # Clear screen
#     window.clear
#     
#     # Draw the sprite
#     window.draw(sprite)
#     
#     # Draw the string
#     window.draw(text)
#     
#     # Update the window
#     window.display
#   end

module SFML
  
  # SFML version
  VERSION = "2.0"
  
  # rbSFML version
  BINDING_VERSION = "development"
  
  # Set <tt>true</tt> if you want ruby-like exceptions to be raised.
  # If it is <tt>false</tt>, SFML errors will be printed to stderr and will be ignored.
  # Default is <tt>true</tt>.
  attr_accessor :raise_exceptions
  
  # Called everytime SFML raises a exception.
  # Raises a exception if <tt>raise_exceptions</tt> is <tt>true</tt> and clean the exception cache.
  # Does nothing if called outside SFML internal fucntions.
  # @note Internal function, don't use it!
  def SFML.raise
  end
  
end
