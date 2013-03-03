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

#ifndef GRAPHICS_VERTEX_ARRAY_HPP
#define GRAPHICS_VERTEX_ARRAY_HPP

#include <ruby.h>
#include <rbSFML.hpp>

#include <SFML/Graphics/VertexArray.hpp>

namespace rbVertexArray
{
#if defined( GRAPHICS_VERTEX_ARRAY_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_VERTEX_ARRAY_CPP )
    // VertexArray#initialize
	// VertexArray#initialize(primitive_type, vertex_count = 0)
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );
	
	// VertexArray#initialize_copy(source)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aSource );
	
	// VertexArray#vertex_count
	static VALUE GetVertexCount( VALUE aSelf );
	
	// VertexArray#append(vertex)
	static VALUE Append( VALUE aSelf, VALUE aVertex );
	
	// VertexArray#[index]
	static VALUE IndexOperator( VALUE aSelf, VALUE anIndex );
	
	// VertexArray#clear
	static VALUE Clear( VALUE aSelf );
	
	// VertexArray#resize(vertex_count)
	static VALUE Resize( VALUE aSelf, VALUE aVertexCount );
	
	// VertexArray#primitive_type=(type)
	static VALUE SetPrimitiveType( VALUE aSelf, VALUE aType );
	
	// VertexArray#primitive_type
	static VALUE GetPrimitiveType( VALUE aSelf );
	
	// VertexArray#bounds
	static VALUE GetBounds( VALUE aSelf );
	
	// VertexArray#draw(render_target, render_states)
	static VALUE Draw( VALUE aSelf, VALUE aRenderTarget, VALUE aRenderStates );
	
    // VertexArray#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // VertexArray#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // VertexArray#inspect
    // VertexArray#to_s
    static VALUE Inspect( VALUE aSelf );
#endif
}

#endif // GRAPHICS_VERTEX_ARRAY_HPP
