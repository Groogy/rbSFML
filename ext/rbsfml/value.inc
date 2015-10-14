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

namespace rb
{

template<typename Base, int MaxFunctions>
Value::Value(const Module<Base, MaxFunctions>& module)
: myValue(module.myDefinition)
, myCachedStr()
{
}

template<const char* Name, typename ReturnType, typename ...Args>
ReturnType Value::call(Args... args)
{
	static ID sym = rb_intern(Name);
	VALUE returnValue = rb_funcall(myValue, sym, sizeof...(args), (Value(args).to<VALUE>())...);
	return Value(returnValue).to<ReturnType>();
}

template<const char* Name, typename ValueType>
void Value::setVar(ValueType value)
{
	static ID sym = rb_intern(Name);
	rb_ivar_set(myValue, sym, Value(value).to<VALUE>());
}

template<const char* Name, typename ValueType>
ValueType Value::getVar() const
{
	static ID sym = rb_intern(Name);
	VALUE value = rb_ivar_get(myValue, sym);
	return Value(value).to<ValueType>();
}

}