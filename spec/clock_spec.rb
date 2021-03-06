require './lib/sfml/rbsfml.so'

describe SFML::Clock do
  describe "will give elapsed time" do
    context "after two seconds has passed" do
      clock = SFML::Clock.new
      SFML.sleep(SFML.milliseconds(20))

      it "the returned time will be longer" do
        expect(clock.elapsed_time.as_milliseconds).to be > 20
      end
    end
  end

  describe "will reset its time" do
    context "after restart has been called" do
      clock = SFML::Clock.new
      time = SFML::Time.new
      before(:each) do
        SFML.sleep(SFML.milliseconds(20))
        time = clock.restart
      end

      it "returning the elapsed time up to that point" do
        expect(time.as_milliseconds).to be > 18 # SFML doesn't guarantee that elapsed time will be passed 20 milliseconds
      end

      it "next call to elapsed_time give a lower elapsed time" do
        expect(clock.elapsed_time).to be < time
      end
    end
  end
end