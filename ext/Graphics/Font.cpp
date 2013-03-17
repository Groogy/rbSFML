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

#define GRAPHICS_FONT_CPP

#include "Font.hpp"
#include "Glyph.hpp"
#include "Texture.hpp"
#include "../InputStream.hpp"
#include "../System/SFML.hpp"

void rbFont::Init( VALUE SFML )
{
    rbFont::Class = rb_define_class_under( SFML, "Font", rb_cObject );
	
	// Class methods
	rb_define_alloc_func( rbFont::Class, rbMacros::Allocate< sf::Font > );

    // Instance methods
    ext_define_method( rbFont::Class, "initialize",             rbFont::Initialize,          -1 );
    ext_define_method( rbFont::Class, "initialize_copy",        rbFont::InitializeCopy,       1 );
	ext_define_method( rbFont::Class, "load_from_file",	       rbFont::LoadFromFile,         1 );
	ext_define_method( rbFont::Class, "load_from_memory",       rbFont::LoadFromMemory,       1 );
	ext_define_method( rbFont::Class, "load_from_stream",       rbFont::LoadFromStream,       1 );
	ext_define_method( rbFont::Class, "get_glyph",              rbFont::GetGlyph,             3 );
	ext_define_method( rbFont::Class, "get_kerning",            rbFont::GetKerning,           3 );
	ext_define_method( rbFont::Class, "get_line_spacing",       rbFont::GetLineSpacing,       1 );
	ext_define_method( rbFont::Class, "get_texture",            rbFont::GetTexture,           1 );
    ext_define_method( rbFont::Class, "marshal_dump",           rbFont::MarshalDump,          0 );
    ext_define_method( rbFont::Class, "==",                     rbFont::Equal,                1 );
    ext_define_method( rbFont::Class, "inspect",                rbFont::Inspect,              0 );

    // Instance aliases
	rb_define_alias( rbFont::Class, "loadFromFile",   "load_from_file"   );
	rb_define_alias( rbFont::Class, "load_file",      "load_from_file"   );
	rb_define_alias( rbFont::Class, "load",           "load_from_file"   );
	rb_define_alias( rbFont::Class, "loadFromMemory", "load_from_memory" );
	rb_define_alias( rbFont::Class, "load_memory",    "load_from_memory" );
	rb_define_alias( rbFont::Class, "loadFromStream", "load_from_stream" );
	rb_define_alias( rbFont::Class, "load_stream",    "load_from_stream" );
	rb_define_alias( rbFont::Class, "getGlyph",       "get_glyph"        );
	rb_define_alias( rbFont::Class, "getKerning",     "get_kerning"      );
	rb_define_alias( rbFont::Class, "getLineSpacing", "get_line_spacing" );
	rb_define_alias( rbFont::Class, "getTexture",     "get_texture"      );
    rb_define_alias( rbFont::Class, "to_s",           "inspect"          );
}

// Font#initialize
// Font#initialize(filename)
VALUE rbFont::Initialize( int argc, VALUE* args, VALUE aSelf )
{
	if( argc == 1 )
		rbFont::LoadFromFile( aSelf, args[ 0 ] );
	else if( argc != 0 )
		INVALID_ARGUMENT_LIST( argc, "0 or 1" );
		
    return Qnil;
}

// Font#initialize_copy(font)
VALUE rbFont::InitializeCopy( VALUE aSelf, VALUE aFont )
{
    *rbMacros::ToSFML< sf::Font >( aSelf, rbFont::Class ) = *rbMacros::ToSFML< sf::Font >( aFont, rbFont::Class );
    return aSelf;
}

// Font#load_from_file(filename)
// Font#load_file(filename)
// Font#loadFromFile(filename)
// Font#load(filename)
VALUE rbFont::LoadFromFile( VALUE aSelf, VALUE aFilename )
{
	rb_check_frozen( aSelf );
	
	rbSFML::PrepareErrorStream();
	bool result = rbMacros::ToSFML< sf::Font >( aSelf, rbFont::Class )->loadFromFile( StringValueCStr( aFilename ) );
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Font#load_from_memory(data)
// Font#load_memory(data)
// Font#loadFromMemory(data)
VALUE rbFont::LoadFromMemory( VALUE aSelf, VALUE someData )
{
	rb_check_frozen( aSelf );
	
	rbSFML::PrepareErrorStream();
	bool result = rbMacros::ToSFML< sf::Font >( aSelf, rbFont::Class )->loadFromMemory( RSTRING_PTR( someData ), RSTRING_LEN( someData ) );
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Font#load_from_stream(stream)
// Font#load_stream(stream)
// Font#loadFromStream(stream)
VALUE rbFont::LoadFromStream( VALUE aSelf, VALUE aStream )
{
	rb_check_frozen( aSelf );

	rbInputStream stream( aStream );
	rbSFML::PrepareErrorStream();
	bool result = rbMacros::ToSFML< sf::Font >( aSelf, rbFont::Class )->loadFromStream( stream );
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Font#get_glyph(code_point, character_size, bold)
// Font#getGlyph(code_point, character_size, bold)
VALUE rbFont::GetGlyph( VALUE aSelf, VALUE aCodePoint, VALUE aCharacterSize, VALUE aBoldFlag )
{
	const sf::Glyph& glyph = rbMacros::ToSFML< sf::Font >( aSelf, rbFont::Class )->getGlyph( NUM2UINT( aCodePoint ), NUM2UINT( aCharacterSize ),
																							 RTEST( aBoldFlag ) );
		
	VALUE glyphObj = rbGlyph::ToRuby( glyph );
	rb_obj_freeze( glyphObj );
	return glyphObj;
}

// Font#get_kerning(first, second, character_size)
// Font#getKerning(first, second, character_size)
VALUE rbFont::GetKerning( VALUE aSelf, VALUE aFirst, VALUE aSecond, VALUE aCharacterSize )
{
	return INT2NUM( rbMacros::ToSFML< sf::Font >( aSelf, rbFont::Class )->getKerning( NUM2UINT( aFirst ), NUM2UINT( aSecond ), NUM2UINT( aCharacterSize ) ) );
}

// Font#get_line_spacing(character_size)
// Font#getLineSpacing(character_size)
VALUE rbFont::GetLineSpacing( VALUE aSelf, VALUE aCharacterSize )
{
	return INT2NUM( rbMacros::ToSFML< sf::Font >( aSelf, rbFont::Class )->getLineSpacing( NUM2UINT( aCharacterSize ) ) );
}

// Font#get_texture(character_size)
// Font#getTexture(character_size)
VALUE rbFont::GetTexture( VALUE aSelf, VALUE aCharacterSize )
{
	const sf::Texture& texture = rbMacros::ToSFML< sf::Font >( aSelf, rbFont::Class )->getTexture( NUM2UINT( aCharacterSize ) );
	return rbMacros::ToConstRuby( &texture, rbTexture::Class );
}

// Font#marshal_dump
VALUE rbFont::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
	return Qnil;
}

// Font#==(other)
VALUE rbFont::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbFont::Class ) )
		return Qfalse;
    else if( rbMacros::ToSFML< sf::Font >( aSelf, rbFont::Class ) == rbMacros::ToSFML< sf::Font >( anOther, rbFont::Class ) )
		return Qtrue;
	else
		return Qfalse;
}

// Font#inspect
// Font#to_s
VALUE rbFont::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::Font >( aSelf, rbFont::Class ) );
}
