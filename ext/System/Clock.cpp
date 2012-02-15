#include "Clock.hpp"

static rb::DataClass< rbSFML::Clock > localClockClass;

rb::Class rbSFML::Clock::GetClass()
{
	return localClockClass;
}

void rbSFML::Clock::Init( rb::Module SFML )
{	
	localClockClass = rb::DataClass< rbSFML::Clock >::Define( SFML, "Clock" );
	
	localClockClass.def< &rbSFML::Clock::InitializeCopy >( "initialize_copy" );
	
	localClockClass.def< &rbSFML::Clock::GetElapsedTime >( "get_elapsed_time" );
	localClockClass.def< &rbSFML::Clock::Restart >( "restart" );
	
	localClockClass.def< &rbSFML::Clock::MarshalDump >( "marshal_dump" );
	localClockClass.def< &rbSFML::Clock::Inspect >( "inspect" );
	localClockClass.def< &rbSFML::Clock::GetMemoryUsage >( "memory_usage" );
	
	localClockClass.alias( "elapsed_time", "get_elapsed_time" );
	localClockClass.alias( "to_s", "inspect" );
}

rbSFML::Clock::Clock()
{
}

rbSFML::Clock::~Clock()
{
}

rb::Object rbSFML::Clock::InitializeCopy( rb::Object aSource )
{
	myClock = aSource.data< rbSFML::Clock >().myClock;
	return *this;
}

rb::Object rbSFML::Clock::GetElapsedTime()
{
	rb::Object time = rbSFML::Time::GetClass().New();
	time.data< rbSFML::Time >().myTime = myClock.GetElapsedTime();
	return time;
}

rb::Object rbSFML::Clock::Restart()
{
	rb::Object time = rbSFML::Time::GetClass().New();
	time.data< rbSFML::Time >().myTime = myClock.Restart();
	return time;
}

rb::Object rbSFML::Clock::MarshalDump()
{
	rb_raise( rb::eTypeError, "can't dump %s", rb_class2name( localClockClass ) );
	return rb::Nil;
}

rb::Object rbSFML::Clock::Inspect()
{
	return rb_sprintf( "%s(%fs)", rb_class2name( localClockClass ), myClock.GetElapsedTime().AsSeconds() );
}

rb::Object rbSFML::Clock::GetMemoryUsage()
{
	return sizeof( rbSFML::Clock );
}
