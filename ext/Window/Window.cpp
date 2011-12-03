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
    rb_define_method(Window, "initialize",          Initialize,           -1);
    rb_define_method(Window, "marshal_dump",        MarshalDump,           0);
    rb_define_method(Window, "clone",               Clone,                 0);
    rb_define_method(Window, "dup",                 Dup,                   0);
    rb_define_method(Window, "create",              Create,               -1);
    rb_define_method(Window, "close",               Close,                 0);
    rb_define_method(Window, "opened?",             IsOpened,              0);
    rb_define_method(Window, "width",               GetWidth,              0);
    rb_define_method(Window, "height",              GetHeight,             0);
    rb_define_method(Window, "settings",            GetSettings,           0);
    rb_define_method(Window, "poll_event",          PollEvent,            -1);
    rb_define_method(Window, "wait_event",          WaitEvent,            -1);
    rb_define_method(Window, "each_event",          EachEvent,             0);
    rb_define_method(Window, "vertical_sync=",      EnableVerticalSync,    1);
    rb_define_method(Window, "mouse_cursor=",       ShowMouseCursor,       1);
    rb_define_method(Window, "position",            SetPosition,           2);
    rb_define_method(Window, "position=",           SetPosition2,          1);
    rb_define_method(Window, "size",                SetSize,               2);
    rb_define_method(Window, "size=",               SetSize2,              1);
    rb_define_method(Window, "title=",              SetTitle,              1);
    rb_define_method(Window, "show=",               Show,                  1);
    rb_define_method(Window, "key_repeat=",         EnableKeyRepeat,       1);
    rb_define_method(Window, "icon",                SetIcon,               3);
    rb_define_method(Window, "active",              SetActive,            -1);
    rb_define_method(Window, "display",             Display,               0);
    rb_define_method(Window, "framerate=",          SetFramerateLimit,     1);
    rb_define_method(Window, "frame_time",          GetFrameTime,          0);
    rb_define_method(Window, "joystick_threshold=", SetJoystickThreshold,  1);
    rb_define_method(Window, "system_handle",       GetSystemHandle,       0);
    rb_define_method(Window, "inspect",             Inspect,               0);
    rb_define_method(Window, "memory_usage",        GetMemoryUsage,        0);
    
    // Instance aliasses
    rb_define_alias(Window, "Create",               "create"             );
    rb_define_alias(Window, "Close",                "close"              );
    rb_define_alias(Window, "IsOpened",             "opened?"            );
    rb_define_alias(Window, "open?",                "opened?"            );
    rb_define_alias(Window, "GetWidth",             "width"              );
    rb_define_alias(Window, "GetHeight",            "height"             );
    rb_define_alias(Window, "GetSettings",          "settings"           );
    rb_define_alias(Window, "PollEvent",            "poll_event"         );
    rb_define_alias(Window, "event",                "poll_event"         );
    rb_define_alias(Window, "WaitEvent",            "wait_event"         );
    rb_define_alias(Window, "EnableVerticalSync",   "vertical_sync="     );
    rb_define_alias(Window, "vertical_sync",        "vertical_sync="     );
    rb_define_alias(Window, "ShowMouseCursor",      "mouse_cursor="      );
    rb_define_alias(Window, "mouse_cursor",         "mouse_cursor="      );
    rb_define_alias(Window, "SetPosition",          "position"           );
    rb_define_alias(Window, "SetSize",              "size"               );
    rb_define_alias(Window, "SetTitle",             "title="             );
    rb_define_alias(Window, "title",                "title="             );
    rb_define_alias(Window, "Show",                 "show="              );
    rb_define_alias(Window, "show",                 "show="              );
    rb_define_alias(Window, "EnableKeyRepeat",      "key_repeat="        );
    rb_define_alias(Window, "key_repeat",           "key_repeat="        );
    rb_define_alias(Window, "SetIcon",              "icon"               );
    rb_define_alias(Window, "SetActive",            "active"             );
    rb_define_alias(Window, "active=",              "active"             );
    rb_define_alias(Window, "Display",              "display"            );
    rb_define_alias(Window, "SetFramerateLimit",    "framerate="         );
    rb_define_alias(Window, "framerate",            "framerate="         );
    rb_define_alias(Window, "framerate_limit=",     "framerate="         );
    rb_define_alias(Window, "framerate_limit",      "framerate="         );
    rb_define_alias(Window, "fps=",                 "framerate="         );
    rb_define_alias(Window, "GetFrameTime",         "frame_time"         );
    rb_define_alias(Window, "time",                 "frame_time"         );
    rb_define_alias(Window, "SetJoystickThreshold", "joystick_threshold=");
    rb_define_alias(Window, "joystick_threshold",   "joystick_threshold=");
    rb_define_alias(Window, "GetSystemHandle",      "system_handle"      );
    rb_define_alias(Window, "handle",               "system_handle"      );
    rb_define_alias(Window, "to_s",                 "inspect"            );
}

// Window#initialize(...)
VALUE rbWindow::Initialize(int argc, VALUE argv[], VALUE self)
{
    if (argc > 0)
        Create(argc, argv, self);
    
    return Qnil;
}

// Window#marshal_dump
VALUE rbWindow::MarshalDump(VALUE self)
{
    rb_raise(rb_eTypeError, "can't dump Window");
    return Qnil;
}

// Window#clone
VALUE rbWindow::Clone(VALUE self)
{
    rb_raise(rb_eTypeError, "can't clone instance of Window");
    return Qnil;
}

// Window#dup
VALUE rbWindow::Dup(VALUE self)
{
    rb_raise(rb_eTypeError, "can't dup instance of Window");
    return Qnil;
}

// Window#create(...)
// Window#Create(...)
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
            handle = sf::WindowHandle(NUM2UINT(argv[0]));
            break;
        case 2:
            if (FIXNUM_P(argv[0]))
            {
                settings = *rbContextSettings::ToSFML(argv[1]);
            }
            else
            {
                mode = *rbVideoMode::ToSFML(argv[0]);
                rb_iv_set(self, "@title", StringValue(argv[1]));
                title = StringValueCStr(argv[1]);
            }
            break;
        case 4:
            settings = *rbContextSettings::ToSFML(argv[3]);
        case 3:
            mode = *rbVideoMode::ToSFML(argv[0]);
            rb_iv_set(self, "@title", StringValue(argv[1]));
            title = StringValueCStr(argv[1]);
            style = NUM2INT(argv[2]);
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 1..4)", argc);
    }
    
    rbSFML::PrepareErrorStream();
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
    }
    rbSFML::CheckWarn();
    
    return Qnil;
}

// Window#close
// Window#Close
VALUE rbWindow::Close(VALUE self)
{
    rb_iv_set(self, "@title", Qnil);
    ToSFML(self)->Close();
    return Qnil;
}

// Window#opened?
// Window#IsOpened
// Window#open?
VALUE rbWindow::IsOpened(VALUE self)
{
    return RBOOL(ToSFML(self)->IsOpened());
}

// Window#width
// Window#GetWidth
VALUE rbWindow::GetWidth(VALUE self)
{
    return INT2FIX(ToSFML(self)->GetWidth());
}

// Window#height
// Window#GetHeight
VALUE rbWindow::GetHeight(VALUE self)
{
    return INT2FIX(ToSFML(self)->GetHeight());
}

// Window#settings
// Window#GetSettings
VALUE rbWindow::GetSettings(VALUE self)
{
    VALUE settings = rbContextSettings::Allocate(0);
    *rbContextSettings::ToSFML(settings) = ToSFML(self)->GetSettings();
    rb_obj_freeze(settings);
    return settings;
}

// Internal
static inline bool PollEvent(VALUE self, VALUE event)
{
    sf::Event ev;
    bool ret = rbWindow::ToSFML(self)->PollEvent(ev);
    if (ret)
    {
        *rbEvent::ToSFML(event) = ev;
        return true;
    }
    else
    {
        return false;
    }
}

// Window#poll_event
// Window#PollEvent
// Window#poll_event(event)
// Window#PollEvent(event)
VALUE rbWindow::PollEvent(int argc, VALUE argv[], VALUE self)
{
    switch (argc)
    {
        case 0:
        {
            VALUE event = rbEvent::Allocate(rbEvent::Event);
            return (::PollEvent(self, event)) ? event : Qnil;
        }
        case 1:
            return RBOOL(::PollEvent(self, argv[0]));
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..1)", argc);
    }
}

// Internal
static inline bool WaitEvent(VALUE self, VALUE event)
{
    sf::Event ev;
    bool ret = rbWindow::ToSFML(self)->WaitEvent(ev);
    if (ret)
    {
        *rbEvent::ToSFML(event) = ev;
        return true;
    }
    else
    {
        return false;
    }
}

// Window#wait_event
// Window#WaitEvent
// Window#wait_event(event)
// Window#WaitEvent(event)
VALUE rbWindow::WaitEvent(int argc, VALUE argv[], VALUE self)
{
    switch (argc)
    {
        case 0:
        {
            VALUE event = rbEvent::Allocate(rbEvent::Event);
            return (::WaitEvent(self, event)) ? event : Qnil;
        }
        case 1:
            return RBOOL(::WaitEvent(self, argv[0]));
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..1)", argc);
    }
}

// Window#each_event
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
    return self;
}

// Window#vertical_sync=(enabled)
// Window#EnableVerticalSync(enabled)
// Window#vertical_sync(enabled)
VALUE rbWindow::EnableVerticalSync(VALUE self, VALUE enabled)
{
    rb_check_frozen(self);
    ToSFML(self)->EnableVerticalSync(RTEST(enabled));
    return Qnil;
}

// Window#mouse_cursor=(show)
// Window#ShowMouseCursor(show)
// Window#mouse_cursor(show)
VALUE rbWindow::ShowMouseCursor(VALUE self, VALUE show)
{
    rb_check_frozen(self);
    ToSFML(self)->ShowMouseCursor(RTEST(show));
    return Qnil;
}

// Window#position(x, y)
// Window#Position(x, y)
VALUE rbWindow::SetPosition(VALUE self, VALUE x, VALUE y)
{
    rb_check_frozen(self);
    ToSFML(self)->SetPosition(NUM2INT(x), NUM2INT(y));
    return Qnil;
}

// Window#position=(vector2)
VALUE rbWindow::SetPosition2(VALUE self, VALUE vector2)
{
    rb_check_frozen(self);
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

// Window#size(width, height)
// Window#Size(width, height)
VALUE rbWindow::SetSize(VALUE self, VALUE width, VALUE height)
{
    rb_check_frozen(self);
    ToSFML(self)->SetSize(NUM2INT(width), NUM2INT(height));
    return Qnil;
}

// Window#size=(vector2)
VALUE rbWindow::SetSize2(VALUE self, VALUE vector2)
{
    rb_check_frozen(self);
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

// Window#title=(title)
// Window#SetTitle(title)
// Window#title(title)
VALUE rbWindow::SetTitle(VALUE self, VALUE title)
{
    rb_check_frozen(self);
    rb_iv_set(self, "@title", StringValue(title));
    ToSFML(self)->SetTitle(StringValueCStr(title));
    return Qnil;
}

// Window#show=(show)
// Window#Show(show)
// Window#show(show)
VALUE rbWindow::Show(VALUE self, VALUE show)
{
    ToSFML(self)->Show(RTEST(show));
    return Qnil;
}

// Window#key_repeat=(enabled)
// Window#EnableKeyRepeat(enabled)
// Window#key_repeat(enabled)
VALUE rbWindow::EnableKeyRepeat(VALUE self, VALUE enabled)
{
    rb_check_frozen(self);
    ToSFML(self)->EnableKeyRepeat(RTEST(enabled));
    return Qnil;
}

// Window#icon(width, height, pixels)
// Window#SetIcon(width, height, pixels)
VALUE rbWindow::SetIcon(VALUE self, VALUE width, VALUE height, VALUE pixels)
{
    unsigned int _width  = NUM2UINT(width);
    unsigned int _height = NUM2UINT(height);
    pixels = rb_ary_to_ary(pixels);
    
    size_t size = _width * _height * 4;
    if (RARRAY_LEN(pixels) != size)
        rb_raise(rb_eTypeError, "expected array lenght to be %d", size);
    
    sf::Uint8* _pixels = new(std::nothrow) sf::Uint8[size];
    if (_pixels == NULL) rb_memerror();
    
    VALUE* pixels_p = RARRAY_PTR(pixels);
    for (size_t i = 0; i < size; ++i)
    {
        _pixels[i] = NUM2CHR(pixels_p[i]);
    }
    
    ToSFML(self)->SetIcon(_width, _height, _pixels);
    delete[] _pixels;
    return Qnil;
}

// Window#active(active=true)
// Window#SetActive(active=true)
// Window#active=(active=true)
VALUE rbWindow::SetActive(int argc, VALUE argv[], VALUE self)
{
    bool ret;
    rbSFML::PrepareErrorStream();
    switch (argc)
    {
        case 0:
            ret = ToSFML(self)->SetActive();
            break;
        case 1:
            ret = ToSFML(self)->SetActive(RTEST(argv[0]));
            break;
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..1)", argc);
    }
    rbSFML::CheckRaise();
    return RBOOL(ret);
}

// Window#display(active)
// Window#Display(active)
VALUE rbWindow::Display(VALUE self)
{
    ToSFML(self)->Display();
    return Qnil;
}

// Window#framerate=(limit)
// Window#SetFramerateLimit(limit)
// Window#framerate(limit)
// Window#framerate_limit=(limit)
// Window#framerate_limit(limit)
VALUE rbWindow::SetFramerateLimit(VALUE self, VALUE limit)
{
    rb_check_frozen(self);
    ToSFML(self)->SetFramerateLimit(NUM2INT(limit));
    return Qnil;
}

// Window#frame_time
// Window#GetFrameTime
// Window#time
VALUE rbWindow::GetFrameTime(VALUE self)
{
    return UINT2NUM(ToSFML(self)->GetFrameTime());
}

// Window#joystick_threshold=(threshold)
// Window#SetJoystickThreshold(threshold)
// Window#joystick_threshold(threshold)
VALUE rbWindow::SetJoystickThreshold(VALUE self, VALUE threshold)
{
    rb_check_frozen(self);
    ToSFML(self)->SetJoystickThreshold(NUM2DBL(threshold));
    return Qnil;
}

// Window#system_handle
// Window#GetSystemHandle
// Window#handle
VALUE rbWindow::GetSystemHandle(VALUE self)
{
    unsigned int handle = (unsigned int)ToSFML(self)->GetSystemHandle();
    return UINT2NUM(handle);
}

// Window#inspect
// Window#to_s
VALUE rbWindow::Inspect(VALUE self)
{
    VALUE ret = rb_sprintf("Window(%p:", (void*)self);
    rb_str_append(ret, rb_inspect(rb_iv_get(self, "@title")));
    rb_str_cat2(ret, ")");
    return ret;
}

// Window#memory_usage
VALUE rbWindow::GetMemoryUsage(VALUE self)
{
    return INT2FIX(sizeof(sf::Window));
}
