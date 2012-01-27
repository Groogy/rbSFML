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

#define AUDIO_LISTENER_CPP

#include "Listener.hpp"

void rbListener::Init( VALUE SFML )
{
    rbListener::Module = rb_define_module_under( SFML, "Listener" );

    // Singleton methods
    rb_define_module_function( rbListener::Module, "get_global_volumen", rbListener::GetGlobalVolume,  0 );
    rb_define_module_function( rbListener::Module, "set_global_volume",  rbListener::SetGlobalVolume,  1 );
    rb_define_module_function( rbListener::Module, "get_position",       rbListener::GetPosition,      0 );
    rb_define_module_function( rbListener::Module, "set_position",       rbListener::SetPosition,     -1 );
    rb_define_module_function( rbListener::Module, "get_direction",      rbListener::GetDirection,     0 );
    rb_define_module_function( rbListener::Module, "set_direction",      rbListener::SetDirection,    -1 );

    // Singleton aliasses
    VALUE sListener = rb_singleton_class( rbListener::Module );
    rb_define_alias( sListener, "global_volume=", "set_global_volume" );
    rb_define_alias( sListener, "global_volume",  "get_global_volume" );
    rb_define_alias( sListener, "position=",      "set_position"      );
    rb_define_alias( sListener, "position",       "get_position"      );
    rb_define_alias( sListener, "direction=",     "set_direction"     );
    rb_define_alias( sListener, "direction",      "get_direction"     );
}

// Listener::GetGlobalVolume
VALUE rbListener::GetGlobalVolume( VALUE aSelf )
{
    return rb_float_new( sf::Listener::GetGlobalVolume() );
}

// Listener::SetGlobalVolume(volume)
VALUE rbListener::SetGlobalVolume( VALUE aSelf, VALUE aVolume )
{
    sf::Listener::SetGlobalVolume( NUM2DBL( aVolume ) );
    return Qnil;
}

// Listener::GetPosition
VALUE rbListener::GetPosition( VALUE aSelf )
{
    sf::Vector3f pos = sf::Listener::GetPosition();
    return rbVector3::ToRuby( pos );
}

// Listener::SetPosition(position)
// Listener::SetPosition(x, y, z)
VALUE rbListener::SetPosition( int argc, VALUE argv[], VALUE aSelf )
{
    switch( argc )
    {
        case 1:
        {
            sf::Vector3f pos = rbVector3::ToSFMLf( argv[ 0 ] );
            sf::Listener::SetPosition( pos );
            break;
        }
        case 3:
        {
            float x = NUM2DBL( argv[ 0 ] );
            float y = NUM2DBL( argv[ 1 ] );
            float z = NUM2DBL( argv[ 2 ] );
            sf::Listener::SetPosition( x, y, z );
            break;
        }
        default:
            INVALID_ARGUMENT_LIST( argc, "1 or 3" );
    }
    return Qnil;
}

// Listener::GetDirection
VALUE rbListener::GetDirection( VALUE aSelf )
{
    sf::Vector3f pos = sf::Listener::GetDirection();
    return rbVector3::ToRuby( pos );
}

// Listener::SetDirection(direction)
// Listener::SetDirection(x, y, z)
VALUE rbListener::SetDirection( int argc, VALUE argv[], VALUE aSelf )
{
    switch( argc )
    {
        case 1:
        {
            sf::Vector3f pos = rbVector3::ToSFMLf( argv[ 0 ] );
            sf::Listener::SetDirection( pos );
            break;
        }
        case 3:
        {
            float x = NUM2DBL( argv[ 0 ] );
            float y = NUM2DBL( argv[ 1 ] );
            float z = NUM2DBL( argv[ 2 ] );
            sf::Listener::SetDirection( x, y, z );
            break;
        }
        default:
            INVALID_ARGUMENT_LIST( argc, "1 or 3" );
    }
    return Qnil;
}
