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

#ifndef GRAPHICS_RENDER_TARGET_HPP
#define GRAPHICS_RENDER_TARGET_HPP

#include <ruby.h>
#include <rbSFML.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace rbRenderTarget
{
	static inline sf::RenderTarget* ToSFML( VALUE aValue );

#if defined( GRAPHICS_RENDER_TARGET_CPP )
    VALUE Module;
#else
    extern VALUE Module;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_RENDER_TARGET_CPP )
    // RenderTarget#initialize
    static VALUE Initialize( VALUE aSelf );
	
	// RenderTarget#initialize_copy(source)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSource );
	
    // RenderTarget#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // RenderTarget#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // RenderTarget#inspect
    // RenderTarget#to_s
    static VALUE Inspect( VALUE aSelf );

    // RenderTarget#memory_usage
    static VALUE GetMemoryUsage( VALUE aSelf );
#endif
}

sf::RenderTarget* rbRenderTarget::ToSFML( VALUE aValue )
{
	aValue = rbMacros::ToRuby( aValue, rbRenderTarget::Module );
	char* compensationPtr = reinterpret_cast< char* >( DATA_PTR( aValue ) );
    unsigned int ptrOffset = FIX2UINT( rb_iv_get( aValue, "@__internal__render_target_offset" ) );
	return reinterpret_cast< sf::RenderTarget* >( compensationPtr + ptrOffset );
}

#endif // GRAPHICS_RENDER_TARGET_HPP
