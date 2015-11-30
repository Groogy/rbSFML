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

#include "rbtouch.hpp"
#include "rbvector2.hpp"
#include "error.hpp"
#include "macros.hpp"

rbTouchModule rbTouch::ourDefinition;

void rbTouch::defineModule(const rb::Value& sfml)
{
	ourDefinition = rbTouchModule::defineModuleUnder("Touch", sfml);
	ourDefinition.defineFunction<0>("is_down?", &sf::Touch::isDown);
	ourDefinition.defineFunction<1>("get_position", &rbTouch::getPosition);
}

rb::Value rbTouch::getPosition(const std::vector<rb::Value>& arguments)
{
	sf::Vector2i result;
	switch(arguments.size())
	{
	case 1:
		result = sf::Touch::getPosition(arguments[0].to<unsigned int>());
		break;
	case 2:
		result = sf::Touch::getPosition(arguments[0].to<unsigned int>(), arguments[1].to<const sf::Window&>());
		break;
	default:
		rb::expectedNumArgs(arguments.size(), 1, 2);
	}
	return rb::Value::create(result);
}
