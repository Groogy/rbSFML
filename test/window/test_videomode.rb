
class TestVideoMode < Test::Unit::TestCase
  include SFML
  
  def test_initialization1
    video_mode = VideoMode.new(800, 600)
    assert(video_mode == VideoMode.new(800, 600))
    assert(video_mode.eql? VideoMode.new(800, 600))
  end
  
  def test_initialization2
    video_mode = VideoMode.new(640, 480, 8)
    assert(video_mode == VideoMode.new(640, 480, 8))
    assert(video_mode.eql? VideoMode.new(640, 480, 8))
  end
  
  def test_initialization3
    video_mode = VideoMode.new
    assert(video_mode == VideoMode.new(0, 0, 0))
  end
  
  def test_classmethods
    desktop_mode = VideoMode.desktop_mode
    assert_instance_of(VideoMode, desktop_mode)
    
    fullscreen_modes = VideoMode.fullscreen_modes
    assert_instance_of(Array, fullscreen_modes)
    
    fullscreen_modes.each do |fullscreen_mode|
      #assert_instance_of(VideoMode, fullscreen_mode)
    end
  end
  
  def test_inspect
    video_mode1 = VideoMode.new(800, 600)
    video_mode2 = VideoMode.new(640, 480, 8)
    assert_equal("VideoMode(800x600, 32bits)", video_mode1.inspect)
    assert_equal("VideoMode(640x480, 8bits)", video_mode2.inspect)
    assert_equal(" VideoMode(800x600, 32bits) ", " #{video_mode1} ")
    assert_equal(" VideoMode(640x480, 8bits) ", " #{video_mode2} ")
  end
  
  def test_exceptions
    assert_raise(TypeError)     { VideoMode.new(1000) }
    assert_raise(TypeError)     { VideoMode.new("aaa", "bbb") }
  end
  
end
