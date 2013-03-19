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

#define GRAPHICS_RENDER_WINDOW_CPP

#include "RenderWindow.hpp"
#include "RenderTarget.hpp"
#include "Image.hpp"
#include "../Window/Window.hpp"

void rbRenderWindow::Init( VALUE SFML )
{
    rbRenderWindow::Class = rb_define_class_under( SFML, "RenderWindow", rbWindow::Class );
	rb_include_module( rbRenderWindow::Class, rbRenderTarget::Module );
	
	// Class methods
	rb_define_alloc_func( rbRenderWindow::Class, rbMacros::Allocate< sf::RenderWindow > );

    // Instance methods
    ext_define_method( rbRenderWindow::Class, "initialize",             rbRenderWindow::Initialize,          -1 );
	ext_define_method( rbRenderWindow::Class, "get_size",               rbRenderWindow::GetSize,              0 );
	ext_define_method( rbRenderWindow::Class, "capture",                rbRenderWindow::Capture,              0 );
    ext_define_method( rbRenderWindow::Class, "marshal_dump",           rbRenderWindow::MarshalDump,          0 );
    ext_define_method( rbRenderWindow::Class, "==",                     rbRenderWindow::Equal,                1 );
    ext_define_method( rbRenderWindow::Class, "inspect",                rbRenderWindow::Inspect,              0 );

    // Instance aliases
    rb_define_alias( rbRenderWindow::Class, "to_s",         "inspect"       );
	rb_define_alias( rbRenderWindow::Class, "size",         "get_size"      );
	rb_define_alias( rbRenderWindow::Class, "getSize",      "get_size"      );
}

// RenderWindow#initialize
VALUE rbRenderWindow::Initialize( int argc, VALUE* args, VALUE aSelf )
{
	rb_iv_set( aSelf, "@__internal__render_target_offset", INT2FIX( sizeof( sf::Window ) ) );
    return rb_call_super( argc, args );
}

// RenderWindow#size
// RenderWindow#get_size
// RenderWindow#getSize
VALUE rbRenderWindow::GetSize( VALUE aSelf )
{
	return rbVector2::ToRuby( rbMacros::ToSFML< sf::RenderWindow >( aSelf, rbRenderWindow::Class )->getSize() );
}

// RenderWindow#capture
VALUE rbRenderWindow::Capture( VALUE aSelf )
{
	sf::Image* image = new sf::Image();
	VALUE imageObj = rbMacros::ToRuby( image, rbImage::Class );
	*image = rbMacros::ToSFML< sf::RenderWindow >( aSelf, rbWindow::Class )->capture();
	return imageObj;
}

// RenderWindow#marshal_dump
VALUE rbRenderWindow::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
	return Qnil;
}

// RenderWindow#==(other)
VALUE rbRenderWindow::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbRenderWindow::Class ) )
		return Qfalse;
    else if( rbMacros::ToSFML< sf::RenderWindow >( aSelf, rbRenderWindow::Class ) == rbMacros::ToSFML< sf::RenderWindow >( anOther, rbRenderWindow::Class ) )
		return Qtrue;
	else
		return Qfalse;
}

// RenderWindow#inspect
// RenderWindow#to_s
VALUE rbRenderWindow::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%ix%i, %p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::RenderWindow >( aSelf, rbRenderWindow::Class )->getSize().x,
					   rbMacros::ToSFML< sf::RenderWindow >( aSelf, rbRenderWindow::Class )->getSize().y,
					   rbMacros::ToSFML< sf::RenderWindow >( aSelf, rbRenderWindow::Class ) );
}
