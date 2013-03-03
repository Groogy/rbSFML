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

#define GRAPHICS_COLOR_CPP

#include "Color.hpp"

void rbColor::Init( VALUE SFML )
{
    rbColor::Class = rb_define_class_under( SFML, "Color", rb_cObject );

    // Instance methods
    ext_define_method( rbColor::Class, "initialize",      rbColor::Initialize,     -1 );
    ext_define_method( rbColor::Class, "initialize_copy", rbColor::InitializeCopy,  1 );
    ext_define_method( rbColor::Class, "marshal_dump",    rbColor::MarshalDump,     0 );
    ext_define_method( rbColor::Class, "marshal_load",    rbColor::MarshalLoad,     1 );
    ext_define_method( rbColor::Class, "+",               rbColor::Add,             1 );
    ext_define_method( rbColor::Class, "*",               rbColor::Multiply,        1 );
    ext_define_method( rbColor::Class, "==",              rbColor::Equal,           1 );
    ext_define_method( rbColor::Class, "inspect",         rbColor::Inspect,         0 );

    // Attribute accessors
    rb_define_attr( rbColor::Class, "r", true, true );
    rb_define_attr( rbColor::Class, "g", true, true );
    rb_define_attr( rbColor::Class, "b", true, true );
	rb_define_attr( rbColor::Class, "a", true, true );

    // Instance aliases
    rb_define_alias( rbColor::Class, "to_s",   "inspect" );
	
	rb_define_const( rbColor::Class, "Black",       rb_obj_freeze( rbColor::ToRuby( sf::Color::Black ) ) );
	rb_define_const( rbColor::Class, "White",       rb_obj_freeze( rbColor::ToRuby( sf::Color::White ) ) );
	rb_define_const( rbColor::Class, "Red",         rb_obj_freeze( rbColor::ToRuby( sf::Color::Red ) ) );
	rb_define_const( rbColor::Class, "Green",       rb_obj_freeze( rbColor::ToRuby( sf::Color::Green ) ) );
	rb_define_const( rbColor::Class, "Blue",        rb_obj_freeze( rbColor::ToRuby( sf::Color::Blue ) ) );
	rb_define_const( rbColor::Class, "Yellow",      rb_obj_freeze( rbColor::ToRuby( sf::Color::Yellow ) ) );
	rb_define_const( rbColor::Class, "Magenta",     rb_obj_freeze( rbColor::ToRuby( sf::Color::Magenta ) ) );
	rb_define_const( rbColor::Class, "Cyan",        rb_obj_freeze( rbColor::ToRuby( sf::Color::Cyan ) ) );
	rb_define_const( rbColor::Class, "Transparent", rb_obj_freeze( rbColor::ToRuby( sf::Color::Transparent ) ) );
}

// Color#initialize
// Color#initialize(color)
// Color#initialize(r, g, b, a=255)
VALUE rbColor::Initialize( int argc, VALUE argv[], VALUE aSelf )
{
    switch( argc )
    {
        case 0:
            rbColor::SetRed( aSelf, INT2FIX( 0 ) );
            rbColor::SetGreen( aSelf, INT2FIX( 0 ) );
            rbColor::SetBlue( aSelf, INT2FIX( 0 ) );
			rbColor::SetAlpha( aSelf, INT2FIX( 255 ) );
            break;
        case 1:
            rbColor::InitializeCopy( aSelf, rbColor::ToRuby( argv[ 0 ] ) );
            break;
        case 3:
            if( FIXNUM_P( argv[ 0 ] ) and FIXNUM_P( argv[ 1 ] ) and FIXNUM_P( argv[ 2 ] ) )
            {
                rbColor::SetRed( aSelf, argv[ 0 ] );
                rbColor::SetGreen( aSelf, argv[ 1 ] );
                rbColor::SetBlue( aSelf, argv[ 2 ] );
				rbColor::SetAlpha( aSelf, INT2FIX( 255 ) );
            }
            else
            {
                INVALID_EXPECTED_TYPE( rb_cFixnum );
            }
            break;
		case 4:
			if( FIXNUM_P( argv[ 0 ] ) and FIXNUM_P( argv[ 1 ] ) and FIXNUM_P( argv[ 2 ] ) and FIXNUM_P( argv[ 3 ] ) )
            {
                rbColor::SetRed( aSelf, argv[ 0 ] );
                rbColor::SetGreen( aSelf, argv[ 1 ] );
                rbColor::SetBlue( aSelf, argv[ 2 ] );
				rbColor::SetAlpha( aSelf, argv[ 3 ] );
            }
            else
            {
                INVALID_EXPECTED_TYPE( rb_cFixnum );
            }
            break;
        default:
            INVALID_ARGUMENT_LIST( argc, "0, 1, 3 or 4" );
    }

    return Qnil;
}

// Color#initialize_copy(color)
VALUE rbColor::InitializeCopy( VALUE aSelf, VALUE aColor )
{
    rbColor::SetRed( aSelf, rbColor::GetRed( aColor ) );
	rbColor::SetGreen( aSelf, rbColor::GetGreen( aColor ) );
	rbColor::SetBlue( aSelf, rbColor::GetBlue( aColor ) );
	rbColor::SetAlpha( aSelf, rbColor::GetAlpha( aColor ) );

    return aSelf;
}

// Color#marshal_dump
VALUE rbColor::MarshalDump( VALUE aSelf )
{
    VALUE ptr[ 4 ];
    ptr[ 0 ] = rbColor::GetRed( aSelf );
    ptr[ 1 ] = rbColor::GetGreen( aSelf );
    ptr[ 2 ] = rbColor::GetBlue( aSelf );
	ptr[ 3 ] = rbColor::GetAlpha( aSelf );
    return rb_ary_new4( 4, ptr );
}

// Color#marshal_load(data)
VALUE rbColor::MarshalLoad( VALUE aSelf, VALUE aData )
{
    VALUE* ptr = RARRAY_PTR( aData );
    rbColor::SetRed( aSelf, ptr[ 0 ] );
    rbColor::SetGreen( aSelf, ptr[ 1 ] );
    rbColor::SetBlue( aSelf, ptr[ 2 ] );
	rbColor::SetAlpha( aSelf, ptr[ 2 ] );
    return Qnil;
}

// Internal
static inline VALUE DoMath( VALUE aLeft, const char* anOperator, VALUE aRight )
{
}

// Color#+(other)
VALUE rbColor::Add( VALUE aLeft, VALUE aRight )
{
	static VALUE maxValue = INT2NUM( 255 );
    VALUE r = MAX( rb_funcall( rbColor::GetRed( aLeft ), rb_intern( "+" ), 1, rbColor::GetRed( aRight ) ), maxValue );
    VALUE g = MAX( rb_funcall( rbColor::GetGreen( aLeft ), rb_intern( "+" ), 1, rbColor::GetGreen( aRight ) ), maxValue );
    VALUE b = MAX( rb_funcall( rbColor::GetBlue( aLeft ), rb_intern( "+" ), 1, rbColor::GetBlue( aRight ) ), maxValue );
	VALUE a = MAX( rb_funcall( rbColor::GetAlpha( aLeft ), rb_intern( "+" ), 1, rbColor::GetAlpha( aRight ) ), maxValue );
    VALUE array[] = { r, g, b, a };
    return rb_class_new_instance( 4, array, rbColor::Class );
}

// Color#*(other)
VALUE rbColor::Multiply( VALUE aLeft, VALUE aRight )
{
    static VALUE maxValue = INT2NUM( 255 );
    VALUE r = rb_funcall( rb_funcall( rbColor::GetRed( aLeft ), rb_intern( "*" ), 1, rbColor::GetRed( aRight ) ), rb_intern( "/" ), 1, maxValue );
    VALUE g = rb_funcall( rb_funcall( rbColor::GetGreen( aLeft ), rb_intern( "*" ), 1, rbColor::GetGreen( aRight ) ), rb_intern( "/" ), 1, maxValue );
    VALUE b = rb_funcall( rb_funcall( rbColor::GetBlue( aLeft ), rb_intern( "*" ), 1, rbColor::GetBlue( aRight ) ), rb_intern( "/" ), 1, maxValue );
	VALUE a = rb_funcall( rb_funcall( rbColor::GetAlpha( aLeft ), rb_intern( "*" ), 1, rbColor::GetAlpha( aRight ) ), rb_intern( "/" ), 1, maxValue );
    VALUE array[] = { r, g, b, a };
    return rb_class_new_instance( 4, array, rbColor::Class );
}

// Color#==(other)
VALUE rbColor::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbColor::Class ) && !( rb_obj_is_kind_of( anOther, rb_cArray ) && ( RARRAY_LEN( anOther ) == 3 || RARRAY_LEN( anOther ) == 4 ) ) ) return Qfalse;
    anOther = rbColor::ToRuby( anOther );
    if( !RTEST( rb_equal( rbColor::GetRed( aSelf ), rbColor::GetRed( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( rbColor::GetGreen( aSelf ), rbColor::GetGreen( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( rbColor::GetBlue( aSelf ), rbColor::GetBlue( anOther ) ) ) ) return Qfalse;
    if( !RTEST( rb_equal( rbColor::GetAlpha( aSelf ), rbColor::GetAlpha( anOther ) ) ) ) return Qfalse;
    return Qtrue;
}

// Color#inspect
// Color#to_s
VALUE rbColor::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%i, %i, %i, %i)",
					   rb_obj_classname( aSelf ),
					   FIX2INT( rbColor::GetRed( aSelf ) ),
					   FIX2INT( rbColor::GetGreen( aSelf ) ),
					   FIX2INT( rbColor::GetBlue( aSelf ) ),
					   FIX2INT( rbColor::GetAlpha( aSelf ) ) );
}
