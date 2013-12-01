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

#include "../Extra.hpp"
#include "../System/SFML.hpp"

#include <SFML/Graphics.hpp>

#include <GL/glew.h>

#if !defined( RBSFML_SFML )
#include <sstream>
std::stringstream globalErrorStream;
namespace rbVector2 { VALUE Class; }
namespace rbVector3 { VALUE Class; }
namespace rbNonCopyable { VALUE Module; }
namespace rbDrawable { VALUE Module; }
namespace rbTransformable { VALUE Module; }
namespace rbTexture { VALUE Class; }
#endif

static inline void InitDependencies( VALUE SFML )
{
#if !defined( RBSFML_SFML )
  rbVector2::Class = rb_const_get( SFML, rb_intern( "Vector2" ) );
	rbVector3::Class = rb_const_get( SFML, rb_intern( "Vector3" ) );
	rbNonCopyable::Module = rb_const_get( SFML, rb_intern( "NonCopyable" ) );
	rbDrawable::Module = rb_const_get( SFML, rb_intern( "Drawable" ) );
	rbTransformable::Module = rb_const_get( SFML, rb_intern( "Transformable" ) );
  rbTexture::Class = rb_const_get( SFML, rb_intern( "Texture" ) );
#endif
}

static VALUE LoadOpenGL( VALUE aSelf )
{
	bool result = true;
	rbSFML::PrepareErrorStream();
	
	GLenum err = glewInit();
  if(GLEW_OK != err)
  {
    const char* error = reinterpret_cast<const char*>(glewGetErrorString(err));
    sf::err() << "Error: " << error << std::endl;
    result = false;
  }

    if(!GLEW_VERSION_3_3)
    {
      sf::err() << "Error: Does not support OpenGL 3.3" << std::endl;
      result = false;
    }
	rbSFML::CheckRaise();
	return result ? Qtrue : Qfalse;
}

extern "C"
void Init_extra()
{
    VALUE SFML = rbSFML::Module();
    
    if( !RBOOL( rb_const_defined( SFML, rb_intern( "SYSTEM_LOADED" ) ) ) || 
		!RBOOL( rb_const_defined( SFML, rb_intern( "WINDOW_LOADED" ) ) ) || 
		!RBOOL( rb_const_defined( SFML, rb_intern( "GRAPHICS_LOADED" ) ) ) )
	{
        rb_require( "sfml/system" );
		rb_require( "sfml/window" );
		rb_require( "sfml/graphics" );
	}
    
    rb_define_const( SFML, "EXTRA_LOADED", Qtrue );
    
    InitDependencies( SFML );
	
	rbVertexLayout::Init( SFML );
	rbVertexBufferObject::Init( SFML );
  rbEffect::Init( SFML );
	
	ext_define_module_function( SFML, "load_opengl", LoadOpenGL, 0 );
}
