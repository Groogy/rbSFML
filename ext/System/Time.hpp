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
		
		rb::Object AsSeconds();
		rb::Object AsMilliseconds();
		rb::Object AsMicroseconds();
		
		rb::Object NegateOperator();
		rb::Object AdditionOperator( rb::Object aRightOperand );
		rb::Object SubtractOperator( rb::Object aRightOperand );
		
	private:
		sf::Time myTime;
	};
}

#endif // RBSFML_SYSTEM_TIME_HEADER_