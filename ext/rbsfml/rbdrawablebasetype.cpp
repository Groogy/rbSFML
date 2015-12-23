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

#include "rbdrawablebasetype.hpp"
#include "error.hpp"
#include "macros.hpp"
#include "base.hpp"

rbDrawableBaseType::~rbDrawableBaseType()
{
}

rbDrawableBaseType::rbDrawableBaseType()
{
}

sf::Drawable* rbDrawableBaseType::getDrawable() { return nullptr; }
const sf::Drawable* rbDrawableBaseType::getDrawable() const { return nullptr; }

sf::Transformable* rbDrawableBaseType::getTransformable() { return nullptr; }
const sf::Transformable* rbDrawableBaseType::getTransformable() const { return nullptr; }

namespace rb
{

template<>
rbDrawableBaseType* Value::to() const
{
	errorHandling(T_DATA);
	rbDrawableBaseType* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbDrawableBaseType, object);
	return object;
}

template<>
const rbDrawableBaseType* Value::to() const
{
	errorHandling(T_DATA);
	const rbDrawableBaseType* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbDrawableBaseType, object);
	return object;
}

template<>
sf::Drawable& Value::to() const
{
    return *to<rbDrawableBaseType*>()->getDrawable();
}

template<>
const sf::Drawable& Value::to() const
{
    return *to<const rbDrawableBaseType*>()->getDrawable();
}

template<>
sf::Transformable& Value::to() const
{
    return *to<rbDrawableBaseType*>()->getTransformable();
}

template<>
const sf::Transformable& Value::to() const
{
    return *to<const rbDrawableBaseType*>()->getTransformable();
}

}