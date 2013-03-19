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

#ifndef GRAPHICS_SPRITE_HPP
#define GRAPHICS_SPRITE_HPP

#include <ruby.h>

#include "../rbSFML.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace rbSprite
{
#if defined( GRAPHICS_SPRITE_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_SPRITE_CPP )
    // Sprite#initialize
	// Sprite#initialize(texture)
	// Sprite#initialize(texture, rect)
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // Sprite#initialize_copy(source)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSource );
	
	// Sprite#texture
	// Sprite#get_texture
	// Sprite#getTexture
	static VALUE GetTexture( VALUE aSelf );
	
	// Sprite#texture=(texture)
	// Sprite#set_texture(texture, reset_rect=false)
	// Sprite#setTexture(texture, reset_rect=false)
	static VALUE SetTexture( int argc, VALUE* args, VALUE aSelf );
	
	// Sprite#texture_rect=(rect)
	// Sprite#set_texture_rect(rect)
	// Sprite#setTextureRect(rect)
	static VALUE SetTextureRect( VALUE aSelf, VALUE aRect );
	
	// Sprite#texture_rect
	// Sprite#get_texture_rect
	// Sprite#getTextureRect
	static VALUE GetTextureRect( VALUE aSelf );
	
	// Sprite#color=(color)
	// Sprite#set_color(color)
	// Sprite#setColor(color)
	static VALUE SetColor( VALUE aSelf, VALUE aColor );
	
	// Sprite#color
	// Sprite#get_color
	// Sprite#getColor
	static VALUE GetColor( VALUE aSelf );
	
	// Sprite#local_bounds
	// Sprite#get_local_bounds
	// Sprite#getLocalBounds
	static VALUE GetLocalBounds( VALUE aSelf );
	
	// Sprite#global_bounds
	// Sprite#get_global_bounds
	// Sprite#getGlobalBounds
	static VALUE GetGlobalBounds( VALUE aSelf );

    // Sprite#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Sprite#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Sprite#inspect
    // Sprite#to_s
    static VALUE Inspect( VALUE aSelf );
#endif

}

#endif // GRAPHICS_SPRITE_HPP
