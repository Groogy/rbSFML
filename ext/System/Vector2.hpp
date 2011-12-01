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

#ifndef SYSTEM_VECTOR2_HPP
#define SYSTEM_VECTOR2_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>

#include <SFML/System/Vector2.hpp>

namespace rbVector2
{
    
    static inline int Type(VALUE vector2);
    static inline VALUE ToRuby(VALUE other);
    static inline VALUE ToRuby(sf::Vector2i* vector2);
    static inline VALUE ToRuby(sf::Vector2i& vector2);
    static inline VALUE ToRuby(sf::Vector2f* vector2);
    static inline VALUE ToRuby(sf::Vector2f& vector2);
    static inline sf::Vector2i ToSFMLi(VALUE vector2);
    static inline sf::Vector2f ToSFMLf(VALUE vector2);
    
    static inline VALUE GetX(VALUE vector2);
    static inline VALUE GetY(VALUE vector2);
    static inline void SetX(VALUE vector2, VALUE value);
    static inline void SetY(VALUE vector2, VALUE value);
    
#if defined(SYSTEM_VECTOR2_CPP)
    VALUE Vector2;
#else
    extern VALUE Vector2;
#endif
    
#if defined(RBSFML_SYSTEM)
    void Init(VALUE SFML);
#endif

#if defined(SYSTEM_VECTOR2_CPP)
    // Vector2#initialize(...)
    static VALUE Initialize(int argc, VALUE* args, VALUE self);
    
    // Vector2#initialize_copy(vector2)
    static VALUE InitializeCopy(VALUE self, VALUE vector2);
    
    // Vector2#-@
    static VALUE Negate(VALUE self);
    
    // Vector2#+(other)
    static VALUE Add(VALUE self, VALUE other);
    
    // Vector2#-(other)
    static VALUE Subtract(VALUE self, VALUE other);
    
    // Vector2#*(other)
    static VALUE Multiply(VALUE self, VALUE other);
    
    // Vector2#/(other)
    static VALUE Divide(VALUE self, VALUE other);
    
    // Vector2#==(other)
    static VALUE Equal(VALUE self, VALUE other);
    
    // Vector2#eql?(other)
    // Vector2#equal?(other)
    static VALUE StrictEqual(VALUE self, VALUE other);
    
    // Vector2#inspect
    // Vector2#to_s
    static VALUE Inspect(VALUE self);
    
    // Vector2#memory_usage
    static VALUE GetMemoryUsage(VALUE self);
#endif
    
}

int rbVector2::Type(VALUE vector2)
{
    // T_FIXNUM or T_FLOAT
    return rb_type(GetX(vector2));
}

VALUE rbVector2::ToRuby(VALUE other)
{
    if (rb_obj_is_instance_of(other, Vector2))
    {
        return other;
    }
    else if (rb_obj_is_kind_of(other, rb_cNumeric))
    {
        VALUE argv[] = {other, other};
        return rb_class_new_instance(2, argv, Vector2);
    }
    else if (rb_type(other) == T_ARRAY)
    {
        VALUE* argv = RARRAY_PTR(other);
        return rb_class_new_instance(RARRAY_LEN(other), argv, Vector2);
    }
    else
    {
        rb_raise(rb_eTypeError,
                 "can't convert %s into Vector2", rb_obj_classname(other));
    }
}

VALUE rbVector2::ToRuby(sf::Vector2i* vector2)
{
    VALUE x = INT2FIX(vector2->x);
    VALUE y = INT2FIX(vector2->y);
    VALUE argv[] = {x, y};
    return rb_class_new_instance(2, argv, Vector2);
}

VALUE rbVector2::ToRuby(sf::Vector2i& vector2)
{
    return ToRuby(&vector2);
}

VALUE rbVector2::ToRuby(sf::Vector2f* vector2)
{
    VALUE x = rb_float_new(vector2->x);
    VALUE y = rb_float_new(vector2->y);
    VALUE argv[] = {x, y};
    return rb_class_new_instance(2, argv, Vector2);
}

VALUE rbVector2::ToRuby(sf::Vector2f& vector2)
{
    return ToRuby(&vector2);
}

sf::Vector2i rbVector2::ToSFMLi(VALUE vector2)
{
    vector2 = ToRuby(vector2);
    int x = NUM2INT(GetX(vector2));
    int y = NUM2INT(GetY(vector2));
    return sf::Vector2i(x, y);
}

sf::Vector2f rbVector2::ToSFMLf(VALUE vector2)
{
    vector2 = ToRuby(vector2);
    float x = NUM2DBL(GetX(vector2));
    float y = NUM2DBL(GetY(vector2));
    return sf::Vector2f(x, y);
}

VALUE rbVector2::GetX(VALUE vector2)
{
    return rb_iv_get(vector2, "@x");
}

VALUE rbVector2::GetY(VALUE vector2)
{
    return rb_iv_get(vector2, "@y");
}

void rbVector2::SetX(VALUE vector2, VALUE value)
{
    rb_iv_set(vector2, "@x", value);
}

void rbVector2::SetY(VALUE vector2, VALUE value)
{
    rb_iv_set(vector2, "@y", value);
}

#endif // SYSTEM_VECTOR2_HPP
