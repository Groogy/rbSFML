/* rbSFML
 * Copyright (c) 2012 Henrik Valter Vogelius Hansson - groogy@groogy.se
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

#define GRAPHICS_RENDER_TEXTURE_CPP

#include "RenderTexture.hpp"
#include "RenderTarget.hpp"
#include "Texture.hpp"
#include "../System/Vector2.hpp"

void rbRenderTexture::Init( VALUE SFML )
{
    rbRenderTexture::Class = rb_define_class_under( SFML, "RenderTexture", rb_cObject );
	rb_include_module( rbRenderTexture::Class, rbRenderTarget::Module );
	
	// Class methods
	rb_define_alloc_func( rbRenderTexture::Class, rbMacros::Allocate< sf::RenderTexture > );

    // Instance methods
    ext_define_method( rbRenderTexture::Class, "initialize",             rbRenderTexture::Initialize,          -1 );
	ext_define_method( rbRenderTexture::Class, "get_size",               rbRenderTexture::GetSize,              0 );
	ext_define_method( rbRenderTexture::Class, "create",                 rbRenderTexture::Create,              -1 );
	ext_define_method( rbRenderTexture::Class, "set_smooth",             rbRenderTexture::SetSmooth,            1 );
	ext_define_method( rbRenderTexture::Class, "is_smooth?",             rbRenderTexture::IsSmooth,             0 );
	ext_define_method( rbRenderTexture::Class, "set_active",             rbRenderTexture::SetActive,           -1 );
	ext_define_method( rbRenderTexture::Class, "display",                rbRenderTexture::Display,              0 );
	ext_define_method( rbRenderTexture::Class, "get_texture",            rbRenderTexture::GetTexture,           0 );
    ext_define_method( rbRenderTexture::Class, "marshal_dump",           rbRenderTexture::MarshalDump,          0 );
    ext_define_method( rbRenderTexture::Class, "==",                     rbRenderTexture::Equal,                1 );
    ext_define_method( rbRenderTexture::Class, "inspect",                rbRenderTexture::Inspect,              0 );

    // Instance aliases
    rb_define_alias( rbRenderTexture::Class, "to_s",         "inspect"       );
	rb_define_alias( rbRenderTexture::Class, "size",         "get_size"      );
	rb_define_alias( rbRenderTexture::Class, "getSize",      "get_size"      );
	rb_define_alias( rbRenderTexture::Class, "smooth=",      "set_smooth"    );
	rb_define_alias( rbRenderTexture::Class, "setSmooth",    "set_smooth"    );
	rb_define_alias( rbRenderTexture::Class, "smooth?",      "is_smooth?"    );
	rb_define_alias( rbRenderTexture::Class, "is_smooth",    "is_smooth?"    );
	rb_define_alias( rbRenderTexture::Class, "isSmooth",     "is_smooth?"    );
	rb_define_alias( rbRenderTexture::Class, "active=",      "set_active"    );
	rb_define_alias( rbRenderTexture::Class, "setActive",    "set_active"    );
	rb_define_alias( rbRenderTexture::Class, "getTexture",   "get_texture"   );
	rb_define_alias( rbRenderTexture::Class, "texture",      "get_texture"   );
}

// RenderTexture#initialize
VALUE rbRenderTexture::Initialize( int argc, VALUE* args, VALUE aSelf )
{
	rb_iv_set( aSelf, "@__internal__render_target_offset", INT2FIX( 0 ) );
	if( argc > 0 )
		Create( argc, args, aSelf );
		
    return Qnil;
}

// RenderTexture#size
// RenderTexture#get_size
// RenderTexture#getSize
VALUE rbRenderTexture::GetSize( VALUE aSelf )
{
	return rbVector2::ToRuby( rbMacros::ToSFML< sf::RenderTexture >( aSelf, rbRenderTexture::Class )->getSize() );
}

// RenderTexture#create(width, height, depth_buffer=false)
VALUE rbRenderTexture::Create( int argc, VALUE* args, VALUE aSelf )
{
	bool useDepth = false;
	bool result = false;
	switch( argc )
	{
	case 3:
		useDepth = RTEST( args[ 2 ] );
	case 2:
#ifdef SFML_GROOGY_EXTENSION
		result = rbMacros::ToSFML< sf::RenderTexture >( aSelf, rbRenderTexture::Class )->create( NUM2UINT( args[ 0 ] ), NUM2UINT( args[ 1 ] ), sf::TextureFormat::RGBA8, useDepth );
#else
		result = rbMacros::ToSFML< sf::RenderTexture >( aSelf, rbRenderTexture::Class )->create( NUM2UINT( args[ 0 ] ), NUM2UINT( args[ 1 ] ), useDepth );
#endif
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "2 or 3" );
	}
	
	return RBOOL( result );
}

// RenderTexture#smooth=(flag)
// RenderTexture#set_smooth(flag)
// RenderTexture#setSmooth(flag)
VALUE rbRenderTexture::SetSmooth( VALUE aSelf, VALUE aFlag )
{
	rbMacros::ToSFML< sf::RenderTexture >( aSelf, rbRenderTexture::Class )->setSmooth( RTEST( aFlag ) );
	return Qnil;
}

// RenderTexture#smooth?
// RenderTexture#is_smooth?
// RenderTexture#is_smooth
// RenderTexture#isSmooth
VALUE rbRenderTexture::IsSmooth( VALUE aSelf )
{
	return RBOOL( rbMacros::ToSFML< sf::RenderTexture >( aSelf, rbRenderTexture::Class )->isSmooth() );
}

// RenderTexture#active=(flag)
// RenderTexture#set_active(flag)
// RenderTexture#setActive(flag)
VALUE rbRenderTexture::SetActive( int argc, VALUE* args, VALUE aSelf )
{
	bool flag = false;
	switch( argc )
	{
	case 1:
		flag = RTEST( args[ 0 ] );
	case 0:
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "0 or 1" );
	}
	
	bool result = rbMacros::ToSFML< sf::RenderTexture >( aSelf, rbRenderTexture::Class )->setActive( flag );
	return RBOOL( result );
}

// RenderTexture#display
VALUE rbRenderTexture::Display( VALUE aSelf )
{
	rbMacros::ToSFML< sf::RenderTexture >( aSelf, rbRenderTexture::Class )->display();
	return Qnil;
}

// RenderTexture#texture
// RenderTexture#get_texture
// RenderTexture#getTexture
VALUE rbRenderTexture::GetTexture( VALUE aSelf )
{
	const sf::Texture& texture = rbMacros::ToSFML< sf::RenderTexture >( aSelf, rbRenderTexture::Class )->getTexture();
	VALUE object = rbMacros::ToRubyNoGC( const_cast< sf::Texture* >( &texture ), rbTexture::Class );
	rb_iv_set( object, "@__ref__owner", aSelf );
	rb_obj_freeze( object );
	return object;
}

// RenderTexture#marshal_dump
VALUE rbRenderTexture::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
	return Qnil;
}

// RenderTexture#==(other)
VALUE rbRenderTexture::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbRenderTexture::Class ) )
		return Qfalse;
    else if( rbMacros::ToSFML< sf::RenderTexture >( aSelf, rbRenderTexture::Class ) == rbMacros::ToSFML< sf::RenderTexture >( anOther, rbRenderTexture::Class ) )
		return Qtrue;
	else
		return Qfalse;
}

// RenderTexture#inspect
// RenderTexture#to_s
VALUE rbRenderTexture::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%ix%i, %p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::RenderTexture >( aSelf, rbRenderTexture::Class )->getSize().x,
					   rbMacros::ToSFML< sf::RenderTexture >( aSelf, rbRenderTexture::Class )->getSize().y,
					   rbMacros::ToSFML< sf::RenderTexture >( aSelf, rbRenderTexture::Class ) );
}
