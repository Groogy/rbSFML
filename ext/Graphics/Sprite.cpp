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

#define GRAPHICS_SPRITE_CPP

#include "Sprite.hpp"
#include "Drawable.hpp"
#include "Transformable.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "Rect.hpp"
#include "Color.hpp"

void rbSprite::Init( VALUE SFML )
{
    rbSprite::Class = rb_define_class_under( SFML, "Sprite", rb_cObject );
	rb_include_module( rbSprite::Class, rbDrawable::Module );
	rb_include_module( rbSprite::Class, rbTransformable::Module );
	
	// Class methods
	rb_define_alloc_func( rbSprite::Class, rbMacros::Allocate< sf::Sprite > );

    // Instance methods
    ext_define_method( rbSprite::Class, "initialize",        rbSprite::Initialize,     	-1 );
    ext_define_method( rbSprite::Class, "initialize_copy",   rbSprite::InitializeCopy, 	 1 );
	ext_define_method( rbSprite::Class, "get_texture",       rbSprite::GetTexture, 		 0 );
	ext_define_method( rbSprite::Class, "set_texture",	     rbSprite::SetTexture,		-1 );
	ext_define_method( rbSprite::Class, "get_texture_rect",  rbSprite::GetTextureRect, 	 0 );
	ext_define_method( rbSprite::Class, "set_texture_rect",  rbSprite::SetTextureRect, 	 1 );
	ext_define_method( rbSprite::Class, "get_color",         rbSprite::GetColor,       	 0 );
	ext_define_method( rbSprite::Class, "set_color",         rbSprite::SetColor,       	 1 );
	ext_define_method( rbSprite::Class, "get_local_bounds",  rbSprite::GetLocalBounds, 	 0 );
	ext_define_method( rbSprite::Class, "get_global_bounds", rbSprite::GetGlobalBounds,	 0 );
    ext_define_method( rbSprite::Class, "marshal_dump",      rbSprite::MarshalDump,    	 0 );
    ext_define_method( rbSprite::Class, "==",                rbSprite::Equal,          	 1 );
    ext_define_method( rbSprite::Class, "inspect",           rbSprite::Inspect,        	 0 );

    // Instance aliases
	rb_define_alias( rbSprite::Class, "to_s",            "inspect"           );
	rb_define_alias( rbSprite::Class, "texture",         "get_texture"       );
	rb_define_alias( rbSprite::Class, "getTexture",      "get_texture"       );
	rb_define_alias( rbSprite::Class, "texture=",        "set_texture"       );
	rb_define_alias( rbSprite::Class, "setTexture",      "set_texture"       );
	rb_define_alias( rbSprite::Class, "texture_rect",    "get_texture_rect"  );
	rb_define_alias( rbSprite::Class, "getTextureRect",  "get_texture_rect"  );
	rb_define_alias( rbSprite::Class, "texture_rect=",   "set_texture_rect"  );
	rb_define_alias( rbSprite::Class, "setTextureRect",  "set_texture_rect"  );
	rb_define_alias( rbSprite::Class, "color",           "get_color"         );
	rb_define_alias( rbSprite::Class, "getColor",        "get_color"         );
	rb_define_alias( rbSprite::Class, "color=",          "set_color"         );
	rb_define_alias( rbSprite::Class, "setColor",        "set_color"         );
	rb_define_alias( rbSprite::Class, "local_bounds",    "get_local_bounds"  );
	rb_define_alias( rbSprite::Class, "getLocalBounds",  "get_local_bounds"  );
	rb_define_alias( rbSprite::Class, "global_bounds",   "get_global_bounds" );
	rb_define_alias( rbSprite::Class, "getGlobalBounds", "get_global_bounds" );
}

// Sprite#initialize
// Sprite#initialize(texture)
// Sprite#initialize(texture, rect)
VALUE rbSprite::Initialize( int argc, VALUE* args, VALUE aSelf )
{
	switch( argc )
	{
	case 0:
		break;
	case 2:
		rbMacros::ToSFML< sf::Sprite >( aSelf, rbSprite::Class )->setTextureRect( rbRect::ToSFMLi( args[ 1 ] ) );
	case 1:
		rbMacros::ToSFML< sf::Sprite >( aSelf, rbSprite::Class )->setTexture( *rbMacros::ToSFML< sf::Texture >( args[ 0 ], rbTexture::Class ) );
		rb_iv_set( aSelf, "@__ref__texture", args[ 0 ] );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "0..2" );
	}
	
	rb_iv_set( aSelf, "@__internal__drawable_offset", INT2FIX( 0 ) );
	rb_iv_set( aSelf, "@__internal__transformable_offset", INT2FIX( sizeof( sf::Drawable ) ) );
	
    return Qnil;
}

// Sprite#initialize_copy(source)
VALUE rbSprite::InitializeCopy( VALUE aSelf, VALUE aSource )
{
	*rbMacros::ToSFML< sf::Sprite >( aSelf, rbSprite::Class ) = *rbMacros::ToSFML< sf::Sprite >( aSource, rbSprite::Class );
	rb_iv_set( aSelf, "@__ref__texture", rb_iv_get( aSource, "@__ref__texture" ) );
    return aSelf;
}

// Sprite#texture
// Sprite#get_texture
// Sprite#getTexture
VALUE rbSprite::GetTexture( VALUE aSelf )
{
	return rb_iv_get( aSelf, "@__ref__texture" );
}

// Sprite#texture=(texture)
// Sprite#set_texture(texture, reset_rect=false)
// Sprite#setTexture(texture, reset_rect=false)
VALUE rbSprite::SetTexture( int argc, VALUE* args, VALUE aSelf )
{
	bool reset = false;
	switch( argc )
	{
	case 2:
		reset = RTEST( args[ 1 ] );
	case 1:
		rbMacros::ToSFML< sf::Sprite >( aSelf, rbSprite::Class )->setTexture( *rbMacros::ToSFML< sf::Texture >( args[ 0 ], rbTexture::Class ), reset );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	rb_iv_set( aSelf, "@__ref__texture", args[ 0 ] );
	return Qnil;
}
 
// Sprite#texture_rect=(rect)
// Sprite#set_texture_rect(rect)
// Sprite#setTextureRect(rect)
VALUE rbSprite::SetTextureRect( VALUE aSelf, VALUE aRect )
{
	rbMacros::ToSFML< sf::Sprite >( aSelf, rbSprite::Class )->setTextureRect( rbRect::ToSFMLi( aRect ) );
	return Qnil;
}

// Sprite#texture_rect
// Sprite#get_texture_rect
// Sprite#getTextureRect
VALUE rbSprite::GetTextureRect( VALUE aSelf )
{
	return rbRect::ToRuby( rbMacros::ToSFML< sf::Sprite >( aSelf, rbSprite::Class )->getTextureRect() );
}

// Sprite#color=(color)
// Sprite#set_color(color)
// Sprite#setColor(color)
VALUE rbSprite::SetColor( VALUE aSelf, VALUE aColor )
{
	rbMacros::ToSFML< sf::Sprite >( aSelf, rbSprite::Class )->setColor( rbColor::ToSFML( aColor ) );
	return Qnil;
}

// Sprite#color
// Sprite#get_color
// Sprite#getColor
VALUE rbSprite::GetColor( VALUE aSelf )
{
	return rbColor::ToRuby( rbMacros::ToSFML< sf::Sprite >( aSelf, rbSprite::Class )->getColor() );
}

// Sprite#local_bounds
// Sprite#get_local_bounds
// Sprite#getLocalBounds
VALUE rbSprite::GetLocalBounds( VALUE aSelf )
{
	return rbRect::ToRuby( rbMacros::ToSFML< sf::Sprite >( aSelf, rbSprite::Class )->getLocalBounds() );
}

// Sprite#global_bounds
// Sprite#get_global_bounds
// Sprite#getGlobalBounds
VALUE rbSprite::GetGlobalBounds( VALUE aSelf )
{
	return rbRect::ToRuby( rbMacros::ToSFML< sf::Sprite >( aSelf, rbSprite::Class )->getGlobalBounds() );
}

// Sprite#marshal_dump
VALUE rbSprite::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
    return Qnil; 
}

// Sprite#==(other)
VALUE rbSprite::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbSprite::Class ) ) return Qfalse;
    if( !RTEST( rbMacros::ToSFML< sf::Sprite >( aSelf, rbSprite::Class ) != rbMacros::ToSFML< sf::Sprite >( anOther, rbSprite::Class ) ) ) return Qfalse;
    return Qtrue;
}

// Sprite#inspect
// Sprite#to_s
VALUE rbSprite::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::Sprite >( aSelf, rbSprite::Class ) );
}
