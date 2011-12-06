
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
    refute(clock1.eql? clock2)
    refute(clock1.eql? clock3)
  end
  
  def test_inspect
    clock = Clock.new
    assert_match(/SFML::Clock\(\d+ms\)/, clock.inspect)
    assert_match(/ SFML::Clock\(\d+ms\) /, " #{clock} ")
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
  
  class MyClock < Clock
  end
  
  def test_subclass
    my_clock = MyClock.new
    
    assert_in_delta(my_clock.time, 0, 10)
    assert_equal(my_clock.class, my_clock.dup.class)
    
    assert_match(/TestClock::MyClock\(\d+ms\)/, my_clock.inspect)
    
  end
  
end
