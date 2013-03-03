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
 
#define GRAPHICS_DRAWABLE_CPP

#include "Drawable.hpp"

class rbInternalDrawable : public sf::Drawable
{
public:
	rbInternalDrawable()
	{
		mySelf = Qnil;
		myDrawID = rb_intern( "draw" );
	}
	
	void SetSelf( VALUE aSelf )
	{
		mySelf = aSelf;
	}
	
	void draw( sf::RenderTarget& aTarget, sf::RenderStates states) const
	{
		rb_funcall( mySelf, myDrawID, 0 );
	}
	
private:
	VALUE mySelf;
	ID myDrawID;
};

static VALUE rbInternalAllocateDrawable( VALUE aKlass )
{
	rbInternalDrawable* drawable = rbMacros::Allocate< rbInternalDrawable >();
	VALUE object = rbMacros::ToRuby( drawable, rbDrawable::Module );
	drawable->SetSelf( object );
	return object;
}

static VALUE rbInternalIncludedDrawable( VALUE aModule, VALUE aBase )
{
	rb_define_alloc_func( aBase, rbInternalAllocateDrawable );
	return Qnil;
}

void rbDrawable::Init( VALUE SFML )
{
    rbDrawable::Module = rb_define_module_under( SFML, "Drawable" );
	
	// Class methods
	ext_define_module_function( rbDrawable::Module, "included", rbInternalIncludedDrawable, 1 );

    // Instance methods
	//rb_define_method( rbDrawable::Module, "initialize",             rbDrawable::Initialize,           0 );
    ext_define_method( rbDrawable::Module, "initialize_copy",        rbDrawable::InitializeCopy,       1 );
	ext_define_method( rbDrawable::Module, "draw",                   rbDrawable::Draw,                 2 );
	ext_define_method( rbDrawable::Module, "marshal_dump",           rbDrawable::MarshalDump,          0 );
    ext_define_method( rbDrawable::Module, "==",                     rbDrawable::Equal,                1 );
    ext_define_method( rbDrawable::Module, "inspect",                rbDrawable::Inspect,              0 );

    // Instance aliases
    rb_define_alias( rbDrawable::Module, "to_s",       "inspect" );
}

// Drawable#initialize
VALUE rbDrawable::Initialize( VALUE aSelf )
{
	if( rb_iv_get( aSelf, "@__internal__drawable_offset" ) == Qnil )
	{
		rb_iv_set( aSelf, "@__internal__drawable_offset", INT2FIX( 0 ) );
	}
	
	rb_call_super( 0, NULL );
	return Qnil;
}

// Drawable#initialize_copy(source)
VALUE rbDrawable::InitializeCopy( VALUE aSelf, VALUE aSource )
{
    return aSelf;
}

// Drawable#draw(render_target, render_states)
VALUE rbDrawable::Draw( VALUE aSelf, VALUE aRenderTarget, VALUE aRenderStates )
{
	rb_raise( rb_eRuntimeError, "Call to abstract method '#draw'. Please override the method to use it." );
	return Qnil;
}

// Drawable#marshal_dump
VALUE rbDrawable::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
	return Qnil;
}

// Drawable#==(other)
VALUE rbDrawable::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbDrawable::Module ) )
		return Qfalse;
    else if( rbDrawable::ToSFML( aSelf ) == rbDrawable::ToSFML( anOther ) )
		return Qtrue;
	else
		return Qfalse;
}

// Drawable#inspect
// Drawable#to_s
VALUE rbDrawable::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbDrawable::ToSFML( aSelf ) );
}
