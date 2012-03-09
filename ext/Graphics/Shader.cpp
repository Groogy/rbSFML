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
#include "InputStream.hpp"
#include "System/SFML.hpp"
#include "System/Vector2.hpp"
#include "System/Vector3.hpp"
#include "System/NonCopyable.hpp"
#include "Graphics/Transform.hpp"
#include "Graphics/Texture.hpp"

void rbShader::Init( VALUE SFML )
{
    rbShader::Class = rb_define_class_under( SFML, "Shader", rb_cObject );
	rb_include_module( rbShader::Class, rbNonCopyable::Module );
	
	// Class methods
	rb_define_alloc_func( rbShader::Class, rbMacros::Allocate< sf::Shader > );
	rb_define_class_method( rbShader::Class, "available?", rbShader::IsAvailable, 0 );

    // Instance methods
    rb_define_method( rbShader::Class, "initialize",             rbShader::Initialize,          -1 );
	rb_define_method( rbShader::Class, "load_from_file",	     rbShader::LoadFromFile,         2 );
	rb_define_method( rbShader::Class, "load_from_memory",       rbShader::LoadFromMemory,       2 );
	rb_define_method( rbShader::Class, "load_from_stream",       rbShader::LoadFromStream,       2 );
	rb_define_method( rbShader::Class, "bind",                   rbShader::Bind,                 0 );
	rb_define_method( rbShader::Class, "unbind",                 rbShader::Unbind,               0 );
    rb_define_method( rbShader::Class, "marshal_dump",           rbShader::MarshalDump,          0 );
    rb_define_method( rbShader::Class, "==",                     rbShader::Equal,                1 );
    rb_define_method( rbShader::Class, "inspect",                rbShader::Inspect,              0 );
    rb_define_method( rbShader::Class, "memory_usage",           rbShader::GetMemoryUsage,       0 );
	
	// Class aliases
	rb_define_alias( rb_singleton_class( rbShader::Class ), "is_available?", "available?" );

    // Instance aliases
    rb_define_alias( rbShader::Class, "to_s",       "inspect"       );
	
	rb_define_const( rbShader::Class, "Vertex",   INT2NUM( sf::Shader::Vertex )   );
	rb_define_const( rbShader::Class, "Fragment", INT2NUM( sf::Shader::Fragment ) );
}

// Shader.available?()
VALUE rbShader::IsAvailable( VALUE aSelf )
{
	return RBOOL( sf::Shader::IsAvailable() );	
}

// Shader#initialize
// Shader#initialize(vertex_filename, fragment_filename)
// Shader#initialize(shader_filename, shader_type)
VALUE rbShader::Initialize( int argc, VALUE* args, VALUE aSelf )
{	
    return Qnil;
}

// Shader#load_from_file(filename, type)
// Shader#load_from_file(vertex_filename, fragment_filename)
VALUE rbShader::LoadFromFile( VALUE aSelf, VALUE anArg1, VALUE anArg2 )
{
	rb_check_frozen( aSelf );
	rbSFML::PrepareErrorStream();
	bool result = false;
	if( rb_obj_is_kind_of( anArg2, rb_cString ) == Qtrue )
	{
		result = rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->LoadFromFile( StringValueCStr( anArg1 ), StringValueCStr( anArg2 ) );
	}
	else
	{
		result = rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->LoadFromFile( StringValueCStr( anArg1 ), static_cast< sf::Shader::Type >( NUM2INT( anArg2 ) ) );
	}
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Shader#load_from_memory(data, type)
// Shader#load_from_memory(vertex_data, fragment_data)
VALUE rbShader::LoadFromMemory( VALUE aSelf, VALUE anArg1, VALUE anArg2 )
{
	rb_check_frozen( aSelf );
	rbSFML::PrepareErrorStream();
	bool result = false;
	if( rb_obj_is_kind_of( anArg2, rb_cString ) == Qtrue )
	{
		result = rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->LoadFromMemory( std::string( RSTRING_PTR( anArg1 ), RSTRING_LEN( anArg1 ) ), std::string( RSTRING_PTR( anArg2 ), RSTRING_LEN( anArg2 ) ) );
	}
	else
	{
		result = rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->LoadFromMemory( std::string( RSTRING_PTR( anArg1 ), RSTRING_LEN( anArg1 ) ), static_cast< sf::Shader::Type >( NUM2INT( anArg2 ) ) );
	}
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Shader#load_from_stream(stream, type)
// Shader#load_from_stream(vertex_stream, fragment_stream)
VALUE rbShader::LoadFromStream( VALUE aSelf, VALUE anArg1, VALUE anArg2 )
{
	rb_check_frozen( aSelf );
	rbSFML::PrepareErrorStream();
	bool result = false;
	if( rb_obj_is_kind_of( anArg2, rb_cIO ) == Qtrue )
	{
		rbInputStream stream1( anArg1 );
		rbInputStream stream2( anArg2 );
		result = rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->LoadFromStream( stream1, stream2 );
	}
	else
	{
		rbInputStream stream1( anArg1 );
		result = rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->LoadFromStream( stream1, static_cast< sf::Shader::Type >( NUM2INT( anArg2 ) ) );
	}
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Shader#bind()
VALUE rbShader::Bind( VALUE aSelf )
{
	rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->Bind();
	return Qnil;
}

// Shader#unbind()
VALUE rbShader::Unbind( VALUE aSelf )
{
	rbMacros::ToSFML< sf::Shader >( aSelf, rbShader::Class )->Unbind();
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

// Shader#memory_usage
VALUE rbShader::GetMemoryUsage( VALUE aSelf )
{
    return INT2FIX( sizeof( sf::Shader ) );
}
