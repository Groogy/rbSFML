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
#include "../System/NonCopyable.hpp"

void rbWindow::Init( VALUE SFML )
{
    rbWindow::Class = rb_define_class_under( SFML, "Window", rb_cObject );
	rb_include_module( rbWindow::Class, rbNonCopyable::Module );
    
    // Class methods
    rb_define_alloc_func( rbWindow::Class, rbMacros::Allocate< sf::Window > );
    
    // Instance methods
    ext_define_method( rbWindow::Class, "initialize",             rbWindow::Initialize,             -1 );
    ext_define_method( rbWindow::Class, "marshal_dump",           rbWindow::MarshalDump,             0 );
    ext_define_method( rbWindow::Class, "create",                 rbWindow::Create,                 -1 );
    ext_define_method( rbWindow::Class, "close",                  rbWindow::Close,                   0 );
    ext_define_method( rbWindow::Class, "open?",                  rbWindow::IsOpen,                  0 );
    ext_define_method( rbWindow::Class, "settings",               rbWindow::GetSettings,             0 );
    ext_define_method( rbWindow::Class, "poll_event",             rbWindow::PollEvent,              -1 );
    ext_define_method( rbWindow::Class, "wait_event",             rbWindow::WaitEvent,              -1 );
    ext_define_method( rbWindow::Class, "each_event",             rbWindow::EachEvent,               0 );
    ext_define_method( rbWindow::Class, "vertical_sync_enabled=", rbWindow::SetVerticalSyncEnabled,  1 );
    ext_define_method( rbWindow::Class, "mouse_cursor_visible=",  rbWindow::SetMouseCursorVisible,   1 );
    ext_define_method( rbWindow::Class, "position=",              rbWindow::SetPosition,             1 );
	ext_define_method( rbWindow::Class, "position",              rbWindow::GetPosition,             0 );
    ext_define_method( rbWindow::Class, "size=",                  rbWindow::SetSize,                 1 );
	ext_define_method( rbWindow::Class, "size",                  rbWindow::GetSize,                 0 );
    ext_define_method( rbWindow::Class, "title=",                 rbWindow::SetTitle,                1 );
    ext_define_method( rbWindow::Class, "visible=",               rbWindow::SetVisible,              1 );
    ext_define_method( rbWindow::Class, "key_repeat_enabled=",    rbWindow::SetKeyRepeatEnabled,     1 );
    ext_define_method( rbWindow::Class, "set_icon",               rbWindow::SetIcon,                 3 );
    ext_define_method( rbWindow::Class, "set_active",             rbWindow::SetActive,              -1 );
    ext_define_method( rbWindow::Class, "display",                rbWindow::Display,                 0 );
    ext_define_method( rbWindow::Class, "framerate=",             rbWindow::SetFramerateLimit,       1 );
    ext_define_method( rbWindow::Class, "joystick_threshold=",    rbWindow::SetJoystickThreshold,    1 );
    ext_define_method( rbWindow::Class, "system_handle",          rbWindow::GetSystemHandle,         0 );
    ext_define_method( rbWindow::Class, "inspect",                rbWindow::Inspect,                 0 );
    
    // Instance aliasses
    rb_define_alias( rbWindow::Class, "Create",                    "create"                 );
    rb_define_alias( rbWindow::Class, "Close",                     "close"                  );
	rb_define_alias( rbWindow::Class, "is_open?",                  "open?"                  );
	rb_define_alias( rbWindow::Class, "is_open",                   "open?"                  );
    rb_define_alias( rbWindow::Class, "isOpen",                    "open?"                  );
	rb_define_alias( rbWindow::Class, "get_settings",              "settings"               );
    rb_define_alias( rbWindow::Class, "getSettings",               "settings"               );
    rb_define_alias( rbWindow::Class, "pollEvent",                 "poll_event"             );
    rb_define_alias( rbWindow::Class, "waitEvent",                 "wait_event"             );
	rb_define_alias( rbWindow::Class, "set_vertical_sync_enabled", "vertical_sync_enabled=" );
    rb_define_alias( rbWindow::Class, "setVerticalSyncEnabled",    "vertical_sync_enabled=" );
	rb_define_alias( rbWindow::Class, "set_mouse_cursor_visible",  "mouse_cursor_visible="  );
    rb_define_alias( rbWindow::Class, "setMouseCursorVisible",     "mouse_cursor_visible="  );
	rb_define_alias( rbWindow::Class, "set_position",              "position="              );
    rb_define_alias( rbWindow::Class, "setPosition",               "position="              );
	rb_define_alias( rbWindow::Class, "get_position",              "position"               );
    rb_define_alias( rbWindow::Class, "getPosition",               "position"               );
	rb_define_alias( rbWindow::Class, "set_size",                  "size="                  );
    rb_define_alias( rbWindow::Class, "setSize",                   "size="                  );
	rb_define_alias( rbWindow::Class, "get_size",                  "size"                   );
    rb_define_alias( rbWindow::Class, "getSize",                   "size"                   );
	rb_define_alias( rbWindow::Class, "set_title",                 "title="                 );
    rb_define_alias( rbWindow::Class, "setTitle",                  "title="                 );
	rb_define_alias( rbWindow::Class, "set_visible",               "visible="               );
    rb_define_alias( rbWindow::Class, "setVisible",                "visible="               );
	rb_define_alias( rbWindow::Class, "set_key_repeat_enabled",    "key_repeat_enabled="    );
    rb_define_alias( rbWindow::Class, "setKeyRepeatEnabled",       "key_repeat_enabled="    );
    rb_define_alias( rbWindow::Class, "setIcon",                   "set_icon"               );
	rb_define_alias( rbWindow::Class, "active=",                   "set_active"             );
    rb_define_alias( rbWindow::Class, "setActive",                 "set_active"             );
    rb_define_alias( rbWindow::Class, "setFramerateLimit",         "framerate="             );
    rb_define_alias( rbWindow::Class, "framerate_limit=",          "framerate="             );
    rb_define_alias( rbWindow::Class, "set_framerate_limit",       "framerate="             );
	rb_define_alias( rbWindow::Class, "set_framerate",             "framerate="             );
    rb_define_alias( rbWindow::Class, "fps=",                      "framerate="             );
    rb_define_alias( rbWindow::Class, "setJoystickThreshold",      "joystick_threshold="    );
    rb_define_alias( rbWindow::Class, "set_joystick_threshold",    "joystick_threshold="    );
    rb_define_alias( rbWindow::Class, "getSystemHandle",           "system_handle"          );
    rb_define_alias( rbWindow::Class, "handle",                    "system_handle"          );
    rb_define_alias( rbWindow::Class, "to_s",                      "inspect"                );
}

// Window#initialize(...)
VALUE rbWindow::Initialize( int argc, VALUE argv[], VALUE aSelf )
{
    if( argc > 0 )
        Create( argc, argv, aSelf );
    
    return rb_call_super( 0, NULL );
}

// Window#marshal_dump
VALUE rbWindow::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
    return Qnil;
}

// Window#create(...)
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
            window->create( handle );
            break;
        case 2:
            if( handle == 0 )
                window->create( *mode, title );
            else
                window->create( handle, *settings );
            break;
        case 3:
            window->create( *mode, title, style );
            break;
        case 4:
            window->create( *mode, title, style, *settings );
            break;
    }
    rbSFML::CheckRaise();
    
    return Qnil;
}

// Window#close
VALUE rbWindow::Close( VALUE aSelf )
{
    rb_iv_set( aSelf, "@title", Qnil );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->close();
    return Qnil;
}

// Window#open?
// Window#is_open?
// Window#is_open
// Window#isOpen
VALUE rbWindow::IsOpen( VALUE aSelf )
{
    return RBOOL( rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->isOpen() );
}

// Window#settings
// Window#get_settings
// Window#getSettings
VALUE rbWindow::GetSettings( VALUE aSelf )
{
	sf::ContextSettings& settings = const_cast< sf::ContextSettings& >( rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->getSettings() );
	VALUE object = rbMacros::ToRuby( &settings, rbContextSettings::Class );
	rb_iv_set( object, "@__ref__owner", aSelf );
	rb_obj_freeze( object );
	return object;
}

// Internal
static inline bool internalPollEvent( VALUE aSelf, VALUE anEvent )
{    
    sf::Event event;
    bool ret = rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->pollEvent( event );
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
    bool ret = rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->waitEvent( event );
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
    while( rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->pollEvent( event ) )
    {
        *eventPtr = event;
        rb_yield( eventObject );
    }
    return aSelf;
}

// Window#vertical_sync_enabled=(enabled)
// Window#setVerticalSyncEnabled(enabled)
// Window#set_vertical_sync_enabled(enabled)
VALUE rbWindow::SetVerticalSyncEnabled( VALUE aSelf, VALUE anEnabled )
{
    rb_check_frozen( aSelf );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->setVerticalSyncEnabled( RTEST( anEnabled ) );
    return Qnil;
}

// Window#mouse_cursor_visible=(show)
// Window#setMouseCursorVisible(show)
// Window#set_mouse_cursor_visible(show)
VALUE rbWindow::SetMouseCursorVisible( VALUE aSelf, VALUE aShow )
{
    rb_check_frozen( aSelf );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->setMouseCursorVisible( RTEST( aShow ) );
    return Qnil;
}

// Window#position=(vector2)
// Window#set_position(vector2)
// Window#setPosition(vector2)
VALUE rbWindow::SetPosition( VALUE aSelf, VALUE aPosition )
{
    rb_check_frozen( aSelf );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->setPosition( rbVector2::ToSFMLi( aPosition ) );
    return Qnil;
}

// Window#position()
// Window#get_position()
// Window#getPosition()
VALUE rbWindow::GetPosition( VALUE aSelf )
{
    return rbVector2::ToRuby( rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->getPosition() );
}

// Window#size=(vector2)
// Window#set_size(vector2)
// Window#setSize(vector2)
VALUE rbWindow::SetSize( VALUE aSelf, VALUE aSize )
{
    rb_check_frozen( aSelf );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->setSize( rbVector2::ToSFMLu( aSize ) );
    return Qnil;
}

// Window#size()
// Window#get_size()
// Window#getSize()
VALUE rbWindow::GetSize( VALUE aSelf )
{
    return rbVector2::ToRuby( rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->getSize() );
}

// Window#title=(title)
// Window#set_title(title)
// Window#setTitle(title)
VALUE rbWindow::SetTitle( VALUE aSelf, VALUE aTitle )
{
    rb_check_frozen( aSelf );
    rb_iv_set( aSelf, "@title", StringValue( aTitle ) );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->setTitle( StringValueCStr( aTitle ) );
    return Qnil;
}

// Window#visible=(show)
// Window#set_visible(show)
// Window#setVisible(show)
VALUE rbWindow::SetVisible( VALUE aSelf, VALUE aShow )
{
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->setVisible( RTEST( aShow ) );
    return Qnil;
}

// Window#key_repeat=(enabled)
// Window#set_key_repeat_enabled(enabled)
// Window#setKeyRepeatEnabled(enabled)
VALUE rbWindow::SetKeyRepeatEnabled( VALUE aSelf, VALUE anEnabled )
{
    rb_check_frozen( aSelf );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->setKeyRepeatEnabled( RTEST( anEnabled ) );
    return Qnil;
}

// Window#set_icon(width, height, pixels)
// Window#etIcon(width, height, pixels)
VALUE rbWindow::SetIcon( VALUE aSelf, VALUE aWidth, VALUE aHeight, VALUE somePixels )
{
    unsigned int width  = NUM2UINT( aWidth );
    unsigned int height = NUM2UINT( aHeight );
    somePixels = rb_ary_to_ary( somePixels );
    
    unsigned long size = width * height * 4;
    if( static_cast< unsigned long >( RARRAY_LEN( somePixels ) ) != size )
        rb_raise( rb_eTypeError, "expected array lenght to be %lu", size );
    
	sf::Uint8* pixels = static_cast< sf::Uint8 * >( xmalloc( sizeof( sf::Uint8 ) * size ) );
    if( pixels == NULL ) rb_memerror();
    
    VALUE* pixelsPtr = RARRAY_PTR( somePixels );
    for( unsigned long index = 0; index < size; index++ )
    {
        pixels[ index ] = NUM2CHR( pixelsPtr[ index ] );
    }
    
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->setIcon( width, height, pixels );
    xfree( pixels );
    return Qnil;
}

// Window#active=(active=true)
// Window#set_active(active=true)
// Window#setActive(active=true)
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
            ret = rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->setActive();
            break;
        case 1:
            ret = rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->setActive( RTEST( argv[ 0 ] ) );
            break;
    }
    rbSFML::CheckRaise();
    return RBOOL( ret );
}

// Window#display()
VALUE rbWindow::Display( VALUE aSelf )
{
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->display();
    return Qnil;
}

// Window#fps=(limit)
// Window#framerate=(limit)
// Window#framerate_limit=(limit)
// Window#set_framerate(limit)
// Window#set_framerate_limit(limit)
// Window#setFramerateLimit(limit)
VALUE rbWindow::SetFramerateLimit( VALUE aSelf, VALUE aLimit )
{
    rb_check_frozen( aSelf );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->setFramerateLimit( NUM2INT( aLimit ) );
    return Qnil;
}

// Window#joystick_threshold=(threshold)
// Window#set_joystick_threshold(threshold)
// Window#setJoystickThreshold(threshold)
VALUE rbWindow::SetJoystickThreshold( VALUE aSelf, VALUE aThreshold )
{
    rb_check_frozen( aSelf );
    rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->setJoystickThreshold( NUM2DBL( aThreshold ) );
    return Qnil;
}

// Window#system_handle
// Window#getSystemHandle
// Window#handle
VALUE rbWindow::GetSystemHandle( VALUE aSelf )
{
    return ULONG2NUM( (unsigned long)( rbMacros::ToSFML< sf::Window >( aSelf, rbWindow::Class )->getSystemHandle() ) );
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
