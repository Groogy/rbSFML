# @example
#   require "sfml/all"
#   include SFML
#   
#   # Create the main window
#   window = RenderWindow.new([800, 600], "SFML window")
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
#     # Draw the text
#     window.draw(text)
#     
#     # Update the window
#     window.display
#   end

module SFML
  
  # <tt>Error</tt> is an exception class to show error messages from
  # <tt>SFML</tt> in a more ruby like way.
  class Error < RuntimeError
  end
  
  # SFML version
  SFML_VERSION = "2.0"
  
  # rbSFML version
  BINDING_VERSION = "development-unstable"
  
  # Set <tt>true</tt> if you want ruby-like exceptions to be raised. If it is
  # <tt>false</tt>, SFML errors will be printed to stderr and will be ignored.
  # Default is <tt>true</tt>.
  attr_accessor :raise_exceptions
  
  # Checks if <tt>'sfml/system'</tt> is loaded.
  # @return [Boolean] <tt>true</tt> if system is loaded, <tt>false</tt>
  #   otherwise
  def SFML.system?
  end
  
  # Checks if <tt>'sfml/window'</tt> is loaded.
  # @return [Boolean] <tt>true</tt> if window is loaded, <tt>false</tt>
  #   otherwise
  def SFML.window?
  end
  
  # Checks if <tt>'sfml/graphics'</tt> is loaded.
  # @return [Boolean] <tt>true</tt> if graphics is loaded, <tt>false</tt>
  #   otherwise
  def SFML.graphics?
  end
  
  # Checks if <tt>'sfml/audio'</tt> is loaded.
  # @return [Boolean] <tt>true</tt> if audio is loaded, <tt>false</tt>
  #   otherwise
  def SFML.audio?
  end
  
  
end
