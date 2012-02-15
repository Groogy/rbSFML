#include "Time.hpp"

static rb::DataClass< rbSFML::Time > localTimeClass;

rb::Class rbSFML::Time::GetClass()
{
	return localTimeClass;
}

void rbSFML::Time::Init( rb::Module SFML )
{	
	localTimeClass = rb::DataClass< rbSFML::Time >::Define( SFML, "Time" );
	localTimeClass.include( rb::mComparable );
	
	localTimeClass.def< &rbSFML::Time::InitializeCopy >( "initialize_copy" );
	
	localTimeClass.def< &rbSFML::Time::AsSeconds >( "as_seconds" );
	localTimeClass.def< &rbSFML::Time::AsMilliseconds >( "as_milliseconds" );
	localTimeClass.def< &rbSFML::Time::AsMicroseconds >( "as_microseconds" );
	
	localTimeClass.def< &rbSFML::Time::MarshalDump >( "marshal_dump" );
	localTimeClass.def< &rbSFML::Time::Inspect >( "inspect" );
	localTimeClass.def< &rbSFML::Time::GetMemoryUsage >( "memory_usage" );
	
	localTimeClass.def< &rbSFML::Time::NegateOperator >( "-@" );
	localTimeClass.def< &rbSFML::Time::AdditionOperator >( "+" );
	localTimeClass.def< &rbSFML::Time::SubtractOperator >( "-" );
	localTimeClass.def< &rbSFML::Time::MultiplyOperator >( "*" );
	localTimeClass.def< &rbSFML::Time::DivisionOperator >( "/" );
	localTimeClass.def< &rbSFML::Time::CompareOperator >( "<=>" );
	
	localTimeClass.alias( "to_s", "inspect" );
}

rbSFML::Time::Time()
{
}

rbSFML::Time::~Time()
{
}

rb::Object rbSFML::Time::InitializeCopy( rb::Object aSource )
{
	myTime = aSource.data< rbSFML::Time >().myTime;
	return *this;
}

rb::Object rbSFML::Time::AsSeconds()
{
	return rb::ruby_cast< rb::Object >( myTime.AsSeconds() );
}

rb::Object rbSFML::Time::AsMilliseconds()
{
	return rb::ruby_cast< rb::Object >( myTime.AsMilliseconds() );
}

rb::Object rbSFML::Time::AsMicroseconds()
{
	return rb::ruby_cast< rb::Object >( myTime.AsMicroseconds() );
}

rb::Object rbSFML::Time::MarshalDump()
{
	rb_raise( rb::eTypeError, "can't dump %s", rb_class2name( localTimeClass ) );
	return rb::Nil;
}

rb::Object rbSFML::Time::Inspect()
{
	return rb_sprintf( "%s(%fs)", rb_class2name( localTimeClass ), myTime.AsSeconds() );
}

rb::Object rbSFML::Time::GetMemoryUsage()
{
	return sizeof( rbSFML::Time );
}

rb::Object rbSFML::Time::NegateOperator()
{
	rb::Object newTime = localTimeClass.New();
	newTime.data< rbSFML::Time >().myTime = -myTime;
	return newTime;
}

rb::Object rbSFML::Time::AdditionOperator( rb::Object aRightOperand )
{
	if( aRightOperand.is_instance_of( localTimeClass ) == rb::False )
	{
		INVALID_EXPECTED_TYPE( localTimeClass );
	}
	
	rb::Object newTime = localTimeClass.New();
	newTime.data< rbSFML::Time >().myTime = aRightOperand.data< rbSFML::Time >().myTime + myTime;
	return newTime;
}

rb::Object rbSFML::Time::SubtractOperator( rb::Object aRightOperand )
{
	if( aRightOperand.is_instance_of( localTimeClass ) == rb::False )
	{
		INVALID_EXPECTED_TYPE( localTimeClass );
	}
	
	rb::Object newTime = localTimeClass.New();
	newTime.data< rbSFML::Time >().myTime = aRightOperand.data< rbSFML::Time >().myTime - myTime;
	return newTime;
}

rb::Object rbSFML::Time::MultiplyOperator( rb::Object aRightOperand )
{
	rb::Object newTime = localTimeClass.New();
	if( aRightOperand.is_instance_of( rb::cFixnum ) == rb::True )
	{
		newTime.data< rbSFML::Time >().myTime = myTime * rb::ruby_cast< sf::Int64 >( aRightOperand );
	}
	else if( aRightOperand.is_instance_of( rb::cFloat ) == rb::True )
	{
		newTime.data< rbSFML::Time >().myTime = myTime * rb::ruby_cast< float >( aRightOperand );
	}
	else
	{
		INVALID_EXPECTED_TYPES( rb::cFixnum, rb::cFloat );
	}
	
	return newTime;
}

rb::Object rbSFML::Time::DivisionOperator( rb::Object aRightOperand )
{
	rb::Object newTime = localTimeClass.New();
	if( aRightOperand.is_instance_of( rb::cFixnum ) == rb::True )
	{
		newTime.data< rbSFML::Time >().myTime = myTime / rb::ruby_cast< sf::Int64 >( aRightOperand );
	}
	else if( aRightOperand.is_instance_of( rb::cFloat ) == rb::True )
	{
		newTime.data< rbSFML::Time >().myTime = myTime / rb::ruby_cast< float >( aRightOperand );
	}
	else
	{
		INVALID_EXPECTED_TYPES( rb::cFixnum, rb::cFloat );
	}
	
	return newTime;
}

rb::Object rbSFML::Time::CompareOperator( rb::Object aRightOperand )
{
	sf::Time time = aRightOperand.data< rbSFML::Time >().myTime;
	if( myTime == time ) return 0;
	if( myTime > time ) return 1;
	return -1;
}