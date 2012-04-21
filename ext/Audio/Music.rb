module SFML
  class SoundStream
  end
  
  # Streamed music played from an audio file.
  #
  # Musics are sounds that are streamed rather than completely loaded in memory.
  #
  # This is especially useful for compressed musics that usually take hundreds of MB when they are uncompressed: by streaming it instead of loading it entirely, you avoid saturating the memory and have almost no loading delay.
  #
  # Apart from that, a SFML::Music has almost the same features as the SFML::SoundBuffer / SFML::Sound pair: you can play/pause/stop it, request its parameters (channels, sample rate), change the way it is played (pitch, volume, 3D position, ...), etc.
  #
  # As a sound stream, a music is played in its own thread in order not to block the rest of the program. This means that you can leave the music alone after calling play(), it will manage itself very well.
  #
  # @example
  #   # Declare a new music
  #   music = SFML::Music.new
  #
  #   # Open it from an audio file
  #   if music.openFromFile("music.ogg") == false
  #     # error...
  #   end
  #
  #   # Change some parameters
  #   music.position = [0, 1, 10] # change its 3D position
  #   music.pitch = 2             # increase the pitch
  #   music.volume = 50           # reduce the volume
  #   music.loop = true           # make it loop
  #
  #   # Play it
  #   music.play()
  class Music < SFML::SoundStream
    def open_from_file(filename)
    end
    
    def open_from_memory(memory)
    end
    
    def open_from_stream(io_stream)
    end
    
    def duration
    end
  end
end
