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

#define SYSTEM_CLOCK_CPP

#include "Clock.hpp"
#include "Time.hpp"

void rbClock::Init( VALUE SFML )
{
    rbClock::Class = rb_define_class_under( SFML, "Clock", rb_cObject );

    // Class methods
    rb_define_alloc_func( rbClock::Class, rbMacros::Allocate< sf::Clock > );

    // Instance methods
    ext_define_method( rbClock::Class, "initialize_copy", rbClock::InitializeCopy, 1 );
    ext_define_method( rbClock::Class, "marshal_dump",    rbClock::MarshalDump,    0 );
    ext_define_method( rbClock::Class, "elapsed_time",    rbClock::GetElapsedTime, 0 );
    ext_define_method( rbClock::Class, "restart",         rbClock::Restart,        0 );
    ext_define_method( rbClock::Class, "inspect",         rbClock::Inspect,        0 );

    // Instance aliasses
    rb_define_alias( rbClock::Class, "getElapsedTime",   "elapsed_time" );
    rb_define_alias( rbClock::Class, "get_elapsed_time", "elapsed_time" );
    rb_define_alias( rbClock::Class, "time",             "elapsed_time" );
    rb_define_alias( rbClock::Class, "to_s",             "inspect"      );
}

// Clock#initialize_copy(clock)
VALUE rbClock::InitializeCopy( VALUE aSelf, VALUE aClock )
{
    *rbMacros::ToSFML< sf::Clock >( aSelf, rbClock::Class ) = *rbMacros::ToSFML< sf::Clock >( aClock, rbClock::Class );
    return aSelf;
}

// Clock#marshal_dump
VALUE rbClock::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
    return Qnil;
}

// Clock#elapsed_time
// Clock#getElapsedTime
// Clock#time
VALUE rbClock::GetElapsedTime( VALUE aSelf )
{
	sf::Time* time = rbMacros::Allocate< sf::Time >();
	*time = rbMacros::ToSFML< sf::Clock >( aSelf, rbClock::Class )->getElapsedTime();
    return rbMacros::ToRuby( time, rbTime::Class );
}

// Clock#restart
VALUE rbClock::Restart( VALUE aSelf )
{
    rb_check_frozen( aSelf );
	sf::Time* time = rbMacros::Allocate< sf::Time >();
    *time = rbMacros::ToSFML< sf::Clock >( aSelf, rbClock::Class )->restart();
    return rbMacros::ToRuby( time, rbTime::Class );
}

// Clock#inspect
// Clock#to_s
VALUE rbClock::Inspect( VALUE aSelf )
{
    sf::Clock* clock = rbMacros::ToSFML< sf::Clock >( aSelf, rbClock::Class );
    return rb_sprintf( "%s(%fs)",
                       rb_obj_classname( aSelf ),
                       clock->getElapsedTime().asSeconds() );
}

