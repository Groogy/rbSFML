#include <ruby.h>
#include "module.hpp"
#include <iostream>

class rbSFML
{
public:
	static void blah()
	{
		std::cout << "EEEY!" << std::endl;
	}

	static std::string say(const std::string& arg)
	{
		std::cout << arg << std::endl;
		return "Leol!";
	}
};

extern "C" void Init_rbsfml() {
	rb::Module<rbSFML> sfml("SFML");
	sfml.defineFunction<0>("blah", &rbSFML::blah);
	sfml.defineFunction<1>("say", &rbSFML::say);
}