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
 
#include "RenderTexture.hpp"
#include "main.hpp"
#include <SFML/Graphics/RenderTexture.hpp>

VALUE globalRenderTextureClass;

/* External classes */
extern VALUE globalRenderTargetModule;
extern VALUE globalTextureClass;
extern VALUE globalDrawableModule;
extern VALUE globalShaderClass;
extern VALUE globalViewClass;

static void RenderTexture_Free( sf::RenderTexture *anObject )
{
	delete anObject;
}

static void View_Free( sf::View *anObject )
{
	delete anObject;
}

/* call-seq:
 *   render_texture.create( width, height, depthBuffer = false )	-> true or false
 *
 * Create the render-texture.
 *
 * Before calling this function, the render-texture is in an invalid state, thus it is mandatory to call it before 
 * doing anything with the render-texture. The last parameter, depthBuffer, is useful if you want to use the render-texture
 * for 3D OpenGL rendering that requires a depth-buffer. Otherwise it is unnecessary, and you should leave this 
 * parameter to false (which is its default value).
 */
static VALUE RenderTexture_Create( int argc, VALUE *args, VALUE self )
{
	unsigned int width = 0;
	unsigned int height = 0;
	bool depthBuffer = false;
	switch( argc )
	{
		case 3:
			if( args[2] == Qtrue )
			{
				depthBuffer = true;
			}
			else if( args[2] == Qfalse )
			{
				depthBuffer = false;
			}
			else
			{
				VALIDATE_CLASS( args[2], rb_cTrueClass, "depthBuffer" );
			}
		case 2:
			width  = FIX2UINT( args[0] );
			height = FIX2UINT( args[1] );
			break;
		default:
			rb_raise( rb_eArgError, "Expected 2 or 3 arguments but was given %d", argc );
	}
	
	sf::RenderTexture *object = NULL;
	Data_Get_Struct( self, sf::RenderTexture, object );
	if( object->Create( width, height, depthBuffer ) == true )
	{
		return Qtrue;
	}
	else
	{
		return Qfalse;
	}
}

static VALUE RenderTexture_Draw( int argc, VALUE *args, VALUE self )
{
	sf::RenderTexture *object = NULL;
	Data_Get_Struct( self, sf::RenderTexture, object );
	switch( argc )
	{
		case 2:
		{
			VALIDATE_CLASS( args[0], globalDrawableModule, "object" );
			VALIDATE_CLASS( args[1], globalShaderClass, "shader" );
			sf::Drawable *drawable = NULL;
			Data_Get_Struct( args[0], sf::Drawable, drawable );
			sf::Shader *shader = NULL;
			Data_Get_Struct( args[1], sf::Shader, shader );
			object->Draw( *drawable, *shader );
			break;
		}
		case 1:
		{
			VALIDATE_CLASS( args[0], globalDrawableModule, "object" );
			sf::Drawable *drawable = NULL;
			Data_Get_Struct( args[0], sf::Drawable, drawable );
			object->Draw( *drawable );
			break;
		}
		default:
			rb_raise( rb_eArgError, "Expected 1 or 2 arguments but was given %d", argc );
	}
	return Qnil;
}

/* call-seq:
 *   render_texture.display()
 *
 * Update the contents of the target texture.
 *
 * This function updates the target texture with what has been drawn so far. Like for windows, calling this function is
 * mandatory at the end of rendering. Not calling it may leave the image in an undefined state. 
 */
static VALUE RenderTexture_Display( VALUE self )
{
	sf::RenderTexture *object = NULL;
	Data_Get_Struct( self, sf::RenderTexture, object );
	object->Display();
	return Qnil;
}

/* call-seq:
 *   render_texture.getTexture()	-> texture
 *
 * Get a read-only reference to the target texture.
 *
 * After drawing to the render-texture and calling display, you can retrieve the updated texture using this function, and 
 * draw it using a sprite (for example). The internal SFML::Texture of a render-texture is always the same instance, so that
 * it is possible to call this function once and keep a reference to the texture even after is it modified.
 */
static VALUE RenderTexture_GetTexture( VALUE self )
{
	sf::RenderTexture *object = NULL;
	Data_Get_Struct( self, sf::RenderTexture, object );
	const sf::Texture &texture = object->GetTexture();
	VALUE rbData = Data_Wrap_Struct( globalTextureClass, 0, 0, const_cast< sf::Texture * >( &texture ) );
	rb_obj_call_init( rbData, 0, 0 );
	rb_iv_set( rbData, "@__owner_ref", self );
	return rbData;
}

/* call-seq:
 *   render_texture.isSmooth()	-> true or false
 *
 * Tell whether the smooth filtering is enabled or not. 
 */
static VALUE RenderTexture_IsSmooth( VALUE self )
{
	sf::RenderTexture *object = NULL;
	Data_Get_Struct( self, sf::RenderTexture, object );
	return ( object->IsSmooth() == true ? Qtrue : Qfalse );
}

/* call-seq:
 *   render_texture.setActive( active )
 *
 * Activate of deactivate the render-texture for rendering.
 *
 * This function makes the render-texture's. context current for future OpenGL rendering operations (so you shouldn't 
 * care about it if you're not doing direct OpenGL stuff). Only one context can be current on a thread, so if you want
 * to draw OpenGL geometry to another render target (like a RenderWindow) don't forget to activate it again.
 */
static VALUE RenderTexture_SetActive( int argc, VALUE *args, VALUE self )
{
	sf::RenderTexture *object = NULL;
	Data_Get_Struct( self, sf::RenderTexture, object );
	bool flag = true;
	switch( argc )
	{
		case 1:
			if( args[0] == Qtrue )
			{
				flag = true;
			}
			else if( args[0] == Qfalse )
			{
				flag = false;
			}
			else
			{
				VALIDATE_CLASS( args[0], rb_cTrueClass, "active" );
			}
		case 0:
			break;
		default:
			rb_raise( rb_eArgError, "Expected 0 or 1 arguments but was given %d", argc );	
	}
	object->SetActive( flag );
	return Qnil;
}

/* call-seq:
 *   render_texture.setSmooth( smooth )
 *
 * Enable or disable image smoothing.
 *
 * This function is similar to SFML::Texture#setSmooth. This parameter is enabled by default.
 */
static VALUE RenderTexture_SetSmooth( VALUE self, VALUE aSmoothFlag )
{
	sf::RenderTexture *object = NULL;
	Data_Get_Struct( self, sf::RenderTexture, object );
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
		VALIDATE_CLASS( aSmoothFlag, rb_cTrueClass, "smooth" );
	}
	return Qnil;
}

/* call-seq:
 *   render_texture.setView( view )
 *
 * Change the current active view.
 *
 * The new view will affect everything that is drawn, until another view is activated. The render image keeps its own
 * copy of the view object, so it is not necessary to keep the original one alive as long as it is in use. To restore
 * the original view of the rendertexture, you can pass the result of getDefaultView() to this function.
 */
static VALUE RenderTexture_SetView( VALUE self, VALUE aView )
{
	VALIDATE_CLASS( aView, globalViewClass, "view" );
	sf::View *view = NULL;
	sf::RenderTexture *object = NULL;
	Data_Get_Struct( self, sf::RenderTexture, object );
	Data_Get_Struct( aView, sf::View, view );
	object->SetView( *view );
	return Qnil;
}

/* call-seq:
 *   render_texture.getView()	-> view
 *
 * Retrieve the view currently in use in the render texture.
 */
static VALUE RenderTexture_GetView( VALUE self )
{
	sf::RenderTexture *object = NULL;
	Data_Get_Struct( self, sf::RenderTexture, object );
	const sf::View &original = object->GetView();
	sf::View * view = new sf::View( original );
	VALUE rbData = Data_Wrap_Struct( globalViewClass, 0, View_Free, view );
	rb_obj_call_init( rbData, 0, 0 );
	return rbData;
}

/* call-seq:
 *   render_texture.getDefaultView()	-> view
 *
 * Get the default view of the render texture.
 *
 * The default view has the initial size of the render target, and never changes after the target has been created.
 */
static VALUE RenderTexture_GetDefaultView( VALUE self )
{
	sf::RenderTexture *object = NULL;
	Data_Get_Struct( self, sf::RenderTexture, object );
	const sf::View &original = object->GetDefaultView();
	sf::View *view = new sf::View( original );
	VALUE rbData = Data_Wrap_Struct( globalViewClass, 0, View_Free, view );
	rb_obj_call_init( rbData, 0, 0 );
	return rbData;
}

/* call-seq:
 *   render_texture.getWidth	-> fixnum
 *
 * Get the width of the render texture.
 */
static VALUE RenderTexture_GetWidth( VALUE self )
{
	sf::RenderTexture *object = NULL;
	Data_Get_Struct( self, sf::RenderTexture, object );
	return INT2FIX( object->GetWidth() );
}

/* call-seq:
 *   render_texture.getHeight	-> fixnum
 *
 * Get the height of the render texture.
 */
static VALUE RenderTexture_GetHeight( VALUE self )
{
	sf::RenderTexture *object = NULL;
	Data_Get_Struct( self, sf::RenderTexture, object );
	return INT2FIX( object->GetHeight() );
}

/* call-seq:
 *   RenderTexture.new()										-> render_texture
 *   RenderTexture.new( width, height, depthBuffer = false )	-> render_texture
 *
 * Will create a new render texture instance.
 * 
 * If any arguments are specified then a call to the #create method will be made passing the arguments to it.
 */
static VALUE RenderTexture_Initialize( int argc, VALUE *args, VALUE self )
{
	if( argc > 0 )
	{
		rb_funcall2( self, rb_intern( "create" ), argc, args );
	}
	return self;
}

static VALUE RenderTexture_Alloc( VALUE aKlass )
{
	sf::RenderTexture *object = new sf::RenderTexture();
	return Data_Wrap_Struct( aKlass, 0, RenderTexture_Free, object );
}

void Init_RenderTexture( void )
{
/* SFML namespace which contains the classes of this module. */
	VALUE sfml = rb_define_module( "SFML" );
/* Target for off-screen 2D rendering into a texture.
 *
 * sf::RenderTexture is the little brother of sf::RenderWindow.
 *
 * It implements the same 2D drawing and OpenGL-related functions (see their base class sf::RenderTarget for 
 * more details), the difference is that the result is stored in an off-screen image rather than being show in a window.
 *
 * Rendering to an image can be useful in a variety of situations:
 *
 *   - precomputing a complex static image (like a level's background from multiple tiles)
 *   - applying post-effects to the whole scene with shaders
 *   - creating a sprite from a 3D object rendered with OpenGL
 *   - etc.
 *
 * Usage example:
 *
 *   # Create a new render-window
 *   window = SFML::RenderWindow.new( SFML::VideoMode.new(800, 600), "SFML window" )
 *
 *   # Create a new render-texture
 *   image = SFML::RenderTexture.new
 *   if image.create( 500, 500 ) == false
 *     # Handle error
 *   end
 *
 *   # The main loop
 *   while window.open?
 *     # Event processing
 *     # ...
 *
 *     # Clear the whole image with red color
 *     image.clear( SFML::Color::Red )
 *
 *     # Draw stuff to the image
 *     image.draw( sprite )  # sprite is a SFML::Sprite
 *     image.draw( shape )   # shape is a SFML::Shape
 *     image.draw( text )    # text is a SFML::Text
 *
 *     # We're done drawing to the image
 *     image.display()
 *
 *     # Now we start rendering to the window, clear it first
 *     window.clear()
 *
 *     # Draw the image
 *     sprite = SFML::Sprite.new( image.getTexture() )
 *     window.draw( sprite )
 *
 *     # End the current frame and display its contents on screen
 *     window.display()
 *   end
 *
 * Like SFML::RenderWindow, SFML::RenderTexture is still able to render direct OpenGL stuff. It is even possible to mix
 * together OpenGL calls and regular SFML drawing commands. If you need a depth buffer for 3D rendering, don't 
 * forget to request it when calling SFML::RenderTexture#create.
 */
 	globalRenderTextureClass	= rb_define_class_under( sfml, "RenderTexture", rb_cObject );
	rb_include_module( globalRenderTextureClass, globalRenderTargetModule );
	
	// Class methods
	rb_define_alloc_func( globalRenderTextureClass, RenderTexture_Alloc );
	
	// Instance methods
	rb_define_method( globalRenderTextureClass, "initialize", RenderTexture_Initialize, -1 );
	rb_define_method( globalRenderTextureClass, "draw", RenderTexture_Draw, -1 );
	rb_define_method( globalRenderTextureClass, "create", RenderTexture_Create, -1 );
	rb_define_method( globalRenderTextureClass, "display", RenderTexture_Display, 0 );
	rb_define_method( globalRenderTextureClass, "getTexture", RenderTexture_GetTexture, 0 );
	rb_define_method( globalRenderTextureClass, "isSmooth", RenderTexture_IsSmooth, 0 );
	rb_define_method( globalRenderTextureClass, "setActive", RenderTexture_SetActive, -1 );
	rb_define_method( globalRenderTextureClass, "setSmooth", RenderTexture_SetSmooth, 1 );
	rb_define_method( globalRenderTextureClass, "getView", RenderTexture_GetView, 0 );
	rb_define_method( globalRenderTextureClass, "setView", RenderTexture_SetView, 1 );
	rb_define_method( globalRenderTextureClass, "getDefaultView", RenderTexture_GetDefaultView, 0 );
	rb_define_method( globalRenderTextureClass, "getWidth", RenderTexture_GetWidth, 0 );
	rb_define_method( globalRenderTextureClass, "getHeight", RenderTexture_GetHeight, 0 );
	
	// Instance Aliases
	rb_define_alias( globalRenderTextureClass, "get_texture", "getTexture" );
	rb_define_alias( globalRenderTextureClass, "texture", "getTexture" );
	
	rb_define_alias( globalRenderTextureClass, "is_smooth", "isSmooth" );
	rb_define_alias( globalRenderTextureClass, "smooth?", "isSmooth" );
	rb_define_alias( globalRenderTextureClass, "smooth", "isSmooth" );
	rb_define_alias( globalRenderTextureClass, "get_smooth", "isSmooth" );
	
	rb_define_alias( globalRenderTextureClass, "set_active", "setActive" );
	rb_define_alias( globalRenderTextureClass, "activate", "setActive" );
	rb_define_alias( globalRenderTextureClass, "active=", "setActive" );
	
	rb_define_alias( globalRenderTextureClass, "smooth=", "setSmooth" );
	rb_define_alias( globalRenderTextureClass, "set_smooth", "setSmooth" );
	
	rb_define_alias( globalRenderTextureClass, "view=", "setView" );
	rb_define_alias( globalRenderTextureClass, "set_view", "setView" );
	
	rb_define_alias( globalRenderTextureClass, "view", "getView" );
	rb_define_alias( globalRenderTextureClass, "get_view", "getView" );
	
	rb_define_alias( globalRenderTextureClass, "defaultView", "getDefaultView" );
	rb_define_alias( globalRenderTextureClass, "default_view", "getDefaultView" );
	rb_define_alias( globalRenderTextureClass, "get_default_view", "getDefaultView" );
	
	rb_define_alias( globalRenderTextureClass, "width", "getWidth" );
	rb_define_alias( globalRenderTextureClass, "get_width", "getWidth" );
	
	rb_define_alias( globalRenderTextureClass, "height", "getHeight" );
	rb_define_alias( globalRenderTextureClass, "get_height", "getHeight" );
}
	