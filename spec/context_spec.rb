require './lib/rbsfml.so'

describe SFML::Context do
  describe "in creation" do
    context "with simple arguments" do
      it "should give a context that can be set active" do
        context = SFML::Context.new(SFML::ContextSettings.new, 800, 600)
        expect(context.set_active(true)).to be_truthy
      end
    end
  end
end