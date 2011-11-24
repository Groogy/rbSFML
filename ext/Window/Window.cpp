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

#define WINDOW_WINDOW_CPP
#include "Window.hpp"

void rbWindow::Init(VALUE SFML)
{
    Window = rb_define_class_under(SFML, "Window", rb_cObject);
    
    // Class methods
    rb_define_alloc_func(Window, Allocate);
    
    // Instance methods
    rb_define_method(Window, "initialize",     Initialize,         -1);
    rb_define_method(Window, "create",         Create,             -1);
    rb_define_method(Window, "close",          Close,               0);
    rb_define_method(Window, "opened?",        IsOpened,            0);
    rb_define_method(Window, "width",          GetWidth,            0);
    rb_define_method(Window, "height",         GetHeight,           0);
    rb_define_method(Window, "settings",       GetSettings,         0);
    rb_define_method(Window, "poll_event",     PollEvent,          -1);
    rb_define_method(Window, "wait_event",     WaitEvent,          -1);
    rb_define_method(Window, "each_event",     EachEvent,           0);
    rb_define_method(Window, "vertical_sync=", EnableVerticalSync,  1);
    rb_define_method(Window, "mouse_cursor=",  ShowMouseCursor,     1);
    rb_define_method(Window, "position",       SetPosition,         2);
    rb_define_method(Window, "position=",      SetPosition2,        1);
    rb_define_method(Window, "size",           SetSize,             2);
    rb_define_method(Window, "size=",          SetSize2,            1);
    rb_define_method(Window, "title=",         SetTitle,            1);
    rb_define_method(Window, "show=",          Show,                1);
    
    // Instance aliasses
    rb_define_alias(Window, "Create",             "create"        );
    rb_define_alias(Window, "Close",              "close"         );
    rb_define_alias(Window, "IsOpened",           "opened?"       );
    rb_define_alias(Window, "GetWidth",           "width"         );
    rb_define_alias(Window, "GetHeight",          "height"        );
    rb_define_alias(Window, "GetSettings",        "settings"      );
    rb_define_alias(Window, "PollEvent",          "poll_event"    );
    rb_define_alias(Window, "event",              "poll_event"    );
    rb_define_alias(Window, "WaitEvent",          "wait_event"    );
    rb_define_alias(Window, "EnableVerticalSync", "vertical_sync=");
    rb_define_alias(Window, "vertical_sync",      "vertical_sync=");
    rb_define_alias(Window, "ShowMouseCursor",    "mouse_cursor=" );
    rb_define_alias(Window, "mouse_cursor",       "mouse_cursor=" );
    rb_define_alias(Window, "SetPosition",        "position"      );
    rb_define_alias(Window, "SetSize",            "size"          );
    rb_define_alias(Window, "SetTitle",           "title="        );
    rb_define_alias(Window, "title",              "title="        );
    rb_define_alias(Window, "Show",               "show="         );
    rb_define_alias(Window, "show",               "show="         );
}

VALUE rbWindow::Initialize(int argc, VALUE argv[], VALUE self)
{
    if (argc > 0)
    {
        Create(argc, argv, self);
    }
}

VALUE rbWindow::Create(int argc, VALUE argv[], VALUE self)
{
    sf::Window* window = ToSFML(self);
    sf::WindowHandle handle = 0;
    sf::VideoMode mode;
    std::string title;
    sf::Uint32 style = 0;
    sf::ContextSettings settings;
    
    switch (argc)
    {
        case 1:
            VALIDATE_CLASS(argv[0], rb_cFixnum, FIXNUM_P(argv[0]));
            handle = sf::WindowHandle(FIX2INT(argv[0]));
            break;
        case 3:
            style = FIX2INT(argv[2]);
        case 2:
            if (FIXNUM_P(argv[0]))
            {
                settings = *(rbContextSettings::ToSFML(argv[1]));
            }
            else
            {
                mode = *(rbVideoMode::ToSFML(argv[0]));
                VALIDATE_CLASS(argv[1], rb_cString);
                title.assign(RSTRING_PTR(argv[1]), RSTRING_LEN(argv[1]));
            }
            break;
        case 4:
            settings = *(rbContextSettings::ToSFML(argv[3]));
            break;
    }
    
    switch (argc)
    {
        case 1:
            window->Create(handle);
            break;
        case 2:
            if (handle == 0)
                window->Create(mode, title);
            else
                window->Create(handle, settings);
            break;
        case 3:
            window->Create(mode, title, style);
            break;
        case 4:
            window->Create(mode, title, style, settings);
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 1..4)", argc);
    }
    
    rbSFML::RaiseError();
    return Qnil;
}

VALUE rbWindow::Close(VALUE self)
{
    ToSFML(self)->Close();
    return Qnil;
}

VALUE rbWindow::IsOpened(VALUE self)
{
    return ToSFML(self)->IsOpened() ? Qtrue : Qfalse;
}

VALUE rbWindow::GetWidth(VALUE self)
{
    return INT2FIX(ToSFML(self)->GetWidth());
}

VALUE rbWindow::GetHeight(VALUE self)
{
    return INT2FIX(ToSFML(self)->GetHeight());
}

VALUE rbWindow::GetSettings(VALUE self)
{
    VALUE settings = rbContextSettings::ToRuby(
        const_cast<sf::ContextSettings*>(&(ToSFML(self)->GetSettings())));
    rb_obj_freeze(settings);
    return settings;
}

static inline VALUE PollEvent(VALUE self, VALUE event)
{
    sf::Event ev;
    bool ret = rbWindow::ToSFML(self)->PollEvent(ev);
    if (ret)
    {
        *rbEvent::ToSFML(event) = ev;
        return Qtrue;
    }
    else
    {
        return Qfalse;
    }
}

VALUE rbWindow::PollEvent(int argc, VALUE argv[], VALUE self)
{
    switch (argc)
    {
        case 0:
        {
            VALUE event = rbEvent::Allocate(rbEvent::Event);
            VALUE test = ::PollEvent(self, event);
            return (test == Qtrue) ? event : Qnil;
        }
        case 1:
            return ::PollEvent(self, argv[0]);
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..1)", argc);
    }
}

static inline VALUE WaitEvent(VALUE self, VALUE event)
{
    sf::Event ev;
    bool ret = rbWindow::ToSFML(self)->WaitEvent(ev);
    if (ret)
    {
        *rbEvent::ToSFML(event) = ev;
        return Qtrue;
    }
    else
    {
        return Qfalse;
    }
}

VALUE rbWindow::WaitEvent(int argc, VALUE argv[], VALUE self)
{
    switch (argc)
    {
        case 0:
        {
            VALUE event = rbEvent::Allocate(rbEvent::Event);
            VALUE test = ::WaitEvent(self, event);
            return (test == Qtrue) ? event : Qnil;
        }
        case 1:
            return ::WaitEvent(self, argv[0]);
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..1)", argc);
    }
}

VALUE rbWindow::EachEvent(VALUE self)
{
    RETURN_ENUMERATOR(self, 0, NULL);
    sf::Event ev;
    while (ToSFML(self)->PollEvent(ev))
    {
        VALUE event = rbEvent::Allocate(rbEvent::Event);
        *rbEvent::ToSFML(event) = ev;
        rb_yield(event);
    }
    return Qnil;
}

VALUE rbWindow::EnableVerticalSync(VALUE self, VALUE enabled)
{
    ToSFML(self)->EnableVerticalSync(RTEST(enabled));
    return Qnil;
}

VALUE rbWindow::ShowMouseCursor(VALUE self, VALUE show)
{
    ToSFML(self)->ShowMouseCursor(RTEST(show));
    return Qnil;
}

VALUE rbWindow::SetPosition(VALUE self, VALUE x, VALUE y)
{
    VALIDATE_CLASS(x, rb_cFixnum, FIXNUM_P(x));
    VALIDATE_CLASS(y, rb_cFixnum, FIXNUM_P(y));
    
    ToSFML(self)->SetPosition(FIX2INT(x), FIX2INT(y));
    return Qnil;
}

VALUE rbWindow::SetPosition2(VALUE self, VALUE vector2)
{
    vector2 = rbVector2::ToRuby(vector2);
    VALUE x = rbVector2::GetX(vector2);
    VALUE y = rbVector2::GetY(vector2);
    
    switch (rbVector2::Type(vector2))
    {
        case T_FIXNUM:
            ToSFML(self)->SetPosition(FIX2INT(x), FIX2INT(y));
            break;
        case T_FLOAT:
            ToSFML(self)->SetPosition(NUM2DBL(x), NUM2DBL(y));
            break;
    }
    
    return Qnil;
}

VALUE rbWindow::SetSize(VALUE self, VALUE width, VALUE height)
{
    VALIDATE_CLASS(width,  rb_cFixnum, FIXNUM_P(width ));
    VALIDATE_CLASS(height, rb_cFixnum, FIXNUM_P(height));
    
    ToSFML(self)->SetSize(FIX2INT(width), FIX2INT(height));
    return Qnil;
}

VALUE rbWindow::SetSize2(VALUE self, VALUE vector2)
{
    vector2 = rbVector2::ToRuby(vector2);
    VALUE width  = rbVector2::GetX(vector2);
    VALUE height = rbVector2::GetY(vector2);
    
    switch (rbVector2::Type(vector2))
    {
        case T_FIXNUM:
            ToSFML(self)->SetSize(FIX2INT(width), FIX2INT(height));
            break;
        case T_FLOAT:
            ToSFML(self)->SetSize(NUM2DBL(width), NUM2DBL(height));
            break;
    }
    
    return Qnil;
}

VALUE rbWindow::SetTitle(VALUE self, VALUE title)
{
    VALIDATE_CLASS(title, rb_cString);
    
    ToSFML(self)->SetTitle(std::string(RSTRING_PTR(title), RSTRING_LEN(title)));
    return Qnil;
}

VALUE rbWindow::Show(VALUE self, VALUE show)
{
    ToSFML(self)->Show(RTEST(show));
    return Qnil;
}
