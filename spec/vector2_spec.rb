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
  end
end