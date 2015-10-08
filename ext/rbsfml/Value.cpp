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