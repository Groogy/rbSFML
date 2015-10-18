require './lib/rbsfml.so'

describe SFML::Vector2 do
  describe "in creation" do
    context "given no arguments" do
      obj = SFML::Vector2.new
      it "vector attributes should be zero" do
        expect(obj.x).to be(0)
        expect(obj.y).to be(0)
      end

      it "should be equal to the zero vector" do
        expect(obj == SFML::Vector2::Zero).to be_truthy
      end
    end

    context "given fixnum arguments" do
      obj = SFML::Vector2.new(3, 8)
      it "vector attributes should be equal to given values" do
        expect(obj.x).to eql(3)
        expect(obj.y).to eql(8)
      end

      it "vector attributes should be of fixnum type" do
        expect(obj.x).to be_kind_of(Fixnum)
        expect(obj.y).to be_kind_of(Fixnum)
      end
    end

    context "given fixnum arguments" do
      obj = SFML::Vector2.new(3.0, 8.0)
      it "vector attributes should be equal to given values" do
        expect(obj.x).to eql(3.0)
        expect(obj.y).to eql(8.0)
      end

      it "vector attributes should be of float type" do
        expect(obj.x).to be_kind_of(Float)
        expect(obj.y).to be_kind_of(Float)
      end
    end
  end
end