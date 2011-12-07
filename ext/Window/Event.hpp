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
    static inline VALUE Allocate(VALUE);
    
    static inline VALUE ToRuby(VALUE other, VALUE klass=false);
    static inline VALUE ToRuby(sf::Event* event, VALUE klass=false);
    static inline sf::Event* ToSFML(VALUE event, VALUE klass=false);
    
#if defined(WINDOW_EVENT_CPP)
    VALUE Event;
    VALUE Event_Type;
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
    extern VALUE Event_Type;
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
    
#if defined(RBSFML_WINDOW)
    void Init(VALUE SFML);
#endif
    
#if defined(WINDOW_EVENT_CPP)
    static VALUE EventType(int id);
    static VALUE EventTypeCaseEqual(VALUE self, VALUE other);
    
    // Event#initialize_copy(event)
    static VALUE InitializeCopy(VALUE self, VALUE event);
    
    // Event#marshal_dump
    static VALUE MarshalDump(VALUE self);
    
    // Event#type
    // Event#Type
    static VALUE Type(VALUE self);
    
    // Event#info
    static VALUE Info(VALUE self);
    
    // Event#size
    // Event#Size
    static VALUE Size(VALUE self);
    
    // Event#key
    // Event#Key
    static VALUE Key(VALUE self);
    
    // Event#text
    // Event#Text
    static VALUE Text(VALUE self);
    
    // Event#mouse_move
    // Event#MouseMove
    static VALUE MouseMove(VALUE self);
    
    // Event#mouse_button
    // Event#MouseButton
    static VALUE MouseButton(VALUE self);
    
    // Event#mouse_wheel
    // Event#MouseWheel
    static VALUE MouseWheel(VALUE self);
    
    // Event#joystick_move
    // Event#JoystickMove
    static VALUE JoystickMove(VALUE self);
    
    // Event#joystick_button
    // Event#JoystickButton
    static VALUE JoystickButton(VALUE self);
    
    // Event#joystick_connect
    // Event#JoystickConnect
    static VALUE JoystickConnect(VALUE self);
    
    // Event#==(other)
    static VALUE Equal(VALUE self, VALUE other);
    
    // Event#inspect
    static VALUE Inspect(VALUE self);
    
    // Event#memory_usage
    static VALUE GetMemoryUsage(VALUE self);
#endif
    
}

void rbEvent::Free(void* event)
{
    delete (sf::Event*)event;
}

VALUE rbEvent::Allocate(VALUE self)
{
    sf::Event* event = new(std::nothrow) sf::Event;
    if (event == NULL) rb_memerror();
    return ToRuby(event, self);
}

VALUE rbEvent::ToRuby(VALUE other, VALUE klass)
{
    if (!klass)
        klass = Event;
    
    if (rb_obj_is_kind_of(other, Event))
        return other;
    
    rb_raise(rb_eTypeError, "can't convert %s into %s",
             rb_obj_classname(other), rb_class2name(klass));
}

VALUE rbEvent::ToRuby(sf::Event* event, VALUE klass)
{
    if (!klass)
        klass = Event;
    
    return rb_data_object_alloc(Event, event, NULL, Free);
}

sf::Event* rbEvent::ToSFML(VALUE event, VALUE klass)
{
    event = ToRuby(event);
    return (sf::Event*)DATA_PTR(event);
}

#endif // WINDOW_EVENT_HPP
