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

#define GRAPHICS_TEXT_CPP

#include "Text.hpp"
#include "Drawable.hpp"
#include "Transformable.hpp"
#include "Transform.hpp"
#include "Font.hpp"
#include "Rect.hpp"
#include "Color.hpp"
#include "../System/Vector2.hpp"

void rbText::Init( VALUE SFML )
{
    rbText::Class = rb_define_class_under( SFML, "Text", rb_cObject );
	rb_include_module( rbText::Class, rbDrawable::Module );
	rb_include_module( rbText::Class, rbTransformable::Module );
	
	// Class methods
	rb_define_alloc_func( rbText::Class, rbMacros::Allocate< sf::Text > );

    // Instance methods
    ext_define_method( rbText::Class, "initialize",         rbText::Initialize,      -1 );
    ext_define_method( rbText::Class, "initialize_copy",    rbText::InitializeCopy,   1 );
	ext_define_method( rbText::Class, "get_color",          rbText::GetColor,         0 );
	ext_define_method( rbText::Class, "set_color",          rbText::SetColor,         1 );
	ext_define_method( rbText::Class, "get_string",         rbText::GetString,        0 );
	ext_define_method( rbText::Class, "set_string",         rbText::SetString,        1 );
	ext_define_method( rbText::Class, "get_font",           rbText::GetFont,          0 );
	ext_define_method( rbText::Class, "set_font",           rbText::SetFont,          1 );
	ext_define_method( rbText::Class, "get_character_size", rbText::GetCharacterSize, 0 );
	ext_define_method( rbText::Class, "set_character_size", rbText::SetCharacterSize, 1 );
	ext_define_method( rbText::Class, "get_style",          rbText::GetStyle,         0 );
	ext_define_method( rbText::Class, "set_style",          rbText::SetStyle,         1 );
	ext_define_method( rbText::Class, "find_character_pos", rbText::FindCharacterPos, 1 );
	ext_define_method( rbText::Class, "get_local_bounds",   rbText::GetLocalBounds,   0 );
	ext_define_method( rbText::Class, "get_global_bounds",  rbText::GetGlobalBounds,  0 );
    ext_define_method( rbText::Class, "marshal_dump",       rbText::MarshalDump,      0 );
    ext_define_method( rbText::Class, "==",                 rbText::Equal,            1 );
    ext_define_method( rbText::Class, "inspect",            rbText::Inspect,          0 );

    // Instance aliases
	rb_define_alias( rbText::Class, "to_s",             "inspect"            );
	rb_define_alias( rbText::Class, "color",            "get_color"          );
	rb_define_alias( rbText::Class, "getColor",         "get_color"          );
	rb_define_alias( rbText::Class, "color=",           "set_color"          );
	rb_define_alias( rbText::Class, "setColor",         "set_color"          );
	rb_define_alias( rbText::Class, "string",           "get_string"         );
	rb_define_alias( rbText::Class, "getString",        "get_string"         );
	rb_define_alias( rbText::Class, "string=",          "set_string"         );
	rb_define_alias( rbText::Class, "setString",        "set_string"         );
	rb_define_alias( rbText::Class, "font",             "get_font"           );
	rb_define_alias( rbText::Class, "getFont",          "get_font"           );
	rb_define_alias( rbText::Class, "font=",            "set_font"           );
	rb_define_alias( rbText::Class, "setFont",          "set_font"           );
	rb_define_alias( rbText::Class, "character_size",   "get_character_size" );
	rb_define_alias( rbText::Class, "getCharacterSize", "get_character_size" );
	rb_define_alias( rbText::Class, "character_size=",  "set_character_size" );
	rb_define_alias( rbText::Class, "setCharacterSize", "set_character_size" );
	rb_define_alias( rbText::Class, "style",            "get_style"          );
	rb_define_alias( rbText::Class, "getStyle",         "get_style"          );
	rb_define_alias( rbText::Class, "style=",           "set_style"          );
	rb_define_alias( rbText::Class, "setStyle",         "set_style"          );
	rb_define_alias( rbText::Class, "findCharacterPos", "find_character_pos" );
	rb_define_alias( rbText::Class, "local_bounds",     "get_local_bounds"   );
	rb_define_alias( rbText::Class, "getLocalBounds",   "get_local_bounds"   );
	rb_define_alias( rbText::Class, "global_bounds",    "get_global_bounds"  );
	rb_define_alias( rbText::Class, "getGlobalBounds",  "get_global_bounds"  );
}

// Text#initialize
// Text#initialize(string, font=SFML::Font.default_font, character_size=30)
VALUE rbText::Initialize( int argc, VALUE* args, VALUE aSelf )
{
	rb_iv_set( aSelf, "@__ref__font", Qnil );
	
	switch( argc )
	{
	case 3:
		rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class )->setCharacterSize( NUM2INT( args[ 2 ] ) );
	case 2:
		rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class )->setFont( *rbMacros::ToSFML< sf::Font >( args[ 1 ], rbFont::Class ) );
		rb_iv_set( aSelf, "@__ref__font", args[ 1 ] );
	case 1:
		rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class )->setString( StringValueCStr( args[ 0 ] ) );
	case 0:
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "0..3" );
	}
	
	rb_iv_set( aSelf, "@__internal__drawable_offset", INT2FIX( 0 ) );
	rb_iv_set( aSelf, "@__internal__transformable_offset", INT2FIX( sizeof( sf::Drawable ) ) );
	
    return Qnil;
}

// Text#initialize_copy(source)
VALUE rbText::InitializeCopy( VALUE aSelf, VALUE aSource )
{
	*rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class ) = *rbMacros::ToSFML< sf::Text >( aSource, rbText::Class );
	rb_iv_set( aSelf, "@__ref__font", rb_iv_get( aSource, "@__ref__font" ) );
    return aSelf;
}

// Text#color=(color)
// Text#set_color(color)
// Text#setColor(color)
VALUE rbText::SetColor( VALUE aSelf, VALUE aColor )
{
	rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class )->setColor( rbColor::ToSFML( aColor ) );
	return Qnil;
}

// Text#color
// Text#get_color
// Text#getColor
VALUE rbText::GetColor( VALUE aSelf )
{
	return rbColor::ToRuby( rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class )->getColor() );
}

// Text#string=(string)
// Text#set_string(string)
// Text#setString(string)
VALUE rbText::SetString( VALUE aSelf, VALUE aString )
{
	rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class )->setString( StringValueCStr( aString ) );
	return Qnil;
}

// Text#string
// Text#get_string
// Text#getString
VALUE rbText::GetString( VALUE aSelf )
{
	sf::Text *text = rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class );
	return rb_str_new( text->getString().toAnsiString().c_str(), text->getString().getSize() );
}

// Text#font=(font)
// Text#set_font(font)
// Text#setfont(font)
VALUE rbText::SetFont( VALUE aSelf, VALUE aFont )
{
	rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class )->setFont( *rbMacros::ToSFML< sf::Font >( aFont, rbFont::Class ) );
	rb_iv_set( aSelf, "@__ref__font", aFont );
	return Qnil;
}

// Text#font
// Text#get_font
// Text#getfont
VALUE rbText::GetFont( VALUE aSelf )
{
	return rb_iv_get( aSelf, "@__ref__font" );
}

// Text#character_size=(size)
// Text#set_character_size(size)
// Text#setCharacterSize(size)
VALUE rbText::SetCharacterSize( VALUE aSelf, VALUE aSize )
{
	rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class )->setCharacterSize( NUM2UINT( aSize ) );
	return Qnil;
}

// Text#character_size
// Text#get_character_size
// Text#getCharacterSize
VALUE rbText::GetCharacterSize( VALUE aSelf )
{
	return INT2FIX( rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class )->getCharacterSize() );
}

// Text#style=(style)
// Text#set_style(style)
// Text#setStyle(style)
VALUE rbText::SetStyle( VALUE aSelf, VALUE aStyle )
{
	rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class )->setStyle( NUM2UINT( aStyle ) );
	return Qnil;
}

// Text#style
// Text#get_style
// Text#getStyle
VALUE rbText::GetStyle( VALUE aSelf )
{
	return INT2FIX( rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class )->getStyle() );
}

// Text#find_character_pos(index)
// Text#findCharacterPos(index)
VALUE rbText::FindCharacterPos( VALUE aSelf, VALUE anIndex )
{
	return rbVector2::ToRuby( rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class )->findCharacterPos( NUM2UINT( anIndex ) ) );
}

// Text#local_bounds
// Text#get_local_bounds
// Text#getLocalBounds
VALUE rbText::GetLocalBounds( VALUE aSelf )
{
	return rbRect::ToRuby( rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class )->getLocalBounds() );
}

// Text#global_bounds
// Text#get_global_bounds
// Text#getGlobalBounds
VALUE rbText::GetGlobalBounds( VALUE aSelf )
{
	return rbRect::ToRuby( rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class )->getGlobalBounds() );
}

// Text#marshal_dump
VALUE rbText::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
    return Qnil; 
}

// Text#==(other)
VALUE rbText::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbText::Class ) ) return Qfalse;
    if( !RTEST( rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class ) != rbMacros::ToSFML< sf::Text >( anOther, rbText::Class ) ) ) return Qfalse;
    return Qtrue;
}

// Text#inspect
// Text#to_s
VALUE rbText::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::Text >( aSelf, rbText::Class ) );
}
