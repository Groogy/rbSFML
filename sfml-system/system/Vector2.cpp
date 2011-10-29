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
 
#include "Vector2.hpp"

static VALUE mSFML;
static VALUE cVector2;

/* Internal:
 * Forces the argument someValue to be a Vector2. If it can convert it then it will.
 * So you can always safely asume that this function returns a Rect object.
 * If it fails then an exception will be thrown.
 */
VALUE Vector2_ForceType( VALUE someValue )
{
	if ( rb_obj_is_kind_of( someValue, cVector2 ) == Qtrue )
	{
		return someValue;
	}
	else if ( rb_obj_is_kind_of( someValue, rb_cNumeric ) == Qtrue )
	{
		VALUE args[] = { someValue, someValue };
		return rb_class_new_instance( 2, args, cVector2 );
	}
	else if ( rb_obj_is_kind_of( someValue, rb_cArray ) == Qtrue )
	{
		return rb_class_new_instance( RARRAY_LEN( someValue ), RARRAY_PTR( someValue ), cVector2 );
	}
	else
	{
		rb_raise( rb_eTypeError, "can't convert %s into Vector2", rb_obj_classname( someValue ) );
	}
}

// Getter functions:
static VALUE Vector2_GetX( VALUE self )
{
	return rb_iv_get( self, "@x" );
}
static VALUE Vector2_GetY( VALUE self )
{
	return rb_iv_get( self, "@y" );
}

// Setter functions:
static VALUE Vector2_SetX( VALUE self, VALUE aVal )
{
	rb_iv_set( self, "@x", aVal );
}
static VALUE Vector2_SetY( VALUE self, VALUE aVal )
{
	rb_iv_set( self, "@y", aVal );
}

/* Internal:
 * Returns the type of the Vector2, outputs 'i' for int or 'f' for float.
 */
int Vector2_Type( VALUE aVector2 )
{
	switch( TYPE( rb_iv_get( aVector2, "@x" ) ) )
	{
	case T_FIXNUM:
		return 'i';
	case T_FLOAT:
		return 'f';
	}
}

/* Internal:
 * Returns a SFML vector2 from a ruby one. Argument must be a int ruby vector2 (see Vector2_Type)
 */
sf::Vector2i Vector2_ToSFMLi( VALUE aVector2 )
{
	return sf::Vector2i( FIX2INT( Vector2_GetX( aVector2 ) ), FIX2INT( Vector2_GetY( aVector2 ) ) );
}

/* Internal:
 * Returns a SFML vector2 from a ruby one. Argument must be a float ruby vector2 (see Vector2_Type)
 */
sf::Vector2f Vector2_ToSFMLf( VALUE aVector2 )
{
	return sf::Vector2f( NUM2DBL( Vector2_GetX( aVector2 ) ), NUM2DBL( Vector2_GetY( aVector2 ) ) );
}

/* Internal:
 * Returns a ruby vector2 from a SFML one.
 */
VALUE Vector2_ToRuby( const sf::Vector2i &aVector2 )
{
	VALUE args[] = { INT2FIX( aVector2.x ), INT2FIX( aVector2.y ) };
	return rb_class_new_instance( 2, args, cVector2 );
}

/* Internal:
 * Returns a ruby vector2 from a SFML one.
 */
VALUE Vector2_ToRuby( const sf::Vector2f &aVector2 )
{
	VALUE args[] = { rb_float_new( aVector2.x ), rb_float_new( aVector2.y ) };
	return rb_class_new_instance( 2, args, cVector2 );
}

// Vector2#initialize_copy
static VALUE Vector2_InitializeCopy( VALUE self, VALUE aVector2 )
{
	switch( TYPE( rb_iv_get( aVector2, "@x" ) ) )
	{
		case T_FIXNUM:
			rb_iv_set( self, "@x", rb_iv_get( aVector2, "@x" ) );
			rb_iv_set( self, "@y", rb_iv_get( aVector2, "@y" ) );
			break;
		case T_FLOAT:
			rb_iv_set( self, "@x", rb_float_new( NUM2DBL( rb_iv_get( aVector2, "@x" ) ) ) );
			rb_iv_set( self, "@y", rb_float_new( NUM2DBL( rb_iv_get( aVector2, "@y" ) ) ) );
			break;
	}
}

// Vector2#-@
static VALUE Vector2_Negate( VALUE self )
{
	VALUE args[] = {
		rb_funcall( rb_iv_get( self, "@x" ), rb_intern( "-@" ), 0 ),
		rb_funcall( rb_iv_get( self, "@y" ), rb_intern( "-@" ), 0 )
	};
	return rb_class_new_instance( 2, args, cVector2 );
}

// Vector2#+
static VALUE Vector2_Add( VALUE self, VALUE aRightOperand )
{
	aRightOperand = Vector2_ForceType( aRightOperand );
	VALUE args[] = {
		rb_funcall( rb_iv_get( self, "@x" ), rb_intern( "+" ), 1, rb_iv_get( aRightOperand, "@x" ) ),
		rb_funcall( rb_iv_get( self, "@y" ), rb_intern( "+" ), 1, rb_iv_get( aRightOperand, "@y" ) )
	};
	return rb_class_new_instance( 2, args, cVector2 );
}

// Vector2#-
static VALUE Vector2_Subtract( VALUE self, VALUE aRightOperand )
{
	aRightOperand = Vector2_ForceType( aRightOperand );
	VALUE args[] = {
		rb_funcall( rb_iv_get( self, "@x" ), rb_intern( "-" ), 1, rb_iv_get( aRightOperand, "@x" ) ),
		rb_funcall( rb_iv_get( self, "@y" ), rb_intern( "-" ), 1, rb_iv_get( aRightOperand, "@y" ) )
	};
	return rb_class_new_instance( 2, args, cVector2 );
}

// Vector2#*
static VALUE Vector2_Multiply( VALUE self, VALUE aRightOperand )
{
	aRightOperand = Vector2_ForceType( aRightOperand );
	VALUE args[] = {
		rb_funcall( rb_iv_get( self, "@x" ), rb_intern( "*" ), 1, rb_iv_get( aRightOperand, "@x" ) ),
		rb_funcall( rb_iv_get( self, "@y" ), rb_intern( "*" ), 1, rb_iv_get( aRightOperand, "@y" ) )
	};
	return rb_class_new_instance( 2, args, cVector2 );
}

// Vector2#/
static VALUE Vector2_Divide( VALUE self, VALUE aRightOperand )
{
	aRightOperand = Vector2_ForceType( aRightOperand );
	VALUE args[] = {
		rb_funcall( rb_iv_get( self, "@x" ), rb_intern( "/" ), 1, rb_iv_get( aRightOperand, "@x" ) ),
		rb_funcall( rb_iv_get( self, "@y" ), rb_intern( "/" ), 1, rb_iv_get( aRightOperand, "@y" ) )
	};
	return rb_class_new_instance( 2, args, cVector2 );
}

// Vector2#==
static VALUE Vector2_Equal( VALUE self, VALUE aValue )
{
	if ( CLASS_OF( aValue ) != cVector2 ) return Qfalse;
	if ( !rb_equal( rb_iv_get( self, "@x" ), rb_iv_get( aValue, "@x" ) ) ) return Qfalse;
	if ( !rb_equal( rb_iv_get( self, "@y" ), rb_iv_get( aValue, "@y" ) ) ) return Qfalse;
	return Qtrue;
}

// Vector2#eql?
static VALUE Vector2_StrictEqual( VALUE self, VALUE aValue )
{
	if ( CLASS_OF( aValue ) != cVector2 ) return Qfalse;
	if ( !rb_eql( rb_iv_get( self, "@x" ), rb_iv_get( aValue, "@x" ) ) ) return Qfalse;
	if ( !rb_eql( rb_iv_get( self, "@y" ), rb_iv_get( aValue, "@y" ) ) ) return Qfalse;
	return Qtrue;
}

// Vector2#inspect
static VALUE Vector2_Inspect( VALUE self )
{
	VALUE result = rb_str_new2( "Vector2(" );
	rb_str_append( result, rb_inspect( rb_iv_get( self, "@x" ) ) );
	rb_str_append( result, rb_str_new2( ", " ) );
	rb_str_append( result, rb_inspect( rb_iv_get( self, "@y" ) ) );
	rb_str_append( result, rb_str_new2( ")" ) );
	return result;
}

// Vector2#initialize
static VALUE Vector2_Initialize( int argc, VALUE *args, VALUE self )
{	
	switch( argc )
	{
		case 0:
			rb_iv_set( self, "@x", INT2FIX( 0 ) );
			rb_iv_set( self, "@y", INT2FIX( 0 ) );
			break;
		case 1:
			Vector2_InitializeCopy( self, Vector2_ForceType( args[0] ) );
			break;
		case 2:
			// Ensure all arguments are kind of Numeric.
			VALIDATE_CLASS( args[0], rb_cNumeric, "x" );
			VALIDATE_CLASS( args[1], rb_cNumeric, "y" );
			
			// Ensure all arguments are instance of Float or Fixnum.
			if ( !FIXNUM_P( args[0] ) or !FIXNUM_P( args[1] ) )
			{
				args[0] = rb_convert_type( args[0], T_FLOAT, "Float", "to_f" );
				args[1] = rb_convert_type( args[1], T_FLOAT, "Float", "to_f" );
			}
			
			rb_iv_set( self, "@x", args[0] );
			rb_iv_set( self, "@y", args[1] );
			break;
		default:
			rb_raise( rb_eArgError, "wrong number of arguments(%i for 0..2)", argc );
	}
	
	return self;
}

// Vector2#memory_usage
static VALUE Vector2_MemoryUsage( VALUE self )
{
	return INT2FIX( 0 );
}

void Init_Vector2( void )
{
	mSFML = rb_define_module( "SFML" );
	cVector2 = rb_define_class_under( mSFML, "Vector2", rb_cObject );
	
	// Instance methods
	rb_define_method( cVector2, "initialize",      Vector2_Initialize,     -1 );
	rb_define_method( cVector2, "initialize_copy", Vector2_InitializeCopy,  1 );
	rb_define_method( cVector2, "inspect",         Vector2_Inspect,         0 );
	rb_define_method( cVector2, "memory_usage",    Vector2_MemoryUsage,     0 );
	rb_define_method( cVector2, "eql?",            Vector2_StrictEqual,     1 );
	rb_define_method( cVector2, "==",              Vector2_Equal,           1 );
	rb_define_method( cVector2, "-@",              Vector2_Negate,          0 );
	rb_define_method( cVector2, "+",               Vector2_Add,             1 );
	rb_define_method( cVector2, "-",               Vector2_Subtract,        1 );
	rb_define_method( cVector2, "*",               Vector2_Multiply,        1 );
	rb_define_method( cVector2, "/",               Vector2_Divide,          1 );
	
	// Attribute accessors
	rb_define_attr( cVector2, "x", 1, 1 );
	rb_define_attr( cVector2, "y", 1, 1 );
	
	// Instance aliases
	rb_define_alias( cVector2, "to_s",   "inspect" );
	rb_define_alias( cVector2, "to_str", "inspect" );
	rb_define_alias( cVector2, "X",      "x"       );
	rb_define_alias( cVector2, "X=",     "x="      );
	rb_define_alias( cVector2, "Y",      "y"       );
	rb_define_alias( cVector2, "Y=",     "y="      );
	rb_define_alias( cVector2, "equal?", "eql?"    );
}
