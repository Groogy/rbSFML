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

#define EXTRA_EFFECT_CPP

#include <gl/glew.h>
#include <gl/gl.h>

#include "Effect.hpp"
#include "EffectImp.hpp"
#include "../System/NonCopyable.hpp"
#include "../System/Vector2.hpp"
#include "../System/Vector3.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/Transform.hpp"

void rbEffect::Init( VALUE SFML )
{
  rbEffect::Class = rb_define_class_under( SFML, "Effect", rb_cObject );
	rb_include_module( rbEffect::Class, rbNonCopyable::Module );
	
	// Class methods
	rb_define_alloc_func( rbEffect::Class, rbMacros::Allocate< Shader > );

  // Instance methods
  ext_define_method( rbEffect::Class, "initialize", rbEffect::Initialize, 0 );
  ext_define_method( rbEffect::Class, "load_from_file", rbEffect::LoadFromFile, 1 );
  ext_define_method( rbEffect::Class, "set_parameter", rbEffect::SetParameter, -1 );
  ext_define_method( rbEffect::Class, "bind", rbEffect::Bind, 0 );
  ext_define_method( rbEffect::Class, "unbind", rbEffect::Unbind, 0 );
  
  rb_define_alias( rbEffect::Class, "[]=", "set_parameter" );
}

// Effect#initialize
VALUE rbEffect::Initialize( VALUE aSelf )
{
	return aSelf;
}

// Effect#load_from_file(filename)
VALUE rbEffect::LoadFromFile( VALUE aSelf, VALUE aFilename )
{
  Shader* pShader = rbMacros::ToSFML< Shader >( aSelf, rbEffect::Class );
  bool result = true;
  try
  {
    pShader->loadFromFile( StringValueCStr( aFilename ) );
  } catch( std::exception& exception )
  {
    sf::err() << exception.what() << std::endl;
    result = false;
  }
  return result ? Qtrue : Qfalse;
}

// Effect#set_parameter(name, x)
// Effect#set_parameter(name, x, y)
// Effect#set_parameter(name, x, y, z)
// Effect#set_parameter(name, vector2)
// Effect#set_parameter(name, vector3)
// Effect#set_parameter(name, color)
// Effect#set_parameter(name, transform)
// Effect#set_parameter(name, texture)
// Effect#set_parameter(name, current_texture)
// Effect#[]=(name, x)
// Effect#[]=(name, vector2)
// Effect#[]=(name, vector3)
// Effect#[]=(name, color)
// Effect#[]=(name, transform)
// Effect#[]=(name, texture)
// Effect#[]=(name, current_texture)
VALUE rbEffect::SetParameter( int argc, VALUE* args, VALUE aSelf )
{
	rb_check_frozen( aSelf );
	if( argc <= 1 )
		INVALID_ARGUMENT_LIST( argc, "2..5" );
		
	std::string name = StringValueCStr( args[ 0 ] );
	switch( argc )
	{
	case 2:
		if( rb_obj_is_kind_of( args[ 1 ], rb_cNumeric ) == Qtrue )
		{
			rbMacros::ToSFML< Shader >( aSelf, rbEffect::Class )->setParameter( name, NUM2DBL( args[ 1 ] ) );
		}
		else if( rb_obj_is_kind_of( args[ 1 ], rbVector2::Class ) == Qtrue || ( TYPE( args[ 1 ] ) == T_ARRAY && RARRAY_LEN( args[ 1 ] ) == 2 ) )
		{
			rbMacros::ToSFML< Shader >( aSelf, rbEffect::Class )->setParameter( name, rbVector2::ToSFMLf( args[ 1 ] ) );
		}
		else if( rb_obj_is_kind_of( args[ 1 ], rbVector3::Class ) == Qtrue || ( TYPE( args[ 1 ] ) == T_ARRAY && RARRAY_LEN( args[ 1 ] ) == 3 ) )
		{
			rbMacros::ToSFML< Shader >( aSelf, rbEffect::Class )->setParameter( name, rbVector3::ToSFMLf( args[ 1 ] ) );
		}
		else if( rb_obj_is_kind_of( args[ 1 ], rbTransform::Class ) == Qtrue )
		{
			rbMacros::ToSFML< Shader >( aSelf, rbEffect::Class )->setParameter( name, *rbMacros::ToSFML< sf::Transform >( args[ 1 ], rbTransform::Class ) );
		}
		else if( rb_obj_is_kind_of( args[ 1 ], rbTexture::Class ) == Qtrue )
		{
			rbMacros::ToSFML< Shader >( aSelf, rbEffect::Class )->setParameter( name, *rbMacros::ToSFML< sf::Texture >( args[ 1 ], rbTexture::Class ) );
		}
		else
		{
			INVALID_EXPECTED_TYPES5( rb_cNumeric, rbVector2::Class, rbVector3::Class, rbTransform::Class, rbTexture::Class );
		}
		break;
	case 3:
		rbMacros::ToSFML< Shader >( aSelf, rbEffect::Class )->setParameter( name, NUM2DBL( args[ 1 ] ), NUM2DBL( args[ 2 ] ) );
		break;
	case 4:
		rbMacros::ToSFML< Shader >( aSelf, rbEffect::Class )->setParameter( name, NUM2DBL( args[ 1 ] ), NUM2DBL( args[ 2 ] ), NUM2DBL( args[ 3 ] ) );
		break;
  case 5:
		rbMacros::ToSFML< Shader >( aSelf, rbEffect::Class )->setParameter( name, NUM2DBL( args[ 1 ] ), NUM2DBL( args[ 2 ] ), NUM2DBL( args[ 3 ] ), NUM2DBL( args[ 4 ] ) );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "2..5" );
	}
	return Qnil;
}

// Shader#blind()
VALUE rbEffect::Bind( VALUE aSelf )
{
  rbMacros::ToSFML< Shader >( aSelf, rbEffect::Class )->bind();
  return Qnil;
}

// Shader#unbind()
VALUE rbEffect::Unbind( VALUE aSelf )
{
  rbMacros::ToSFML< Shader >( aSelf, rbEffect::Class )->unbind();
  return Qnil;
}
