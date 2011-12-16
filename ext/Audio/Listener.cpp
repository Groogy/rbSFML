/* rbSFML
 * Copyright (c) 2010 Henrik Valter Vogelius Hansson - groogy@groogy.se
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

void rbListener::Init(VALUE SFML)
{
    Listener = rb_define_module_under(SFML, "Listener");
    
    // Singleton methods
    rb_define_singleton_method(Listener, "global_volume",   GlobalVolume,    -1);
    rb_define_singleton_method(Listener, "GetGlobalVolume", GetGlobalVolume,  0);
    rb_define_singleton_method(Listener, "SetGlobalVolume", SetGlobalVolume,  1);
    rb_define_singleton_method(Listener, "position",        Position,        -1);
    rb_define_singleton_method(Listener, "GetPosition",     GetPosition,      0);
    rb_define_singleton_method(Listener, "SetPosition",     SetPosition,      1);
    rb_define_singleton_method(Listener, "direction",       Direction,       -1);
    rb_define_singleton_method(Listener, "GetDirection",    GetDirection,     0);
    rb_define_singleton_method(Listener, "SetDirection",    SetDirection,     1);
    
    // Singleton aliasses
    VALUE sListener = rb_singleton_class(Listener);
    rb_define_alias(sListener, "global_volume=", "global_volume");
    rb_define_alias(sListener, "position=",      "position"     );
    rb_define_alias(sListener, "direction=",     "direction"    );
}

// Listener::global_volume
// Listener::global_volume(volume)
// Listener::global_volume=(volume)
VALUE rbListener::GlobalVolume(int argc, VALUE argv[], VALUE self)
{
    switch(argc)
    {
        case 0:
            return GetGlobalVolume(self);
        case 1:
            return SetGlobalVolume(self, argv[0]);
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments (%i for 0..1)", argc);
    }
    return Qnil;
}

// Listener::GetGlobalVolume
VALUE rbListener::GetGlobalVolume(VALUE self)
{
    return rb_float_new(sf::Listener::GetGlobalVolume());
}

// Listener::SetGlobalVolume(volume)
VALUE rbListener::SetGlobalVolume(VALUE self, VALUE volume)
{
    sf::Listener::SetGlobalVolume(NUM2DBL(volume));
    return Qnil;
}

// Listener::position
// Listener::position(position)
// Listener::position=(position)
// Listener::position(x, y, z)
VALUE rbListener::Position(int argc, VALUE argv[], VALUE self)
{
    switch(argc)
    {
        case 0:
            return GetPosition(self);
        case 1:
        case 3:
            return SetPosition(argc, argv, self);
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments (%i for 0, 1, or 3)", argc);
    }
    return Qnil;
}

// Listener::GetPosition
VALUE rbListener::GetPosition(VALUE self)
{
    sf::Vector3f pos = sf::Listener::GetPosition();
    return rbVector3::ToRuby(pos);
}

// Listener::SetPosition(position)
// Listener::SetPosition(x, y, z)
VALUE rbListener::SetPosition(int argc, VALUE argv[], VALUE self)
{
    switch (argc)
    {
        case 1:
        {
            sf::Vector3f pos = rbVector3::ToSFMLf(argv[0]);
            sf::Listener::SetPosition(pos);
            break;
        }
        case 3:
        {
            float x = NUM2DBL(argv[0]);
            float y = NUM2DBL(argv[1]);
            float z = NUM2DBL(argv[2]);
            sf::Listener::SetPosition(x, y, z);
            break;
        }
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 1 or 3)", argc);
    }
    return Qnil;
}

// Listener::direction
// Listener::direction(direction)
// Listener::direction=(direction)
// Listener::direction(x, y, z)
VALUE rbListener::Direction(int argc, VALUE argv[], VALUE self)
{
    switch(argc)
    {
        case 0:
            return GetDirection(self);
        case 1:
        case 3:
            return SetDirection(argc, argv, self);
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments (%i for 0, 1, or 3)", argc);
    }
    return Qnil;
}

// Listener::GetDirection
VALUE rbListener::GetDirection(VALUE self)
{
    sf::Vector3f pos = sf::Listener::GetDirection();
    return rbVector3::ToRuby(pos);
}

// Listener::SetDirection(direction)
// Listener::SetDirection(x, y, z)
VALUE rbListener::SetDirection(int argc, VALUE argv[], VALUE self)
{
    switch (argc)
    {
        case 1:
        {
            sf::Vector3f pos = rbVector3::ToSFMLf(argv[0]);
            sf::Listener::SetDirection(pos);
            break;
        }
        case 3:
        {
            float x = NUM2DBL(argv[0]);
            float y = NUM2DBL(argv[1]);
            float z = NUM2DBL(argv[2]);
            sf::Listener::SetDirection(x, y, z);
            break;
        }
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 1 or 3)", argc);
    }
    return Qnil;
}
