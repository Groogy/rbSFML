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

#include "rbblendmode.hpp"
#include "error.hpp"
#include "macros.hpp"

rbBlendModeModule rbBlendMode::ourDefinition;

void rbBlendMode::defineModule(const rb::Value& sfml)
{
	ourDefinition = rbBlendModeModule::defineModuleUnder("BlendMode", sfml);

	ourDefinition.defineConstant("Zero", rb::Value(sf::BlendMode::Zero));
	ourDefinition.defineConstant("One", rb::Value(sf::BlendMode::One));
	ourDefinition.defineConstant("SrcColor", rb::Value(sf::BlendMode::SrcColor));
	ourDefinition.defineConstant("OneMinusSrcColor", rb::Value(sf::BlendMode::OneMinusSrcColor));
	ourDefinition.defineConstant("DstColor", rb::Value(sf::BlendMode::DstColor));
	ourDefinition.defineConstant("OneMinusDstColor", rb::Value(sf::BlendMode::OneMinusDstColor));
	ourDefinition.defineConstant("SrcAlpha", rb::Value(sf::BlendMode::SrcAlpha));
	ourDefinition.defineConstant("OneMinusSrcAlpha", rb::Value(sf::BlendMode::OneMinusSrcAlpha));
	ourDefinition.defineConstant("DstAlpha", rb::Value(sf::BlendMode::DstAlpha));
	ourDefinition.defineConstant("OneMinusDstAlpha", rb::Value(sf::BlendMode::OneMinusDstAlpha));
	ourDefinition.defineConstant("Add", rb::Value(sf::BlendMode::Add));
	ourDefinition.defineConstant("Subtract", rb::Value(sf::BlendMode::Subtract));
}

namespace rb
{

template<>
sf::BlendMode::Factor Value::to() const
{
	unsigned int value = to<unsigned int>();
	return static_cast<sf::BlendMode::Factor>(value);
}

template<>
Value Value::create( sf::BlendMode::Factor value )
{
	return create(static_cast<unsigned int>(value));
}

template<>
sf::BlendMode::Equation Value::to() const
{
	unsigned int value = to<unsigned int>();
	return static_cast<sf::BlendMode::Equation>(value);
}

template<>
Value Value::create( sf::BlendMode::Equation value )
{
	return create(static_cast<unsigned int>(value));
}

}