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
end