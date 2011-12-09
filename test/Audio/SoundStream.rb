
class TestSoundStream < Test::Unit::TestCase
  include SFML
  
  class MySoundStream1 < SoundStream
  end
  
  class MySoundStream2 < SoundStream
    def self.allocate
      raise TypeError
    end
  end
  
  class MySoundStream3 < SoundStream
    class << self
      undef allocate
    end
  end
  
  def test_exceptions
    assert_raise(RuntimeError) { SoundStream.new }
    assert_raise(RuntimeError) { MySoundStream1.new }
    assert_raise(RuntimeError) { MySoundStream2.new }
    assert_raise(RuntimeError) { MySoundStream3.new }
  end
  
end
