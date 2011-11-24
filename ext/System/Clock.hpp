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

#ifndef SYSTEM_CLOCK_HPP
#define SYSTEM_CLOCK_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>

#include <SFML/System/Clock.hpp>

namespace rbClock
{
    
    static inline void Free(void* clock);
    
    static inline VALUE ToRuby(VALUE other);
    static inline VALUE ToRuby(sf::Clock* clock);
    static inline VALUE ToRuby(sf::Clock& clock);
    static inline sf::Clock* ToSFML(VALUE clock);
    
    static inline VALUE Allocate(VALUE);
    
#if defined(SYSTEM_CLOCK_CPP)
    VALUE Clock;
#else
    extern VALUE Clock;
#endif
    
#if defined(RBSFML_SYSTEM)
    
    void Init(VALUE SFML);
    
    // Clock#initialize_copy(other)
    static VALUE InitializeCopy(VALUE self, VALUE clock);
    
    // Clock#elapsed_time
    static VALUE GetElapsedTime(VALUE self);
    
    // Clock#reset
    static VALUE Reset(VALUE self);
    
    // Clock#==(other)
    static VALUE Equal(VALUE self, VALUE other);
    
    // Clock#inspect
    static VALUE Inspect(VALUE self);
    
    // Clock#memory_usage
    static VALUE GetMemoryUsage(VALUE self);
    
#endif

};

void rbClock::Free(void* clock)
{
    delete (sf::Clock*)clock;
}

VALUE rbClock::Allocate(VALUE)
{
    sf::Clock* clock = new(std::nothrow) sf::Clock;
    if (clock == NULL) rb_memerror();
    return ToRuby(clock);
}

VALUE rbClock::ToRuby(VALUE other)
{
    if (rb_obj_is_instance_of(other, Clock))
    {
        return other;
    }
    else
    {
        rb_raise(rb_eTypeError,
                 "can't convert %s into Clock", rb_obj_classname(other));
    }
}

VALUE rbClock::ToRuby(sf::Clock* clock)
{
    return rb_data_object_alloc(Clock, clock, NULL, Free);
}

VALUE rbClock::ToRuby(sf::Clock& clock)
{
    return rb_data_object_alloc(Clock, &clock, NULL, NULL);
}

sf::Clock* rbClock::ToSFML(VALUE clock)
{
    clock = ToRuby(clock);
    return (sf::Clock*)DATA_PTR(clock);
}

#endif // SYSTEM_CLOCK_HPP
