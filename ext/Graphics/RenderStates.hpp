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

#ifndef GRAPHICS_RENDER_STATES_HPP
#define GRAPHICS_RENDER_STATES_HPP

#include <ruby.h>

#include "../rbSFML.hpp"

#include <SFML/Graphics/RenderStates.hpp>

namespace rbRenderStates
{
    static inline VALUE ToRuby( VALUE anOther );
    static inline VALUE ToRuby( sf::RenderStates* aState );
    static inline sf::RenderStates* ToSFML( VALUE aState );

#if defined( GRAPHICS_RENDER_STATES_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif

#if defined( RBSFML_GRAPHICS )
    void Init( VALUE SFML );
#endif

#if defined( GRAPHICS_RENDER_STATES_CPP )
    // RenderStates#initialize
	// RenderStates#initialize(blend_mode)
	// RenderStates#initialize(tranform)
	// RenderStates#initialize(texture)
	// RenderStates#initialize(shader)
	// RenderStates#initialize(blend_mode, transform, texture, shader)
	// RenderStates#initialize([blend_mode, transform, texture, shader])
    static VALUE Initialize( int argc, VALUE* args, VALUE aSelf );

    // RenderStates#initialize_copy(state)
    static VALUE InitializeCopy( VALUE aSelf, VALUE aState );
	
	// RenderStates#blend_mode
	// RenderStates#blendMode
	static VALUE GetBlendMode( VALUE aSelf );
	
	// RenderStates#blend_mode=(mode)
	// RenderStates#blendMode=(mode)
	static VALUE SetBlendMode( VALUE aSelf, VALUE aBlendMode );
	
	// RenderStates#transform
	static VALUE GetTransform( VALUE aSelf );
	
	// RenderStates#transform=(transform)
	static VALUE SetTransform( VALUE aSelf, VALUE aTransform );
	
	// RenderStates#texture
	static VALUE GetTexture( VALUE aSelf );
	
	// RenderStates#texture=(texture)
	static VALUE SetTexture( VALUE aSelf, VALUE aTexture );
	
	// RenderStates#shader
	static VALUE GetShader( VALUE aSelf );
	
	// RenderStates#shader=(shader)
	static VALUE SetShader( VALUE aSelf, VALUE aShader );

    // RenderStates#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );

    // RenderStates#==(other)
    static VALUE Equal( VALUE aSelf, VALUE anOther );

    // RenderStates#inspect
    // RenderStates#to_s
    static VALUE Inspect( VALUE aSelf );
#endif

}

VALUE rbRenderStates::ToRuby( VALUE anOther )
{
    if(rb_obj_is_kind_of( anOther, rbRenderStates::Class ) )
        return anOther;

    if( rb_type( anOther ) == T_ARRAY )
        return rb_class_new_instance( RARRAY_LEN( anOther ), RARRAY_PTR( anOther ),
                                      rbRenderStates::Class );

    rb_raise( rb_eTypeError, "can't convert %s into %s",
              rb_obj_classname( anOther ), rb_class2name( rbRenderStates::Class ) );
}

VALUE rbRenderStates::ToRuby( sf::RenderStates* aState )
{
	return rbMacros::ToRuby( aState, rbRenderStates::Class );
}

sf::RenderStates* rbRenderStates::ToSFML( VALUE aState )
{
	return rbMacros::ToSFML< sf::RenderStates >( aState, rbRenderStates::Class );
}

#endif // GRAPHICS_RENDER_STATES_HPP
