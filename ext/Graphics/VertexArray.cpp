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
#include "Graphics/Drawable.hpp"

void rbVertexArray::Init( VALUE SFML )
{
    rbVertexArray::Class = rb_define_class_under( SFML, "VertexArray", rb_cObject );
	rb_include_module( rbVertexArray::Class, rbDrawable::Module );
	
	// Class methods
	rb_define_alloc_func( rbVertexArray::Class, rbMacros::Allocate< sf::VertexArray > );

    // Instance methods
	rb_define_method( rbVertexArray::Class, "initialize",             rbVertexArray::Initialize,          -1 );
    rb_define_method( rbVertexArray::Class, "initialize_copy",        rbVertexArray::InitializeCopy,       1 );
	rb_define_method( rbVertexArray::Class, "draw",                   rbVertexArray::Draw,                 2 );
	rb_define_method( rbVertexArray::Class, "marshal_dump",           rbVertexArray::MarshalDump,          0 );
    rb_define_method( rbVertexArray::Class, "==",                     rbVertexArray::Equal,                1 );
    rb_define_method( rbVertexArray::Class, "inspect",                rbVertexArray::Inspect,              0 );
    rb_define_method( rbVertexArray::Class, "memory_usage",           rbVertexArray::GetMemoryUsage,       0 );

    // Instance aliases
    rb_define_alias( rbVertexArray::Class, "to_s",       "inspect" );
}

// VertexArray#initialize
// VertexArray#initialize(primitive_type, vertex_count = 0)
VALUE rbVertexArray::Initialize( int argc, VALUE* args, VALUE aSelf )
{
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

// VertexArray#draw(render_target, render_states)
VALUE rbVertexArray::Draw( VALUE aSelf, VALUE aRenderTarget, VALUE aRenderStates )
{
	rb_raise( rb_eRuntimeError, "Call to abstract method '#draw'. Please override the method to use it." );
	return Qnil;
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

// Drawable#memory_usage
VALUE rbVertexArray::GetMemoryUsage( VALUE aSelf )
{
    return INT2FIX( sizeof( sf::VertexArray ) );
}
