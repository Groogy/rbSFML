require './lib/sfml/rbsfml.so'

describe SFML::Color do
  describe "in creation" do
    context "given no arguments" do
      obj = SFML::Color.new
      it "color properties should be zero" do
        expect(obj.r).to be(0)
        expect(obj.g).to be(0)
        expect(obj.b).to be(0)
      end

      it "should be equal to black color" do
        expect(obj == SFML::Color::Black).to be_truthy
      end

      it "should be equal an array of zeros" do
        expect(obj == [0, 0, 0]).to be_truthy
      end
    end

    context "given out of bounds arguments" do
      obj = SFML::Color.new(300, -100, 200)
      it "should clamp the values" do
        expect(obj.r).to be(255)
        expect(obj.g).to be(0)
        expect(obj.b).to be(200)
      end
    end
  end

  describe "in math" do
    context "between two color objects" do
      before(:each) do
        @color1 = SFML::Color.new(100, 200, 50)
        @color2 = SFML::Color.new(200, 25, 25)
      end

      it "addition will produce expected result" do
        expect(@color1 + @color2).to eq([255, 225, 75])
      end

      it "subtraction will produce expected result" do
        expect(@color1 - @color2).to eq([0, 175, 25, 0])
      end

      it "multiplication will produce expected result" do
        expect(@color1 * @color2).to eq([78, 19, 4])
      end
    end
  end
end