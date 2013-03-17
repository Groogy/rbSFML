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

#define WINDOW_CONTEXT_CPP
#include "Context.hpp"
#include "../System/SFML.hpp"
#include "../System/NonCopyable.hpp"

void rbContext::Init( VALUE SFML )
{
    rbContext::Class = rb_define_class_under( SFML, "Context", rb_cObject );
	rb_include_module( rbContext::Class, rbNonCopyable::Module );
    
    // Class methods
    rb_define_alloc_func( rbContext::Class, rbMacros::Allocate< sf::Context > );
    
    // Instance methods
    ext_define_method( rbContext::Class, "initialize",   rbContext::Initialize,     -1 );
    ext_define_method( rbContext::Class, "marshal_dump", rbContext::MarshalDump,     0 );
    ext_define_method( rbContext::Class, "active=",      rbContext::SetActive,       1 );
	
	// Instance aliasses
    rb_define_alias( rbContext::Class, "setActive", "active=" );
}

// Context#initialize
// Context#initialize(settings, width, height)
VALUE rbContext::Initialize( int argc, VALUE argv[], VALUE aSelf )
{
    switch(argc)
    {
        case 0:
            break;
        case 3:
            new( rbMacros::ToSFML< sf::Context >( aSelf, rbContext::Class ) ) sf::Context( *rbContextSettings::ToSFML( argv[ 0 ] ),
                                          UINT2NUM( argv[ 1 ] ),
                                          UINT2NUM( argv[ 2 ] ) );
            break;
        default:
            rb_raise( rb_eArgError,
                      "wrong number of arguments(%i for 0 or 3)", argc );
    }
    
    return Qnil;
}

// Context#marshal_dump
VALUE rbContext::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
    return Qnil;
}

// Context#active=(active)
// Context#SetActive(active)
// Context#active(active)
VALUE rbContext::SetActive( VALUE aSelf, VALUE anActiveFlag )
{
    rb_check_frozen( aSelf );
	rbSFML::PrepareErrorStream();
    bool ret = rbMacros::ToSFML< sf::Context >( aSelf, rbContext::Class )->setActive( RTEST( anActiveFlag ) );
    rbSFML::CheckRaise();	
    return RBOOL(ret);
}
