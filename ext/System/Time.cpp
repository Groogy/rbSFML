#include "Time.hpp"

static rb::DataClass< rbSFML::Time > localClass;

rb::Class rbSFML::Time::GetClass()
{
	return localClass;
}

void rbSFML::Time::Init( rb::Module SFML )
{	
	localClass = rb::DataClass< rbSFML::Time >::Define( SFML, "Time" );
	
	localClass.def< &rbSFML::Time::AsSeconds >( "as_seconds" );
	localClass.def< &rbSFML::Time::AsMilliseconds >( "as_milliseconds" );
	localClass.def< &rbSFML::Time::AsMicroseconds >( "as_microseconds" );
	
	localClass.def< &rbSFML::Time::Inspect >( "inspect" );
	localClass.def< &rbSFML::Time::GetMemoryUsage >( "memory_usage" );
	
	localClass.def< &rbSFML::Time::NegateOperator >( "-@" );
	localClass.def< &rbSFML::Time::AdditionOperator >( "+" );
	localClass.def< &rbSFML::Time::SubtractOperator >( "-" );
	localClass.def< &rbSFML::Time::MultiplyOperator >( "*" );
	localClass.def< &rbSFML::Time::DivisionOperator >( "/" );
	
	localClass.alias( "to_s", "inspect" );
}

rbSFML::Time::Time()
{
}

rbSFML::Time::~Time()
{
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

rb::Object rbSFML::Time::Inspect()
{
	return rb_sprintf( "%s(%fs)", rb_class2name( localClass ), myTime.AsSeconds() );
}

rb::Object rbSFML::Time::GetMemoryUsage()
{
	return sizeof( rbSFML::Time );
}

rb::Object rbSFML::Time::NegateOperator()
{
	rb::Object newTime = localClass.New();
	newTime.data< rbSFML::Time >().myTime = -myTime;
	return newTime;
}

rb::Object rbSFML::Time::AdditionOperator( rb::Object aRightOperand )
{
	if( aRightOperand.is_instance_of( localClass ) == rb::False )
	{
		INVALID_EXPECTED_TYPE( localClass );
	}
	
	rb::Object newTime = localClass.New();
	newTime.data< rbSFML::Time >().myTime = aRightOperand.data< rbSFML::Time >().myTime + myTime;
	return newTime;
}

rb::Object rbSFML::Time::SubtractOperator( rb::Object aRightOperand )
{
	if( aRightOperand.is_instance_of( localClass ) == rb::False )
	{
		INVALID_EXPECTED_TYPE( localClass );
	}
	
	rb::Object newTime = localClass.New();
	newTime.data< rbSFML::Time >().myTime = aRightOperand.data< rbSFML::Time >().myTime - myTime;
	return newTime;
}

rb::Object rbSFML::Time::MultiplyOperator( rb::Object aRightOperand )
{
	rb::Object newTime = localClass.New();
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
	rb::Object newTime = localClass.New();
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