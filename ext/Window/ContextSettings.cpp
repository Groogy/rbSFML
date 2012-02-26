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

void rbContextSettings::Init( VALUE SFML )
{
    rbContextSettings::Class = rb_define_class_under( SFML, "ContextSettings", rb_cObject );
    
    // Class methods
    rb_define_alloc_func( rbContextSettings::Class, rbMacros::Allocate< sf::ContextSettings > );
    
    // Instance methods
    rb_define_method( rbContextSettings::Class, "initialize",          rbContextSettings::Initialize,           -1 );
    rb_define_method( rbContextSettings::Class, "initialize_copy",     rbContextSettings::InitializeCopy,        1 );
    rb_define_method( rbContextSettings::Class, "marshal_dump",        rbContextSettings::MarshalDump,           0 );
    rb_define_method( rbContextSettings::Class , "marshal_load",       rbContextSettings::MarshalLoad,           1 );
    rb_define_method( rbContextSettings::Class, "depth_bits",          rbContextSettings::GetDepthBits,          0 );
    rb_define_method( rbContextSettings::Class, "stencil_bits",        rbContextSettings::GetStencilBits,        0 );
    rb_define_method( rbContextSettings::Class, "antialiasing_level",  rbContextSettings::GetAntialiasingLevel,  0 );
    rb_define_method( rbContextSettings::Class, "major_version",       rbContextSettings::GetMajorVersion,       0 );
    rb_define_method( rbContextSettings::Class, "minor_version",       rbContextSettings::GetMinorVersion,       0 );
    rb_define_method( rbContextSettings::Class, "depth_bits=",         rbContextSettings::SetDepthBits,          1 );
    rb_define_method( rbContextSettings::Class, "stencil_bits=",       rbContextSettings::SetStencilBits,        1 );
    rb_define_method( rbContextSettings::Class, "antialiasing_level=", rbContextSettings::SetAntialiasingLevel,  1 );
    rb_define_method( rbContextSettings::Class, "major_version=",      rbContextSettings::SetMajorVersion,       1 );
    rb_define_method( rbContextSettings::Class, "minor_version=",      rbContextSettings::SetMinorVersion,       1 );
    rb_define_method( rbContextSettings::Class, "==",                  rbContextSettings::Equal,                 1 );
    rb_define_method( rbContextSettings::Class, "inspect",             rbContextSettings::Inspect,               0 );
    rb_define_method( rbContextSettings::Class, "memory_usage",        rbContextSettings::GetMemoryUsage,        0 );
    
    // Instance aliasses
    rb_define_alias( rbContextSettings::Class, "DepthBits",          "depth_bits"          );
    rb_define_alias( rbContextSettings::Class, "StencilBits",        "stencil_bits"        );
    rb_define_alias( rbContextSettings::Class, "AntialiasingLevel",  "antialiasing_level"  );
    rb_define_alias( rbContextSettings::Class, "MajorVersion",       "major_version"       );
    rb_define_alias( rbContextSettings::Class, "MinorVersion",       "minor_version"       );
    rb_define_alias( rbContextSettings::Class, "DepthBits=",         "depth_bits="         );
    rb_define_alias( rbContextSettings::Class, "StencilBits=",       "stencil_bits="       );
    rb_define_alias( rbContextSettings::Class, "AntialiasingLevel=", "antialiasing_level=" );
    rb_define_alias( rbContextSettings::Class, "MajorVersion=",      "major_version="      );
    rb_define_alias( rbContextSettings::Class, "MinorVersion=",      "minor_version="      );
    rb_define_alias( rbContextSettings::Class, "to_s",               "inspect"             );
    rb_define_alias( rbContextSettings::Class, "eql?",               "=="                  );
    rb_define_alias( rbContextSettings::Class, "equal?",             "=="                  );
}

// ContextSettings#initialize(...)
VALUE rbContextSettings::Initialize( int argc, VALUE argv[], VALUE aSelf )
{
    sf::ContextSettings* settings = rbContextSettings::ToSFML( aSelf );
    
    if( argc == 1 and rb_type( argv[ 0 ] ) == T_HASH )
    {
        VALUE other = rbContextSettings::ToRuby( argv[ 0 ] );
        InitializeCopy( aSelf, other );
        return Qnil;
    }
    
    switch( argc )
    {
        case 5:
            settings->MinorVersion = NUM2UINT( argv[ 4 ] );
        case 4:
            settings->MajorVersion = NUM2UINT( argv[ 3 ] );
        case 3:
            settings->AntialiasingLevel = NUM2UINT( argv[ 2 ] );
        case 2:
            settings->StencilBits = NUM2UINT( argv[ 1 ] );
        case 1:
            settings->DepthBits = NUM2UINT( argv[ 0 ] );
        case 0:
            break;
        default:
            rb_raise( rb_eArgError,
                      "wrong number of arguments(%i for 0..5)", argc );
    }
    
    return Qnil;
}

// ContextSettings#initialize_copy(settings)
VALUE rbContextSettings::InitializeCopy( VALUE aSelf, VALUE someSettings )
{
    *rbContextSettings::ToSFML( aSelf ) = *rbContextSettings::ToSFML( someSettings );
    return aSelf;
}

// ContextSettings#marshal_dump
VALUE rbContextSettings::MarshalDump( VALUE aSelf )
{
    sf::ContextSettings* settings = rbContextSettings::ToSFML( aSelf );
    
    VALUE ptr[ 5 ];
    ptr[ 0 ] = UINT2NUM( settings->DepthBits );
    ptr[ 1 ] = UINT2NUM( settings->StencilBits );
    ptr[ 2 ] = UINT2NUM( settings->AntialiasingLevel );
    ptr[ 3 ] = UINT2NUM( settings->MajorVersion );
    ptr[ 4 ] = UINT2NUM( settings->MinorVersion );
    return rb_ary_new4( 5, ptr );
}

// ContextSettings#marshal_load(data)
VALUE rbContextSettings::MarshalLoad( VALUE aSelf, VALUE aData )
{
    sf::ContextSettings* settings = rbContextSettings::ToSFML( aSelf );
    
    VALUE* ptr = RARRAY_PTR( aData );
    settings->DepthBits         = NUM2UINT( ptr[ 0 ] );
    settings->StencilBits       = NUM2UINT( ptr[ 1 ] );
    settings->AntialiasingLevel = NUM2UINT( ptr[ 2 ] );
    settings->MajorVersion      = NUM2UINT( ptr[ 3 ] );
    settings->MinorVersion      = NUM2UINT( ptr[ 4 ] );
    return Qnil;
}

// ContextSettings#depth_bits
// ContextSettings#DepthBits
VALUE rbContextSettings::GetDepthBits( VALUE aSelf )
{
    return UINT2NUM( rbContextSettings::ToSFML( aSelf )->DepthBits );
}

// ContextSettings#stencil_bits
// ContextSettings#StencilBits
VALUE rbContextSettings::GetStencilBits( VALUE aSelf )
{
    return UINT2NUM( rbContextSettings::ToSFML( aSelf )->StencilBits );
}

// ContextSettings#antialiasing_level
// ContextSettings#AntialiasingLevel
VALUE rbContextSettings::GetAntialiasingLevel( VALUE aSelf )
{
    return UINT2NUM( rbContextSettings::ToSFML( aSelf )->AntialiasingLevel );
}

// ContextSettings#major_version
// ContextSettings#MajorVersion
VALUE rbContextSettings::GetMajorVersion( VALUE aSelf )
{
    return UINT2NUM( rbContextSettings::ToSFML( aSelf )->MajorVersion );
}

// ContextSettings#minor_version
// ContextSettings#MinorVersion
VALUE rbContextSettings::GetMinorVersion( VALUE aSelf )
{
    return UINT2NUM( rbContextSettings::ToSFML( aSelf )->MinorVersion );
}

// ContextSettings#depth_bits=(value)
// ContextSettings#DepthBits=(value)
VALUE rbContextSettings::SetDepthBits( VALUE aSelf, VALUE aValue )
{
    rb_check_frozen( aSelf );
    rbContextSettings::ToSFML( aSelf )->DepthBits = NUM2UINT( aValue );
    return Qnil;
}

// ContextSettings#stencil_bits=(value)
// ContextSettings#StencilBits=(value)
VALUE rbContextSettings::SetStencilBits( VALUE aSelf, VALUE aValue )
{
    rb_check_frozen( aSelf );
    rbContextSettings::ToSFML( aSelf )->StencilBits = NUM2UINT( aValue );
    return Qnil;
}

// ContextSettings#antialiasing_level=(value)
// ContextSettings#AntialiasingLevel=(value)
VALUE rbContextSettings::SetAntialiasingLevel( VALUE aSelf, VALUE aValue )
{
    rb_check_frozen( aSelf );
    rbContextSettings::ToSFML( aSelf )->AntialiasingLevel = NUM2UINT( aValue );
    return Qnil;
}

// ContextSettings#major_version=(value)
// ContextSettings#MajorVersion=(value)
VALUE rbContextSettings::SetMajorVersion( VALUE aSelf, VALUE aValue )
{
    rb_check_frozen( aSelf );
    rbContextSettings::ToSFML( aSelf )->MajorVersion = NUM2UINT( aValue );
    return Qnil;
}

// ContextSettings#minor_version=(value)
// ContextSettings#MinorVersion=(value)
VALUE rbContextSettings::SetMinorVersion( VALUE aSelf, VALUE aValue )
{
    rb_check_frozen( aSelf );
    rbContextSettings::ToSFML( aSelf )->MinorVersion = NUM2UINT( aValue );
    return Qnil;
}

// ContextSettings#==(other)
// ContextSettings#eql?(other)
// ContextSettings#equal?(other)
VALUE rbContextSettings::Equal( VALUE aSelf, VALUE anOther )
{
    if( CLASS_OF( aSelf ) != CLASS_OF( anOther ) ) return Qfalse;
    sf::ContextSettings* left = rbContextSettings::ToSFML( aSelf );
    sf::ContextSettings* right = rbContextSettings::ToSFML( anOther );
    
    if( left->DepthBits         != right->DepthBits         ) return Qfalse;
    if( left->StencilBits       != right->StencilBits       ) return Qfalse;
    if( left->AntialiasingLevel != right->AntialiasingLevel ) return Qfalse;
    if( left->MajorVersion      != right->MajorVersion      ) return Qfalse;
    if( left->MinorVersion      != right->MinorVersion      ) return Qfalse;
    
    return Qtrue;
}

// ContextSettings#inspect
// ContextSettings#to_s
VALUE rbContextSettings::Inspect( VALUE aSelf )
{
    sf::ContextSettings* settings = rbContextSettings::ToSFML( aSelf );
    return rb_sprintf( "%s(depth_bits: %u, stencil_bits: %u, "
                       "antialiasing_level: %u, major_version: %u, "
                       "minor_version: %u)",
                       rb_obj_classname( aSelf ),
                       settings->DepthBits,
                       settings->StencilBits,
                       settings->AntialiasingLevel,
                       settings->MajorVersion,
                       settings->MinorVersion );
}

// ContextSettings#memory_usage
VALUE rbContextSettings::GetMemoryUsage( VALUE aSelf )
{
    return SIZET2NUM( sizeof( sf::ContextSettings ) );
}
