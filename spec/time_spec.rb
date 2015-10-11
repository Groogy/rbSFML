require './lib/rbsfml.so'

describe SFML::Time do
  describe "compare methods" do
    context "given an equal time" do
      time1 = SFML.seconds(2.0)
      time2 = SFML.seconds(2.0)

      it "returns true on equal" do
        expect(time1 == time2).to be_truthy
      end

      it "returns false on less than" do
        expect(time1 < time2).to be_falsy
      end

      it "returns false on greater than" do
        expect(time1 > time2).to be_falsy
      end
    end
  end

  describe "dup" do
    context "given an initialized time" do
      original = SFML.seconds(4.0)
      copy = original.dup
      
      it "creates an equal object" do
        expect(copy == original).to be_truthy
      end

      it "creates a new object" do
        expect(copy.equal?(original)).to be_falsy
      end
    end
  end
end