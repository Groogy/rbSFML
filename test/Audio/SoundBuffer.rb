
class TestSoundBuffer < Test::Unit::TestCase
  include SFML
  
  def test_load
    sound_buffer1 = SoundBuffer.new
    sound_buffer2 = SoundBuffer.new
    sound_buffer3 = SoundBuffer.new
    sound_buffer4 = SoundBuffer.new
    assert_equal(sound_buffer1, sound_buffer1)
    assert_equal(sound_buffer1, sound_buffer2)
    assert_equal(sound_buffer1, sound_buffer3)
    assert_equal(sound_buffer1, sound_buffer4)
    
    sound_buffer1.load("test/canary.wav")
    assert_equal(sound_buffer1, sound_buffer1)
    refute_equal(sound_buffer1, sound_buffer2)
    refute_equal(sound_buffer1, sound_buffer3)
    refute_equal(sound_buffer1, sound_buffer4)
      
    file = File.open("test/canary.wav", "rb")
    sound_buffer2.load_stream(file)
    file.close
    assert_equal(sound_buffer1, sound_buffer1)
    assert_equal(sound_buffer1, sound_buffer2)
    refute_equal(sound_buffer1, sound_buffer3)
    refute_equal(sound_buffer1, sound_buffer4)
    
    samples = sound_buffer1.samples
    channels_count = sound_buffer1.channels_count
    sample_rate = sound_buffer1.sample_rate
    sound_buffer3.load_samples(samples, channels_count, sample_rate)
    assert_equal(sound_buffer1, sound_buffer1)
    assert_equal(sound_buffer1, sound_buffer2)
    assert_equal(sound_buffer1, sound_buffer3)
    refute_equal(sound_buffer1, sound_buffer4)
    
    file = File.open("test/canary.wav", "rb")
    sound_buffer4.load_memory(file.read)
    file.close
    assert_equal(sound_buffer1, sound_buffer1)
    assert_equal(sound_buffer1, sound_buffer2)
    assert_equal(sound_buffer1, sound_buffer3)
    assert_equal(sound_buffer1, sound_buffer4)
    
    assert_equal(sound_buffer1, Marshal.load(Marshal.dump(sound_buffer1)))
  end
  
  def test_save
    sound_buffer1 = SoundBuffer.new
    sound_buffer2 = SoundBuffer.new
    sound_buffer1.load("test/canary.wav")
    sound_buffer1.save("test/temp.wav")
    sound_buffer2.load("test/temp.wav")
    assert_equal(sound_buffer1, sound_buffer2)
    File.delete("test/temp.wav")
  end
  
end
