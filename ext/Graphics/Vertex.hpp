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

#ifndef GRAPHICS_VERTEX_HPP
#define GRAPHICS_VERTEX_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include "System/Vector2.hpp"
#include "Graphics/Color.hpp"

#include <SFML/Graphics/Vertex.hpp>

namespace rbVertex
{
    static inline VALUE ToRuby( VALUE anOther );
    static inline VALUE ToRuby( const sf::Vertex& aVertex );
    static inline sf::Vertex ToSFML( VALUE aVertex );
	
	static inline VALUE GetPosition( VALUE aSelf );
	static inline VALUE GetColor( VALUE aSelf );
	static inline VALUE GetTexCoords( VALUE aSelf );
	
	static inline void SetPosition( VALUE aSelf, VALUE aValue );
	static inline void SetColor( VALUE aSelf, VALUE aValue );
	static inline void SetTexCoords( VALUE aSelf, VALUE aValue );

#if defined( GRAPHICS_VERTEX_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_VERTEX_CPP )
    // Vertex#initialize
    // Vertex#initialize(vertex)
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // Vertex#initialize_copy(vertex)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aColor );

    // Vertex#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // Vertex#marshal_load(data)
    static VALUE MarshalLoad( VALUE aSelf, VALUE aData );

    // Vertex#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // Vertex#inspect
    // Vertex#to_s
    static VALUE Inspect( VALUE aSelf );
#endif

}

VALUE rbVertex::ToRuby( VALUE anOther )
{
    if(rb_obj_is_kind_of( anOther, rbVertex::Class ) )
        return anOther;

    if( rb_type( anOther ) == T_ARRAY )
        return rb_class_new_instance( RARRAY_LEN( anOther ), RARRAY_PTR( anOther ),
                                      rbVertex::Class );

    rb_raise( rb_eTypeError, "can't convert %s into %s",
              rb_obj_classname( anOther ), rb_class2name( rbVertex::Class ) );
}

VALUE rbVertex::ToRuby( const sf::Vertex& aVertex )
{
	VALUE position  = rbVector2::ToRuby( aVertex.position );
	VALUE color     = rbColor::ToRuby( aVertex.color );
	VALUE texCoords = rbVector2::ToRuby( aVertex.texCoords );
    VALUE array[] = { position, color, texCoords };
    return rb_class_new_instance( 3, array, rbVertex::Class );
}

sf::Vertex rbVertex::ToSFML( VALUE aVertex )
{
    aVertex = rbVertex::ToRuby( aVertex );
	sf::Vector2f position  = rbVector2::ToSFMLf( rbVertex::GetPosition( aVertex ) );
	sf::Color color        = rbColor::ToSFML( rbVertex::GetColor( aVertex ) );
	sf::Vector2f texCoords = rbVector2::ToSFMLf( rbVertex::GetTexCoords( aVertex ) );
    return sf::Vertex( position, color, texCoords );
}

VALUE rbVertex::GetPosition( VALUE aSelf )
{
	return rb_iv_get( aSelf, "@position" );
}

VALUE rbVertex::GetColor( VALUE aSelf )
{
	return rb_iv_get( aSelf, "@color" );
}

VALUE rbVertex::GetTexCoords( VALUE aSelf )
{
	return rb_iv_get( aSelf, "@tex_coords" );
}

void rbVertex::SetPosition( VALUE aSelf, VALUE aValue )
{
	rb_iv_set( aSelf, "@position", aValue );
}

void rbVertex::SetColor( VALUE aSelf, VALUE aValue )
{
	rb_iv_set( aSelf, "@color", aValue );
}

void rbVertex::SetTexCoords( VALUE aSelf, VALUE aValue )
{
	rb_iv_set( aSelf, "@tex_coords", aValue );
}

#endif // GRAPHICS_VERTEX_HPP
