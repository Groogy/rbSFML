require './lib/sfml/rbsfml.so'

describe SFML::Window do
  describe "in creation" do
    context "with no arguments" do
      before(:each) do
        @window = SFML::Window.new
      end

      it "should not open the window" do
        expect(@window.open?).to be_falsy
      end

      it "should open window if calling create" do
        @window.create(SFML::VideoMode.new(800, 600), "Hello World!")
        expect(@window.open?).to be_truthy
      end
    end

    context "with arguments" do
      before(:all) do
        @window = SFML::Window.new(SFML::VideoMode.new(800, 600), "Hello World!")
      end

      it "should open the window" do
        expect(@window.open?).to be_truthy
      end
    end
  end

  describe "in usage" do
    before(:each) do
      @window = SFML::Window.new(SFML::VideoMode.new(800, 600), "Hello World!")
    end

    context "when closing the window" do
      it "should be closed" do
        @window.close
        expect(@window.open?).to be_falsy
      end
    end

    context "when retrieving the settings" do
      it "should return a frozen object" do
        settings = @window.settings
        expect(settings.frozen?).to be_truthy
      end
    end

    context "when setting the position" do
      pos = SFML::Vector2.new(150, 88)
      before(:each) do
        @window.position = pos
      end

      it "should have that new position" do
        expect(@window.position).to eql(pos)
      end
    end

    context "when setting the size" do
      size = SFML::Vector2.new(300, 300)
      before(:each) do
        @window.size = size
      end

      it "should have that new size" do
        expect(@window.size).to eql(size)
      end
    end
  end
end