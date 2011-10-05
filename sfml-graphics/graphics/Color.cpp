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

/* Free a heap allocated object 
 * Not accessible trough ruby directly!
 */
static void Color_Free( sf::Color *anObject )
{
	delete anObject;
}

/* Internal function
 * Forces the argument someValue to be a Color. If it can convert it then it will.
 * So you can always safely asume that this function returns a Color object.
 * If it fails then an exception will be thrown.
 */
VALUE Color_ForceType( VALUE someValue )
{
	if( rb_obj_is_kind_of( someValue, globalColorClass ) == Qtrue )
	{
		return someValue;
	}
	else if( rb_obj_is_kind_of( someValue, rb_cArray ) == Qtrue )
	{
		return rb_class_new_instance( RARRAY_LEN( someValue ), RARRAY_PTR( someValue ), globalColorClass );
	}
	else
	{
		rb_raise( rb_eTypeError, "can't convert %s into Color", rb_obj_classname( someValue ) );
	}
}

// Ruby method: r
VALUE Color_GetR( VALUE self ) {
	sf::Color *color = Color_ToSFML( self );
	return INT2FIX( color->r );
}

// Ruby method: g
VALUE Color_GetG( VALUE self ) {
	sf::Color *color = Color_ToSFML( self );
	return INT2FIX( color->g );
}

// Ruby method: b
VALUE Color_GetB( VALUE self ) {
	sf::Color *color = Color_ToSFML( self );
	return INT2FIX( color->b );
}

// Ruby method: a
VALUE Color_GetA( VALUE self ) {
	sf::Color *color = Color_ToSFML( self );
	return INT2FIX( color->a );
}

// Ruby method: r=
VALUE Color_SetR( VALUE self, VALUE aVal ) {
	rb_check_frozen( self );
	sf::Color *color = Color_ToSFML( self );
	color->r = FIX2INT( aVal );
}

// Ruby method: g=
VALUE Color_SetG( VALUE self, VALUE aVal ) {
	rb_check_frozen( self );
	sf::Color *color = Color_ToSFML( self );
	color->g = FIX2INT( aVal );
}

// Ruby method: b=
VALUE Color_SetB( VALUE self, VALUE aVal ) {
	rb_check_frozen( self );
	sf::Color *color = Color_ToSFML( self );
	color->b = FIX2INT( aVal );
}

// Ruby method: a=
VALUE Color_SetA( VALUE self, VALUE aVal ) {
	rb_check_frozen( self );
	sf::Color *color = Color_ToSFML( self );
	color->a = FIX2INT( aVal );
}

/* Internal:
 * Returns a SFML color from a ruby one.
 */
sf::Color* Color_ToSFML( VALUE aColor ) {
	sf::Color *object = NULL;
	Data_Get_Struct( aColor, sf::Color, object );
	return object;
}

/* Internal:
 * Returns a ruby object from a pointer. It assumes that the pointer
 * will not be freed and will never be invalid. (It frees the pointer
 * when the object is gabage collected.)
 */
VALUE Color_ToRuby( sf::Color *aColor )
{
	return Data_Wrap_Struct( globalColorClass, 0, Color_Free, aColor );
}

/* Internal:
 * Returns a ruby object from a reference. It assumes that the return value
 * will not be sent to the end user and that the object will free itself.
 */
VALUE Color_ToRuby( sf::Color &aColor )
{
	return Data_Wrap_Struct( globalColorClass, 0, 0, &aColor );
}

// Ruby method: initialize_copy
static VALUE Color_InitializeCopy( VALUE self, VALUE aSource )
{
	sf::Color *object = Color_ToSFML( self );
	sf::Color *source = Color_ToSFML( aSource );
	*object = *source;
}

// Ruby method: +
static VALUE Color_Add( VALUE self, VALUE aRightOperand )
{
	sf::Color *left = Color_ToSFML( self );
	sf::Color *right = Color_ToSFML( Color_ForceType( aRightOperand ) );
	sf::Color *result = new sf::Color( (*left) + (*right) );
	return Color_ToRuby( result );
}

// Ruby method: *
static VALUE Color_Multiply( VALUE self, VALUE aRightOperand )
{
	sf::Color *left = Color_ToSFML( self );
	sf::Color *right = Color_ToSFML( Color_ForceType( aRightOperand ) );
	sf::Color *result = new sf::Color( (*left) * (*right) );
	return Color_ToRuby( result );
}

// Ruby method: ==
static VALUE Color_Equal( VALUE self, VALUE anArgument )
{
	sf::Color *left = Color_ToSFML( self );
	sf::Color *right = Color_ToSFML( Color_ForceType( anArgument ) );
	return (*left) == (*right) ? Qtrue : Qfalse;
}

// Ruby method: inspect
static VALUE Color_inspect( VALUE self )
{
	sf::Color* color = Color_ToSFML( self );
	VALUE r = rb_inspect( INT2FIX( color->r ) );
	VALUE g = rb_inspect( INT2FIX( color->g ) );
	VALUE b = rb_inspect( INT2FIX( color->b ) );
	VALUE a = rb_inspect( INT2FIX( color->a ) );
	VALUE comma  = rb_str_new2( ", " );
	VALUE rparen = rb_str_new2( ")" );
	VALUE result = rb_str_new2( "Color(" );
	rb_str_concat( result, r      );
	rb_str_concat( result, comma  );
	rb_str_concat( result, g      );
	rb_str_concat( result, comma  );
	rb_str_concat( result, b      );
	rb_str_concat( result, comma  );
	rb_str_concat( result, a      );
	rb_str_concat( result, rparen );
	return result;
}

// Ruby method: initialize
static VALUE Color_Initialize( int argc, VALUE * args, VALUE self )
{
	sf::Color *color = Color_ToSFML( self );
	color->a = 255;
	
	switch( argc )
	{
		case 0:
			color->r = 0;
			color->g = 0;
			color->b = 0;
			break;
		case 1:
			Color_InitializeCopy( self, Color_ForceType( args[0] ) );
			break;
		case 4:
			VALIDATE_CLASS( args[3], rb_cFixnum, "alpha" );
			color->a = FIX2INT( args[3] );
		case 3:
			VALIDATE_CLASS( args[0], rb_cFixnum, "red" );
			VALIDATE_CLASS( args[1], rb_cFixnum, "green" );
			VALIDATE_CLASS( args[2], rb_cFixnum, "blue" );
			color->r = FIX2INT( args[0] );
			color->g = FIX2INT( args[1] );
			color->b = FIX2INT( args[2] );
			break;
		default:
			rb_raise( rb_eArgError, "Expected 0, 1, 3 or 4 arguments but was given %d", argc );
	}
	return self;
}

// Ruby method: memory_usage
static VALUE Color_MemoryUsage( VALUE self )
{
	return INT2FIX( sizeof( sf::Color ) );
}

// Ruby method: allocate
static VALUE Color_Alloc( VALUE aKlass )
{
	sf::Color *object = new sf::Color();
	return Data_Wrap_Struct( aKlass, 0, Color_Free, object );
}

/* Internal:
 * Creates the Color class.
 */
void Init_Color( void )
{
	VALUE sfml = rb_define_module( "SFML" );
	globalColorClass = rb_define_class_under( sfml, "Color", rb_cObject );
	
	// Class methods
	rb_define_alloc_func( globalColorClass, Color_Alloc );
	
	// Instance methods
	rb_define_method( globalColorClass, "initialize",      Color_Initialize,     -1 );
	rb_define_method( globalColorClass, "initialize_copy", Color_InitializeCopy,  1 );
	rb_define_method( globalColorClass, "+",               Color_Add,             1 );
	rb_define_method( globalColorClass, "*",               Color_Multiply,        1 );
	rb_define_method( globalColorClass, "==",              Color_Equal,           1 );
	rb_define_method( globalColorClass, "inspect",         Color_inspect,         0 );
	rb_define_method( globalColorClass, "r",               Color_GetR,            0 );
	rb_define_method( globalColorClass, "g",               Color_GetG,            0 );
	rb_define_method( globalColorClass, "b",               Color_GetB,            0 );
	rb_define_method( globalColorClass, "a",               Color_GetA,            0 );
	rb_define_method( globalColorClass, "r=",              Color_SetR,            1 );
	rb_define_method( globalColorClass, "g=",              Color_SetG,            1 );
	rb_define_method( globalColorClass, "b=",              Color_SetB,            1 );
	rb_define_method( globalColorClass, "a=",              Color_SetA,            1 );
	rb_define_method( globalColorClass, "memory_usage",    Color_MemoryUsage,     0 );
	
	// Instance aliasses
	rb_define_alias( globalColorClass, "red",    "r"       );
	rb_define_alias( globalColorClass, "red=",   "r="      );
	rb_define_alias( globalColorClass, "green",  "g"       );
	rb_define_alias( globalColorClass, "green=", "g="      );
	rb_define_alias( globalColorClass, "blue",   "b"       );
	rb_define_alias( globalColorClass, "blue=",  "b="      );
	rb_define_alias( globalColorClass, "alpha",  "a"       );
	rb_define_alias( globalColorClass, "alpha=", "a="      );
	rb_define_alias( globalColorClass, "to_s",   "inspect" );
	rb_define_alias( globalColorClass, "to_str", "inspect" );
	
	// Class constants
	VALUE const_black   = Data_Wrap_Struct( globalColorClass, 0, 0, const_cast< sf::Color * >( &sf::Color::Black   ) );
	VALUE const_white   = Data_Wrap_Struct( globalColorClass, 0, 0, const_cast< sf::Color * >( &sf::Color::White   ) );
	VALUE const_red     = Data_Wrap_Struct( globalColorClass, 0, 0, const_cast< sf::Color * >( &sf::Color::Red     ) );
	VALUE const_green   = Data_Wrap_Struct( globalColorClass, 0, 0, const_cast< sf::Color * >( &sf::Color::Green   ) );
	VALUE const_blue    = Data_Wrap_Struct( globalColorClass, 0, 0, const_cast< sf::Color * >( &sf::Color::Blue    ) );
	VALUE const_yellow  = Data_Wrap_Struct( globalColorClass, 0, 0, const_cast< sf::Color * >( &sf::Color::Yellow  ) );
	VALUE const_magenta = Data_Wrap_Struct( globalColorClass, 0, 0, const_cast< sf::Color * >( &sf::Color::Magenta ) );
	VALUE const_cyan    = Data_Wrap_Struct( globalColorClass, 0, 0, const_cast< sf::Color * >( &sf::Color::Cyan    ) );
  
	rb_define_const( globalColorClass, "Black",   const_black   );
	rb_define_const( globalColorClass, "White",   const_white   );
	rb_define_const( globalColorClass, "Red",     const_red     );
	rb_define_const( globalColorClass, "Green",   const_green   );
	rb_define_const( globalColorClass, "Blue",    const_blue    );
	rb_define_const( globalColorClass, "Yellow",  const_yellow  );
	rb_define_const( globalColorClass, "Magenta", const_magenta );
	rb_define_const( globalColorClass, "Cyan",    const_cyan    );
	
	rb_funcall( const_black,   rb_intern( "freeze" ), 0 );
	rb_funcall( const_white,   rb_intern( "freeze" ), 0 );
	rb_funcall( const_red,     rb_intern( "freeze" ), 0 );
	rb_funcall( const_green,   rb_intern( "freeze" ), 0 );
	rb_funcall( const_blue,    rb_intern( "freeze" ), 0 );
	rb_funcall( const_yellow,  rb_intern( "freeze" ), 0 );
	rb_funcall( const_magenta, rb_intern( "freeze" ), 0 );
	rb_funcall( const_cyan,    rb_intern( "freeze" ), 0 );
}
