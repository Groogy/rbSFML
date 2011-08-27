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
 
#include "Texture.hpp"
#include "Color.hpp"
#include "Rect.hpp"
#include "main.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>

VALUE globalTextureClass;

/* External classes */
extern VALUE globalImageClass;
extern VALUE globalColorClass;
extern VALUE globalRectClass;
extern VALUE globalInputStreamClass;
extern VALUE globalWindowClass;

/* Free a heap allocated object 
 * Not accessible trough ruby directly!
 */
static void Texture_Free( sf::Texture *anObject )
{
	delete anObject;
}

/* call-seq:
 *   texture.loadFromFile( filename, area = [0,0,0,0] )	-> true or false
 *
 * Load the texture from a file on disk.
 *
 * This function is a shortcut for the following code:
 *
 *   image = SFML::Image.new
 *   image.load_from_file( filename )
 *   texture.load_from_image( image, area )
 *
 * The area argument can be used to load only a sub-rectangle of the whole image. 
 * If you want the entire image then leave the default value (which is an empty IntRect). 
 * If the area rectangle crosses the bounds of the image, it is adjusted to fit the image size.
 *
 * The maximum size for a texture depends on the graphics driver and can be retrieved with the 
 * getMaximumSize function.
 *
 * If this function fails, the texture is left unchanged.
 */
static VALUE Texture_LoadFromFile( int argc, VALUE *args, VALUE self )
{
	sf::Texture *object = NULL;
	Data_Get_Struct( self, sf::Texture, object );
	
	sf::IntRect area;
	std::string filename;
	switch( argc )
	{
	case 2:
		area = Rect_ToSFMLi( Rect_ForceType( args[ 1 ] ) );
	case 1:
		filename = rb_string_value_cstr( &args[ 0 ] );
		break;
	default:
		rb_raise( rb_eArgError, "Expected 1 or 2 arguments but was given %d", argc );
	}
	
	if( object->LoadFromFile( filename, area ) == true )
	{
		return Qtrue;
	}
	else
	{
		return Qfalse;
	}
}

/* call-seq:
 *   image.loadFromImage( image, area  = [0,0,0,0] )	-> true or false
 *
 * Load the texture from an image.
 *
 * The area argument can be used to load only a sub-rectangle of the whole image. If you want
 * the entire image then leave the default value (which is an empty IntRect). If the area 
 * rectangle crosses the bounds of the image, it is adjusted to fit the image size.
 *
 * The maximum size for a texture depends on the graphics driver and can be retrieved with the 
 * getMaximumSize function.
 *
 * If this function fails, the texture is left unchanged.
 */
static VALUE Texture_LoadFromImage( int argc, VALUE *args, VALUE self )
{
	sf::Texture *object = NULL;
	Data_Get_Struct( self, sf::Texture, object );
	
	sf::IntRect area;
	sf::Image *image;
	
	switch( argc )
	{
	case 2:
		area = Rect_ToSFMLi( Rect_ForceType( args[ 1 ] ) );
	case 1:
		VALIDATE_CLASS( args[ 0 ], globalImageClass, "image" );
		Data_Get_Struct( args[ 0 ], sf::Image, image );
		break;
	default:
		rb_raise( rb_eArgError, "Expected 1 or 2 arguments but was given %d", argc );
	}
	
	if( object->LoadFromImage( *image, area ) == true )
	{
		return Qtrue;
	}
	else
	{
		return Qfalse;
	}
}

/* call-seq:
 *   texture.loadFromStream( stream, area = [0,0,0,0] )	-> true or false
 *
 * Load the texture from a file in memory.
 *
 * This function is a shortcut for the following code:
 *
 *   sf::Image image;
 *   image.LoadFromStream(stream);
 *   texture.LoadFromImage(image, area);
 *
 * The area argument can be used to load only a sub-rectangle of the whole image. If you want the entire image
 * then leave the default value (which is an empty IntRect). If the area rectangle crosses the bounds of the 
 * image, it is adjusted to fit the image size.
 *
 * The maximum size for a texture depends on the graphics driver and can be retrieved with the getMaximumSize
 * function.
 *
 * If this function fails, the texture is left unchanged.
 */
static VALUE Texture_LoadFromStream( int argc, VALUE *args, VALUE self )
{
	sf::Texture *object = NULL;
	Data_Get_Struct( self, sf::Texture, object );
	
	sf::IntRect area;
	sf::InputStream *stream;
	
	switch( argc )
	{
	case 2:
		area = Rect_ToSFMLi( Rect_ForceType( args[ 1 ] ) );
	case 1:
		VALIDATE_CLASS( args[ 0 ], globalInputStreamClass, "stream" );
		Data_Get_Struct( args[ 0 ], sf::InputStream, stream );
		break;
	default:
		rb_raise( rb_eArgError, "Expected 1 or 2 arguments but was given %d", argc );
	}
	
	if( object->LoadFromStream( *stream, area ) == true )
	{
		return Qtrue;
	}
	else
	{
		return Qfalse;
	}
}

/* call-seq:
 *   texture.create( width, height )	-> true or false
 *
 * Create the texture.
 */
static VALUE Texture_Create( VALUE self, VALUE aWidth, VALUE aHeight )
{
	sf::Texture *object = NULL;
	Data_Get_Struct( self, sf::Texture, object );
	
	unsigned int width = 0;
	unsigned int height = 0;
	
	width = NUM2UINT( aWidth );
	height = NUM2UINT( aHeight );
	
	return ( object->Create( width, height ) == true ? Qtrue : Qfalse );
}

/* call-seq:
 *   texture.bind()
 *
 * Activate the texture for rendering.
 *
 * This function is mainly used internally by the SFML render system. However it can be useful when
 * using SFML::Texture together with OpenGL code (it calls glBindTexture). 
 */
static VALUE Texture_Bind( VALUE self )
{
	sf::Texture *object = NULL;
	Data_Get_Struct( self, sf::Texture, object );
	object->Bind();
	return Qnil;
}

/* call-seq:
 *   texture.setSmooth( smooth )
 *
 * Enable or disable the smooth filter.
 *
 * When the filter is activated, the texture appears smoother so that pixels are less noticeable. However if you want 
 * the texture to look exactly the same as its source file, you should disable it. The smooth filter is enabled 
 * by default.
 */
static VALUE Texture_SetSmooth( VALUE self, VALUE aSmoothFlag )
{
	sf::Texture *object = NULL;
	Data_Get_Struct( self, sf::Texture, object );
	
	if( aSmoothFlag == Qtrue )
	{
		object->SetSmooth( true );
	}
	else if( aSmoothFlag == Qfalse )
	{
		object->SetSmooth( false );
	}
	else
	{
		VALIDATE_CLASS( aSmoothFlag, rb_cTrueClass, "smoothFlag" );
	}
	return Qnil;
}

/* call-seq:
 *   texture.isSmooth()	-> true or false
 *
 * Tell whether the smooth filter is enabled or not. 
 */
static VALUE Texture_IsSmooth( VALUE self )
{
	sf::Texture *object = NULL;
	Data_Get_Struct( self, sf::Texture, object );
	return ( object->IsSmooth() == true ? Qtrue : Qfalse );
}

/* call-seq:
 *   texture.getWidth()	-> width
 *
 * Return the width of the texture. 
 */
static VALUE Texture_GetWidth( VALUE self )
{
	sf::Texture *object = NULL;
	Data_Get_Struct( self, sf::Texture, object );
	return INT2FIX( object->GetWidth() );
}

/* call-seq:
 *   texture.getHeight()	-> height
 *
 * Return the height of the texture. 
 */
static VALUE Texture_GetHeight( VALUE self )
{
	sf::Texture *object = NULL;
	Data_Get_Struct( self, sf::Texture, object );
	return INT2FIX( object->GetHeight() );
}

/* call-seq:
 *   texture.copyToImage()	-> image
 *
 * Copy the texture pixels to an image.
 *
 * This function performs a slow operation that downloads the texture's pixels from the
 * graphics card and copies them to a new image, potentially applying transformations to 
 * pixels if necessary (texture may be padded or flipped).
 *
 */
static VALUE Texture_CopyToImage( VALUE self )
{
	sf::Texture *object = NULL;
	Data_Get_Struct( self, sf::Texture, object );

	VALUE image = rb_funcall( globalImageClass, rb_intern( "new" ), 0 );
	sf::Image *imagePtr = NULL;
	Data_Get_Struct( image, sf::Image, imagePtr );
	*imagePtr = object->CopyToImage();

	return image;
}

/* call-seq:
 *   texture.update( pixels )
 *	 texture.update( pixels, width, height, x, y )
 *   texture.update( image )
 *   texture.update( image, x, y )
 *   texture.update( window )
 *   texture.update( window, x, y )
 * 
 * Update the pixels of the texture.
 *
 * This method has several overloads in C++ so there are several different possible argument lists
 * for it in rbSFML. 
 *
 * If a single argument is passed the whole texture is updated. If an array is passed it is assumed 
 * to be pixels as 8bit integers representing 32bit colors. Otherwise if an image or window object is 
 * passed then these are used instead.
 *
 * If further arguments are passed with pixels, image or window then only a part of the texture will
 * be updated by the source.
 *
 * For pixels the memory must be as this:
 *   [ r1, g1, b1, a1, r2, g2, ... ]
 * But the array is flattened first so you can arrange it as this as well:
 *   [ [ r1, g1, b1, a1 ], [ r2, g2, b2, a2 ], ... ]
 */
static VALUE Texture_Update( int argc, VALUE *args, VALUE self )
{
	sf::Texture *object = NULL;
	Data_Get_Struct( self, sf::Texture, object );

	switch( argc )
	{
	case 5:
		{
			VALIDATE_CLASS( args[ 0 ], rb_cArray, "pixels" );
			VALUE pixels = rb_funcall( args[ 0 ], rb_intern("flatten"), 0 );
			const unsigned int width = FIX2UINT( args[ 1 ] );
			const unsigned int height = FIX2UINT( args[ 2 ] );
			const unsigned int dataSize = width * height * 4;
			if( RARRAY_LEN( pixels ) < dataSize )
				return Qnil;
			
			sf::Uint8 * const tempData = new sf::Uint8[ dataSize ];
			for(unsigned long index = 0; index < dataSize; index++)
			{
				sf::Uint8 val = NUM2CHR( rb_ary_entry( pixels, index ) );
				tempData[index] = val;
			}
			
			object->Update( tempData, width, height, FIX2UINT( args[ 3 ] ), FIX2UINT( args[ 4 ] ) );
			delete[] tempData;
		}
		break;
	case 3:
		{
			if( rb_obj_is_kind_of( args[ 0 ], rb_cArray ) == true )
			{
				rb_raise( rb_eArgError, "Expected 1 or 5 arguments but was given %d", argc );
			}
			else if( rb_obj_is_kind_of( args[ 0 ], globalWindowClass ) == true )
			{
				sf::Window *window = NULL;
				Data_Get_Struct( args[ 0 ], sf::Window, window );
				object->Update( *window, FIX2UINT( args[ 1 ] ), FIX2UINT( args[ 2 ] ) );
			}
			else if( rb_obj_is_kind_of( args[ 0 ], globalImageClass ) == true )
			{
				sf::Image *image = NULL;
				Data_Get_Struct( args[ 0 ], sf::Image, image );
				object->Update( *image, FIX2UINT( args[ 1 ] ), FIX2UINT( args[ 2 ] ) );
			}
		}
		break;
	case 1:
		{
			if( rb_obj_is_kind_of( args[ 0 ], rb_cArray ) == true )
			{
				VALUE pixels = rb_funcall( args[ 0 ], rb_intern("flatten"), 0 );

				const unsigned long dataSize = RARRAY_LEN( pixels );
				sf::Uint8 * const tempData = new sf::Uint8[ dataSize ];
				for(unsigned long index = 0; index < dataSize; index++)
				{
					sf::Uint8 val = NUM2CHR( rb_ary_entry( pixels, index ) );
					tempData[index] = val;
				}
				
				object->Update( tempData );
				delete[] tempData;
			}
			else if( rb_obj_is_kind_of( args[ 0 ], globalWindowClass ) == true )
			{
				sf::Window *window = NULL;
				Data_Get_Struct( args[ 0 ], sf::Window, window );
				object->Update( *window );
			}
			else if( rb_obj_is_kind_of( args[ 0 ], globalImageClass ) == true )
			{
				sf::Image *image = NULL;
				Data_Get_Struct( args[ 0 ], sf::Image, image );
				object->Update( *image );
			}
			else
			{
				VALUE typeName = rb_funcall( CLASS_OF( args[ 0 ] ), rb_intern( "to_s" ), 0 );
				rb_raise( rb_eTypeError, "Expected first argument to be either Array, SFML::Window or SFML::Image but was given %s", rb_string_value_cstr( &typeName ) );
			}
		}
		break;
	default:
		rb_raise( rb_eArgError, "Expected 1, 3 or 5 arguments but was given %d", argc );
	}

	return Qnil;
}

/* call-seq:
 *   texture.getTexCoords( rectangle )	-> tex coordinates rectangle
 *
 * Convert a rectangle of pixels into texture coordinates.
 *
 * This function is used by code that needs to map the texture to some OpenGL geometry. It converts the source 
 * rectangle, expressed in pixels, to float coordinates in the range [0, 1].
 */
static VALUE Texture_GetTexCoords( VALUE self, VALUE aRectangle )
{
	VALUE rubyRectangle = Rect_ForceType( aRectangle );
	sf::IntRect rectangle;
	rectangle.Left = FIX2INT( Rect_GetLeft( aRectangle ) );
	rectangle.Top = FIX2INT( Rect_GetTop( aRectangle ) );
	rectangle.Width = FIX2INT( Rect_GetWidth( aRectangle ) );
	rectangle.Height = FIX2INT( Rect_GetHeight( aRectangle ) );
	
	sf::Texture *object = NULL;
	Data_Get_Struct( self, sf::Texture, object );
	
	sf::FloatRect result = object->GetTexCoords( rectangle );
	return rb_funcall( globalRectClass, rb_intern( "new" ), 4, 
					rb_float_new( result.Left ), rb_float_new( result.Top ), 
					rb_float_new( result.Width ), rb_float_new( result.Height ) );
}

/* call-seq:
 *   Texture.new()					-> texture
 *   Texture.new( filename )		-> texture
 *   Texture.new( width, height )	-> texture
 *
 * Will create a new texture instance.
 * 
 * If a filename argument is specified then Texture#loadFromFile will be called on the created instance. If width, height
 * are specified then Image#create will be called on the created instance. 
 */
static VALUE Texture_Initialize( int argc, VALUE *args, VALUE self )
{
	switch( argc )
	{
	case 2:
		rb_funcall2( self, rb_intern( "create" ), argc, args );
		break;
	case 1:
		if( rb_obj_is_kind_of( args[ 0 ], globalImageClass ) == Qtrue )
		{
			rb_funcall2( self, rb_intern( "loadFromImage" ), argc, args );
		}
		else
		{
			rb_funcall2( self, rb_intern( "loadFromFile" ), argc, args );
		}
		break;
	case 0:
		break;
	default:
		rb_raise( rb_eArgError, "Expected 0, 1 or 2 arguments but was given %d", argc );
	}
	return self;
}

static VALUE Texture_InitializeCopy( VALUE self, VALUE aSource )
{
	sf::Texture *object = NULL;
	Data_Get_Struct( self, sf::Texture, object );
	sf::Texture *source = NULL;
	Data_Get_Struct( aSource, sf::Texture, source );
	*object = *source;
}

static VALUE Texture_Alloc( VALUE aKlass )
{
	sf::Texture *object = new sf::Texture();
	return Data_Wrap_Struct( aKlass, 0, Texture_Free, object );
}

/* call-seq:
 *   Texture.getMaximumSize()	-> size
 *
 * Get the maximum image size allowed.
 *
 * This maximum size is defined by the graphics driver. You can expect a value of 512 pixels for low-end graphics 
 * card, and up to 8192 pixels for newer hardware.
 */
static VALUE Texture_GetMaximumSize( VALUE aKlass )
{
	return INT2FIX( sf::Texture::GetMaximumSize() );
}

void Init_Texture( void )
{
/* SFML namespace which contains the classes of this module. */
	VALUE sfml = rb_define_module( "SFML" );
/* Image living on the graphics card that can be used for drawing.
 *
 * SFML::Texture stores pixels that can be drawn, with a sprite for example.
 *
 * A texture lives in the graphics card memory, therefore it is very fast to draw a texture
 * to a render target, or copy a render target to a texture (the graphics card can access both
 * directly).
 *
 * Being stored in the graphics card memory has some drawbacks. A texture cannot be manipulated 
 * as freely as a sf::Image, you need to prepare the pixels first and then upload them to the 
 * texture in a single operation (see Texture::Update).
 *
 * sf::Texture makes it easy to convert from/to sf::Image, but keep in mind that these calls require
 * transfers between the graphics card and the central memory, therefore they are slow operations.
 *
 * A texture can be loaded from an image, but also directly from a file/memory/stream. The necessary 
 * shortcuts are defined so that you don't need an image first for the most common cases. However, 
 * if you want to perform some modifications on the pixels before creating the final texture, you can
 * load your file to a sf::Image, do whatever you need with the pixels, and then call 
 * Texture::LoadFromImage.
 *
 * Since they live in the graphics card memory, the pixels of a texture cannot be accessed without a
 * slow copy first. And they cannot be accessed individually. Therefore, if you need to read the 
 * texture's pixels (like for pixel-perfect collisions), it is recommended to store the collision 
 * information separately, for example in an array of booleans.
 *
 * Like sf::Image, sf::Texture can handle a unique internal representation of pixels, which is 
 * RGBA 32 bits. This means that a pixel must be composed of 8 bits red, green, blue and alpha 
 * channels -- just like a sf::Color.
 *
 * Usage example:
 *
 *   # This example shows the most common use of sf::Texture:
 *   # drawing a sprite
 *
 *   # Load a texture from a file
 *   texture = SFML::Texture.new
 *   if texture.load_from_file( "texture.png" ) == false
 *     return -1
 *
 *   # Assign it to a sprite
 *   sprite = SFML::Sprite.new
 *   sprite.texture = texture
 *
 *   # Draw the textured sprite
 *   window.draw( sprite ) # window is a SFML::RenderWindow
 *
 *   # This example shows another common use of SFML::Texture:
 *   # streaming real-time data, like video frames
 *
 *   # Create an empty texture
 *   texture = SFML::Texture.new
 *   if texture.create( 640, 480 ) == false
 *     return -1
 *
 *   # Create a sprite that will display the texture
 *   sprite = SFML::Sprite.new( texture )
 *
 *   while ... # the main loop
 *   
 *     ...
 *
 *     # update the texture
 *     pixels = ... # get a fresh chunk of pixels (the next frame of a movie, for example)
 *     texture.update( pixels )
 *
 *     # draw it
 *     window.draw( sprite )
 *
 *     ...
 *   end
 *
 */
	globalTextureClass = rb_define_class_under( sfml, "Texture", rb_cObject );
	
	// Class methods
	rb_define_alloc_func( globalTextureClass, Texture_Alloc );
	rb_define_singleton_method( globalTextureClass, "getMaximumSize", Texture_GetMaximumSize, 0 );
	
	// Instance methods
	rb_define_method( globalTextureClass, "initialize", Texture_Initialize, -1 );
	rb_define_method( globalTextureClass, "initialize_copy", Texture_InitializeCopy, 1 );
	rb_define_method( globalTextureClass, "loadFromFile", Texture_LoadFromFile, -1 );
	rb_define_method( globalTextureClass, "loadFromImage", Texture_LoadFromImage, -1 );
	rb_define_method( globalTextureClass, "create", Texture_Create, 2 );
	rb_define_method( globalTextureClass, "bind", Texture_Bind, 0 );
	rb_define_method( globalTextureClass, "setSmooth", Texture_SetSmooth, 1 );
	rb_define_method( globalTextureClass, "isSmooth", Texture_IsSmooth, 0 );
	rb_define_method( globalTextureClass, "getWidth", Texture_GetWidth, 0 );
	rb_define_method( globalTextureClass, "getHeight", Texture_GetHeight, 0 );
	rb_define_method( globalTextureClass, "copyToImage", Texture_CopyToImage, 0 );
	rb_define_method( globalTextureClass, "update", Texture_Update, -1 );
	rb_define_method( globalTextureClass, "getTexCoords", Texture_GetTexCoords, 1 );
	
	// Class aliases
	rb_define_alias( CLASS_OF( globalTextureClass ), "maximumSize", "getMaximumSize" );
	rb_define_alias( CLASS_OF( globalTextureClass ), "maximum_size", "getMaximumSize" );
	rb_define_alias( CLASS_OF( globalTextureClass ), "get_maximum_size", "getMaximumSize" );
	
	// Instance Aliases
	rb_define_alias( globalTextureClass, "load_from_file", "loadFromFile" );
	rb_define_alias( globalTextureClass, "loadFile", "loadFromFile" );
	rb_define_alias( globalTextureClass, "load_file", "loadFromFile" );
	
	rb_define_alias( globalTextureClass, "load_from_image", "loadFromImage" );
	rb_define_alias( globalTextureClass, "loadImage", "loadFromImage" );
	rb_define_alias( globalTextureClass, "load_image", "loadFromImage" );
	
	rb_define_alias( globalTextureClass, "set_smooth", "setSmooth" );
	rb_define_alias( globalTextureClass, "smooth=", "setSmooth" );
	
	rb_define_alias( globalTextureClass, "isSmooth?", "isSmooth" );
	rb_define_alias( globalTextureClass, "get_smooth", "isSmooth" );
	rb_define_alias( globalTextureClass, "is_smooth", "isSmooth" );
	rb_define_alias( globalTextureClass, "is_smooth?", "isSmooth" );
	rb_define_alias( globalTextureClass, "smooth?", "isSmooth" );
	rb_define_alias( globalTextureClass, "smooth", "isSmooth" );
	
	rb_define_alias( globalTextureClass, "get_width", "getWidth" );
	rb_define_alias( globalTextureClass, "width", "getWidth" );
	
	rb_define_alias( globalTextureClass, "get_height", "getHeight" );
	rb_define_alias( globalTextureClass, "height", "getHeight" );

	rb_define_alias( globalTextureClass, "copy_to_image", "copyToImage" );
	rb_define_alias( globalTextureClass, "toImage", "copyToImage" );
	rb_define_alias( globalTextureClass, "to_image", "copyToImage" );
	
	rb_define_alias( globalTextureClass, "get_tex_coords", "getTexCoords" );
}
