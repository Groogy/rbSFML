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

#define GRAPHICS_VERTEX_CPP

#include "Vertex.hpp"

void rbVertex::Init( VALUE SFML )
{
    rbVertex::Class = rb_define_class_under( SFML, "Vertex", rb_cObject );

    // Instance methods
    ext_define_method( rbVertex::Class, "initialize",      rbVertex::Initialize,     -1 );
    ext_define_method( rbVertex::Class, "initialize_copy", rbVertex::InitializeCopy,  1 );
    ext_define_method( rbVertex::Class, "marshal_dump",    rbVertex::MarshalDump,     0 );
    ext_define_method( rbVertex::Class, "marshal_load",    rbVertex::MarshalLoad,     1 );
    ext_define_method( rbVertex::Class, "==",              rbVertex::Equal,           1 );
    ext_define_method( rbVertex::Class, "inspect",         rbVertex::Inspect,         0 );

    // Attribute accessors
    rb_define_attr( rbVertex::Class, "position", true, true );
    rb_define_attr( rbVertex::Class, "color", true, true );
    rb_define_attr( rbVertex::Class, "tex_coords", true, true );

    // Instance aliases
    rb_define_alias( rbVertex::Class, "to_s",   "inspect" );
}

// Vertex#initialize
// Vertex#intialize(position)
// Vertex#initialize(position, color)
// Vertex#initialize(position, tex_coords)
// Vertex#initialize(position, color, tex_coords)
VALUE rbVertex::Initialize( int argc, VALUE* args, VALUE aSelf )
{
	switch( argc )
	{
	case 0:
		rbVertex::SetPosition( aSelf, rbVector2::ToRuby( sf::Vector2f( 0, 0 ) ) );
		rbVertex::SetColor( aSelf, rbColor::ToRuby( sf::Color::White ) );
		rbVertex::SetTexCoords( aSelf, rbVector2::ToRuby( sf::Vector2f( 0, 0 ) ) );
		break;
	case 1:
		rbVertex::SetPosition( aSelf, rbVector2::ToRuby( args[ 0 ] ) );
		rbVertex::SetColor( aSelf, rbColor::ToRuby( sf::Color::White ) );
		rbVertex::SetTexCoords( aSelf, rbVector2::ToRuby( sf::Vector2f( 0, 0 ) ) );
		break;
	case 2:
		rbVertex::SetPosition( aSelf, rbVector2::ToRuby( args[ 0 ] ) );
		if( rb_obj_is_kind_of( args[ 1 ], rbColor::Class ) == Qtrue || ( TYPE( args[ 1 ] ) == T_ARRAY && RARRAY_LEN( args[ 1 ] ) >= 3 ) )
		{
			rbVertex::SetColor( aSelf, rbColor::ToRuby( args[ 1 ] ) );
			rbVertex::SetTexCoords( aSelf, rbVector2::ToRuby( sf::Vector2f( 0, 0 ) ) );
		}
		else if( rb_obj_is_kind_of( args[ 1 ], rbVector2::Class ) == Qtrue || ( TYPE( args[ 1 ] ) == T_ARRAY && RARRAY_LEN( args[ 1 ] ) == 2 ) )
		{
			rbVertex::SetColor( aSelf, rbColor::ToRuby( sf::Color::White ) );
			rbVertex::SetTexCoords( aSelf, rbVector2::ToRuby( args[ 1 ] ) );
		}
		else
		{
			INVALID_EXPECTED_TYPES( rbVector2::Class, rbColor::Class );
		}
		break;
	case 3:
		rbVertex::SetPosition( aSelf, rbVector2::ToRuby( args[ 0 ] ) );
		rbVertex::SetColor( aSelf, rbColor::ToRuby( args[ 1 ] ) );
		rbVertex::SetTexCoords( aSelf, rbVector2::ToRuby( args[ 2 ] ) );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "0, 1, 3 or 4" );
	}
    return Qnil;
}

// Vertex#initialize_copy(vertex)
VALUE rbVertex::InitializeCopy( VALUE aSelf, VALUE aVertex )
{
    rbVertex::SetPosition( aSelf, rbVertex::GetPosition( aVertex ) );
	rbVertex::SetColor( aSelf, rbVertex::GetColor( aVertex ) );
	rbVertex::SetTexCoords( aSelf, rbVertex::GetTexCoords( aVertex ) );

    return aSelf;
}

// Vertex#marshal_dump
VALUE rbVertex::MarshalDump( VALUE aSelf )
{
    VALUE ptr[ 3 ];
    ptr[ 0 ] = rbVertex::GetPosition( aSelf );
    ptr[ 1 ] = rbVertex::GetColor( aSelf );
    ptr[ 2 ] = rbVertex::GetTexCoords( aSelf );
    return rb_ary_new4( 3, ptr );
}

// Vertex#marshal_load(data)
VALUE rbVertex::MarshalLoad( VALUE aSelf, VALUE aData )
{
    VALUE* ptr = RARRAY_PTR( aData );
    rbVertex::SetPosition( aSelf, ptr[ 0 ] );
    rbVertex::SetColor( aSelf, ptr[ 1 ] );
    rbVertex::SetTexCoords( aSelf, ptr[ 2 ] );
    return Qnil;
}

// Vertex#==(other)
VALUE rbVertex::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbVertex::Class ) ) return Qfalse;
    if( !RTEST( rb_equal( rbVertex::GetPosition( aSelf ), rbVertex::GetPosition( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( rbVertex::GetColor( aSelf ), rbVertex::GetColor( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( rbVertex::GetTexCoords( aSelf ), rbVertex::GetTexCoords( anOther ) ) ) ) return Qfalse;
    return Qtrue;
}

// Vertex#inspect
// Vertex#to_s
VALUE rbVertex::Inspect( VALUE aSelf )
{
	VALUE position = rb_funcall( rbVertex::GetPosition( aSelf ), rb_intern( "inspect" ), 0 );
	VALUE color = rb_funcall( rbVertex::GetColor( aSelf ), rb_intern( "inspect" ), 0 );
	VALUE texCoords = rb_funcall( rbVertex::GetTexCoords( aSelf ), rb_intern( "inspect" ), 0 );
	return rb_sprintf( "%s(%s, %s, %s)",
					   rb_obj_classname( aSelf ),
					   StringValueCStr( position ), 
					   StringValueCStr( color ), 
					   StringValueCStr( texCoords ) );
}
