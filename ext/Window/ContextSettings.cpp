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

#define WINDOW_CONTEXTSETTINGS_CPP
#include "ContextSettings.hpp"

void rbContextSettings::Init(VALUE SFML)
{
    ContextSettings = rb_define_class_under(SFML, "ContextSettings", rb_cObject);
    
    // Class methods
    rb_define_alloc_func(ContextSettings, Allocate);
    
    // Instance methods
    rb_define_method(ContextSettings, "initialize",          Initialize,           -1);
    rb_define_method(ContextSettings, "depth_bits",          GetDepthBits,          0);
    rb_define_method(ContextSettings, "stencil_bits",        GetStencilBits,        0);
    rb_define_method(ContextSettings, "antialiasing_level",  GetAntialiasingLevel,  0);
    rb_define_method(ContextSettings, "major_version",       GetMajorVersion,       0);
    rb_define_method(ContextSettings, "minor_version",       GetMinorVersion,       0);
    rb_define_method(ContextSettings, "depth_bits=",         SetDepthBits,          1);
    rb_define_method(ContextSettings, "stencil_bits=",       SetStencilBits,        1);
    rb_define_method(ContextSettings, "antialiasing_level=", SetAntialiasingLevel,  1);
    rb_define_method(ContextSettings, "major_version=",      SetMajorVersion,       1);
    rb_define_method(ContextSettings, "minor_version=",      SetMinorVersion,       1);
    
    // Instance aliasses
    rb_define_alias(ContextSettings, "DepthBits",          "depth_bits"         );
    rb_define_alias(ContextSettings, "StencilBits",        "stencil_bits"       );
    rb_define_alias(ContextSettings, "AntialiasingLevel",  "antialiasing_level" );
    rb_define_alias(ContextSettings, "MajorVersion",       "major_version"      );
    rb_define_alias(ContextSettings, "MinorVersion",       "minor_version"      );
    rb_define_alias(ContextSettings, "DepthBits=",         "depth_bits="        );
    rb_define_alias(ContextSettings, "StencilBits=",       "stencil_bits="      );
    rb_define_alias(ContextSettings, "AntialiasingLevel=", "antialiasing_level=");
    rb_define_alias(ContextSettings, "MajorVersion=",      "major_version="     );
    rb_define_alias(ContextSettings, "MinorVersion=",      "minor_version="     );
}

VALUE rbContextSettings::Initialize(int argc, VALUE argv[], VALUE self)
{
    sf::ContextSettings* settings = ToSFML(self);
    
    switch (argc)
    {
        case 5:
            settings->MinorVersion = NUM2INT(argv[4]);
        case 4:
            settings->MajorVersion = NUM2INT(argv[3]);
        case 3:
            settings->AntialiasingLevel = NUM2INT(argv[2]);
        case 2:
            settings->StencilBits = NUM2INT(argv[1]);
        case 1:
            settings->DepthBits = NUM2INT(argv[0]);
        case 0:
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..5)", argc);
    }
}

VALUE rbContextSettings::GetDepthBits(VALUE self)
{
    return INT2FIX(ToSFML(self)->DepthBits);
}
    
VALUE rbContextSettings::GetStencilBits(VALUE self)
{
    return INT2FIX(ToSFML(self)->StencilBits);
}
    
VALUE rbContextSettings::GetAntialiasingLevel(VALUE self)
{
    return INT2FIX(ToSFML(self)->AntialiasingLevel);
}
    
VALUE rbContextSettings::GetMajorVersion(VALUE self)
{
    return INT2FIX(ToSFML(self)->MajorVersion);
}
    
VALUE rbContextSettings::GetMinorVersion(VALUE self)
{
    return INT2FIX(ToSFML(self)->MinorVersion);
}

VALUE rbContextSettings::SetDepthBits(VALUE self, VALUE value)
{
    ToSFML(self)->DepthBits = NUM2INT(value);
}
    
VALUE rbContextSettings::SetStencilBits(VALUE self, VALUE value)
{
    ToSFML(self)->StencilBits = NUM2INT(value);
}
    
VALUE rbContextSettings::SetAntialiasingLevel(VALUE self, VALUE value)
{
    ToSFML(self)->AntialiasingLevel = NUM2INT(value);
}
    
VALUE rbContextSettings::SetMajorVersion(VALUE self, VALUE value)
{
    ToSFML(self)->MajorVersion = NUM2INT(value);
}
    
VALUE rbContextSettings::SetMinorVersion(VALUE self, VALUE value)
{
    ToSFML(self)->MinorVersion = NUM2INT(value);
}

