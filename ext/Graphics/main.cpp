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

#include "../Graphics.hpp"
#include "../System/SFML.hpp"

#include <SFML/Graphics.hpp>

#if !defined( RBSFML_SFML )
#include <sstream>
std::stringstream globalErrorStream;
namespace rbVector2 { VALUE Class; }
namespace rbVector3 { VALUE Class; }
namespace rbNonCopyable { VALUE Module; }
namespace rbWindow { VALUE Class; }
#endif

static inline void InitDependencies( VALUE SFML )
{
#if !defined( RBSFML_SFML )
    rbVector2::Class = rb_const_get( SFML, rb_intern( "Vector2" ) );
	rbVector3::Class = rb_const_get( SFML, rb_intern( "Vector3" ) );
	rbNonCopyable::Module = rb_const_get( SFML, rb_intern( "NonCopyable" ) );
	rbWindow::Class = rb_const_get( SFML, rb_intern( "Window" ) );
#endif
}

static inline void InitEnumerations( VALUE SFML )
{
	if( rb_const_defined( SFML, rb_intern( "BlendAlpha" ) ) == Qfalse )
	{
		rb_define_const( SFML, "BlendAlpha",    INT2FIX( sf::BlendAlpha    ) );
		rb_define_const( SFML, "BlendAdd",      INT2FIX( sf::BlendAdd      ) );
		rb_define_const( SFML, "BlendMultiply", INT2FIX( sf::BlendMultiply ) );
		rb_define_const( SFML, "BlendNone",     INT2FIX( sf::BlendNone     ) );
	
		rb_define_const( SFML, "Points",         INT2FIX( sf::Points         ) );
		rb_define_const( SFML, "Lines",          INT2FIX( sf::Lines          ) );
		rb_define_const( SFML, "LinesStrip",     INT2FIX( sf::LinesStrip     ) );
		rb_define_const( SFML, "Triangles",      INT2FIX( sf::Triangles      ) );
		rb_define_const( SFML, "TrianglesStrip", INT2FIX( sf::TrianglesStrip ) );
		rb_define_const( SFML, "TrianglesFan",   INT2FIX( sf::TrianglesFan   ) );
		rb_define_const( SFML, "Quads",          INT2FIX( sf::Quads          ) );
	}
}

extern "C"
void Init_graphics()
{
    VALUE SFML = rbSFML::Module();
    
    if( !RBOOL( rb_const_defined( SFML, rb_intern( "SYSTEM_LOADED" ) ) ) || !RBOOL( rb_const_defined( SFML, rb_intern( "WINDOW_LOADED" ) ) ) )
	{
        rb_require( "sfml/system" );
		rb_require( "sfml/window" );
	}
    
    rb_define_const( SFML, "GRAPHICS_LOADED", Qtrue );
    
    InitDependencies( SFML );
	InitEnumerations( SFML );
	
	rbColor::Init( SFML );
	rbRect::Init( SFML );
	rbGlyph::Init( SFML );
	rbImage::Init( SFML );
	rbTexture::Init( SFML );
	rbFont::Init( SFML );
	rbDrawable::Init( SFML );
	rbTransform::Init( SFML );
	rbTransformable::Init( SFML );
	rbVertex::Init( SFML );
	rbVertexArray::Init( SFML );
	rbShader::Init( SFML );
	rbRenderStates::Init( SFML );
	rbView::Init( SFML );
	rbRenderTarget::Init( SFML );
	rbRenderWindow::Init( SFML );
	rbRenderTexture::Init( SFML );
	rbSprite::Init( SFML );
	rbText::Init( SFML );
	rbShape::Init( SFML );
	rbCircleShape::Init( SFML );
	rbConvexShape::Init( SFML );
	rbRectangleShape::Init( SFML );
}
