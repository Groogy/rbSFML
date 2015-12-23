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

#ifndef RBSFML_RBDRAWABLEBASETYPE_HPP_
#define RBSFML_RBDRAWABLEBASETYPE_HPP_

#include "class.hpp"
#include "object.hpp"

namespace sf
{
    class Drawable;
    class Transformable;
}

class rbDrawableBaseType : public rb::Object
{
public:
    virtual ~rbDrawableBaseType();

protected:
    friend class rb::Value;

    rbDrawableBaseType();

    virtual sf::Drawable* getDrawable();
    virtual const sf::Drawable* getDrawable() const;

    virtual sf::Transformable* getTransformable();
    virtual const sf::Transformable* getTransformable() const;
};

namespace rb
{
    template<>
    rbDrawableBaseType* Value::to() const;
    template<>
    const rbDrawableBaseType* Value::to() const;

	template<>
    sf::Drawable& Value::to() const;
    template<>
    const sf::Drawable& Value::to() const;

    template<>
    sf::Transformable& Value::to() const;
    template<>
    const sf::Transformable& Value::to() const;
}

#endif // RBSFML_RBDRAWABLEBASETYPE_HPP_
