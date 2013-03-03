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

#define SYSTEM_TIME_CPP

#include "Time.hpp"

void rbTime::Init( VALUE SFML )
{
    rbTime::Class = rb_define_class_under( SFML, "Time", rb_cObject );
    rb_include_module( rbTime::Class, rb_mComparable );

    // Class methods
    rb_define_alloc_func( rbTime::Class, rbMacros::Allocate< sf::Time > );

    // Instance methods
    ext_define_method( rbTime::Class, "initialize_copy", rbTime::InitializeCopy, 1 );
	ext_define_method( rbTime::Class, "as_seconds",      rbTime::AsSeconds,      0 );
	ext_define_method( rbTime::Class, "as_milliseconds", rbTime::AsMilliseconds, 0 );
	ext_define_method( rbTime::Class, "as_microseconds", rbTime::AsMicroseconds, 0 );
	ext_define_method( rbTime::Class, "-@",				rbTime::Negate, 		0 );
	ext_define_method( rbTime::Class, "+",				rbTime::Addition,		1 );
	ext_define_method( rbTime::Class, "-",				rbTime::Subtract,		1 );
	ext_define_method( rbTime::Class, "*",				rbTime::Multiply,		1 );
	ext_define_method( rbTime::Class, "/",				rbTime::Divide,			1 );
    ext_define_method( rbTime::Class, "marshal_dump",    rbTime::MarshalDump,    0 );
    ext_define_method( rbTime::Class, "<=>",             rbTime::Compare,        1 );
    ext_define_method( rbTime::Class, "inspect",         rbTime::Inspect,        0 );

	// Class attributes
	rb_define_const( rbTime::Class, "Zero", rbMacros::ToConstRuby( &sf::Time::Zero, rbTime::Class ) );

    // Instance aliasses
    rb_define_alias( rbTime::Class, "to_s",           "inspect"         );
	rb_define_alias( rbTime::Class, "asSeconds",      "as_seconds"      );
	rb_define_alias( rbTime::Class, "asMilliseconds", "as_milliseconds" );
	rb_define_alias( rbTime::Class, "asMicroseconds", "as_microseconds" );
}

// Time#initialize_copy( time )
VALUE rbTime::InitializeCopy( VALUE aSelf, VALUE aTime )
{
    *rbMacros::ToSFML< sf::Time >( aSelf, rbTime::Class ) = *rbMacros::ToSFML< sf::Time >( aTime, rbTime::Class );
    return aSelf;
}

// Time#as_seconds
// Time#asSeconds
VALUE rbTime::AsSeconds( VALUE aSelf )
{
	return rb_float_new( rbMacros::ToSFML< sf::Time >( aSelf, rbTime::Class )->asSeconds() );
}

// Time#as_milliseconds
// Time#asMilliseconds
VALUE rbTime::AsMilliseconds( VALUE aSelf )
{
	return INT2NUM( rbMacros::ToSFML< sf::Time >( aSelf, rbTime::Class )->asMilliseconds() );
}

// Time#as_microseconds
// Time#asMicroseconds
VALUE rbTime::AsMicroseconds( VALUE aSelf )
{
	return LONG2NUM( rbMacros::ToSFML< sf::Time >( aSelf, rbTime::Class )->asMicroseconds() );
}

// Time#marshal_dump
VALUE rbTime::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
    return Qnil;
}

// Time#<=>( other )
VALUE rbTime::Compare( VALUE aSelf, VALUE anOther )
{
    sf::Uint64 time1 = rbMacros::ToSFML< sf::Time >( aSelf, rbTime::Class )->asMicroseconds();
    sf::Uint64 time2 = rbMacros::ToSFML< sf::Time >( anOther, rbTime::Class )->asMicroseconds();

    if( time1 == time2 ) return INT2FIX( 0 );
    if( time1 > time2 ) return INT2FIX( 1 );
    return INT2FIX( -1 );
}

// Time#-@
VALUE rbTime::Negate( VALUE aSelf )
{
	sf::Time* time = rbMacros::Allocate< sf::Time >();
	*time = -( *rbMacros::ToSFML< sf::Time >( aSelf, rbTime::Class ) );
	return rbMacros::ToRuby( time, rbTime::Class );
}

// Time#+( other )
VALUE rbTime::Addition( VALUE aSelf, VALUE anOther )
{
	sf::Time* time = rbMacros::Allocate< sf::Time >();
	*time = ( *rbMacros::ToSFML< sf::Time >( aSelf, rbTime::Class ) ) +
			( *rbMacros::ToSFML< sf::Time >( anOther, rbTime::Class ) );
	return rbMacros::ToRuby( time, rbTime::Class );
}

// Time#-( other )
VALUE rbTime::Subtract( VALUE aSelf, VALUE anOther )
{
	sf::Time* time = rbMacros::Allocate< sf::Time >();
	*time = ( *rbMacros::ToSFML< sf::Time >( aSelf, rbTime::Class ) ) -
			( *rbMacros::ToSFML< sf::Time >( anOther, rbTime::Class ) );
	return rbMacros::ToRuby( time, rbTime::Class );
}

// Time#*( other )
VALUE rbTime::Multiply( VALUE aSelf, VALUE anOther )
{
	sf::Time* time = rbMacros::Allocate< sf::Time >();

	if( rb_obj_is_kind_of( anOther, rb_cFixnum ) )
	{
		*time = ( *rbMacros::ToSFML< sf::Time >( aSelf, rbTime::Class ) ) *
				static_cast< sf::Int64 >( FIX2LONG( anOther ) );
	}
	else if( rb_obj_is_kind_of( anOther, rb_cFloat ) )
	{
		*time = ( *rbMacros::ToSFML< sf::Time >( aSelf, rbTime::Class ) ) *
				static_cast< float >( NUM2DBL( anOther ) );
	}
	else
	{
		INVALID_EXPECTED_TYPES( rb_cFixnum, rb_cFloat );
	}

	return rbMacros::ToRuby( time, rbTime::Class );
}

// Time#/( other )
VALUE rbTime::Divide( VALUE aSelf, VALUE anOther )
{
	sf::Time* time = rbMacros::Allocate< sf::Time >();

	if( rb_obj_is_kind_of( anOther, rb_cFixnum ) )
	{
		*time = ( *rbMacros::ToSFML< sf::Time >( aSelf, rbTime::Class ) ) /
				static_cast< sf::Int64 >( FIX2LONG( anOther ) );
	}
	else if( rb_obj_is_kind_of( anOther, rb_cFloat ) )
	{
		*time = ( *rbMacros::ToSFML< sf::Time >( aSelf, rbTime::Class ) ) /
				static_cast< float >( NUM2DBL( anOther ) );
	}
	else
	{
		INVALID_EXPECTED_TYPES( rb_cFixnum, rb_cFloat );
	}

	return rbMacros::ToRuby( time, rbTime::Class );
}

// Time#inspect
// Timne#to_s
VALUE rbTime::Inspect( VALUE aSelf )
{
    sf::Time* time = rbMacros::ToSFML< sf::Time >( aSelf, rbTime::Class );
    return rb_sprintf( "%s(%fs)",
                       rb_obj_classname( aSelf ),
                       time->asSeconds() );
}
