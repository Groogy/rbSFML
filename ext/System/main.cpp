#include "rbSFML.hpp"
#include "Time.hpp"
#include "Time.cpp"
#include "Clock.hpp"
#include "Clock.cpp"

extern "C"
void Init_system()
{
	rb::Module SFML = rb::Module::Define( "SFML" );
	
	rbSFML::Time::Init( SFML );
	rbSFML::Clock::Init( SFML );
}