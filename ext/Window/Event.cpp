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

void rbEvent::Init(VALUE SFML)
{
    Event = rb_define_class_under(SFML, "Event", rb_cObject);
    
    // Subclasses
    Event_Size            = rb_define_class_under(Event, "Size",            rb_cObject);
    Event_Key             = rb_define_class_under(Event, "Key",             rb_cObject);
    Event_Text            = rb_define_class_under(Event, "Text",            rb_cObject);
    Event_MouseMove       = rb_define_class_under(Event, "MouseMove",       rb_cObject);
    Event_MouseButton     = rb_define_class_under(Event, "MouseButton",     rb_cObject);
    Event_MouseWheel      = rb_define_class_under(Event, "MouseWheel",      rb_cObject);
    Event_JoystickMove    = rb_define_class_under(Event, "JoystickMove",    rb_cObject);
    Event_JoystickButton  = rb_define_class_under(Event, "JoystickButton",  rb_cObject);
    Event_JoystickConnect = rb_define_class_under(Event, "JoystickConnect", rb_cObject);
    
    // Event::Size accessors
    rb_define_attr(Event_Size, "width",  true, false);
    rb_define_attr(Event_Size, "height", true, false);
    rb_define_alias(Event_Size, "Width",  "width");
    rb_define_alias(Event_Size, "Height", "height");
    
    // Event::Key accessors
    rb_define_attr(Event_Key, "code",    true, false);
    rb_define_attr(Event_Key, "alt",     true, false);
    rb_define_attr(Event_Key, "control", true, false);
    rb_define_attr(Event_Key, "shift",   true, false);
    rb_define_attr(Event_Key, "system",  true, false);
    rb_define_alias(Event_Key, "Code",    "code"  );
    rb_define_alias(Event_Key, "Alt",     "alt"   );
    rb_define_alias(Event_Key, "Control", "control");
    rb_define_alias(Event_Key, "Shift",   "shift" );
    rb_define_alias(Event_Key, "System",  "system");
    
    // Event::Text accessors
    rb_define_attr(Event_Text, "unicode", true, false);
    rb_define_alias(Event_Text, "Unicode",  "unicode");
    
    // Event::MouseMove accessors
    rb_define_attr(Event_MouseMove, "x", true, false);
    rb_define_attr(Event_MouseMove, "y", true, false);
    rb_define_alias(Event_MouseMove, "X", "x");
    rb_define_alias(Event_MouseMove, "Y", "y");
    
    // Event::MouseButton accessors
    rb_define_attr(Event_MouseButton, "button", true, false);
    rb_define_attr(Event_MouseButton, "x",      true, false);
    rb_define_attr(Event_MouseButton, "y",      true, false);
    rb_define_alias(Event_MouseButton, "Button", "button");
    rb_define_alias(Event_MouseButton, "X",      "x"    );
    rb_define_alias(Event_MouseButton, "Y",      "y"    );
    
    // Event::MouseWheel accessors
    rb_define_attr(Event_MouseWheel, "delta", true, false);
    rb_define_attr(Event_MouseWheel, "x",     true, false);
    rb_define_attr(Event_MouseWheel, "y",     true, false);
    rb_define_alias(Event_MouseWheel, "Delta", "delta");
    rb_define_alias(Event_MouseWheel, "X",     "x"   );
    rb_define_alias(Event_MouseWheel, "Y",     "y"   );
    
    // Event::JoystickConnect accessors
    rb_define_attr(Event_JoystickConnect, "id", true, false);
    rb_define_alias(Event_JoystickConnect, "JoystickId", "id");
    
    // Event::JoystickMove accessors
    rb_define_attr(Event_JoystickMove, "id",       true, false);
    rb_define_attr(Event_JoystickMove, "axis",     true, false);
    rb_define_attr(Event_JoystickMove, "position", true, false);
    rb_define_alias(Event_JoystickMove, "JoystickId", "id"     );
    rb_define_alias(Event_JoystickMove, "Axis",       "axis"   );
    rb_define_alias(Event_JoystickMove, "Position",   "position");
    
    // Event::JoystickButton accessors
    rb_define_attr(Event_JoystickButton, "id",     true, false);
    rb_define_attr(Event_JoystickButton, "button", true, false);
    rb_define_alias(Event_JoystickButton, "JoystickId", "id"   );
    rb_define_alias(Event_JoystickButton, "Button",     "button");
    
    // Constants
    rb_define_const(Event, "Closed",                 INT2FIX(sf::Event::Closed                ));
    rb_define_const(Event, "Resized",                INT2FIX(sf::Event::Resized               ));
    rb_define_const(Event, "LostFocus",              INT2FIX(sf::Event::LostFocus             ));
    rb_define_const(Event, "GainedFocus",            INT2FIX(sf::Event::GainedFocus           ));
    rb_define_const(Event, "TextEntered",            INT2FIX(sf::Event::TextEntered           ));
    rb_define_const(Event, "KeyPressed",             INT2FIX(sf::Event::KeyPressed            ));
    rb_define_const(Event, "KeyReleased",            INT2FIX(sf::Event::KeyReleased           ));
    rb_define_const(Event, "MouseWheelMoved",        INT2FIX(sf::Event::MouseWheelMoved       ));
    rb_define_const(Event, "MouseButtonPressed",     INT2FIX(sf::Event::MouseButtonPressed    ));
    rb_define_const(Event, "MouseButtonReleased",    INT2FIX(sf::Event::MouseButtonReleased   ));
    rb_define_const(Event, "MouseMoved",             INT2FIX(sf::Event::MouseMoved            ));
    rb_define_const(Event, "MouseEntered",           INT2FIX(sf::Event::MouseEntered          ));
    rb_define_const(Event, "MouseLeft",              INT2FIX(sf::Event::MouseLeft             ));
    rb_define_const(Event, "JoystickButtonPressed",  INT2FIX(sf::Event::JoystickButtonPressed ));
    rb_define_const(Event, "JoystickButtonReleased", INT2FIX(sf::Event::JoystickButtonReleased));
    rb_define_const(Event, "JoystickMoved",          INT2FIX(sf::Event::JoystickMoved         ));
    rb_define_const(Event, "JoystickConnected",      INT2FIX(sf::Event::JoystickConnected     ));
    rb_define_const(Event, "JoystickDisconnected",   INT2FIX(sf::Event::JoystickDisconnected  ));
    
    // Class methods
    rb_define_alloc_func(Event, Allocate);
    
    // Instance methods
    rb_define_method(Event, "type",             Type,            0);
    rb_define_method(Event, "info",             Info,            0);
    rb_define_method(Event, "===",              CaseEqual,       1);
    rb_define_method(Event, "size",             Size,            0);
    rb_define_method(Event, "key",              Key,             0);
    rb_define_method(Event, "text",             Text,            0);
    rb_define_method(Event, "mouse_move",       MouseMove,       0);
    rb_define_method(Event, "mouse_button",     MouseButton,     0);
    rb_define_method(Event, "mouse_wheel",      MouseWheel,      0);
    rb_define_method(Event, "joystick_move",    JoystickMove,    0);
    rb_define_method(Event, "joystick_button",  JoystickButton,  0);
    rb_define_method(Event, "joystick_connect", JoystickConnect, 0);
    
    // Instance aliasses
    rb_define_alias(Event, "Type",            "type"            );
    rb_define_alias(Event, "Size",            "size"            );
    rb_define_alias(Event, "Key",             "key"             );
    rb_define_alias(Event, "Text",            "text"            );
    rb_define_alias(Event, "MouseMove",       "mouse_move"      );
    rb_define_alias(Event, "MouseButton",     "mouse_button"    );
    rb_define_alias(Event, "MouseWheel",      "mouse_wheel"     );
    rb_define_alias(Event, "JoystickMove",    "joystick_move"   );
    rb_define_alias(Event, "JoystickButton",  "joystick_button" );
    rb_define_alias(Event, "JoystickConnect", "joystick_connect");
}

VALUE rbEvent::Type(VALUE self)
{
    return INT2FIX(ToSFML(self)->Type);
}

VALUE rbEvent::Info(VALUE self)
{
    switch (ToSFML(self)->Type)
    {
        case sf::Event::Closed:
        case sf::Event::LostFocus:
        case sf::Event::GainedFocus:
        case sf::Event::MouseEntered:
        case sf::Event::MouseLeft:
            return Qnil;
        case sf::Event::Resized:
            return Size(self);
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
            return Key(self);
        case sf::Event::TextEntered:
            return Text(self);
        case sf::Event::MouseMoved:
            return MouseMove(self);
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
            return MouseButton(self);
        case sf::Event::MouseWheelMoved:
            return MouseWheel(self);
        case sf::Event::JoystickMoved:
            return JoystickMove(self);
        case sf::Event::JoystickButtonPressed:
        case sf::Event::JoystickButtonReleased:
            return JoystickButton(self);
        case sf::Event::JoystickConnected:
        case sf::Event::JoystickDisconnected:
            return JoystickConnect(self);
    }
}

VALUE rbEvent::CaseEqual(VALUE self, VALUE other)
{
    return rb_obj_is_kind_of(Info(self), other);
}

VALUE rbEvent::Size(VALUE self)
{
    sf::Event::SizeEvent size_ev = ToSFML(self)->Size;
    VALUE size = rb_obj_alloc(Event_Size);
    
    rb_iv_set(size, "@width",  INT2FIX(size_ev.Width ));
    rb_iv_set(size, "@height", INT2FIX(size_ev.Height));
    
    return size;
}

VALUE rbEvent::Key(VALUE self)
{
    sf::Event::KeyEvent key_ev = ToSFML(self)->Key;
    VALUE key = rb_obj_alloc(Event_Key);
    
    rb_iv_set(key, "@code",    INT2FIX(key_ev.Code   ));
    rb_iv_set(key, "@alt",     INT2FIX(key_ev.Alt    ));
    rb_iv_set(key, "@control", INT2FIX(key_ev.Control));
    rb_iv_set(key, "@shift",   INT2FIX(key_ev.Shift  ));
    rb_iv_set(key, "@system",  INT2FIX(key_ev.System ));
    
    return key;
}

VALUE rbEvent::Text(VALUE self)
{
    sf::Event::TextEvent text_ev = ToSFML(self)->Text;
    VALUE text = rb_obj_alloc(Event_Text);
    
    rb_iv_set(text, "@unicode", INT2NUM(text_ev.Unicode));
    
    return text;
}

VALUE rbEvent::MouseMove(VALUE self)
{
    sf::Event::MouseMoveEvent mouse_move_ev = ToSFML(self)->MouseMove;
    VALUE mouse_move = rb_obj_alloc(Event_MouseMove);
    
    rb_iv_set(mouse_move, "@x", INT2FIX(mouse_move_ev.X));
    rb_iv_set(mouse_move, "@y", INT2FIX(mouse_move_ev.Y));
    
    return mouse_move;
}

VALUE rbEvent::MouseButton(VALUE self)
{
    sf::Event::MouseButtonEvent mouse_button_ev = ToSFML(self)->MouseButton;
    VALUE mouse_button = rb_obj_alloc(Event_MouseButton);
    
    rb_iv_set(mouse_button, "@button", INT2FIX(mouse_button_ev.Button));
    rb_iv_set(mouse_button, "@x",      INT2FIX(mouse_button_ev.X     ));
    rb_iv_set(mouse_button, "@y",      INT2FIX(mouse_button_ev.Y     ));
    
    return mouse_button;
}

VALUE rbEvent::MouseWheel(VALUE self)
{
    sf::Event::MouseWheelEvent mouse_wheel_ev = ToSFML(self)->MouseWheel;
    VALUE mouse_wheel = rb_obj_alloc(Event_MouseWheel);
    
    rb_iv_set(mouse_wheel, "@delta", INT2FIX(mouse_wheel_ev.Delta));
    rb_iv_set(mouse_wheel, "@x",     INT2FIX(mouse_wheel_ev.X    ));
    rb_iv_set(mouse_wheel, "@y",     INT2FIX(mouse_wheel_ev.Y    ));
    
    return mouse_wheel;
}

VALUE rbEvent::JoystickMove(VALUE self)
{
    sf::Event::JoystickMoveEvent joystick_move_ev = ToSFML(self)->JoystickMove;
    VALUE joystick_move = rb_obj_alloc(Event_JoystickMove);
    
    rb_iv_set(joystick_move, "@id",       INT2FIX(joystick_move_ev.JoystickId));
    rb_iv_set(joystick_move, "@axis",     INT2FIX(joystick_move_ev.Axis      ));
    rb_iv_set(joystick_move, "@position", rb_float_new(joystick_move_ev.Position));
    
    return joystick_move;
}

VALUE rbEvent::JoystickButton(VALUE self)
{
    sf::Event::JoystickButtonEvent joystick_button_ev = ToSFML(self)->JoystickButton;
    VALUE joystick_button = rb_obj_alloc(Event_JoystickButton);
    
    rb_iv_set(joystick_button, "@id",     INT2FIX(joystick_button_ev.JoystickId));
    rb_iv_set(joystick_button, "@button", INT2FIX(joystick_button_ev.Button    ));
    
    return joystick_button;
}

VALUE rbEvent::JoystickConnect(VALUE self)
{
    sf::Event::JoystickConnectEvent joystick_connect_ev = ToSFML(self)->JoystickConnect;
    VALUE joystick_connect = rb_obj_alloc(Event_JoystickConnect);
    
    rb_iv_set(joystick_connect, "@id", INT2FIX(joystick_connect_ev.JoystickId));
    
    return joystick_connect;
}
