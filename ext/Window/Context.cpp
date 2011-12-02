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

#define WINDOW_CONTEXT_CPP
#include "Context.hpp"

void rbContext::Init(VALUE SFML)
{
    Context = rb_define_class_under(SFML, "Context", rb_cObject);
    
    // Class methods
    rb_define_alloc_func(Context, Allocate);
    
    // Instance methods
    rb_define_method(Context, "initialize",   Initialize,     -1);
    rb_define_method(Context, "marshal_dump", MarshalDump,     0);
    rb_define_method(Context, "clone",        Clone,           0);
    rb_define_method(Context, "dup",          Dup,             0);
    rb_define_method(Context, "active=",      SetActive,       1);
    rb_define_method(Context, "memory_usage", GetMemoryUsage,  0);
    
    // Instance aliasses
    rb_define_alias(Context, "SetActive", "active=");
    rb_define_alias(Context, "active",    "active=");
}

// Context#initialize
// Context#initialize(settings, width, height)
VALUE rbContext::Initialize(int argc, VALUE argv[], VALUE self)
{
    switch(argc)
    {
        case 0:
            break;
        case 3:
        {
            sf::ContextSettings* settings;
            settings = rbContextSettings::ToSFML(argv[0]);
            unsigned int width = UINT2NUM(argv[1]);
            unsigned int height = UINT2NUM(argv[1]);
            new(ToSFML(self)) sf::Context(*settings, width, height);
            break;
        }
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0 or 3)", argc);
    }
    
    return Qnil;
}

// Context#marshal_dump
VALUE rbContext::MarshalDump(VALUE self)
{
    rb_raise(rb_eTypeError, "can't dump Context");
    return Qnil;
}

// Context#clone
VALUE rbContext::Clone(VALUE self)
{
    rb_raise(rb_eTypeError, "can't clone instance of Context");
    return Qnil;
}

// Context#dup
VALUE rbContext::Dup(VALUE self)
{
    rb_raise(rb_eTypeError, "can't dup instance of Context");
    return Qnil;
}


// Context#active=(active)
// Context#SetActive(active)
// Context#active(active)
VALUE rbContext::SetActive(VALUE self, VALUE active)
{
    rb_check_frozen(self);
    bool ret = ToSFML(self)->SetActive(RTEST(active));
    if (!ret)
        rbSFML::Raise("");
    return RBOOL(ret);
}

// VideoMode#memory_usage
VALUE rbContext::GetMemoryUsage(VALUE self)
{
    return INT2FIX(sizeof(sf::Context));
}
