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

#define SYSTEM_VECTOR3_CPP

#include "Vector3.hpp"

void rbVector3::Init( VALUE SFML )
{
    rbVector3::Class = rb_define_class_under( SFML, "Vector3", rb_cObject );

    // Instance methods
    rb_define_method(rbVector3::Class, "initialize",      Initialize,     -1);
    rb_define_method(rbVector3::Class, "initialize_copy", InitializeCopy,  1);
    rb_define_method(rbVector3::Class, "marshal_dump",    MarshalDump,     0);
    rb_define_method(rbVector3::Class, "marshal_load",    MarshalLoad,     1);
    rb_define_method(rbVector3::Class, "coerce",          Coerce,          1);
    rb_define_method(rbVector3::Class, "-@",              Negate,          0);
    rb_define_method(rbVector3::Class, "+",               Add,             1);
    rb_define_method(rbVector3::Class, "-",               Subtract,        1);
    rb_define_method(rbVector3::Class, "*",               Multiply,        1);
    rb_define_method(rbVector3::Class, "/",               Divide,          1);
    rb_define_method(rbVector3::Class, "==",              Equal,           1);
    rb_define_method(rbVector3::Class, "eql?",            StrictEqual,     1);
    rb_define_method(rbVector3::Class, "inspect",         Inspect,         0);
    rb_define_method(rbVector3::Class, "memory_usage",    GetMemoryUsage,  0);

    // Attribute accessors
    rb_define_attr(rbVector3::Class, "x", true, true);
    rb_define_attr(rbVector3::Class, "y", true, true);
    rb_define_attr(rbVector3::Class, "z", true, true);

    // Instance aliases
    rb_define_alias(rbVector3::Class, "equal?", "eql?"   );
    rb_define_alias(rbVector3::Class, "to_s",   "inspect");
}

// Vector3#initialize
// Vector3#initialize(vector3)
// Vector3#initialize(x, y, z)
VALUE rbVector3::Initialize( int argc, VALUE argv[], VALUE aSelf )
{
    switch( argc )
    {
        case 0:
            SetX( aSelf, INT2FIX( 0 ) );
            SetY( aSelf, INT2FIX( 0 ) );
            SetZ( aSelf, INT2FIX( 0 ) );
            break;
        case 1:
            InitializeCopy( aSelf, ToRuby( argv[ 0 ] ) );
            break;
        case 3:
            if( FIXNUM_P( argv[ 0 ] ) and FIXNUM_P( argv[ 1 ] ) and FIXNUM_P( argv[ 2 ] ) )
            {
                SetX( aSelf, argv[ 0 ] );
                SetY( aSelf, argv[ 1 ] );
                SetZ( aSelf, argv[ 2 ] );
            }
            else if( ISFLOAT( argv[ 0 ] ) and ISFLOAT( argv[ 1 ] ) and ISFLOAT( argv[ 2 ] ) )
            {
                SetX( aSelf, rb_to_float( argv[ 0 ] ) );
                SetY( aSelf, rb_to_float( argv[ 1 ] ) );
                SetZ( aSelf, rb_to_float( argv[ 2 ] ) );
            }
            else
            {
                INVALID_EXPECTED_TYPES( rb_cFixnum, rb_cFloat );
            }
            break;
        default:
            rb_raise( rb_eArgError,
                      "wrong number of arguments(%i for 0, 1, or 3)", argc );
    }

    return Qnil;
}

// Vector3#initialize_copy(vector3)
VALUE rbVector3::InitializeCopy( VALUE aSelf, VALUE aVector3 )
{
    VALUE x = GetX( aVector3 );
    VALUE y = GetY( aVector3 );
    VALUE z = GetZ( aVector3 );

    switch( rbVector3::Type( aVector3 ) )
    {
        case T_FIXNUM:
            SetX( aSelf, x );
            SetY( aSelf, y );
            SetZ( aSelf, z );
            break;
        case T_FLOAT:
            SetX( aSelf, rb_float_new( NUM2DBL( x ) ) );
            SetY( aSelf, rb_float_new( NUM2DBL( y ) ) );
            SetZ( aSelf, rb_float_new( NUM2DBL( z ) ) );
            break;
        default:
            INVALID_EXPECTED_TYPES( rb_cFixnum, rb_cFloat );
            break;
    }

    return aSelf;
}

// Vector3#marshal_dump
VALUE rbVector3::MarshalDump( VALUE aSelf )
{
    VALUE ptr[ 3 ];
    ptr[ 0 ] = GetX( aSelf );
    ptr[ 1 ] = GetY( aSelf );
    ptr[ 2 ] = GetZ( aSelf );
    return rb_ary_new4( 3, ptr );
}

// Vector3#marshal_load(data)
VALUE rbVector3::MarshalLoad( VALUE aSelf, VALUE aData )
{
    VALUE* ptr = RARRAY_PTR( aData );
    SetX( aSelf, ptr[ 0 ] );
    SetY( aSelf, ptr[ 1 ] );
    SetZ( aSelf, ptr[ 2 ] );
    return Qnil;
}

// Vector3#coerce(other)
VALUE rbVector3::Coerce( VALUE aSelf, VALUE anOther )
{
    VALUE ary[] = { ToRuby( anOther ), aSelf };
    return rb_ary_new4( 2, ary );
}

// Vector3#-@
VALUE rbVector3::Negate( VALUE aSelf )
{
    VALUE x = rb_funcall( GetX( aSelf ), rb_intern( "-@" ), 0 );
    VALUE y = rb_funcall( GetY( aSelf ), rb_intern( "-@" ), 0 );
    VALUE z = rb_funcall( GetZ( aSelf ), rb_intern( "-@" ), 0 );
    return rb_class_new_instance( 3, ( VALUE[] ){ x, y, z }, rbVector3::Class );
}

// Internal
static inline VALUE DoMath( VALUE aLeft, const char* anOperator, VALUE aRight )
{
    using namespace rbVector3;

    VALUE x = rb_funcall( GetX( aLeft ), rb_intern( anOperator ), 1, GetX( aRight ) );
    VALUE y = rb_funcall( GetY( aLeft ), rb_intern( anOperator ), 1, GetY( aRight ) );
    VALUE z = rb_funcall( GetZ( aLeft ), rb_intern( anOperator ), 1, GetZ( aRight ) );
    return rb_class_new_instance( 3, ( VALUE[] ){ x, y, z }, rbVector3::Class );
}

// Vector3#+(other)
VALUE rbVector3::Add( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "+", ToRuby( anOther ) );
}

// Vector3#-(other)
VALUE rbVector3::Subtract( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "-", ToRuby( anOther ) );
}

// Vector3#*(other)
VALUE rbVector3::Multiply( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "*", ToRuby( anOther ) );
}

// Vector3#/(other)
VALUE rbVector3::Divide( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "/", ToRuby( anOther ) );
}

// Vector3#==(other)
VALUE rbVector3::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbVector3::Class ) ) return Qfalse;
    if( !RTEST( rb_equal( GetX( aSelf ), GetX( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( GetY( aSelf ), GetY( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( GetZ( aSelf ), GetZ( anOther ) ) ) ) return Qfalse;
    return Qtrue;
}

// Vector3#eql?(other)
// Vector3#equal?(other)
VALUE rbVector3::StrictEqual( VALUE aSelf, VALUE anOther )
{
    if( Type( aSelf ) != Type( anOther ) ) return Qfalse;
    return Equal( aSelf, anOther );
}

// Vector3#inspect
// Vector3#to_s
VALUE rbVector3::Inspect( VALUE aSelf )
{
    switch( rbVector3::Type( aSelf ) )
    {
        case T_FIXNUM:
            return rb_sprintf( "%s(%i, %i, %i)",
                               rb_obj_classname( aSelf ),
                               FIX2INT( GetX( aSelf ) ),
                               FIX2INT( GetY( aSelf ) ),
                               FIX2INT( GetZ( aSelf ) ) );
        case T_FLOAT:
            return rb_sprintf( "%s(%lg, %lg, %lg)",
                              rb_obj_classname( aSelf ),
                              NUM2DBL( GetX( aSelf ) ),
                              NUM2DBL( GetY( aSelf ) ),
                              NUM2DBL( GetZ( aSelf ) ) );
    }
    return Qnil;
}

// Vector3#memory_usage
VALUE rbVector3::GetMemoryUsage( VALUE aSelf )
{
    return INT2FIX( 0 );
}
