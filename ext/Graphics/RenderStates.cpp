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

#define GRAPHICS_RENDER_STATES_CPP

#include "RenderStates.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

void rbRenderStates::Init( VALUE SFML )
{
    rbRenderStates::Class = rb_define_class_under( SFML, "RenderStates", rb_cObject );
	
	// Class methods
	rb_define_alloc_func( rbRenderStates::Class, rbMacros::Allocate< sf::RenderStates > );

    // Instance methods
    ext_define_method( rbRenderStates::Class, "initialize",      rbRenderStates::Initialize,     	-1 );
    ext_define_method( rbRenderStates::Class, "initialize_copy", rbRenderStates::InitializeCopy, 	 1 );
	ext_define_method( rbRenderStates::Class, "blend_mode", 	 rbRenderStates::GetBlendMode,		 0 );
	ext_define_method( rbRenderStates::Class, "blend_mode=", 	 rbRenderStates::SetBlendMode,		 1 );
	ext_define_method( rbRenderStates::Class, "transform", 		 rbRenderStates::GetTransform,		 0 );
	ext_define_method( rbRenderStates::Class, "transform=",	 	 rbRenderStates::SetTransform,		 1 );
	ext_define_method( rbRenderStates::Class, "texture", 		 rbRenderStates::GetTexture,		 0 );
	ext_define_method( rbRenderStates::Class, "texture=",	 	 rbRenderStates::SetTexture,		 1 );
	ext_define_method( rbRenderStates::Class, "shader",	 		 rbRenderStates::GetShader,			 0 );
	ext_define_method( rbRenderStates::Class, "shader=", 		 rbRenderStates::SetShader,	 		 1 );
    ext_define_method( rbRenderStates::Class, "marshal_dump",    rbRenderStates::MarshalDump,    	 0 );
    ext_define_method( rbRenderStates::Class, "==",              rbRenderStates::Equal,          	 1 );
    ext_define_method( rbRenderStates::Class, "inspect",         rbRenderStates::Inspect,        	 0 );

    // Instance aliases
	rb_define_alias( rbRenderStates::Class, "blendMode",    "blend_mode"  );
    rb_define_alias( rbRenderStates::Class, "blendMode=",   "blend_mode=" );
	rb_define_alias( rbRenderStates::Class, "to_s",         "inspect"     );
	
	// Constants
	rb_define_const( rbRenderStates::Class, "Default", rbMacros::ToConstRuby( &sf::RenderStates::Default, rbRenderStates::Class ) );
}

// RenderStates#initialize
// RenderStates#initialize(blend_mode)
// RenderStates#initialize(tranform)
// RenderStates#initialize(texture)
// RenderStates#initialize(shader)
// RenderStates#initialize(blend_mode, transform, texture, shader)
// RenderStates#initialize([blend_mode, transform, texture, shader])
VALUE rbRenderStates::Initialize( int argc, VALUE* args, VALUE aSelf )
{
	sf::RenderStates* states = rbRenderStates::ToSFML( aSelf );
	switch( argc )
	{
	case 0:
		break;
	case 1:
		if( TYPE( args[ 0 ] ) == T_ARRAY || RARRAY_LEN( args[ 0 ] ) == 4 )
		{
			states->blendMode =  static_cast< sf::BlendMode >( NUM2UINT( rb_ary_entry( args[ 0 ], 0 ) ) );
			states->transform = *rbMacros::ToSFML< sf::Transform >( rb_ary_entry( args[ 0 ], 1 ), rbTransform::Class );
			states->texture   =  rbMacros::ToSFML< sf::Texture >( rb_ary_entry( args[ 0 ], 2 ), rbTexture::Class );
			states->shader    =  rbMacros::ToSFML< sf::Shader >( rb_ary_entry( args[ 0 ], 3 ), rbShader::Class );
		}
		else if( rb_obj_is_kind_of( args[ 0 ], rb_cNumeric ) == Qtrue )
		{
			states->blendMode = static_cast< sf::BlendMode >( NUM2UINT( args[ 0 ] ) );
		}
		else if( rb_obj_is_kind_of( args[ 0 ], rbTransform::Class ) == Qtrue )
		{
			states->transform = *rbMacros::ToSFML< sf::Transform >( args[ 0 ], rbTransform::Class );
		}
		else if( rb_obj_is_kind_of( args[ 0 ], rbTexture::Class ) == Qtrue )
		{
			states->texture = rbMacros::ToSFML< sf::Texture >( args[ 0 ], rbTexture::Class );
		}
		else if( rb_obj_is_kind_of( args[ 0 ], rbShader::Class ) == Qtrue )
		{
			states->shader = rbMacros::ToSFML< sf::Shader >( args[ 0 ], rbShader::Class );
		}
		else
		{
			INVALID_EXPECTED_TYPES5( rb_cNumeric, rbTransform::Class, rbTexture::Class, rbShader::Class, rb_cArray );
		}
		break;
	case 4:
		states->blendMode =  static_cast< sf::BlendMode >( NUM2UINT( args[ 0 ] ) );
		states->transform = *rbMacros::ToSFML< sf::Transform >( args[ 1 ], rbTransform::Class );
		states->texture   =  rbMacros::ToSFML< sf::Texture >( args[ 2 ], rbTexture::Class );
		states->shader    =  rbMacros::ToSFML< sf::Shader >( args[ 3 ], rbShader::Class );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "0, 1 or 4" );
	}
	
	VALUE transform = rbMacros::ToRubyNoGC( &states->transform, rbTransform::Class );
	rb_iv_set( aSelf, "@__ref__transform", transform );
	rb_iv_set( transform, "@__ref__state_owner", aSelf );
	rb_obj_freeze( transform );
	
	VALUE texture = rbMacros::ToRubyNoGC( const_cast< sf::Texture* >( states->texture ), rbTexture::Class );
	rb_iv_set( aSelf, "@__ref__texture", texture );
	rb_iv_set( texture, "@__ref__state_owner", aSelf );
	rb_obj_freeze( texture );
	
	VALUE shader = rbMacros::ToRubyNoGC( const_cast< sf::Shader* >( states->shader ), rbShader::Class );
	rb_iv_set( aSelf, "@__ref__shader", shader );
	rb_iv_set( shader, "@__ref__state_owner", aSelf );
	rb_obj_freeze( shader );
	
    return Qnil;
}

// RenderStates#initialize_copy(state)
VALUE rbRenderStates::InitializeCopy( VALUE aSelf, VALUE aState )
{
	sf::RenderStates* states = rbRenderStates::ToSFML( aSelf );
    *states = *rbRenderStates::ToSFML( aState );
	
	VALUE transform = rbMacros::ToRubyNoGC( &states->transform, rbTransform::Class );
	rb_iv_set( aSelf, "@__ref__transform", transform );
	rb_iv_set( transform, "@__ref__state_owner", aSelf );
	rb_obj_freeze( transform );
	
	VALUE texture = rbMacros::ToRubyNoGC( const_cast< sf::Texture* >( states->texture ), rbTexture::Class );
	rb_iv_set( aSelf, "@__ref__texture", texture );
	rb_iv_set( texture, "@__ref__state_owner", aSelf );
	rb_obj_freeze( texture );
	
	VALUE shader = rbMacros::ToRubyNoGC( const_cast< sf::Shader* >( states->shader ), rbShader::Class );
	rb_iv_set( aSelf, "@__ref__shader", shader );
	rb_iv_set( shader, "@__ref__state_owner", aSelf );
	rb_obj_freeze( shader );
    return aSelf;
}

// RenderStates#blend_mode
// RenderStates#blendMode
VALUE rbRenderStates::GetBlendMode( VALUE aSelf )
{
	return INT2NUM( rbRenderStates::ToSFML( aSelf )->blendMode );
}

// RenderStates#blend_mode=(mode)
// RenderStates#blendMode=(mode)
VALUE rbRenderStates::SetBlendMode( VALUE aSelf, VALUE aBlendMode )
{
	rbRenderStates::ToSFML( aSelf )->blendMode = static_cast< sf::BlendMode >( NUM2UINT( aBlendMode ) );
	return Qnil;
}

// RenderStates#transform
VALUE rbRenderStates::GetTransform( VALUE aSelf )
{
	return rb_iv_get( aSelf, "@__ref__transform" );
}

// RenderStates#transform=(transform)
VALUE rbRenderStates::SetTransform( VALUE aSelf, VALUE aTransform )
{
	rbRenderStates::ToSFML( aSelf )->transform = *rbMacros::ToSFML< sf::Transform >( aTransform, rbTransform::Class );
	return Qnil;
}

// RenderStates#texture
VALUE rbRenderStates::GetTexture( VALUE aSelf )
{
	return rb_iv_get( aSelf, "@__ref__texture" );
}

// RenderStates#texture=(texture)
VALUE rbRenderStates::SetTexture( VALUE aSelf, VALUE aTexture )
{
	sf::RenderStates* states = rbRenderStates::ToSFML( aSelf );
	if( aTexture == Qnil )
	{
		states->texture = NULL;
	}
	else
	{
		states->texture = rbMacros::ToSFML< sf::Texture >( aTexture, rbTexture::Class );
		rb_iv_set( aTexture, "@__ref__state_owner", aSelf );
	}
	rb_iv_set( aSelf, "@__ref__texture", aTexture );
	return Qnil;
}

// RenderStates#shader
VALUE rbRenderStates::GetShader( VALUE aSelf )
{
	return rb_iv_get( aSelf, "@__ref__shader" );
}

// RenderStates#shader=(shader)
VALUE rbRenderStates::SetShader( VALUE aSelf, VALUE aShader )
{
	sf::RenderStates* states = rbRenderStates::ToSFML( aSelf );
	if( aShader == Qnil )
	{
		states->shader = NULL;
	}
	else
	{
		states->shader = rbMacros::ToSFML< sf::Shader >( aShader, rbShader::Class );
		rb_iv_set( aShader, "@__ref__state_owner", aSelf );
	}
	
	rb_iv_set( aSelf, "@__ref__shader", aShader );
	return Qnil;
}
 
// RenderStates#marshal_dump
VALUE rbRenderStates::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
    return Qnil; 
}

// RenderStates#==(other)
VALUE rbRenderStates::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbRenderStates::Class ) ) return Qfalse;
    if( !RTEST( rbRenderStates::ToSFML( aSelf ) != rbRenderStates::ToSFML( anOther ) ) ) return Qfalse;
    return Qtrue;
}

// RenderStates#inspect
// RenderStates#to_s
VALUE rbRenderStates::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbRenderStates::ToSFML( aSelf ) );
}
