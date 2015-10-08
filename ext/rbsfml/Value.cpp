#include "Value.hpp"

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
	myCachedStr.assign(RSTRING_PTR(myValue), RSTRING_LEN(myValue));
	return myCachedStr;
}

}