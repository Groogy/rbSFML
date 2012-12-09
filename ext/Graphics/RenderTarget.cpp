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
#include "System/Vector2.hpp"
#include "System/NonCopyable.hpp"
#include "Graphics/View.hpp"
#include "Graphics/Color.hpp"
#include "Graphics/Rect.hpp"
#include "Graphics/Drawable.hpp"
#include "Graphics/RenderStates.hpp"
#include "Graphics/Vertex.hpp"
#include "Graphics/Transform.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Shader.hpp"

class rbInternalRenderTarget : public sf::RenderTarget
{
public:
	rbInternalRenderTarget()
	{
		mySelf = Qnil;
		myGetSizeSym  = rb_intern( "get_size" );
		myActivateSym = rb_intern( "activate" );
	}
	
	void SetSelf( VALUE aSelf )
	{
		mySelf = aSelf;
	}
	
	sf::Vector2u getSize() const
	{
		return rbVector2::ToSFMLu( rb_funcall( mySelf, myGetSizeSym, 0 ) );
	}
	
	bool activate( bool aFlag )
	{
		return RTEST( rb_funcall( mySelf, myActivateSym, 1, RBOOL( aFlag ) ) );
	}
	
	void initialize()
	{
		sf::RenderTarget::initialize();
	}
	
private:
	ID myGetSizeSym;
	ID myActivateSym;
	VALUE mySelf;
};

static VALUE rbInternalAllocateRenderTarget( VALUE aKlass )
{
	rbInternalRenderTarget* target = rbMacros::Allocate< rbInternalRenderTarget >();
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
	rb_include_module( rbRenderTarget::Module, rbNonCopyable::Module );
	
	// Class methods
	rb_define_module_function( rbRenderTarget::Module, "included", rbInternalIncludedRenderTarget, 1 );

    // Instance methods
	rb_define_method( rbRenderTarget::Module, "clear",                       rbRenderTarget::Clear,                   -1 );
	rb_define_method( rbRenderTarget::Module, "set_view",                    rbRenderTarget::SetView,                  1 );
	rb_define_method( rbRenderTarget::Module, "get_view",                    rbRenderTarget::GetView,                  0 );
	rb_define_method( rbRenderTarget::Module, "get_default_view",            rbRenderTarget::GetDefaultView,           0 );
	rb_define_method( rbRenderTarget::Module, "get_viewport",                rbRenderTarget::GetViewport,              1 );
	rb_define_method( rbRenderTarget::Module, "map_pixel_to_coords",         rbRenderTarget::MapPixelToCoords,        -1 );
	rb_define_method( rbRenderTarget::Module, "map_coords_to_pixel",         rbRenderTarget::MapCoordsToPixel,        -1 );
	rb_define_method( rbRenderTarget::Module, "draw",                        rbRenderTarget::Draw,                    -1 );
	rb_define_method( rbRenderTarget::Module, "get_size",                    rbRenderTarget::GetSize,                  0 );
	rb_define_method( rbRenderTarget::Module, "push_gl_states",              rbRenderTarget::PushGLStates,             0 );
	rb_define_method( rbRenderTarget::Module, "pop_gl_states",               rbRenderTarget::PopGLStates,              0 );
	rb_define_method( rbRenderTarget::Module, "reset_gl_states",             rbRenderTarget::ResetGLStates,            0 );
	rb_define_method( rbRenderTarget::Module, "internal_initialize",         rbRenderTarget::InternalInitialize,       0 );
	rb_define_method( rbRenderTarget::Module, "marshal_dump",                rbRenderTarget::MarshalDump,              0 );
    rb_define_method( rbRenderTarget::Module, "==",                          rbRenderTarget::Equal,                    1 );
    rb_define_method( rbRenderTarget::Module, "inspect",                     rbRenderTarget::Inspect,                  0 );
    rb_define_method( rbRenderTarget::Module, "memory_usage",                rbRenderTarget::GetMemoryUsage,           0 );

    // Instance aliases
    rb_define_alias( rbRenderTarget::Module, "to_s",                     "inspect"                     );
	rb_define_alias( rbRenderTarget::Module, "view=",                    "set_view"                    );
	rb_define_alias( rbRenderTarget::Module, "setView",                  "set_view"                    );
	rb_define_alias( rbRenderTarget::Module, "view",                     "get_view"                    );
	rb_define_alias( rbRenderTarget::Module, "getView",                  "get_view"                    );
	rb_define_alias( rbRenderTarget::Module, "default_view",             "get_default_view"            );
	rb_define_alias( rbRenderTarget::Module, "getDefaultView",           "get_default_view"            );
	rb_define_alias( rbRenderTarget::Module, "get_viewport",             "get_viewport"                );
	rb_define_alias( rbRenderTarget::Module, "getViewport",              "get_viewport"                );
	rb_define_alias( rbRenderTarget::Module, "map_coords",               "map_pixel_to_coords"         );
	rb_define_alias( rbRenderTarget::Module, "mapPixelToCoords",         "map_pixel_to_coords"         );
	rb_define_alias( rbRenderTarget::Module, "map_pixel",                "map_coords_to_pixel"         );
	rb_define_alias( rbRenderTarget::Module, "mapCoordsToPixel",         "map_coords_to_pixel"         );
	rb_define_alias( rbRenderTarget::Module, "size",                     "get_size"                    );
	rb_define_alias( rbRenderTarget::Module, "getSize",                  "get_size"                    );
	rb_define_alias( rbRenderTarget::Module, "push_states",              "push_gl_states"              );
	rb_define_alias( rbRenderTarget::Module, "pushGLStates",             "push_gl_states"              );
	rb_define_alias( rbRenderTarget::Module, "pop_states",               "pop_gl_states"               );
	rb_define_alias( rbRenderTarget::Module, "popGLStates",              "pop_gl_states"               );
	rb_define_alias( rbRenderTarget::Module, "reset_states",             "reset_gl_states"             );
	rb_define_alias( rbRenderTarget::Module, "resetGLStates",            "reset_gl_states"             );
	rb_define_alias( rbRenderTarget::Module, "internalInitialize",       "internal_initialize"         );
}

#include <iostream>
// RenderTarget#clear(color=SFML::Color::Black)
VALUE rbRenderTarget::Clear( int argc, VALUE* args, VALUE aSelf )
{
	sf::Color color = sf::Color::Black;
	switch( argc )
	{
	case 1:
		color = rbColor::ToSFML( args[ 0 ] );
	case 0:
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "0 or 1" );
	}
	
	rbRenderTarget::ToSFML( aSelf )->clear( color );
	return Qnil;
}

// RenderTarget#view=(view)
// RenderTarget#set_view(view)
// RenderTarget#setView(view)
VALUE rbRenderTarget::SetView( VALUE aSelf, VALUE aView )
{
	rbRenderTarget::ToSFML( aSelf )->setView( *rbMacros::ToSFML< sf::View >( aView, rbView::Class ) );
	return Qnil;
}

// RenderTarget#view
// RenderTarget#get_view
// RenderTarget#getView
VALUE rbRenderTarget::GetView( VALUE aSelf )
{
	const sf::View& view = rbRenderTarget::ToSFML( aSelf )->getView();
	VALUE obj = rbMacros::ToRubyNoGC( const_cast< sf::View* >( &view ), rbView::Class );
	rb_iv_set( obj, "@__ref__owner", aSelf );
	rb_obj_freeze( obj );
	return obj;
}
	
// RenderTarget#default_view
// RenderTarget#get_default_view
// RenderTarget#getDefaultView
VALUE rbRenderTarget::GetDefaultView( VALUE aSelf )
{
	const sf::View& view = rbRenderTarget::ToSFML( aSelf )->getDefaultView();
	VALUE obj = rbMacros::ToRubyNoGC( const_cast< sf::View* >( &view ), rbView::Class );
	rb_iv_set( obj, "@__ref__owner", aSelf );
	rb_obj_freeze( obj );
	return obj;
}

// RenderTarget#get_viewport(view)
// RenderTarget#getViewport(view)
VALUE rbRenderTarget::GetViewport( VALUE aSelf, VALUE aView )
{
	return rbRect::ToRuby( rbRenderTarget::ToSFML( aSelf )->getViewport( *rbMacros::ToSFML< sf::View >( aView, rbView::Class ) ) );
}

// RenderTarget#map_coords(vector2)
// RenderTarget#mapPixelToCoords(vector2)
// RenderTarget#map_coords(vector2, view)
// RenderTarget#mapPixelToCoords(vector2, view)
VALUE rbRenderTarget::MapPixelToCoords( int argc, VALUE* args, VALUE aSelf )
{
	VALUE coords = Qnil;
	switch( argc )
	{
	case 1:
		coords = rbVector2::ToRuby( rbRenderTarget::ToSFML( aSelf )->mapPixelToCoords( rbVector2::ToSFMLi( args[ 0 ] ) ) );
		break;
	case 2:
		coords = rbVector2::ToRuby( rbRenderTarget::ToSFML( aSelf )->mapPixelToCoords( 
				rbVector2::ToSFMLi( args[ 0 ] ),
				*rbMacros::ToSFML< sf::View >( args[ 1 ], rbView::Class ) 
			) 
		);
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "2 or 3" );
	}
	
	return coords;
}

// RenderTarget#map_pixel(vector2)
// RenderTarget#mapCoordsToPixel(vector2)
// RenderTarget#map_pixel(vector2, view)
// RenderTarget#mapCoordsToPixel(vector2, view)
VALUE rbRenderTarget::MapCoordsToPixel( int argc, VALUE* args, VALUE aSelf )
{
	VALUE coords = Qnil;
	switch( argc )
	{
	case 1:
		coords = rbVector2::ToRuby( rbRenderTarget::ToSFML( aSelf )->mapCoordsToPixel( rbVector2::ToSFMLf( args[ 0 ] ) ) );
		break;
	case 2:
		coords = rbVector2::ToRuby( rbRenderTarget::ToSFML( aSelf )->mapCoordsToPixel( 
				rbVector2::ToSFMLf( args[ 0 ] ),
				*rbMacros::ToSFML< sf::View >( args[ 1 ], rbView::Class ) 
			) 
		);
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "2 or 3" );
	}
	
	return coords;
}

// RenderTarget#draw(drawable, render_state=SFML::RenderStates::Default)
// RenderTarget#draw(vertices, primitive_type, render_state)
VALUE rbRenderTarget::Draw( int argc, VALUE* args, VALUE aSelf )
{
	switch( argc )
	{
	case 1:
		rbRenderTarget::ToSFML( aSelf )->draw( *rbDrawable::ToSFML( args[ 0 ] ) );
		break;
	case 2:
		rbRenderTarget::ToSFML( aSelf )->draw( *rbDrawable::ToSFML( args[ 0 ] ), *rbMacros::ToSFML< sf::RenderStates >( args[ 1 ], rbRenderStates::Class ) );
		break;
	case 3:
		if( TYPE( args[ 0 ] ) == T_ARRAY )
		{
			unsigned int vertexCount = RARRAY_LEN( args[ 0 ] );
			VALUE* vertexPtr         = RARRAY_PTR( args[ 0 ] );
			sf::Vertex* vertices     = static_cast< sf::Vertex* >( xmalloc( sizeof( sf::Vertex ) * vertexCount ) );
			for( unsigned int index = 0; index < vertexCount; index++ )
			{
				vertices[ index ] = rbVertex::ToSFML( vertexPtr[ index ] );
			}
			
			rbRenderTarget::ToSFML( aSelf )->draw( vertices, vertexCount, static_cast< sf::PrimitiveType >( NUM2INT( args[ 1 ] ) ), *rbMacros::ToSFML< sf::RenderStates >( args[ 2 ], rbRenderStates::Class ) );
			
			xfree( vertices );
		}
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1..3" );
	}
	
	return Qnil;
}

// RenderTarget#size
// RenderTarget#get_size
// RenderTarget#getSize
VALUE rbRenderTarget::GetSize( VALUE aSelf )
{
	return rbVector2::ToRuby( rbRenderTarget::ToSFML( aSelf )->getSize() );
}

// RenderTarget#push_states
// RenderTarget#push_gl_states
// RenderTarget#pushGLStates
VALUE rbRenderTarget::PushGLStates( VALUE aSelf )
{
	rbRenderTarget::ToSFML( aSelf )->pushGLStates();
	return Qnil;
}

// RenderTarget#pop_states
// RenderTarget#pop_gl_states
// RenderTarget#popGLStates
VALUE rbRenderTarget::PopGLStates( VALUE aSelf )
{
	rbRenderTarget::ToSFML( aSelf )->popGLStates();
	return Qnil;
}

// RenderTarget#reset_states
// RenderTarget#reset_gl_states
// RenderTarget#resetGLStates
VALUE rbRenderTarget::ResetGLStates( VALUE aSelf )
{
	rbRenderTarget::ToSFML( aSelf )->resetGLStates();
	return Qnil;
}

// RenderTarget#internal_initialize
// RenderTarget#internalInitialize
VALUE rbRenderTarget::InternalInitialize( VALUE aSelf )
{
	sf::RenderTarget* targetBase = rbRenderTarget::ToSFML( aSelf );
	rbInternalRenderTarget* derivedTarget = dynamic_cast< rbInternalRenderTarget* >( targetBase );
	if( derivedTarget == NULL )
		rb_raise( rb_eRuntimeError, "Called internal method on non-custom render target" );
		
	derivedTarget->initialize();
	
	return Qnil;
}

// RenderTarget#marshal_dump
VALUE rbRenderTarget::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
	return Qnil;
}

// RenderTarget#==(other)
VALUE rbRenderTarget::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbRenderTarget::Module ) )
		return Qfalse;
    else if( rbRenderTarget::ToSFML( aSelf ) == rbRenderTarget::ToSFML( anOther ) )
		return Qtrue;
	else
		return Qfalse;
}

// RenderTarget#inspect
// RenderTarget#to_s
VALUE rbRenderTarget::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbRenderTarget::ToSFML( aSelf ) );
}

// RenderTarget#memory_usage
VALUE rbRenderTarget::GetMemoryUsage( VALUE aSelf )
{
    return INT2FIX( sizeof( rbInternalRenderTarget ) );
}
