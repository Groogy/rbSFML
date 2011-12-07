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
    rb_define_method(ContextSettings, "initialize_copy",     InitializeCopy,        1);
    rb_define_method(ContextSettings, "marshal_dump",        MarshalDump,           0);
    rb_define_method(ContextSettings, "marshal_load",        MarshalLoad,           1);
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
    rb_define_method(ContextSettings, "==",                  Equal,                 1);
    rb_define_method(ContextSettings, "inspect",             Inspect,               0);
    rb_define_method(ContextSettings, "memory_usage",        GetMemoryUsage,        0);
    
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
    rb_define_alias(ContextSettings, "to_s",               "inspect"            );
    rb_define_alias(ContextSettings, "eql?",               "=="                 );
    rb_define_alias(ContextSettings, "equal?",             "=="                 );
}

// ContextSettings#initialize(...)
VALUE rbContextSettings::Initialize(int argc, VALUE argv[], VALUE self)
{
    sf::ContextSettings* settings = ToSFML(self);
    
    if (argc == 1 and rb_type(argv[0]) == T_HASH)
    {
        VALUE other = ToRuby(argv[0], CLASS_OF(self));
        InitializeCopy(self, other);
        return Qnil;
    }
    
    switch (argc)
    {
        case 5:
            settings->MinorVersion = NUM2UINT(argv[4]);
        case 4:
            settings->MajorVersion = NUM2UINT(argv[3]);
        case 3:
            settings->AntialiasingLevel = NUM2UINT(argv[2]);
        case 2:
            settings->StencilBits = NUM2UINT(argv[1]);
        case 1:
            settings->DepthBits = NUM2UINT(argv[0]);
        case 0:
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..5)", argc);
    }
    
    return Qnil;
}

// ContextSettings#initialize_copy(settings)
VALUE rbContextSettings::InitializeCopy(VALUE self, VALUE settings)
{
    *ToSFML(self) = *ToSFML(settings);
    return self;
}

// ContextSettings#marshal_dump
VALUE rbContextSettings::MarshalDump(VALUE self)
{
    sf::ContextSettings* settings = ToSFML(self);
    
    VALUE ptr[5];
    ptr[0] = UINT2NUM(settings->DepthBits);
    ptr[1] = UINT2NUM(settings->StencilBits);
    ptr[2] = UINT2NUM(settings->AntialiasingLevel);
    ptr[3] = UINT2NUM(settings->MajorVersion);
    ptr[4] = UINT2NUM(settings->MinorVersion);
    return rb_ary_new4(5, ptr);
}

// ContextSettings#marshal_load(data)
VALUE rbContextSettings::MarshalLoad(VALUE self, VALUE data)
{
    sf::ContextSettings* settings = ToSFML(self);
    
    VALUE* ptr = RARRAY_PTR(data);
    settings->DepthBits         = NUM2UINT(ptr[0]);
    settings->StencilBits       = NUM2UINT(ptr[1]);
    settings->AntialiasingLevel = NUM2UINT(ptr[2]);
    settings->MajorVersion      = NUM2UINT(ptr[3]);
    settings->MinorVersion      = NUM2UINT(ptr[4]);
    return Qnil;
}

// ContextSettings#depth_bits
// ContextSettings#DepthBits
VALUE rbContextSettings::GetDepthBits(VALUE self)
{
    return UINT2NUM(ToSFML(self)->DepthBits);
}

// ContextSettings#stencil_bits
// ContextSettings#StencilBits
VALUE rbContextSettings::GetStencilBits(VALUE self)
{
    return UINT2NUM(ToSFML(self)->StencilBits);
}

// ContextSettings#antialiasing_level
// ContextSettings#AntialiasingLevel
VALUE rbContextSettings::GetAntialiasingLevel(VALUE self)
{
    return UINT2NUM(ToSFML(self)->AntialiasingLevel);
}

// ContextSettings#major_version
// ContextSettings#MajorVersion
VALUE rbContextSettings::GetMajorVersion(VALUE self)
{
    return UINT2NUM(ToSFML(self)->MajorVersion);
}

// ContextSettings#minor_version
// ContextSettings#MinorVersion
VALUE rbContextSettings::GetMinorVersion(VALUE self)
{
    return UINT2NUM(ToSFML(self)->MinorVersion);
}

// ContextSettings#depth_bits=(value)
// ContextSettings#DepthBits=(value)
VALUE rbContextSettings::SetDepthBits(VALUE self, VALUE value)
{
    rb_check_frozen(self);
    ToSFML(self)->DepthBits = NUM2UINT(value);
    return Qnil;
}

// ContextSettings#stencil_bits=(value)
// ContextSettings#StencilBits=(value)
VALUE rbContextSettings::SetStencilBits(VALUE self, VALUE value)
{
    rb_check_frozen(self);
    ToSFML(self)->StencilBits = NUM2UINT(value);
    return Qnil;
}

// ContextSettings#antialiasing_level=(value)
// ContextSettings#AntialiasingLevel=(value)
VALUE rbContextSettings::SetAntialiasingLevel(VALUE self, VALUE value)
{
    rb_check_frozen(self);
    ToSFML(self)->AntialiasingLevel = NUM2UINT(value);
    return Qnil;
}

// ContextSettings#major_version=(value)
// ContextSettings#MajorVersion=(value)
VALUE rbContextSettings::SetMajorVersion(VALUE self, VALUE value)
{
    rb_check_frozen(self);
    ToSFML(self)->MajorVersion = NUM2UINT(value);
    return Qnil;
}

// ContextSettings#minor_version=(value)
// ContextSettings#MinorVersion=(value)
VALUE rbContextSettings::SetMinorVersion(VALUE self, VALUE value)
{
    rb_check_frozen(self);
    ToSFML(self)->MinorVersion = NUM2UINT(value);
    return Qnil;
}

// ContextSettings#==(other)
// ContextSettings#eql?(other)
// ContextSettings#equal?(other)
VALUE rbContextSettings::Equal(VALUE self, VALUE other)
{
    if (CLASS_OF(self) != CLASS_OF(other)) return Qfalse;
    sf::ContextSettings* left = ToSFML(self);
    sf::ContextSettings* right = ToSFML(other, CLASS_OF(self));
    
    if (left->DepthBits         != right->DepthBits        ) return Qfalse;
    if (left->StencilBits       != right->StencilBits      ) return Qfalse;
    if (left->AntialiasingLevel != right->AntialiasingLevel) return Qfalse;
    if (left->MajorVersion      != right->MajorVersion     ) return Qfalse;
    if (left->MinorVersion      != right->MinorVersion     ) return Qfalse;
    
    return Qtrue;
}

// ContextSettings#inspect
// ContextSettings#to_s
VALUE rbContextSettings::Inspect(VALUE self)
{
    sf::ContextSettings* settings = ToSFML(self);
    return rb_sprintf("%s(depth_bits: %u, stencil_bits: %u, "
                      "antialiasing_level: %u, major_version: %u, "
                      "minor_version: %u)",
                      rb_obj_classname(self),
                      settings->DepthBits,
                      settings->StencilBits,
                      settings->AntialiasingLevel,
                      settings->MajorVersion,
                      settings->MinorVersion);
}

// ContextSettings#memory_usage
VALUE rbContextSettings::GetMemoryUsage(VALUE self)
{
    return SIZET2NUM(sizeof(sf::ContextSettings));
}
