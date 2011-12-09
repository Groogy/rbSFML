# Based on SFML example Sound
# https://github.com/LaurentGomila/SFML/blob/master/examples/sound/Sound.cpp

begin
  require 'sfml/sfml'
rescue LoadError
  require 'sfml/system'
  require 'sfml/audio'
end

include SFML

def play_sound
  # Load a sound buffer from a wav file
  buffer = SoundBuffer.new
  buffer.load("resources/canary.wav")
  
  # Display sound informations
  puts "canary.wav:"
  puts "  #{buffer.duration / 1000.0} seconds"
  puts "  #{buffer.sample_rate} samples / sec"
  puts "  #{buffer.channels} channels"
  
  # Create a sound instance and play it
  sound = Sound.new(buffer)
  sound.play
  
  # Loop while the sound is playing
  while sound.status == Sound::Playing
    # Display the playing position
    print "\rPlaying... #{"%.2f" % (sound.offset / 1000.0)} sec"
    
    # Leave some CPU time for other processes
    sleep(0.1)
  end
  print "\n\n"
end

def play_music
  # Load an ogg music file
  music = Music.new
  music.open("resources/orchestral.ogg")
  
  # Display music informations
  puts "orchestral.ogg:"
  puts "  #{music.duration / 1000.0} seconds"
  puts "  #{music.sample_rate} samples / sec"
  puts "  #{music.channels} channels"

  # Play it
  music.play
  
  # Loop while the music is playing
  while music.status == Music::Playing
    # Display the playing position
    print "\rPlaying... #{"%.2f" % (music.offset / 1000.0)} sec"
    
    # Leave some CPU time for other processes
    sleep(0.1)
  end
  print "\n\n"
end

# Play a sound
play_sound

# Play a music
play_music

# Wait until the user presses 'enter' key
puts "Press enter to exit..."
gets
