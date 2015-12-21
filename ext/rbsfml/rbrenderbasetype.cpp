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

#include "rbrenderbasetype.hpp"
#include "error.hpp"
#include "macros.hpp"
#include "base.hpp"

rbRenderBaseType::~rbRenderBaseType()
{
}

rbRenderBaseType::rbRenderBaseType()
{
}

sf::RenderTarget* rbRenderBaseType::getRenderTarget() { return nullptr; }
const sf::RenderTarget* rbRenderBaseType::getRenderTarget() const { return nullptr; }

sf::Window* rbRenderBaseType::getWindow() { return nullptr; }
const sf::Window* rbRenderBaseType::getWindow() const { return nullptr; }

sf::RenderWindow* rbRenderBaseType::getRenderWindow() { return nullptr; }
const sf::RenderWindow* rbRenderBaseType::getRenderWindow() const { return nullptr; }

namespace rb
{

template<>
rbRenderBaseType* Value::to() const
{
	errorHandling(T_DATA);
	rbRenderBaseType* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbRenderBaseType, object);
	return object;
}

template<>
const rbRenderBaseType* Value::to() const
{
	errorHandling(T_DATA);
	const rbRenderBaseType* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbRenderBaseType, object);
	return object;
}

template<>
sf::RenderTarget& Value::to() const
{
    return *to<rbRenderBaseType*>()->getRenderTarget();
}

template<>
const sf::RenderTarget& Value::to() const
{
    return *to<const rbRenderBaseType*>()->getRenderTarget();
}

template<>
sf::Window& Value::to() const
{
    return *to<rbRenderBaseType*>()->getWindow();
}

template<>
const sf::Window& Value::to() const
{
    return *to<const rbRenderBaseType*>()->getWindow();
}

template<>
sf::RenderWindow& Value::to() const
{
    return *to<rbRenderBaseType*>()->getRenderWindow();
}

template<>
const sf::RenderWindow& Value::to() const
{
    return *to<const rbRenderBaseType*>()->getRenderWindow();
}

}