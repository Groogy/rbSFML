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

/* Internal:
 * Forces the argument someValue to be a Rect. If it can convert it then it will.
 * So you can always safely asume that this function returns a Rect object.
 * If it fails then an exception will be thrown.
 */
VALUE Rect_ForceType( VALUE someValue )
{
	if( rb_obj_is_kind_of( someValue, globalRectClass ) == Qtrue )
	{
		return someValue;
	}
	else if( rb_obj_is_kind_of( someValue, rb_cArray ) == Qtrue )
	{
		return rb_class_new_instance( RARRAY_LEN( someValue ), RARRAY_PTR( someValue ), globalRectClass );
	}
	else
	{
		rb_raise( rb_eTypeError, "can't convert %s into Color", rb_obj_classname( someValue ) );
	}
}

// Getter functions:
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

// Setter functions:
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

/* Internal:
 * Returns the type of the Rect, outputs 'i' for int rects or 'f' for float rects.
 */
int Rect_Type( VALUE aRect )
{
	switch( TYPE( rb_iv_get( aRect, "@left" ) ) )
	{
		case T_FIXNUM:
			return 'i';
		case T_FLOAT:
			return 'f';
	}
}

/* Internal:
 * Returns a SFML rect from a ruby one. Argument must be a int ruby rect (see Rect_Type)
 */
sf::IntRect Rect_ToSFMLi( VALUE aRect )
{
	return sf::IntRect( FIX2INT( Rect_GetLeft( aRect ) ), FIX2INT( Rect_GetTop( aRect ) ), 
	                    FIX2INT( Rect_GetWidth( aRect ) ), FIX2INT( Rect_GetHeight( aRect ) ) );
}

/* Internal:
 * Returns a SFML rect from a ruby one. Argument must be a float ruby rect (see Rect_Type)
 */
sf::FloatRect Rect_ToSFMLf( VALUE aRect )
{
	return sf::FloatRect( NUM2DBL( Rect_GetLeft( aRect ) ),  NUM2DBL( Rect_GetTop( aRect ) ), 
	                      NUM2DBL( Rect_GetWidth( aRect ) ), NUM2DBL( Rect_GetHeight( aRect ) ) );
}

VALUE Rect_ToRuby( const sf::IntRect &aRect )
{
	VALUE args[] = { INT2FIX( aRect.Left  ), INT2FIX( aRect.Top    ),
	                 INT2FIX( aRect.Width ), INT2FIX( aRect.Height ) };
	return rb_class_new_instance( 4, args, globalRectClass );
}

VALUE Rect_ToRuby( const sf::FloatRect &aRect )
{
	VALUE args[] = { rb_float_new( aRect.Left  ), rb_float_new( aRect.Top    ), 
	                 rb_float_new( aRect.Width ), rb_float_new( aRect.Height ) };
	return rb_class_new_instance( 4, args, globalRectClass );
}

static VALUE Rect_InitializeCopy( VALUE self, VALUE aSource )
{
	rb_iv_set( self, "@left",   rb_iv_get( aSource, "@left"   ) );
	rb_iv_set( self, "@top",    rb_iv_get( aSource, "@top"    ) );
	rb_iv_set( self, "@width",  rb_iv_get( aSource, "@width"  ) );
	rb_iv_set( self, "@height", rb_iv_get( aSource, "@height" ) );
}

static VALUE Rect_equal( VALUE self, VALUE aValue )
{
	if ( CLASS_OF( aValue ) != globalRectClass ) return Qfalse;
	if ( !rb_equal( rb_iv_get( self, "@left"   ), rb_iv_get( aValue, "@left"   ) ) ) return Qfalse;
	if ( !rb_equal( rb_iv_get( self, "@top"    ), rb_iv_get( aValue, "@top"    ) ) ) return Qfalse;
	if ( !rb_equal( rb_iv_get( self, "@width"  ), rb_iv_get( aValue, "@width"  ) ) ) return Qfalse;
	if ( !rb_equal( rb_iv_get( self, "@height" ), rb_iv_get( aValue, "@height" ) ) ) return Qfalse;
	if ( CLASS_OF( rb_iv_get( self, "@left"   ) ) != CLASS_OF( rb_iv_get( aValue, "@left"   ) )) return Qfalse;
	return Qtrue;
}

static VALUE Rect_Contains( int argc, VALUE * args, VALUE self )
{
	VALUE pointX;
	VALUE pointY;
	VALUE left   = rb_iv_get( self, "@left"   );
	VALUE top    = rb_iv_get( self, "@top"    );
	VALUE width  = rb_iv_get( self, "@width"  );
	VALUE height = rb_iv_get( self, "@height" );
  
	switch( argc )
	{
		case 1:
			args[0] = Vector2_ForceType( args[0] );
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
	return ( first == Qtrue && second == Qtrue && third == Qtrue && fourth == Qtrue ) ? Qtrue : Qfalse;
}

static VALUE Rect_Intersects( VALUE self, VALUE aRect )
{
	VALUE selfLeft 	 = rb_iv_get( self, "@left"   );
	VALUE selfTop    = rb_iv_get( self, "@top"    );
	VALUE selfWidth  = rb_iv_get( self, "@width"  );
	VALUE selfHeight = rb_iv_get( self, "@height" );
	VALUE selfRight  = rb_funcall( selfLeft, rb_intern( "+" ), 1, selfWidth  );
	VALUE selfBottom = rb_funcall( selfTop,  rb_intern( "+" ), 1, selfHeight );
	
	aRect = Rect_ForceType( aRect );
	VALUE rectLeft 	 = rb_iv_get( aRect, "@left"   );
	VALUE rectTop    = rb_iv_get( aRect, "@top"    );
	VALUE rectWidth  = rb_iv_get( aRect, "@width"  );
	VALUE rectHeight = rb_iv_get( aRect, "@height" );
	VALUE rectRight  = rb_funcall( rectLeft, rb_intern( "+" ), 1, rectWidth  );
	VALUE rectBottom = rb_funcall( rectTop,  rb_intern( "+" ), 1, rectHeight );
	
	VALUE left, top, right, bottom;
	
	left   = RMAX( selfLeft,   rectLeft   );
	top    = RMAX( selfTop,    rectTop    );
	right  = RMIN( selfRight,  rectRight  );
	bottom = RMIN( selfBottom, rectBottom );
	
	if( rb_funcall( left, rb_intern( "<" ), 1, right  ) == Qtrue && 
	    rb_funcall( top,  rb_intern( "<" ), 1, bottom ) == Qtrue )
	{
		VALUE width  = rb_funcall( right,  rb_intern( "-" ), 1, left );
		VALUE height = rb_funcall( bottom, rb_intern( "-" ), 1, top  );
		VALUE args[] = { left, top, width, height };
		return rb_class_new_instance( 4, args, globalRectClass );
	}
	else
	{
		return Qnil;
	}
}

static VALUE Rect_inspect( VALUE self )
{
	VALUE left   = rb_inspect( rb_iv_get( self, "@left"   ) );
	VALUE top    = rb_inspect( rb_iv_get( self, "@top"    ) );
	VALUE width  = rb_inspect( rb_iv_get( self, "@width"  ) );
	VALUE height = rb_inspect( rb_iv_get( self, "@height" ) );
	VALUE comma  = rb_str_new2( ", " );
	VALUE rparen = rb_str_new2( ")" );
	VALUE result = rb_str_new2( "Rect(" );
	rb_str_concat( result, left   );
	rb_str_concat( result, comma  );
	rb_str_concat( result, top    );
	rb_str_concat( result, comma  );
	rb_str_concat( result, width  );
	rb_str_concat( result, comma  );
	rb_str_concat( result, height );
	rb_str_concat( result, rparen );
	return result;
}

static VALUE Rect_Initialize( int argc, VALUE *args, VALUE self )
{	
	VALUE list[4];
	switch( argc )
	{
		case 0:
			rb_iv_set( self, "@left",   INT2FIX( 0 ) );
			rb_iv_set( self, "@top",    INT2FIX( 0 ) );
			rb_iv_set( self, "@width",  INT2FIX( 0 ) );
			rb_iv_set( self, "@height", INT2FIX( 0 ) );
			break;
		case 1:
			Rect_InitializeCopy( self, Rect_ForceType( args[0] ) );
			break;
		case 2:
			args[0] = Vector2_ForceType( args[0] );
			args[1] = Vector2_ForceType( args[1] );
			list[0] = Vector2_GetX( args[0] );
			list[1] = Vector2_GetY( args[0] );
			list[2] = Vector2_GetX( args[1] );
			list[3] = Vector2_GetY( args[1] );
			
			// Ensure all arguments are instance of Float or Fixnum.
			if ( !IMMEDIATE_P(list[0]) or !IMMEDIATE_P(list[1]) or !IMMEDIATE_P(list[2]) or !IMMEDIATE_P(list[3]) )
			{
				list[0] = rb_convert_type( list[0], T_FLOAT, "Float", "to_f" );
				list[1] = rb_convert_type( list[1], T_FLOAT, "Float", "to_f" );
				list[2] = rb_convert_type( list[2], T_FLOAT, "Float", "to_f" );
				list[3] = rb_convert_type( list[3], T_FLOAT, "Float", "to_f" );
			}
			
			rb_iv_set( self, "@left",   list[0]);
			rb_iv_set( self, "@top",    list[1]);
			rb_iv_set( self, "@width",  list[2]);
			rb_iv_set( self, "@height", list[3]);
			break;
		case 4:
			// Ensure all arguments are kind of Numeric.
			VALIDATE_CLASS( args[0], rb_cNumeric, "left"   );
			VALIDATE_CLASS( args[1], rb_cNumeric, "top"    );
			VALIDATE_CLASS( args[2], rb_cNumeric, "width"  );
			VALIDATE_CLASS( args[3], rb_cNumeric, "height" );
			
			// Ensure all arguments are instance of Float or Fixnum.
			if ( !IMMEDIATE_P(args[0]) or !IMMEDIATE_P(args[1]) or !IMMEDIATE_P(args[2]) or !IMMEDIATE_P(args[3]) )
			{
				args[0] = rb_convert_type( args[0], T_FLOAT, "Float", "to_f" );
				args[1] = rb_convert_type( args[1], T_FLOAT, "Float", "to_f" );
				args[2] = rb_convert_type( args[2], T_FLOAT, "Float", "to_f" );
				args[3] = rb_convert_type( args[3], T_FLOAT, "Float", "to_f" );
			}
			
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
	VALUE sfml = rb_define_module( "SFML" );
	globalRectClass = rb_define_class_under( sfml, "Rect", rb_cObject );
	
	// Instance methods
	rb_define_method( globalRectClass, "initialize",      Rect_Initialize,     -1 );
	rb_define_method( globalRectClass, "initialize_copy", Rect_InitializeCopy,  1 );
	rb_define_method( globalRectClass, "==",              Rect_equal,           1 );
	rb_define_method( globalRectClass, "contains",        Rect_Contains,       -1 );
	rb_define_method( globalRectClass, "intersects",      Rect_Intersects,      1 );
	rb_define_method( globalRectClass, "inspect",         Rect_inspect,         0 );
	
	// Attribute accessors
	rb_define_attr( globalRectClass, "left",   1, 1 );
	rb_define_attr( globalRectClass, "top",    1, 1 );
	rb_define_attr( globalRectClass, "width",  1, 1 );
	rb_define_attr( globalRectClass, "height", 1, 1 );
	
	// Instance aliases
	rb_define_alias( globalRectClass, "Contains",   "contains"   );
	rb_define_alias( globalRectClass, "contains?",  "contains"   );
	rb_define_alias( globalRectClass, "include?",   "contains"   );
	rb_define_alias( globalRectClass, "Intersects", "intersects" );
	rb_define_alias( globalRectClass, "&",          "intersects" );
	rb_define_alias( globalRectClass, "to_s",       "inspect"    );
	rb_define_alias( globalRectClass, "to_str",     "inspect"    );
	rb_define_alias( globalRectClass, "Left",       "left"       );
	rb_define_alias( globalRectClass, "Left=",      "left="      );
	rb_define_alias( globalRectClass, "Top",        "top"        );
	rb_define_alias( globalRectClass, "Top=",       "top="       );
	rb_define_alias( globalRectClass, "Width",      "width"      );
	rb_define_alias( globalRectClass, "Width=",     "width="     );
	rb_define_alias( globalRectClass, "Height",     "height"     );
	rb_define_alias( globalRectClass, "Height=",    "height="    );
}
