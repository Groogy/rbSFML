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
#include "error.hpp"
#include "macros.hpp"

rbTimeClass rbTime::ourDefinition;

void rbTime::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbTimeClass::defineClassUnder("Time", sfml);
	ourDefinition.includeModule(rb::Value(rb_mComparable));
	ourDefinition.defineMethod<0>("initialize_copy", &rbTime::initializeCopy);
	ourDefinition.defineMethod<1>("as_seconds", &rbTime::asSeconds);
	ourDefinition.defineMethod<2>("as_milliseconds", &rbTime::asMilliseconds);
	ourDefinition.defineMethod<3>("as_microseconds", &rbTime::asMicroseconds);
	ourDefinition.defineMethod<4>("marshal_dump", &rbTime::marshalDump);
	ourDefinition.defineMethod<5>("inspect", &rbTime::inspect);
	ourDefinition.defineMethod<6>("-@", &rbTime::negate);
	ourDefinition.defineMethod<7>("+", &rbTime::addition);
	ourDefinition.defineMethod<8>("-", &rbTime::subtract);
	ourDefinition.defineMethod<9>("*", &rbTime::multiply);
	ourDefinition.defineMethod<10>("/", &rbTime::divide);
	ourDefinition.defineMethod<11>("<=>", &rbTime::compare);

	ourDefinition.aliasMethod("inspect", "to_s");

	rb::Value zero = ourDefinition.newObject();
	zero.freeze();
	ourDefinition.defineConstant("Zero", zero);
}

rbTime* rbTime::seconds(float val)
{
	rbTime* object = ourDefinition.newObject().to<rbTime*>();
	object->myObject = sf::seconds(val);
	return object;
}

rbTime* rbTime::milliseconds(sf::Int32 val)
{
	rbTime* object = ourDefinition.newObject().to<rbTime*>();
	object->myObject = sf::milliseconds(val);
	return object;
}

rbTime* rbTime::microseconds(sf::Int64 val)
{
	rbTime* object = ourDefinition.newObject().to<rbTime*>();
	object->myObject = sf::microseconds(val);
	return object;
}

rbTime::rbTime()
: rb::Object()
, myObject()
{
}

rbTime::~rbTime()
{
}

rbTime* rbTime::initializeCopy(const rbTime* value)
{
	myObject = value->myObject;
	return this;
}

float rbTime::asSeconds() const
{
	return myObject.asSeconds();
}

sf::Int32 rbTime::asMilliseconds() const
{
	return myObject.asMilliseconds();
}

sf::Int64 rbTime::asMicroseconds() const
{
	return myObject.asMicroseconds();
}

rb::Value rbTime::marshalDump() const
{
	rb::raise(rb::TypeError, "can't dump %s", ourDefinition.getName().c_str() );
	return rb::Nil;
}

std::string rbTime::inspect() const
{
	return ourDefinition.getName() + "(" + macro::toString(myObject.asSeconds()) + ")";
}

rbTime* rbTime::negate() const
{
	rbTime* object = ourDefinition.newObject().to<rbTime*>();
	object->myObject = -myObject;
	return object;
}

rbTime* rbTime::addition(const rbTime* other) const
{
	rbTime* object = ourDefinition.newObject().to<rbTime*>();
	object->myObject = myObject + other->myObject;
	return object;
}

rbTime* rbTime::subtract(const rbTime* other) const
{
	rbTime* object = ourDefinition.newObject().to<rbTime*>();
	object->myObject = myObject - other->myObject;
	return object;
}

rbTime* rbTime::multiply(const rb::Value& other) const
{
	rbTime* object = ourDefinition.newObject().to<rbTime*>();
	if(other.getType() == rb::ValueType::Fixnum)
		object->myObject = myObject * other.to<sf::Int64>();
	else if(other.getType() == rb::ValueType::Float)
		object->myObject = myObject * other.to<float>();
	else
		rb::expectedTypes("Fixnum", "Float");
	return object;
}

rb::Value rbTime::divide(const rb::Value& other) const
{
	rb::Value returnValue;
	if(other.getType() == rb::ValueType::Data)
	{
		rbTime* object = other.to<rbTime*>();
		returnValue = rb::Value(myObject / object->myObject);
	}
	else
	{
		rbTime* object = ourDefinition.newObject().to<rbTime*>();
		if(other.getType() == rb::ValueType::Fixnum)
			object->myObject = myObject / other.to<sf::Int64>();
		else if(other.getType() == rb::ValueType::Float)
			object->myObject = myObject / other.to<float>();

		returnValue = rb::Value(object);
	}

	if(returnValue.isNil())
		rb::expectedTypes("Fixnum", "Float", "Time");
	return rb::Nil;
}

int rbTime::compare(const rbTime* other) const
{
	sf::Int64 time1 = myObject.asMicroseconds();
	sf::Int64 time2 = other->myObject.asMicroseconds();

	if(time1 == time2) return 0;
	if(time1 > time2) return 1;
	return -1;
}

namespace rb
{

template<>
rbTime* Value::to() const
{
	errorHandling(T_DATA);
	rbTime* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbTime, object);
	return object;
}

template<>
const rbTime* Value::to() const
{
	errorHandling(T_DATA);
	const rbTime* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbTime, object);
	return object;
}

}