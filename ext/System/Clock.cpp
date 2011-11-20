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

#define CLOCK_CPP
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
    rb_define_alias(Clock, "getElapsedTime",   "elapsed_time");
    rb_define_alias(Clock, "get_elapsed_time", "elapsed_time");
    rb_define_alias(Clock, "ElapsedTime",      "elapsed_time");
    rb_define_alias(Clock, "elapsedTime",      "elapsed_time");
    rb_define_alias(Clock, "time",             "elapsed_time");
    rb_define_alias(Clock, "Reset",            "reset"       );
    rb_define_alias(Clock, "to_s",             "inspect"     );
    rb_define_alias(Clock, "to_str",           "inspect"     );
}

VALUE rbClock::Allocate(VALUE)
{
    sf::Clock* clock = new(std::nothrow) sf::Clock;
    if (clock == NULL) rb_memerror();
    return ToRuby(clock);
}

VALUE rbClock::InitializeCopy(VALUE self, VALUE other)
{
    sf::Clock* destination = ToSFML(self);
    sf::Clock* source = ToSFML(other);
    *destination = *source;
    return self;
}

VALUE rbClock::GetElapsedTime(VALUE self)
{
    return INT2FIX(ToSFML(self)->GetElapsedTime());
}

VALUE rbClock::Reset(VALUE self)
{
    ToSFML(self)->Reset();
    return Qnil;
}

VALUE rbClock::Equal(VALUE self, VALUE other)
{
    sf::Clock* left = ToSFML(self);
    sf::Clock* right = ToSFML(other);
    return (left->GetElapsedTime()) == (right->GetElapsedTime())
        ? Qtrue
        : Qfalse;
}

VALUE rbClock::Inspect(VALUE self)
{
    VALUE ret = rb_str_new2("Clock(");
    rb_str_append(ret, rb_inspect(GetElapsedTime(self)));
    rb_str_append(ret, rb_str_new2(")"));
    return ret;
}

VALUE rbClock::GetMemoryUsage(VALUE self)
{
    return INT2FIX(sizeof(sf::Clock));
}
