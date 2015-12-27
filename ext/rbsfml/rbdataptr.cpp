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

#include "rbdataptr.hpp"
#include "rbnoncopyable.hpp"
#include "error.hpp"
#include "macros.hpp"

rbDataPtrClass rbDataPtr::ourDefinition;

void rbDataPtr::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbDataPtrClass::defineClassUnder("DataPtr", sfml);
	ourDefinition.includeModule(rb::Value(rbNonCopyable::getDefinition()));
	ourDefinition.defineMethod<0>("inspect", &rbDataPtr::inspect);
    ourDefinition.defineMethod<1>("ptr", &rbDataPtr::getPtr);

	ourDefinition.aliasMethod("inspect", "to_s");
}

rbDataPtrClass& rbDataPtr::getDefinition()
{
    return ourDefinition;
}

rbDataPtr::rbDataPtr()
: rb::Object()
, myObject(0)
{
}

rbDataPtr::~rbDataPtr()
{
}

std::string rbDataPtr::inspect() const
{
    return ourDefinition.getName() + "(" + macro::toString( myObject ) + ")";
}

intptr_t rbDataPtr::getPtr() const
{
    return myObject;
}

void rbDataPtr::setPtr(intptr_t ptr)
{
    myObject = ptr;
}

namespace rb
{

template<>
rbDataPtr* Value::to() const
{
	errorHandling(T_DATA);
	rbDataPtr* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbDataPtr, object);
	return object;
}

template<>
const rbDataPtr* Value::to() const
{
	errorHandling(T_DATA);
	const rbDataPtr* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbDataPtr, object);
	return object;
}

}