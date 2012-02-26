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
#include "System/NonCopyable.hpp"

void rbWindow::Init( VALUE SFML )
{
    rbWindow::Class = rb_define_class_under( SFML, "Window", rb_cObject );
	rb_include_module( rbWindow::Class, rbNonCopyable::Module );
    
    // Class methods
    rb_define_alloc_func( rbWindow::Class, rbMacros::Allocate< sf::Window > );
    
    // Instance methods
    rb_define_method( rbWindow::Class, "initialize",          rbWindow::Initialize,           -1 );
    rb_define_method( rbWindow::Class, "marshal_dump",        rbWindow::MarshalDump,           0 );
    rb_define_method( rbWindow::Class, "create",              rbWindow::Create,               -1 );
    rb_define_method( rbWindow::Class, "close",               rbWindow::Close,                 0 );
    rb_define_method( rbWindow::Class, "open?",               rbWindow::IsOpen,                0 );
    rb_define_method( rbWindow::Class, "width",               rbWindow::GetWidth,              0 );
    rb_define_method( rbWindow::Class, "height",              rbWindow::GetHeight,             0 );
    rb_define_method( rbWindow::Class, "settings",            rbWindow::GetSettings,           0 );
    rb_define_method( rbWindow::Class, "poll_event",          rbWindow::PollEvent,            -1 );
    rb_define_method( rbWindow::Class, "wait_event",          rbWindow::WaitEvent,            -1 );
    rb_define_method( rbWindow::Class, "each_event",          rbWindow::EachEvent,             0 );
    rb_define_method( rbWindow::Class, "vertical_sync=",      rbWindow::EnableVerticalSync,    1 );
    rb_define_method( rbWindow::Class, "mouse_cursor=",       rbWindow::ShowMouseCursor,       1 );
    rb_define_method( rbWindow::Class, "position",            rbWindow::SetPosition,           2 );
    rb_define_method( rbWindow::Class, "position=",           rbWindow::SetPosition2,          1 );
    rb_define_method( rbWindow::Class, "size",                rbWindow::SetSize,               2 );
    rb_define_method( rbWindow::Class, "size=",               rbWindow::SetSize2,              1 );
    rb_define_method( rbWindow::Class, "title=",              rbWindow::SetTitle,              1 );
    rb_define_method( rbWindow::Class, "show=",               rbWindow::Show,                  1 );
    rb_define_method( rbWindow::Class, "key_repeat=",         rbWindow::EnableKeyRepeat,       1 );
    rb_define_method( rbWindow::Class, "icon",                rbWindow::SetIcon,               3 );
    rb_define_method( rbWindow::Class, "active",              rbWindow::SetActive,            -1 );
    rb_define_method( rbWindow::Class, "display",             rbWindow::Display,               0 );
    rb_define_method( rbWindow::Class, "framerate=",          rbWindow::SetFramerateLimit,     1 );
    rb_define_method( rbWindow::Class, "joystick_threshold=", rbWindow::SetJoystickThreshold,  1 );
    rb_define_method( rbWindow::Class, "system_handle",       rbWindow::GetSystemHandle,       0 );
    rb_define_method( rbWindow::Class, "inspect",             rbWindow::Inspect,               0 );
    rb_define_method( rbWindow::Class, "memory_usage",        rbWindow::GetMemoryUsage,        0 );
    
    // Instance aliasses
    rb_define_alias( rbWindow::Class, "Create",               "create"              );
    rb_define_alias( rbWindow::Class, "Close",                "close"               );
    rb_define_alias( rbWindow::Class, "IsOpen",               "opened?"             );
    rb_define_alias( rbWindow::Class, "GetWidth",             "width"               );
    rb_define_alias( rbWindow::Class, "GetHeight",            "height"              );
    rb_define_alias( rbWindow::Class, "GetSettings",          "settings"            );
    rb_define_alias( rbWindow::Class, "PollEvent",            "poll_event"          );
    rb_define_alias( rbWindow::Class, "event",                "poll_event"          );
    rb_define_alias( rbWindow::Class, "WaitEvent",            "wait_event"          );
    rb_define_alias( rbWindow::Class, "EnableVerticalSync",   "vertical_sync="      );
    rb_define_alias( rbWindow::Class, "vertical_sync",        "vertical_sync="      );
    rb_define_alias( rbWindow::Class, "ShowMouseCursor",      "mouse_cursor="       );
    rb_define_alias( rbWindow::Class, "mouse_cursor",         "mouse_cursor="       );
    rb_define_alias( rbWindow::Class, "SetPosition",          "position"            );
    rb_define_alias( rbWindow::Class, "SetSize",              "size"                );
    rb_define_alias( rbWindow::Class, "SetTitle",             "title="              );
    rb_define_alias( rbWindow::Class, "title",                "title="              );
    rb_define_alias( rbWindow::Class, "Show",                 "show="               );
    rb_define_alias( rbWindow::Class, "show",                 "show="               );
    rb_define_alias( rbWindow::Class, "EnableKeyRepeat",      "key_repeat="         );
    rb_define_alias( rbWindow::Class, "key_repeat",           "key_repeat="         );
    rb_define_alias( rbWindow::Class, "SetIcon",              "icon"                );
    rb_define_alias( rbWindow::Class, "SetActive",            "active"              );
    rb_define_alias( rbWindow::Class, "active=",              "active"              );
    rb_define_alias( rbWindow::Class, "Display",              "display"             );
    rb_define_alias( rbWindow::Class, "SetFramerateLimit",    "framerate="          );
    rb_define_alias( rbWindow::Class, "framerate",            "framerate="          );
    rb_define_alias( rbWindow::Class, "framerate_limit=",     "framerate="          );
    rb_define_alias( rbWindow::Class, "framerate_limit",      "framerate="          );
    rb_define_alias( rbWindow::Class, "fps=",                 "framerate="          );
    rb_define_alias( rbWindow::Class, "SetJoystickThreshold", "joystick_threshold=" );
    rb_define_alias( rbWindow::Class, "joystick_threshold",   "joystick_threshold=" );
    rb_define_alias( rbWindow::Class, "GetSystemHandle",      "system_handle"       );
    rb_define_alias( rbWindow::Class, "handle",               "system_handle"       );
    rb_define_alias( rbWindow::Class, "to_s",                 "inspect"             );
}

// Window#initialize(...)
VALUE rbWindow::Initialize( int argc, VALUE argv[], VALUE aSelf )
{
    if( argc > 0 )
        Create( argc, argv, aSelf );
    
    return Qnil;
}

// Window#marshal_dump
VALUE rbWindow::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
    return Qnil;
}

// Window#create(...)
// Window#Create(...)
VALUE rbWindow::Create( int argc, VALUE argv[], VALUE aSelf )
{
    sf::Window* window = rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class );
    sf::WindowHandle handle = 0;
    sf::VideoMode* mode = NULL;
    std::string title;
    sf::Uint32 style = 0;
    sf::ContextSettings* settings = NULL;
    
    switch( argc )
    {
        case 1:
            handle = sf::WindowHandle( NUM2UINT( argv[ 0 ] ) );
            break;
        case 2:
            if( FIXNUM_P( argv[ 0 ] ) )
            {
                settings = rbContextSettings::ToSFML( argv[ 1 ] );
            }
            else
            {
                mode = rbVideoMode::ToSFML( argv[ 0 ] );
                rb_iv_set( aSelf, "@title", StringValue( argv[ 1 ] ) );
                title = StringValueCStr( argv[ 1 ] );
            }
            break;
        case 4:
            settings = rbContextSettings::ToSFML( argv[ 3 ] );
			
        case 3:
            mode = rbVideoMode::ToSFML( argv[ 0 ] );
            rb_iv_set( aSelf, "@title", StringValue( argv[ 1 ] ) );
            title = StringValueCStr( argv[ 1 ] );
            style = NUM2INT( argv[ 2 ] );
            break;
        default:
            rb_raise( rb_eArgError,
                      "wrong number of arguments(%i for 1..4)", argc );
    }
    
    rbSFML::PrepareErrorStream();
    switch( argc )
    {
        case 1:
            window->Create( handle );
            break;
        case 2:
            if( handle == 0 )
                window->Create( *mode, title );
            else
                window->Create( handle, *settings );
            break;
        case 3:
            window->Create( *mode, title, style );
            break;
        case 4:
            window->Create( *mode, title, style, *settings );
            break;
    }
    rbSFML::CheckWarn();
    
    return Qnil;
}

// Window#close
// Window#Close
VALUE rbWindow::Close( VALUE aSelf )
{
    rb_iv_set( aSelf, "@title", Qnil );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->Close();
    return Qnil;
}

// Window#opened?
// Window#IsOpened
// Window#open?
VALUE rbWindow::IsOpen( VALUE aSelf )
{
    return RBOOL( rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->IsOpen() );
}

// Window#width
// Window#GetWidth
VALUE rbWindow::GetWidth( VALUE aSelf )
{
    return INT2FIX( rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->GetWidth() );
}

// Window#height
// Window#GetHeight
VALUE rbWindow::GetHeight( VALUE aSelf )
{
    return INT2FIX( rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->GetHeight() );
}

// Window#settings
// Window#GetSettings
VALUE rbWindow::GetSettings( VALUE aSelf )
{
	sf::ContextSettings& settings = const_cast< sf::ContextSettings& >( rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->GetSettings() );
	VALUE object = rbMacros::ToRuby( &settings, rbContextSettings::Class );
	rb_iv_set( object, "@__ref__owner", aSelf );
	rb_obj_freeze( object );
	return object;
}

// Internal
static inline bool internalPollEvent( VALUE aSelf, VALUE anEvent )
{    
    sf::Event event;
    bool ret = rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->PollEvent( event );
    if( ret )
        *rbMacros::ToSFML< sf::Event >( anEvent, rbEvent::Class ) = event;
    
    return ret;
}

// Window#poll_event
// Window#PollEvent
// Window#poll_event(event)
// Window#PollEvent(event)
VALUE rbWindow::PollEvent( int argc, VALUE argv[], VALUE aSelf )
{
    switch( argc )
    {
        case 0:
        {
            VALUE event = rbMacros::Allocate< sf::Event >( rbEvent::Class );
            return internalPollEvent( aSelf, event ) ? event : Qnil;
        }
        case 1:
            return RBOOL( internalPollEvent( aSelf, argv[ 0 ] ) );
        default:
            rb_raise( rb_eArgError,
                      "wrong number of arguments(%i for 0..1)", argc );
    }
}

// Internal
static inline bool internalWaitEvent( VALUE aSelf, VALUE anEvent )
{
    using namespace rbWindow;
    
    sf::Event event;
    bool ret = rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->WaitEvent( event );
    if( ret )
        *rbMacros::ToSFML< sf::Event >( anEvent, rbEvent::Class ) = event;
    
    return ret;
}

// Window#wait_event
// Window#WaitEvent
// Window#wait_event(event)
// Window#WaitEvent(event)
VALUE rbWindow::WaitEvent( int argc, VALUE argv[], VALUE aSelf )
{
    switch( argc )
    {
        case 0:
        {
            VALUE event = rbMacros::Allocate< sf::Event >( rbEvent::Class );
            return internalWaitEvent( aSelf, event ) ? event : Qnil;
        }
        case 1:
            return RBOOL( internalWaitEvent( aSelf, argv[ 0 ] ) );
        default:
            rb_raise( rb_eArgError,
                      "wrong number of arguments(%i for 0..1)", argc );
    }
}

// Window#each_event
VALUE rbWindow::EachEvent( VALUE aSelf )
{
    RETURN_ENUMERATOR( aSelf, 0, NULL );
    sf::Event event;
	VALUE eventObject = rbMacros::Allocate< sf::Event >( rbEvent::Class );
	sf::Event* eventPtr = rbMacros::ToSFML< sf::Event >( eventObject, rbEvent::Class );
    while( rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->PollEvent( event ) )
    {
        *eventPtr = event;
        rb_yield( eventObject );
    }
    return aSelf;
}

// Window#vertical_sync=(enabled)
// Window#EnableVerticalSync(enabled)
// Window#vertical_sync(enabled)
VALUE rbWindow::EnableVerticalSync( VALUE aSelf, VALUE anEnabled )
{
    rb_check_frozen( aSelf );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->EnableVerticalSync( RTEST( anEnabled ) );
    return Qnil;
}

// Window#mouse_cursor=(show)
// Window#ShowMouseCursor(show)
// Window#mouse_cursor(show)
VALUE rbWindow::ShowMouseCursor( VALUE aSelf, VALUE aShow )
{
    rb_check_frozen( aSelf );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->ShowMouseCursor( RTEST( aShow ) );
    return Qnil;
}

// Window#position(x, y)
// Window#Position(x, y)
VALUE rbWindow::SetPosition( VALUE aSelf, VALUE anX, VALUE anY )
{
    rb_check_frozen( aSelf );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->SetPosition( NUM2INT( anX ), NUM2INT( anY ) );
    return Qnil;
}

// Window#position=(vector2)
VALUE rbWindow::SetPosition2( VALUE aSelf, VALUE aVector2 )
{
    rb_check_frozen( aSelf );
    aVector2 = rbVector2::ToRuby( aVector2 );
    VALUE x = rbVector2::GetX( aVector2 );
    VALUE y = rbVector2::GetY( aVector2 );
    SetPosition( aSelf, x, y );
    
    return Qnil;
}

// Window#size(width, height)
// Window#Size(width, height)
VALUE rbWindow::SetSize( VALUE aSelf, VALUE aWidth, VALUE aHeight )
{
    rb_check_frozen( aSelf );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->SetSize( NUM2INT( aWidth ), NUM2INT( aHeight ) );
    return Qnil;
}

// Window#size=(vector2)
VALUE rbWindow::SetSize2( VALUE aSelf, VALUE aVector2 )
{
    rb_check_frozen( aSelf );
    aVector2 = rbVector2::ToRuby( aVector2 );
    VALUE width  = rbVector2::GetX( aVector2 );
    VALUE height = rbVector2::GetY( aVector2 );
    SetSize( aSelf, width, height );
    
    return Qnil;
}

// Window#title=(title)
// Window#SetTitle(title)
// Window#title(title)
VALUE rbWindow::SetTitle( VALUE aSelf, VALUE aTitle )
{
    rb_check_frozen( aSelf );
    rb_iv_set( aSelf, "@title", StringValue( aTitle ) );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->SetTitle( StringValueCStr( aTitle ) );
    return Qnil;
}

// Window#show=(show)
// Window#Show(show)
// Window#show(show)
VALUE rbWindow::Show( VALUE aSelf, VALUE aShow )
{
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->Show( RTEST( aShow ) );
    return Qnil;
}

// Window#key_repeat=(enabled)
// Window#EnableKeyRepeat(enabled)
// Window#key_repeat(enabled)
VALUE rbWindow::EnableKeyRepeat( VALUE aSelf, VALUE anEnabled )
{
    rb_check_frozen( aSelf );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->EnableKeyRepeat( RTEST( anEnabled ) );
    return Qnil;
}

// Window#icon(width, height, pixels)
// Window#SetIcon(width, height, pixels)
VALUE rbWindow::SetIcon( VALUE aSelf, VALUE aWidth, VALUE aHeight, VALUE somePixels )
{
    unsigned int width  = NUM2UINT( aWidth );
    unsigned int height = NUM2UINT( aHeight );
    somePixels = rb_ary_to_ary( somePixels );
    
    size_t size = width * height * 4;
    if( RARRAY_LEN( somePixels ) != size )
        rb_raise( rb_eTypeError, "expected array lenght to be %d", size );
    
	sf::Uint8* pixels = static_cast< sf::Uint8 * >( xmalloc( sizeof( sf::Uint8 ) * size ) );
    if( pixels == NULL ) rb_memerror();
    
    VALUE* pixelsPtr = RARRAY_PTR( somePixels );
    for( size_t index = 0; index < size; index++ )
    {
        pixels[ index ] = NUM2CHR( pixelsPtr[ index ] );
    }
    
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->SetIcon( width, height, pixels );
    xfree( pixels );
    return Qnil;
}

// Window#active(active=true)
// Window#SetActive(active=true)
// Window#active=(active=true)
VALUE rbWindow::SetActive( int argc, VALUE argv[], VALUE aSelf )
{
    switch( argc )
    {
        case 0:
        case 1:
            break;
        default:
            rb_raise( rb_eArgError,
                      "wrong number of arguments(%i for 0..1)", argc );
    }
    bool ret;
    rbSFML::PrepareErrorStream();
    switch( argc )
    {
        case 0:
            ret = rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->SetActive();
            break;
        case 1:
            ret = rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->SetActive( RTEST( argv[ 0 ] ) );
            break;
    }
    rbSFML::CheckRaise();
    return RBOOL( ret );
}

// Window#display(active)
// Window#Display(active)
VALUE rbWindow::Display( VALUE aSelf )
{
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->Display();
    return Qnil;
}

// Window#framerate=(limit)
// Window#SetFramerateLimit(limit)
// Window#framerate(limit)
// Window#framerate_limit=(limit)
// Window#framerate_limit(limit)
VALUE rbWindow::SetFramerateLimit( VALUE aSelf, VALUE aLimit )
{
    rb_check_frozen( aSelf );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->SetFramerateLimit( NUM2INT( aLimit ) );
    return Qnil;
}

// Window#joystick_threshold=(threshold)
// Window#SetJoystickThreshold(threshold)
// Window#joystick_threshold(threshold)
VALUE rbWindow::SetJoystickThreshold( VALUE aSelf, VALUE aThreshold )
{
    rb_check_frozen( aSelf );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->SetJoystickThreshold( NUM2DBL( aThreshold ) );
    return Qnil;
}

// Window#system_handle
// Window#GetSystemHandle
// Window#handle
VALUE rbWindow::GetSystemHandle( VALUE aSelf )
{
    return UINT2NUM( (unsigned int)rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->GetSystemHandle() );
}

// Window#inspect
// Window#to_s
VALUE rbWindow::Inspect( VALUE aSelf )
{
    VALUE title = rb_iv_get( aSelf, "@title" );
    if( NIL_P( title ) ) // Closed
        return rb_sprintf( "%s(%p)",
                           rb_obj_classname( aSelf ),
                           (void*)aSelf );
    else
        return rb_sprintf( "%s(%p: \"%s\")",
                           rb_obj_classname( aSelf ),
                           (void*)aSelf,
                           StringValueCStr( title ) );
}

// Window#memory_usage
VALUE rbWindow::GetMemoryUsage( VALUE aSelf )
{
    return SIZET2NUM( sizeof( sf::Window ) );
}
