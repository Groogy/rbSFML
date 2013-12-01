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

#define EXTRA_VERTEX_BUFFER_OBJECT_CPP

#include <gl/glew.h>
#include <gl/gl.h>

#include "VertexBufferObject.hpp"
#include "Effect.hpp"
#include "EffectImp.hpp"
#include "../System/NonCopyable.hpp"
#include "../Graphics/Drawable.hpp"
#include "../Graphics/Transformable.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

enum DataType
{
	Float = GL_FLOAT,
	Integer = GL_INT
};

enum Primitive
{
	Points          = GL_POINTS,
	Lines           = GL_LINES,
  LineStrip       = GL_LINE_STRIP,
	Triangles       = GL_TRIANGLES,
	TriangleStrip   = GL_TRIANGLE_STRIP,
  TriangleFan     = GL_TRIANGLE_FAN
};

struct VertexLayout
{
	struct Attribute
	{
		int size;
		DataType type;
		std::size_t stride;
		std::size_t offset;
	};

	std::vector<Attribute> attributes;
};


class VertexBufferObject : public sf::Drawable
{
public:
	VertexBufferObject()
	: mySelf( Qnil )
	, myVAO( 0 )
	, myBufferObjectID( 0 )
	, myVertexData()
	, myPrimitive( Points )
	, myLayout()
	, myEffect( NULL )
	, myNeedBuild( true )
	, myNeedUpdate( false )
	, myNeedVertexLayoutUpdate( true )
	{
	}
	
	virtual ~VertexBufferObject()
	{
		glDeleteBuffers( 1, &myBufferObjectID );
		glDeleteVertexArrays( 1, &myVAO );
	}
	
	void Initialize( VALUE aSelf, VALUE aLayout )
	{
		mySelf = aSelf;
		CreateLayoutCache( aLayout );
		
		glGenVertexArrays( 1, &myVAO );
		glBindVertexArray( myVAO );

		glGenBuffers( 1, &myBufferObjectID );

		glBindVertexArray( 0 );
	}
	
	void SetPrimitive( Primitive aPrimitive )
	{
		myPrimitive = aPrimitive;
	}

	Primitive GetPrimitive() const
	{
		return myPrimitive;
	}
  
  void SetEffect( Shader* anEffect )
	{
		myEffect = anEffect;
	}

	void SetVertexLayout( VALUE aLayout )
	{
		CreateLayoutCache( aLayout );
	}

	const VertexLayout& GetVertexLayout() const
	{
		return myLayout;
	}

	void AddVertexData( const std::vector<char>& someData )
	{
		myVertexData.insert( myVertexData.end(), someData.begin(), someData.end() );
		myNeedBuild = true;
	}

	void AddVertexData( const char someData[], std::size_t aCount )
	{
		for( std::size_t index = 0; index < aCount; index++ )
		{
			myVertexData.push_back( someData[index] );
		}
		myNeedBuild = true;
	}

	void ModifyVertexData(std::size_t anIndex, const std::vector<char>& someData)
	{
		ModifyVertexData( anIndex, someData.data(), someData.size() );
	}

	void ModifyVertexData( std::size_t anIndex, const char data[], std::size_t aCount )
	{
		for( std::size_t dataIndex = 0; dataIndex < aCount; dataIndex++, anIndex++ )
		{
			myVertexData[anIndex] = data[dataIndex];
		}
		myNeedUpdate = true;
	}
	
	std::size_t GetNumVertexes() const
	{
		std::size_t vertexSize = GetVertexSize();
		if(vertexSize <= 0)
			return 0;

		return myVertexData.size() / vertexSize;
	}

	std::size_t GetVertexSize() const
	{
		std::size_t size = 0;
		for(int i = 0, nSize = myLayout.attributes.size(); i < nSize; i++)
		{
			std::size_t typeSize = 0;
			const VertexLayout::Attribute& attribute = myLayout.attributes[i];
			switch(attribute.type)
			{
			case Float:
				typeSize += sizeof(float);
				break;
			case Integer:
				typeSize += sizeof(int);
				break;
			}

			size += typeSize * attribute.size;
		}
		return size;
	}
	
	void draw( sf::RenderTarget& aTarget, sf::RenderStates someStates ) const
	{
		Bind();
    if( myEffect )
      myEffect->bind();
      
    glDrawArrays(myPrimitive, 0, GetNumVertexes());
	}
	
	void Bind() const
	{
		glBindVertexArray( myVAO );
		glBindBuffer( GL_ARRAY_BUFFER, myBufferObjectID );
		if( myNeedBuild )
		{
			glBufferData( GL_ARRAY_BUFFER, myVertexData.size() * sizeof(char), myVertexData.data(), GL_STATIC_DRAW );
			myNeedBuild = false;
		}
		if( myNeedUpdate )
		{
			glBufferSubData( GL_ARRAY_BUFFER, 0, myVertexData.size() * sizeof(char), myVertexData.data() );
			myNeedUpdate = false;
		}

		if( myNeedVertexLayoutUpdate )
		{
			for( int i = 0, nSize = myLayout.attributes.size(); i < nSize; i++ )
			{
				const VertexLayout::Attribute& attribute = myLayout.attributes[i];
				glEnableVertexAttribArray(i);
				glVertexAttribPointer( i, static_cast<GLint>( attribute.size ), attribute.type, GL_FALSE, static_cast<GLsizei>( attribute.stride ), reinterpret_cast<const GLvoid*>( attribute.offset ) );
			}
			myNeedVertexLayoutUpdate = false;
		}
	}
	
	void CreateLayoutCache( VALUE aLayout )
	{
    rbSFML::PrepareErrorStream();
		myNeedVertexLayoutUpdate = true;
		myLayout.attributes.clear();
		
		VALUE attributes = rb_iv_get( aLayout, "@attributes" );
		unsigned int numAttributes = RARRAY_LEN( attributes );
		for( unsigned int index = 0; index < numAttributes; index++ )
		{
			VALUE attributeRaw = rb_ary_entry( attributes, index );
			VertexLayout::Attribute attribute;
			attribute.size = FIX2INT( rb_hash_aref( attributeRaw, ID2SYM( rb_intern( "size" ) ) ) );
			attribute.stride = FIX2INT( rb_hash_aref( attributeRaw, ID2SYM( rb_intern( "stride" ) ) ) );
			attribute.offset = FIX2INT( rb_hash_aref( attributeRaw, ID2SYM( rb_intern( "offset" ) ) ) );
			
			VALUE typeClass = rb_hash_aref( attributeRaw, ID2SYM( rb_intern( "type" ) ) );
			if( typeClass == rb_cFloat )
				attribute.type = Float;
			else if( typeClass == rb_cFixnum )
				attribute.type = Integer;
			else
				sf::err() << "Unsupported data type for vertex layout attribute #" << index << std::endl;
				
			myLayout.attributes.push_back( attribute );
		}
    rbSFML::CheckRaise();
	}
	
private:
	VALUE mySelf;
	GLuint myVAO;
  GLuint myBufferObjectID;
  std::vector<char> myVertexData;
  Primitive myPrimitive;
  VertexLayout myLayout;
  Shader* myEffect;
  mutable bool myNeedBuild;
  mutable bool myNeedUpdate;
  mutable bool myNeedVertexLayoutUpdate;
};

template<typename Type>
void appendRawData( std::vector<char>& aResult, const Type& aValue )
{
  char rawValue[ sizeof( Type ) ];
  memcpy( rawValue, &aValue, sizeof( Type ) );
  for ( int index = 0; index < sizeof( Type ); index++ )
  {
    aResult.push_back( rawValue[ index ] );
  }
}

void rbVertexBufferObject::Init( VALUE SFML )
{
  rbVertexBufferObject::Class = rb_define_class_under( SFML, "VertexBufferObject", rb_cObject );
	rb_include_module( rbVertexBufferObject::Class, rbDrawable::Module );
	rb_include_module( rbVertexBufferObject::Class, rbTransformable::Module );
	rb_include_module( rbVertexBufferObject::Class, rbNonCopyable::Module );
	
	// Class methods
	rb_define_alloc_func( rbVertexBufferObject::Class, rbMacros::Allocate< VertexBufferObject > );

  // Instance methods
  ext_define_method( rbVertexBufferObject::Class, "initialize", rbVertexBufferObject::Initialize, 1 );
  ext_define_method( rbVertexBufferObject::Class, "primitive=", rbVertexBufferObject::SetPrimitive, 1 );
  ext_define_method( rbVertexBufferObject::Class, "primitive", rbVertexBufferObject::GetPrimitive, 0 );
  ext_define_method( rbVertexBufferObject::Class, "effect=", rbVertexBufferObject::SetEffect, 1 );
  ext_define_method( rbVertexBufferObject::Class, "effect", rbVertexBufferObject::GetEffect, 0 );
  ext_define_method( rbVertexBufferObject::Class, "num_vertices", rbVertexBufferObject::GetNumVertices, 0 );
  ext_define_method( rbVertexBufferObject::Class, "vertex_size", rbVertexBufferObject::GetVertexSize, 0 );
	ext_define_method( rbVertexBufferObject::Class, "<<", rbVertexBufferObject::Append, 1 );
}

// VertexBufferObject#initialize
VALUE rbVertexBufferObject::Initialize( VALUE aSelf, VALUE aLayout )
{
	rbMacros::ToSFML< VertexBufferObject >( aSelf, rbVertexBufferObject::Class )->Initialize( aSelf, aLayout );
	return aSelf;
}

// VertexBufferObject#<<
VALUE rbVertexBufferObject::Append( VALUE aSelf, VALUE someData )
{
  rbSFML::PrepareErrorStream();
	VALUE data = rb_funcall( someData, rb_intern( "flatten" ), 0 );
  std::vector<char> result;
	for( unsigned int index = 0, end = RARRAY_LEN( data ); index < end; index++ )
	{
    VALUE entry = rb_ary_entry( data, index );
    switch( rb_type( entry ) )
    {
      case T_FLOAT:
      {
        float value = NUM2DBL( entry );
        appendRawData(result, value);
      }
      break;
      case T_FIXNUM:
      {
        int value = FIX2INT( entry );
        appendRawData(result, value);
      }
      break;
      default:
        sf::err() << "Received invalid data for vertex!" << std::endl;
    }
	}
  
  rbSFML::CheckRaise();
	
	rbMacros::ToSFML< VertexBufferObject >( aSelf, rbVertexBufferObject::Class )->AddVertexData( result );
	return aSelf;
}

// VertexBufferObject#primitive=(primitive)
VALUE rbVertexBufferObject::SetPrimitive( VALUE aSelf, VALUE aPrimitive )
{
  rbSFML::PrepareErrorStream();
  sf::PrimitiveType primitive = static_cast< sf::PrimitiveType >( FIX2INT( aPrimitive ) );
  Primitive glPrimitive;
  switch( primitive )
  {
    case sf::Points:          glPrimitive = Points; break;
    case sf::Lines:           glPrimitive = Lines; break;
    case sf::LinesStrip:      glPrimitive = LineStrip; break;
    case sf::Triangles:       glPrimitive = Triangles; break;
    case sf::TrianglesStrip:  glPrimitive = TriangleStrip; break;
    case sf::TrianglesFan:    glPrimitive = TriangleFan; break;
    case sf::Quads:
    default:
      sf::err() << "Invalid primitive given" << std::endl;
  }
  
  rbSFML::CheckRaise();
  
  rbMacros::ToSFML< VertexBufferObject >( aSelf, rbVertexBufferObject::Class )->SetPrimitive( glPrimitive );
  return aPrimitive;
}

// VertexBufferObject#primitive
VALUE rbVertexBufferObject::GetPrimitive( VALUE aSelf )
{
  Primitive glPrimitive = rbMacros::ToSFML< VertexBufferObject >( aSelf, rbVertexBufferObject::Class )->GetPrimitive();
  sf::PrimitiveType primitive;
  
  switch( glPrimitive )
  {
    case Points:         primitive = sf::Points; break;
    case Lines:          primitive = sf::Lines; break;
    case LineStrip:      primitive = sf::LinesStrip; break;
    case Triangles:      primitive = sf::Triangles; break;
    case TriangleStrip:  primitive = sf::TrianglesStrip; break;
    case TriangleFan:    primitive = sf::TrianglesFan; break;
  }
  
  return INT2FIX( primitive );
}

// VertexBufferObject#effect=(effect)
VALUE rbVertexBufferObject::SetEffect( VALUE aSelf, VALUE aEffect )
{
  rb_iv_set( aSelf, "@__ref__effect", aEffect );
  Shader* effect = rbMacros::ToSFML< Shader >( aEffect, rbEffect::Class );
  rbMacros::ToSFML< VertexBufferObject >( aSelf, rbVertexBufferObject::Class )->SetEffect( effect );
  return Qnil;
}
  
// VertexBufferObject#effect
VALUE rbVertexBufferObject::GetEffect( VALUE aSelf )
{
  return rb_iv_get( aSelf, "@__ref__effect" );
}

// VertexBufferObject#num_vertices
static VALUE rbVertexBufferObject::GetNumVertices( VALUE aSelf )
{
  return INT2FIX( rbMacros::ToSFML< VertexBufferObject >( aSelf, rbVertexBufferObject::Class )->GetNumVertexes() );
}
  
// VertexBufferObject#vertex_size
static VALUE rbVertexBufferObject::GetVertexSize( VALUE aSelf )
{
  return INT2FIX( rbMacros::ToSFML< VertexBufferObject >( aSelf, rbVertexBufferObject::Class )->GetVertexSize() );
}
