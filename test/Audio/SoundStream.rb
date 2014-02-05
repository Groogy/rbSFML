require 'minitest/autorun'
require 'sfml/audio'
include SFML

describe SoundStream do
  it "cannot be manually instantiated" do
    proc { SoundStream.new }.must_raise RuntimeError
  end

  describe "when subclassed" do
    before do
      class MySoundStream < SoundStream
      end
    end

    it "cannot be manually instantiated" do
      proc { MySoundStream.new }.must_raise RuntimeError
    end

    it "cannot be manually instantiated if allocate is redefined" do
      def MySoundStream.allocate
        raise TypeError
      end
      proc { MySoundStream.new }.must_raise RuntimeError
    end

    it "cannot be manually instantiated if allocate is undefined in the singleton class" do
      class << MySoundStream
        undef allocate
      end
      proc { MySoundStream.new }.must_raise RuntimeError
    end
  end
end
