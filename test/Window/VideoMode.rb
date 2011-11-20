
class TestVideoMode < Test::Unit::TestCase
  include SFML
  
  def test_initialization1
    video_mode = VideoMode.new(800, 600)
    assert_equal(800, video_mode.width)
    assert_equal(600, video_mode.height)
    assert_equal(32, video_mode.bpp)
    assert(video_mode == VideoMode.new(800, 600, 32))
    assert(video_mode.eql? VideoMode.new(800, 600))
    assert_equal(video_mode, VideoMode.new([800, 600]))
  end
  
  def test_initialization2
    video_mode = VideoMode.new(640, 480, 8)
    assert_equal(640, video_mode.width)
    assert_equal(480, video_mode.height)
    assert_equal(8, video_mode.bpp)
    assert(video_mode == VideoMode.new(640, 480, 8))
    assert(video_mode.eql? VideoMode.new(640, 480, 8))
    assert_equal(video_mode, VideoMode.new([640, 480, 8]))
  end
  
  def test_initialization3
    video_mode = VideoMode.new
    assert_equal(0, video_mode.width)
    assert_equal(0, video_mode.height)
    assert_equal(0, video_mode.bpp)
    assert(video_mode == VideoMode.new(0, 0, 0))
    assert_equal(video_mode, VideoMode.new([]))
    refute(video_mode.valid?)
    
    video_mode.width = 544
    video_mode.height = 416
    video_mode.bpp = 24
    assert_equal(544, video_mode.width)
    assert_equal(416, video_mode.height)
    assert_equal(24, video_mode.bpp)
  end
  
  def test_classmethods
    desktop_mode = VideoMode.desktop_mode
    assert_instance_of(VideoMode, desktop_mode)
    
    fullscreen_modes = VideoMode.fullscreen_modes
    assert_instance_of(Array, fullscreen_modes)
    
    fullscreen_modes.each do |mode|
      assert_instance_of(VideoMode, mode)
      assert(mode.valid?)
    end
  end
  
  def test_comparations
    video_mode1 = VideoMode.new(800, 600)
    video_mode2 = VideoMode.new(640, 480, 8)
    video_mode3 = VideoMode.new(640, 480, 32)
    video_mode4 = VideoMode.new(800, 600)
    assert(video_mode1 > video_mode2)
    assert(video_mode1 > video_mode3)
    assert(video_mode1 >= video_mode4)
    assert(video_mode1 <= video_mode4)
    assert(video_mode1 == video_mode4)
    refute(video_mode1 < video_mode2)
    refute(video_mode1 < video_mode3)
    assert(video_mode2 < video_mode3)
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
    assert_raise(ArgumentError) { VideoMode.new(0, 0, 0, 0) }
  end
  
end
