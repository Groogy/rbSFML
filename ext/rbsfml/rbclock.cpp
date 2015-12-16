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

#include "rbclock.hpp"
#include "error.hpp"
#include "macros.hpp"
#include "rbtime.hpp"

rbClockClass rbClock::ourDefinition;

void rbClock::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbClockClass::defineClassUnder("Clock", sfml);
	ourDefinition.defineMethod<0>("initialize_copy", &rbClock::initializeCopy);
	ourDefinition.defineMethod<1>("elapsed_time", &rbClock::getElapsedTime);
	ourDefinition.defineMethod<2>("restart", &rbClock::restart);
	ourDefinition.defineMethod<3>("marshal_dump", &rbClock::marshalDump);
	ourDefinition.defineMethod<4>("inspect", &rbClock::inspect);

	ourDefinition.aliasMethod("inspect", "to_s");
}

rbClock::rbClock()
: rb::Object()
, myObject()
{
}

rbClock::~rbClock()
{
}

rbClock* rbClock::initializeCopy(const rbClock* value)
{
	myObject = value->myObject;
	return this;
}

rbTime* rbClock::getElapsedTime() const
{
	sf::Time time = myObject.getElapsedTime();
	rbTime* timeObject = rbTime::ourDefinition.newObject().to<rbTime*>();
	timeObject->myObject = time;
	return timeObject;
}

rbTime* rbClock::restart()
{
	sf::Time time = myObject.restart();
	rbTime* timeObject = rbTime::ourDefinition.newObject().to<rbTime*>();
	timeObject->myObject = time;
	return timeObject;
}

rb::Value rbClock::marshalDump() const
{
	rb::raise(rb::TypeError, "can't dump %s", ourDefinition.getName().c_str() );
	return rb::Nil;
}

std::string rbClock::inspect() const
{
	sf::Time time = myObject.getElapsedTime();
	return ourDefinition.getName() + "(" + macro::toString(time.asSeconds()) + ")";
}

namespace rb
{

template<>
rbClock* Value::to() const
{
	errorHandling(T_DATA);
	rbClock* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbClock, object);
	return object;
}

template<>
const rbClock* Value::to() const
{
	errorHandling(T_DATA);
	const rbClock* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbClock, object);
	return object;
}

}