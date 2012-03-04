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
 
#define GRAPHICS_TRANSFORMABLE_CPP

#include "Transformable.hpp"

static VALUE rbInternalAllocateTransformable( VALUE aKlass )
{
	sf::Transformable* transformable = rbMacros::Allocate< sf::Transformable >();
	VALUE object = rbMacros::ToRuby( transformable, rbTransformable::Module );
	return object;
}

static VALUE rbInternalIncludedTransformable( VALUE aModule, VALUE aBase )
{
	rb_define_alloc_func( aBase, rbInternalAllocateTransformable );
	return Qnil;
}

void rbTransformable::Init( VALUE SFML )
{
    rbTransformable::Module = rb_define_module_under( SFML, "Drawable" );
	
	// Class methods
	rb_define_module_function( rbTransformable::Module, "included", rbInternalIncludedTransformable, 1 );

    // Instance methods
	rb_define_method( rbTransformable::Module, "initialize",             rbTransformable::Initialize,           0 );
    rb_define_method( rbTransformable::Module, "initialize_copy",        rbTransformable::InitializeCopy,       1 );
	rb_define_method( rbTransformable::Module, "marshal_dump",           rbTransformable::MarshalDump,          0 );
    rb_define_method( rbTransformable::Module, "==",                     rbTransformable::Equal,                1 );
    rb_define_method( rbTransformable::Module, "inspect",                rbTransformable::Inspect,              0 );
    rb_define_method( rbTransformable::Module, "memory_usage",           rbTransformable::GetMemoryUsage,       0 );

    // Instance aliases
    rb_define_alias( rbTransformable::Module, "to_s",       "inspect" );
}

// Transformable#initialize
VALUE rbTransformable::Initialize( VALUE aSelf )
{
	rb_raise( rb_eRuntimeError, "can't allocate instance of abstract class %s", rb_obj_classname( aSelf ) );
	return Qnil;
}

// Transformable#initialize_copy(source)
VALUE rbTransformable::InitializeCopy( VALUE aSelf, VALUE aSource )
{
    return aSelf;
}

// Transformable#marshal_dump
VALUE rbTransformable::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
	return Qnil;
}

// Transformable#==(other)
VALUE rbTransformable::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbTransformable::Module ) )
		return Qfalse;
    else if( rbMacros::ToSFML< sf::Transformable >( aSelf, rbTransformable::Module ) == rbMacros::ToSFML< sf::Transformable >( anOther, rbTransformable::Module ) )
		return Qtrue;
	else
		return Qfalse;
}

// Transformable#inspect
// Transformable#to_s
VALUE rbTransformable::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::Transformable >( aSelf, rbTransformable::Module ) );
}

// Transformable#memory_usage
VALUE rbTransformable::GetMemoryUsage( VALUE aSelf )
{
    return INT2FIX( sizeof( sf::Transformable ) );
}
