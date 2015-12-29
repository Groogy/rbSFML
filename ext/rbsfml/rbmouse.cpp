/* rbSFML
 * Copyright (c) 2015 Henrik Valter Vogelius Hansson - groogy@groogy.se
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "rbmouse.hpp"
#include "rbvector2.hpp"
#include "error.hpp"
#include "macros.hpp"

rbMouseModule rbMouse::ourDefinition;

void rbMouse::defineModule(const rb::Value& sfml)
{
	ourDefinition = rbMouseModule::defineModuleUnder("Mouse", sfml);
	ourDefinition.defineFunction<0>("button_pressed?", &sf::Mouse::isButtonPressed);
	ourDefinition.defineFunction<1>("get_position", &rbMouse::getPosition);
	ourDefinition.defineFunction<2>("set_position", &rbMouse::setPosition);

	ourDefinition.defineConstant("Left", rb::Value(sf::Mouse::Left));
	ourDefinition.defineConstant("Right", rb::Value(sf::Mouse::Right));
	ourDefinition.defineConstant("Middle", rb::Value(sf::Mouse::Middle));
	ourDefinition.defineConstant("XButton1", rb::Value(sf::Mouse::XButton1));
	ourDefinition.defineConstant("XButton2", rb::Value(sf::Mouse::XButton2));
	ourDefinition.defineConstant("ButtonCount", rb::Value(sf::Mouse::ButtonCount));
	ourDefinition.defineConstant("VerticalWheel", rb::Value(sf::Mouse::VerticalWheel));
	ourDefinition.defineConstant("HorizontalWheel", rb::Value(sf::Mouse::HorizontalWheel));
}

rb::Value rbMouse::getPosition(const std::vector<rb::Value>& arguments)
{
	sf::Vector2i result;
	switch(arguments.size())
	{
	case 0:
		result = sf::Mouse::getPosition();
		break;
	case 1:
		result = sf::Mouse::getPosition(arguments[0].to<const sf::Window&>());
		break;
	default:
		rb::expectedNumArgs(arguments.size(), 0, 1);
	}
	return rb::Value::create(result);
}

rb::Value rbMouse::setPosition(const std::vector<rb::Value>& arguments)
{
	switch(arguments.size())
	{
	case 1:
		sf::Mouse::setPosition(arguments[0].to<sf::Vector2i>());
		break;
	case 2:
		sf::Mouse::setPosition(arguments[0].to<sf::Vector2i>(), arguments[1].to<const sf::Window&>());
		break;
	default:
		rb::expectedNumArgs(arguments.size(), 1, 2);
	}
	return rb::Nil;
}

namespace rb
{

template<>
sf::Mouse::Button Value::to() const
{
	unsigned int value = to<unsigned int>();
	return static_cast<sf::Mouse::Button>(value);
}

template<>
Value Value::create(sf::Mouse::Button value)
{
	return create(static_cast<unsigned int>(value));
}

template<>
sf::Mouse::Wheel Value::to() const
{
	unsigned int value = to<unsigned int>();
	return static_cast<sf::Mouse::Wheel>(value);
}

template<>
Value Value::create(sf::Mouse::Wheel value)
{
	return create(static_cast<unsigned int>(value));
}

}