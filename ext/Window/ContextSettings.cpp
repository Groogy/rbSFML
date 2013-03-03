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
    ext_define_method( rbContextSettings::Class, "initialize",          rbContextSettings::Initialize,           -1 );
    ext_define_method( rbContextSettings::Class, "initialize_copy",     rbContextSettings::InitializeCopy,        1 );
    ext_define_method( rbContextSettings::Class, "marshal_dump",        rbContextSettings::MarshalDump,           0 );
    ext_define_method( rbContextSettings::Class , "marshal_load",       rbContextSettings::MarshalLoad,           1 );
    ext_define_method( rbContextSettings::Class, "depth_bits",          rbContextSettings::GetDepthBits,          0 );
    ext_define_method( rbContextSettings::Class, "stencil_bits",        rbContextSettings::GetStencilBits,        0 );
    ext_define_method( rbContextSettings::Class, "antialiasing_level",  rbContextSettings::GetAntialiasingLevel,  0 );
    ext_define_method( rbContextSettings::Class, "major_version",       rbContextSettings::GetMajorVersion,       0 );
    ext_define_method( rbContextSettings::Class, "minor_version",       rbContextSettings::GetMinorVersion,       0 );
    ext_define_method( rbContextSettings::Class, "depth_bits=",         rbContextSettings::SetDepthBits,          1 );
    ext_define_method( rbContextSettings::Class, "stencil_bits=",       rbContextSettings::SetStencilBits,        1 );
    ext_define_method( rbContextSettings::Class, "antialiasing_level=", rbContextSettings::SetAntialiasingLevel,  1 );
    ext_define_method( rbContextSettings::Class, "major_version=",      rbContextSettings::SetMajorVersion,       1 );
    ext_define_method( rbContextSettings::Class, "minor_version=",      rbContextSettings::SetMinorVersion,       1 );
    ext_define_method( rbContextSettings::Class, "==",                  rbContextSettings::Equal,                 1 );
    ext_define_method( rbContextSettings::Class, "inspect",             rbContextSettings::Inspect,               0 );
    
    // Instance aliasses
    rb_define_alias( rbContextSettings::Class, "depthBits",          "depth_bits"          );
    rb_define_alias( rbContextSettings::Class, "stencilBits",        "stencil_bits"        );
    rb_define_alias( rbContextSettings::Class, "antialiasingLevel",  "antialiasing_level"  );
    rb_define_alias( rbContextSettings::Class, "majorVersion",       "major_version"       );
    rb_define_alias( rbContextSettings::Class, "minorVersion",       "minor_version"       );
    rb_define_alias( rbContextSettings::Class, "depthBits=",         "depth_bits="         );
    rb_define_alias( rbContextSettings::Class, "stencilBits=",       "stencil_bits="       );
    rb_define_alias( rbContextSettings::Class, "antialiasingLevel=", "antialiasing_level=" );
    rb_define_alias( rbContextSettings::Class, "majorVersion=",      "major_version="      );
    rb_define_alias( rbContextSettings::Class, "minorVersion=",      "minor_version="      );
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
            settings->minorVersion = NUM2UINT( argv[ 4 ] );
        case 4:
            settings->majorVersion = NUM2UINT( argv[ 3 ] );
        case 3:
            settings->antialiasingLevel = NUM2UINT( argv[ 2 ] );
        case 2:
            settings->stencilBits = NUM2UINT( argv[ 1 ] );
        case 1:
            settings->depthBits = NUM2UINT( argv[ 0 ] );
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
    ptr[ 0 ] = UINT2NUM( settings->depthBits );
    ptr[ 1 ] = UINT2NUM( settings->stencilBits );
    ptr[ 2 ] = UINT2NUM( settings->antialiasingLevel );
    ptr[ 3 ] = UINT2NUM( settings->majorVersion );
    ptr[ 4 ] = UINT2NUM( settings->minorVersion );
    return rb_ary_new4( 5, ptr );
}

// ContextSettings#marshal_load(data)
VALUE rbContextSettings::MarshalLoad( VALUE aSelf, VALUE aData )
{
    sf::ContextSettings* settings = rbContextSettings::ToSFML( aSelf );
    
    VALUE* ptr = RARRAY_PTR( aData );
    settings->depthBits         = NUM2UINT( ptr[ 0 ] );
    settings->stencilBits       = NUM2UINT( ptr[ 1 ] );
    settings->antialiasingLevel = NUM2UINT( ptr[ 2 ] );
    settings->majorVersion      = NUM2UINT( ptr[ 3 ] );
    settings->minorVersion      = NUM2UINT( ptr[ 4 ] );
    return Qnil;
}

// ContextSettings#depth_bits
// ContextSettings#septhBits
VALUE rbContextSettings::GetDepthBits( VALUE aSelf )
{
    return UINT2NUM( rbContextSettings::ToSFML( aSelf )->depthBits );
}

// ContextSettings#stencil_bits
// ContextSettings#stencilBits
VALUE rbContextSettings::GetStencilBits( VALUE aSelf )
{
    return UINT2NUM( rbContextSettings::ToSFML( aSelf )->stencilBits );
}

// ContextSettings#antialiasing_level
// ContextSettings#antialiasingLevel
VALUE rbContextSettings::GetAntialiasingLevel( VALUE aSelf )
{
    return UINT2NUM( rbContextSettings::ToSFML( aSelf )->antialiasingLevel );
}

// ContextSettings#major_version
// ContextSettings#majorVersion
VALUE rbContextSettings::GetMajorVersion( VALUE aSelf )
{
    return UINT2NUM( rbContextSettings::ToSFML( aSelf )->majorVersion );
}

// ContextSettings#minor_version
// ContextSettings#minorVersion
VALUE rbContextSettings::GetMinorVersion( VALUE aSelf )
{
    return UINT2NUM( rbContextSettings::ToSFML( aSelf )->minorVersion );
}

// ContextSettings#depth_bits=(value)
// ContextSettings#depthBits=(value)
VALUE rbContextSettings::SetDepthBits( VALUE aSelf, VALUE aValue )
{
    rb_check_frozen( aSelf );
    rbContextSettings::ToSFML( aSelf )->depthBits = NUM2UINT( aValue );
    return Qnil;
}

// ContextSettings#stencil_bits=(value)
// ContextSettings#stencilBits=(value)
VALUE rbContextSettings::SetStencilBits( VALUE aSelf, VALUE aValue )
{
    rb_check_frozen( aSelf );
    rbContextSettings::ToSFML( aSelf )->stencilBits = NUM2UINT( aValue );
    return Qnil;
}

// ContextSettings#antialiasing_level=(value)
// ContextSettings#antialiasingLevel=(value)
VALUE rbContextSettings::SetAntialiasingLevel( VALUE aSelf, VALUE aValue )
{
    rb_check_frozen( aSelf );
    rbContextSettings::ToSFML( aSelf )->antialiasingLevel = NUM2UINT( aValue );
    return Qnil;
}

// ContextSettings#major_version=(value)
// ContextSettings#majorVersion=(value)
VALUE rbContextSettings::SetMajorVersion( VALUE aSelf, VALUE aValue )
{
    rb_check_frozen( aSelf );
    rbContextSettings::ToSFML( aSelf )->majorVersion = NUM2UINT( aValue );
    return Qnil;
}

// ContextSettings#minor_version=(value)
// ContextSettings#minorVersion=(value)
VALUE rbContextSettings::SetMinorVersion( VALUE aSelf, VALUE aValue )
{
    rb_check_frozen( aSelf );
    rbContextSettings::ToSFML( aSelf )->minorVersion = NUM2UINT( aValue );
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
    
    if( left->depthBits         != right->depthBits         ) return Qfalse;
    if( left->stencilBits       != right->stencilBits       ) return Qfalse;
    if( left->antialiasingLevel != right->antialiasingLevel ) return Qfalse;
    if( left->majorVersion      != right->majorVersion      ) return Qfalse;
    if( left->minorVersion      != right->minorVersion      ) return Qfalse;
    
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
                       settings->depthBits,
                       settings->stencilBits,
                       settings->antialiasingLevel,
                       settings->majorVersion,
                       settings->minorVersion );
}
