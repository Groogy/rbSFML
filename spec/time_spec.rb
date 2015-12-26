require './lib/sfml/rbsfml.so'

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
    context "given a smaller time" do
      time1 = SFML.seconds(4.0)
      time2 = SFML.seconds(2.0)

      it "returns false on equal" do
        expect(time1 == time2).to be_falsy
      end

      it "returns false on less than" do
        expect(time1 < time2).to be_falsy
      end

      it "returns true on greater than" do
        expect(time1 > time2).to be_truthy
      end
    end
    context "given an bigger time" do
      time1 = SFML.seconds(2.0)
      time2 = SFML.seconds(4.0)

      it "returns false on equal" do
        expect(time1 == time2).to be_falsy
      end

      it "returns true on less than" do
        expect(time1 < time2).to be_truthy
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