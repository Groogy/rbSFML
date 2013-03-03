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

#ifndef GRAPHICS_TEXT_HPP
#define GRAPHICS_TEXT_HPP

#include <ruby.h>
#include <rbSFML.hpp>

#include <SFML/Graphics/Text.hpp>

namespace rbText
{
#if defined( GRAPHICS_TEXT_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_TEXT_CPP )
    // Text#initialize
	// Text#initialize(string, font=SFML::Font.default_font, character_size=30)
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // Text#initialize_copy(source)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSource );
	
	// Text#string=(string)
	// Text#set_string(string)
	// Text#setString(string)
	static VALUE SetString( VALUE aSelf, VALUE aString );
	
	// Text#string
	// Text#get_string
	// Text#getString
	static VALUE GetString( VALUE aSelf );
	
	// Text#font=(font)
	// Text#set_font(font)
	// Text#setFont(font)
	static VALUE SetFont( VALUE aSelf, VALUE aFont );
	
	// Text#font
	// Text#get_font
	// Text#getFont
	static VALUE GetFont( VALUE aSelf );
	
	// Text#character_size=(size)
	// Text#set_character_size(size)
	// Text#setCharacterSize(size)
	static VALUE SetCharacterSize( VALUE aSelf, VALUE aSize );
	
	// Text#character_size
	// Text#get_character_size
	// Text#getCharacterSize
	static VALUE GetCharacterSize( VALUE aSelf );
	
	// Text#style=(style)
	// Text#set_style(style)
	// Text#setStyle(style)
	static VALUE SetStyle( VALUE aSelf, VALUE aStyle );
	
	// Text#style
	// Text#get_style
	// Text#getStyle
	static VALUE GetStyle( VALUE aSelf );
	
	// Text#color=(color)
	// Text#set_color(color)
	// Text#setColor(color)
	static VALUE SetColor( VALUE aSelf, VALUE aColor );
	
	// Text#color
	// Text#get_color
	// Text#getColor
	static VALUE GetColor( VALUE aSelf );
	
	// Text#find_character_pos(index)
	// Text#findCharacterPos(index)
	static VALUE FindCharacterPos( VALUE aSelf, VALUE anIndex );
	
	// Text#local_bounds
	// Text#get_local_bounds
	// Text#getLocalBounds
	static VALUE GetLocalBounds( VALUE aSelf );
	
	// Text#global_bounds
	// Text#get_global_bounds
	// Text#getGlobalBounds
	static VALUE GetGlobalBounds( VALUE aSelf );

    // Text#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Text#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Text#inspect
    // Text#to_s
    static VALUE Inspect( VALUE aSelf );
#endif

}

#endif // GRAPHICS_TEXT_HPP
