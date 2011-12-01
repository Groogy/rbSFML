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
 
#define SYSTEM_VECTOR3_CPP
#include "Vector3.hpp"

void rbVector3::Init(VALUE SFML)
{
    Vector3 = rb_define_class_under(SFML, "Vector3", rb_cObject);
    
    // Instance methods
    rb_define_method(Vector3, "initialize",      Initialize,     -1);
    rb_define_method(Vector3, "initialize_copy", InitializeCopy,  1);
    rb_define_method(Vector3, "-@",              Negate,          0);
    rb_define_method(Vector3, "+",               Add,             1);
    rb_define_method(Vector3, "-",               Subtract,        1);
    rb_define_method(Vector3, "*",               Multiply,        1);
    rb_define_method(Vector3, "/",               Divide,          1);
    rb_define_method(Vector3, "==",              Equal,           1);
    rb_define_method(Vector3, "eql?",            StrictEqual,     1);
    rb_define_method(Vector3, "inspect",         Inspect,         0);
    rb_define_method(Vector3, "memory_usage",    GetMemoryUsage,  0);
    
    // Attribute accessors
    rb_define_attr(Vector3, "x", true, true);
    rb_define_attr(Vector3, "y", true, true);
    rb_define_attr(Vector3, "z", true, true);
    
    // Instance aliases
    rb_define_alias(Vector3, "equal?", "eql?"   );
    rb_define_alias(Vector3, "to_s",   "inspect");
    rb_define_alias(Vector3, "X",      "x"      );
    rb_define_alias(Vector3, "X=",     "x="     );
    rb_define_alias(Vector3, "Y",      "y"      );
    rb_define_alias(Vector3, "Y=",     "y="     );
    rb_define_alias(Vector3, "Z",      "z"      );
    rb_define_alias(Vector3, "Z=",     "z="     );
}

// Vector3#initialize(...)
VALUE rbVector3::Initialize(int argc, VALUE argv[], VALUE self)
{
    switch (argc)
    {
        case 0:
            SetX(self, INT2FIX(0));
            SetY(self, INT2FIX(0));
            SetZ(self, INT2FIX(0));
            break;
        case 1:
            InitializeCopy(self, ToRuby(argv[0]));
            break;
        case 3:
            if (FIXNUM_P(argv[0]) and FIXNUM_P(argv[1]) and FIXNUM_P(argv[2]))
            {
                SetX(self, argv[0]);
                SetY(self, argv[1]);
                SetZ(self, argv[2]);
            }
            else
            {
                SetX(self, rb_to_float(argv[0]));
                SetY(self, rb_to_float(argv[1]));
                SetZ(self, rb_to_float(argv[2]));
            }
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0, 1, or 3)", argc);
    }
    
    return Qnil;
}

// Vector3#initialize_copy(vector3)
VALUE rbVector3::InitializeCopy(VALUE self, VALUE vector3)
{
    VALUE x = GetX(vector3);
    VALUE y = GetY(vector3);
    VALUE z = GetZ(vector3);
    
    switch(Type(vector3))
    {
        case T_FIXNUM:
            SetX(self, x);
            SetY(self, y);
            SetZ(self, z);
            break;
        case T_FLOAT:
            SetX(self, rb_float_new(NUM2DBL(x)));
            SetY(self, rb_float_new(NUM2DBL(y)));
            SetZ(self, rb_float_new(NUM2DBL(z)));
            break;
    }
    
    return self;
}

// Vector3#-@
VALUE rbVector3::Negate(VALUE self)
{
    VALUE x = GetX(self);
    VALUE y = GetY(self);
    VALUE z = GetY(self);
    
    x = rb_funcall(x, rb_intern("-@"), 0);
    y = rb_funcall(y, rb_intern("-@"), 0);
    z = rb_funcall(z, rb_intern("-@"), 0);
    
    VALUE argv[] = {x, y, z};
    return rb_class_new_instance(3, argv, Vector3);
}

// Internal
static inline VALUE DoMath(VALUE left, const char* op, VALUE right)
{
    VALUE x = rbVector3::GetX(left);
    VALUE y = rbVector3::GetY(left);
    VALUE z = rbVector3::GetZ(left);
    VALUE ox = rbVector3::GetX(right);
    VALUE oy = rbVector3::GetY(right);
    VALUE oz = rbVector3::GetZ(right);
    
    x = rb_funcall(x, rb_intern(op), 1, ox);
    y = rb_funcall(y, rb_intern(op), 1, oy);
    z = rb_funcall(z, rb_intern(op), 1, oz);
    
    VALUE argv[] = {x, y, z};
    return rb_class_new_instance(3, argv, rbVector3::Vector3);
}

// Vector3#+(other)
VALUE rbVector3::Add(VALUE self, VALUE other)
{
    return DoMath(self, "+", ToRuby(other));
}

// Vector3#-(other)
VALUE rbVector3::Subtract(VALUE self, VALUE other)
{
    return DoMath(self, "-", ToRuby(other));
}

// Vector3#*(other)
VALUE rbVector3::Multiply(VALUE self, VALUE other)
{
    return DoMath(self, "*", ToRuby(other));
}

// Vector3#/(other)
VALUE rbVector3::Divide(VALUE self, VALUE other)
{
    return DoMath(self, "/", ToRuby(other));
}

// Vector3#==(other)
VALUE rbVector3::Equal(VALUE self, VALUE other)
{
    if (CLASS_OF(other) != Vector3) return Qfalse;
    if (!RTEST(rb_equal(GetX(self), GetX(other)))) return Qfalse;
    if (!RTEST(rb_equal(GetY(self), GetY(other)))) return Qfalse;
    if (!RTEST(rb_equal(GetZ(self), GetZ(other)))) return Qfalse;
    return Qtrue;
}

// Vector3#eql?(other)
// Vector3#equal?(other)
VALUE rbVector3::StrictEqual(VALUE self, VALUE other)
{
    if (CLASS_OF(other) != Vector3) return Qfalse;
    if (!rb_eql(GetX(self), GetX(other))) return Qfalse;
    if (!rb_eql(GetY(self), GetY(other))) return Qfalse;
    if (!rb_eql(GetZ(self), GetZ(other))) return Qfalse;
    return Qtrue;
}

// Vector3#inspect
// Vector3#to_s
VALUE rbVector3::Inspect(VALUE self)
{
    VALUE result = rb_str_new2("Vector3(");
    rb_str_append(result, rb_inspect(GetX(self)));
    rb_str_append(result, rb_str_new2(", "));
    rb_str_append(result, rb_inspect(GetY(self)));
    rb_str_append(result, rb_str_new2(", "));
    rb_str_append(result, rb_inspect(GetZ(self)));
    rb_str_append(result, rb_str_new2(")"));
    return result;
}

// Vector3#memory_usage
VALUE rbVector3::GetMemoryUsage(VALUE self)
{
    return INT2FIX(0);
}
