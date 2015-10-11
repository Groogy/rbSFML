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

#include "rbtime.hpp"

rb::Class<rbTime> rbTime::ourDefinition;

void rbTime::defineClass(const rb::Value& sfml)
{
	ourDefinition = rb::Class<rbTime>::defineClassUnder("Time", sfml);
	ourDefinition.defineMethod<0>("as_seconds", &rbTime::asSeconds);
	ourDefinition.defineMethod<1>("as_milliseconds", &rbTime::asMilliseconds);
	ourDefinition.defineMethod<2>("as_microseconds", &rbTime::asMicroseconds);
}

rb::Value rbTime::seconds(float val)
{
	rb::Value object = ourDefinition.newObject();
	rbTime* time = object.to<rbTime*>();
	time->myObject = sf::seconds(val);
	return object;
}

rbTime::rbTime()
: myObject()
{
}

rbTime::~rbTime()
{
}

float rbTime::asSeconds()
{
	return myObject.asSeconds();
}

sf::Int32 rbTime::asMilliseconds()
{
	return myObject.asMilliseconds();
}

sf::Int64 rbTime::asMicroseconds()
{
	return myObject.asMicroseconds();
}

namespace rb
{

template<>
rbTime* Value::to() const
{
	errorHandling(T_DATA);
	rbTime* object = nullptr;
	Data_Get_Struct(myValue, rbTime, object);
	return object;
}

}