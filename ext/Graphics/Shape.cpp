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

#define GRAPHICS_SHAPE_CPP

#include "Shape.hpp"
#include "Drawable.hpp"
#include "Transformable.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "Rect.hpp"
#include "Color.hpp"
#include "System/Vector2.hpp"

class rbInternalShape : public sf::Shape
{
public:
	rbInternalShape()
	{
		mySelf = Qnil;
		myGetPointCountID = rb_intern( "get_point_count" );
		myGetPointID      = rb_intern( "get_point" );
	}
	
	void SetSelf( VALUE aSelf )
	{
		mySelf = aSelf;
	}
	
	unsigned int getPointCount() const
	{
		return NUM2UINT( rb_funcall( mySelf, myGetPointCountID, 0 ) );
	}
	
	sf::Vector2f getPoint( unsigned int anIndex ) const
	{
		return rbVector2::ToSFMLf( rb_funcall( mySelf, myGetPointID, 1, INT2FIX( anIndex ) ) );
	}
	
private:
	VALUE mySelf;
	ID myGetPointCountID;
	ID myGetPointID;
};

static VALUE rbInternalAllocateShape( VALUE aKlass )
{
	rbInternalShape* shape = rbMacros::Allocate< rbInternalShape >();
	VALUE object = rbMacros::ToRuby( shape, rbShape::Class );
	shape->SetSelf( object );
	return object;
}

void rbShape::Init( VALUE SFML )
{
    rbShape::Class = rb_define_class_under( SFML, "Shape", rb_cObject );
	rb_include_module( rbShape::Class, rbDrawable::Module );
	rb_include_module( rbShape::Class, rbTransformable::Module );
	
	// Class methods
	rb_define_alloc_func( rbShape::Class, rbInternalAllocateShape );

    // Instance methods
    ext_define_method( rbShape::Class, "initialize",            rbShape::Initialize,         -1 );
    ext_define_method( rbShape::Class, "initialize_copy",       rbShape::InitializeCopy,      1 );
	ext_define_method( rbShape::Class, "get_texture",           rbShape::GetTexture,          0 );
	ext_define_method( rbShape::Class, "set_texture",	        rbShape::SetTexture,	     -1 );
	ext_define_method( rbShape::Class, "get_texture_rect",      rbShape::GetTextureRect,      0 );
	ext_define_method( rbShape::Class, "set_texture_rect",      rbShape::SetTextureRect,      1 );
	ext_define_method( rbShape::Class, "get_fill_color",        rbShape::GetFillColor,        0 );
	ext_define_method( rbShape::Class, "set_fill_color",        rbShape::SetFillColor,        1 );
	ext_define_method( rbShape::Class, "get_outline_color",     rbShape::GetOutlineColor,     0 );
	ext_define_method( rbShape::Class, "set_outline_color",     rbShape::SetOutlineColor,     1 );
	ext_define_method( rbShape::Class, "get_outline_thickness", rbShape::GetOutlineThickness, 0 );
	ext_define_method( rbShape::Class, "set_outline_thickness", rbShape::SetOutlineThickness, 1 );
	ext_define_method( rbShape::Class, "get_point_count",       rbShape::GetPointCount,       0 );
	ext_define_method( rbShape::Class, "get_point",             rbShape::GetPoint,            1 );
	ext_define_method( rbShape::Class, "get_local_bounds",      rbShape::GetLocalBounds,      0 );
	ext_define_method( rbShape::Class, "get_global_bounds",     rbShape::GetGlobalBounds,     0 );
    ext_define_method( rbShape::Class, "marshal_dump",          rbShape::MarshalDump,         0 );
    ext_define_method( rbShape::Class, "==",                    rbShape::Equal,               1 );
    ext_define_method( rbShape::Class, "inspect",               rbShape::Inspect,             0 );

    // Instance aliases
	rb_define_alias( rbShape::Class, "to_s",                "inspect"               );
	rb_define_alias( rbShape::Class, "texture",             "get_texture"           );
	rb_define_alias( rbShape::Class, "getTexture",          "get_texture"           );
	rb_define_alias( rbShape::Class, "texture=",            "set_texture"           );
	rb_define_alias( rbShape::Class, "setTexture",          "set_texture"           );
	rb_define_alias( rbShape::Class, "texture_rect",        "get_texture_rect"      );
	rb_define_alias( rbShape::Class, "getTextureRect",      "get_texture_rect"      );
	rb_define_alias( rbShape::Class, "texture_rect=",       "set_texture_rect"      );
	rb_define_alias( rbShape::Class, "setTextureRect",      "set_texture_rect"      );
	rb_define_alias( rbShape::Class, "fill_color",          "get_fill_color"        );
	rb_define_alias( rbShape::Class, "getFillColor",        "get_fill_color"        );
	rb_define_alias( rbShape::Class, "fill_color=",         "set_fill_color"        );
	rb_define_alias( rbShape::Class, "setFillColor",        "set_fill_color"        );
	rb_define_alias( rbShape::Class, "outline_color",       "get_outline_color"     );
	rb_define_alias( rbShape::Class, "getOutlineColor",     "get_outline_color"     );
	rb_define_alias( rbShape::Class, "outline_color=",      "set_outline_color"     );
	rb_define_alias( rbShape::Class, "setOutlineColor",     "set_outline_color"     );
	rb_define_alias( rbShape::Class, "outline_thickness",   "get_outline_thickness" );
	rb_define_alias( rbShape::Class, "getOutlineThickness", "get_outline_thickness" );
	rb_define_alias( rbShape::Class, "outline_thickness=",  "set_outline_thickness" );
	rb_define_alias( rbShape::Class, "setOutlineThickness", "set_outline_thickness" );
	rb_define_alias( rbShape::Class, "point_count",         "get_point_count"       );
	rb_define_alias( rbShape::Class, "getPointCount",       "get_point_count"       );
	rb_define_alias( rbShape::Class, "getPoint",            "get_point"             );
	rb_define_alias( rbShape::Class, "local_bounds",        "get_local_bounds"      );
	rb_define_alias( rbShape::Class, "getLocalBounds",      "get_local_bounds"      );
	rb_define_alias( rbShape::Class, "global_bounds",       "get_global_bounds"     );
	rb_define_alias( rbShape::Class, "getGlobalBounds",     "get_global_bounds"     );
}

// Sprite#initialize
// Sprite#initialize(texture)
// Sprite#initialize(texture, rect)
VALUE rbShape::Initialize( int argc, VALUE* args, VALUE aSelf )
{	
	rb_iv_set( aSelf, "@__ref__texture", Qnil );
	rb_iv_set( aSelf, "@__internal__drawable_offset", INT2FIX( 0 ) );
	rb_iv_set( aSelf, "@__internal__transformable_offset", INT2FIX( sizeof( sf::Drawable ) ) );
	
    return Qnil;
}

// Shape#initialize_copy(source)
VALUE rbShape::InitializeCopy( VALUE aSelf, VALUE aSource )
{
	*rbMacros::ToSFML< rbInternalShape >( aSelf, rbShape::Class ) = *rbMacros::ToSFML< rbInternalShape >( aSource, rbShape::Class );
	rb_iv_set( aSelf, "@__ref__texture", rb_iv_get( aSource, "@__ref__texture" ) );
    return aSelf;
}

// Shape#texture
// Shape#get_texture
// Shape#getTexture
VALUE rbShape::GetTexture( VALUE aSelf )
{
	return rb_iv_get( aSelf, "@__ref__texture" );
}

// Shape#texture=(texture)
// Shape#set_texture(texture, reset_rect=false)
// Shape#setTexture(texture, reset_rect=false)
VALUE rbShape::SetTexture( int argc, VALUE* args, VALUE aSelf )
{
	bool reset = false;
	switch( argc )
	{
	case 2:
		reset = RTEST( args[ 1 ] );
	case 1:
		rbMacros::ToSFML< sf::Shape >( aSelf, rbShape::Class )->setTexture( rbMacros::ToSFML< sf::Texture >( args[ 0 ], rbTexture::Class ), reset );
		break;
	default:
		INVALID_ARGUMENT_LIST( argc, "1 or 2" );
	}
	rb_iv_set( aSelf, "@__ref__texture", args[ 0 ] );
	return Qnil;
}
 
// Shape#texture_rect=(rect)
// Shape#set_texture_rect(rect)
// Shape#setTextureRect(rect)
VALUE rbShape::SetTextureRect( VALUE aSelf, VALUE aRect )
{
	rbMacros::ToSFML< sf::Shape >( aSelf, rbShape::Class )->setTextureRect( rbRect::ToSFMLi( aRect ) );
	return Qnil;
}

// Shape#texture_rect
// Shape#get_texture_rect
// Shape#getTextureRect
VALUE rbShape::GetTextureRect( VALUE aSelf )
{
	return rbRect::ToRuby( rbMacros::ToSFML< sf::Shape >( aSelf, rbShape::Class )->getTextureRect() );
}

// Shape#fill_color=(color)
// Shape#set_fill_color(color)
// Shape#setFillColor(color)
VALUE rbShape::SetFillColor( VALUE aSelf, VALUE aColor )
{
	rbMacros::ToSFML< sf::Shape >( aSelf, rbShape::Class )->setFillColor( rbColor::ToSFML( aColor ) );
	return Qnil;
}

// Shape#fill_color
// Shape#get_fill_color
// Shape#getFillColor
VALUE rbShape::GetFillColor( VALUE aSelf )
{
	return rbColor::ToRuby( rbMacros::ToSFML< sf::Shape >( aSelf, rbShape::Class )->getFillColor() );
}

// Shape#outline_color=(color)
// Shape#set_outline_color(color)
// Shape#setOutlineColor(color)
VALUE rbShape::SetOutlineColor( VALUE aSelf, VALUE aColor )
{
	rbMacros::ToSFML< sf::Shape >( aSelf, rbShape::Class )->setOutlineColor( rbColor::ToSFML( aColor ) );
	return Qnil;
}

// Shape#outline_color
// Shape#get_outline_color
// Shape#getOutlineColor
VALUE rbShape::GetOutlineColor( VALUE aSelf )
{
	return rbColor::ToRuby( rbMacros::ToSFML< sf::Shape >( aSelf, rbShape::Class )->getOutlineColor() );
}

// Shape#outline_thickness=(thickness)
// Shape#set_outline_thickness(thickness)
// Shape#setOutlineThickness(thickness)
VALUE rbShape::SetOutlineThickness( VALUE aSelf, VALUE aThickness )
{
	rbMacros::ToSFML< sf::Shape >( aSelf, rbShape::Class )->setOutlineThickness( NUM2DBL( aThickness ) );
	return Qnil;
}

// Shape#outline_thickness
// Shape#get_outline_thickness
// Shape#getOutlineThickness
VALUE rbShape::GetOutlineThickness( VALUE aSelf )
{
	return rb_float_new( rbMacros::ToSFML< sf::Shape >( aSelf, rbShape::Class )->getOutlineThickness() );
}

// Shape#point_count
// Shape#get_point_count
// Shape#getPointCount
VALUE rbShape::GetPointCount( VALUE aSelf )
{
	rb_raise( rb_eRuntimeError, "Call to abstract method '#get_point_count'. Please override the method to use it." );
	return Qnil;
}

// Shape#get_point(index)
// Shape#getPoint(index)
VALUE rbShape::GetPoint( VALUE aSelf, VALUE anIndex )
{
	rb_raise( rb_eRuntimeError, "Call to abstract method '#get_point'. Please override the method to use it." );
	return Qnil;
}

// Shape#local_bounds
// Shape#get_local_bounds
// Shape#getLocalBounds
VALUE rbShape::GetLocalBounds( VALUE aSelf )
{
	return rbRect::ToRuby( rbMacros::ToSFML< sf::Shape >( aSelf, rbShape::Class )->getLocalBounds() );
}

// Shape#global_bounds
// Shape#get_global_bounds
// Shape#getGlobalBounds
VALUE rbShape::GetGlobalBounds( VALUE aSelf )
{
	return rbRect::ToRuby( rbMacros::ToSFML< sf::Shape >( aSelf, rbShape::Class )->getGlobalBounds() );
}

// Shape#marshal_dump
VALUE rbShape::MarshalDump( VALUE aSelf )
{
    rb_raise( rb_eTypeError, "can't dump %s", rb_obj_classname( aSelf ) );
    return Qnil; 
}

// Shape#==(other)
VALUE rbShape::Equal( VALUE aSelf, VALUE anOther )
{
    if( !rb_obj_is_kind_of( anOther, rbShape::Class ) ) return Qfalse;
    if( !RTEST( rbMacros::ToSFML< sf::Shape >( aSelf, rbShape::Class ) != rbMacros::ToSFML< sf::Shape >( anOther, rbShape::Class ) ) ) return Qfalse;
    return Qtrue;
}

// Shape#inspect
// Shape#to_s
VALUE rbShape::Inspect( VALUE aSelf )
{
	return rb_sprintf( "%s(%p)",
					   rb_obj_classname( aSelf ),
					   rbMacros::ToSFML< sf::Shape >( aSelf, rbShape::Class ) );
}
