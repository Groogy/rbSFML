require './lib/rbsfml.so'

describe SFML::ContextSettings do
  describe "in creation" do
    context "with no arguments" do
      mode = SFML::ContextSettings.new

      it "should give a context with default values" do
        expect(mode.depth_bits).to eql(0)
        expect(mode.stencil_bits).to eql(0)
        expect(mode.antialiasing_level).to eql(0)
        expect(mode.major_version).to eql(1)
        expect(mode.minor_version).to eql(1)
        expect(mode.attribute_flags).to eql(SFML::ContextSettings::Default)
      end
    end

    context "with two arguments" do
    end
  end

  describe "in basic instance usage" do
  end
end