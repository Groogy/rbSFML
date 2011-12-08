
class TestSound < Test::Unit::TestCase
  include SFML
  
  def test_equal
    sound1 = Sound.new
    sound2 = Sound.new
    refute(sound1 == sound2)
    refute(sound1.eql? sound2)
  end
  
  def test
    sound = Sound.new
    sound_buffer = SoundBuffer.new
    sound_buffer.load("test/canary.wav")
    assert_equal(nil, sound.buffer)
    sound.buffer = sound_buffer
    assert_equal(sound_buffer.object_id, sound.buffer.object_id)
    dumped = Marshal.dump(sound_buffer)
    sound_buffer = nil
    GC.start
    assert_equal(Marshal.load(dumped), sound.buffer)
  end
  
  def test_inspect
    sound = Sound.new
    assert_match(/SFML::Sound\([0-9a-fx]+\)/, sound.inspect)
    assert_match(/ SFML::Sound\([0-9a-fx]+\) /, " #{sound} ")
  end
  
  def test_exceptions
    assert_raise(TypeError) { Marshal.dump(Sound.new) }
  end
  
  class MySound < Sound
  end
  
  def test_subclass
    my_sound = MySound.new
    sound = Sound.new
    
    assert_equal(my_sound.class, my_sound.dup.class)
  end
  
end
