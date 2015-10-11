require './lib/rbsfml.so'

describe SFML::Clock do
  describe "will give elapsed time" do
    context "after two seconds has passed" do
      clock = SFML::Clock.new()
      sleep(2)

      it "the returned time will be longer" do
        expect(clock.elapsed_time.as_seconds).to be > 2.0
      end
    end
  end

  describe "will reset its time" do
    context "after restart has been called" do
      clock = SFML::Clock.new()
      sleep(2)
      time = clock.restart

      it "returning the elapsed time up to that point" do
        expect(time.as_seconds).to be > 2.0
      end

      it "next call to elapsed_time give a lower elapsed time" do
        expect(clock.elapsed_time).to be < time
      end
    end
  end
end