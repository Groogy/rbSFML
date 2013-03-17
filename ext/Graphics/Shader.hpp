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

#ifndef GRAPHICS_SHADER_HPP
#define GRAPHICS_SHADER_HPP

#include <ruby.h>

#include "../rbSFML.hpp"

#include <SFML/Graphics/Shader.hpp>

namespace rbShader
{
#if defined( GRAPHICS_SHADER_CPP )
    VALUE Class;
	VALUE Class_CurrentTextureType;
#else
    extern VALUE Class;
	extern VALUE Class_CurrentTextureType;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_SHADER_CPP )
	// Shader.available?
	// Shader.is_available?
	// Shader.is_available
	// Shader.isAvailable
	static VALUE IsAvailable( VALUE aSelf );

	// Shader.bind
	// Shader.bind(shader)
	static VALUE Bind( int argc, VALUE* args, VALUE aSelf );

    // Shader#initialize
	// Shader#initialize(vertex_filename, fragment_filename)
	// Shader#initialize(shader_filename, shader_type)
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );
	
	// Shader#load_from_file(filename, type)
	// Shader#load_from_file(vertex_filename, fragment_filename)
	// Shader#loadFromFile(filename, type)
	// Shader#loadFromFile(vertex_filename, fragment_filename)
	static VALUE LoadFromFile( VALUE aSelf, VALUE anArg1, VALUE anArg2 );
	
	// Shader#load_from_memory(data, type)
	// Shader#load_from_memory(vertex_data, fragment_data)
	// Shader#loadFromMemory(data, type)
	// Shader#loadFromMemory(vertex_data, fragment_data)
	static VALUE LoadFromMemory( VALUE aSelf, VALUE anArg1, VALUE anArg2 );
	
	// Shader#load_from_stream(stream, type)
	// Shader#load_from_stream(vertex_stream, fragment_stream)
	// Shader#loadFromStream(data, type)
	// Shader#loadFromStream(vertex_data, fragment_data)
	static VALUE LoadFromStream( VALUE aSelf, VALUE anArg1, VALUE anArg2 );
	
	// Shader#set_parameter(name, x)
	// Shader#set_parameter(name, x, y)
	// Shader#set_parameter(name, x, y, z)
	// Shader#set_parameter(name, vector2)
	// Shader#set_parameter(name, vector3)
	// Shader#set_parameter(name, color)
	// Shader#set_parameter(name, transform)
	// Shader#set_parameter(name, texture)
	// Shader#set_parameter(name, current_texture)
	// Shader#setParameter(name, x)
	// Shader#setParameter(name, x, y)
	// Shader#setParameter(name, x, y, z)
	// Shader#setParameter(name, vector2)
	// Shader#setParameter(name, vector3)
	// Shader#setParameter(name, color)
	// Shader#setParameter(name, transform)
	// Shader#setParameter(name, texture)
	// Shader#setParameter(name, current_texture)
	// Shader#[]=(name, x)
	// Shader#[]=(name, vector2)
	// Shader#[]=(name, vector3)
	// Shader#[]=(name, color)
	// Shader#[]=(name, transform)
	// Shader#[]=(name, texture)
	// Shader#[]=(name, current_texture)
	static VALUE SetParameter( int argc, VALUE* args, VALUE aSelf );
	
    // Shader#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Shader#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Shader#inspect
    // Shader#to_s
    static VALUE Inspect( VALUE aSelf );
#endif
}

#endif // GRAPHICS_SHADER_HPP
