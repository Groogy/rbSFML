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

#ifndef GRAPHICS_RENDER_TARGET_HPP
#define GRAPHICS_RENDER_TARGET_HPP

#include <ruby.h>
#include <rbSFML.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace rbRenderTarget
{
	static inline sf::RenderTarget* ToSFML( VALUE aValue );

#if defined( GRAPHICS_RENDER_TARGET_CPP )
    VALUE Module;
#else
    extern VALUE Module;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_RENDER_TARGET_CPP )
    // RenderTarget#initialize
    static VALUE Initialize( VALUE aSelf );
	
	// RenderTarget#clear(color=SFML::Color::Black)
	static VALUE Clear( int argc, VALUE* args, VALUE aSelf );
	
	// RenderTarget#view=(view)
	// RenderTarget#set_view(view)
	// RenderTarget#setView(view)
	static VALUE SetView( VALUE aSelf, VALUE aView );
	
	// RenderTarget#view
	// RenderTarget#get_view
	// RenderTarget#getView
	static VALUE GetView( VALUE aSelf );
		
	// RenderTarget#default_view
	// RenderTarget#get_default_view
	// RenderTarget#getDefaultView
	static VALUE GetDefaultView( VALUE aSelf );
	
	// RenderTarget#get_viewport(view)
	// RenderTarget#getViewport(view)
	static VALUE GetViewport( VALUE aSelf, VALUE aView );
	
	// RenderTarget#convert(x, y)
	// RenderTarget#convert_coords(x, y)
	// RenderTarget#convertCoords(x, y)
	// RenderTarget#convert(x, y, view)
	// RenderTarget#convert_coords(x, y, view)
	// RenderTarget#convertCoords(x, y, view)
	static VALUE ConvertCoords( int argc, VALUE* args, VALUE aSelf );
	
	// RenderTarget#draw(drawable, render_state)
	// RenderTarget#draw(vertices, primitive_type, render_state)
	static VALUE Draw( int argc, VALUE* args, VALUE aSelf );
	
	// RenderTarget#size
	// RenderTarget#get_size
	// RenderTarget#getSize
	static VALUE GetSize( VALUE aSelf );
	
	// RenderTarget#push_states
	// RenderTarget#push_gl_states
	// RenderTarget#pushGLStates
	static VALUE PushGLStates( VALUE aSelf );
	
	// RenderTarget#pop_states
	// RenderTarget#pop_gl_states
	// RenderTarget#popGLStates
	static VALUE PopGLStates( VALUE aSelf );
	
	// RenderTarget#reset_states
	// RenderTarget#reset_gl_states
	// RenderTarget#resetGLStates
	static VALUE ResetGLStates( VALUE aSelf );
	
	// RenderTarget#internal_initialize
	// RenderTarget#internalInitialize
	static VALUE InternalInitialize( VALUE aSelf );
	
	// RenderTarget#internal_apply_current_view
	// RenderTarget#internalApplyCurrentView
	static VALUE InternalApplyCurrentView( VALUE aSelf );
	
	// RenderTarget#internal_apply_blend_mode(mode)
	// RenderTarget#internalApplyBlendMode(mode)
	static VALUE InternalApplyBlendMode( VALUE aSelf, VALUE aMode );
	
	// RenderTarget#internal_apply_transform(transform)
	// RenderTarget#internalApplyTransform(transform)
	static VALUE InternalApplyTransform( VALUE aSelf, VALUE aTransformation );
	
	// RenderTarget#internal_apply_texture(texture)
	// RenderTarget#internalApplyTexture(texture)
	static VALUE InternalApplyTexture( VALUE aSelf, VALUE aTexture );
	
	// RenderTarget#internal_apply_shader(shader)
	// RenderTarget#internalApplyShader(shader)
	static VALUE InternalApplyShader( VALUE aSelf, VALUE aShader );
	
    // RenderTarget#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // RenderTarget#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // RenderTarget#inspect
    // RenderTarget#to_s
    static VALUE Inspect( VALUE aSelf );

    // RenderTarget#memory_usage
    static VALUE GetMemoryUsage( VALUE aSelf );
#endif
}

sf::RenderTarget* rbRenderTarget::ToSFML( VALUE aValue )
{
	aValue = rbMacros::ToRuby( aValue, rbRenderTarget::Module );
	char* compensationPtr = reinterpret_cast< char* >( DATA_PTR( aValue ) );
    unsigned int ptrOffset = FIX2UINT( rb_iv_get( aValue, "@__internal__render_target_offset" ) );
	return reinterpret_cast< sf::RenderTarget* >( compensationPtr + ptrOffset );
}

#endif // GRAPHICS_RENDER_TARGET_HPP
