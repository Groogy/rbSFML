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
#include "value.hpp"
#include "object.hpp"
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

Value Nil(Qnil);
Value True(Qtrue);
Value False(Qfalse);

Value::Value()
: myValue(Qnil)
, myCachedStr()
, myCachedArray()
{
}

Value::Value(VALUE value)
: myValue(value)
, myCachedStr()
, myCachedArray()
{
}

Value::Value(const std::string& value)
: myValue(rb_str_new2(value.c_str()))
, myCachedStr()
, myCachedArray()
{
}

Value::Value(int value)
: myValue(INT2FIX(value))
, myCachedStr()
, myCachedArray()
{
}

Value::Value(float value)
: myValue(rb_float_new(value))
, myCachedStr()
, myCachedArray()
{
}

Value::Value(long long int value)
: myValue(LL2NUM(value))
, myCachedStr()
, myCachedArray()
{
}

Value::Value(unsigned int value)
: myValue(UINT2NUM(value))
, myCachedStr()
, myCachedArray()
{
}

Value::Value(bool value)
: myValue(value ? Qtrue : Qfalse)
, myCachedStr()
, myCachedArray()
{
}

Value::Value(rb::Object* object)
: myValue(object ? object->myValue.myValue : Qnil)
, myCachedStr()
, myCachedArray()
{
}

Value::Value(const std::vector<rb::Value>& collection)
: myValue(Qnil)
, myCachedStr()
, myCachedArray()
{
	std::vector<VALUE> convertedData(collection.size(), Qnil);
	for(int index = 0, size = collection.size(); index < size; index++)
	{
		convertedData[index] = collection[index].to<VALUE>();
	}
	myValue =  rb_ary_new4( convertedData.size(), convertedData.data() );
}

Value::~Value()
{
}

ValueType Value::getType() const
{
	switch(TYPE(myValue))
	{
		case T_NONE: 		return ValueType::None;
		case T_OBJECT: 		return ValueType::Object;
		case T_CLASS: 		return ValueType::Class;
		case T_MODULE: 		return ValueType::Module;
		case T_FLOAT: 		return ValueType::Float;
		case T_STRING: 		return ValueType::String;
		case T_REGEXP: 		return ValueType::Regexp;
		case T_ARRAY: 		return ValueType::Array;
		case T_STRUCT:		return ValueType::Struct;
		case T_BIGNUM: 		return ValueType::Bignum;
		case T_FILE: 		return ValueType::File;
		case T_MATCH: 		return ValueType::Match;
		case T_COMPLEX: 	return ValueType::Complex;
		case T_RATIONAL: 	return ValueType::Rational;
		case T_NIL: 		return ValueType::Nil;
		case T_TRUE: 		return ValueType::Bool;
		case T_FALSE: 		return ValueType::Bool;
		case T_SYMBOL: 		return ValueType::Symbol;
		case T_FIXNUM: 		return ValueType::Fixnum;
		default: return ValueType::Unknown;
	}
}

std::string Value::getClassName() const
{
	return rb_obj_classname(myValue);
}

bool Value::isKindOf(const Value& klass) const
{
	return rb_obj_is_kind_of(myValue, klass.myValue);
}

bool Value::equal(const Value& other) const
{
	return rb_equal(myValue, other.myValue);
}

bool Value::operator==(const Value& other) const
{
	return equal(other);
}

bool Value::isNil() const
{
	return myValue == Qnil;
}

bool Value::isFrozen() const
{
	return OBJ_FROZEN(myValue);
}

int Value::getArrayLength() const
{
	errorHandling(T_ARRAY);
	return RARRAY_LEN(myValue);
}

void Value::freeze()
{
	OBJ_FREEZE(myValue);
}

void Value::errorHandling(int rubyType) const
{
	if(TYPE(myValue) != rubyType)
		rb_raise(rb_eTypeError, "tried converting '%s' to '%s'", RubyTypeNames[TYPE(myValue)], RubyTypeNames[rubyType]);
}

void Value::errorHandling(int type1, int type2) const
{
	if(TYPE(myValue) != type1 && TYPE(myValue) != type2)
		rb_raise(rb_eTypeError, "tried converting '%s' to '%s'", RubyTypeNames[TYPE(myValue)], RubyTypeNames[type1]);
}

template<>
VALUE Value::to() const
{
	return myValue;
}

template<>
const Value& Value::to() const
{
	return *this;
}

template<>
Value Value::to() const
{
	return *this;
}

template<>
std::vector<Value> Value::to() const
{
	return to<const std::vector<Value>&>();
}

template<>
const std::vector<Value>& Value::to() const
{
	errorHandling(T_ARRAY);
	int count = RARRAY_LEN(myValue);
	VALUE* ptr = RARRAY_PTR(myValue);
	myCachedArray.resize(count);
	for(int index = 0; index < count; index++)
	{
		myCachedArray[index] = Value(ptr[index]);
	}
	return myCachedArray;
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

template<>
int Value::to() const
{
	errorHandling(T_FIXNUM);
	return FIX2INT(myValue);
}

template<>
float Value::to() const
{
	errorHandling(T_FLOAT);
	return NUM2DBL(myValue);
}

template<>
long long int Value::to() const
{
	errorHandling(T_FIXNUM);
	return NUM2LL(myValue);
}

template<>
unsigned int Value::to() const
{
	errorHandling(T_FIXNUM);
	return NUM2UINT(myValue);
}

template<>
bool Value::to() const
{
	errorHandling(T_TRUE, T_FALSE);
	return myValue == Qtrue;
}

}