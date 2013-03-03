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

#define GRAPHICS_TEXTURE_CPP

#include "Texture.hpp"
#include "Image.hpp"
#include "Rect.hpp"
#include "InputStream.hpp"
#include "System/SFML.hpp"
#include "Window/Window.hpp"

void rbTexture::Init( VALUE SFML )
{
    rbTexture::Class = rb_define_class_under( SFML, "Texture", rb_cObject );
	
	// Class methods
	rb_define_alloc_func( rbTexture::Class, rbMacros::Allocate< sf::Texture > );
	ext_define_class_method( rbTexture::Class, "maximum_size", rbTexture::GetMaximumSize, 0 );
	ext_define_class_method( rbTexture::Class, "bind",         rbTexture::Bind,          -1 );

    // Instance methods
    ext_define_method( rbTexture::Class, "initialize",             rbTexture::Initialize,          -1 );
    ext_define_method( rbTexture::Class, "initialize_copy",        rbTexture::InitializeCopy,       1 );
	ext_define_method( rbTexture::Class, "create",			      rbTexture::Create,               2 );
	ext_define_method( rbTexture::Class, "load_from_file",	      rbTexture::LoadFromFile,        -1 );
	ext_define_method( rbTexture::Class, "load_from_memory",       rbTexture::LoadFromMemory,      -1 );
	ext_define_method( rbTexture::Class, "load_from_stream",       rbTexture::LoadFromStream,      -1 );
	ext_define_method( rbTexture::Class, "load_from_image" ,       rbTexture::LoadFromImage,       -1 );
	ext_define_method( rbTexture::Class, "size",                   rbTexture::GetSize,              0 );
	ext_define_method( rbTexture::Class, "copy_to_image",          rbTexture::CopyToImage,          0 );
	ext_define_method( rbTexture::Class, "update",                 rbTexture::Update,              -1 );
	ext_define_method( rbTexture::Class, "smooth=",                rbTexture::SetSmooth,            1 );
	ext_define_method( rbTexture::Class, "smooth?",                rbTexture::GetSmooth,            0 );
	ext_define_method( rbTexture::Class, "repeated=",              rbTexture::SetRepeated,          1 );
	ext_define_method( rbTexture::Class, "repeated?",              rbTexture::GetRepeated,          0 );
    ext_define_method( rbTexture::Class, "marshal_dump",           rbTexture::MarshalDump,          0 );
    ext_define_method( rbTexture::Class, "==",                     rbTexture::Equal,                1 );
    ext_define_method( rbTexture::Class, "inspect",                rbTexture::Inspect,              0 );
	
	// Class aliases
	rb_define_alias( rb_singleton_class( rbTexture::Class ), "get_maximum_size", "maximum_size" );
	rb_define_alias( rb_singleton_class( rbTexture::Class ), "getMaximumSize", "maximum_size" );

    // Instance aliases
    rb_define_alias( rbTexture::Class, "to_s",           "inspect"          );
	rb_define_alias( rbTexture::Class, "loadFromFile",   "load_from_file"   );
	rb_define_alias( rbTexture::Class, "loadFromMemory", "load_from_memory" );
	rb_define_alias( rbTexture::Class, "loadFromStream", "load_from_stream" );
	rb_define_alias( rbTexture::Class, "loadFromImage",  "load_from_image"  );
	rb_define_alias( rbTexture::Class, "to_image",       "copy_to_image"    );
	rb_define_alias( rbTexture::Class, "copyToImage",    "copy_to_image"    );
	rb_define_alias( rbTexture::Class, "get_size",       "size"             );
	rb_define_alias( rbTexture::Class, "getSize",        "size"             );
	rb_define_alias( rbTexture::Class, "smooth",         "smooth?"          );
	rb_define_alias( rbTexture::Class, "isSmooth",       "smooth?"          );
	rb_define_alias( rbTexture::Class, "is_smooth?",     "smooth?"          );
	rb_define_alias( rbTexture::Class, "is_smooth",      "smooth?"          );
	rb_define_alias( rbTexture::Class, "repeated",       "repeated?"        );
	rb_define_alias( rbTexture::Class, "is_repeated?",   "repeated?"        );
	rb_define_alias( rbTexture::Class, "is_repeated",    "repeated?"        );
	rb_define_alias( rbTexture::Class, "isRepeated",     "repeated?"        );
	
	rb_define_const( rbTexture::Class, "Normalized", INT2NUM( sf::Texture::Normalized ) );
	rb_define_const( rbTexture::Class, "Pixels",     INT2NUM( sf::Texture::Pixels ) );
}

// Texture.maximum_size()
VALUE rbTexture::GetMaximumSize( VALUE aSelf )
{
	return INT2NUM( sf::Texture::getMaximumSize() );	
}

// Texture.bind
// Texture.bind(texture, coordinate_type = Normalized)
VALUE rbTexture::Bind( int argc, VALUE* args, VALUE aSelf )
{
	sf::Texture::CoordinateType type = sf::Texture::Normalized;

	switch( argc )
	{
	case 0:
		sf::Texture::bind( NULL );
		break;
	case 2:
		type = static_cast< sf::Texture::CoordinateType >( NUM2INT( args[ 1 ] ) );
	case 1:
		sf::Texture::bind( rbMacros::ToSFML< sf::Texture >( args[ 0 ], rbTexture::Class ), type );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "0..2" );
	}

	return Qnil;
}

// Texture#initialize
// Texture#initialize(filename)
// Texture#initialize(width, height)
VALUE rbTexture::Initialize( int argc, VALUE* args, VALUE aSelf )
{
	if( argc == 2 )
	{
		rbTexture::Create( aSelf, args[ 0 ], args[ 1 ] );
	}
	else if( argc == 1 )
	{
		rbTexture::LoadFromFile( argc, args, aSelf );
	}
		
    return Qnil;
}

// Texture#initialize_copy(texture)
VALUE rbTexture::InitializeCopy( VALUE aSelf, VALUE aTexture )
{
    *rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class ) = *rbMacros::ToSFML< sf::Texture >( aTexture, rbTexture::Class );
    return aSelf;
}

// Texture#create(width, height)
VALUE rbTexture::Create( VALUE aSelf, VALUE aWidth, VALUE aHeight )
{
	rb_check_frozen( aSelf );
	
	rbSFML::PrepareErrorStream();
	bool result = rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->create( NUM2UINT( aWidth ), NUM2UINT( aHeight ) );
	rbSFML::CheckRaise();
	return result ? Qtrue : Qfalse;
}

// Texture#load_from_file(filename, area = nil)
// Texture#loadFromFile(filename, area = nil)
VALUE rbTexture::LoadFromFile( int argc, VALUE* args, VALUE aSelf )
{
	rb_check_frozen( aSelf );
	
	VALUE filename;
	VALUE area = rbRect::ToRuby( sf::IntRect() );
	
	switch( argc )
	{
	case 2:
		area = rbRect::ToRuby( args[ 1 ] );
	case 1:
		filename = args[ 0 ];
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	rbSFML::PrepareErrorStream();
#ifdef SFML_GROOGY_EXTENSION
  bool result = rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->loadFromFile( StringValueCStr( filename ), sf::TextureFormat::RGBA8, rbRect::ToSFMLi( area ) );
#else
	bool result = rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->loadFromFile( StringValueCStr( filename ), rbRect::ToSFMLi( area ) );
#endif
	rbSFML::CheckRaise();
	return result ? Qtrue : Qfalse;
}

// Texture#load_from_memory(data, area = nil)
// Texture#loadFromMemory(data, area = nil)
VALUE rbTexture::LoadFromMemory( int argc, VALUE* args, VALUE aSelf )
{
	rb_check_frozen( aSelf );
	
	VALUE data;
	VALUE area = rbRect::ToRuby( sf::IntRect() );
	
	switch( argc )
	{
	case 2:
		area = rbRect::ToRuby( args[ 1 ] );
	case 1:
		data = args[ 0 ];
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	rbSFML::PrepareErrorStream();
#ifdef SFML_GROOGY_EXTENSION
  bool result = rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->loadFromMemory( RSTRING_PTR( data ),
																						  RSTRING_LEN( data ), sf::TextureFormat::RGBA8, rbRect::ToSFMLi( area ) );
#else
	bool result = rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->loadFromMemory( RSTRING_PTR( data ),
																						  RSTRING_LEN( data ), rbRect::ToSFMLi( area ) );
#endif
	rbSFML::CheckRaise();
	return result ? Qtrue : Qfalse;
}

// Texture#load_from_stream(stream, area = nil)
// Texture#loadFromStream(stream, area = nil)
VALUE rbTexture::LoadFromStream( int argc, VALUE* args, VALUE aSelf )
{
	rb_check_frozen( aSelf );
	
	VALUE streamObj;
	VALUE area = rbRect::ToRuby( sf::IntRect() );
	
	switch( argc )
	{
	case 2:
		area = rbRect::ToRuby( args[ 1 ] );
	case 1:
		streamObj = args[ 0 ];
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	rbInputStream stream( streamObj );
	rbSFML::PrepareErrorStream();
#ifdef SFML_GROOGY_EXTENSION
  bool result = rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->loadFromStream( stream, sf::TextureFormat::RGBA8, rbRect::ToSFMLi( area ) );
#else
	bool result = rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->loadFromStream( stream, rbRect::ToSFMLi( area ) );
#endif
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Texture#load_from_image(image, area = nil)
// Texture#loadFromImage(image, area = nil)
VALUE rbTexture::LoadFromImage( int argc, VALUE* args, VALUE aSelf )
{
	rb_check_frozen( aSelf );
	
	VALUE image;
	VALUE area = rbRect::ToRuby( sf::IntRect() );
	
	switch( argc )
	{
	case 2:
		area = rbRect::ToRuby( args[ 1 ] );
	case 1:
		image = args[ 0 ];
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	rbSFML::PrepareErrorStream();
#ifdef SFML_GROOGY_EXTENSION
  bool result = rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->loadFromImage( *rbMacros::ToSFML< sf::Image >( image, rbImage::Class ), sf::TextureFormat::RGBA8, rbRect::ToSFMLi( area ) );
#else
	bool result = rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->loadFromImage( *rbMacros::ToSFML< sf::Image >( image, rbImage::Class ), rbRect::ToSFMLi( area ) );
#endif
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Texture#size
// Texture#get_size
// Texture#getSize
VALUE rbTexture::GetSize( VALUE aSelf )
{
	return rbVector2::ToRuby( rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->getSize() );
}

// Texture#copy_to_image
// Texture#copyToImage
// Texture#to_image
VALUE rbTexture::CopyToImage( VALUE aSelf )
{
	VALUE image = rb_class_new_instance( 0, NULL, rbImage::Class );
	*rbMacros::ToSFML< sf::Image >( image, rbImage::Class ) = rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->copyToImage();
	return image;
}

// Texture#update(pixels)
// Texture#update(pixels, width, height, x, y)
// Texture#update(image)
// Texture#update(image, x, y)
// Texture#update(window)
// Texture#update(window, x, y)
static VALUE rbTexture::Update( int argc, VALUE* args, VALUE aSelf )
{
	rb_check_frozen( aSelf );
	
	sf::Texture* texture = rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class );
	switch( argc )
	{
	case 1:
		if( rb_obj_is_kind_of( args[ 0 ], rb_cArray ) )
		{
			const unsigned int arraySize = RARRAY_LEN( args[ 0 ] );
			sf::Uint8* pixels = static_cast< sf::Uint8* >( xmalloc( sizeof( sf::Uint8 ) * arraySize ) );
			for( unsigned int index = 0; index < arraySize; index++ )
			{
				pixels[ index ] = NUM2INT( rb_ary_entry( args[ 0 ], index ) );
			}
			texture->update( pixels );
			xfree( pixels );
		}
		else if( rb_obj_is_kind_of( args[ 0 ], rbImage::Class ) )
		{
			sf::Image* image = rbMacros::ToSFML< sf::Image >( args[ 0 ], rbImage::Class );
			texture->update( *image );
		}
		else if( rb_obj_is_kind_of( args[ 0 ], rbWindow::Class ) )
		{
			sf::Window* window = rbMacros::ToSFML< sf::Window >( args[ 0 ], rbWindow::Class );
			texture->update( *window );
		}
		else
		{
			INVALID_EXPECTED_TYPES3( rb_cArray, rbImage::Class, rbWindow::Class );
		}
		break;
	case 3:
		if( rb_obj_is_kind_of( args[ 0 ], rbImage::Class ) )
		{
			sf::Image* image = rbMacros::ToSFML< sf::Image >( args[ 0 ], rbImage::Class );
			texture->update( *image, NUM2INT( args[ 1 ] ), NUM2INT( args[ 2 ] ) );
		}
		else if( rb_obj_is_kind_of( args[ 0 ], rbWindow::Class ) )
		{
			sf::Window* window = rbMacros::ToSFML< sf::Window >( args[ 0 ], rbWindow::Class );
			texture->update( *window, NUM2INT( args[ 1 ] ), NUM2INT( args[ 2 ] ) );
		}
		else
		{
			INVALID_EXPECTED_TYPES( rbImage::Class, rbWindow::Class );
		}
		break;
	case 5:
		if( rb_obj_is_kind_of( args[ 0 ], rb_cArray ) )
		{
			const unsigned int arraySize = RARRAY_LEN( args[ 0 ] );
			sf::Uint8* pixels = static_cast< sf::Uint8* >( xmalloc( sizeof( sf::Uint8 ) * arraySize ) );
			for( unsigned int index = 0; index < arraySize; index++ )
			{
				pixels[ index ] = NUM2INT( rb_ary_entry( args[ 0 ], index ) );
			}
			texture->update( pixels, NUM2INT( args[ 1 ] ), NUM2INT( args[ 2 ] ), NUM2INT( args[ 3 ] ), NUM2INT( args[ 4 ] ) );
			xfree( pixels );
		}
		else
		{
			INVALID_EXPECTED_TYPE( rb_cArray );
		}
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1, 3, or 5" );
	}
	
	return Qnil;
}

// Texture#smooth=(flag)
// Texture#set_smooth(flag)
// Texture#setSmooth(flag)
VALUE rbTexture::SetSmooth( VALUE aSelf, VALUE aFlag )
{
	rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->setSmooth( RTEST( aFlag ) );
	return Qnil;
}

// Texture#smooth?
// Texture#is_smooth?
// Texture#is_smooth
// Texture#isSmooth
VALUE rbTexture::GetSmooth( VALUE aSelf )
{
	bool result = rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->isSmooth();
	return result == true ? Qtrue : Qfalse;
}

// Texture#repeated=(flag)
// Texture#set_repeated(flag)
// Texture#setRepeated(flag)
VALUE rbTexture::SetRepeated( VALUE aSelf, VALUE aFlag )
{
	rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->setRepeated( RTEST( aFlag ) );
	return Qnil;
}

// Texture#repeated?
// Texture#is_repeated?
// Texture#is_repeated
// Texture#isRepeated
VALUE rbTexture::GetRepeated( VALUE aSelf )
{
	bool result = rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->isRepeated();
	return result == true ? Qtrue : Qfalse;
}

// Texture#marshal_dump
VALUE rbTexture::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
	return Qnil;
}

// Texture#==(other)
VALUE rbTexture::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbTexture::Class ) )
		return Qfalse;
    else if( rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class ) == rbMacros::ToSFML< sf::Texture >( anOther, rbTexture::Class ) )
		return Qtrue;
	else
		return Qfalse;
}

// Texture#inspect
// Texture#to_s
VALUE rbTexture::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%ix%i, %p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->getSize().x,
					   rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class )->getSize().y,
					   rbMacros::ToSFML< sf::Texture >( aSelf, rbTexture::Class ) );
}
