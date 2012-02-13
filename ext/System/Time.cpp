#include "Time.hpp"

static rb::DataClass< rbSFML::Time > localClass;

rb::Class rbSFML::Time::GetClass()
{
	return localClass;
}

void rbSFML::Time::Init( rb::Module SFML )
{	
	localClass = rb::DataClass< rbSFML::Time >::Define( SFML, "Time" );
	
	localClass.def< &rbSFML::Time::AsSeconds >( "AsSeconds" );
	localClass.def< &rbSFML::Time::AsMilliseconds >( "AsMilliseconds" );
	localClass.def< &rbSFML::Time::AsMicroseconds >( "AsMicroseconds" );
	
	localClass.def< &rbSFML::Time::NegateOperator >( "-@" );
	localClass.def< &rbSFML::Time::AdditionOperator >( "+" );
	localClass.def< &rbSFML::Time::SubtractOperator >( "-" );
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