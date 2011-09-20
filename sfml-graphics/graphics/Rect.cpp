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
 
#include "Rect.hpp"
#include "Vector2.hpp"
#include "main.hpp"

VALUE globalRectClass;

/* Internal function
 * Forces the argument someValue to be a Rect. IF it can convert it then it will.
 * So you can always safely asume that this function returns a Rect object.
 * If it fails then an exception will be thrown.
 */
VALUE Rect_ForceType( VALUE someValue )
{
	if( rb_obj_is_kind_of( someValue, rb_cArray ) == Qtrue )
	{
		VALUE arg1 = rb_ary_entry( someValue, 0 );
		VALUE arg2 = rb_ary_entry( someValue, 1 );
		VALUE arg3 = rb_ary_entry( someValue, 2 );
		VALUE arg4 = rb_ary_entry( someValue, 3 );
		return rb_funcall( globalRectClass, rb_intern( "new" ), 4, arg1, arg2, arg3, arg4 );
	}
	else if( rb_obj_is_kind_of( someValue, globalRectClass ) == Qtrue )
	{
		return someValue;
	}
	else
	{
		VALUE typeName = rb_funcall( CLASS_OF( someValue ), rb_intern( "to_s" ), 0 );
		rb_raise( rb_eTypeError, "Expected argument to be either Array or Rect but was given %s", rb_string_value_cstr( &typeName ) );
	}
}

VALUE Rect_GetLeft( VALUE self )
{
  return rb_iv_get( self, "@left" );
}
VALUE Rect_GetTop( VALUE self )
{
  return rb_iv_get( self, "@top" );
}
VALUE Rect_GetWidth( VALUE self )
{
  return rb_iv_get( self, "@width" );
}
VALUE Rect_GetHeight( VALUE self )
{
  return rb_iv_get( self, "@height" );
}

void Rect_SetLeft( VALUE self, VALUE aVal )
{
  rb_iv_set( self, "@left", aVal );
}
void Rect_SetTop( VALUE self, VALUE aVal )
{
  rb_iv_set( self, "@top", aVal );
}
void Rect_SetWidth( VALUE self, VALUE aVal )
{
  rb_iv_set( self, "@width", aVal );
}
void Rect_SetHeight( VALUE self, VALUE aVal )
{
  rb_iv_set( self, "@height", aVal );
}

sf::IntRect Rect_ToSFMLi( VALUE aRect )
{
	return sf::IntRect( FIX2INT( Rect_GetLeft( aRect ) ), FIX2INT( Rect_GetTop( aRect ) ), 
	                    FIX2INT( Rect_GetWidth( aRect ) ), FIX2INT( Rect_GetHeight( aRect ) ) 
	                  );
}

sf::FloatRect Rect_ToSFMLf( VALUE aRect )
{
	return sf::FloatRect( NUM2DBL( Rect_GetLeft( aRect ) ), NUM2DBL( Rect_GetTop( aRect ) ), 
	                      NUM2DBL( Rect_GetWidth( aRect ) ), NUM2DBL( Rect_GetHeight( aRect ) ) 
	                    );
}

VALUE Rect_ToRuby( const sf::IntRect &aRect )
{
	return rb_funcall( globalRectClass, rb_intern( "new" ), 4, 
	                   INT2FIX( aRect.Left ), INT2FIX( aRect.Top ), 
	                   INT2FIX( aRect.Width ), INT2FIX( aRect.Height )
	                 );
}

VALUE Rect_ToRuby( const sf::FloatRect &aRect )
{
	return rb_funcall( globalRectClass, rb_intern( "new" ), 4, 
	                   rb_float_new( aRect.Left ), rb_float_new( aRect.Top ), 
	                   rb_float_new( aRect.Width ), rb_float_new( aRect.Height )
	                 );
}

/* Internal function
 * Will copy the x and y from aSource to self.
 */
static void Rect_internal_CopyFrom( VALUE self, VALUE aSource )
{
	VALUE rect = Rect_ForceType( aSource );
  rb_iv_set( self, "@left",   rb_iv_get( rect, "@left" ) );
  rb_iv_set( self, "@top",    rb_iv_get( rect, "@top" ) );
  rb_iv_set( self, "@width",  rb_iv_get( rect, "@width" ) );
  rb_iv_set( self, "@height", rb_iv_get( rect, "@height" ) );
}

/* Internal function
 * Validate that the passed types are the same and numeric.
 */
static void Rect_internal_ValidateTypes( VALUE aFirst, VALUE aSecond, VALUE aThird, VALUE aFourth )
{
	if( CLASS_OF( aFirst ) != CLASS_OF( aSecond ) || CLASS_OF( aFirst ) != CLASS_OF( aThird ) || CLASS_OF( aFirst ) != CLASS_OF( aFourth ) )
	{
		rb_raise( rb_eRuntimeError, "left, top, width and height must be of same type" );
	}
	
	if( rb_obj_is_kind_of( aFirst, rb_cNumeric ) == Qfalse )
	{
		rb_raise( rb_eRuntimeError, "left, top, width and height must be numeric!" );
	}
}

/* call-seq:
 *   rect.contains( x, y )	-> true or false
 *   rect.contains( vector2 )	-> true or false
 * 
 * Check if a point is inside the rectangle's area.
 */
static VALUE Rect_Contains( int argc, VALUE * args, VALUE self )
{
	VALUE pointX;
	VALUE pointY;
	VALUE left 	 = rb_iv_get( self, "@left" );
	VALUE top    = rb_iv_get( self, "@top" );
	VALUE width  = rb_iv_get( self, "@width" );
	VALUE height = rb_iv_get( self, "@height" );
  
	switch( argc )
	{
		case 1:
			pointX = Vector2_GetX( args[0] );
			pointY = Vector2_GetY( args[0] );
			break;
		case 2:
			VALIDATE_CLASS( args[0], rb_cNumeric, "x" );
			VALIDATE_CLASS( args[1], rb_cNumeric, "y" );
			pointX = args[0];
			pointY = args[1];
			break;
		default:
			rb_raise( rb_eArgError, "Expected 1 or 2 arguments but was given %d", argc );
	}
	
	VALUE first  = rb_funcall( pointX, rb_intern( ">=" ), 1, left );
	VALUE second = rb_funcall( pointX, rb_intern( "<" ), 1, rb_funcall( left, rb_intern( "+" ), 1, width ) );
	VALUE third  = rb_funcall( pointY, rb_intern( ">=" ), 1, top );
	VALUE fourth = rb_funcall( pointY, rb_intern( "<" ), 1, rb_funcall( top, rb_intern( "+" ), 1, height ) );
	if( first == Qtrue && second == Qtrue && third == Qtrue && fourth == Qtrue )
	{
		return Qtrue;
	}
	else
	{
		return Qfalse;
	}
}

/* call-seq:
 *   rect.intersects( rectangle )	-> intersection rectangel or nil
 * 
 * Check the intersection between two rectangles.
 *
 * This method returns the overlapped rectangle if intersecting otherwise nil.
 */
static VALUE Rect_Intersects( VALUE self, VALUE aRect )
{
	VALUE selfLeft 	 = rb_iv_get( self, "@left" );
	VALUE selfTop    = rb_iv_get( self, "@top" );
	VALUE selfWidth  = rb_iv_get( self, "@width" );
	VALUE selfHeight = rb_iv_get( self, "@height" );
	VALUE selfRight  = rb_funcall( selfLeft, rb_intern( "+" ), 1, selfWidth );
	VALUE selfBottom = rb_funcall( selfTop, rb_intern( "+" ), 1, selfHeight );
	VALUE rectLeft 	 = rb_iv_get( aRect, "@left" );
	VALUE rectTop    = rb_iv_get( aRect, "@top" );
	VALUE rectWidth  = rb_iv_get( aRect, "@width" );
	VALUE rectHeight = rb_iv_get( aRect, "@height" );
	VALUE rectRight  = rb_funcall( rectLeft, rb_intern( "+" ), 1, rectWidth );
	VALUE rectBottom = rb_funcall( rectTop, rb_intern( "+" ), 1, rectHeight );
	
	VALUE left, top, right, bottom;
	
	if( rb_funcall( selfLeft, rb_intern( ">" ), 1, rectLeft ) == Qtrue )
	{
		left = selfLeft;
	}
	else
	{
		left = rectLeft;
	}
	
	if( rb_funcall( selfTop, rb_intern( ">" ), 1, rectTop ) == Qtrue )
	{
		top = selfTop;
	}
	else
	{
		top = rectTop;
	}
	
	if( rb_funcall( selfRight , rb_intern( "<" ), 1, rectRight ) == Qtrue )
	{
		right = selfRight;
	}
	else
	{
		right = rectRight;
	}
	
	if( rb_funcall( selfBottom , rb_intern( "<" ), 1, rectBottom ) == Qtrue )
	{
		bottom = selfBottom;
	}
	else
	{
		bottom = rectBottom;
	}
	
	if( rb_funcall( left, rb_intern( "<" ), 1, right) == Qtrue && rb_funcall( top, rb_intern( "<" ), 1, bottom) == Qtrue )
	{
		VALUE newWidth  = rb_funcall( right, rb_intern( "-" ), 1, left );
		VALUE newHeight = rb_funcall( bottom, rb_intern( "-" ), 1, top );
		return rb_funcall( globalRectClass, rb_intern( "new" ), 4, left, top, newWidth, newHeight );
	}
	else
	{
		return Qnil;
	}
}

/* call-seq:
 *   Rect.new() 				-> rect
 *   Rect.new( [left, top, width, height] )	-> rect
 *   Rect.new( rect ) 				-> rect
 *   Rect.new( left, top, width, height )	-> rect
 *   Rect.new( position, size )			-> rect
 * 
 * Create a new rect instance.
 */
static VALUE Rect_Initialize( int argc, VALUE *args, VALUE self )
{	
	VALUE arg0;
	VALUE arg1;
	switch( argc )
	{
		case 0:
			rb_iv_set( self, "@left",   INT2NUM( 0 ) );
			rb_iv_set( self, "@top",    INT2NUM( 0 ) );
			rb_iv_set( self, "@width",  INT2NUM( 0 ) );
			rb_iv_set( self, "@height", INT2NUM( 0 ) );
			break;
		case 1:
			Rect_internal_CopyFrom( self, args[0] );
			break;
		case 2:
			arg0 = Vector2_ForceType( args[0] );
			arg1 = Vector2_ForceType( args[1] );
			rb_iv_set( self, "@left",   Vector2_GetX( arg0 ) );
			rb_iv_set( self, "@top",    Vector2_GetY( arg0 ) );
			rb_iv_set( self, "@width",  Vector2_GetX( arg1 ) );
			rb_iv_set( self, "@height", Vector2_GetY( arg1 ) );
			break;
		case 4:
			Rect_internal_ValidateTypes( args[0], args[1], args[2], args[3] );
			rb_iv_set( self, "@left",   args[0]);
			rb_iv_set( self, "@top",    args[1]);
			rb_iv_set( self, "@width",  args[2]);
			rb_iv_set( self, "@height", args[3]);
			break;
		default:
			rb_raise( rb_eArgError, "Expected 0, 1, 2 or 4 arguments but was given %d", argc );
	}
	
	return self;
}

void Init_Rect( void )
{
/* SFML namespace which contains the classes of this module. */
	VALUE sfml = rb_define_module( "SFML" );
/* Utility class for manipulating 2D axis aligned rectangles.
 *
 * A rectangle is defined by its top-left corner and its size.
 *
 * It is a very simple class defined for convenience, so its member variables (left, top, width and height) are public 
 * and can be accessed directly, just like the vector classes (SFML::Vector2 and SFML::Vector3).
 *
 * To keep things simple, SFML::Rect doesn't define functions to emulate the properties that are not directly members 
 * (such as right, bottom, center, etc.), it rather only provides intersection functions.
 *
 * SFML::Rect uses the usual rules for its boundaries:
 *
 *   - The left and top edges are included in the rectangle's area
 *   - The right (left + width) and bottom (top + height) edges are excluded from the rectangle's area
 *
 * This means that SFML::Rect.new(0, 0, 1, 1) and SFML::Rect.new(1, 1, 1, 1) don't intersect.
 *
 * SFML::Rect works just like SFML::Vector2 and SFML::Vector3 when it comes to types. It will accept any value that is 
 * Numeric but all values must be of the same class.
 *
 * Usage example:
 *
 *   # Define a rectangle, located at (0, 0) with a size of 20x5
 *   r1 = SFML::Rect.new( 0, 0, 20, 5 )
 *
 *   # Define another rectangle, located at (4, 2) with a size of 18x10
 *   position = SFML::Vector2.new( 4, 2 )
 *   size = SFML::Vector2.new( 18, 10 )
 *   r2 = SFML::Rect.new( position, size )
 *  
 *   # Test intersections with the point (3, 1)
 *   b1 = r1.contains( 3, 1 ) # true
 *   b2 = r2.contains( 3, 1 ) # false
 *
 *   # Test the intersection between r1 and r2
 *   result = r1.intersects( r2 ) # If r1 don't intersect r2 then result would be nil
 *   # result == (4, 2, 16, 3)
 *
 */
	globalRectClass = rb_define_class_under( sfml, "Rect", rb_cObject );
	
	// Instance methods
	rb_define_method( globalRectClass, "initialize", Rect_Initialize, -1 );
	rb_define_method( globalRectClass, "contains",   Rect_Contains,   -1 );
	rb_define_method( globalRectClass, "intersects", Rect_Intersects,  1 );
		
	// Attribute accessors
	rb_define_attr( globalRectClass, "left",   1, 1 );
	rb_define_attr( globalRectClass, "top",    1, 1 );
	rb_define_attr( globalRectClass, "width",  1, 1 );
	rb_define_attr( globalRectClass, "height", 1, 1 );
  
	// Instance Aliases
	rb_define_alias( globalRectClass, "Contains",   "contains"   );
	rb_define_alias( globalRectClass, "include?",   "contains"   );
	rb_define_alias( globalRectClass, "Intersects", "intersects" );
	rb_define_alias( globalRectClass, "Left",       "left"       );
	rb_define_alias( globalRectClass, "Left=",      "left="      );
	rb_define_alias( globalRectClass, "Top",        "top"        );
	rb_define_alias( globalRectClass, "Top=",       "top="       );
	rb_define_alias( globalRectClass, "Width",      "width"      );
	rb_define_alias( globalRectClass, "Width=",     "width="     );
	rb_define_alias( globalRectClass, "Height",     "height"     );
	rb_define_alias( globalRectClass, "Height=",    "height="    );
}
