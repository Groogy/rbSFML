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
 
#include "Vector3.hpp"

static VALUE mSFML;
static VALUE cVector3;

/* Internal:
 * Forces the argument someValue to be a Vector3. If it can convert it then it will.
 * So you can always safely asume that this function returns a Rect object.
 * If it fails then an exception will be thrown.
 */
VALUE Vector3_ForceType( VALUE someValue )
{
	if ( rb_obj_is_kind_of( someValue, cVector3 ) == Qtrue )
	{
		return someValue;
	}
	else if ( rb_obj_is_kind_of( someValue, rb_cNumeric ) == Qtrue )
	{
		VALUE args[] = { someValue, someValue, someValue };
		return rb_class_new_instance( 3, args, cVector3 );
	}
	else if ( rb_obj_is_kind_of( someValue, rb_cArray ) == Qtrue )
	{
		return rb_class_new_instance( RARRAY_LEN( someValue ), RARRAY_PTR( someValue ), cVector3 );
	}
	else
	{
		rb_raise( rb_eTypeError, "can't convert %s into Vector3", rb_obj_classname( someValue ) );
	}
}

// Getter functions:
static VALUE Vector3_GetX( VALUE self )
{
	return rb_iv_get( self, "@x" );
}
static VALUE Vector3_GetY( VALUE self )
{
	return rb_iv_get( self, "@y" );
}
static VALUE Vector3_GetZ( VALUE self )
{
	return rb_iv_get( self, "@z" );
}

// Setter functions:
static VALUE Vector3_SetX( VALUE self, VALUE aVal )
{
	rb_iv_set( self, "@x", aVal );
}
static VALUE Vector3_SetY( VALUE self, VALUE aVal )
{
	rb_iv_set( self, "@y", aVal );
}
static VALUE Vector3_SetZ( VALUE self, VALUE aVal )
{
	rb_iv_set( self, "@z", aVal );
}

/* Internal:
 * Returns the type of the Vector3, outputs 'i' for int or 'f' for float.
 */
int Vector3_Type( VALUE aVector3 )
{
	switch( TYPE( rb_iv_get( aVector3, "@x" ) ) )
	{
	case T_FIXNUM:
		return 'i';
	case T_FLOAT:
		return 'f';
	}
}

/* Internal:
 * Returns a SFML Vector3 from a ruby one. Argument must be a int ruby Vector3 (see Vector3_Type)
 */
sf::Vector3i Vector3_ToSFMLi( VALUE aVector3 )
{
	return sf::Vector3i( FIX2INT( Vector3_GetX( aVector3 ) ), FIX2INT( Vector3_GetY( aVector3 ) ), FIX2INT( Vector3_GetZ( aVector3 ) ) );
}

/* Internal:
 * Returns a SFML Vector3 from a ruby one. Argument must be a float ruby Vector3 (see Vector3_Type)
 */
sf::Vector3f Vector3_ToSFMLf( VALUE aVector3 )
{
	return sf::Vector3f( NUM2DBL( Vector3_GetX( aVector3 ) ), NUM2DBL( Vector3_GetY( aVector3 ) ), NUM2DBL( Vector3_GetZ( aVector3 ) ) );
}

/* Internal:
 * Returns a ruby Vector3 from a SFML one.
 */
VALUE Vector3_ToRuby( const sf::Vector3i &aVector3 )
{
	VALUE args[] = { INT2FIX( aVector3.x ), INT2FIX( aVector3.y ), INT2FIX( aVector3.z ) };
	return rb_class_new_instance( 3, args, cVector3 );
}

/* Internal:
 * Returns a ruby Vector3 from a SFML one.
 */
VALUE Vector3_ToRuby( const sf::Vector3f &aVector3 )
{
	VALUE args[] = { rb_float_new( aVector3.x ), rb_float_new( aVector3.y ), rb_float_new( aVector3.z ) };
	return rb_class_new_instance( 3, args, cVector3 );
}

// Vector3#initialize_copy
static VALUE Vector3_InitializeCopy( VALUE self, VALUE aVector3 )
{
	switch( TYPE( rb_iv_get( aVector3, "@x" ) ) )
	{
		case T_FIXNUM:
			rb_iv_set( self, "@x", rb_iv_get( aVector3, "@x" ) );
			rb_iv_set( self, "@y", rb_iv_get( aVector3, "@y" ) );
			rb_iv_set( self, "@z", rb_iv_get( aVector3, "@z" ) );
			break;
		case T_FLOAT:
			rb_iv_set( self, "@x", rb_float_new( NUM2DBL( rb_iv_get( aVector3, "@x" ) ) ) );
			rb_iv_set( self, "@y", rb_float_new( NUM2DBL( rb_iv_get( aVector3, "@y" ) ) ) );
			rb_iv_set( self, "@z", rb_float_new( NUM2DBL( rb_iv_get( aVector3, "@z" ) ) ) );
			break;
	}
}

// Vector3#-@
static VALUE Vector3_Negate( VALUE self )
{
	VALUE args[] = {
		rb_funcall( rb_iv_get( self, "@x" ), rb_intern( "-@" ), 0 ),
		rb_funcall( rb_iv_get( self, "@y" ), rb_intern( "-@" ), 0 ),
		rb_funcall( rb_iv_get( self, "@z" ), rb_intern( "-@" ), 0 )
	};
	return rb_class_new_instance( 3, args, cVector3 );
}

// Vector3#+
static VALUE Vector3_Add( VALUE self, VALUE aRightOperand )
{
	aRightOperand = Vector3_ForceType( aRightOperand );
	VALUE args[] = {
		rb_funcall( rb_iv_get( self, "@x" ), rb_intern( "+" ), 1, rb_iv_get( aRightOperand, "@x" ) ),
		rb_funcall( rb_iv_get( self, "@y" ), rb_intern( "+" ), 1, rb_iv_get( aRightOperand, "@y" ) ),
		rb_funcall( rb_iv_get( self, "@z" ), rb_intern( "+" ), 1, rb_iv_get( aRightOperand, "@z" ) )
	};
	return rb_class_new_instance( 3, args, cVector3 );
}

// Vector3#-
static VALUE Vector3_Subtract( VALUE self, VALUE aRightOperand )
{
	aRightOperand = Vector3_ForceType( aRightOperand );
	VALUE args[] = {
		rb_funcall( rb_iv_get( self, "@x" ), rb_intern( "-" ), 1, rb_iv_get( aRightOperand, "@x" ) ),
		rb_funcall( rb_iv_get( self, "@y" ), rb_intern( "-" ), 1, rb_iv_get( aRightOperand, "@y" ) ),
		rb_funcall( rb_iv_get( self, "@z" ), rb_intern( "-" ), 1, rb_iv_get( aRightOperand, "@z" ) )
	};
	return rb_class_new_instance( 3, args, cVector3 );
}

// Vector3#*
static VALUE Vector3_Multiply( VALUE self, VALUE aRightOperand )
{
	aRightOperand = Vector3_ForceType( aRightOperand );
	VALUE args[] = {
		rb_funcall( rb_iv_get( self, "@x" ), rb_intern( "*" ), 1, rb_iv_get( aRightOperand, "@x" ) ),
		rb_funcall( rb_iv_get( self, "@y" ), rb_intern( "*" ), 1, rb_iv_get( aRightOperand, "@y" ) ),
		rb_funcall( rb_iv_get( self, "@z" ), rb_intern( "*" ), 1, rb_iv_get( aRightOperand, "@z" ) )
	};
	return rb_class_new_instance( 3, args, cVector3 );
}

// Vector3#/
static VALUE Vector3_Divide( VALUE self, VALUE aRightOperand )
{
	aRightOperand = Vector3_ForceType( aRightOperand );
	VALUE args[] = {
		rb_funcall( rb_iv_get( self, "@x" ), rb_intern( "/" ), 1, rb_iv_get( aRightOperand, "@x" ) ),
		rb_funcall( rb_iv_get( self, "@y" ), rb_intern( "/" ), 1, rb_iv_get( aRightOperand, "@y" ) ),
		rb_funcall( rb_iv_get( self, "@z" ), rb_intern( "/" ), 1, rb_iv_get( aRightOperand, "@z" ) )
	};
	return rb_class_new_instance( 3, args, cVector3 );
}

// Vector3#==
static VALUE Vector3_Equal( VALUE self, VALUE aValue )
{
	if ( CLASS_OF( aValue ) != cVector3 ) return Qfalse;
	if ( !rb_equal( rb_iv_get( self, "@x" ), rb_iv_get( aValue, "@x" ) ) ) return Qfalse;
	if ( !rb_equal( rb_iv_get( self, "@y" ), rb_iv_get( aValue, "@y" ) ) ) return Qfalse;
	if ( !rb_equal( rb_iv_get( self, "@z" ), rb_iv_get( aValue, "@z" ) ) ) return Qfalse;
	return Qtrue;
}

// Vector3#eql?
static VALUE Vector3_StrictEqual( VALUE self, VALUE aValue )
{
	if ( CLASS_OF( aValue ) != cVector3 ) return Qfalse;
	if ( !rb_eql( rb_iv_get( self, "@x" ), rb_iv_get( aValue, "@x" ) ) ) return Qfalse;
	if ( !rb_eql( rb_iv_get( self, "@y" ), rb_iv_get( aValue, "@y" ) ) ) return Qfalse;
	if ( !rb_eql( rb_iv_get( self, "@z" ), rb_iv_get( aValue, "@z" ) ) ) return Qfalse;
	return Qtrue;
}

// Vector3#inspect
static VALUE Vector3_Inspect( VALUE self )
{
	VALUE result = rb_str_new2( "Vector3(" );
	rb_str_append( result, rb_inspect( rb_iv_get( self, "@x" ) ) );
	rb_str_append( result, rb_str_new2( ", " ) );
	rb_str_append( result, rb_inspect( rb_iv_get( self, "@y" ) ) );
	rb_str_append( result, rb_str_new2( ", " ) );
	rb_str_append( result, rb_inspect( rb_iv_get( self, "@z" ) ) );
	rb_str_append( result, rb_str_new2( ")" ) );
	return result;
}

// Vector3#initialize
static VALUE Vector3_Initialize( int argc, VALUE *args, VALUE self )
{	
	switch( argc )
	{
		case 0:
			rb_iv_set( self, "@x", INT2FIX( 0 ) );
			rb_iv_set( self, "@y", INT2FIX( 0 ) );
			rb_iv_set( self, "@z", INT2FIX( 0 ) );
			break;
		case 1:
			Vector3_InitializeCopy( self, Vector3_ForceType( args[0] ) );
			break;
		case 3:
			// Ensure all arguments are kind of Numeric.
			VALIDATE_CLASS( args[0], rb_cNumeric, "x" );
			VALIDATE_CLASS( args[1], rb_cNumeric, "y" );
			VALIDATE_CLASS( args[2], rb_cNumeric, "z" );
			
			// Ensure all arguments are instance of Float or Fixnum.
			if ( !FIXNUM_P( args[0] ) or !FIXNUM_P( args[1] ) or !FIXNUM_P( args[2] ) )
			{
				args[0] = rb_convert_type( args[0], T_FLOAT, "Float", "to_f" );
				args[1] = rb_convert_type( args[1], T_FLOAT, "Float", "to_f" );
				args[2] = rb_convert_type( args[2], T_FLOAT, "Float", "to_f" );
			}
			
			rb_iv_set( self, "@x", args[0] );
			rb_iv_set( self, "@y", args[1] );
			rb_iv_set( self, "@z", args[2] );
			break;
		default:
			rb_raise( rb_eArgError, "wrong number of arguments(%i for 0, 1 or 3)", argc );
	}
	
	return self;
}

// Vector3#memory_usage
static VALUE Vector3_MemoryUsage( VALUE self )
{
	return INT2FIX( 0 );
}

void Init_Vector3( void )
{
	mSFML = rb_define_module( "SFML" );
	cVector3 = rb_define_class_under( mSFML, "Vector3", rb_cObject );
	
	// Instance methods
	rb_define_method( cVector3, "initialize",      Vector3_Initialize,     -1 );
	rb_define_method( cVector3, "initialize_copy", Vector3_InitializeCopy,  1 );
	rb_define_method( cVector3, "inspect",         Vector3_Inspect,         0 );
	rb_define_method( cVector3, "memory_usage",    Vector3_MemoryUsage,     0 );
	rb_define_method( cVector3, "eql?",            Vector3_StrictEqual,     1 );
	rb_define_method( cVector3, "==",              Vector3_Equal,           1 );
	rb_define_method( cVector3, "-@",              Vector3_Negate,          0 );
	rb_define_method( cVector3, "+",               Vector3_Add,             1 );
	rb_define_method( cVector3, "-",               Vector3_Subtract,        1 );
	rb_define_method( cVector3, "*",               Vector3_Multiply,        1 );
	rb_define_method( cVector3, "/",               Vector3_Divide,          1 );
	
	// Attribute accessors
	rb_define_attr( cVector3, "x", 1, 1 );
	rb_define_attr( cVector3, "y", 1, 1 );
	rb_define_attr( cVector3, "z", 1, 1 );
	
	// Instance aliases
	rb_define_alias( cVector3, "to_s",   "inspect" );
	rb_define_alias( cVector3, "to_str", "inspect" );
	rb_define_alias( cVector3, "X",      "x"       );
	rb_define_alias( cVector3, "X=",     "x="      );
	rb_define_alias( cVector3, "Y",      "y"       );
	rb_define_alias( cVector3, "Y=",     "y="      );
	rb_define_alias( cVector3, "Z",      "z"       );
	rb_define_alias( cVector3, "Z=",     "z="      );
	rb_define_alias( cVector3, "equal?", "eql?"    );
}
