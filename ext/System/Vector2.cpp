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
 
#define VECTOR2_CPP
#include "Vector2.hpp"

void rbVector2::Init(VALUE SFML)
{
    Vector2 = rb_define_class_under(SFML, "Vector2", rb_cObject);
    
    // Instance methods
    rb_define_method(Vector2, "initialize",      Initialize,     -1);
    rb_define_method(Vector2, "initialize_copy", InitializeCopy,  1);
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
    rb_define_attr(Vector2, "x", 1, 1);
    rb_define_attr(Vector2, "y", 1, 1);
    
    // Instance aliases
    rb_define_alias(Vector2, "to_s",   "inspect");
    rb_define_alias(Vector2, "to_str", "inspect");
    rb_define_alias(Vector2, "X",      "x"      );
    rb_define_alias(Vector2, "X=",     "x="     );
    rb_define_alias(Vector2, "Y",      "y"      );
    rb_define_alias(Vector2, "Y=",     "y="     );
    rb_define_alias(Vector2, "equal?", "eql?"   );
}

VALUE rbVector2::Initialize(int argc, VALUE argv[], VALUE self)
{    
    VALUE x, y, vector2;
    switch (argc)
    {
        case 0:
            SetX(self, INT2FIX(0));
            SetY(self, INT2FIX(0));
            break;
        case 1:
            vector2 = ToRuby(argv[0]);
            InitializeCopy(self, vector2);
            break;
        case 2:
            x = argv[0];
            y = argv[1];
            
            // Ensure all arguments are kind of Numeric.
            VALIDATE_CLASS(x, rb_cNumeric);
            VALIDATE_CLASS(y, rb_cNumeric);
            
            // Ensure all arguments are instance of Float or Fixnum.
            if (!FIXNUM_P(x) or !FIXNUM_P(y))
            {
                x = rb_convert_type(x, T_FLOAT, "Float", "to_f");
                y = rb_convert_type(y, T_FLOAT, "Float", "to_f");
            }
            
            SetX(self, x);
            SetY(self, y);
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..2)", argc);
    }
}

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
}

VALUE rbVector2::Negate(VALUE self)
{
    VALUE x = GetX(self);
    VALUE y = GetY(self);
    
    static ID id_negate = rb_intern("-@");
    x = rb_funcall(x, id_negate, 0);
    y = rb_funcall(y, id_negate, 0);
    
    VALUE argv[] = {x, y};
    return rb_class_new_instance(2, argv, Vector2);
}

static inline VALUE DoMath(VALUE left, ID op, VALUE right)
{
    VALUE x = rbVector2::GetX(left);
    VALUE y = rbVector2::GetY(left);
    VALUE ox = rbVector2::GetX(right);
    VALUE oy = rbVector2::GetY(right);
    
    x = rb_funcall(x, op, 1, ox);
    y = rb_funcall(y, op, 1, oy);
    
    VALUE argv[] = {x, y};
    return rb_class_new_instance(2, argv, rbVector2::Vector2);
}

VALUE rbVector2::Add(VALUE self, VALUE other)
{
    static ID id_add = rb_intern("+");
    return DoMath(self, id_add, ToRuby(other));
}

VALUE rbVector2::Subtract(VALUE self, VALUE other)
{
    static ID id_subtract = rb_intern("-");
    return DoMath(self, id_subtract, ToRuby(other));
}

VALUE rbVector2::Multiply(VALUE self, VALUE other)
{
    static ID id_multiply = rb_intern("*");
    return DoMath(self, id_multiply, ToRuby(other));
}

VALUE rbVector2::Divide(VALUE self, VALUE other)
{
    static ID id_divide = rb_intern("/");
    return DoMath(self, id_divide, ToRuby(other));
}

VALUE rbVector2::Equal(VALUE self, VALUE other)
{
    if (CLASS_OF(other) != Vector2) return Qfalse;
    if (!rb_equal(GetX(self), GetX(other))) return Qfalse;
    if (!rb_equal(GetY(self), GetY(other))) return Qfalse;
    return Qtrue;
}

VALUE rbVector2::StrictEqual(VALUE self, VALUE other)
{
    if (CLASS_OF(other) != Vector2) return Qfalse;
    if (!rb_eql(GetX(self), GetX(other))) return Qfalse;
    if (!rb_eql(GetY(self), GetY(other))) return Qfalse;
    return Qtrue;
}

VALUE rbVector2::Inspect(VALUE self)
{
    VALUE result = rb_str_new2("Vector2(");
    rb_str_append(result, rb_inspect(GetX(self)));
    rb_str_append(result, rb_str_new2(", "));
    rb_str_append(result, rb_inspect(GetY(self)));
    rb_str_append(result, rb_str_new2(")"));
    return result;
}

VALUE rbVector2::GetMemoryUsage(VALUE self)
{
    return INT2FIX(0);
}
