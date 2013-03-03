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

#ifndef GRAPHICS_SHAPE_HPP
#define GRAPHICS_SHAPE_HPP

#include <ruby.h>
#include <rbSFML.hpp>

#include <SFML/Graphics/Shape.hpp>

namespace rbShape
{
#if defined( GRAPHICS_SHAPE_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_SHAPE_CPP )
    // Shape#initialize
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // Shape#initialize_copy(source)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSource );
	
	// Shape#texture
	// Shape#get_texture
	// Shape#getTexture
	static VALUE GetTexture( VALUE aSelf );
	
	// Shape#texture=(texture)
	// Shape#set_texture(texture, reset_rect=false)
	// Shape#setTexture(texture, reset_rect=false)
	static VALUE SetTexture( int argc, VALUE* args, VALUE aSelf );
	
	// Shape#texture_rect=(rect)
	// Shape#set_texture_rect(rect)
	// Shape#setTextureRect(rect)
	static VALUE SetTextureRect( VALUE aSelf, VALUE aRect );
	
	// Shape#texture_rect
	// Shape#get_texture_rect
	// Shape#getTextureRect
	static VALUE GetTextureRect( VALUE aSelf );
	
	// Shape#fill_color=(color)
	// Shape#set_fill_color(color)
	// Shape#setFillColor(color)
	static VALUE SetFillColor( VALUE aSelf, VALUE aColor );
	
	// Shape#fill_color
	// Shape#get_fill_color
	// Shape#getFillColor
	static VALUE GetFillColor( VALUE aSelf );
	
	// Shape#outline_color=(color)
	// Shape#set_outline_color(color)
	// Shape#setOutlineColor(color)
	static VALUE SetOutlineColor( VALUE aSelf, VALUE aColor );
	
	// Shape#outline_color
	// Shape#get_outline_color
	// Shape#getOutlineColor
	static VALUE GetOutlineColor( VALUE aSelf );
	
	// Shape#outline_thickness=(thickness)
	// Shape#set_outline_thickness(thickness)
	// Shape#setOutlineThickness(thickness)
	static VALUE SetOutlineThickness( VALUE aSelf, VALUE aThickness );
	
	// Shape#outline_thickness
	// Shape#get_outline_thickness
	// Shape#getOutlineThickness
	static VALUE GetOutlineThickness( VALUE aSelf );
	
	// Shape#point_count
	// Shape#get_point_count
	// Shape#getPointCount
	static VALUE GetPointCount( VALUE aSelf );
	
	// Shape#get_point(index)
	// Shape#getPoint(index)
	static VALUE GetPoint( VALUE aSelf, VALUE anIndex );
	
	// Shape#local_bounds
	// Shape#get_local_bounds
	// Shape#getLocalBounds
	static VALUE GetLocalBounds( VALUE aSelf );
	
	// Shape#global_bounds
	// Shape#get_global_bounds
	// Shape#getGlobalBounds
	static VALUE GetGlobalBounds( VALUE aSelf );

    // Shape#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Shape#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Shape#inspect
    // Shape#to_s
    static VALUE Inspect( VALUE aSelf );
#endif

}

#endif // GRAPHICS_SPRITE_HPP
