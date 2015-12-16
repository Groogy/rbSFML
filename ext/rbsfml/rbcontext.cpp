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

#include "rbcontext.hpp"
#include "rbcontextsettings.hpp"
#include "rbnoncopyable.hpp"
#include "error.hpp"
#include "macros.hpp"

rbContextClass rbContext::ourDefinition;

void rbContext::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbContextClass::defineClassUnder("Context", sfml);
	ourDefinition.includeModule(rb::Value(rbNonCopyable::getDefinition()));
	ourDefinition.defineMethod<0>("initialize", &rbContext::initialize);
	ourDefinition.defineMethod<1>("set_active", &rbContext::setActive);
}

rbContext::rbContext()
: rb::Object()
, myObject(nullptr)
{
}

rbContext::~rbContext()
{
	delete myObject;
}

void rbContext::initialize(rbContextSettings* settings, unsigned int width, unsigned int height)
{
	myObject = new sf::Context(settings->myObject, width, height);
}

bool rbContext::setActive(bool flag)
{
	return myObject->setActive(flag);
}

namespace rb
{

template<>
rbContext* Value::to() const
{
	errorHandling(T_DATA);
	rbContext* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbContext, object);
	return object;
}

template<>
const rbContext* Value::to() const
{
	errorHandling(T_DATA);
	const rbContext* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbContext, object);
	return object;
}

}