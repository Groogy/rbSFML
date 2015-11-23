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

#ifndef RBSFML_RBJOYSTICK_HPP
#define RBSFML_RBJOYSTICK_HPP

#include <SFML/Window/Joystick.hpp>
#include "class.hpp"
#include "object.hpp"

class rbJoystick;
class rbJoystickIdentification;

typedef rb::Module<sf::Joystick> rbJoystickModule;
typedef rb::Class<rbJoystickIdentification> rbJoystickIdentificationClass;

class rbJoystick
{
public:
	static void defineModule(const rb::Value& sfml);

private:
	friend class rbJoystickIdentification;

	static rbJoystickModule ourDefinition;
};


class rbJoystickIdentification
{
public:
	static void defineClass(const rb::Value& sfml);
	static const rbJoystickIdentificationClass& getDefinition();

	static void initialize(rb::Value self);
	static rb::Value initializeCopy(rb::Value self, const rb::Value& value);
	static std::vector<rb::Value> marshalDump(const rb::Value& self);
	static rb::Value marshalLoad(rb::Value self, const rb::Value& data);

private:
	friend class rbJoystick;

	static rbJoystickIdentificationClass ourDefinition;
};

namespace rb
{
	template<>
	sf::Joystick::Axis Value::to() const;

	template<>
	Value Value::create( sf::Joystick::Axis value );

	template<>
	sf::Joystick::Identification Value::to() const;

	template<>
	Value Value::create( const sf::Joystick::Identification value );	
}

#endif // RBSFML_RBJOYSTICK_HPP