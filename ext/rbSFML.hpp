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

#ifndef RBSFML_HPP
#define RBSFML_HPP

#include <ruby.h>
#include <new>

#define SFML_VERSION    "2.0-RC"
#define BINDING_VERSION "1.0-RC"

namespace rbMacros
{
	template< typename T >
	static inline void Free( void* someMemory );
	
	template< typename T >
	static inline T* Allocate();

	template< typename T >
	static inline VALUE Allocate( VALUE aKlass );
	
	static inline VALUE RubyAllocate( VALUE aKlass );

    static inline VALUE AbstractAllocate( VALUE aKlass );

    static inline VALUE ToRuby( VALUE anOther, VALUE aKlass );

    template< typename T >
    static inline VALUE ToRuby( T* anObject, VALUE aKlass );
	
	template< typename T >
    static inline VALUE ToRubyNoGC( T* anObject, VALUE aKlass );

    template< typename T >
    static inline VALUE ToConstRuby( const T* anObject, VALUE aKlass );

    template< typename T >
    static inline T* ToSFML( VALUE anObject, VALUE aKlass );
	
    template< typename T >
    static inline void Free( void* someMemory )
    {
        T* object = static_cast< T* >( someMemory );
        object->~T();
        xfree( someMemory );
    }
	
	template< typename T >
	static inline T* Allocate()
	{
		void* memory = xmalloc( sizeof( T ) );
        if( memory == NULL ) rb_memerror();
        T* object = new( memory ) T;
		return object;
	}

    template< typename T >
    static inline VALUE Allocate( VALUE aKlass )
    {
        T* object = Allocate< T >();
        return ToRuby( object, aKlass );
    }

    static inline VALUE RubyAllocate( VALUE aKlass )
    {
        return rb_obj_alloc( aKlass );
    }

    static inline VALUE AbstractAllocate( VALUE aKlass )
    {
        rb_raise( rb_eRuntimeError, "can't allocate instance of abstract class %s", rb_class2name( aKlass ) );
        return Qnil;
    }

    static inline VALUE ToRuby( VALUE anOther, VALUE aKlass )
    {
        if( rb_obj_is_kind_of( anOther, aKlass ) )
            return anOther;

        rb_raise( rb_eTypeError, "can't convert %s into %s",
                  rb_obj_classname( anOther ), rb_class2name( aKlass ) );
    }

    template< typename T >
    static inline VALUE ToRuby( T* anObject, VALUE aKlass )
    {
        return rb_data_object_alloc( aKlass, anObject, NULL, rbMacros::Free< T > );
    }
	
	template< typename T >
    static inline VALUE ToRubyNoGC( T* anObject, VALUE aKlass )
    {
        return rb_data_object_alloc( aKlass, anObject, NULL, NULL );
    }

    template< typename T >
    static inline VALUE ToConstRuby( const T* anObject, VALUE aKlass )
    {
        static ID freezeSymbol = rb_intern( "freeze" );
        VALUE constObj = rb_data_object_alloc( aKlass, const_cast< T* >( anObject ), NULL, NULL );
        rb_funcall( constObj, freezeSymbol, 0 );
        return constObj;
    }

    template< typename T >
    static inline T* ToSFML( VALUE anObject, VALUE aKlass )
    {
        anObject = ToRuby( anObject, aKlass );
        return static_cast< T* >( DATA_PTR( anObject ) );
    }
}
template< typename T >
static inline T MAX( T a, T b )
{
    return a > b ? a : b;
}

template< typename T >
static inline T MIN( T a, T b )
{
    return a > b ? b : a;
}

static inline VALUE MAX( VALUE a, VALUE b )
{
    return rb_funcall( a, rb_intern( ">" ), 1, b ) == Qtrue ? a : b;
}

static inline VALUE MIN( VALUE a, VALUE b )
{
    return rb_funcall( a, rb_intern( ">" ), 1, b ) == Qtrue ? b : a;
}

static inline VALUE RBOOL( bool value )
{
    return value ? Qtrue : Qfalse;
}

typedef VALUE ( *RubyFunctionPtr )( ... );

#define ext_define_module_function( klass, name, func, argc, ... ) \
        rb_define_module_function( klass, name, reinterpret_cast< RubyFunctionPtr >( func ), argc, ##__VA_ARGS__ )

#define ext_define_singleton_method( klass, name, func, argc, ... ) \
        rb_define_singleton_method( klass, name, reinterpret_cast< RubyFunctionPtr >( func ), argc, ##__VA_ARGS__ )

#define ext_define_class_method( klass, name, func, argc, ... ) \
		rb_define_singleton_method( klass, name, reinterpret_cast< RubyFunctionPtr >( func ), argc, ##__VA_ARGS__ )

#define ext_define_method( klass, name, func, argc, ... ) \
        rb_define_method( klass, name, reinterpret_cast< RubyFunctionPtr >( func ), argc, ##__VA_ARGS__ )

#define INVALID_EXPECTED_TYPE( type ) \
		rb_raise( rb_eTypeError, "Did not receive expected type '%s'", rb_class2name( type ) );

#define INVALID_EXPECTED_TYPES( type1, type2 ) \
		rb_raise( rb_eTypeError, "Did not receive expected types ( '%s', '%s' )", rb_class2name( type1 ), rb_class2name( type2 ) );
		
#define INVALID_EXPECTED_TYPES3( type1, type2, type3 ) \
		rb_raise( rb_eTypeError, "Did not receive expected types ( '%s', '%s', '%s' )", rb_class2name( type1 ), rb_class2name( type2 ), rb_class2name( type3 ) );

#define INVALID_EXPECTED_TYPES5( type1, type2, type3, type4, type5 ) \
		rb_raise( rb_eTypeError, "Did not receive expected types ( '%s', '%s', '%s', '%s', '%s' )", \
		rb_class2name( type1 ), rb_class2name( type2 ), rb_class2name( type3 ), rb_class2name( type4 ), rb_class2name( type5 ) );
		
#define INVALID_EXPECTED_TYPES6( type1, type2, type3, type4, type5, type6 ) \
		rb_raise( rb_eTypeError, "Did not receive expected types ( '%s', '%s', '%s', '%s', '%s', '%s' )", \
		rb_class2name( type1 ), rb_class2name( type2 ), rb_class2name( type3 ), rb_class2name( type4 ), rb_class2name( type5 ), rb_class2name( type6 ) );
		
#define INVALID_EXPECTED_TYPES7( type1, type2, type3, type4, type5, type6, type7 ) \
		rb_raise( rb_eTypeError, "Did not receive expected types ( '%s', '%s', '%s', '%s', '%s', '%s', '%s' )", \
		rb_class2name( type1 ), rb_class2name( type2 ), rb_class2name( type3 ), rb_class2name( type4 ), rb_class2name( type5 ), rb_class2name( type6 ), \
		rb_class2name( type7 ) );

#define INVALID_ARGUMENT_LIST( count, argumentList ) \
        rb_raise( rb_eArgError, "wrong number of arguments(%i for %s)", count, argumentList );

#define ISFLOAT( value ) rb_obj_is_kind_of( value, rb_cFloat )

#endif // RBSFML_HPP
