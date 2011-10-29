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
 
#include "InputStream.hpp"

rbInputStream::rbInputStream( VALUE aIO )
{
	myIO = aIO;
}

sf::Int64 rbInputStream::Read( char *aDataBuffer, sf::Int64 aSize )
{
	VALUE buffer = rb_funcall( myIO, rb_intern( "read" ), 1, LONG2NUM( aSize ) );
	memcpy( aDataBuffer, RSTRING_PTR( buffer ), RSTRING_LEN( buffer ) );
	return RSTRING_LEN( buffer );
}

sf::Int64 rbInputStream::Seek( sf::Int64 aPosition )
{
	rb_funcall( myIO, rb_intern( "seek" ), 1, LONG2NUM( aPosition ) );
	return aPosition;
}

sf::Int64 rbInputStream::Tell()
{
	return NUM2LONG( rb_funcall( myIO, rb_intern( "tell" ), 0 ) );
}

sf::Int64 rbInputStream::GetSize()
{
	VALUE pos = rb_funcall( myIO, rb_intern( "tell" ), 0 );
	rb_funcall( myIO, rb_intern( "seek" ), 2, LONG2NUM( 0 ), rb_const_get( rb_cIO, rb_intern( "SEEK_END" ) ) );
	VALUE size = rb_funcall( myIO, rb_intern( "tell" ), 0 );
	rb_funcall( myIO, rb_intern( "seek" ), 1, pos );
	return size;
}
