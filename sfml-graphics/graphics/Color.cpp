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
 
#include "Color.hpp"
#include "main.hpp"

VALUE globalColorClass;

/* Internal function
 * Forces the argument someValue to be a Color. If it can convert it then it will.
 * So you can always safely asume that this function returns a Color object.
 * If it fails then an exception will be thrown.
 */
VALUE Color_ForceType( VALUE someValue )
{
	if( rb_obj_is_kind_of( someValue, rb_cArray ) == Qtrue )
	{
		VALUE arg1 = rb_ary_entry( someValue, 0 );
		VALUE arg2 = rb_ary_entry( someValue, 1 );
		VALUE arg3 = rb_ary_entry( someValue, 2 );
		if( RARRAY_LEN( someValue ) == 4 )
		{
			VALUE arg4 = rb_ary_entry( someValue, 3 );
			return rb_funcall( globalColorClass, rb_intern( "new" ), 4, arg1, arg2, arg3, arg4 );
		}
		return rb_funcall( globalColorClass, rb_intern( "new" ), 3, arg1, arg2, arg3 );
	}
	else if( rb_obj_is_kind_of( someValue, globalColorClass ) == Qtrue )
	{
		return someValue;
	}
	else
	{
		VALUE typeName = rb_funcall( CLASS_OF( someValue ), rb_intern( "to_s" ), 0 );
		rb_raise( rb_eTypeError, "Expected argument to be either Array or Color but was given %s", rb_string_value_cstr( &typeName ) );
	}
}

VALUE Color_GetR( VALUE self )
{
	return rb_iv_get( self, "@r" );
}
VALUE Color_GetG( VALUE self )
{
	return rb_iv_get( self, "@g" );
}
VALUE Color_GetB( VALUE self )
{
	return rb_iv_get( self, "@b" );
}
VALUE Color_GetA( VALUE self )
{
	return rb_iv_get( self, "@a" );
}

void Color_SetR( VALUE self, VALUE aVal )
{
	rb_iv_set( self, "@r", aVal );
}
void Color_SetG( VALUE self, VALUE aVal )
{
	rb_iv_set( self, "@g", aVal );
}
void Color_SetB( VALUE self, VALUE aVal )
{
	rb_iv_set( self, "@b", aVal );
}
void Color_SetA( VALUE self, VALUE aVal )
{
	rb_iv_set( self, "@a", aVal );
}

sf::Color Color_ToSFML( VALUE aColor )
{
	return sf::Color( FIX2INT( Color_GetR( aColor ) ), FIX2INT( Color_GetG( aColor ) ), 
                    FIX2INT( Color_GetB( aColor ) ), FIX2INT( Color_GetA( aColor ) ) 
	                );
}

VALUE Color_ToRuby( const sf::Color &aColor )
{
	return rb_funcall( globalColorClass, rb_intern( "new" ), 4, 
	                   INT2FIX( aColor.r ), INT2FIX( aColor.g ), 
	                   INT2FIX( aColor.b ), INT2FIX( aColor.a )
	                 );
}

/* Internal function
 * Will copy the color components from aSource to self.
 */
static void Color_internal_CopyFrom( VALUE self, VALUE aSource )
{
	VALUE source = Color_ForceType( aSource );
	VALUE r = Color_GetR( source );
	VALUE g = Color_GetG( source );
	VALUE b = Color_GetB( source );
	VALUE a = Color_GetA( source );
	
	Color_SetR( self, r );
	Color_SetG( self, g );
	Color_SetB( self, b );
	Color_SetA( self, a ); 
}

/* call-seq:
 *   color1 + color2	-> color
 *
 * This operator returns the component-wise sum of two colors. Components that exceed 255 are clamped to 255.
 */
static VALUE Color_Add( VALUE self, VALUE aRightOperand )
{
	VALUE right = Color_ForceType( aRightOperand );
	// Get values
	unsigned int leftR  = FIX2INT( Color_GetR( self ) );
	unsigned int leftG  = FIX2INT( Color_GetG( self ) );
	unsigned int leftB  = FIX2INT( Color_GetB( self ) );
	unsigned int leftA  = FIX2INT( Color_GetA( self ) );
	unsigned int rightR = FIX2INT( Color_GetR( right ) );
	unsigned int rightG = FIX2INT( Color_GetG( right ) );
	unsigned int rightB = FIX2INT( Color_GetB( right ) );
	unsigned int rightA = FIX2INT( Color_GetA( right ) );

	// Do calculation	
	unsigned int newR = MIN( leftR + rightR, 255 );
	unsigned int newG = MIN( leftG + rightG, 255 );
	unsigned int newB = MIN( leftB + rightB, 255 );
	unsigned int newA = MIN( leftA + rightA, 255 );
	
	return rb_funcall( globalColorClass, rb_intern( "new" ), 4, INT2FIX( newR ), INT2FIX( newG ), INT2FIX( newB ), INT2FIX( newA ) );
}

/* call-seq:
 *   color1 * color2	-> color
 *
 * This operator returns the component-wise multiplication (also called "modulation") of two colors. Components are 
 * then divided by 255 so that the result is still in the range [0, 255].
 */
static VALUE Color_Multiply( VALUE self, VALUE aRightOperand )
{
	VALUE right = Color_ForceType( aRightOperand );
	// Get values
	unsigned int leftR  = FIX2INT( Color_GetR( self ) );
	unsigned int leftG  = FIX2INT( Color_GetG( self ) );
	unsigned int leftB  = FIX2INT( Color_GetB( self ) );
	unsigned int leftA  = FIX2INT( Color_GetA( self ) );
	unsigned int rightR = FIX2INT( Color_GetR( right ) );
	unsigned int rightG = FIX2INT( Color_GetG( right ) );
	unsigned int rightB = FIX2INT( Color_GetB( right ) );
	unsigned int rightA = FIX2INT( Color_GetA( right ) );

	// Do calculation	
	unsigned int newR = ( leftR * rightR ) / 255;
	unsigned int newG = ( leftG * rightG ) / 255;
	unsigned int newB = ( leftB * rightB ) / 255;
	unsigned int newA = ( leftA * rightA ) / 255;
	
	return rb_funcall( globalColorClass, rb_intern( "new" ), 4, INT2FIX( newR ), INT2FIX( newG ), INT2FIX( newB ), INT2FIX( newA ) );
}

/* call-seq:
 *   color1 == color2	-> true or false
 *
 * This operator compares two colors and check if they are equal.
 */
static VALUE Color_Equal( VALUE self, VALUE anArgument )
{
	VALUE right = Color_ForceType( anArgument );
	// Get values
	unsigned int leftR  = FIX2INT( Color_GetR( self ) );
	unsigned int leftG  = FIX2INT( Color_GetG( self ) );
	unsigned int leftB  = FIX2INT( Color_GetB( self ) );
	unsigned int leftA  = FIX2INT( Color_GetA( self ) );
	unsigned int rightR = FIX2INT( Color_GetR( right ) );
	unsigned int rightG = FIX2INT( Color_GetG( right ) );
	unsigned int rightB = FIX2INT( Color_GetB( right ) );
	unsigned int rightA = FIX2INT( Color_GetA( right ) );

	// Do calculation	
	if( leftR == rightR && leftG == rightG && leftB == rightB && leftA == rightA )
	{
		return Qtrue;
	}
	return Qfalse;
}

/* call-seq:
 *   Color.new() 		-> color
 *   Color.new([r,g,b,a=255])	-> color
 *   Color.new(vector) 		-> color
 *   Color.new(r,g,b,a=255)	-> color
 * 
 * Create a new color instance.
 */
static VALUE Color_Initialize( int argc, VALUE * args, VALUE self )
{
	rb_iv_set( self, "@a", INT2FIX( 255 ) );
	
	switch( argc )
	{
		case 0:
      rb_iv_set( self, "@r", INT2FIX( 0 ) );
      rb_iv_set( self, "@g", INT2FIX( 0 ) );
      rb_iv_set( self, "@b", INT2FIX( 0 ) );
			break;
		case 1:
			Color_internal_CopyFrom( self, args[0] );
			break;
		case 4:
			VALIDATE_CLASS( args[3], rb_cFixnum, "alpha" );
			rb_iv_set( self, "@a", args[3]);
		case 3:
			VALIDATE_CLASS( args[0], rb_cFixnum, "red" );
			VALIDATE_CLASS( args[1], rb_cFixnum, "green" );
			VALIDATE_CLASS( args[2], rb_cFixnum, "blue" );
			rb_iv_set( self, "@r", args[0]);
			rb_iv_set( self, "@g", args[1]);
			rb_iv_set( self, "@b", args[2]);
			break;
		default:
			rb_raise( rb_eArgError, "Expected 0, 1, 3 or 4 arguments but was given %d", argc );
	}
	return self;
}

void Init_Color( void )
{
/* SFML namespace which contains the classes of this module. */
	VALUE sfml = rb_define_module( "SFML" );
/* Utility class for manpulating RGBA colors.
 *
 * SFML::Color is a simple color class composed of 4 components:
 *
 *   - Red
 *   - Green
 *   - Blue
 *   - Alpha (opacity)
 *
 * Each component is a public member, an unsigned integer in the range [0, 255]. Thus, colors can be constructed and manipulated very easily:
 *
 *   c1 = SFML::Color.new(255, 0, 0)	# red
 *   c1.red = 0				# make it black
 *   c1.blue = 128			# make it dark blue
 *
 * The fourth component of colors, named "alpha", represents the opacity of the color. A color with an alpha value of 
 * 255 will be fully opaque, while an alpha value of 0 will make a color fully transparent, whatever the value of the 
 * other components.
 * 
 * The most common colors are already defined as class constants:
 *
 * black   = SFML::Color::Black
 * white   = SFML::Color::White
 * red     = SFML::Color::Red
 * green   = SFML::Color::Green
 * blue    = SFML::Color::Blue
 * yellow  = SFML::Color::Yellow
 * magenta = SFML::Color::Magenta
 * cyan    = SFML::Color::Cyan
 *
 * Colors can also be added and modulated (multiplied) using the overloaded operators + and *. 
 */
	globalColorClass = rb_define_class_under( sfml, "Color", rb_cObject );
	
	// Instance methods
	rb_define_method( globalColorClass, "initialize", Color_Initialize, -1 );
	rb_define_method( globalColorClass, "+",          Color_Add,         1 );
	rb_define_method( globalColorClass, "*",          Color_Multiply,    1 );
	rb_define_method( globalColorClass, "==",         Color_Equal,       1 );
	
	// Attribute accessors
	rb_define_attr( globalColorClass, "r", 1, 1 );
	rb_define_attr( globalColorClass, "g", 1, 1 );
	rb_define_attr( globalColorClass, "b", 1, 1 );
	rb_define_attr( globalColorClass, "a", 1, 1 );
	
	// Class constants
  VALUE const_black   = rb_funcall( globalColorClass, rb_intern( "new" ), 3, INT2FIX(   0 ), INT2FIX(   0 ), INT2FIX(   0 ) );
  VALUE const_white   = rb_funcall( globalColorClass, rb_intern( "new" ), 3, INT2FIX( 255 ), INT2FIX( 255 ), INT2FIX( 255 ) );
  VALUE const_red     = rb_funcall( globalColorClass, rb_intern( "new" ), 3, INT2FIX( 255 ), INT2FIX(   0 ), INT2FIX(   0 ) );
  VALUE const_green   = rb_funcall( globalColorClass, rb_intern( "new" ), 3, INT2FIX(   0 ), INT2FIX( 255 ), INT2FIX(   0 ) );
  VALUE const_blue    = rb_funcall( globalColorClass, rb_intern( "new" ), 3, INT2FIX(   0 ), INT2FIX(   0 ), INT2FIX( 255 ) );
  VALUE const_yellow  = rb_funcall( globalColorClass, rb_intern( "new" ), 3, INT2FIX( 255 ), INT2FIX( 255 ), INT2FIX(   0 ) );
  VALUE const_magneta = rb_funcall( globalColorClass, rb_intern( "new" ), 3, INT2FIX( 255 ), INT2FIX(   0 ), INT2FIX( 255 ) );
  VALUE const_cyan    = rb_funcall( globalColorClass, rb_intern( "new" ), 3, INT2FIX(   0 ), INT2FIX( 255 ), INT2FIX( 255 ) );
  
	rb_define_const( globalColorClass, "Black",   const_black   );
	rb_define_const( globalColorClass, "White",   const_white   );
	rb_define_const( globalColorClass, "Red",     const_red     );
	rb_define_const( globalColorClass, "Green",   const_green   );
	rb_define_const( globalColorClass, "Blue",    const_blue    );
	rb_define_const( globalColorClass, "Yellow",  const_yellow  );
	rb_define_const( globalColorClass, "Magneta", const_magneta );
	rb_define_const( globalColorClass, "Cyan",    const_cyan    );
	
	rb_funcall( const_black,   rb_intern( "freeze" ), 0 );
	rb_funcall( const_white,   rb_intern( "freeze" ), 0 );
	rb_funcall( const_red,     rb_intern( "freeze" ), 0 );
	rb_funcall( const_green,   rb_intern( "freeze" ), 0 );
	rb_funcall( const_blue,    rb_intern( "freeze" ), 0 );
	rb_funcall( const_yellow,  rb_intern( "freeze" ), 0 );
	rb_funcall( const_magneta, rb_intern( "freeze" ), 0 );
	rb_funcall( const_cyan,    rb_intern( "freeze" ), 0 );
}
