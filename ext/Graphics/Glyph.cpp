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

#define GRAPHICS_GLYPH_CPP

#include "Glyph.hpp"

void rbGlyph::Init( VALUE SFML )
{
    rbGlyph::Class = rb_define_class_under( SFML, "Glyph", rb_cObject );

    // Instance methods
    ext_define_method( rbGlyph::Class, "initialize",      rbGlyph::Initialize,      0 );
    ext_define_method( rbGlyph::Class, "initialize_copy", rbGlyph::InitializeCopy,  1 );
    ext_define_method( rbGlyph::Class, "marshal_dump",    rbGlyph::MarshalDump,     0 );
    ext_define_method( rbGlyph::Class, "marshal_load",    rbGlyph::MarshalLoad,     1 );
    ext_define_method( rbGlyph::Class, "==",              rbGlyph::Equal,           1 );
    ext_define_method( rbGlyph::Class, "inspect",         rbGlyph::Inspect,         0 );

    // Attribute accessors
    rb_define_attr( rbGlyph::Class, "advance", true, true );
    rb_define_attr( rbGlyph::Class, "bounds", true, true );
    rb_define_attr( rbGlyph::Class, "texture_rect", true, true );

    // Instance aliases
    rb_define_alias( rbGlyph::Class, "to_s",   "inspect" );
}

// Glyph#initialize
VALUE rbGlyph::Initialize( VALUE aSelf )
{
	rb_iv_set( aSelf, "@advance", INT2NUM( 0 ) );
	rb_iv_set( aSelf, "@bounds", rbRect::ToRuby( sf::IntRect() ) );
	rb_iv_set( aSelf, "@texture_rect", rbRect::ToRuby( sf::IntRect() ) );
    return Qnil;
}

// Glyph#initialize_copy(glyph)
VALUE rbGlyph::InitializeCopy( VALUE aSelf, VALUE aGlyph )
{
    VALUE advance = rbGlyph::GetAdvance( aGlyph );
    VALUE bounds = rb_funcall( rbGlyph::GetBounds( aGlyph ), rb_intern( "clone" ), 0 );
    VALUE textureRect = rb_funcall( rbGlyph::GetTextureRect( aGlyph ), rb_intern( "clone" ), 0 );

    rbGlyph::SetAdvance( aSelf, advance );
	rbGlyph::SetBounds( aSelf, bounds );
	rbGlyph::SetTextureRect( aSelf, textureRect );

    return aSelf;
}

// Glyph#marshal_dump
VALUE rbGlyph::MarshalDump( VALUE aSelf )
{
    VALUE ptr[ 3 ];
    ptr[ 0 ] = rbGlyph::GetAdvance( aSelf );
    ptr[ 1 ] = rbGlyph::GetBounds( aSelf );
    ptr[ 2 ] = rbGlyph::GetTextureRect( aSelf );
    return rb_ary_new4( 3, ptr );
}

// Glyph#marshal_load(data)
VALUE rbGlyph::MarshalLoad( VALUE aSelf, VALUE aData )
{
    VALUE* ptr = RARRAY_PTR( aData );
    rbGlyph::SetAdvance( aSelf, ptr[ 0 ] );
    rbGlyph::SetBounds( aSelf, ptr[ 1 ] );
    rbGlyph::SetTextureRect( aSelf, ptr[ 2 ] );
    return Qnil;
}

// Glyph#==(other)
VALUE rbGlyph::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbGlyph::Class ) ) return Qfalse;
    if( !RTEST( rb_equal( rbGlyph::GetAdvance( aSelf ), rbGlyph::GetAdvance( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( rbGlyph::GetBounds( aSelf ), rbGlyph::GetBounds( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( rbGlyph::GetTextureRect( aSelf ), rbGlyph::GetTextureRect( anOther ) ) ) ) return Qfalse;
    return Qtrue;
}

// Glyph#inspect
// Glyph#to_s
VALUE rbGlyph::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%i, %s, %s)",
					   rb_obj_classname( aSelf ),
					   FIX2INT( rbGlyph::GetAdvance( aSelf ) ),
					   rb_funcall( rbGlyph::GetBounds( aSelf ), rb_intern( "inspect" ), 0 ),
					   rb_funcall( rbGlyph::GetTextureRect( aSelf ), rb_intern( "inspect" ), 0 ) );
}
