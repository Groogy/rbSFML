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

#define GRAPHICS_RECT_CPP

#include "Rect.hpp"
#include "System/Vector2.hpp"

void rbRect::Init( VALUE SFML )
{
    rbRect::Class = rb_define_class_under( SFML, "Rect", rb_cObject );

    // Instance methods
    ext_define_method( rbRect::Class, "initialize",      rbRect::Initialize,     	-1 );
    ext_define_method( rbRect::Class, "initialize_copy", rbRect::InitializeCopy,  	 1 );
	ext_define_method( rbRect::Class, "contains?",		 rbRect::Contains,			-1 );
	ext_define_method( rbRect::Class, "intersects?",	 rbRect::Intersects,		-1 );
    ext_define_method( rbRect::Class, "marshal_dump",    rbRect::MarshalDump,     	 0 );
    ext_define_method( rbRect::Class, "marshal_load",    rbRect::MarshalLoad,    	 1 );
    ext_define_method( rbRect::Class, "==",              rbRect::Equal,          	 1 );
    ext_define_method( rbRect::Class, "eql?",            rbRect::StrictEqual,    	 1 );
    ext_define_method( rbRect::Class, "inspect",         rbRect::Inspect,       	 0 );

    // Attribute accessors
    rb_define_attr( rbRect::Class, "left", true, true );
    rb_define_attr( rbRect::Class, "top", true, true );
    rb_define_attr( rbRect::Class, "width", true, true );
	rb_define_attr( rbRect::Class, "height", true, true );

    // Instance aliases
    rb_define_alias( rbRect::Class, "equal?", "eql?"    );
    rb_define_alias( rbRect::Class, "to_s",   "inspect" );
}

// Rect#initialize
// Rect#initialize(rect)
// Rect#initialize(position, size)
// Rect#initialize(left, top, width, height)
VALUE rbRect::Initialize( int argc, VALUE argv[], VALUE aSelf )
{
	VALUE position;
	VALUE size;
    switch( argc )
    {
        case 0:
            rbRect::SetLeft( aSelf, INT2FIX( 0 ) );
            rbRect::SetTop( aSelf, INT2FIX( 0 ) );
            rbRect::SetWidth( aSelf, INT2FIX( 0 ) );
			rbRect::SetHeight( aSelf, INT2FIX( 0 ) );
            break;
        case 1:
            rbRect::InitializeCopy( aSelf, rbRect::ToRuby( argv[ 0 ] ) );
            break;
		case 2:
			position = rbVector2::ToRuby( argv[ 0 ] );
			size = rbVector2::ToRuby( argv[ 1 ] );
				
			rbRect::SetLeft( aSelf, rbVector2::GetX( position ) );
			rbRect::SetTop( aSelf, rbVector2::GetY( position ) );
			rbRect::SetWidth( aSelf, rbVector2::GetX( size ) );
			rbRect::SetHeight( aSelf, rbVector2::GetY( size ) );
			break;
        case 4:
			rbRect::SetLeft( aSelf, argv[ 0 ] );
			rbRect::SetTop( aSelf, argv[ 1 ] );
			rbRect::SetWidth( aSelf, argv[ 2 ] );
			rbRect::SetHeight( aSelf, argv[ 3 ] );
            break;
        default:
            INVALID_ARGUMENT_LIST( argc, "0, 1, 2 or 4" );
    }

    return Qnil;
}

// Rect#initialize_copy(rect)
VALUE rbRect::InitializeCopy( VALUE aSelf, VALUE aRect )
{
    VALUE left = rbRect::GetLeft( aRect );
    VALUE top = rbRect::GetTop( aRect );
    VALUE width = rbRect::GetWidth( aRect );
	VALUE height = rbRect::GetHeight( aRect );

    rbRect::SetLeft( aSelf, left );
	rbRect::SetTop( aSelf, top );
	rbRect::SetWidth( aSelf, width );
	rbRect::SetHeight( aSelf, height );

    return aSelf;
}

static VALUE internalContains( VALUE aSelf, VALUE anX, VALUE anY )
{
	if( rb_funcall( anX, rb_intern( ">=" ), 1, rbRect::GetLeft( aSelf ) ) == Qtrue &&
		rb_funcall( anX, rb_intern( "<" ), 1, rb_funcall( rbRect::GetLeft( aSelf ), rb_intern( "+" ), 1, rbRect::GetWidth( aSelf ) ) ) == Qtrue && 
		rb_funcall( anY, rb_intern( ">=" ), 1, rbRect::GetTop( aSelf ) ) == Qtrue && 
		rb_funcall( anY, rb_intern( "<" ), 1, rb_funcall( rbRect::GetTop( aSelf ), rb_intern( "+" ), 1, rbRect::GetHeight( aSelf ) ) ) == Qtrue )
		return Qtrue;
	else
		return Qfalse;
}

// Rect#contains?(x, y)
// Rect#contains?(vector2)
VALUE rbRect::Contains( int argc, VALUE* args, VALUE aSelf )
{
	VALUE point;
	switch( argc )
	{
		case 1:
			point = rbVector2::ToRuby( args[ 0 ] );
			
			return internalContains( aSelf, rbVector2::GetX( point ), rbVector2::GetY( point ) );
		case 2:
			return internalContains( aSelf, args[ 0 ], args[ 1 ] );
		default:
            INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	return Qfalse;
}

static VALUE internalIntersects( VALUE aSelf, VALUE aRect, VALUE anIntersection )
{
	VALUE left   = MAX( rbRect::GetLeft( aSelf ),   rbRect::GetLeft( aRect ) );
	VALUE top    = MAX( rbRect::GetTop( aSelf ),    rbRect::GetTop( aRect ) );
	VALUE right  = MIN( rb_funcall( rbRect::GetLeft( aSelf ), rb_intern( "+" ), 1, rbRect::GetWidth( aSelf ) ), rb_funcall( rbRect::GetLeft( aRect ), rb_intern( "+" ), 1, rbRect::GetWidth( aRect ) ) );
	VALUE bottom = MIN( rb_funcall( rbRect::GetTop( aSelf ), rb_intern( "+" ), 1, rbRect::GetHeight( aSelf ) ), rb_funcall( rbRect::GetTop( aRect ), rb_intern( "+" ), 1, rbRect::GetHeight( aRect ) ) );

	if( rb_funcall( left, rb_intern( "<" ), 1, right ) == Qtrue && rb_funcall( top, rb_intern( "<" ), 1, bottom ) )
	{
		if( anIntersection != Qnil )
		{
			rbRect::SetLeft( anIntersection, left );
			rbRect::SetTop( anIntersection, top );
			rbRect::SetWidth( anIntersection, rb_funcall( right, rb_intern( "-" ), 1, left ) );
			rbRect::SetHeight( anIntersection, rb_funcall( bottom, rb_intern( "-" ), 1, top ) );
		}
		return Qtrue;
	}
	else
	{
		return Qfalse;
	}
}

// Rect#intersects?(rect)
// Rect#intersects?(rect, intersection)
VALUE rbRect::Intersects( int argc, VALUE* args, VALUE aSelf )
{
	VALUE rect;
	VALUE intersection;
	switch( argc )
	{
		case 1:
			rect = rbRect::ToRuby( args[ 0 ] );
			return internalIntersects( aSelf, rect, Qnil );
		case 2:
			rect = rbRect::ToRuby( args[ 0 ] );
			intersection = rbRect::ToRuby( args[ 1 ] );
			return internalIntersects( aSelf, rect, intersection );
		default:
            INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	
	return Qfalse;
}

// Rect#marshal_dump
VALUE rbRect::MarshalDump( VALUE aSelf )
{
    VALUE ptr[ 4 ];
    ptr[ 0 ] = rbRect::GetLeft( aSelf );
    ptr[ 1 ] = rbRect::GetTop( aSelf );
    ptr[ 2 ] = rbRect::GetWidth( aSelf );
	ptr[ 3 ] = rbRect::GetHeight( aSelf );
    return rb_ary_new4( 4, ptr );
}

// Rect#marshal_load(data)
VALUE rbRect::MarshalLoad( VALUE aSelf, VALUE aData )
{
    VALUE* ptr = RARRAY_PTR( aData );
    rbRect::SetLeft( aSelf, ptr[ 0 ] );
    rbRect::SetTop( aSelf, ptr[ 1 ] );
    rbRect::SetWidth( aSelf, ptr[ 2 ] );
	rbRect::SetHeight( aSelf, ptr[ 3 ] );
    return Qnil;
}

// Rect#==(other)
VALUE rbRect::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbRect::Class ) ) return Qfalse;
    if( !RTEST( rb_equal( rbRect::GetLeft( aSelf ), rbRect::GetLeft( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( rbRect::GetTop( aSelf ), rbRect::GetTop( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( rbRect::GetWidth( aSelf ), rbRect::GetWidth( anOther ) ) ) ) return Qfalse;
	if( !RTEST( rb_equal( rbRect::GetHeight( aSelf ), rbRect::GetHeight( anOther ) ) ) ) return Qfalse;
    return Qtrue;
}

// Rect#eql?(other)
// Rect#equal?(other)
VALUE rbRect::StrictEqual( VALUE aSelf, VALUE anOther )
{
    if( rbRect::Type( aSelf ) != rbRect::Type( anOther ) ) return Qfalse;
    return rbRect::Equal( aSelf, anOther );
}

// Rect#inspect
// Rect#to_s
VALUE rbRect::Inspect( VALUE aSelf )
{
	VALUE left = rb_funcall( rbRect::GetLeft( aSelf ), rb_intern( "inspect" ), 0 );
	VALUE top = rb_funcall( rbRect::GetTop( aSelf ), rb_intern( "inspect" ), 0 );
	VALUE width = rb_funcall( rbRect::GetWidth( aSelf ), rb_intern( "inspect" ), 0 );
	VALUE height = rb_funcall( rbRect::GetHeight( aSelf ), rb_intern( "inspect" ), 0 );
	return rb_sprintf( "%s(%s, %s, %s, %s)",
					   rb_obj_classname( aSelf ),
					   StringValueCStr( left ),
					   StringValueCStr( top ),
					   StringValueCStr( width ),
					   StringValueCStr( height ) );
}
