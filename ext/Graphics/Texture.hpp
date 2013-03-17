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

#ifndef GRAPHICS_TEXTURE_HPP
#define GRAPHICS_TEXTURE_HPP

#include <ruby.h>

#include "../rbSFML.hpp"

#include <SFML/Graphics/Texture.hpp>

namespace rbTexture
{
#if defined( GRAPHICS_TEXTURE_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_TEXTURE_CPP )
	// Texture.maximum_size
	static VALUE GetMaximumSize( VALUE aSelf );

	// Texture.bind
	// Texture.bind(coordinate_type = Normalized)
	static VALUE Bind( int argc, VALUE* args, VALUE aSelf );

    // Texture#initialize
	// Texture#initialize(filename)
	// Texture#initialize(width, height)
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // Texture#initialize_copy(texture)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aTexture );
	
	// Texture#create(width, height)
	static VALUE Create( VALUE aSelf, VALUE aWidth, VALUE aHeight );
	
	// Texture#load_from_file(filename, area = nil)
	// Texture#loadFromFile(filename, area = nil)
	static VALUE LoadFromFile( int argc, VALUE* args, VALUE aSelf );
	
	// Texture#load_from_memory(data, area = nil)
	// Texture#loadFromMemory(data, area = nil)
	static VALUE LoadFromMemory( int argc, VALUE* args, VALUE aSelf );
	
	// Texture#load_from_stream(stream, area = nil)
	// Texture#loadFromStream(stream, area = nil)
	static VALUE LoadFromStream( int argc, VALUE* args, VALUE aSelf );
	
	// Texture#load_from_image(image, area = nil)
	// Texture#loadFromImage(image, area = nil)
	static VALUE LoadFromImage( int argc, VALUE* args, VALUE aSelf );
	
	// Texture#size
	// Texture#get_size
	// Texture#getSize
	static VALUE GetSize( VALUE aSelf );
	
	// Texture#copy_to_image
	// Texture#to_image
	// Texture#copyToImage
	static VALUE CopyToImage( VALUE aSelf );
	
	// Texture#update(pixels)
	// Texture#update(pixels, width, height, x, y)
	// Texture#update(image)
	// Texture#update(image, x, y)
	// Texture#update(window)
	// Texture#update(window, x, y)
	static VALUE Update( int argc, VALUE* args, VALUE aSelf );
	
	// Texture#smooth=(flag)
	// Texture#setSmooth=(flag)
	static VALUE SetSmooth( VALUE aSelf, VALUE aFlag );
	
	// Texture#smooth?
	// Texture#is_smooth?
	// Texture#is_smooth
	// Texture#isSmooth
	static VALUE GetSmooth( VALUE aSelf );
	
	// Texture#repeated=(flag)
	// Texture#set_repeated(flag)
	// Texture#setRepeated=(flag)
	static VALUE SetRepeated( VALUE aSelf, VALUE aFlag );
	
	// Texture#repeated?
	// Texture#is_repeated?
	// Texture#is_repeated
	// Texture#isRepeated
	static VALUE GetRepeated( VALUE aSelf );
	
    // Texture#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Texture#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Texture#inspect
    // Texture#to_s
    static VALUE Inspect( VALUE aSelf );
#endif
}

#endif // GRAPHICS_TEXTURE_HPP
