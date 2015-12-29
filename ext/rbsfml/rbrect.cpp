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
#include "rbvector2.hpp"
#include "error.hpp"
#include "macros.hpp"
#include "base.hpp"

namespace 
{
	constexpr char symVarLeft[] = "@left";
	constexpr char symVarTop[] = "@top";
	constexpr char symVarWidth[] = "@width";
	constexpr char symVarHeight[] = "@height";

	constexpr char symVarX[] = "@x";
	constexpr char symVarY[] = "@y";

	constexpr char symInspect[] = "inspect";
	constexpr char symMoreEqual[] = ">=";
	constexpr char symLessEqual[] = "<=";
	constexpr char symMore[] = ">";
	constexpr char symLess[] = "<";
	constexpr char symAdd[] = "+";
	constexpr char symSubtract[] = "-";
}

rbRectClass rbRect::ourDefinition;

void rbRect::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbRectClass::defineClassUnder<rb::RubyObjAllocator>("Rect", sfml);
	ourDefinition.defineMethod<0>("initialize", &rbRect::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbRect::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbRect::marshalDump);
	ourDefinition.defineMethod<3>("marshal_load", &rbRect::marshalLoad);
	ourDefinition.defineMethod<4>("contains?", &rbRect::contains);
	ourDefinition.defineMethod<5>("intersects?", &rbRect::intersects);
	ourDefinition.defineMethod<6>("==", &rbRect::equal);
	ourDefinition.defineMethod<7>("eql?", &rbRect::strictEqual);
	ourDefinition.defineMethod<8>("inspect", &rbRect::inspect);

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

rb::Value rbRect::contains(rb::Value self, const std::vector<rb::Value>& args)
{
	rb::Value vector = rbVector2::getDefinition().newObject(args);
	bool result = false;
	rb::Value x = vector.getVar<symVarX>();
	rb::Value y = vector.getVar<symVarY>();
	rb::Value left = self.getVar<symVarLeft>();
	rb::Value top = self.getVar<symVarTop>();
	rb::Value width = self.getVar<symVarWidth>();
	rb::Value height = self.getVar<symVarHeight>();

	if( x.call<symMoreEqual>(left) == rb::True && 
		x.call<symLess>(left.call<symAdd>(width)) == rb::True && 
		y.call<symMoreEqual>(top) == rb::True && 
		y.call<symLess>(top.call<symAdd>(height)) == rb::True)
	{
		return rb::True;
	}
	else
	{
		return rb::False;
	}
}

rb::Value rbRect::intersects(const rb::Value& self, const rb::Value& other)
{
	rb::Value otherRect = rbRect::getDefinition().newObject(other);
	bool result = false;

	rb::Value myLeft = self.getVar<symVarLeft>();
	rb::Value myTop = self.getVar<symVarTop>();
	rb::Value myWidth = self.getVar<symVarWidth>();
	rb::Value myHeight = self.getVar<symVarHeight>();
	rb::Value otherLeft = otherRect.getVar<symVarLeft>();
	rb::Value otherTop = otherRect.getVar<symVarTop>();
	rb::Value otherWidth = otherRect.getVar<symVarWidth>();
	rb::Value otherHeight = otherRect.getVar<symVarHeight>();

	rb::Value left = rb::max(myLeft, otherLeft);
	rb::Value top = rb::max(myTop, otherTop);
	rb::Value right = rb::min(myLeft.call<symAdd>(myWidth), otherLeft.call<symAdd>(otherWidth));
	rb::Value bottom = rb::min(myTop.call<symAdd>(myHeight), otherTop.call<symAdd>(otherHeight));

	if(left.call<symLess>(right) == rb::True && top.call<symLess>(bottom) == rb::True)
	{
		rb::Value intersection = ourDefinition.newObject();
		intersection.setVar<symVarLeft>(left);
		intersection.setVar<symVarTop>(top);
		intersection.setVar<symVarWidth>(right.call<symSubtract>(left));
		intersection.setVar<symVarHeight>(bottom.call<symSubtract>(top));
		return intersection;
	}
	else
	{
		return rb::Nil;
	}
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
    if(getType() == rb::ValueType::Array && getArrayLength() == 4)
    {
        std::vector<rb::Value> elements = to<std::vector<rb::Value>>();
        sf::FloatRect rect(
            elements[0].to<float>(), elements[1].to<float>(),
            elements[2].to<float>(), elements[3].to<float>()
        );
        return rect;
    }
    else
    {
        errorHandling(T_OBJECT);
        sf::FloatRect rect(
            getVar<symVarLeft, float>(), getVar<symVarTop, float>(),
            getVar<symVarWidth, float>(), getVar<symVarHeight, float>()
        );
        return rect;
    }
}

template<>
sf::IntRect Value::to() const
{
    if(getType() == rb::ValueType::Array && getArrayLength() == 4)
    {
        std::vector<rb::Value> elements = to<std::vector<rb::Value>>();
        sf::IntRect rect(
            elements[0].to<int>(), elements[1].to<int>(),
            elements[2].to<int>(), elements[3].to<int>()
        );
        return rect;
    }
    else
    {
        errorHandling(T_OBJECT);
        sf::IntRect rect(
            getVar<symVarLeft, int>(), getVar<symVarTop, int>(),
            getVar<symVarWidth, int>(), getVar<symVarHeight, int>()
        );
        return rect;
    }
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