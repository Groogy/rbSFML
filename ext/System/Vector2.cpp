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

#define SYSTEM_VECTOR2_CPP

#include "Vector2.hpp"

void rbVector2::Init( VALUE SFML )
{
    rbVector2::Class = rb_define_class_under( SFML, "Vector2", rb_cObject );

    // Instance methods
    ext_define_method( rbVector2::Class, "initialize",      rbVector2::Initialize,     -1 );
    ext_define_method( rbVector2::Class, "initialize_copy", rbVector2::InitializeCopy,  1 );
    ext_define_method( rbVector2::Class, "marshal_dump",    rbVector2::MarshalDump,     0 );
    ext_define_method( rbVector2::Class, "marshal_load",    rbVector2::MarshalLoad,     1 );
    ext_define_method( rbVector2::Class, "coerce",          rbVector2::Coerce,          1 );
    ext_define_method( rbVector2::Class, "-@",              rbVector2::Negate,          0 );
    ext_define_method( rbVector2::Class, "+",               rbVector2::Add,             1 );
    ext_define_method( rbVector2::Class, "-",               rbVector2::Subtract,        1 );
    ext_define_method( rbVector2::Class, "*",               rbVector2::Multiply,        1 );
    ext_define_method( rbVector2::Class, "/",               rbVector2::Divide,          1 );
    ext_define_method( rbVector2::Class, "==",              rbVector2::Equal,           1 );
    ext_define_method( rbVector2::Class, "eql?",            rbVector2::StrictEqual,     1 );
    ext_define_method( rbVector2::Class, "inspect",         rbVector2::Inspect,         0 );

    // Attribute accessors
    rb_define_attr( rbVector2::Class, "x", true, true );
    rb_define_attr( rbVector2::Class, "y", true, true );

    // Instance aliases
    rb_define_alias( rbVector2::Class, "equal?", "eql?"    );
    rb_define_alias( rbVector2::Class, "to_s",   "inspect" );
}

// Vector2#initialize
// Vector2#initialize(vector2)
// Vector2#initialize(x, y)
VALUE rbVector2::Initialize( int argc, VALUE argv[], VALUE aSelf )
{
    switch( argc )
    {
        case 0:
            rbVector2::SetX( aSelf, INT2FIX( 0 ) );
            rbVector2::SetY( aSelf, INT2FIX( 0 ) );
            break;
        case 1:
            rbVector2::InitializeCopy( aSelf, rbVector2::ToRuby( argv[ 0 ] ) );
            break;
        case 2:
            rbVector2::SetX( aSelf, argv[ 0 ] );
            rbVector2::SetY( aSelf, argv[ 1 ] );
            break;
        default:
            INVALID_ARGUMENT_LIST( argc, "0..2" );
    }

    return Qnil;
}

// Vector2#initialize_copy(vector2)
VALUE rbVector2::InitializeCopy( VALUE aSelf, VALUE aVector2 )
{
	rbVector2::SetX( aSelf, rbVector2::GetX( aVector2 ) );
	rbVector2::SetY( aSelf, rbVector2::GetY( aVector2 ) );

    return aSelf;
}

// Vector2#marshal_dump
VALUE rbVector2::MarshalDump( VALUE aSelf )
{
    VALUE ptr[ 2 ];
    ptr[ 0 ] = rbVector2::GetX( aSelf );
    ptr[ 1 ] = rbVector2::GetY( aSelf );
    return rb_ary_new4( 2, ptr );
}

// Vector2#marshal_load(data)
VALUE rbVector2::MarshalLoad( VALUE aSelf, VALUE aData )
{
    VALUE* ptr = RARRAY_PTR( aData );
    rbVector2::SetX( aSelf, ptr[0] );
    rbVector2::SetY( aSelf, ptr[1] );
    return Qnil;
}

// Vector2#coerce(other)
VALUE rbVector2::Coerce( VALUE aSelf, VALUE anOther )
{
    VALUE ary[] = { rbVector2::ToRuby( anOther ), aSelf };
    return rb_ary_new4( 2, ary );
}

// Vector2#-@
VALUE rbVector2::Negate( VALUE aSelf )
{
    VALUE x = rb_funcall( rbVector2::GetX( aSelf ), rb_intern( "-@" ), 0 );
    VALUE y = rb_funcall( rbVector2::GetY( aSelf ), rb_intern( "-@" ), 0 );
    VALUE array[] = { x, y };
    return rb_class_new_instance( 2, array, rbVector2::Class );
}

// Internal
static inline VALUE DoMath( VALUE aLeft, const char* anOperator, VALUE aRight )
{
    VALUE x = rb_funcall( rbVector2::GetX( aLeft ), rb_intern( anOperator ), 1, rbVector2::GetX( aRight ) );
    VALUE y = rb_funcall( rbVector2::GetY( aLeft ), rb_intern( anOperator ), 1, rbVector2::GetY( aRight ) );
    VALUE array[] = { x, y };
    return rb_class_new_instance( 2, array, rbVector2::Class );
}

// Vector2#+(other)
VALUE rbVector2::Add( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "+", rbVector2::ToRuby( anOther ) );
}

// Vector2#-(other)
VALUE rbVector2::Subtract( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "-", rbVector2::ToRuby( anOther ) );
}

// Vector2#*(other)
VALUE rbVector2::Multiply( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "*", rbVector2::ToRuby( anOther ) );
}

// Vector2#/(other)
VALUE rbVector2::Divide( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "/", rbVector2::ToRuby( anOther ) );
}

// Vector2#==(other)
VALUE rbVector2::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbVector2::Class ) && !( rb_obj_is_kind_of( anOther, rb_cArray ) && RARRAY_LEN( anOther ) == 2 ) ) return Qfalse;
    anOther = rbVector2::ToRuby( anOther );
    if( !RTEST( rb_equal( rbVector2::GetX( aSelf ), rbVector2::GetX( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( rbVector2::GetY( aSelf ), rbVector2::GetY( anOther ) ) ) ) return Qfalse;
    return Qtrue;
}

// Vector2#eql?(other)
// Vector2#equal?(other)
VALUE rbVector2::StrictEqual( VALUE aSelf, VALUE anOther )
{
    if( rbVector2::Type( aSelf ) != rbVector2::Type( anOther ) ) return Qfalse;
    return Equal( aSelf, anOther );
}

// Vector2#inspect
// Vector2#to_s
VALUE rbVector2::Inspect( VALUE aSelf )
{
	VALUE x = rb_funcall( rbVector2::GetX( aSelf ), rb_intern( "inspect" ), 0 );
	VALUE y = rb_funcall( rbVector2::GetY( aSelf ), rb_intern( "inspect" ), 0 );
	return rb_sprintf(  "%s(%s, %s)", rb_obj_classname( aSelf ),
						StringValueCStr( x ),
						StringValueCStr( y ) );
}
