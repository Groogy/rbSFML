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

#include "InputStream.hpp"

// TODO: Work with bignums. Now it's limited to Int32.

rbInputStream::rbInputStream( VALUE anInputObject )
{
    self = anInputObject;
}

sf::Int64 rbInputStream::Read( char* aBuffer, sf::Int64 aSize )
{
    VALUE str = rb_funcall( self, rb_intern( "read" ), 1, INT2NUM( aSize ) );
    memcpy( aBuffer, RSTRING_PTR( str ), RSTRING_LEN( str ) );
    return RSTRING_LEN( str );
}

sf::Int64 rbInputStream::Seek( sf::Int64 aPosition )
{
    VALUE returnValue = rb_funcall( self, rb_intern( "seek" ), 1, INT2NUM( aPosition ) );
    return NUM2INT( returnValue );
}

sf::Int64 rbInputStream::Tell()
{
    return NUM2INT( rb_funcall( self, rb_intern( "tell" ), 0 ) );
}

sf::Int64 rbInputStream::GetSize()
{
    static VALUE cSEEK_END = rb_const_get( rb_cIO, rb_intern( "SEEK_END" ) );
    VALUE pos = rb_funcall( self, rb_intern( "tell" ), 0 );
    rb_funcall( self, rb_intern( "seek" ), 2, INT2FIX( 0 ), cSEEK_END );
    VALUE size = rb_funcall( self, rb_intern( "tell" ), 0 );
    rb_funcall( self, rb_intern( "seek" ), 1, pos );
    return NUM2INT( size );
}
