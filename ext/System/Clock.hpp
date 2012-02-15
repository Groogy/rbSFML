#ifndef RBSFML_SYSTEM_CLOCK_HEADER_
#define RBSFML_SYSTEM_CLOCK_HEADER_

#include <SFML/System/Clock.hpp>

namespace rbSFML
{
	class Clock : public rb::Object
	{
	public:
		static rb::Class GetClass();
		
#ifdef RBSFML_SYSTEM
		static void Init( rb::Module SFML );
#endif // RBSFML_SYSTEM
		Clock();
		~Clock();
		
		rb::Object InitializeCopy( rb::Object aSource );
		
		rb::Object GetElapsedTime();
		rb::Object Restart();
		
		rb::Object MarshalDump();
		rb::Object Inspect();
		rb::Object GetMemoryUsage();
		
		sf::Clock myClock;
	};
}

#endif // RBSFML_SYSTEM_CLOCK_HEADER_