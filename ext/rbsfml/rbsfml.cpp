#include <ruby.h>
#include "module.hpp"
#include <iostream>

class rbSFML
{
public:
	static VALUE Blah(VALUE self)
	{
		std::cout << "EEEY!" << std::endl;
		return Qnil;
	}
};

extern "C" void Init_rbsfml() {
	rb::Module<rbSFML> sfml("SFML");
	sfml.defineFunction("blah", &rbSFML::Blah);
}