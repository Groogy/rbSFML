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
 
#ifndef RBSFML_HPP
#define RBSFML_HPP

#include <ruby.h>

#define SFML_VERSION    "2.0"
#define BINDING_VERSION "development-unstable"

template<typename T>
static inline T MAX(T a, T b)
{
    return a > b ? a : b;
}

template<typename T>
static inline T MIN(T a, T b)
{
    return a > b ? b : a;
}

static inline VALUE MAX(VALUE a, VALUE b)
{
    return rb_funcall(a, rb_intern(">"), 1, b) == Qtrue ? a : b;
}

static inline VALUE MIN(VALUE a, VALUE b)
{
    return rb_funcall(a, rb_intern(">"), 1, b) == Qtrue ? b : a;
}

typedef VALUE (*RubyFunctionPtr)(...);

#define rb_define_module_function(klass, name, func, argc, ...) \
        rb_define_module_function(klass, name, reinterpret_cast<RubyFunctionPtr>(func), argc, ##__VA_ARGS__)
        
#define rb_define_singleton_method(klass, name, func, argc, ...) \
        rb_define_singleton_method(klass, name, reinterpret_cast<RubyFunctionPtr>(func), argc, ##__VA_ARGS__)
        
#define rb_define_method(klass, name, func, argc, ...) \
        rb_define_method(klass, name, reinterpret_cast<RubyFunctionPtr>(func), argc, ##__VA_ARGS__)

#endif // RBSFML_HPP
