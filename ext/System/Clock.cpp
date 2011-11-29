/* rbSFML
 * Copyright (c) 2010 Henrik Valter Vogelius Hansson - groogy@groogy.se
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

#define SYSTEM_CLOCK_CPP
#include "Clock.hpp"

void rbClock::Init(VALUE SFML)
{
    Clock = rb_define_class_under(SFML, "Clock", rb_cObject);
    
    // Class methods
    rb_define_alloc_func(Clock, Allocate);
    
    // Instance methods
    rb_define_method(Clock, "initialize_copy", InitializeCopy, 1);
    rb_define_method(Clock, "elapsed_time",    GetElapsedTime, 0);
    rb_define_method(Clock, "reset",           Reset,          0);
    rb_define_method(Clock, "==",              Equal,          1);
    rb_define_method(Clock, "inspect",         Inspect,        0);
    rb_define_method(Clock, "memory_usage",    GetMemoryUsage, 0);
    
    // Instance aliasses
    rb_define_alias(Clock, "GetElapsedTime",   "elapsed_time");
    rb_define_alias(Clock, "get_elapsed_time", "elapsed_time");
    rb_define_alias(Clock, "time",             "elapsed_time");
    rb_define_alias(Clock, "Reset",            "reset"       );
    rb_define_alias(Clock, "eql?",             "=="          );
    rb_define_alias(Clock, "equal?",           "=="          );
    rb_define_alias(Clock, "to_s",             "inspect"     );
}

// Clock#initialize_copy(clock)
VALUE rbClock::InitializeCopy(VALUE self, VALUE clock)
{
    *ToSFML(self) = *ToSFML(clock);
    return self;
}

// Clock#elapsed_time
// Clock#GetElapsedTime
// Clock#time
VALUE rbClock::GetElapsedTime(VALUE self)
{
    return UINT2NUM(ToSFML(self)->GetElapsedTime());
}

// Clock#reset
// Clock#Reset
VALUE rbClock::Reset(VALUE self)
{
    ToSFML(self)->Reset();
    return Qnil;
}

// Clock#==(other)
// Clock#eql?(other)
// Clock#equal?(other)
VALUE rbClock::Equal(VALUE self, VALUE other)
{
    if (CLASS_OF(other) != Clock) return Qfalse;
    sf::Clock* left = ToSFML(self);
    sf::Clock* right = ToSFML(other);
    return RBOOL(left->GetElapsedTime() == right->GetElapsedTime());
}

// Clock#inspect
// Clock#to_s
VALUE rbClock::Inspect(VALUE self)
{
    VALUE ret = rb_str_new2("Clock(");
    rb_str_append(ret, rb_inspect(GetElapsedTime(self)));
    rb_str_append(ret, rb_str_new2(")"));
    return ret;
}

// Clock#memory_usage
VALUE rbClock::GetMemoryUsage(VALUE self)
{
    return INT2FIX(sizeof(sf::Clock));
}
