
class TestClock < Test::Unit::TestCase
  include SFML
  
  def test_initialization
    clock = Clock.new
  end
  
  def test_equal
    clock1 = Clock.new
    clock2 = clock1.dup
    sleep(0.010)
    clock3 = Clock.new
    assert_equal(clock1, clock2)
    refute_equal(clock1, clock3)
    assert(clock1.eql? clock2)
    refute(clock1.eql? clock3)
  end
  
  def test_inspect
    clock = Clock.new
    assert_match(/Clock\(\d+\)/, clock.inspect)
    assert_match(/ Clock\(\d+\) /, " #{clock} ")
  end
  
  def test_elapsed_time
    clock = Clock.new
    sleep(0.010)
    assert_in_delta(clock.time, 10, 10)
  end
  
  def test_reset
    clock = Clock.new
    assert_in_delta(clock.time, 0, 10)
    sleep(0.010)
    assert_in_delta(clock.time, 10, 10)
    clock.reset
    assert_in_delta(clock.time, 0, 10)
    sleep(0.010)
    assert_in_delta(clock.time, 10, 10)
  end
  
end
