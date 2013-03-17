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

#ifndef WINDOW_WINDOW_HPP
#define WINDOW_WINDOW_HPP

#include <ruby.h>

#include "../rbSFML.hpp"
#include "../System/SFML.hpp"
#include "../System/Vector2.hpp"
#include "ContextSettings.hpp"
#include "Event.hpp"
#include "VideoMode.hpp"

#include <SFML/Window/Window.hpp>

namespace rbWindow
{
#if defined( WINDOW_WINDOW_CPP )
    VALUE Class;
#else
    extern VALUE Class;
#endif
    
#if defined( RBSFML_WINDOW )
    void Init( VALUE SFML );
#endif
    
#if defined( WINDOW_WINDOW_CPP )
    // Window#initialize(...)
    static VALUE Initialize( int argc, VALUE args[], VALUE aSelf );
    
    // Window#marshal_dump
    static VALUE MarshalDump( VALUE aSelf );
    
    // Window#create(...)
    static VALUE Create( int argc, VALUE args[], VALUE aSelf );
    
    // Window#close
    static VALUE Close( VALUE aSelf );
    
    // Window#open?
	// Window#is_open?
	// Window#is_open
    // Window#isOpen
    static VALUE IsOpen( VALUE aSelf );
    
    // Window#settings
	// Window#get_settings
    // Window#getSettings
    static VALUE GetSettings( VALUE aSelf );
    
    // Window#poll_event
    // Window#pollEvent
    // Window#poll_event(event)
    // Window#pollEvent(event)
    static VALUE PollEvent( int argc, VALUE argv[], VALUE aSelf );
    
    // Window#wait_event
    // Window#waitEvent
    // Window#wait_event(event)
    // Window#waitEvent(event)
    static VALUE WaitEvent( int argc, VALUE argv[], VALUE aSelf );
    
    // Window#each_event
    static VALUE EachEvent( VALUE aSelf );
    
    // Window#vertical_sync_enabled=(enabled)
    // Window#setVerticalSyncEnabled(enabled)
	// Window#set_vertical_sync_enabled(enabled)
    static VALUE SetVerticalSyncEnabled( VALUE aSelf, VALUE anEnabled );
    
    // Window#mouse_cursor_visible=(show)
    // Window#setMouseCursorVisible(show)
	// Window#set_mouse_cursor_visible(show)
    static VALUE SetMouseCursorVisible( VALUE aSelf, VALUE aShow );
    
    // Window#position=(vector2)
	// Window#set_position(vector2)
	// Window#setPosition(vector2)
    static VALUE SetPosition( VALUE aSelf, VALUE aPosition );
	
	// Window#position()
	// Window#get_position()
	// Window#getPosition()
    static VALUE GetPosition( VALUE aSelf );
    
    // Window#size=(vector2)
	// Window#set_size(vector2)
	// Window#setSize(vector2)
    static VALUE SetSize( VALUE aSelf, VALUE aSize );
	
	// Window#size()
	// Window#get_size()
	// Window#getSize()
    static VALUE GetSize( VALUE aSelf );
    
    // Window#title=(title)
    // Window#set_title(title)
    // Window#setTitle(title)
    static VALUE SetTitle( VALUE aSelf, VALUE aTitle );
    
    // Window#visible=(show)
	// Window#set_visible(show)
	// Window#setVisible(show)
    static VALUE SetVisible( VALUE aSelf, VALUE aShow );
    
    // Window#key_repeat=(enabled)
	// Window#set_key_repeat_enabled(enabled)
    // Window#setKeyRepeatEnabled(enabled)
    static VALUE SetKeyRepeatEnabled( VALUE aSelf, VALUE anEnabled );
    
    // Window#set_icon(width, height, pixels)
    // Window#setIcon(width, height, pixels)
    static VALUE SetIcon( VALUE aSelf, VALUE aWidth, VALUE aHeight, VALUE aPixels );
    
	// Window#active=(active = true)
	// Window#set_active(active = true)
    // Window#setActive(active = true)
    static VALUE SetActive( int argc, VALUE argv[], VALUE aSelf );
    
    // Window#display()
    static VALUE Display( VALUE aSelf );
    
	// Window#fps=(limit)
    // Window#framerate=(limit)
    // Window#framerate_limit=(limit)
	// Window#set_framerate(limit)
	// Window#set_framerate_limit(limit)
	// Window#setFramerateLimit(limit)
    static VALUE SetFramerateLimit( VALUE aSelf, VALUE aLimit );
    
    // Window#joystick_threshold=(threshold)
	// Window#set_joystick_threshold(threshold)
    // Window#setJoystickThreshold(threshold)
    static VALUE SetJoystickThreshold( VALUE aSelf, VALUE aThreshold );
    
    // Window#system_handle
    // Window#getSystemHandle
    // Window#handle
    static VALUE GetSystemHandle( VALUE aSelf );
    
    // Window#inspect
    // Window#to_s
    static VALUE Inspect( VALUE aSelf );

#endif
}

#endif // WINDOW_WINDOW_HPP
