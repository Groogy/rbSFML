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

#ifndef GRAPHICS_RENDER_TEXTURE_HPP
#define GRAPHICS_RENDER_TEXTURE_HPP

#include <ruby.h>

#include "../rbSFML.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

namespace rbRenderTexture
{
#if defined( GRAPHICS_RENDER_TEXTURE_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_RENDER_TEXTURE_CPP )

    // RenderTexture#initialize
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );
	
	// RenderTexture#size
	// RenderTexture#get_size
	// RenderTexture#getSize
	static VALUE GetSize( VALUE aSelf );
	
	// RenderTexture#create(width, height, depth_buffer=false)
	static VALUE Create( int argc, VALUE* args, VALUE aSelf );
	
	// RenderTexture#smooth=(flag)
	// RenderTexture#set_smooth(flag)
	// RenderTexture#setSmooth(flag)
	static VALUE SetSmooth( VALUE aSelf, VALUE aFlag );
	
	// RenderTexture#smooth?
	// RenderTexture#is_smooth?
	// RenderTexture#is_smooth
	// RenderTexture#isSmooth
	static VALUE IsSmooth( VALUE aSelf );
	
	// RenderTexture#active=(flag=true)
	// RenderTexture#set_active(flag=true)
	// RenderTexture#setActive(flag=true)
	static VALUE SetActive( int argc, VALUE* args, VALUE aSelf );
	
	// RenderTexture#display
	static VALUE Display( VALUE aSelf );
	
	// RenderTexture#texture
	// RenderTexture#get_texture
	// RenderTexture#getTexture
	static VALUE GetTexture( VALUE aSelf );
	
    // RenderTexture#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // RenderTexture#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // RenderTexture#inspect
    // RenderTexture#to_s
    static VALUE Inspect( VALUE aSelf );
#endif
}

#endif // GRAPHICS_RENDER_TEXTURE_HPP
