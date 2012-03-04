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

#define GRAPHICS_IMAGE_CPP

#include "Image.hpp"
#include "Color.hpp"
#include "Rect.hpp"
#include "InputStream.hpp"
#include "System/SFML.hpp"

void rbImage::Init( VALUE SFML )
{
    rbImage::Class = rb_define_class_under( SFML, "Image", rb_cObject );
	
	rb_define_alloc_func( rbImage::Class, rbMacros::Allocate< sf::Image > );

    // Instance methods
    rb_define_method( rbImage::Class, "initialize",             rbImage::Initialize,          -1 );
    rb_define_method( rbImage::Class, "initialize_copy",        rbImage::InitializeCopy,       1 );
	rb_define_method( rbImage::Class, "create",			        rbImage::Create,              -1 );
	rb_define_method( rbImage::Class, "load_from_file",	        rbImage::LoadFromFile,         1 );
	rb_define_method( rbImage::Class, "load_from_memory",       rbImage::LoadFromMemory,       1 );
	rb_define_method( rbImage::Class, "load_from_stream",       rbImage::LoadFromStream,       1 );
	rb_define_method( rbImage::Class, "save_to_file",           rbImage::SaveToFile,           1 );
	rb_define_method( rbImage::Class, "width",                  rbImage::GetWidth,             0 );
	rb_define_method( rbImage::Class, "height",                 rbImage::GetHeight,            0 );
	rb_define_method( rbImage::Class, "create_mask_from_color", rbImage::CreateMaskFromColor, -1 );
	rb_define_method( rbImage::Class, "copy",                   rbImage::Copy,                -1 );
	rb_define_method( rbImage::Class, "set_pixel",              rbImage::SetPixel,             3 );
	rb_define_method( rbImage::Class, "get_pixel",              rbImage::GetPixel,             2 );
	rb_define_method( rbImage::Class, "pixels",                 rbImage::GetPixelsPtr,         0 );
	rb_define_method( rbImage::Class, "flip_horizontally",      rbImage::FlipHorizontally,     0 );
	rb_define_method( rbImage::Class, "flip_vertically",        rbImage::FlipVertically,       0 );
    rb_define_method( rbImage::Class, "marshal_dump",           rbImage::MarshalDump,          0 );
    rb_define_method( rbImage::Class, "==",                     rbImage::Equal,                1 );
    rb_define_method( rbImage::Class, "inspect",                rbImage::Inspect,              0 );
    rb_define_method( rbImage::Class, "memory_usage",           rbImage::GetMemoryUsage,       0 );

    // Instance aliases
    rb_define_alias( rbImage::Class, "to_s",   "inspect" );
}

// Image#initialize
// Image#initialize(filename)
// Image#initialize(width, height, color = SFML::Color::Black)
// Image#initialize(width, height, pixels)
VALUE rbImage::Initialize( int argc, VALUE* args, VALUE aSelf )
{
	if( argc >= 2 )
	{
		rbImage::Create( argc, args, aSelf );
	}
	else if( argc == 1 )
	{
		rbImage::LoadFromFile( aSelf, args[ 0 ] );
	}
		
    return Qnil;
}

// Image#initialize_copy(image)
VALUE rbImage::InitializeCopy( VALUE aSelf, VALUE anImage )
{
    *rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class ) = *rbMacros::ToSFML< sf::Image >( anImage, rbImage::Class );
    return aSelf;
}

// Image#create(width, height, color = SFML::Color::Black)
// Image#create(width, height, pixels)
VALUE rbImage::Create( int argc, VALUE* args, VALUE aSelf )
{
	rb_check_frozen( aSelf );
	
	VALUE color = Qnil;
	switch( argc )
	{
	case 2:
		color = rb_const_get( rbColor::Class, rb_intern( "Black" ) );
		rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->Create( NUM2INT( args[ 0 ] ), NUM2INT( args[ 1 ] ), rbColor::ToSFML( color ) );
		break;
	case 3:
		if( ( TYPE( args[ 2 ] ) == T_ARRAY && ( RARRAY_LEN( args[ 2 ] ) == 3 || RARRAY_LEN( args[ 2 ] ) == 4 ) ) || rb_obj_is_kind_of( args[ 2 ], rbColor::Class ) == Qtrue )
		{
			color = rbColor::ToRuby( args[ 2 ] );
			rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->Create( NUM2INT( args[ 0 ] ), NUM2INT( args[ 1 ] ), rbColor::ToSFML( color ) );
		}
		else if( TYPE( args[ 2 ] ) == T_ARRAY )
		{
			VALUE pixelsArray = rb_funcall( args[ 2 ], rb_intern( "flatten" ), 0 );
			const unsigned int length = RARRAY_LEN( pixelsArray );
			sf::Uint8* pixels = static_cast< sf::Uint8* >( xmalloc( sizeof( sf::Uint8 ) * length ) );
			for( unsigned int index = 0; index < length; index++ )
			{
				pixels[ index ] = rb_ary_entry( pixelsArray, index );
			}
			rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->Create( NUM2INT( args[ 0 ] ), NUM2INT( args[ 1 ] ), pixels );
			xfree( pixels );
		}
		else
		{
			INVALID_EXPECTED_TYPE( rb_cArray );
		}
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "2 or 3" );
	}
	
	return Qnil;
}

// Image#load_from_file(filename)
VALUE rbImage::LoadFromFile( VALUE aSelf, VALUE aFilename )
{
	rb_check_frozen( aSelf );
	
	rbSFML::PrepareErrorStream();
	bool result = rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->LoadFromFile( StringValueCStr( aFilename ) );
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Image#load_from_memory(data)
VALUE rbImage::LoadFromMemory( VALUE aSelf, VALUE someData )
{
	rb_check_frozen( aSelf );
	
	rbSFML::PrepareErrorStream();
	bool result = rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->LoadFromMemory( RSTRING_PTR( someData ),
																						  RSTRING_LEN( someData ) );
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Image#load_from_stream(stream)
VALUE rbImage::LoadFromStream( VALUE aSelf, VALUE aStream )
{
	rb_check_frozen( aSelf );
	
	rbInputStream stream( aStream );
	rbSFML::PrepareErrorStream();
	bool result = rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->LoadFromStream( stream );
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Image#save_to_file(filename)
VALUE rbImage::SaveToFile( VALUE aSelf, VALUE aFilename )
{
	rbSFML::PrepareErrorStream();
	bool result = rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->SaveToFile( StringValueCStr( aFilename ) );
	rbSFML::CheckWarn();
	return result ? Qtrue : Qfalse;
}

// Image#width
VALUE rbImage::GetWidth( VALUE aSelf )
{
	return INT2NUM( rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->GetWidth() );
}

// Image#height
VALUE rbImage::GetHeight( VALUE aSelf )
{
	return INT2NUM( rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->GetHeight() );
}

// Image#create_mask_from_color(color, alpha=0)
VALUE rbImage::CreateMaskFromColor( int argc, VALUE* args, VALUE aSelf )
{
	rb_check_frozen( aSelf );
	
	VALUE color;
	VALUE alpha = INT2NUM( 0 );
	switch( argc )
	{
	case 2:
		alpha = args[ 1 ];
	case 1:
		color = rbColor::ToRuby( args[ 0 ] );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->CreateMaskFromColor( rbColor::ToSFML( color ), NUM2INT( alpha ) );
	return Qnil;
}

// Image#copy(image, dest_x, dest_y, source_rect = nil, apply_alpha = false)
VALUE rbImage::Copy( int argc, VALUE* args, VALUE aSelf )
{
	rb_check_frozen( aSelf );
	
	VALUE sourceImage;
	VALUE destX;
	VALUE destY;
	VALUE sourceRect = rbRect::ToRuby( sf::IntRect( 0, 0, 0, 0 ) );
	VALUE applyAlpha = Qfalse;
	
	switch( argc )
	{
	case 5:
		applyAlpha = args[ 4 ];
	case 4:
		if( args[ 3 ] != Qnil )
			sourceRect = rbRect::ToRuby( args[ 3 ] );
		
	case 3:
		destX = args[ 2 ];
		destY = args[ 1 ];
		sourceImage = rbMacros::ToRuby( args[ 0 ], rbImage::Class );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "3..5" );
	}
	
	rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->Copy( *rbMacros::ToSFML< sf::Image >( sourceImage, rbImage::Class ), 
																  NUM2UINT( destX ), NUM2UINT( destY ), rbRect::ToSFMLi( sourceRect ), 
																  applyAlpha == Qtrue ? true : false );
																  
	return Qnil;
}

// Image#set_pixel(x, y, color)
VALUE rbImage::SetPixel( VALUE aSelf, VALUE anX, VALUE anY, VALUE aColor )
{
	rb_check_frozen( aSelf );
	
	rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->SetPixel( NUM2INT( anX ), NUM2INT( anY ), rbColor::ToSFML( aColor ) );
	return Qnil;
}

// Image#get_pixel(x, y)
VALUE rbImage::GetPixel( VALUE aSelf, VALUE anX, VALUE anY )
{
	return rbColor::ToRuby( rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->GetPixel( NUM2INT( anX ), NUM2INT( anY ) ) );
}

// Image#pixels()
VALUE rbImage::GetPixelsPtr( VALUE aSelf )
{
	sf::Image* selfImage = rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class );
	const sf::Uint8* pixels = selfImage->GetPixelsPtr();
	const unsigned int pixelArraySize = selfImage->GetWidth() * selfImage->GetHeight() * 4;
	VALUE pixelsArray = rb_ary_new2( pixelArraySize );
	
	for( unsigned int index = 0; index < pixelArraySize; index++ )
	{
		rb_ary_store( pixelsArray, index, INT2NUM( pixels[ index ] ) );
	}
	rb_obj_freeze( pixelsArray );
	return pixelsArray;
}

// Image#flip_horizontally
VALUE rbImage::FlipHorizontally( VALUE aSelf )
{
	rb_check_frozen( aSelf );
	rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->FlipHorizontally();
	return Qnil;
}

// Image#flip_vertically
VALUE rbImage::FlipVertically( VALUE aSelf )
{
	rb_check_frozen( aSelf );
	rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->FlipVertically();
	return Qnil;
}

// Image#marshal_dump
VALUE rbImage::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
	return Qnil;
}

// Image#==(other)
VALUE rbImage::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbImage::Class ) )
		return Qfalse;
    else if( rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class ) == rbMacros::ToSFML< sf::Image >( anOther, rbImage::Class ) )
		return Qtrue;
	else
		return Qfalse;
}

// Image#inspect
// Image#to_s
VALUE rbImage::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%ix%i, %p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->GetWidth(),
					   rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class )->GetHeight(),
					   rbMacros::ToSFML< sf::Image >( aSelf, rbImage::Class ) );
}

// Image#memory_usage
VALUE rbImage::GetMemoryUsage( VALUE aSelf )
{
	sf::Image* image = rbMacros::ToSFML< sf::Image >( aSelf );
    return INT2FIX( sizeof( sf::Image ) + image->GetWidth() * image->GetHeight() );
}
