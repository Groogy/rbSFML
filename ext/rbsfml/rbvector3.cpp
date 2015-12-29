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

#include "rbvector3.hpp"
#include "error.hpp"
#include "macros.hpp"

namespace 
{
	constexpr char symVarX[] = "@x";
	constexpr char symVarY[] = "@y";
	constexpr char symVarZ[] = "@z";
	constexpr char symNegate[] = "-@";

	constexpr char symInspect[] = "inspect";

	constexpr char symAdd[] = "+";
	constexpr char symSubtract[] = "-";
	constexpr char symMultiply[] = "*";
	constexpr char symDivide[] = "/";

	template<const char* operation, const char* varX = symVarX, const char* varY = symVarY, const char* varZ = symVarZ>
	void doMath(rb::Value result, const rb::Value& left, const rb::Value& right)
	{
		rb::Value leftX = left.getVar<varX>();
		rb::Value leftY = left.getVar<varY>();
		rb::Value leftZ = left.getVar<varZ>();
		rb::Value rightX, rightY, rightZ;
		if(right.getType() == rb::ValueType::Float || right.getType() == rb::ValueType::Fixnum)
        {
            rightX = right;
            rightY = right;
            rightZ = right;
        }
        else
        {
            rightX = right.getVar<varX>();
            rightY = right.getVar<varY>();
            rightZ = right.getVar<varZ>();
        }

		rb::Value x = leftX.call<operation>(rightX);
		rb::Value y = leftY.call<operation>(rightY);
		rb::Value z = leftZ.call<operation>(rightZ);

		result.setVar<varX>(x);
		result.setVar<varY>(y);
		result.setVar<varZ>(z);
	}
}

rbVector3Class rbVector3::ourDefinition;

void rbVector3::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbVector3Class::defineClassUnder<rb::RubyObjAllocator>("Vector3", sfml);
	ourDefinition.defineMethod<0>("initialize", &rbVector3::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbVector3::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbVector3::marshalDump);
	ourDefinition.defineMethod<3>("marshal_load", &rbVector3::marshalLoad);
	ourDefinition.defineMethod<4>("-@", &rbVector3::negate);
	ourDefinition.defineMethod<5>("+", &rbVector3::add);
	ourDefinition.defineMethod<6>("-", &rbVector3::subtract);
	ourDefinition.defineMethod<7>("*", &rbVector3::multiply);
	ourDefinition.defineMethod<8>("/", &rbVector3::divide);
	ourDefinition.defineMethod<9>("==", &rbVector3::equal);
	ourDefinition.defineMethod<10>("eql?", &rbVector3::strictEqual);
	ourDefinition.defineMethod<11>("inspect", &rbVector3::inspect);

	ourDefinition.defineAttribute("x", true, true);
	ourDefinition.defineAttribute("y", true, true);
	ourDefinition.defineAttribute("z", true, true);

	ourDefinition.aliasMethod("eql?", "equal?");
	ourDefinition.aliasMethod("inspect", "to_s");

	ourDefinition.defineConstant("Zero", ourDefinition.newObject());
}

const rbVector3Class& rbVector3::getDefinition()
{
	return ourDefinition;
}

rb::Value rbVector3::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
	switch( args.size() )
    {
        case 0:
        	self.setVar<symVarX>(0);
        	self.setVar<symVarY>(0);
        	self.setVar<symVarZ>(0);
            break;
        case 1:
        	if(args[0].getType() == rb::ValueType::Array)
        	{
        		const std::vector<rb::Value>& elements = args[0].to<const std::vector<rb::Value>&>();
        		self.setVar<symVarX>(elements[0]);
	        	self.setVar<symVarY>(elements[1]);
	        	self.setVar<symVarZ>(elements[2]);
        	}
        	else
        	{
        		rbVector3::initializeCopy(self, args[0]);
        	}
            break;
        case 3:
        	self.setVar<symVarX>(args[0]);
        	self.setVar<symVarY>(args[1]);
        	self.setVar<symVarZ>(args[2]);
            break;
        default:
        	rb::expectedNumArgs( args.size(), "0, 1, or 3" );
        	break;
    }

	return self;
}

rb::Value rbVector3::initializeCopy(rb::Value self, const rb::Value& value)
{
	self.setVar<symVarX>(value.getVar<symVarX, rb::Value>());
    self.setVar<symVarY>(value.getVar<symVarY, rb::Value>());
    self.setVar<symVarZ>(value.getVar<symVarZ, rb::Value>());
	return self;
}

std::vector<rb::Value> rbVector3::marshalDump(const rb::Value& self)
{
	std::vector<rb::Value> array;
	array.push_back(self.getVar<symVarX, rb::Value>());
    array.push_back(self.getVar<symVarY, rb::Value>());
    array.push_back(self.getVar<symVarZ, rb::Value>());
    return array;
}

rb::Value rbVector3::marshalLoad(rb::Value self, const rb::Value& data)
{
	std::vector<rb::Value> array = data.to<std::vector<rb::Value>>();
	self.setVar<symVarX>(array[0]);
    self.setVar<symVarY>(array[1]);
    self.setVar<symVarZ>(array[2]);
	return rb::Nil;
}

rb::Value rbVector3::negate(const rb::Value& self)
{
	rb::Value object = ourDefinition.newObject();
	object.setVar<symVarX>(object.getVar<symVarX>().call<symNegate>());
	object.setVar<symVarY>(object.getVar<symVarY>().call<symNegate>());
	object.setVar<symVarZ>(object.getVar<symVarZ>().call<symNegate>());
	return object;
}

rb::Value rbVector3::add(const rb::Value& self, const rb::Value& other)
{
	rb::Value result = ourDefinition.newObject();
	doMath<symAdd>(result, self, other);
	return result;
}

rb::Value rbVector3::subtract(const rb::Value& self, const rb::Value& other)
{
	rb::Value result = ourDefinition.newObject();
	doMath<symSubtract>(result, self, other);
	return result;
}

rb::Value rbVector3::multiply(const rb::Value& self, const rb::Value& other)
{
	rb::Value result = ourDefinition.newObject();
	doMath<symMultiply>(result, self, other);
	return result;
}

rb::Value rbVector3::divide(const rb::Value& self, const rb::Value& other)
{
	rb::Value result = ourDefinition.newObject();
	doMath<symDivide>(result, self, other);
	return result;
}

bool rbVector3::equal(const rb::Value& self, const rb::Value& other)
{
	if(	!other.isKindOf(rb::Value(ourDefinition)) && 
		!(other.getType() == rb::ValueType::Array && other.getArrayLength() == 3))
		return false;

	rb::Value vector = ourDefinition.newObject(other);
	if(!self.getVar<symVarX>().equal(vector.getVar<symVarX>())) return false;
	if(!self.getVar<symVarY>().equal(vector.getVar<symVarY>())) return false;
	if(!self.getVar<symVarZ>().equal(vector.getVar<symVarZ>())) return false;
	return true;
}

bool rbVector3::strictEqual(const rb::Value& self, const rb::Value& other)
{
	if(!other.isKindOf(rb::Value(ourDefinition))) return false;
	if(self.getVar<symVarX>().getType() != other.getVar<symVarX>().getType()) return false;
	if(self.getVar<symVarY>().getType() != other.getVar<symVarY>().getType()) return false;
	if(self.getVar<symVarZ>().getType() != other.getVar<symVarZ>().getType()) return false;
	return equal(self, other);
}

std::string rbVector3::inspect(const rb::Value& self)
{
	std::string xStr = self.getVar<symVarX>().call<symInspect, std::string>();
	std::string yStr = self.getVar<symVarY>().call<symInspect, std::string>();
	std::string zStr = self.getVar<symVarZ>().call<symInspect, std::string>();
	return ourDefinition.getName() + "(" + xStr + ", " + yStr + ", " + zStr + ")";
}

namespace rb
{

template<>
sf::Vector3f Value::to() const
{
	if(getType() == rb::ValueType::Array && getArrayLength() == 3)
    {
        std::vector<rb::Value> elements = to<std::vector<rb::Value>>();
        sf::Vector3f vector(elements[0].to<float>(), elements[1].to<float>(), elements[2].to<float>());
        return vector;
    }
    else
    {
        errorHandling(T_OBJECT);
        sf::Vector3f vector(getVar<symVarX, float>(), getVar<symVarY, float>(), getVar<symVarZ, float>());
        return vector;
    }
}

template<>
sf::Vector3i Value::to() const
{
	if(getType() == rb::ValueType::Array && getArrayLength() == 3)
    {
        std::vector<rb::Value> elements = to<std::vector<rb::Value>>();
        sf::Vector3i vector(elements[0].to<int>(), elements[1].to<int>(), elements[2].to<int>());
        return vector;
    }
    else
    {
        errorHandling(T_OBJECT);
        sf::Vector3i vector(getVar<symVarX, int>(), getVar<symVarY, int>(), getVar<symVarZ, int>());
        return vector;
    }
}

template<>
Value Value::create<sf::Vector3f>( sf::Vector3f value )
{
	rb::Value object = rbVector3::getDefinition().newObject(value.x, value.y, value.z);
	return object;
}

template<>
Value Value::create<const sf::Vector3f&>( const sf::Vector3f& value )
{
	rb::Value object = rbVector3::getDefinition().newObject(value.x, value.y, value.z);
	return object;
}

template<>
Value Value::create<sf::Vector3i>( sf::Vector3i value )
{
	rb::Value object = rbVector3::getDefinition().newObject(value.x, value.y, value.z);
	return object;
}

template<>
Value Value::create<const sf::Vector3i&>( const sf::Vector3i& value )
{
	rb::Value object = rbVector3::getDefinition().newObject(value.x, value.y, value.z);
	return object;
}

}
