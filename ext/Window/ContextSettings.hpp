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

#ifndef WINDOW_CONTEXTSETTINGS_HPP
#define WINDOW_CONTEXTSETTINGS_HPP

#include <ruby.h>
#include <ruby/st.h>

#include "../rbSFML.hpp"
#include "../System/SFML.hpp"

#include <string>

#include <SFML/Window/ContextSettings.hpp>

namespace rbContextSettings
{
	static inline VALUE ToRuby( VALUE anOther );
	static inline VALUE ToRuby( sf::ContextSettings* someSettings );
	static inline sf::ContextSettings* ToSFML( VALUE someSettings );
	
#if defined( WINDOW_CONTEXTSETTINGS_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif
    
#if defined( RBSFML_WINDOW ) || defined( RBSFML_SFML )
    void Init( VALUE SFML );
#endif
    
#if defined( WINDOW_CONTEXTSETTINGS_CPP )
    // ContextSettings#initialize(...)
    static VALUE Initialize( int argc, VALUE argv[], VALUE aSelf );
    
    // ContextSettings#initialize_copy(settings)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSettings );
    
    // ContextSettings#marshal_dump
    static VALUE MarshalDump( VALUE aSelf);
    
    // ContextSettings#marshal_load(data)
    static VALUE MarshalLoad( VALUE aSelf, VALUE aData );
    
    // ContextSettings#depth_bits
    // ContextSettings#depthBits
    static VALUE GetDepthBits( VALUE aSelf );
    
    // ContextSettings#stencil_bits
    // ContextSettings#stencilBits
    static VALUE GetStencilBits( VALUE aSelf );
    
    // ContextSettings#antialiasing_level
    // ContextSettings#antialiasingLevel
    static VALUE GetAntialiasingLevel( VALUE aSelf );
    
    // ContextSettings#major_version
    // ContextSettings#majorVersion
    static VALUE GetMajorVersion( VALUE aSelf );
    
    // ContextSettings#minor_version
    // ContextSettings#minorVersion
    static VALUE GetMinorVersion( VALUE aSelf );
    
    // ContextSettings#depth_bits=(value)
    // ContextSettings#depthBits=(value)
    static VALUE SetDepthBits( VALUE aSelf, VALUE aValue );
    
    // ContextSettings#stencil_bits=(value)
    // ContextSettings#stencilBits=(value)
    static VALUE SetStencilBits( VALUE aSelf, VALUE aValue );
    
    // ContextSettings#antialiasing_level=(value)
    // ContextSettings#antialiasingLevel=(value)
    static VALUE SetAntialiasingLevel( VALUE aSelf, VALUE aValue );
    
    // ContextSettings#major_version=(value)
    // ContextSettings#MajorVersion=(value)
    static VALUE SetMajorVersion( VALUE aSelf, VALUE aValue );
    
    // ContextSettings#minor_version=(value)
    // ContextSettings#minorVersion=(value)
    static VALUE SetMinorVersion( VALUE aSelf, VALUE aValue );
    
    // ContextSettings#==(other)
    // ContextSettings#eql?(other)
    // ContextSettings#equal?(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );
    
    // ContextSettings#inspect
    // ContextSettings#to_s
    static VALUE Inspect( VALUE aSelf );
#endif
    
}

// Internal
struct ToRubyHashInfo
{
    sf::ContextSettings* instance;
    const char* klass;
};

// Internal
static int ToRubyHashIterator( VALUE aKey, VALUE aValue, VALUE anExtra )
{
    ToRubyHashInfo* info = ( ToRubyHashInfo* )anExtra;
    
    std::string sym;
    if( rb_type( aKey ) == T_SYMBOL )
        sym = rb_id2name( SYM2ID( aKey ) );
    else
        sym = StringValueCStr( aKey );
    
    if( sym == "depth_bits" or sym == "DepthBits" )
        info->instance->depthBits = NUM2UINT( aValue );
    else if( sym == "stencil_bits" or sym == "StencilBits" )
        info->instance->stencilBits = NUM2UINT( aValue );
    else if( sym == "antialiasing_level" or sym == "AntialiasingLevel" )
        info->instance->antialiasingLevel = NUM2UINT( aValue );
    else if( sym == "major_version" or sym == "MajorVersion" )
        info->instance->majorVersion = NUM2UINT( aValue );
    else if( sym == "minor_version" or sym == "MinorVersion" )
        info->instance->minorVersion = NUM2UINT( aValue );
    else
        rb_raise( rb_eArgError,
                  "unknown attribute %s for %s", sym.c_str(), info->klass );
                 
    return ST_CONTINUE;
}

VALUE rbContextSettings::ToRuby( VALUE anOther )
{    
    if( rb_obj_is_kind_of( anOther, rbContextSettings::Class ) )
        return anOther;
    
    if( rb_type( anOther ) == T_HASH )
    {
        ToRubyHashInfo info;
        info.instance = rbMacros::Allocate< sf::ContextSettings >();
        info.klass = rb_class2name( rbContextSettings::Class );
        rb_hash_foreach( anOther, reinterpret_cast< int(*)(...) >( ToRubyHashIterator ), reinterpret_cast< VALUE >( &info ) );  
        return rbContextSettings::ToRuby( info.instance );
    }
    
    rb_raise( rb_eTypeError, "can't convert %s into %s",
              rb_obj_classname( anOther ), rb_class2name( rbContextSettings::Class ) );
}

VALUE rbContextSettings::ToRuby( sf::ContextSettings* someSettings )
{    
    return rb_data_object_alloc( rbContextSettings::Class, someSettings, NULL, rbMacros::Free< sf::ContextSettings* > );
}

sf::ContextSettings* rbContextSettings::ToSFML( VALUE someSettings )
{
    someSettings = rbContextSettings::ToRuby( someSettings );
    return ( sf::ContextSettings* )DATA_PTR( someSettings );
}

#endif // WINDOW_CONTEXTSETTINGS_HPP
