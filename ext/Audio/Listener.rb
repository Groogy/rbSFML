module SFML
  
  # The audio listener is the point in the scene from where all the sounds are heard.
  #
  # The audio listener defines the global properties of the audio environment, it defines where and how sounds and musics are heard.
  #
  # If SFML::View is the eyes of the user, then SFML::Listener is his ears (by the way, they are often linked together -- same position, orientation, etc.).
  #
  # SFML::Listener is a simple interface, which allows to setup the listener in the 3D audio environment (position and direction), and to adjust the global volume.
  #
  # Because the listener is unique in the scene, SFML::Listener only contains static functions and doesn't have to be instanciated.
  #
  # @example
  #   # Move the listener to the position(1, 0, -5)
  #   SFML::Listener.position = [1, 0, -5]
  #
  #   # Make it face the right axis
  #   SFML::Listener.direction = [1, 0, 0]
  #
  #
  #   # Reduce the global volume
  #   SFML::Listener.global_volume = 50
  module Listener
    # Get the current value of the global volume.
    # @return [Float] Current global volume, in the range [0, 100]
    def get_global_volume
    end
    alias getGlobalVolume get_global_volume
    alias global_volume get_global_volume
    
    # Change the global volume of all the sounds and musics.
    #
    # The volume is a number between 0 and 100; it is combined with the individual volume of each sound / music. The default value for the volume is 100 (maximum).
    # @param [Float] volume New global volume, in the range [0, 100]
    def set_global_volume(volume)
    end
    alias setGlobalVolume set_global_volume
    alias global_volume= set_global_volume
    
    # Get the current position of the listener in the scene. 
    # @return [SFML::Vector3] Listener's position
    def get_position
    end
    alias getPosition get_position
    alias position get_position
    
    # @overload set_position(x, y, z)
    #   Set the position of the listener in the scene.
    #
    #   The default listener's position is (0, 0, 0).
    #   @param [Float] x X coordinate of the listener's position
    #   @param [Float] y Y coordinate of the listener's position
    #   @param [Float] z Z coordinate of the listener's position
    # @overload set_position(position)
    #   Set the position of the listener in the scene.
    #
    #   The default listener's position is (0, 0, 0).
    #   @param [SFML::Vector3] position New listener's position
    def set_position(*args)
    end
    alias setPosition set_position
    alias position= set_position
    
    # Get the current orientation of the listener in the scene. 
    # @return [SFML::Vector3] Listener's orientation
    def get_direction
    end
    alias getDirection get_direction
    alias direction get_direction
    
    # @overload set_direction(x, y, z)
    #   Set the position of the listener in the scene.
    #
    #   The default listener's orientation is (0, 0, 0).
    #   @param [Float] x X coordinate of the listener's orientation
    #   @param [Float] y Y coordinate of the listener's orientation
    #   @param [Float] z Z coordinate of the listener's orientation
    # @overload set_direction(direction)
    #   Set the position of the listener in the scene.
    #
    #   The default listener's orientation is (0, 0, 0).
    #   @param [SFML::Vector3] direction New listener's orientation
    def set_direction(*args)
    end
    alias setDirection set_direction
    alias direction= set_direction
  end
end
