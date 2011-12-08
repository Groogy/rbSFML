
class TestSoundSource < Test::Unit::TestCase
  include SFML
  
  class MySoundSource1 < SoundSource
  end
  
  class MySoundSource2 < SoundSource
    def self.allocate
      raise TypeError
    end
  end
  
  class MySoundSource3 < SoundSource
    class << self
      undef allocate
    end
  end
  
  def test_exceptions
    assert_raise(RuntimeError) { SoundSource.new }
    assert_raise(RuntimeError) { MySoundSource1.new }
    assert_raise(RuntimeError) { MySoundSource2.new }
    assert_raise(RuntimeError) { MySoundSource3.new }
  end
  
end
