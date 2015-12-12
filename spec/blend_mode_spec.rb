require './lib/rbsfml.so'

describe SFML::BlendMode do

  describe "in creation" do
    context "given three arguments" do
      before(:each) do
        @mode = SFML::BlendMode.new(SFML::BlendMode::Zero, SFML::BlendMode::One, SFML::BlendMode::Subtract)
      end

      it "should set the properties accordingly" do
        expect(@mode.color_src_factor).to eql(SFML::BlendMode::Zero)
        expect(@mode.color_dst_factor).to eql(SFML::BlendMode::One)
        expect(@mode.color_equation).to eql(SFML::BlendMode::Subtract)
      end

      it "should set the alpha properties to the same" do
        expect(@mode.alpha_src_factor).to eql(@mode.color_src_factor)
        expect(@mode.alpha_dst_factor).to eql(@mode.color_dst_factor)
        expect(@mode.alpha_equation).to eql(@mode.color_equation)
      end
    end

    context "given six arguments" do
      before(:each) do
        @mode = SFML::BlendMode.new(
            SFML::BlendMode::Zero, SFML::BlendMode::One, SFML::BlendMode::Subtract,
            SFML::BlendMode::SrcColor, SFML::BlendMode::DstAlpha, SFML::BlendMode::Add
        )
      end

      it "should set the properties accordingly" do
        expect(@mode.color_src_factor).to eql(SFML::BlendMode::Zero)
        expect(@mode.color_dst_factor).to eql(SFML::BlendMode::One)
        expect(@mode.color_equation).to eql(SFML::BlendMode::Subtract)
        expect(@mode.alpha_src_factor).to eql(SFML::BlendMode::SrcColor)
        expect(@mode.alpha_dst_factor).to eql(SFML::BlendMode::DstAlpha)
        expect(@mode.alpha_equation).to eql(SFML::BlendMode::Add)
      end
    end
  end
end