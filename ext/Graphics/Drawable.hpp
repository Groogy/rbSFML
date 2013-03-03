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

#ifndef GRAPHICS_DRAWABLE_HPP
#define GRAPHICS_DRAWABLE_HPP

#include <ruby.h>
#include <rbSFML.hpp>

#include <SFML/Graphics/Drawable.hpp>

namespace rbDrawable
{
	static inline sf::Drawable* ToSFML( VALUE aValue );

#if defined( GRAPHICS_DRAWABLE_CPP )
    VALUE Module;
#else
    extern VALUE Module;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_DRAWABLE_CPP )
    // Drawable#initialize
    static VALUE Initialize( VALUE aSelf );
	
	// Drawable#initialize_copy(source)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSource );
	
	// Drawable#draw(render_target, render_states)
	static VALUE Draw( VALUE aSelf, VALUE aRenderTarget, VALUE aRenderStates );
	
    // Drawable#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Drawable#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Drawable#inspect
    // Drawable#to_s
    static VALUE Inspect( VALUE aSelf );
#endif
}

sf::Drawable* rbDrawable::ToSFML( VALUE aValue )
{
	aValue = rbMacros::ToRuby( aValue, rbDrawable::Module );
	char* compensationPtr = reinterpret_cast< char* >( DATA_PTR( aValue ) );
	unsigned int ptrOffset = 0;
	VALUE offset = rb_iv_get( aValue, "@__internal__drawable_offset" );
	if( offset != Qnil )
		ptrOffset = FIX2UINT( offset );
	return reinterpret_cast< sf::Drawable* >( compensationPtr + ptrOffset );
}

#endif // GRAPHICS_DRAWABLE_HPP
