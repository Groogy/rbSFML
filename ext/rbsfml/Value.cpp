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
#include "Value.hpp"
#include <array>

namespace
{
	std::array<const char*, T_MASK> RubyTypeNames = {
		"T_NONE", "T_OBJECT", "T_CLASS", "T_MODULE",
		"T_FLOAT", "T_STRING", "T_REGEXP", "T_ARRAY", 
		"T_HASH", "T_STRUCT", "T_BIGNUM", "T_FILE", 
		"T_DATA", "T_MATCH", "T_COMPLEX", "T_RATIONAL",
		"",
		"T_NIL", "T_TRUE", "T_FALSE", "T_SYMBOL",
		"T_FIXNUM", "", "", "", "", ""
		"T_UNDEF", "T_NODE", "T_ICLASS", "T_ZOMBIE",
	};
}

namespace rb
{

Value::Value()
: myValue(Qnil)
, myCachedStr()
{
}

Value::Value(VALUE value)
: myValue(value)
, myCachedStr()
{
}

Value::Value(const std::string& value)
: myValue(rb_str_new2(value.c_str()))
, myCachedStr()
{
}

Value::~Value()
{
}

void Value::errorHandling(int rubyType) const
{
	if(TYPE(myValue) != rubyType)
		rb_raise(rb_eTypeError, "tried converting '%s' to '%s'", RubyTypeNames[TYPE(myValue)], RubyTypeNames[rubyType]);
}

template<>
VALUE Value::to() const
{
	return myValue;
}

template<>
std::string Value::to() const
{
	return to<const std::string&>();
}

template<>
const std::string& Value::to() const
{
	errorHandling(T_STRING);
	myCachedStr.assign(RSTRING_PTR(myValue), RSTRING_LEN(myValue));
	return myCachedStr;
}

}