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

#ifndef WINDOW_EVENT_HPP
#define WINDOW_EVENT_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>
#include <Window/VideoMode.hpp>

#include <SFML/Window/Event.hpp>

namespace rbEvent
{
    
    static inline void Free(void* event);
    
    static inline VALUE ToRuby(VALUE other);
    static inline VALUE ToRuby(sf::Event* event);
    static inline VALUE ToRuby(sf::Event& event);
    static inline sf::Event* ToSFML(VALUE event);
    
    static inline VALUE Allocate(VALUE);
    
#if defined(WINDOW_EVENT_CPP)
    VALUE Event;
    VALUE Event_Size;
    VALUE Event_Key;
    VALUE Event_Text;
    VALUE Event_MouseMove;
    VALUE Event_MouseButton;
    VALUE Event_MouseWheel;
    VALUE Event_JoystickMove;
    VALUE Event_JoystickButton;
    VALUE Event_JoystickConnect;
#else
    extern VALUE Event;
    extern VALUE Event_Size;
    extern VALUE Event_Key;
    extern VALUE Event_Text;
    extern VALUE Event_MouseMove;
    extern VALUE Event_MouseButton;
    extern VALUE Event_MouseWheel;
    extern VALUE Event_JoystickMove;
    extern VALUE Event_JoystickButton;
    extern VALUE Event_JoystickConnect;
#endif
    
#if defined(RBSFML_WINDOW) || defined(RBSFML_SFML)
    
    void Init(VALUE SFML);
    
    // Event#type
    static VALUE Type(VALUE self);
    
    // Event#info
    static VALUE Info(VALUE self);
    
    // Event#===(other)
    static VALUE CaseEqual(VALUE self, VALUE other);
    
    // Event#size
    static VALUE Size(VALUE self);
    
    // Event#key
    static VALUE Key(VALUE self);
    
    // Event#text
    static VALUE Text(VALUE self);
    
    // Event#mouse_move
    static VALUE MouseMove(VALUE self);
    
    // Event#mouse_button
    static VALUE MouseButton(VALUE self);
    
    // Event#mouse_wheel
    static VALUE MouseWheel(VALUE self);
    
    // Event#joystick_move
    static VALUE JoystickMove(VALUE self);
    
    // Event#joystick_button
    static VALUE JoystickButton(VALUE self);
    
    // Event#joystick_connect
    static VALUE JoystickConnect(VALUE self);
    
#endif
    
}

void rbEvent::Free(void* event)
{
    delete (sf::Event*)event;
}

VALUE rbEvent::Allocate(VALUE)
{
    sf::Event* video_mode = new(std::nothrow) sf::Event;
    if (video_mode == NULL) rb_memerror();
    return ToRuby(video_mode);
}

VALUE rbEvent::ToRuby(VALUE other)
{
    if (rb_obj_is_instance_of(other, Event))
    {
        return other;
    }
    else
    {
        rb_raise(rb_eTypeError,
                 "can't convert %s into Event", rb_obj_classname(other));
    }
}

VALUE rbEvent::ToRuby(sf::Event* event)
{
    return rb_data_object_alloc(Event, event, NULL, Free);
}

VALUE rbEvent::ToRuby(sf::Event& event)
{
    return rb_data_object_alloc(Event, &event, NULL, NULL);
}

sf::Event* rbEvent::ToSFML(VALUE event)
{
    event = ToRuby(event);
    return (sf::Event*)DATA_PTR(event);
}

#endif // WINDOW_EVENT_HPP
