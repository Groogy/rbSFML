require 'minitest/autorun'
require 'sfml/audio'
include SFML

describe SoundBuffer do
  before do
    @sound_buffer = SoundBuffer.new
  end

  it "will have new instances that are distinct but equal" do
    sound_buffer = SoundBuffer.new
    @sound_buffer.wont_be_same_as sound_buffer
    @sound_buffer.must_equal sound_buffer
  end

  describe "when loading audio" do
    before do
      @sound_buffer.load('test/canary.wav')
      @other_buffer = SoundBuffer.new
    end

    it "will not be equal to a new instance" do
      @sound_buffer.wont_equal @other_buffer
    end

    it "will load identically by file name and file stream" do
      file = File.open('test/canary.wav', 'rb')
      @other_buffer.load_stream file
      file.close
      @sound_buffer.must_equal @other_buffer
    end

    it "will load identically by file name and samples" do
      @other_buffer.load_samples(@sound_buffer.samples, @sound_buffer.channel_count, @sound_buffer.sample_rate)
      @sound_buffer.must_equal @other_buffer
    end

    it "will load identically by file name and raw bytes" do
      file = File.open("test/canary.wav", "rb")
      @other_buffer.load_memory(file.read)
      file.close
      @sound_buffer.must_equal @other_buffer
    end

    it "will be marshallable" do
      @sound_buffer.must_equal Marshal.load(Marshal.dump(@sound_buffer))
    end

    it "will be identical after saving and loading" do
      @sound_buffer.save('test/temp.wav')
      @other_buffer.load('test/temp.wav')
      @sound_buffer.must_equal @other_buffer
      File.delete('test/temp.wav')
    end

    it "will have useful string representations" do
     @sound_buffer.inspect.must_match /^SFML::SoundBuffer\([0-9a-fx]+: [0-9]+ms\)$/
     @sound_buffer.to_s.must_match /^SFML::SoundBuffer\([0-9a-fx]+: [0-9]+ms\)$/
    end
  end

  describe "when subclassed" do
    before do
      class MySoundBuffer < SoundBuffer
      end

      @other_buffer = MySoundBuffer.new
    end

    it "will be comparable to regular instances" do
      @other_buffer = MySoundBuffer.new
      @sound_buffer.must_equal @other_buffer
    end

    it "will duplicate correctly" do
      @other_buffer.class.must_be_same_as @other_buffer.dup.class
    end
  end
end
