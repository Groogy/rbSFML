require './lib/sfml/rbsfml.so'

describe SFML::VideoMode do
  describe "in creation" do
    context "with no arguments" do
      mode = SFML::VideoMode.new

      it "should give an invalid video mode" do
        expect(mode.valid?).to be_falsy
      end
    end

    context "with two arguments" do
      mode = SFML::VideoMode.new(800, 600)
      it "should give a valid video mode" do
        expect(mode.valid?).to be_truthy
      end

      it "should return correct width" do
        expect(mode.width).to eql(800)
      end

      it "should return correct height" do
        expect(mode.height).to eql(600)
      end

      it "should return default bits per pixel" do
        expect(mode.bpp).to eql(32)
      end
    end

    context "with invalid bits per pixel" do
      mode = SFML::VideoMode.new(800, 600, 88)
      it "should give an invalid video mode" do
        expect(mode.valid?).to be_falsy
      end
    end
  end

  describe "in basic instance usage" do
    before(:each) do
      @mode = SFML::VideoMode.new
    end

    it "should allow you to modify the width" do
      @mode.width = 1024
      expect(@mode.width).to eql(1024)
    end

    it "should allow you to modify the height" do
      @mode.height = 900
      expect(@mode.height).to eql(900)
    end
  end

  describe "in fetching desktop resolution" do
    mode = SFML::VideoMode.desktop_mode

    it "should give a valid video mode" do
      expect(mode.valid?).to be_truthy
    end
  end

  describe "in fetching fullscreen resolutions" do
    modes = SFML::VideoMode.fullscreen_modes

    it "should give array with more than one mode" do
      expect(modes.size).to be > 1
    end

    it "should give only valid video modes" do
      modes.each do |mode|
        expect(mode.valid?).to be_truthy
      end
    end
  end
end