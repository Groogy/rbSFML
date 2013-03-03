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
    ext_define_method(rbVector3::Class, "initialize",      rbVector3::Initialize,     -1);
    ext_define_method(rbVector3::Class, "initialize_copy", rbVector3::InitializeCopy,  1);
    ext_define_method(rbVector3::Class, "marshal_dump",    rbVector3::MarshalDump,     0);
    ext_define_method(rbVector3::Class, "marshal_load",    rbVector3::MarshalLoad,     1);
    ext_define_method(rbVector3::Class, "coerce",          rbVector3::Coerce,          1);
    ext_define_method(rbVector3::Class, "-@",              rbVector3::Negate,          0);
    ext_define_method(rbVector3::Class, "+",               rbVector3::Add,             1);
    ext_define_method(rbVector3::Class, "-",               rbVector3::Subtract,        1);
    ext_define_method(rbVector3::Class, "*",               rbVector3::Multiply,        1);
    ext_define_method(rbVector3::Class, "/",               rbVector3::Divide,          1);
    ext_define_method(rbVector3::Class, "==",              rbVector3::Equal,           1);
    ext_define_method(rbVector3::Class, "eql?",            rbVector3::StrictEqual,     1);
    ext_define_method(rbVector3::Class, "inspect",         rbVector3::Inspect,         0);

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
            rbVector3::SetX( aSelf, INT2FIX( 0 ) );
            rbVector3::SetY( aSelf, INT2FIX( 0 ) );
            rbVector3::SetZ( aSelf, INT2FIX( 0 ) );
            break;
        case 1:
            rbVector3::InitializeCopy( aSelf, rbVector3::ToRuby( argv[ 0 ] ) );
            break;
        case 3:
			rbVector3::SetX( aSelf, argv[ 0 ] );
			rbVector3::SetY( aSelf, argv[ 1 ] );
			rbVector3::SetZ( aSelf, argv[ 2 ] );
            break;
        default:
            INVALID_ARGUMENT_LIST( argc, "0, 1 or 3" );
    }

    return Qnil;
}

// Vector3#initialize_copy(vector3)
VALUE rbVector3::InitializeCopy( VALUE aSelf, VALUE aVector3 )
{
	rbVector3::SetX( aSelf, rbVector3::GetX( aVector3 ) );
	rbVector3::SetY( aSelf, rbVector3::GetY( aVector3 ) );
	rbVector3::SetZ( aSelf, rbVector3::GetZ( aVector3 ) );

    return aSelf;
}

// Vector3#marshal_dump
VALUE rbVector3::MarshalDump( VALUE aSelf )
{
    VALUE ptr[ 3 ];
    ptr[ 0 ] = rbVector3::GetX( aSelf );
    ptr[ 1 ] = rbVector3::GetY( aSelf );
    ptr[ 2 ] = rbVector3::GetZ( aSelf );
    return rb_ary_new4( 3, ptr );
}

// Vector3#marshal_load(data)
VALUE rbVector3::MarshalLoad( VALUE aSelf, VALUE aData )
{
    VALUE* ptr = RARRAY_PTR( aData );
    rbVector3::SetX( aSelf, ptr[ 0 ] );
    rbVector3::SetY( aSelf, ptr[ 1 ] );
    rbVector3::SetZ( aSelf, ptr[ 2 ] );
    return Qnil;
}

// Vector3#coerce(other)
VALUE rbVector3::Coerce( VALUE aSelf, VALUE anOther )
{
    VALUE ary[] = { rbVector3::ToRuby( anOther ), aSelf };
    return rb_ary_new4( 2, ary );
}

// Vector3#-@
VALUE rbVector3::Negate( VALUE aSelf )
{
    VALUE x = rb_funcall( rbVector3::GetX( aSelf ), rb_intern( "-@" ), 0 );
    VALUE y = rb_funcall( rbVector3::GetY( aSelf ), rb_intern( "-@" ), 0 );
    VALUE z = rb_funcall( rbVector3::GetZ( aSelf ), rb_intern( "-@" ), 0 );
    VALUE array[] = { x, y, z };
    return rb_class_new_instance( 3, array, rbVector3::Class );
}

// Internal
static inline VALUE DoMath( VALUE aLeft, const char* anOperator, VALUE aRight )
{
    VALUE x = rb_funcall( rbVector3::GetX( aLeft ), rb_intern( anOperator ), 1, rbVector3::GetX( aRight ) );
    VALUE y = rb_funcall( rbVector3::GetY( aLeft ), rb_intern( anOperator ), 1, rbVector3::GetY( aRight ) );
    VALUE z = rb_funcall( rbVector3::GetZ( aLeft ), rb_intern( anOperator ), 1, rbVector3::GetZ( aRight ) );
    VALUE array[] = { x, y, z };
    return rb_class_new_instance( 3, array, rbVector3::Class );
}

// Vector3#+(other)
VALUE rbVector3::Add( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "+", rbVector3::ToRuby( anOther ) );
}

// Vector3#-(other)
VALUE rbVector3::Subtract( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "-", rbVector3::ToRuby( anOther ) );
}

// Vector3#*(other)
VALUE rbVector3::Multiply( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "*", rbVector3::ToRuby( anOther ) );
}

// Vector3#/(other)
VALUE rbVector3::Divide( VALUE aSelf, VALUE anOther )
{
    return DoMath( aSelf, "/", rbVector3::ToRuby( anOther ) );
}

// Vector3#==(other)
VALUE rbVector3::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbVector3::Class ) && !( rb_obj_is_kind_of( anOther, rb_cArray ) && RARRAY_LEN( anOther ) == 3 ) ) return Qfalse;
    anOther = rbVector3::ToRuby( anOther );
    if( !RTEST( rb_equal( rbVector3::GetX( aSelf ), rbVector3::GetX( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( rbVector3::GetY( aSelf ), rbVector3::GetY( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( rbVector3::GetZ( aSelf ), rbVector3::GetZ( anOther ) ) ) ) return Qfalse;
    return Qtrue;
}

// Vector3#eql?(other)
// Vector3#equal?(other)
VALUE rbVector3::StrictEqual( VALUE aSelf, VALUE anOther )
{
    if( rbVector3::Type( aSelf ) != rbVector3::Type( anOther ) ) return Qfalse;
    return rbVector3::Equal( aSelf, anOther );
}

// Vector3#inspect
// Vector3#to_s
VALUE rbVector3::Inspect( VALUE aSelf )
{
    VALUE x = rb_funcall( rbVector3::GetX( aSelf ), rb_intern( "inspect" ), 0 );
	VALUE y = rb_funcall( rbVector3::GetY( aSelf ), rb_intern( "inspect" ), 0 );
	VALUE z = rb_funcall( rbVector3::GetZ( aSelf ), rb_intern( "inspect" ), 0 );
	return rb_sprintf(  "%s(%s, %s, %s)", rb_obj_classname( aSelf ),
						StringValueCStr( x ),
						StringValueCStr( y ),
						StringValueCStr( z ) );
}
