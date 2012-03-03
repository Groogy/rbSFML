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
    rb_define_method( rbRect::Class, "initialize",      rbRect::Initialize,     -1 );
    rb_define_method( rbRect::Class, "initialize_copy", rbRect::InitializeCopy,  1 );
    rb_define_method( rbRect::Class, "marshal_dump",    rbRect::MarshalDump,     0 );
    rb_define_method( rbRect::Class, "marshal_load",    rbRect::MarshalLoad,     1 );
    rb_define_method( rbRect::Class, "==",              rbRect::Equal,           1 );
    rb_define_method( rbRect::Class, "eql?",            rbRect::StrictEqual,     1 );
    rb_define_method( rbRect::Class, "inspect",         rbRect::Inspect,         0 );
    rb_define_method( rbRect::Class, "memory_usage",    rbRect::GetMemoryUsage,  0 );

    // Attribute accessors
    rb_define_attr( rbRect::Class, "x", true, true );
    rb_define_attr( rbRect::Class, "y", true, true );
    rb_define_attr( rbRect::Class, "z", true, true );

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
			if( rbVector2::Type( position ) != rbVector2::Type( size ) )
				rb_raise( rb_eTypeError, "Vectors must be of same type!" );
				
			rbRect::SetLeft( aSelf, rbVector2::GetX( position ) );
			rbRect::SetTop( aSelf, rbVector2::GetY( position ) );
			rbRect::SetWidth( aSelf, rbVector2::GetX( size ) );
			rbRect::SetHeight( aSelf, rbVector2::GetY( size ) );
			break;
        case 4:
            if( FIXNUM_P( argv[ 0 ] ) and FIXNUM_P( argv[ 1 ] ) and FIXNUM_P( argv[ 2 ] ) and FIXNUM_P( argv[ 3 ] ) )
            {
                rbRect::SetLeft( aSelf, argv[ 0 ] );
                rbRect::SetTop( aSelf, argv[ 1 ] );
                rbRect::SetWidth( aSelf, argv[ 2 ] );
				rbRect::SetHeight( aSelf, argv[ 3 ] );
            }
            else if( ISFLOAT( argv[ 0 ] ) and ISFLOAT( argv[ 1 ] ) and ISFLOAT( argv[ 2 ] ) and FIXNUM_P( argv[ 3 ] ) )
            {
                rbRect::SetLeft( aSelf, rb_to_float( argv[ 0 ] ) );
                rbRect::SetTop( aSelf, rb_to_float( argv[ 1 ] ) );
                rbRect::SetWidth( aSelf, rb_to_float( argv[ 2 ] ) );
				rbRect::SetHeight( aSelf, rb_to_float( argv[ 3 ] ) );
            }
            else
            {
                INVALID_EXPECTED_TYPES( rb_cFixnum, rb_cFloat );
            }
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
    switch( rbRect::Type( aSelf ) )
    {
        case T_FIXNUM:
            return rb_sprintf( "%s(%i, %i, %i, %i)",
                               rb_obj_classname( aSelf ),
                               FIX2INT( rbRect::GetLeft( aSelf ) ),
                               FIX2INT( rbRect::GetTop( aSelf ) ),
                               FIX2INT( rbRect::GetWidth( aSelf ) ),
							   FIX2INT( rbRect::GetHeight( aSelf ) ) );
        case T_FLOAT:
            return rb_sprintf( "%s(%lg, %lg, %lg, %lg)",
                              rb_obj_classname( aSelf ),
                              NUM2DBL( rbRect::GetLeft( aSelf ) ),
                              NUM2DBL( rbRect::GetTop( aSelf ) ),
                              NUM2DBL( rbRect::GetWidth( aSelf ) ),
							  NUM2DBL( rbRect::GetHeight( aSelf ) ) );
    }
    return Qnil;
}

// Rect#memory_usage
VALUE rbRect::GetMemoryUsage( VALUE aSelf )
{
    return INT2FIX( 0 );
}
