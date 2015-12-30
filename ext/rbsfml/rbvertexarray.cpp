/* rbSFML
 * Copyright (c) 2015 Henrik Valter Vogelius Hansson - groogy@groogy.se
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

#include "rbvertexarray.hpp"
#include "rbvertex.hpp"
#include "rbrect.hpp"
#include "error.hpp"
#include "macros.hpp"

rbVertexArrayClass rbVertexArray::ourDefinition;

void rbVertexArray::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbVertexArrayClass::defineClassUnder("VertexArray", sfml);
	ourDefinition.includeModule(rb::Value(rbDrawable::getDefinition()));
	ourDefinition.defineMethod<0>("initialize", &rbVertexArray::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbVertexArray::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbVertexArray::marshalDump);
	ourDefinition.defineMethod<3>("vertex_count", &rbVertexArray::getVertexCount);
	ourDefinition.defineMethod<4>("[]=", &rbVertexArray::setAtIndex);
	ourDefinition.defineMethod<5>("[]", &rbVertexArray::getAtIndex);
	ourDefinition.defineMethod<6>("clear", &rbVertexArray::clear);
	ourDefinition.defineMethod<7>("resize", &rbVertexArray::resize);
	ourDefinition.defineMethod<8>("append", &rbVertexArray::append);
	ourDefinition.defineMethod<9>("primitive_type=", &rbVertexArray::setPrimitiveType);
	ourDefinition.defineMethod<10>("primitive_type", &rbVertexArray::getPrimitiveType);
	ourDefinition.defineMethod<11>("bounds", &rbVertexArray::getBounds);
}

rbVertexArrayClass& rbVertexArray::getDefinition()
{
    return ourDefinition;
}

rbVertexArray::rbVertexArray()
: rbDrawableBaseType()
, myObject()
{
}

rbVertexArray::~rbVertexArray()
{
}

rb::Value rbVertexArray::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
	sf::VertexArray& object = self.to<sf::VertexArray&>();
	switch(args.size())
    {
        case 0:
            break;
        case 2:
            object.resize(args[1].to<unsigned int>());
        case 1:
            object.setPrimitiveType(args[0].to<sf::PrimitiveType>());
            break;
        default:
        	rb::expectedNumArgs(args.size(), 0, 2);
        	break;
    }

	return self;
}

rbVertexArray* rbVertexArray::initializeCopy(const rbVertexArray* value)
{
	myObject = value->myObject;
	return this;
}

rb::Value rbVertexArray::marshalDump() const
{
    rb::raise(rb::TypeError, "can't dump %s", ourDefinition.getName().c_str() );
    return rb::Nil;
}

unsigned int rbVertexArray::getVertexCount() const
{
    return myObject.getVertexCount();
}

void rbVertexArray::setAtIndex(unsigned int index, sf::Vertex vertex)
{
    myObject[index] = vertex;
}

const sf::Vertex& rbVertexArray::getAtIndex(unsigned int index)
{
    return myObject[index];
}

void rbVertexArray::clear()
{
    myObject.clear();
}

void rbVertexArray::resize(unsigned int size)
{
    myObject.resize(size);
}

void rbVertexArray::append(sf::Vertex vertex)
{
    myObject.append(vertex);
}

void rbVertexArray::setPrimitiveType(sf::PrimitiveType type)
{
    myObject.setPrimitiveType(type);
}

sf::PrimitiveType rbVertexArray::getPrimitiveType() const
{
    return myObject.getPrimitiveType();
}

sf::FloatRect rbVertexArray::getBounds() const
{
    return myObject.getBounds();
}

sf::Drawable* rbVertexArray::getDrawable()
{
    return &myObject;
}

const sf::Drawable* rbVertexArray::getDrawable() const
{
    return &myObject;
}

namespace rb
{

template<>
rbVertexArray* Value::to() const
{
	errorHandling(T_DATA);
	rbVertexArray* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbVertexArray, object);
	return object;
}

template<>
const rbVertexArray* Value::to() const
{
	errorHandling(T_DATA);
	const rbVertexArray* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbVertexArray, object);
	return object;
}

template<>
sf::VertexArray& Value::to() const
{
    return to<rbVertexArray*>()->myObject;
}

template<>
const sf::VertexArray& Value::to() const
{
    return to<const rbVertexArray*>()->myObject;
}

}