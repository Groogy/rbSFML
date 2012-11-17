/* rbSFML
 * Copyright (c) 2012 Henrik Valter Vogelius Hansson - groogy@groogy.se
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

#define SYSTEM_SFML_CPP

#include <System/SFML.hpp>

void rbSFML::Init( VALUE SFML )
{
    rb_define_class_under( SFML, "Error", rb_eRuntimeError );

    rb_define_const( SFML, "SFML_VERSION",    rb_str_new2( SFML_VERSION   ) );
    rb_define_const( SFML, "BINDING_VERSION", rb_str_new2( BINDING_VERSION ) );

    SetRaiseExceptions( SFML, Qtrue );

    rb_define_module_function( SFML, "raise_exceptions",  GetRaiseExceptions, 0 );
    rb_define_module_function( SFML, "raise_exceptions=", SetRaiseExceptions, 1 );
    rb_define_module_function( SFML, "system?",           SystemLoaded,       0 );
    rb_define_module_function( SFML, "window?",           WindowLoaded,       0 );
    rb_define_module_function( SFML, "graphics?",         GraphicsLoaded,     0 );
    rb_define_module_function( SFML, "audio?",            AudioLoaded,        0 );
    rb_define_module_function( SFML, "memory_usage",      GetMemoryUsage,     0 );
}

// SFML.raise_exceptions
VALUE rbSFML::GetRaiseExceptions( VALUE aSelf )
{
    if( !rb_cvar_defined( aSelf, rb_intern( "@@raise_exceptions" ) ) )
        return Qfalse;

    return rb_cv_get( aSelf, "@@raise_exceptions" );
}

// SFML.raise_exceptions=(flag)
VALUE rbSFML::SetRaiseExceptions( VALUE aSelf, VALUE aFlag )
{
    rb_cv_set( aSelf, "@@raise_exceptions", aFlag );
    return Qnil;
}

// SFML.system?
VALUE rbSFML::SystemLoaded( VALUE aSelf )
{
    return Qtrue; // You can't call this method without system.
}

// SFML.window?
VALUE rbSFML::WindowLoaded( VALUE aSelf )
{
    return RBOOL( rb_cv_get( aSelf, "@@window" ) );
}

// SFML.graphics?
VALUE rbSFML::GraphicsLoaded( VALUE aSelf )
{
    return RBOOL( rb_cv_get( aSelf, "@@graphics" ) );
}

// SFML.audio?
VALUE rbSFML::AudioLoaded( VALUE aSelf )
{
    return RBOOL( rb_cv_get( aSelf, "@@audio" ) );
}

// Internal
struct GetMemoryUsageInfo
{
    size_t memoryUsage;
    VALUE* listPointer;
    size_t listLength;
};

// Internal
static VALUE GetMemoryUsageIterator( VALUE anObject, VALUE aData )
{
    GetMemoryUsageInfo* info = (GetMemoryUsageInfo*)aData;
    for( size_t index = 0; index < info->listLength; index++ )
    {
        if( CLASS_OF( anObject ) == info->listPointer[ index ] )
        {
            VALUE usage = rb_funcall( anObject, rb_intern( "memory_usage" ), 0 );
            info->memoryUsage += NUM2SIZET( usage );
            return Qnil;
        }
    }

    return Qnil;
}

// SFML.memory_usage
VALUE rbSFML::GetMemoryUsage( VALUE aSelf )
{
    void* table = rb_mod_const_at( aSelf, 0 );
    VALUE list = rb_const_list( table );

    GetMemoryUsageInfo info;
    info.memoryUsage = 0;
    info.listPointer = RARRAY_PTR( list );
    info.listLength  = RARRAY_LEN( list );

    for( size_t index = 0; index < info.listLength; index++ )
    {
        info.listPointer[ index ] = rb_const_get( aSelf, SYM2ID( info.listPointer[ index ] ) );
    }

    VALUE ObjectSpaceModule = rb_const_get( rb_cObject, rb_intern( "ObjectSpace" ) );
    rb_block_call( ObjectSpaceModule, rb_intern( "each_object" ), 0, NULL,
                   ( VALUE( * )( ... ) )GetMemoryUsageIterator, ( VALUE )&info );

    return SIZET2NUM( info.memoryUsage );
}
