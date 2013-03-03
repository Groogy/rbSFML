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
 
#define GRAPHICS_VERTEX_ARRAY_CPP

#include "VertexArray.hpp"
#include "Vertex.hpp"
#include "Rect.hpp"
#include "Graphics/Drawable.hpp"

void rbVertexArray::Init( VALUE SFML )
{
    rbVertexArray::Class = rb_define_class_under( SFML, "VertexArray", rb_cObject );
	rb_include_module( rbVertexArray::Class, rbDrawable::Module );
	
	// Class methods
	rb_define_alloc_func( rbVertexArray::Class, rbMacros::Allocate< sf::VertexArray > );

    // Instance methods
	ext_define_method( rbVertexArray::Class, "initialize",		rbVertexArray::Initialize,			-1 );
    ext_define_method( rbVertexArray::Class, "initialize_copy",	rbVertexArray::InitializeCopy,		 1 );
	ext_define_method( rbVertexArray::Class, "vertex_count",	rbVertexArray::GetVertexCount,		 0 );
	ext_define_method( rbVertexArray::Class, "append", 			rbVertexArray::Append,				 1 );
	ext_define_method( rbVertexArray::Class, "[]", 				rbVertexArray::IndexOperator,		 1 );
	ext_define_method( rbVertexArray::Class, "clear", 			rbVertexArray::Clear,				 0 );
	ext_define_method( rbVertexArray::Class, "resize", 			rbVertexArray::Resize,				 1 );
	ext_define_method( rbVertexArray::Class, "primitive_type=",	rbVertexArray::SetPrimitiveType,	 1 );
	ext_define_method( rbVertexArray::Class, "primitive_type",	rbVertexArray::GetPrimitiveType,	 0 );
	ext_define_method( rbVertexArray::Class, "bounds",			rbVertexArray::GetBounds,			 0 );
	ext_define_method( rbVertexArray::Class, "marshal_dump",    rbVertexArray::MarshalDump,			 0 );
    ext_define_method( rbVertexArray::Class, "==",              rbVertexArray::Equal,				 1 );
    ext_define_method( rbVertexArray::Class, "inspect",         rbVertexArray::Inspect,				 0 );

    // Instance aliases
    rb_define_alias( rbVertexArray::Class, "to_s",               "inspect"         );
	rb_define_alias( rbVertexArray::Class, "vertexCount",        "vertex_count"    );
	rb_define_alias( rbVertexArray::Class, "getVertexCount",     "vertex_count"    );
	rb_define_alias( rbVertexArray::Class, "get_vertex_count",   "vertex_count"    );
	rb_define_alias( rbVertexArray::Class, "set_primitive_type", "primitive_type=" );
	rb_define_alias( rbVertexArray::Class, "setPrimitiveType",   "primitive_type=" );
	rb_define_alias( rbVertexArray::Class, "primitiveType=",     "primitive_type=" );
	rb_define_alias( rbVertexArray::Class, "get_primitive_type", "primitive_type"  );
	rb_define_alias( rbVertexArray::Class, "getPrimitiveType",   "primitive_type"  );
	rb_define_alias( rbVertexArray::Class, "primitiveType",      "primitive_type"  );
	rb_define_alias( rbVertexArray::Class, "get_bounds",         "bounds"          );
	rb_define_alias( rbVertexArray::Class, "getBounds",          "bounds"          );
}

// VertexArray#initialize
// VertexArray#initialize(primitive_type, vertex_count = 0)
VALUE rbVertexArray::Initialize( int argc, VALUE* args, VALUE aSelf )
{;
	switch( argc )
	{
	case 2:
		rbMacros::ToSFML< sf::VertexArray >( aSelf, rbVertexArray::Class )->resize( NUM2UINT( args[ 1 ] ) );
	case 1:
		rbMacros::ToSFML< sf::VertexArray >( aSelf, rbVertexArray::Class )->setPrimitiveType( static_cast< sf::PrimitiveType >( NUM2UINT( args[ 0 ] ) ) );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	rb_iv_set( aSelf, "@__internal__drawable_offset", INT2FIX( 0 ) );
	rb_call_super( 0, NULL );
	return Qnil;
}

// VertexArray#initialize_copy(source)
VALUE rbVertexArray::InitializeCopy( VALUE aSelf, VALUE aSource )
{
	rb_iv_set( aSelf, "@__internal__drawable_offset", INT2FIX( 0 ) );
	*rbMacros::ToSFML< sf::VertexArray >( aSelf, rbVertexArray::Class ) = *rbMacros::ToSFML< sf::VertexArray >( aSelf, rbVertexArray::Class );
    return aSelf;
}

// VertexArray#vertex_count
VALUE rbVertexArray::GetVertexCount( VALUE aSelf )
{
	return UINT2NUM( rbMacros::ToSFML< sf::VertexArray >( aSelf, rbVertexArray::Class )->getVertexCount() );
}

// VertexArray#append(vertex)
VALUE rbVertexArray::Append( VALUE aSelf, VALUE aVertex )
{
	rbMacros::ToSFML< sf::VertexArray >( aSelf, rbVertexArray::Class )->append( rbVertex::ToSFML( aVertex ) );
	return Qnil;
}

// VertexArray#[index]
VALUE rbVertexArray::IndexOperator( VALUE aSelf, VALUE anIndex )
{
	return rbVertex::ToRuby( ( *rbMacros::ToSFML< sf::VertexArray >( aSelf, rbVertexArray::Class ) )[ NUM2UINT( anIndex ) ] );
}

// VertexArray#clear
VALUE rbVertexArray::Clear( VALUE aSelf )
{
	rbMacros::ToSFML< sf::VertexArray >( aSelf, rbVertexArray::Class )->clear();
	return Qnil;
}

// VertexArray#resize(vertex_count)
VALUE rbVertexArray::Resize( VALUE aSelf, VALUE aVertexCount )
{
	rbMacros::ToSFML< sf::VertexArray >( aSelf, rbVertexArray::Class )->resize( NUM2UINT( aVertexCount ) );
	return Qnil;
}

// VertexArray#primitive_type=(type)
VALUE rbVertexArray::SetPrimitiveType( VALUE aSelf, VALUE aType )
{
	rbMacros::ToSFML< sf::VertexArray >( aSelf, rbVertexArray::Class )->setPrimitiveType( static_cast< sf::PrimitiveType >( NUM2UINT( aType ) ) );
	return Qnil;
}

// VertexArray#primitive_type
VALUE rbVertexArray::GetPrimitiveType( VALUE aSelf )
{
	return UINT2NUM( rbMacros::ToSFML< sf::VertexArray >( aSelf, rbVertexArray::Class )->getPrimitiveType() );
}

// VertexArray#bounds
VALUE rbVertexArray::GetBounds( VALUE aSelf )
{
	return rbRect::ToRuby( rbMacros::ToSFML< sf::VertexArray >( aSelf, rbVertexArray::Class )->getBounds() );
}

// VertexArray#marshal_dump
VALUE rbVertexArray::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
	return Qnil;
}

// VertexArray#==(other)
VALUE rbVertexArray::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbVertexArray::Class ) )
		return Qfalse;
    else if( rbMacros::ToSFML< sf::VertexArray >( aSelf, rbVertexArray::Class ) == rbMacros::ToSFML< sf::VertexArray >( anOther, rbVertexArray::Class ) )
		return Qtrue;
	else
		return Qfalse;
}

// VertexArray#inspect
// VertexArray#to_s
VALUE rbVertexArray::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::VertexArray >( aSelf, rbVertexArray::Class ) );
}
