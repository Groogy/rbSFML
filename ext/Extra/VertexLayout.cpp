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

#define EXTRA_VERTEX_LAYOUT_CPP

#include "VertexLayout.hpp"

void rbVertexLayout::Init( VALUE SFML )
{
  rbVertexLayout::Class = rb_define_class_under( SFML, "VertexLayout", rb_cObject );
	
  // Instance methods
  ext_define_method( rbVertexLayout::Class, "initialize", rbVertexLayout::Initialize, 0 );
	ext_define_method( rbVertexLayout::Class, "<<", rbVertexLayout::Append, 1 );
}

// VertexLayout#initialize
VALUE rbVertexLayout::Initialize( VALUE aSelf )
{
	rb_iv_set( aSelf, "@attributes", rb_ary_new() );
	return Qnil;
}

// VertexLayout#<<
VALUE rbVertexLayout::Append( VALUE aSelf, VALUE anAttribute )
{
	VALUE attributes = rb_iv_get( aSelf, "@attributes" );
	rb_ary_push( attributes, anAttribute );
	return aSelf;
}
