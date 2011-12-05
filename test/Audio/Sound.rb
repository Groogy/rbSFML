
class TestSound < Test::Unit::TestCase
  include SFML
  
  def test1
    sound = Sound.new
    sound_buffer = SoundBuffer.new
    sound_buffer.load("test/canary.wav")
    assert_equal(nil, sound.buffer)
    sound.buffer = sound_buffer
    assert_equal(sound_buffer.object_id, sound.buffer.object_id)
    dump = Marshal.dump(sound_buffer)
    sound_buffer = nil
    GC.start
    assert_equal(Marshal.load(dump), sound.buffer)
  end
  
  def test_exceptions
    assert_raise(TypeError) { Marshal.dump(Sound.new) }
  end
  
end
