/* rbSFML - Copyright (c) 2010 Henrik Valter Vogelius Hansson - groogy@groogy.se
 * This software is provided 'as-is', without any express or
 * implied warranty. In no event will the authors be held
 * liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment
 *    in the product documentation would be appreciated but
 *    is not required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any
 *    source distribution.
 */
 
#include "Clock.hpp"
#include "main.hpp"

VALUE globalClockClass;

/* Free a heap allocated object 
 * Not accessible trough ruby directly!
 */
static void Clock_Free( sf::Clock *anObject )
{
	delete anObject;
}

/* Internal:
 * Returns a SFML clock from a ruby one.
 */
sf::Clock* Clock_ToSFML( VALUE aClock ) {
	sf::Clock *clock = NULL;
	Data_Get_Struct( aClock, sf::Clock, clock );
	return clock;
}

/* Internal:
 * Returns a ruby object from a pointer. It assumes that the pointer
 * will not be freed and will never be invalid. (It frees the pointer
 * when the object is gabage collected.)
 */
VALUE Clock_ToRuby( sf::Clock *aClock )
{
	return Data_Wrap_Struct( globalClockClass, 0, Clock_Free, aClock );
}

/* Internal:
 * Returns a ruby object from a reference. It assumes that the return value
 * will not be sent to the end user and that the object will free itself.
 */
VALUE Clock_ToRuby( sf::Clock &aClock )
{
	return Data_Wrap_Struct( globalClockClass, 0, 0, &aClock );
}

// Clock#elapsed_time
static VALUE Clock_GetElapsedTime( VALUE self )
{
	sf::Clock *clock = NULL;
	Data_Get_Struct( self, sf::Clock, clock );
	return INT2FIX( clock->GetElapsedTime() );
}

// Clock#reset
static VALUE Clock_Reset( VALUE self )
{
	sf::Clock *clock = Clock_ToSFML( self );
	clock->Reset();
	return Qnil;
}

// Clock#initialize_copy
static VALUE Clock_InitializeCopy( VALUE self, VALUE aSource )
{
	sf::Clock *clock = Clock_ToSFML( self );
	sf::Clock *source = Clock_ToSFML( aSource );
	*clock = *source;
	return self;
}

// Clock#==
static VALUE Clock_Equal( VALUE self, VALUE anArgument )
{
	sf::Clock *left = Clock_ToSFML( self );
	sf::Clock *right = Clock_ToSFML( anArgument );
	return (left->GetElapsedTime()) == (right->GetElapsedTime()) ? Qtrue : Qfalse;
}

// Clock#inspect
static VALUE Clock_inspect( VALUE self )
{
	sf::Clock *clock = Clock_ToSFML( self );
	VALUE result = rb_str_new2( "Clock(" );
	rb_str_concat( result, INT2FIX( clock->GetElapsedTime() ) );
	rb_str_concat( result, rb_str_new2( ")" ) );
	return result;
}

// Clock#memory_usage
static VALUE Clock_MemoryUsage( VALUE self )
{
	return INT2FIX( sizeof( sf::Clock ) );
}

// Clock.allocate
static VALUE Clock_Allocate( VALUE aKlass )
{
	sf::Clock *object = new sf::Clock();
	return Data_Wrap_Struct( aKlass, 0, Clock_Free, object );
}

// Ruby initiation function
void Init_Clock( void )
{
	VALUE sfml = rb_define_module( "SFML" );
	globalClockClass = rb_define_class_under( sfml, "Clock", rb_cObject );
	
	// Class methods
	rb_define_alloc_func( globalClockClass, Clock_Allocate );
	
	// Instance methods
	rb_define_method( globalClockClass, "initialize_copy", Clock_InitializeCopy, 1 );
	rb_define_method( globalClockClass, "GetElapsedTime",  Clock_GetElapsedTime, 0 );
	rb_define_method( globalClockClass, "Reset",           Clock_Reset,          0 );
	rb_define_method( globalClockClass, "==",              Clock_Equal,          1 );
	rb_define_method( globalClockClass, "inspect",         Clock_inspect,        0 );
	rb_define_method( globalClockClass, "memory_usage",    Clock_MemoryUsage,    0 );
	
	// Instance aliasses
	rb_define_alias( globalClockClass, "ElapsedTime",      "GetElapsedTime" );
	rb_define_alias( globalClockClass, "elapsedTime",      "GetElapsedTime" );
	rb_define_alias( globalClockClass, "elapsed_time",     "GetElapsedTime" );
	rb_define_alias( globalClockClass, "getElapsedTime",   "GetElapsedTime" );
	rb_define_alias( globalClockClass, "get_elapsed_time", "GetElapsedTime" );
	rb_define_alias( globalClockClass, "time",             "GetElapsedTime" );
	rb_define_alias( globalClockClass, "to_s",             "inspect" );
	rb_define_alias( globalClockClass, "to_str",           "inspect" );
}
