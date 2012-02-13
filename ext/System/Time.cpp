#include "Time.hpp"

rb::DataClass< rbSFML::Time > localClass;

rb::Class rbSFML::Time::GetClass()
{
	return localClass;
}

void rbSFML::Time::Init( rb::Module SFML )
{
	if( localClass != rb::Nil )
	{
		/* Handle */
	}
	
	localClass = rb::DataClass< rbSFML::Time >::Define( SFML, "Time" );
}

rbSFML::Time::Time()
{
}

rbSFML::Time::~Time()
{
}