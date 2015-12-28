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
#include "base.hpp"

namespace
{
	constexpr char symMore[] = ">";
	constexpr char symLess[] = "<";
}

namespace rb
{

Value Float(rb_cFloat);
Value Fixnum(rb_cFixnum);

Value yield(const Value& value)
{
	return rb::Value(rb_yield(value.to<VALUE>()));
}

Value getEnumerator(const Value& value)
{
	VALUE enumerator = SIZED_ENUMERATOR(value.to<VALUE>(), 0, nullptr, 0);
	return rb::Value(enumerator);
}

bool blockGiven()
{
	return rb_block_given_p();
}

Value max(Value a, Value b)
{
	return a.call<symMore>(b) == True ? a : b;
}

Value min(Value a, Value b)
{
	return a.call<symLess>(b) == True ? a : b;
}

Value callSuper(const std::vector<Value>& args)
{
    VALUE* argArray = new VALUE[args.size()];
    for(int index = 0, size = args.size(); index < size; index++)
    {
        argArray[index] = args[index].to<VALUE>();
    }
    return rb::Value(rb_call_super(args.size(), argArray));
}

Value eval(const std::string& script)
{
    return rb::Value::create(rb_eval_string(script.c_str()));
}

}
