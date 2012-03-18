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
 
#define GRAPHICS_RENDER_TARGET_CPP

#include "RenderTarget.hpp"

class rbInternalRenderTarget : public sf::RenderTarget
{
public:
	rbInternalRenderTarget()
	{
		mySelf = Qnil;
	}
	
	void SetSelf( VALUE aSelf )
	{
		mySelf = aSelf;
	}
	
	sf::Vector2u GetSize() const
	{
		return sf::Vector2u( 0, 0 );
	}
	
private:
	VALUE mySelf;
};

static VALUE rbInternalAllocateRenderTarget( VALUE aKlass )
{
	rbInternalRenderTarget* target = NULL;// = rbMacros::Allocate< rbInternalRenderTarget >();
	VALUE object = rbMacros::ToRuby( target, rbRenderTarget::Module );
	target->SetSelf( object );
	return object;
}

static VALUE rbInternalIncludedRenderTarget( VALUE aModule, VALUE aBase )
{
	rb_define_alloc_func( aBase, rbInternalAllocateRenderTarget );
	return Qnil;
}

void rbRenderTarget::Init( VALUE SFML )
{
    rbRenderTarget::Module = rb_define_module_under( SFML, "RenderTarget" );
	
	// Class methods
	rb_define_module_function( rbRenderTarget::Module, "included", rbInternalIncludedRenderTarget, 1 );

    // Instance methods
	rb_define_method( rbRenderTarget::Module, "initialize",             rbRenderTarget::Initialize,           0 );
    rb_define_method( rbRenderTarget::Module, "initialize_copy",        rbRenderTarget::InitializeCopy,       1 );
	rb_define_method( rbRenderTarget::Module, "marshal_dump",           rbRenderTarget::MarshalDump,          0 );
    rb_define_method( rbRenderTarget::Module, "==",                     rbRenderTarget::Equal,                1 );
    rb_define_method( rbRenderTarget::Module, "inspect",                rbRenderTarget::Inspect,              0 );
    rb_define_method( rbRenderTarget::Module, "memory_usage",           rbRenderTarget::GetMemoryUsage,       0 );

    // Instance aliases
    rb_define_alias( rbRenderTarget::Module, "to_s",       "inspect" );
}

// Drawable#initialize
VALUE rbRenderTarget::Initialize( VALUE aSelf )
{
	if( rb_iv_get( aSelf, "@__internal__render_target_offset" ) == Qnil )
	{
		rb_iv_set( aSelf, "@__internal__render_target_offset", INT2FIX( 0 ) );
	}
	
	rb_call_super( 0, NULL );
	return Qnil;
}

// Drawable#initialize_copy(source)
VALUE rbRenderTarget::InitializeCopy( VALUE aSelf, VALUE aSource )
{
	rb_call_super( 1, &aSource );
    return aSelf;
}

// Drawable#marshal_dump
VALUE rbRenderTarget::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
	return Qnil;
}

// Drawable#==(other)
VALUE rbRenderTarget::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbRenderTarget::Module ) )
		return Qfalse;
    else if( rbRenderTarget::ToSFML( aSelf ) == rbRenderTarget::ToSFML( anOther ) )
		return Qtrue;
	else
		return Qfalse;
}

// Drawable#inspect
// Drawable#to_s
VALUE rbRenderTarget::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbRenderTarget::ToSFML( aSelf ) );
}

// Drawable#memory_usage
VALUE rbRenderTarget::GetMemoryUsage( VALUE aSelf )
{
    return INT2FIX( sizeof( rbInternalRenderTarget ) );
}
