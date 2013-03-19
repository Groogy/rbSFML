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

#define GRAPHICS_SHADER_CPP

#include "Shader.hpp"
#include "../InputStream.hpp"
#include "../System/SFML.hpp"
#include "../System/Vector2.hpp"
#include "../System/Vector3.hpp"
#include "../System/NonCopyable.hpp"
#include "Color.hpp"
#include "Transform.hpp"
#include "Texture.hpp"

void rbShader::Init( VALUE SFML )
{
    rbShader::Class = rb_define_class_under( SFML, "Shader", rb_cObject );
	rb_include_module( rbShader::Class, rbNonCopyable::Module );
	
	rbShader::Class_CurrentTextureType = rb_define_class_under( rbShader::Class, "CurrentTextureType", rb_cObject );
	rb_include_module( rbShader::Class, rbNonCopyable::Module );
	
	// Class methods
	rb_define_alloc_func( rbShader::Class, rbMacros::Allocate< sf::Shader > );
	ext_define_class_method( rbShader::Class, "available?", rbShader::IsAvailable, 0 );
	ext_define_class_method( rbShader::Class, "bind",       rbShader::Bind,       -1 );

    // Instance methods
    ext_define_method( rbShader::Class, "initialize",             rbShader::Initialize,          -1 );
	ext_define_method( rbShader::Class, "load_from_file",	     rbShader::LoadFromFile,         2 );
	ext_define_method( rbShader::Class, "load_from_memory",       rbShader::LoadFromMemory,       2 );
	ext_define_method( rbShader::Class, "load_from_stream",       rbShader::LoadFromStream,       2 );
	ext_define_method( rbShader::Class, "set_parameter",          rbShader::SetParameter,        -1 );
    ext_define_method( rbShader::Class, "marshal_dump",           rbShader::MarshalDump,          0 );
    ext_define_method( rbShader::Class, "==",                     rbShader::Equal,                1 );
    ext_define_method( rbShader::Class, "inspect",                rbShader::Inspect,              0 );
	
	// Class aliases
	rb_define_alias( rb_singleton_class( rbShader::Class ), "is_available?", "available?" );
	rb_define_alias( rb_singleton_class( rbShader::Class ), "is_available",  "available?" );
	rb_define_alias( rb_singleton_class( rbShader::Class ), "isAvailable",   "available?" );

    // Instance aliases
	rb_define_alias( rbShader::Class, "loadFromFile",        "load_from_file"         );
	rb_define_alias( rbShader::Class, "loadFromMemory",      "load_from_memory"       );
	rb_define_alias( rbShader::Class, "loadFromStream",      "load_from_stream"       );
	rb_define_alias( rbShader::Class, "setParameter",        "set_parameter"          );
	rb_define_alias( rbShader::Class, "[]=",                 "set_parameter"          );
    rb_define_alias( rbShader::Class, "to_s",                "inspect"                );
	
	rb_define_const( rbShader::Class, "Vertex",   INT2NUM( sf::Shader::Vertex )   );
	rb_define_const( rbShader::Class, "Fragment", INT2NUM( sf::Shader::Fragment ) );
	
	rb_define_const( rbShader::Class, "CurrentTexture", rbShader::Class_CurrentTextureType );
}

// Shader.available?()
VALUE rbShader::IsAvailable( VALUE aSelf )
{
	return RBOOL( sf::Shader::isAvailable() );	
}

// Shader.bind()
VALUE rbShader::Bind( int argc, VALUE* args, VALUE aSelf )
{
	if ( argc == 0 || ( argc == 1 && args[ 0 ] == Qnil ) )
		sf::Shader::bind( NULL );
	else if ( argc == 1 )
		sf::Shader::bind( rbMacros::ToSFML< sf::Shader >( args[ 0 ], rbShader::Class ) );
	else
		INVALID_ARGUMENT_LIST( argc, "0..1" );
	return Qnil;
}

// Shader#initialize
// Shader#initialize(vertex_filename, fragment_filename)
// Shader#initialize(shader_filename, shader_type)
VALUE rbShader::Initialize( int argc, VALUE* args, VALUE aSelf )
{	
	if( argc > 0 )
	{
		rb_funcall2( aSelf, rb_intern("load_from_file"), argc, args );
	}
    return Qnil;
}

// Shader#load_from_file(filename, type)
// Shader#load_from_file(vertex_filename, fragment_filename)
// Shader#loadFromFile(filename, type)
// Shader#loadFromFile(vertex_filename, fragment_filename)
VALUE rbShader::LoadFromFile( VALUE aSelf, VALUE anArg1, VALUE anArg2 )
{
	rb_check_frozen( aSelf );
	rbSFML::PrepareErrorStream();
	bool result = false;
	if( rb_obj_is_kind_of( anArg2, rb_cString ) == Qtrue )
	{
		result = rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->loadFromFile( StringValueCStr( anArg1 ), StringValueCStr( anArg2 ) );
	}
	else
	{
		result = rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->loadFromFile( StringValueCStr( anArg1 ), static_cast< sf::Shader::Type >( NUM2INT( anArg2 ) ) );
	}
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Shader#load_from_memory(data, type)
// Shader#load_from_memory(vertex_data, fragment_data)
// Shader#loadFromMemory(data, type)
// Shader#loadFromMemory(vertex_data, fragment_data)
VALUE rbShader::LoadFromMemory( VALUE aSelf, VALUE anArg1, VALUE anArg2 )
{
	rb_check_frozen( aSelf );
	rbSFML::PrepareErrorStream();
	bool result = false;
	if( rb_obj_is_kind_of( anArg2, rb_cString ) == Qtrue )
	{
		result = rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->loadFromMemory( std::string( RSTRING_PTR( anArg1 ), RSTRING_LEN( anArg1 ) ), std::string( RSTRING_PTR( anArg2 ), RSTRING_LEN( anArg2 ) ) );
	}
	else
	{
		result = rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->loadFromMemory( std::string( RSTRING_PTR( anArg1 ), RSTRING_LEN( anArg1 ) ), static_cast< sf::Shader::Type >( NUM2INT( anArg2 ) ) );
	}
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Shader#load_from_stream(stream, type)
// Shader#load_from_stream(vertex_stream, fragment_stream)
// Shader#loadFromStream(stream, type)
// Shader#loadFromStream(vertex_stream, fragment_stream)
VALUE rbShader::LoadFromStream( VALUE aSelf, VALUE anArg1, VALUE anArg2 )
{
	rb_check_frozen( aSelf );
	rbSFML::PrepareErrorStream();
	bool result = false;
	if( rb_obj_is_kind_of( anArg2, rb_cIO ) == Qtrue )
	{
		rbInputStream stream1( anArg1 );
		rbInputStream stream2( anArg2 );
		result = rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->loadFromStream( stream1, stream2 );
	}
	else
	{
		rbInputStream stream1( anArg1 );
		result = rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->loadFromStream( stream1, static_cast< sf::Shader::Type >( NUM2INT( anArg2 ) ) );
	}
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Shader#set_parameter(name, x)
// Shader#set_parameter(name, x, y)
// Shader#set_parameter(name, x, y, z)
// Shader#set_parameter(name, vector2)
// Shader#set_parameter(name, vector3)
// Shader#set_parameter(name, color)
// Shader#set_parameter(name, transform)
// Shader#set_parameter(name, texture)
// Shader#set_parameter(name, current_texture)
// Shader#setParameter(name, x)
// Shader#setParameter(name, x, y)
// Shader#setParameter(name, x, y, z)
// Shader#setParameter(name, vector2)
// Shader#setParameter(name, vector3)
// Shader#setParameter(name, color)
// Shader#setParameter(name, transform)
// Shader#setParameter(name, texture)
// Shader#setParameter(name, current_texture)
// Shader#[]=(name, x)
// Shader#[]=(name, vector2)
// Shader#[]=(name, vector3)
// Shader#[]=(name, color)
// Shader#[]=(name, transform)
// Shader#[]=(name, texture)
// Shader#[]=(name, current_texture)
VALUE rbShader::SetParameter( int argc, VALUE* args, VALUE aSelf )
{
	rb_check_frozen( aSelf );
	if( argc <= 1 )
		INVALID_ARGUMENT_LIST( argc, "2..4" );
		
	std::string name = StringValueCStr( args[ 0 ] );
	switch( argc )
	{
	case 2:
		if( rb_obj_is_kind_of( args[ 1 ], rb_cNumeric ) == Qtrue )
		{
			rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->setParameter( name, NUM2DBL( args[ 1 ] ) );
		}
		else if( rb_obj_is_kind_of( args[ 1 ], rbVector2::Class ) == Qtrue || ( TYPE( args[ 1 ] ) == T_ARRAY && RARRAY_LEN( args[ 1 ] ) == 2 ) )
		{
			rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->setParameter( name, rbVector2::ToSFMLf( args[ 1 ] ) );
		}
		else if( rb_obj_is_kind_of( args[ 1 ], rbVector3::Class ) == Qtrue || ( TYPE( args[ 1 ] ) == T_ARRAY && RARRAY_LEN( args[ 1 ] ) == 3 ) )
		{
			rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->setParameter( name, rbVector3::ToSFMLf( args[ 1 ] ) );
		}
		else if( rb_obj_is_kind_of( args[ 1 ], rbColor::Class ) == Qtrue || ( TYPE( args[ 1 ] ) == T_ARRAY && RARRAY_LEN( args[ 1 ] ) == 4 ) )
		{
			rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->setParameter( name, rbColor::ToSFML( args[ 1 ] ) );
		}
		else if( rb_obj_is_kind_of( args[ 1 ], rbTransform::Class ) == Qtrue )
		{
			rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->setParameter( name, *rbMacros::ToSFML< sf::Transform >( args[ 1 ], rbTransform::Class ) );
		}
		else if( rb_obj_is_kind_of( args[ 1 ], rbTexture::Class ) == Qtrue )
		{
			rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->setParameter( name, *rbMacros::ToSFML< sf::Texture >( args[ 1 ], rbTexture::Class ) );
		}
		else if( args[ 1 ] == rbShader::Class_CurrentTextureType )
		{
			rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->setParameter( name, sf::Shader::CurrentTexture );
		}
		else
		{
			INVALID_EXPECTED_TYPES7( rb_cNumeric, rbVector2::Class, rbVector3::Class, rbColor::Class, rbTransform::Class, rbTexture::Class, rbShader::Class_CurrentTextureType );
		}
		break;
	case 3:
		rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->setParameter( name, NUM2DBL( args[ 1 ] ), NUM2DBL( args[ 2 ] ) );
		break;
	case 4:
		rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->setParameter( name, NUM2DBL( args[ 1 ] ), NUM2DBL( args[ 2 ] ), NUM2DBL( args[ 3 ] ) );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "2..4" );
	}
	return Qnil;
}

// Shader#marshal_dump
VALUE rbShader::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
	return Qnil;
}

// Shader#==(other)
VALUE rbShader::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbShader::Class ) )
		return Qfalse;
    else if( rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class ) == rbMacros::ToSFML< sf::Shader >( anOther, rbShader::Class ) )
		return Qtrue;
	else
		return Qfalse;
}

// Shader#inspect
// Shader#to_s
VALUE rbShader::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class ) );
}
