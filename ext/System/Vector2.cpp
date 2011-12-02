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
 
#define SYSTEM_VECTOR2_CPP
#include "Vector2.hpp"

void rbVector2::Init(VALUE SFML)
{
    Vector2 = rb_define_class_under(SFML, "Vector2", rb_cObject);
    
    // Instance methods
    rb_define_method(Vector2, "initialize",      Initialize,     -1);
    rb_define_method(Vector2, "initialize_copy", InitializeCopy,  1);
    rb_define_method(Vector2, "marshal_dump",    MarshalDump,     0);
    rb_define_method(Vector2, "marshal_load",    MarshalLoad,     1);
    rb_define_method(Vector2, "-@",              Negate,          0);
    rb_define_method(Vector2, "+",               Add,             1);
    rb_define_method(Vector2, "-",               Subtract,        1);
    rb_define_method(Vector2, "*",               Multiply,        1);
    rb_define_method(Vector2, "/",               Divide,          1);
    rb_define_method(Vector2, "==",              Equal,           1);
    rb_define_method(Vector2, "eql?",            StrictEqual,     1);
    rb_define_method(Vector2, "inspect",         Inspect,         0);
    rb_define_method(Vector2, "memory_usage",    GetMemoryUsage,  0);
    
    // Attribute accessors
    rb_define_attr(Vector2, "x", true, true);
    rb_define_attr(Vector2, "y", true, true);
    
    // Instance aliases
    rb_define_alias(Vector2, "equal?", "eql?"   );
    rb_define_alias(Vector2, "to_s",   "inspect");
    rb_define_alias(Vector2, "X",      "x"      );
    rb_define_alias(Vector2, "X=",     "x="     );
    rb_define_alias(Vector2, "Y",      "y"      );
    rb_define_alias(Vector2, "Y=",     "y="     );
}

// Vector2#initialize(...)
VALUE rbVector2::Initialize(int argc, VALUE argv[], VALUE self)
{
    switch (argc)
    {
        case 0:
            SetX(self, INT2FIX(0));
            SetY(self, INT2FIX(0));
            break;
        case 1:
            InitializeCopy(self, ToRuby(argv[0]));
            break;
        case 2:
            if (FIXNUM_P(argv[0]) and FIXNUM_P(argv[1]))
            {
                SetX(self, argv[0]);
                SetY(self, argv[1]);
            }
            else
            {
                SetX(self, rb_to_float(argv[0]));
                SetY(self, rb_to_float(argv[1]));
            }
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..2)", argc);
    }
    
    return Qnil;
}

// Vector2#initialize_copy(vector2)
VALUE rbVector2::InitializeCopy(VALUE self, VALUE vector2)
{
    VALUE x = GetX(vector2);
    VALUE y = GetY(vector2);
    
    switch(Type(vector2))
    {
        case T_FIXNUM:
            SetX(self, x);
            SetY(self, y);
            break;
        case T_FLOAT:
            SetX(self, rb_float_new(NUM2DBL(x)));
            SetY(self, rb_float_new(NUM2DBL(y)));
            break;
    }
    
    return self;
}

// Vector2#marshal_dump
VALUE rbVector2::MarshalDump(VALUE self)
{
    return rb_ary_new3(2, GetX(self), GetY(self));
}

// Vector2#marshal_load(data)
VALUE rbVector2::MarshalLoad(VALUE self, VALUE data)
{
    SetX(self, rb_ary_entry(data, 0));
    SetY(self, rb_ary_entry(data, 1));
    return Qnil;
}

// Vector2#-@
VALUE rbVector2::Negate(VALUE self)
{
    VALUE x = GetX(self);
    VALUE y = GetY(self);
    
    x = rb_funcall(x, rb_intern("-@"), 0);
    y = rb_funcall(y, rb_intern("-@"), 0);
    
    VALUE argv[] = {x, y};
    return rb_class_new_instance(2, argv, Vector2);
}

// Internal
static inline VALUE DoMath(VALUE left, const char* op, VALUE right)
{
    VALUE x = rbVector2::GetX(left);
    VALUE y = rbVector2::GetY(left);
    VALUE ox = rbVector2::GetX(right);
    VALUE oy = rbVector2::GetY(right);
    
    x = rb_funcall(x, rb_intern(op), 1, ox);
    y = rb_funcall(y, rb_intern(op), 1, oy);
    
    VALUE argv[] = {x, y};
    return rb_class_new_instance(2, argv, rbVector2::Vector2);
}

// Vector2#+(other)
VALUE rbVector2::Add(VALUE self, VALUE other)
{
    return DoMath(self, "+", ToRuby(other));
}

// Vector2#-(other)
VALUE rbVector2::Subtract(VALUE self, VALUE other)
{
    return DoMath(self, "-", ToRuby(other));
}

// Vector2#*(other)
VALUE rbVector2::Multiply(VALUE self, VALUE other)
{
    return DoMath(self, "*", ToRuby(other));
}

// Vector2#/(other)
VALUE rbVector2::Divide(VALUE self, VALUE other)
{
    return DoMath(self, "/", ToRuby(other));
}

// Vector2#==(other)
VALUE rbVector2::Equal(VALUE self, VALUE other)
{
    if (CLASS_OF(other) != Vector2) return Qfalse;
    if (!RTEST(rb_equal(GetX(self), GetX(other)))) return Qfalse;
    if (!RTEST(rb_equal(GetY(self), GetY(other)))) return Qfalse;
    return Qtrue;
}

// Vector2#eql?(other)
// Vector2#equal?(other)
VALUE rbVector2::StrictEqual(VALUE self, VALUE other)
{
    if (CLASS_OF(other) != Vector2) return Qfalse;
    if (!rb_eql(GetX(self), GetX(other))) return Qfalse;
    if (!rb_eql(GetY(self), GetY(other))) return Qfalse;
    return Qtrue;
}

// Vector2#inspect
// Vector2#to_s
VALUE rbVector2::Inspect(VALUE self)
{
    VALUE result = rb_str_new2("Vector2(");
    rb_str_append(result, rb_inspect(GetX(self)));
    rb_str_append(result, rb_str_new2(", "));
    rb_str_append(result, rb_inspect(GetY(self)));
    rb_str_append(result, rb_str_new2(")"));
    return result;
}

// Vector2#memory_usage
VALUE rbVector2::GetMemoryUsage(VALUE self)
{
    return INT2FIX(0);
}
