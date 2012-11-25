
class TestClock < Test::Unit::TestCase
  include SFML
  
  def test_initialization
    clock = Clock.new
  end
  
  def test_equal
    clock1 = Clock.new
    sleep(0.100)
    clock2 = clock1.dup
    sleep(0.100)
    clock3 = Clock.new
    assert_equal(clock1, clock2)
    refute_equal(clock1, clock3)
    refute(clock1.eql? clock2)
    refute(clock1.eql? clock3)
  end
  
  def test_inspect
    clock = Clock.new
    assert_match(/SFML::Clock\(\d+\.\d+s\)/, clock.inspect)
    assert_match(/SFML::Clock\(\d+\.\d+s\)/, "#{clock}")
  end
  
  def test_elapsed_time
    clock = Clock.new
    sleep(0.100)
    assert_in_delta(clock.time.as_milliseconds, 100, 40)
  end
  
  def test_restart
    clock = Clock.new
    assert_in_delta(clock.time.as_milliseconds, 0, 40)
    sleep(0.100)
    assert_in_delta(clock.time.as_milliseconds, 100, 40)
    
    clock.restart
    assert_in_delta(clock.time.as_milliseconds, 0, 40)
    sleep(0.100)
    assert_in_delta(clock.time.as_milliseconds, 100, 40)
  end
  
  def test_compare
    clock1 = Clock.new
    sleep(0.100)
    clock2 = Clock.new
    assert_operator(clock1.time, :>, clock2.time)
    refute_operator(clock1.time, :<=, clock2.time)
    sleep(0.100)
    assert_operator(clock1.time, :>, clock2.time)
    refute_operator(clock1.time, :<=, clock2.time)
    clock1.restart
    assert_operator(clock1.time, :<=, clock2.time)
    refute_operator(clock1.time, :>, clock2.time)
    assert_operator(clock2.time, :>, clock1.time)
  end
  
  class MyClock < Clock
  end
  
  def test_subclass
    my_clock = MyClock.new
    
    assert_in_delta(my_clock.time.as_milliseconds, 0, 10)
    assert_equal(my_clock.class, my_clock.dup.class)
    
    assert_match(/TestClock::MyClock\(\d+\.\d+s\)/, my_clock.inspect)
  end
  
end
