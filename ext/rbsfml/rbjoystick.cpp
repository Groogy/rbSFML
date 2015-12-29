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

#include "rbjoystick.hpp"
#include "error.hpp"
#include "macros.hpp"

namespace 
{
	constexpr char symVarName[] = "@name";
	constexpr char symVarVendorId[] = "@vendorId";
	constexpr char symVarProductId[] = "@productId";
}

rbJoystickModule rbJoystick::ourDefinition;
rbJoystickIdentificationClass rbJoystickIdentification::ourDefinition;

void rbJoystick::defineModule(const rb::Value& sfml)
{
	ourDefinition = rbJoystickModule::defineModuleUnder("Joystick", sfml);
	ourDefinition.defineFunction<0>("connected=", &sf::Joystick::isConnected);
	ourDefinition.defineFunction<1>("get_button_count", &sf::Joystick::getButtonCount);
	ourDefinition.defineFunction<2>("has_axis?", &sf::Joystick::hasAxis);
	ourDefinition.defineFunction<3>("button_pressed?", &sf::Joystick::isButtonPressed);
	ourDefinition.defineFunction<4>("get_axis_position", &sf::Joystick::getAxisPosition);
	ourDefinition.defineFunction<5>("update", &sf::Joystick::update);
	ourDefinition.defineFunction<6>("get_identification", &sf::Joystick::getIdentification);

	ourDefinition.defineConstant("Count", rb::Value(sf::Joystick::Count));
	ourDefinition.defineConstant("ButtonCount", rb::Value(sf::Joystick::ButtonCount));
	ourDefinition.defineConstant("AxisCount", rb::Value(sf::Joystick::AxisCount));
	ourDefinition.defineConstant("X", rb::Value(sf::Joystick::X));
	ourDefinition.defineConstant("Y", rb::Value(sf::Joystick::Y));
	ourDefinition.defineConstant("Z", rb::Value(sf::Joystick::Z));
	ourDefinition.defineConstant("R", rb::Value(sf::Joystick::R));
	ourDefinition.defineConstant("U", rb::Value(sf::Joystick::U));
	ourDefinition.defineConstant("V", rb::Value(sf::Joystick::V));
	ourDefinition.defineConstant("PovX", rb::Value(sf::Joystick::PovX));
	ourDefinition.defineConstant("PovY", rb::Value(sf::Joystick::PovY));

	rbJoystickIdentification::defineClass(sfml);
}

void rbJoystickIdentification::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbJoystickIdentificationClass::defineClassUnder<rb::RubyObjAllocator>("Identification", rb::Value(rbJoystick::ourDefinition));	
	ourDefinition.defineMethod<0>("initialize", &rbJoystickIdentification::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbJoystickIdentification::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbJoystickIdentification::marshalDump);
	ourDefinition.defineMethod<3>("marshal_load", &rbJoystickIdentification::marshalLoad);

	ourDefinition.defineAttribute("x", true, true);
	ourDefinition.defineAttribute("y", true, true);
}

const rbJoystickIdentificationClass& rbJoystickIdentification::getDefinition()
{
	return ourDefinition;
}

void rbJoystickIdentification::initialize(rb::Value self)
{
	self.setVar<symVarName>("");
	self.setVar<symVarVendorId>(0);
	self.setVar<symVarProductId>(0);
}

rb::Value rbJoystickIdentification::initializeCopy(rb::Value self, const rb::Value& value)
{
	self.setVar<symVarName>(value.getVar<symVarName, rb::Value>());
    self.setVar<symVarVendorId>(value.getVar<symVarVendorId, rb::Value>());
    self.setVar<symVarProductId>(value.getVar<symVarProductId, rb::Value>());
	return self;
}

std::vector<rb::Value> rbJoystickIdentification::marshalDump(const rb::Value& self)
{
	std::vector<rb::Value> array;
	array.push_back(self.getVar<symVarName, rb::Value>());
    array.push_back(self.getVar<symVarVendorId, rb::Value>());
    array.push_back(self.getVar<symVarProductId, rb::Value>());
    return array;
}

rb::Value rbJoystickIdentification::marshalLoad(rb::Value self, const rb::Value& data)
{
	std::vector<rb::Value> array = data.to<std::vector<rb::Value>>();
	self.setVar<symVarName>(array[0]);
    self.setVar<symVarVendorId>(array[1]);
    self.setVar<symVarProductId>(array[2]);
	return rb::Nil;
}


namespace rb
{
template<>
sf::Joystick::Axis Value::to() const
{
	unsigned int value = to<unsigned int>();
	return static_cast<sf::Joystick::Axis>(value);
}

template<>
Value Value::create( sf::Joystick::Axis value )
{
	return create(static_cast<unsigned int>(value));
}

template<>
sf::Joystick::Identification Value::to() const
{
	errorHandling(T_OBJECT);
	sf::Joystick::Identification identification;
	identification.name = getVar<symVarName, std::string>();
	identification.vendorId = getVar<symVarVendorId, unsigned int>();
	identification.productId = getVar<symVarProductId, unsigned int>();
	return identification;
}

template<>
Value Value::create( sf::Joystick::Identification value )
{
	rb::Value object = rbJoystickIdentification::getDefinition().newObject();
	object.setVar<symVarName>(value.name);
	object.setVar<symVarVendorId>(value.productId);
	object.setVar<symVarProductId>(value.vendorId);
	return object;
}

}