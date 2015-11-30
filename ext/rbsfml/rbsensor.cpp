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

#include "rbsensor.hpp"
#include "rbvector3.hpp"
#include "error.hpp"
#include "macros.hpp"

rbSensorModule rbSensor::ourDefinition;

void rbSensor::defineModule(const rb::Value& sfml)
{
	ourDefinition = rbSensorModule::defineModuleUnder("Sensor", sfml);
	ourDefinition.defineFunction<0>("is_available?", &sf::Sensor::isAvailable);
	ourDefinition.defineFunction<1>("set_enabled", &sf::Sensor::setEnabled);
	ourDefinition.defineFunction<0>("get_value", &sf::Sensor::getValue);

	ourDefinition.defineConstant("Accelerometer", rb::Value(sf::Sensor::Accelerometer));
	ourDefinition.defineConstant("Gyroscope", rb::Value(sf::Sensor::Gyroscope));
	ourDefinition.defineConstant("Magnetometer", rb::Value(sf::Sensor::Magnetometer));
	ourDefinition.defineConstant("Gravity", rb::Value(sf::Sensor::Gravity));
	ourDefinition.defineConstant("UserAcceleration", rb::Value(sf::Sensor::UserAcceleration));
	ourDefinition.defineConstant("Orientation", rb::Value(sf::Sensor::Orientation));
	ourDefinition.defineConstant("Count", rb::Value(sf::Sensor::Count));
}

namespace rb
{

template<>
sf::Sensor::Type Value::to() const
{
	unsigned int value = to<unsigned int>();
	return static_cast<sf::Sensor::Type>(value);
}

template<>
Value Value::create(sf::Sensor::Type value)
{
	return create(static_cast<unsigned int>(value));
}

}