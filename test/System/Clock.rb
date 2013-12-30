require 'minitest/autorun'
require 'sfml/audio'
include SFML

describe Clock do
  before do
    @clock = Clock.new
  end

  it "duplicates elapsed time" do
    sleep 0.1
    clock = @clock.dup
    @clock.time.as_milliseconds.must_be_close_to clock.time.as_milliseconds
    @clock.wont_be_same_as clock
  end

  it "has a useful string representation" do
    @clock.inspect.must_match /^SFML::Clock\(\d+\.\d+s\)$/
    @clock.to_s.must_match /^SFML::Clock\(\d+\.\d+s\)$/
  end

  it "is accurate" do
    sleep 0.1
    @clock.time.as_milliseconds.must_be_close_to 100, 40
  end

  it "can be reset" do
    @clock.time.as_milliseconds.must_be_close_to 0, 40
    sleep 0.1
    @clock.time.as_milliseconds.must_be_close_to 100, 40

    @clock.restart
    @clock.time.as_milliseconds.must_be_close_to 0, 40
    sleep 0.1
    @clock.time.as_milliseconds.must_be_close_to 100, 40
  end

  it "is comparable to other Clocks" do
    sleep 0.1
    clock = Clock.new
    @clock.must_be :>, clock
    @clock.wont_be :<=, clock

    sleep 0.1
    @clock.must_be :>, clock
    @clock.wont_be :<=, clock

    @clock.reset
    @clock.must_be :<=, clock
    @clock.wont_be :>, clock
    clock.must_be :>, @clock.time
  end

  describe "when subclassed" do
    before do
      class MyClock < Clock
      end

      @clock = MyClock.new
    end

    it "is accurate" do
      @clock.time.as_milliseconds.must_be_close_to 0, 10
    end

    it "can be duplicated" do
      @clock.class.must_be_same_as @clock.dup.class
    end

    it "has a useful string representation" do
      @clock.inspect.must_match /^MyClock\(\d+\.\d+s\)$/
    end
  end
end
