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

#include "rbrect.hpp"
#include "error.hpp"
#include "macros.hpp"

namespace 
{
	constexpr char symVarLeft[] = "@left";
	constexpr char symVarTop[] = "@top";
	constexpr char symVarWidth[] = "@width";
	constexpr char symVarHeight[] = "@height";

	constexpr char symInspect[] = "inspect";
}

rbRectClass rbRect::ourDefinition;

void rbRect::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbRectClass::defineClassUnder<rb::RubyObjAllocator>("Rect", sfml);
	ourDefinition.defineMethod<0>("initialize", &rbRect::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbRect::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbRect::marshalDump);
	ourDefinition.defineMethod<3>("marshal_load", &rbRect::marshalLoad);
	ourDefinition.defineMethod<4>("==", &rbRect::equal);
	ourDefinition.defineMethod<5>("eql?", &rbRect::strictEqual);
	ourDefinition.defineMethod<6>("inspect", &rbRect::inspect);

	ourDefinition.defineAttribute("left", true, true);
	ourDefinition.defineAttribute("top", true, true);
	ourDefinition.defineAttribute("width", true, true);
	ourDefinition.defineAttribute("height", true, true);

	ourDefinition.aliasMethod("eql?", "equal?");
	ourDefinition.aliasMethod("inspect", "to_s");
}

const rbRectClass& rbRect::getDefinition()
{
	return ourDefinition;
}

rb::Value rbRect::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
	switch( args.size() )
    {
        case 0:
        	self.setVar<symVarLeft>(0);
        	self.setVar<symVarTop>(0);
        	self.setVar<symVarWidth>(0);
        	self.setVar<symVarHeight>(0);
            break;
        case 1:
        	if(args[0].getType() == rb::ValueType::Array)
        	{
        		const std::vector<rb::Value>& elements = args[0].to<const std::vector<rb::Value>&>();
        		self.setVar<symVarLeft>(elements[0]);
	        	self.setVar<symVarTop>(elements[1]);
	        	self.setVar<symVarWidth>(elements[2]);
	        	self.setVar<symVarHeight>(elements[3]);
        	}
        	else
        	{
        		rbRect::initializeCopy(self, args[0]);
        	}
            break;
        case 4:
        	self.setVar<symVarLeft>(args[0]);
        	self.setVar<symVarTop>(args[1]);
        	self.setVar<symVarWidth>(args[2]);
        	self.setVar<symVarHeight>(args[3]);
            break;
        default:
        	rb::expectedNumArgs( args.size(), "0, 1 or 4" );
        	break;
    }

	return self;
}

rb::Value rbRect::initializeCopy(rb::Value self, const rb::Value& value)
{
	self.setVar<symVarLeft>(value.getVar<symVarLeft, rb::Value>());
    self.setVar<symVarTop>(value.getVar<symVarTop, rb::Value>());
    self.setVar<symVarWidth>(value.getVar<symVarWidth, rb::Value>());
    self.setVar<symVarHeight>(value.getVar<symVarHeight, rb::Value>());
	return self;
}

std::vector<rb::Value> rbRect::marshalDump(const rb::Value& self)
{
	std::vector<rb::Value> array;
	array.push_back(self.getVar<symVarLeft, rb::Value>());
    array.push_back(self.getVar<symVarTop, rb::Value>());
    array.push_back(self.getVar<symVarWidth, rb::Value>());
    array.push_back(self.getVar<symVarHeight, rb::Value>());
    return array;
}

rb::Value rbRect::marshalLoad(rb::Value self, const rb::Value& data)
{
	std::vector<rb::Value> array = data.to<std::vector<rb::Value>>();
	self.setVar<symVarLeft>(array[0]);
    self.setVar<symVarTop>(array[1]);
    self.setVar<symVarWidth>(array[2]);
    self.setVar<symVarHeight>(array[3]);
	return rb::Nil;
}

bool rbRect::equal(const rb::Value& self, const rb::Value& other)
{
	if(	!other.isKindOf(rb::Value(ourDefinition)) && 
		!(other.getType() == rb::ValueType::Array && other.getArrayLength() == 4))
		return false;

	rb::Value rect = ourDefinition.newObject(other);
	if(!self.getVar<symVarLeft>().equal(rect.getVar<symVarLeft>())) return false;
	if(!self.getVar<symVarTop>().equal(rect.getVar<symVarTop>())) return false;
	if(!self.getVar<symVarWidth>().equal(rect.getVar<symVarWidth>())) return false;
	if(!self.getVar<symVarHeight>().equal(rect.getVar<symVarHeight>())) return false;
	return true;
}

bool rbRect::strictEqual(const rb::Value& self, const rb::Value& other)
{
	if(!other.isKindOf(rb::Value(ourDefinition))) return false;
	if(self.getVar<symVarLeft>().getType() != other.getVar<symVarLeft>().getType()) return false;
	if(self.getVar<symVarTop>().getType() != other.getVar<symVarTop>().getType()) return false;
	if(self.getVar<symVarWidth>().getType() != other.getVar<symVarWidth>().getType()) return false;
	if(self.getVar<symVarHeight>().getType() != other.getVar<symVarHeight>().getType()) return false;
	return equal(self, other);
}

std::string rbRect::inspect(const rb::Value& self)
{
	std::string leftStr = self.getVar<symVarLeft>().call<symInspect, std::string>();
	std::string topStr = self.getVar<symVarTop>().call<symInspect, std::string>();
	std::string widthStr = self.getVar<symVarWidth>().call<symInspect, std::string>();
	std::string heightStr = self.getVar<symVarHeight>().call<symInspect, std::string>();
	return ourDefinition.getName() + "(" + leftStr + ", " + topStr + ", " + widthStr + ", " + heightStr + ")";
}

namespace rb
{

template<>
sf::FloatRect Value::to() const
{
	errorHandling(T_OBJECT);
	sf::FloatRect rect(
		getVar<symVarLeft, float>(), getVar<symVarTop, float>(),
		getVar<symVarWidth, float>(), getVar<symVarHeight, float>()
	);
	return rect;
}

template<>
sf::IntRect Value::to() const
{
	errorHandling(T_OBJECT);
	sf::IntRect rect(
		getVar<symVarLeft, int>(), getVar<symVarTop, int>(),
		getVar<symVarWidth, int>(), getVar<symVarHeight, int>()
	);
	return rect;
}


template<>
Value Value::create<sf::FloatRect>( sf::FloatRect value )
{
	rb::Value object = rbRect::getDefinition().newObject(value.left, value.top, value.width, value.height);
	return object;
}

template<>
Value Value::create<const sf::FloatRect&>( const sf::FloatRect& value )
{
	rb::Value object = rbRect::getDefinition().newObject(value.left, value.top, value.width, value.height);
	return object;
}

template<>
Value Value::create<sf::IntRect>( sf::IntRect value )
{
	rb::Value object = rbRect::getDefinition().newObject(value.left, value.top, value.width, value.height);
	return object;
}

template<>
Value Value::create<const sf::IntRect&>( const sf::IntRect& value )
{
	rb::Value object = rbRect::getDefinition().newObject(value.left, value.top, value.width, value.height);
	return object;
}

}