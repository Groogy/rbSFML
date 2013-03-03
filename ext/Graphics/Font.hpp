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

#ifndef GRAPHICS_FONT_HPP
#define GRAPHICS_FONT_HPP

#include <ruby.h>
#include <rbSFML.hpp>

#include <SFML/Graphics/Font.hpp>

namespace rbFont
{
#if defined( GRAPHICS_FONT_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_FONT_CPP )
    // Font#initialize
	// Font#initialize(filename)
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // Font#initialize_copy(font)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aFont );
	
	// Font#load_from_file(filename)
	// Font#load_file(filename)
	// Font#loadFromFile(filename)
	// Font#load(filename)
	static VALUE LoadFromFile( VALUE aSelf, VALUE aFilename );
	
	// Font#load_from_memory(data)
	// Font#load_memory(data)
	// Font#loadFromMemory(data)
	static VALUE LoadFromMemory( VALUE aSelf, VALUE someData );
	
	// Font#load_from_stream(stream)
	// Font#load_stream(stream)
	// Font#loadFromStream(stream)
	static VALUE LoadFromStream( VALUE aSelf, VALUE aStream );
	
	// Font#get_glyph(code_point, character_size, bold)
	// Font#getGlyph(code_point, character_size, bold)
	static VALUE GetGlyph( VALUE aSelf, VALUE aCodePoint, VALUE aCharacterSize, VALUE aBoldFlag );
	
	// Font#get_kerning(first, second, character_size)
	// Font#getKerning(first, second, character_size)
	static VALUE GetKerning( VALUE aSelf, VALUE aFirst, VALUE aSecond, VALUE aCharacterSize );
	
	// Font#get_line_spacing(character_size)
	// Font#getLineSpacing(character_size)
	static VALUE GetLineSpacing( VALUE aSelf, VALUE aCharacterSize );
	
	// Font#get_texture(character_size)
	// Font#getTexture(character_size)
	static VALUE GetTexture( VALUE aSelf, VALUE aCharacterSize );
	
    // Font#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Font#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Font#inspect
    // Font#to_s
    static VALUE Inspect( VALUE aSelf );
#endif
}

#endif // GRAPHICS_FONT_HPP
