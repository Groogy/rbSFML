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
    ext_define_module_function( rbListener::Module, "get_global_volumen", rbListener::GetGlobalVolume,  0 );
    ext_define_module_function( rbListener::Module, "set_global_volume",  rbListener::SetGlobalVolume,  1 );
    ext_define_module_function( rbListener::Module, "get_position",       rbListener::GetPosition,      0 );
    ext_define_module_function( rbListener::Module, "set_position",       rbListener::SetPosition,     -1 );
    ext_define_module_function( rbListener::Module, "get_direction",      rbListener::GetDirection,     0 );
    ext_define_module_function( rbListener::Module, "set_direction",      rbListener::SetDirection,    -1 );

    // Singleton aliasses
    VALUE sListener = rb_singleton_class( rbListener::Module );
    rb_define_alias( sListener, "global_volume=",  "set_global_volume" );
	rb_define_alias( sListener, "setGlobalVolume", "set_global_volume" );
    rb_define_alias( sListener, "global_volume",   "get_global_volume" );
	rb_define_alias( sListener, "getGlobalVolume", "get_global_volume" );
    rb_define_alias( sListener, "position=",       "set_position"      );
	rb_define_alias( sListener, "setPosition",     "set_position"      );
    rb_define_alias( sListener, "position",        "get_position"      );
	rb_define_alias( sListener, "getPosition",     "get_position"      );
    rb_define_alias( sListener, "direction=",      "set_direction"     );
	rb_define_alias( sListener, "setDirection",    "set_direction"     );
    rb_define_alias( sListener, "direction",       "get_direction"     );
	rb_define_alias( sListener, "getDirection",    "get_direction"     );
}

// Listener.global_volume
// Listener.get_global_volume
// Listener.getGlobalVolume
VALUE rbListener::GetGlobalVolume( VALUE aSelf )
{
    return rb_float_new( sf::Listener::getGlobalVolume() );
}

// Listener.global_volume=( volume )
// Listener.set_global_volume( volume )
// Listener.setGlobalVolume( volume )
VALUE rbListener::SetGlobalVolume( VALUE aSelf, VALUE aVolume )
{
    sf::Listener::setGlobalVolume( NUM2DBL( aVolume ) );
    return Qnil;
}

// Listener.position
// Listener.get_position
// Listener.getPoistion
VALUE rbListener::GetPosition( VALUE aSelf )
{
    sf::Vector3f pos = sf::Listener::getPosition();
    return rbVector3::ToRuby( pos );
}

// Listener.set_position(position)
// Listener.set_position(x, y, z)
// Listener.position=(position)
// Listener.position=(x, y, z)
// Listener.setPosition(position)
// Listener.setPosition(x, y, z)
VALUE rbListener::SetPosition( int argc, VALUE argv[], VALUE aSelf )
{
    switch( argc )
    {
        case 1:
        {
            sf::Vector3f pos = rbVector3::ToSFMLf( argv[ 0 ] );
            sf::Listener::setPosition( pos );
            break;
        }
        case 3:
        {
            float x = NUM2DBL( argv[ 0 ] );
            float y = NUM2DBL( argv[ 1 ] );
            float z = NUM2DBL( argv[ 2 ] );
            sf::Listener::setPosition( x, y, z );
            break;
        }
        default:
            INVALID_ARGUMENT_LIST( argc, "1 or 3" );
    }
    return Qnil;
}

// Listener.get_direction
// Listener.direction
// Listener.getDirection
VALUE rbListener::GetDirection( VALUE aSelf )
{
    sf::Vector3f pos = sf::Listener::getDirection();
    return rbVector3::ToRuby( pos );
}

// Listener.set_direction(direction)
// Listener.set_direction(x, y, z)
// Listener.direction=(direction)
// Listener.direction=(x, y, z)
// Listener.setDirection(direction)
// Listener.setDirection(x, y, z)
VALUE rbListener::SetDirection( int argc, VALUE argv[], VALUE aSelf )
{
    switch( argc )
    {
        case 1:
        {
            sf::Vector3f pos = rbVector3::ToSFMLf( argv[ 0 ] );
            sf::Listener::setDirection( pos );
            break;
        }
        case 3:
        {
            float x = NUM2DBL( argv[ 0 ] );
            float y = NUM2DBL( argv[ 1 ] );
            float z = NUM2DBL( argv[ 2 ] );
            sf::Listener::setDirection( x, y, z );
            break;
        }
        default:
            INVALID_ARGUMENT_LIST( argc, "1 or 3" );
    }
    return Qnil;
}
