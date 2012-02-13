#ifndef RBSFML_SYSTEM_TIME_HEADER_
#define RBSFML_SYSTEM_TIME_HEADER_

#include <SFML/System/Time.hpp>

namespace rbSFML
{
	class Time : public rb::Object
	{
	public:
		static rb::Class GetClass();
		
#ifdef RBSFML_SYSTEM
		static void Init( rb::Module SFML );
#endif // RBSFML_SYSTEM
		Time();
		~Time();
		
	private:
		sf::Time myTime;
	};
}

#endif // RBSFML_SYSTEM_TIME_HEADER_