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
#include "global.hpp"
#include <SFML/System/InputStream.hpp>

class rbInputStream : public sf::InputStream
{
public:
	rbInputStream()
	: myReadSym( rb_intern( "read" ) )
	, mySeekSym( rb_intern( "seek" ) )
	, myTellSym( rb_intern( "tell" ) )
	, mySizeSym( rb_intern( "size" ) )
	{
	}

	void Init( VALUE aSelf )
	{
		myRubySelf = aSelf;
	}
	
protected:
	VALUE myRubySelf;
	const ID myReadSym;
	const ID mySeekSym;
	const ID myTellSym;
	const ID mySizeSym;
	
	virtual sf::Int64 Read( char *aDataBuffer, sf::Int64 aSize )
	{
		VALUE buffer = rb_str_new2("");
		sf::Int64 bytesRead = NUM2LONG( rb_funcall( myRubySelf, myReadSym, 2, buffer, LONG2NUM( aSize ) ) );

		memcpy( aDataBuffer, rb_string_value_cstr( &buffer ), bytesRead );
		return bytesRead;
	}

	virtual sf::Int64 Seek( sf::Int64 aPosition )
	{
		return NUM2LONG( rb_funcall( myRubySelf, mySeekSym, 1, LONG2NUM( aPosition ) ) );
	}

	virtual sf::Int64 Tell()
	{
		return NUM2LONG( rb_funcall( myRubySelf, myTellSym, 0 ) );
	}

	virtual sf::Int64 GetSize()
	{
		return NUM2LONG( rb_funcall( myRubySelf, mySizeSym, 0 ) );
	}
};

static void InputStream_Free( rbInputStream *object )
{
	delete object;
}

VALUE globalInputStreamClass;

static VALUE InputStream_InitializeCopy( VALUE self, VALUE aSource )
{
	sf::InputStream *selfStream = NULL;
	Data_Get_Struct( self, sf::InputStream, selfStream );
	sf::InputStream *sourceStream = NULL;
	Data_Get_Struct( aSource, sf::InputStream, sourceStream );
	*selfStream = *sourceStream;
	return self;
}

static VALUE InputStream_Allocate( VALUE aKlass )
{
	rbInputStream *object = new rbInputStream();
	VALUE rbData = Data_Wrap_Struct( aKlass, 0, InputStream_Free, object );
	object->Init( rbData );
	return rbData;
}

void Init_InputStream( void )
{
/* SFML namespace which contains the classes of this module. */
	VALUE sfml = rb_define_module( "SFML" );
/* Abstract class for custom file input streams.
 *
 * This class allows users to define their own file input sources from which SFML can load resources.
 *
 * SFML resource classes like SFML::Texture and SFML::SoundBuffer provide loadFromFile functions, which read data from 
 * conventional sources. However, if you have data coming from a different source (over a network, embedded, encrypted,
 * compressed, etc) you can derive your own class from SFML::InputStream and load SFML resources with their loadFromStream function.
 *
 * Usage example:
 *
 *   # custom stream class that reads from inside a zip file
 *   class ZipStream < SFML::InputStream
 *     def initialize( archive )
 *       # Code
 *     end
 *
 *     def open( filename )
 *       # Code
 *     end
 *
 *     def read( buffer, size )
 *       # Code
 *     end
 *
 *     def seek( position )
 *       # Code
 *     end
 *
 *     def tell()
 *       # Code
 *     end
 *    
 *     def size()
 *       # Code
 *     end
 *   };
 *
 *   # now you can load textures...
 *   texture = SFML::Texture.new
 *   stream = ZipStream.new( "resources.zip" )
 *   stream.open( "images/img.png" )
 *   texture.load_from_stream( stream )
 *
 *   # musics...
 *   music = SFML::Music.new
 *   stream = ZipStream.new( "resources.zip" )
 *   stream.open( "musics/msc.ogg" )
 *   music.open_from_stream( stream )
 *
 *   # etc.
 */
	globalInputStreamClass = rb_define_class_under( sfml, "InputStream", rb_cObject );

	// Class methods
	rb_define_alloc_func( globalInputStreamClass, InputStream_Allocate );
	
	// Instance methods
	rb_define_method( globalInputStreamClass, "initialize_copy", InputStream_InitializeCopy, 1 );
	
}
