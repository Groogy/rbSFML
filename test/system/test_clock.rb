
class TestClock < Test::Unit::TestCase
  include SFML
  
  def test_initialization
    clock = Clock.new
  end
  
  def test_equal
    clock1 = Clock.new
    clock2 = clock1.dup
    sleep(0.01)
    clock3 = Clock.new
    assert_equal(clock1, clock2)
    refute_equal(clock1, clock3)
  end
  
  def test_inspect
    clock = Clock.new
    str = "Clock(#{clock.time})"
    assert_equal(str, clock.inspect)
    assert_equal(" #{str} ", " #{clock} ")
  end
  
  def test_elapsed_time
    clock = Clock.new
    sleep(0.01)
    assert(clock.time < 20)
  end
  
  def test_reset
    clock = Clock.new
    sleep(0.01)
    clock.reset
    sleep(0.01)
    assert(clock.time < 20)
  end
  
end
