module SFML
  
  # Base class defining a sound's properties. <tt>SoundSource</tt> is not
  # meant to be used directly, it only serves as a common base for all audio
  # objects that can live in the audio environment. It defines several
  # properties for the sound: pitch, volume, position, attenuation, etc. All
  # of them can be changed at any time with no impact on performances.
  # @see Sound
  # @see SoundStream
  class SoundSource
    
    # Sound is not playing.
    Stopped = 0
    
    # Sound is paused.
    Paused = 1
    
    # Sound is playing.
    Playing = 2
    
    # @overload position
    #   Get the 3D position of the sound in the audio scene.
    #   @return [Vector3] Position of the sound
    # @overload position=(position)
    #   Set the 3D position of the sound in the audio scene. Only sounds with
    #   one channel (mono sounds) can be spatialized. The default position of
    #   a sound is (0, 0, 0).
    #   @param [Vector3] position Position of the sound in the sceneinate of the position of the sound in the
    #     scene
    # @overload position=(x, y, z)
    #   Set the 3D position of the sound in the audio scene. Only sounds with
    #   one channel (mono sounds) can be spatialized. The default position of
    #   a sound is (0, 0, 0).
    #   @param [Float] x X coordinate of the position of the sound in the
    #     scene
    #   @param [Float] y Y coordinate of the position of the sound in the
    #     scene
    #   @param [Float] z Z coordinate of the position of the sound in the
    #     scene
    def position
    end
    alias position= position
    alias GetPitch position
    alias SetPitch position
    
    # @overload min_distance
    #   Get the minimum distance of the sound.
    #   @return [Float] Minimum distance of the sound
    # @overload min_distance(distance)
    #   Set the minimum distance of the sound. The "minimum distance" of a
    #   sound is the maximum distance at which it is heard at its maximum
    #   volume. Further than the minimum distance, it will start to fade out
    #   according to its attenuation factor. A value of 0 ("inside the head of
    #   the listener") is an invalid value and is forbidden. The default value
    #   of the minimum distance is 1.
    #   @param [Float] distance New minimum distance of the sound
    def min_distance
    end
    alias min_distance= min_distance
    alias GetMinDistance min_distance
    alias SetMinDistance min_distance
    
    # Tell whether the sound's position is relative to the listener or is
    # absolute.
    # @return [Boolean] <tt>true</tt>  if the position is relative,
    #   <tt>false</tt> if it's absolute
    def relative_to_listener?
    end
    alias IsRelativeToListener relative_to_listener?
    
    # Make the sound's position relative to the listener or absolute. Making a
    # sound relative to the listener will ensure that it will always be played
    # the same way regardless the position of the listener. This can be useful
    # for non-spatialized sounds, sounds that are produced by the listener, or
    # sounds attached to it. The default value is false (position is
    # absolute).
    # @param [Boolean] relative <tt>true</tt> to set the position relative,
    #   <tt>false</tt> to set it absolute 
    def relative_to_listener=(relative)
    end
    alias relative_to_listener relative_to_listener=
    alias SetRelativeToListener relative_to_listener=
    
    # @overload volume
    #   Get the volume of the sound.
    #   @return [Float] Volume of the sound, in the range <tt>0..100</tt>
    # @overload volume=(volume)
    #   Set the volume of the sound. The volume is a value between 0 (mute)
    #   and 100 (full volume). The default value for the volume is 100.
    #   @param [Float] volume Volume of the sound
    def volume
    end
    alias volume= volume
    alias GetVolume volume
    alias SetVolume volume
    
    # @overload pitch
    #   Get the pitch of the sound.
    #   @return [Float] Pitch of the sound
    # @overload pitch=(pitch)
    #   Set the pitch of the sound. The pitch represents the perceived
    #   fundamental frequency of a sound; thus you can make a sound more acute
    #   or grave by changing its pitch. A side effect of changing the pitch is
    #   to modify the playing speed of the sound as well. The default value
    #   for the pitch is 1.
    #   @param [Float] pitch New pitch to apply to the sound 
    def pitch=(pitch)
    end
    alias pitch= pitch
    alias GetPitch pitch
    alias SetPitch pitch
    
    # @overload attenuation
    #   Get the attenuation factor of the sound.
    #   @return [Float] Attenuation factor of the sound
    # @overload attenuation=(attenuation)
    #   Set the attenuation factor of the sound. The attenuation is a
    #   multiplicative factor which makes the sound more or less loud
    #   according to its distance from the listener. An attenuation of 0 will
    #   produce a non-attenuated sound, i.e. its volume will always be the
    #   same whether it is heard from near or from far. On the other hand, an
    #   attenuation value such as 100 will make the sound fade out very
    #   quickly as it gets further from the listener. The default value of the
    #   attenuation is 1.
    #   @param [Float] attenuation New attenuation factor of the sound
    def attenuation
    end
    alias attenuation= attenuation
    alias GetAttenuation attenuation
    alias SetAttenuation attenuation
    
  end
  
end
