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
    rb_define_method( rbVector2::Class, "initialize",      Initialize,     -1 );
    rb_define_method( rbVector2::Class, "initialize_copy", InitializeCopy,  1 );
    rb_define_method( rbVector2::Class, "marshal_dump",    MarshalDump,     0 );
    rb_define_method( rbVector2::Class, "marshal_load",    MarshalLoad,     1 );
    rb_define_method( rbVector2::Class, "coerce",          Coerce,          1 );
    rb_define_method( rbVector2::Class, "-@",              Negate,          0 );
    rb_define_method( rbVector2::Class, "+",               Add,             1 );
    rb_define_method( rbVector2::Class, "-",               Subtract,        1 );
    rb_define_method( rbVector2::Class, "*",               Multiply,        1 );
    rb_define_method( rbVector2::Class, "/",               Divide,          1 );
    rb_define_method( rbVector2::Class, "==",              Equal,           1 );
    rb_define_method( rbVector2::Class, "eql?",            StrictEqual,     1 );
    rb_define_method( rbVector2::Class, "inspect",         Inspect,         0 );
    rb_define_method( rbVector2::Class, "memory_usage",    GetMemoryUsage,  0 );

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
            SetX( aSelf, INT2FIX( 0 ) );
            SetY( aSelf, INT2FIX( 0 ) );
            break;
        case 1:
            InitializeCopy( aSelf, ToRuby( argv[ 0 ] ) );
            break;
        case 2:
            if(FIXNUM_P( argv[ 0 ] ) and FIXNUM_P( argv[ 1 ] ) )
            {
                SetX( aSelf, argv[ 0 ] );
                SetY( aSelf, argv[ 1 ] );
            }
            else
            {
                SetX( aSelf, rb_to_float( argv[ 0 ] ) );
                SetY( aSelf, rb_to_float( argv[ 1 ] ) );
            }
            break;
        default:
            rb_raise( rb_eArgError,
                      "wrong number of arguments(%i for 0..2)", argc );
    }

    return Qnil;
}

// Vector2#initialize_copy(vector2)
VALUE rbVector2::InitializeCopy( VALUE aSelf, VALUE aVector2 )
{
    VALUE x = GetX( aVector2 );
    VALUE y = GetY( aVector2 );

    switch( rbVector2::Type( aVector2 ) )
    {
        case T_FIXNUM:
            SetX( aSelf, x );
            SetY( aSelf, y );
            break;
        case T_FLOAT:
            SetX( aSelf, rb_float_new( NUM2DBL(x) ) );
            SetY( aSelf, rb_float_new( NUM2DBL(y) ) );
            break;
    }

    return aSelf;
}

// Vector2#marshal_dump
VALUE rbVector2::MarshalDump( VALUE aSelf )
{
    VALUE ptr[ 2 ];
    ptr[ 0 ] = GetX( aSelf );
    ptr[ 1 ] = GetY( aSelf );
    return rb_ary_new4( 2, ptr );
}

// Vector2#marshal_load(data)
VALUE rbVector2::MarshalLoad( VALUE aSelf, VALUE aData )
{
    VALUE* ptr = RARRAY_PTR( aData );
    SetX( aSelf, ptr[0] );
    SetY( aSelf, ptr[1] );
    return Qnil;
}

// Vector2#coerce(other)
VALUE rbVector2::Coerce( VALUE aSelf, VALUE anOther )
{
    VALUE ary[] = { ToRuby( anOther ), aSelf };
    return rb_ary_new4( 2, ary );
}

// Vector2#-@
VALUE rbVector2::Negate( VALUE aSelf )
{
    VALUE x = rb_funcall( GetX( aSelf ), rb_intern( "-@" ), 0 );
    VALUE y = rb_funcall( GetY( aSelf ), rb_intern( "-@" ), 0 );
    return rb_class_new_instance( 2, ( VALUE[] ){ x, y }, rbVector2::Class );
}

// Internal
static inline VALUE DoMath( VALUE aLeft, const char* anOperator, VALUE aRight )
{
    using namespace rbVector2;

    VALUE x = rb_funcall( GetX( aLeft ), rb_intern( anOperator ), 1, GetX( aRight ) );
    VALUE y = rb_funcall( GetY( aLeft ), rb_intern( anOperator ), 1, GetY( aRight ) );
    return rb_class_new_instance( 2, ( VALUE[] ){ x, y }, rbVector2::Class );
}

// Vector2#+(other)
VALUE rbVector2::Add( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "+", ToRuby( anOther ) );
}

// Vector2#-(other)
VALUE rbVector2::Subtract( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "-", ToRuby( anOther ) );
}

// Vector2#*(other)
VALUE rbVector2::Multiply( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "*", ToRuby( anOther ) );
}

// Vector2#/(other)
VALUE rbVector2::Divide( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "/", ToRuby( anOther ) );
}

// Vector2#==(other)
VALUE rbVector2::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbVector2::Class ) ) return Qfalse;
    if( !RTEST( rb_equal( GetX( aSelf ), GetX( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( GetY( aSelf ), GetY( anOther ) ) ) ) return Qfalse;
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
    switch( Type( aSelf ) )
    {
        case T_FIXNUM:
            return rb_sprintf( "%s(%i, %i)",
                               rb_obj_classname( aSelf ),
                               FIX2INT( GetX( aSelf ) ),
                               FIX2INT( GetY( aSelf ) ) );
        case T_FLOAT:
            return rb_sprintf( "%s(%lg, %lg)",
                               rb_obj_classname( aSelf),
                               NUM2DBL( GetX( aSelf ) ),
                               NUM2DBL( GetY( aSelf ) ) );
    }
    return Qnil;
}

// Vector2#memory_usage
VALUE rbVector2::GetMemoryUsage( VALUE aSelf )
{
    return INT2FIX( 0 );
}
