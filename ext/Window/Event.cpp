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

#define WINDOW_EVENT_CPP
#include "Event.hpp"

void rbEvent::Init( VALUE SFML )
{
    rbEvent::Class = rb_define_class_under( SFML, "Event", rb_cObject );
    
    // Subclasses
    rbEvent::Class_Size            = rb_define_class_under( rbEvent::Class, "Size",            rb_cObject );
    rbEvent::Class_Key             = rb_define_class_under( rbEvent::Class, "Key",             rb_cObject );
    rbEvent::Class_Text            = rb_define_class_under( rbEvent::Class, "Text",            rb_cObject );
    rbEvent::Class_MouseMove       = rb_define_class_under( rbEvent::Class, "MouseMove",       rb_cObject );
    rbEvent::Class_MouseButton     = rb_define_class_under( rbEvent::Class, "MouseButton",     rb_cObject );
    rbEvent::Class_MouseWheel      = rb_define_class_under( rbEvent::Class, "MouseWheel",      rb_cObject );
    rbEvent::Class_JoystickMove    = rb_define_class_under( rbEvent::Class, "JoystickMove",    rb_cObject );
    rbEvent::Class_JoystickButton  = rb_define_class_under( rbEvent::Class, "JoystickButton",  rb_cObject );
    rbEvent::Class_JoystickConnect = rb_define_class_under( rbEvent::Class, "JoystickConnect", rb_cObject );
    
    // Event::Size accessors
    rb_define_attr( rbEvent::Class_Size, "width",  true, false );
    rb_define_attr( rbEvent::Class_Size, "height", true, false );
    rb_define_alias( rbEvent::Class_Size, "Width",  "width" );
    rb_define_alias( rbEvent::Class_Size, "Height", "height" );
    
    // Event::Key accessors
    rb_define_attr( rbEvent::Class_Key, "code",    true, false );
    rb_define_attr( rbEvent::Class_Key, "alt",     true, false );
    rb_define_attr( rbEvent::Class_Key, "control", true, false );
    rb_define_attr( rbEvent::Class_Key, "shift",   true, false );
    rb_define_attr( rbEvent::Class_Key, "system",  true, false );
    
    // Event::Text accessors
    rb_define_attr( rbEvent::Class_Text, "unicode", true, false );
    
    // Event::MouseMove accessors
    rb_define_attr(rbEvent::Class_MouseMove, "x", true, false );
    rb_define_attr(rbEvent::Class_MouseMove, "y", true, false );
    
    // Event::MouseButton accessors
    rb_define_attr(rbEvent::Class_MouseButton, "button", true, false );
    rb_define_attr(rbEvent::Class_MouseButton, "x",      true, false );
    rb_define_attr(rbEvent::Class_MouseButton, "y",      true, false );
    
    // Event::MouseWheel accessors
    rb_define_attr( rbEvent::Class_MouseWheel, "delta", true, false );
    rb_define_attr( rbEvent::Class_MouseWheel, "x",     true, false );
    rb_define_attr( rbEvent::Class_MouseWheel, "y",     true, false );
    
    // Event::JoystickConnect accessors
    rb_define_attr( rbEvent::Class_JoystickConnect, "id", true, false );
    rb_define_alias( rbEvent::Class_JoystickConnect, "joystickId", "id" );
    
    // Event::JoystickMove accessors
    rb_define_attr( rbEvent::Class_JoystickMove, "id",       true, false );
    rb_define_attr( rbEvent::Class_JoystickMove, "axis",     true, false );
    rb_define_attr( rbEvent::Class_JoystickMove, "position", true, false );
    rb_define_alias( rbEvent::Class_JoystickMove, "joystickId", "id"      );
    
    // Event::JoystickButton accessors
    rb_define_attr( rbEvent::Class_JoystickButton, "id",     true, false );
    rb_define_attr( rbEvent::Class_JoystickButton, "button", true, false );
    rb_define_alias( rbEvent::Class_JoystickButton, "joystickId", "id"    );
    
    // Constants
    rb_define_const( rbEvent::Class, "Closed",                 INT2NUM( sf::Event::Closed                 ) );
    rb_define_const( rbEvent::Class, "Resized",                INT2NUM( sf::Event::Resized                ) );
    rb_define_const( rbEvent::Class, "LostFocus",              INT2NUM( sf::Event::LostFocus              ) );
    rb_define_const( rbEvent::Class, "GainedFocus",            INT2NUM( sf::Event::GainedFocus            ) );
    rb_define_const( rbEvent::Class, "TextEntered",            INT2NUM( sf::Event::TextEntered            ) );
    rb_define_const( rbEvent::Class, "KeyPressed",             INT2NUM( sf::Event::KeyPressed             ) );
    rb_define_const( rbEvent::Class, "KeyReleased",            INT2NUM( sf::Event::KeyReleased            ) );
    rb_define_const( rbEvent::Class, "MouseWheelMoved",        INT2NUM( sf::Event::MouseWheelMoved        ) );
    rb_define_const( rbEvent::Class, "MouseButtonPressed",     INT2NUM( sf::Event::MouseButtonPressed     ) );
    rb_define_const( rbEvent::Class, "MouseButtonReleased",    INT2NUM( sf::Event::MouseButtonReleased    ) );
    rb_define_const( rbEvent::Class, "MouseMoved",             INT2NUM( sf::Event::MouseMoved             ) );
    rb_define_const( rbEvent::Class, "MouseEntered",           INT2NUM( sf::Event::MouseEntered           ) );
    rb_define_const( rbEvent::Class, "MouseLeft",              INT2NUM( sf::Event::MouseLeft              ) );
    rb_define_const( rbEvent::Class, "JoystickButtonPressed",  INT2NUM( sf::Event::JoystickButtonPressed  ) );
    rb_define_const( rbEvent::Class, "JoystickButtonReleased", INT2NUM( sf::Event::JoystickButtonReleased ) );
    rb_define_const( rbEvent::Class, "JoystickMoved",          INT2NUM( sf::Event::JoystickMoved          ) );
    rb_define_const( rbEvent::Class, "JoystickConnected",      INT2NUM( sf::Event::JoystickConnected      ) );
    rb_define_const( rbEvent::Class, "JoystickDisconnected",   INT2NUM( sf::Event::JoystickDisconnected   ) );
    
    // Class methods
    rb_define_alloc_func( rbEvent::Class, rbMacros::Allocate< sf::Event > );
    
    // Instance methods
    ext_define_method( rbEvent::Class, "initialize_copy",  rbEvent::InitializeCopy,  1 );
    ext_define_method( rbEvent::Class, "marshal_dump",     rbEvent::MarshalDump,     0 );
    ext_define_method( rbEvent::Class, "type",             rbEvent::Type,            0 );
    ext_define_method( rbEvent::Class, "info",             rbEvent::Info,            0 );
    ext_define_method( rbEvent::Class, "size",             rbEvent::Size,            0 );
    ext_define_method( rbEvent::Class, "key",              rbEvent::Key,             0 );
    ext_define_method( rbEvent::Class, "text",             rbEvent::Text,            0 );
    ext_define_method( rbEvent::Class, "mouse_move",       rbEvent::MouseMove,       0 );
    ext_define_method( rbEvent::Class, "mouse_button",     rbEvent::MouseButton,     0 );
    ext_define_method( rbEvent::Class, "mouse_wheel",      rbEvent::MouseWheel,      0 );
    ext_define_method( rbEvent::Class, "joystick_move",    rbEvent::JoystickMove,    0 );
    ext_define_method( rbEvent::Class, "joystick_button",  rbEvent::JoystickButton,  0 );
    ext_define_method( rbEvent::Class, "joystick_connect", rbEvent::JoystickConnect, 0 );
    ext_define_method( rbEvent::Class, "==",               rbEvent::Equal,           1 );
    ext_define_method( rbEvent::Class, "inspect",          rbEvent::Inspect,         0 );
    
    // Instance aliasses
    rb_define_alias( rbEvent::Class, "mouseMove",       "mouse_move"       );
    rb_define_alias( rbEvent::Class, "mouseButton",     "mouse_button"     );
    rb_define_alias( rbEvent::Class, "mouseWheel",      "mouse_wheel"      );
    rb_define_alias( rbEvent::Class, "joystickMove",    "joystick_move"    );
    rb_define_alias( rbEvent::Class, "joystickButton",  "joystick_button"  );
    rb_define_alias( rbEvent::Class, "joystickConnect", "joystick_connect" );
    rb_define_alias( rbEvent::Class, "eql?",            "=="               );
    rb_define_alias( rbEvent::Class, "equal?",          "=="               );
    rb_define_alias( rbEvent::Class, "to_s",            "inspect"          );
}

#include <iostream>

// Event#initialize_copy(event)
VALUE rbEvent::InitializeCopy( VALUE aSelf, VALUE anEvent )
{
    *rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class ) = *rbMacros::ToSFML< sf::Event >( anEvent, rbEvent::Class );
    return aSelf;
}

// Event#marshal_dump
VALUE rbEvent::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) ); // TODO
    return Qnil;
}

// Event#type
VALUE rbEvent::Type( VALUE aSelf )
{
    return INT2NUM( rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->type );
}

// Event#info
VALUE rbEvent::Info( VALUE aSelf )
{
    switch( rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->type )
    {
        case sf::Event::Closed:
        case sf::Event::LostFocus:
        case sf::Event::GainedFocus:
        case sf::Event::MouseEntered:
        case sf::Event::MouseLeft:
            return Qnil;
        case sf::Event::Resized:
            return Size( aSelf );
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
            return Key( aSelf );
        case sf::Event::TextEntered:
            return Text( aSelf );
        case sf::Event::MouseMoved:
            return MouseMove( aSelf );
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
            return MouseButton( aSelf );
        case sf::Event::MouseWheelMoved:
            return MouseWheel( aSelf );
        case sf::Event::JoystickMoved:
            return JoystickMove( aSelf );
        case sf::Event::JoystickButtonPressed:
        case sf::Event::JoystickButtonReleased:
            return JoystickButton( aSelf );
        case sf::Event::JoystickConnected:
        case sf::Event::JoystickDisconnected:
            return JoystickConnect( aSelf );
        default:
            return Qnil;
    }
}

// Event#size
VALUE rbEvent::Size( VALUE aSelf )
{
    sf::Event::SizeEvent sizeEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->size;
    VALUE size = rb_obj_alloc( rbEvent::Class_Size );
    
    rb_iv_set( size, "@width",  INT2FIX( sizeEvent.width  ) );
    rb_iv_set( size, "@height", INT2FIX( sizeEvent.height ) );
    
    return size;
}

// Event#key
VALUE rbEvent::Key( VALUE aSelf )
{
    sf::Event::KeyEvent keyEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->key;
    VALUE key = rb_obj_alloc( rbEvent::Class_Key );
    
    rb_iv_set( key, "@code",    INT2FIX( keyEvent.code ) );
    rb_iv_set( key, "@alt",     RBOOL( keyEvent.alt     ) );
    rb_iv_set( key, "@control", RBOOL( keyEvent.control ) );
    rb_iv_set( key, "@shift",   RBOOL( keyEvent.shift   ) );
    rb_iv_set( key, "@system",  RBOOL( keyEvent.system  ) );
    
    return key;
}

// Event#text
VALUE rbEvent::Text( VALUE aSelf )
{
    sf::Event::TextEvent textEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->text;
    VALUE text = rb_obj_alloc( rbEvent::Class_Text);
    
    rb_iv_set( text, "@unicode", UINT2NUM( textEvent.unicode ) );
    
    return text;
}

// Event#mouse_move
// Event#mouseMove
VALUE rbEvent::MouseMove( VALUE aSelf )
{
    sf::Event::MouseMoveEvent mouseMoveEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->mouseMove;
    VALUE mouseMove = rb_obj_alloc( rbEvent::Class_MouseMove);
    
    rb_iv_set( mouseMove, "@x", INT2FIX( mouseMoveEvent.x ) );
    rb_iv_set( mouseMove, "@y", INT2FIX( mouseMoveEvent.y ) );
    
    return mouseMove;
}

// Event#mouse_button
// Event#mouseButton
VALUE rbEvent::MouseButton( VALUE aSelf )
{
    sf::Event::MouseButtonEvent mouseButtonEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->mouseButton;
    VALUE mouseButton = rb_obj_alloc( rbEvent::Class_MouseButton );
    
    rb_iv_set( mouseButton, "@button", INT2FIX(mouseButtonEvent.button ) );
    rb_iv_set( mouseButton, "@x",      INT2FIX(mouseButtonEvent.x      ) );
    rb_iv_set( mouseButton, "@y",      INT2FIX(mouseButtonEvent.y      ) );
    
    return mouseButton;
}

// Event#mouse_wheel
// Event#mouseWheel
VALUE rbEvent::MouseWheel( VALUE aSelf )
{
    sf::Event::MouseWheelEvent mouseWheelEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->mouseWheel;
    VALUE mouseWheel = rb_obj_alloc( rbEvent::Class_MouseWheel );
    
    rb_iv_set( mouseWheel, "@delta", INT2FIX( mouseWheelEvent.delta ) );
    rb_iv_set( mouseWheel, "@x",     INT2FIX( mouseWheelEvent.x     ) );
    rb_iv_set( mouseWheel, "@y",     INT2FIX( mouseWheelEvent.y     ) );
    
    return mouseWheel;
}

// Event#joystick_move
// Event#joystickMove
VALUE rbEvent::JoystickMove( VALUE aSelf )
{
    sf::Event::JoystickMoveEvent joystickMoveEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->joystickMove;
    VALUE joystickMove = rb_obj_alloc( rbEvent::Class_JoystickMove );
    
    rb_iv_set( joystickMove, "@id",       INT2FIX( joystickMoveEvent.joystickId ) );
    rb_iv_set( joystickMove, "@axis",     INT2FIX( joystickMoveEvent.axis       ) );
    rb_iv_set( joystickMove, "@position", rb_float_new( joystickMoveEvent.position ) );
    
    return joystickMove;
}

// Event#joystick_button
// Event#joystickButton
VALUE rbEvent::JoystickButton( VALUE aSelf )
{
    sf::Event::JoystickButtonEvent joystickButtonEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->joystickButton;
    VALUE joystickButton = rb_obj_alloc( rbEvent::Class_JoystickButton);
    
    rb_iv_set( joystickButton, "@id",     INT2FIX( joystickButtonEvent.joystickId ) );
    rb_iv_set( joystickButton, "@button", INT2FIX( joystickButtonEvent.button     ) );
    
    return joystickButton;
}

// Event#joystick_connect
// Event#joystickConnect
VALUE rbEvent::JoystickConnect( VALUE aSelf )
{
    sf::Event::JoystickConnectEvent joystickConnectEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->joystickConnect;
    VALUE joystickConnect = rb_obj_alloc( rbEvent::Class_JoystickConnect);
    
    rb_iv_set( joystickConnect, "@id", INT2FIX( joystickConnectEvent.joystickId ) );
    
    return joystickConnect;
}

// Event#==(other)
VALUE rbEvent::Equal( VALUE aSelf, VALUE anOther )
{
    if( CLASS_OF( anOther ) != rbEvent::Class ) return Qfalse;
    if( rbEvent::Type( aSelf ) != rbEvent::Type( anOther ) ) return Qfalse;
    if( rbEvent::Info( aSelf ) != rbEvent::Info( anOther ) ) return Qfalse;
    return Qtrue;
}

static inline const char* EventTypeName( int aType )
{
    switch( aType )
    {
        case sf::Event::Closed:
            return "Closed";
        case sf::Event::LostFocus:
            return "LostFocus";
        case sf::Event::GainedFocus:
            return "GainedFocus";
        case sf::Event::MouseEntered:
            return "MouseEntered";
        case sf::Event::MouseLeft:
            return "MouseLeft";
        case sf::Event::Resized:
            return "Resized";
        case sf::Event::KeyPressed:
            return "KeyPressed";
        case sf::Event::KeyReleased:
            return "KeyReleased";
        case sf::Event::TextEntered:
            return "TextEntered";
        case sf::Event::MouseMoved:
            return "MouseMoved";
        case sf::Event::MouseButtonPressed:
            return "MouseButtonPressed";
        case sf::Event::MouseButtonReleased:
            return "MouseButtonReleased";
        case sf::Event::MouseWheelMoved:
            return "MouseWheelMoved";
        case sf::Event::JoystickMoved:
            return "JoystickMoved";
        case sf::Event::JoystickButtonPressed:
            return "JoystickButtonPressed";
        case sf::Event::JoystickButtonReleased:
            return "JoystickButtonReleased";
        case sf::Event::JoystickConnected:
            return "JoystickConnected";
        case sf::Event::JoystickDisconnected:
            return "JoystickDisconnected";
        default:
            return "";
    }
}

// Event#inspect
VALUE rbEvent::Inspect( VALUE aSelf )
{
    VALUE ret = rb_sprintf( "%s(%s",
							rb_obj_classname( aSelf ),
							EventTypeName( rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->type ) );
    VALUE info = rbEvent::Info( aSelf );
    if( info != Qnil )
    {
        rb_str_cat2( ret, ": " );
        VALUE ary = rb_obj_instance_variables( info );
        for( int index = 0; index < RARRAY_LEN( ary ); index++ )
        {
            VALUE iv = RARRAY_PTR( ary )[ index ];
            rb_str_cat2( ret, rb_id2name( SYM2ID( iv ) ) );
            rb_str_cat2( ret, "=" );
            rb_str_append( ret, rb_inspect( rb_ivar_get( info, rb_to_id( iv ) ) ) );
            if( index + 1 < RARRAY_LEN( ary ) )
                rb_str_cat2( ret, ", " );
        }
    }
    rb_str_cat2( ret, ")" );
    return ret;
}
