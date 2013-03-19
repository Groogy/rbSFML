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

#define GRAPHICS_TRANSFORM_CPP

#include "Transform.hpp"
#include "Rect.hpp"
#include "../InputStream.hpp"
#include "../System/Vector2.hpp"

void rbTransform::Init( VALUE SFML )
{
    rbTransform::Class = rb_define_class_under( SFML, "Transform", rb_cObject );
	
	rb_define_alloc_func( rbTransform::Class, rbMacros::Allocate< sf::Transform > );

    // Instance methods
    ext_define_method( rbTransform::Class, "initialize",             rbTransform::Initialize,          -1 );
    ext_define_method( rbTransform::Class, "initialize_copy",        rbTransform::InitializeCopy,       1 );
	ext_define_method( rbTransform::Class, "matrix",                 rbTransform::GetMatrix,            0 );
	ext_define_method( rbTransform::Class, "inverse",                rbTransform::GetInverse,           0 );
	ext_define_method( rbTransform::Class, "transform_point",        rbTransform::TransformPoint,      -1 );
	ext_define_method( rbTransform::Class, "transform_rect",         rbTransform::TransformRect,        1 );
	ext_define_method( rbTransform::Class, "combine",                rbTransform::Combine,              1 );
	ext_define_method( rbTransform::Class, "translate",              rbTransform::Translate,           -1 );
	ext_define_method( rbTransform::Class, "rotate",                 rbTransform::Rotate,              -1 );
	ext_define_method( rbTransform::Class, "scale",                  rbTransform::Scale,               -1 );
	ext_define_method( rbTransform::Class, "*",                      rbTransform::MultiplyOperator,     1 );
    ext_define_method( rbTransform::Class, "marshal_dump",           rbTransform::MarshalDump,          0 );
	ext_define_method( rbTransform::Class, "marshal_load",           rbTransform::MarshalLoad,          1 );
    ext_define_method( rbTransform::Class, "==",                     rbTransform::Equal,                1 );
    ext_define_method( rbTransform::Class, "inspect",                rbTransform::Inspect,              0 );

    // Instance aliases
    rb_define_alias( rbTransform::Class, "to_s",           "inspect"         );
	rb_define_alias( rbTransform::Class, "get_matrix",     "matrix"          );
	rb_define_alias( rbTransform::Class, "getMatrix",      "matrix"          );
	rb_define_alias( rbTransform::Class, "to_a",           "matrix"          );
	rb_define_alias( rbTransform::Class, "get_inverse",    "inverse"         );
	rb_define_alias( rbTransform::Class, "getInverse",     "inverse"         );
	rb_define_alias( rbTransform::Class, "transformPoint", "transform_point" );
	rb_define_alias( rbTransform::Class, "transformRect",  "transform_rect"  );
	
	if( rb_const_defined( rbTransform::Class, rb_intern( "Identity" ) ) == Qfalse )
		rb_define_const( rbTransform::Class, "Identity", rbMacros::ToConstRuby( &sf::Transform::Identity, rbTransform::Class ) );
}

// Transform#initialize
// Transform#initialize(a00, a01, a02, a10, a11, a12, a20, a21, a22)
VALUE rbTransform::Initialize( int argc, VALUE* args, VALUE aSelf )
{
	if( argc == 9 )
	{
		*rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class ) = sf::Transform(
			NUM2DBL( args[ 0 ] ), NUM2DBL( args[ 1 ] ), NUM2DBL( args[ 2 ] ),
			NUM2DBL( args[ 3 ] ), NUM2DBL( args[ 4 ] ), NUM2DBL( args[ 5 ] ),
			NUM2DBL( args[ 6 ] ), NUM2DBL( args[ 7 ] ), NUM2DBL( args[ 8 ] )
		);
	}
	else if( argc != 0 )
	{
		INVALID_ARGUMENT_LIST( argc, "0 or 9" );
	}
    return Qnil;
}

// Transform#initialize_copy(transform)
VALUE rbTransform::InitializeCopy( VALUE aSelf, VALUE aTransform )
{
    *rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class ) = *rbMacros::ToSFML< sf::Transform >( aTransform, rbTransform::Class );
    return aSelf;
}

// Transform#matrix
// Transform#get_matrix
// Transform#getMatrix
VALUE rbTransform::GetMatrix( VALUE aSelf )
{
	const float* values = rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class )->getMatrix();
	VALUE array = rb_ary_new2( 16 );
	for( unsigned int index = 0; index < 16; index++ )
	{
		rb_ary_store( array, index, rb_float_new( values[ index ] ) );
	}
	rb_obj_freeze( array );
	return array;
}

// Transform#inverse
// Transform#get_inverse
// Transform#getInverse
VALUE rbTransform::GetInverse( VALUE aSelf )
{
	VALUE inverse = rb_class_new_instance( 0, NULL, rbTransform::Class );
	*rbMacros::ToSFML< sf::Transform >( inverse, rbTransform::Class ) = rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class )->getInverse();
	return inverse;
}

// Transform#transform_point(x, y)
// Transform#transform_point(vector2)
// Transform#transformPoint(x, y)
// Transform#transformPoint(vector2)
VALUE rbTransform::TransformPoint( int argc, VALUE* args, VALUE aSelf )
{
	VALUE x;
	VALUE y;
	
	switch( argc )
	{
	case 2:
		x = args[ 0 ];
		y = args[ 1 ];
		break;
	case 1:
		y = rbVector2::ToRuby( args[ 0 ] );
		x = rbVector2::GetX( y );
		y = rbVector2::GetY( y );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	sf::Vector2f point = rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class )->transformPoint( NUM2DBL( x ), NUM2DBL( y ) );
	return rbVector2::ToRuby( point );
}

// Transform#transform_rect(rect)
// Transform#transformRect(rect)
VALUE rbTransform::TransformRect( VALUE aSelf, VALUE aRect )
{
	return rbRect::ToRuby( rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class )->transformRect( rbRect::ToSFMLf( aRect ) ) );	
}

// Transform#combine(transform)
VALUE rbTransform::Combine( VALUE aSelf, VALUE aTransform )
{
	VALUE result = rb_class_new_instance( 0, NULL, rbTransform::Class );
	*rbMacros::ToSFML< sf::Transform >( result, rbTransform::Class ) = rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class )->combine( *rbMacros::ToSFML< sf::Transform >( aTransform, rbTransform::Class ) );
	return result;
}

// Transform#translate(x, y)
// Transform#translate(vector2)
VALUE rbTransform::Translate( int argc, VALUE* args, VALUE aSelf )
{	
	rb_check_frozen( aSelf );
	
	VALUE x;
	VALUE y;
	
	switch( argc )
	{
	case 2:
		x = args[ 0 ];
		y = args[ 1 ];
		break;
	case 1:
		y = rbVector2::ToRuby( args[ 0 ] );
		x = rbVector2::GetX( y );
		y = rbVector2::GetY( y );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class )->translate( NUM2DBL( x ), NUM2DBL( y ) );
	return aSelf;
}

// Transform#rotate(angle)
// Transform#rotate(angle, center_x, center_y)
// Transform#rotate(angle, vector2)
VALUE rbTransform::Rotate( int argc, VALUE* args, VALUE aSelf )
{	
	switch( argc )
	{
	case 1:
		rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class )->rotate( NUM2DBL( args[ 0 ] ) );
		break;
	case 2:
		rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class )->rotate( NUM2DBL( args[ 0 ] ), rbVector2::ToSFMLf( args[ 1 ] ) );
		break;
	case 3:
		rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class )->rotate( NUM2DBL( args[ 0 ] ), NUM2DBL( args[ 1 ] ), NUM2DBL( args[ 2 ] ) );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1..3" );
	}
	
	return aSelf;
}

// Transform#scale(scale_x, scale_y)
// Transform#scale(scale_x, scale_y, center_x, center_y)
// Transform#scale(factors)
// Transform#scale(factors, center)
VALUE rbTransform::Scale( int argc, VALUE* args, VALUE aSelf )
{	
	switch( argc )
	{
	case 1:
		rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class )->scale( rbVector2::ToSFMLf( args[ 0 ] ) );
		break;
	case 2:
		if( rb_obj_is_kind_of( args[ 0 ], rbVector2::Class ) == Qtrue )
		{
			rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class )->scale( rbVector2::ToSFMLf( args[ 0 ] ), rbVector2::ToSFMLf( args[ 1 ] ) );
		}
		else
		{
			rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class )->scale( NUM2DBL( args[ 0 ] ), NUM2DBL( args[ 1 ] ) );
		}
		break;
	case 4:
		rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class )->scale( NUM2DBL( args[ 0 ] ), NUM2DBL( args[ 1 ] ), NUM2DBL( args[ 2 ] ), NUM2DBL( args[ 3 ] ) );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1, 2 or 4" );
	}
	
	return aSelf;
}

// Transform#*(right)
VALUE rbTransform::MultiplyOperator( VALUE aSelf, VALUE aRight )
{
	if( rb_obj_is_kind_of( aRight, rbVector2::Class ) == Qtrue )
	{
		return rbTransform::TransformPoint( 1, &aRight, aSelf );
	}
	else
	{
		return rbTransform::Combine( aSelf, aRight );
	}
}

// Transform#marshal_dump
VALUE rbTransform::MarshalDump( VALUE aSelf )
{
    VALUE data[9];
	const float* values = rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class )->getMatrix();
	data[0] = rb_float_new( values[ 0 ] );
	data[1] = rb_float_new( values[ 4 ] );
	data[2] = rb_float_new( values[ 12 ] );
	data[3] = rb_float_new( values[ 1 ] );
	data[4] = rb_float_new( values[ 5 ] );
	data[5] = rb_float_new( values[ 13 ] );
	data[6] = rb_float_new( values[ 3 ] );
	data[7] = rb_float_new( values[ 7 ] );
	data[8] = rb_float_new( values[ 15 ] );
	return rb_ary_new4( 9, data );
}

// Transform#marshal_load(data)
VALUE rbTransform::MarshalLoad( VALUE aSelf, VALUE someData )
{
	VALUE* data = RARRAY_PTR( someData );
	*rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class ) = sf::Transform(
		NUM2DBL( data[ 0 ] ), NUM2DBL( data[ 1 ] ), NUM2DBL( data[ 2 ] ),
		NUM2DBL( data[ 3 ] ), NUM2DBL( data[ 4 ] ), NUM2DBL( data[ 5 ] ),
		NUM2DBL( data[ 6 ] ), NUM2DBL( data[ 7 ] ), NUM2DBL( data[ 8 ] )
	);
	return Qnil;
}

// Transform#==(other)
VALUE rbTransform::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbTransform::Class ) )
		return Qfalse;
    else if( rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class ) == rbMacros::ToSFML< sf::Transform >( anOther, rbTransform::Class ) )
		return Qtrue;
	else
		return Qfalse;
}

// Transform#inspect
// Transform#to_s
VALUE rbTransform::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::Transform >( aSelf, rbTransform::Class ) );
}
