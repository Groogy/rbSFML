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
    rbEvent::Class_Type            = rb_define_class_under( rbEvent::Class, "Type",            rb_cObject );
    rbEvent::Class_Key             = rb_define_class_under( rbEvent::Class, "Key",             rb_cObject );
    rbEvent::Class_Text            = rb_define_class_under( rbEvent::Class, "Text",            rb_cObject );
    rbEvent::Class_MouseMove       = rb_define_class_under( rbEvent::Class, "MouseMove",       rb_cObject );
    rbEvent::Class_MouseButton     = rb_define_class_under( rbEvent::Class, "MouseButton",     rb_cObject );
    rbEvent::Class_MouseWheel      = rb_define_class_under( rbEvent::Class, "MouseWheel",      rb_cObject );
    rbEvent::Class_JoystickMove    = rb_define_class_under( rbEvent::Class, "JoystickMove",    rb_cObject );
    rbEvent::Class_JoystickButton  = rb_define_class_under( rbEvent::Class, "JoystickButton",  rb_cObject );
    rbEvent::Class_JoystickConnect = rb_define_class_under( rbEvent::Class, "JoystickConnect", rb_cObject );
    rb_define_method( rbEvent::Class_Type, "===", rbEvent::EventTypeCaseEqual, 1 );
	
	rb_define_alias( rbEvent::Class_Type, "==", "===" );
    
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
    rb_define_alias( rbEvent::Class_Key, "Code",    "code"   );
    rb_define_alias( rbEvent::Class_Key, "Alt",     "alt"    );
    rb_define_alias( rbEvent::Class_Key, "Control", "control" );
    rb_define_alias( rbEvent::Class_Key, "Shift",   "shift" );
    rb_define_alias( rbEvent::Class_Key, "System",  "system" );
    
    // Event::Text accessors
    rb_define_attr( rbEvent::Class_Text, "unicode", true, false );
    rb_define_alias( rbEvent::Class_Text, "Unicode",  "unicode" );
    
    // Event::MouseMove accessors
    rb_define_attr(rbEvent::Class_MouseMove, "x", true, false );
    rb_define_attr(rbEvent::Class_MouseMove, "y", true, false );
    rb_define_alias(rbEvent::Class_MouseMove, "X", "x" );
    rb_define_alias(rbEvent::Class_MouseMove, "Y", "y" );
    
    // Event::MouseButton accessors
    rb_define_attr(rbEvent::Class_MouseButton, "button", true, false );
    rb_define_attr(rbEvent::Class_MouseButton, "x",      true, false );
    rb_define_attr(rbEvent::Class_MouseButton, "y",      true, false );
    rb_define_alias(rbEvent::Class_MouseButton, "Button", "button" );
    rb_define_alias(rbEvent::Class_MouseButton, "X",      "x"     );
    rb_define_alias(rbEvent::Class_MouseButton, "Y",      "y"     );
    
    // Event::MouseWheel accessors
    rb_define_attr( rbEvent::Class_MouseWheel, "delta", true, false );
    rb_define_attr( rbEvent::Class_MouseWheel, "x",     true, false );
    rb_define_attr( rbEvent::Class_MouseWheel, "y",     true, false );
    rb_define_alias( rbEvent::Class_MouseWheel, "Delta", "delta" );
    rb_define_alias( rbEvent::Class_MouseWheel, "X",     "x"    );
    rb_define_alias( rbEvent::Class_MouseWheel, "Y",     "y"    );
    
    // Event::JoystickConnect accessors
    rb_define_attr( rbEvent::Class_JoystickConnect, "id", true, false );
    rb_define_alias( rbEvent::Class_JoystickConnect, "JoystickId", "id" );
    
    // Event::JoystickMove accessors
    rb_define_attr( rbEvent::Class_JoystickMove, "id",       true, false );
    rb_define_attr( rbEvent::Class_JoystickMove, "axis",     true, false );
    rb_define_attr( rbEvent::Class_JoystickMove, "position", true, false );
    rb_define_alias( rbEvent::Class_JoystickMove, "JoystickId", "id"      );
    rb_define_alias( rbEvent::Class_JoystickMove, "Axis",       "axis"    );
    rb_define_alias( rbEvent::Class_JoystickMove, "Position",   "position" );
    
    // Event::JoystickButton accessors
    rb_define_attr( rbEvent::Class_JoystickButton, "id",     true, false );
    rb_define_attr( rbEvent::Class_JoystickButton, "button", true, false );
    rb_define_alias( rbEvent::Class_JoystickButton, "JoystickId", "id"    );
    rb_define_alias( rbEvent::Class_JoystickButton, "Button",     "button" );
    
    // Constants
    rb_define_const( rbEvent::Class, "Closed",                 EventType( sf::Event::Closed                 ) );
    rb_define_const( rbEvent::Class, "Resized",                EventType( sf::Event::Resized                ) );
    rb_define_const( rbEvent::Class, "LostFocus",              EventType( sf::Event::LostFocus              ) );
    rb_define_const( rbEvent::Class, "GainedFocus",            EventType( sf::Event::GainedFocus            ) );
    rb_define_const( rbEvent::Class, "TextEntered",            EventType( sf::Event::TextEntered            ) );
    rb_define_const( rbEvent::Class, "KeyPressed",             EventType( sf::Event::KeyPressed             ) );
    rb_define_const( rbEvent::Class, "KeyReleased",            EventType( sf::Event::KeyReleased            ) );
    rb_define_const( rbEvent::Class, "MouseWheelMoved",        EventType( sf::Event::MouseWheelMoved        ) );
    rb_define_const( rbEvent::Class, "MouseButtonPressed",     EventType( sf::Event::MouseButtonPressed     ) );
    rb_define_const( rbEvent::Class, "MouseButtonReleased",    EventType( sf::Event::MouseButtonReleased    ) );
    rb_define_const( rbEvent::Class, "MouseMoved",             EventType( sf::Event::MouseMoved             ) );
    rb_define_const( rbEvent::Class, "MouseEntered",           EventType( sf::Event::MouseEntered           ) );
    rb_define_const( rbEvent::Class, "MouseLeft",              EventType( sf::Event::MouseLeft              ) );
    rb_define_const( rbEvent::Class, "JoystickButtonPressed",  EventType( sf::Event::JoystickButtonPressed  ) );
    rb_define_const( rbEvent::Class, "JoystickButtonReleased", EventType( sf::Event::JoystickButtonReleased ) );
    rb_define_const( rbEvent::Class, "JoystickMoved",          EventType( sf::Event::JoystickMoved          ) );
    rb_define_const( rbEvent::Class, "JoystickConnected",      EventType( sf::Event::JoystickConnected      ) );
    rb_define_const( rbEvent::Class, "JoystickDisconnected",   EventType( sf::Event::JoystickDisconnected   ) );
    
    // Class methods
    rb_define_alloc_func( rbEvent::Class, rbMacros::Allocate< sf::Event > );
    
    // Instance methods
    rb_define_method( rbEvent::Class, "initialize_copy",  rbEvent::InitializeCopy,  1 );
    rb_define_method( rbEvent::Class, "marshal_dump",     rbEvent::MarshalDump,     0 );
    rb_define_method( rbEvent::Class, "type",             rbEvent::Type,            0 );
    rb_define_method( rbEvent::Class, "info",             rbEvent::Info,            0 );
    rb_define_method( rbEvent::Class, "size",             rbEvent::Size,            0 );
    rb_define_method( rbEvent::Class, "key",              rbEvent::Key,             0 );
    rb_define_method( rbEvent::Class, "text",             rbEvent::Text,            0 );
    rb_define_method( rbEvent::Class, "mouse_move",       rbEvent::MouseMove,       0 );
    rb_define_method( rbEvent::Class, "mouse_button",     rbEvent::MouseButton,     0 );
    rb_define_method( rbEvent::Class, "mouse_wheel",      rbEvent::MouseWheel,      0 );
    rb_define_method( rbEvent::Class, "joystick_move",    rbEvent::JoystickMove,    0 );
    rb_define_method( rbEvent::Class, "joystick_button",  rbEvent::JoystickButton,  0 );
    rb_define_method( rbEvent::Class, "joystick_connect", rbEvent::JoystickConnect, 0 );
    rb_define_method( rbEvent::Class, "==",               rbEvent::Equal,           1 );
    rb_define_method( rbEvent::Class, "inspect",          rbEvent::Inspect,         0 );
    rb_define_method( rbEvent::Class, "memory_usage",     rbEvent::GetMemoryUsage,  0 );
    
    // Instance aliasses
    rb_define_alias( rbEvent::Class, "Type",            "type"             );
    rb_define_alias( rbEvent::Class, "Size",            "size"             );
    rb_define_alias( rbEvent::Class, "Key",             "key"              );
    rb_define_alias( rbEvent::Class, "Text",            "text"             );
    rb_define_alias( rbEvent::Class, "MouseMove",       "mouse_move"       );
    rb_define_alias( rbEvent::Class, "MouseButton",     "mouse_button"     );
    rb_define_alias( rbEvent::Class, "MouseWheel",      "mouse_wheel"      );
    rb_define_alias( rbEvent::Class, "JoystickMove",    "joystick_move"    );
    rb_define_alias( rbEvent::Class, "JoystickButton",  "joystick_button"  );
    rb_define_alias( rbEvent::Class, "JoystickConnect", "joystick_connect" );
    rb_define_alias( rbEvent::Class, "eql?",            "=="               );
    rb_define_alias( rbEvent::Class, "equal?",          "=="               );
    rb_define_alias( rbEvent::Class, "to_s",            "inspect"          );
}

// Internal
VALUE rbEvent::EventType( int anID )
{
    VALUE type = rb_obj_alloc( rbEvent::Class_Type );
    rb_iv_set( type, "@id", INT2FIX( anID ) );
    return type;
}

#include <iostream>

// Internal
VALUE rbEvent::EventTypeCaseEqual( VALUE aSelf, VALUE anOther )
{
	if( rb_obj_is_kind_of( anOther, rbEvent::Class_Type ) )
	{
		VALUE id1 = rb_iv_get( aSelf, "@id" );
		VALUE id2 = rb_iv_get( anOther, "@id" );
		return RBOOL( id1 == id2 );
	}
	else
	{
		return Qfalse;
	}
}

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
// Event#Type
VALUE rbEvent::Type( VALUE aSelf )
{
    return EventType( rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->Type );
}

// Event#info
VALUE rbEvent::Info( VALUE aSelf )
{
    switch( rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->Type )
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
// Event#Size
VALUE rbEvent::Size( VALUE aSelf )
{
    sf::Event::SizeEvent sizeEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->Size;
    VALUE size = rb_obj_alloc( rbEvent::Class_Size );
    
    rb_iv_set( size, "@width",  INT2FIX( sizeEvent.Width  ) );
    rb_iv_set( size, "@height", INT2FIX( sizeEvent.Height ) );
    
    return size;
}

// Event#key
// Event#Key
VALUE rbEvent::Key( VALUE aSelf )
{
    sf::Event::KeyEvent keyEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->Key;
    VALUE key = rb_obj_alloc( rbEvent::Class_Key );
    
    rb_iv_set( key, "@code",    INT2FIX( keyEvent.Code ) );
    rb_iv_set( key, "@alt",     RBOOL( keyEvent.Alt     ) );
    rb_iv_set( key, "@control", RBOOL( keyEvent.Control ) );
    rb_iv_set( key, "@shift",   RBOOL( keyEvent.Shift   ) );
    rb_iv_set( key, "@system",  RBOOL( keyEvent.System  ) );
    
    return key;
}

// Event#text
// Event#Text
VALUE rbEvent::Text( VALUE aSelf )
{
    sf::Event::TextEvent textEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->Text;
    VALUE text = rb_obj_alloc( rbEvent::Class_Text);
    
    rb_iv_set( text, "@unicode", UINT2NUM( textEvent.Unicode ) );
    
    return text;
}

// Event#mouse_move
// Event#MouseMove
VALUE rbEvent::MouseMove( VALUE aSelf )
{
    sf::Event::MouseMoveEvent mouseMoveEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->MouseMove;
    VALUE mouseMove = rb_obj_alloc( rbEvent::Class_MouseMove);
    
    rb_iv_set( mouseMove, "@x", INT2FIX( mouseMoveEvent.X ) );
    rb_iv_set( mouseMove, "@y", INT2FIX( mouseMoveEvent.Y ) );
    
    return mouseMove;
}

// Event#mouse_button
// Event#MouseButton
VALUE rbEvent::MouseButton( VALUE aSelf )
{
    sf::Event::MouseButtonEvent mouseButtonEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->MouseButton;
    VALUE mouseButton = rb_obj_alloc( rbEvent::Class_MouseButton );
    
    rb_iv_set( mouseButton, "@button", INT2FIX(mouseButtonEvent.Button ) );
    rb_iv_set( mouseButton, "@x",      INT2FIX(mouseButtonEvent.X      ) );
    rb_iv_set( mouseButton, "@y",      INT2FIX(mouseButtonEvent.Y      ) );
    
    return mouseButton;
}

// Event#mouse_wheel
// Event#MouseWheel
VALUE rbEvent::MouseWheel( VALUE aSelf )
{
    sf::Event::MouseWheelEvent mouseWheelEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->MouseWheel;
    VALUE mouseWheel = rb_obj_alloc( rbEvent::Class_MouseWheel );
    
    rb_iv_set( mouseWheel, "@delta", INT2FIX( mouseWheelEvent.Delta ) );
    rb_iv_set( mouseWheel, "@x",     INT2FIX( mouseWheelEvent.X     ) );
    rb_iv_set( mouseWheel, "@y",     INT2FIX( mouseWheelEvent.Y     ) );
    
    return mouseWheel;
}

// Event#joystick_move
// Event#JoystickMove
VALUE rbEvent::JoystickMove( VALUE aSelf )
{
    sf::Event::JoystickMoveEvent joystickMoveEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->JoystickMove;
    VALUE joystickMove = rb_obj_alloc( rbEvent::Class_JoystickMove );
    
    rb_iv_set( joystickMove, "@id",       INT2FIX( joystickMoveEvent.JoystickId ) );
    rb_iv_set( joystickMove, "@axis",     INT2FIX( joystickMoveEvent.Axis       ) );
    rb_iv_set( joystickMove, "@position", rb_float_new( joystickMoveEvent.Position ) );
    
    return joystickMove;
}

// Event#joystick_button
// Event#JoystickButton
VALUE rbEvent::JoystickButton( VALUE aSelf )
{
    sf::Event::JoystickButtonEvent joystickButtonEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->JoystickButton;
    VALUE joystickButton = rb_obj_alloc( rbEvent::Class_JoystickButton);
    
    rb_iv_set( joystickButton, "@id",     INT2FIX( joystickButtonEvent.JoystickId ) );
    rb_iv_set( joystickButton, "@button", INT2FIX( joystickButtonEvent.Button     ) );
    
    return joystickButton;
}

// Event#joystick_connect
// Event#JoystickConnect
VALUE rbEvent::JoystickConnect( VALUE aSelf )
{
    sf::Event::JoystickConnectEvent joystickConnectEvent = rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->JoystickConnect;
    VALUE joystickConnect = rb_obj_alloc( rbEvent::Class_JoystickConnect);
    
    rb_iv_set( joystickConnect, "@id", INT2FIX( joystickConnectEvent.JoystickId ) );
    
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
							EventTypeName( rbMacros::ToSFML< sf::Event >( aSelf, rbEvent::Class )->Type ) );
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

// Event#memory_usage
VALUE rbEvent::GetMemoryUsage( VALUE aSelf )
{
    return SIZET2NUM( sizeof( sf::Event ) );
}
