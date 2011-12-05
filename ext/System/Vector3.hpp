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

#ifndef SYSTEM_VECTOR3_HPP
#define SYSTEM_VECTOR3_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>

#include <SFML/System/Vector3.hpp>

namespace rbVector3
{
    
    static inline int Type(VALUE vector3);
    static inline VALUE ToRuby(VALUE other);
    static inline VALUE ToRuby(sf::Vector3i* vector3);
    static inline VALUE ToRuby(sf::Vector3i& vector3);
    static inline VALUE ToRuby(sf::Vector3f* vector3);
    static inline VALUE ToRuby(sf::Vector3f& vector3);
    static inline sf::Vector3i ToSFMLi(VALUE vector3);
    static inline sf::Vector3f ToSFMLf(VALUE vector3);
    
    static inline VALUE Allocate();
    
    static inline VALUE GetX(VALUE vector3);
    static inline VALUE GetY(VALUE vector3);
    static inline VALUE GetZ(VALUE vector3);
    static inline void SetX(VALUE vector3, VALUE value);
    static inline void SetY(VALUE vector3, VALUE value);
    static inline void SetZ(VALUE vector3, VALUE value);
    
#if defined(SYSTEM_VECTOR3_CPP)
    VALUE Vector3;
#else
    extern VALUE Vector3;
#endif
    
#if defined(RBSFML_SYSTEM)
    void Init(VALUE SFML);
#endif

#if defined(SYSTEM_VECTOR3_CPP)
    // Vector3#initialize
    // Vector3#initialize(vector3)
    // Vector3#initialize(x, y, z)
    static VALUE Initialize(int argc, VALUE* args, VALUE self);
    
    // Vector3#initialize_copy(vector3)
    static VALUE InitializeCopy(VALUE self, VALUE vector3);
    
    // Vector3#marshal_dump
    static VALUE MarshalDump(VALUE self);
    
    // Vector3#marshal_load(data)
    static VALUE MarshalLoad(VALUE self, VALUE data);
    
    // Vector3#-@
    static VALUE Negate(VALUE self);
    
    // Vector3#+(other)
    static VALUE Add(VALUE self, VALUE other);
    
    // Vector3#-(other)
    static VALUE Subtract(VALUE self, VALUE other);
    
    // Vector3#*(other)
    static VALUE Multiply(VALUE self, VALUE other);
    
    // Vector3#/(other)
    static VALUE Divide(VALUE self, VALUE other);
    
    // Vector3#==(other)
    static VALUE Equal(VALUE self, VALUE other);
    
    // Vector3#eql?(other)
    // Vector3#equal?(other)
    static VALUE StrictEqual(VALUE self, VALUE other);
    
    // Vector3#inspect
    // Vector3#to_s
    static VALUE Inspect(VALUE self);
    
    // Vector3#memory_usage
    static VALUE GetMemoryUsage(VALUE self);
#endif
    
}

VALUE rbVector3::Allocate()
{
    return rb_obj_alloc(Vector3);
}

int rbVector3::Type(VALUE vector3)
{
    // T_FIXNUM or T_FLOAT
    return rb_type(GetX(vector3));
}

VALUE rbVector3::ToRuby(VALUE other)
{
    if (rb_obj_is_instance_of(other, Vector3))
        return other;
    
    if (rb_obj_is_kind_of(other, rb_cNumeric))
        return rb_class_new_instance(3, (VALUE[]){other, other, other},
                                     Vector3);
    
    if (rb_type(other) == T_ARRAY)
        return rb_class_new_instance(RARRAY_LEN(other), RARRAY_PTR(other),
                                     Vector3);
    
    rb_raise(rb_eTypeError,
                 "can't convert %s into Vector3", rb_obj_classname(other));
}

VALUE rbVector3::ToRuby(sf::Vector3i* vector3)
{
    VALUE obj = Allocate();
    SetX(obj, INT2FIX(vector3->x));
    SetY(obj, INT2FIX(vector3->y));
    SetZ(obj, INT2FIX(vector3->z));
    return obj;
}

VALUE rbVector3::ToRuby(sf::Vector3i& vector3)
{
    return ToRuby(&vector3);
}

VALUE rbVector3::ToRuby(sf::Vector3f* vector3)
{
    VALUE obj = Allocate();
    SetX(obj, rb_float_new(vector3->x));
    SetY(obj, rb_float_new(vector3->y));
    SetZ(obj, rb_float_new(vector3->z));
    return obj;
}

VALUE rbVector3::ToRuby(sf::Vector3f& vector3)
{
    return ToRuby(&vector3);
}

sf::Vector3i rbVector3::ToSFMLi(VALUE vector3)
{
    vector3 = ToRuby(vector3);
    int x = NUM2INT(GetX(vector3));
    int y = NUM2INT(GetY(vector3));
    int z = NUM2INT(GetZ(vector3));
    return sf::Vector3i(x, y, z);
}

sf::Vector3f rbVector3::ToSFMLf(VALUE vector3)
{
    vector3 = ToRuby(vector3);
    float x = NUM2DBL(GetX(vector3));
    float y = NUM2DBL(GetY(vector3));
    float z = NUM2DBL(GetZ(vector3));
    return sf::Vector3f(x, y, z);
}

VALUE rbVector3::GetX(VALUE vector3)
{
    return rb_iv_get(vector3, "@x");
}

VALUE rbVector3::GetY(VALUE vector3)
{
    return rb_iv_get(vector3, "@y");
}

VALUE rbVector3::GetZ(VALUE vector3)
{
    return rb_iv_get(vector3, "@z");
}

void rbVector3::SetX(VALUE vector3, VALUE value)
{
    rb_check_frozen(vector3);
    rb_iv_set(vector3, "@x", value);
}

void rbVector3::SetY(VALUE vector3, VALUE value)
{
    rb_check_frozen(vector3);
    rb_iv_set(vector3, "@y", value);
}

void rbVector3::SetZ(VALUE vector3, VALUE value)
{
    rb_check_frozen(vector3);
    rb_iv_set(vector3, "@z", value);
}

#endif // SYSTEM_VECTOR2_HPP
