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

#ifndef RBSFML_RBRENDERBASETYPE_HPP_
#define RBSFML_RBRENDERBASETYPE_HPP_

#include "class.hpp"
#include "object.hpp"

namespace sf
{
    class RenderTarget;
    class Window;
    class RenderWindow;
}

class rbRenderBaseType : public rb::Object
{
public:
    virtual ~rbRenderBaseType();

protected:
    friend class rb::Value;

    rbRenderBaseType();

    virtual sf::RenderTarget* getRenderTarget();
    virtual const sf::RenderTarget* getRenderTarget() const;

    virtual sf::Window* getWindow();
    virtual const sf::Window* getWindow() const;

    virtual sf::RenderWindow* getRenderWindow();
    virtual const sf::RenderWindow* getRenderWindow() const;
};

namespace rb
{
    template<>
    rbRenderBaseType* Value::to() const;
    template<>
    const rbRenderBaseType* Value::to() const;

	template<>
    sf::RenderTarget& Value::to() const;
    template<>
    const sf::RenderTarget& Value::to() const;

    template<>
    sf::Window& Value::to() const;
    template<>
    const sf::Window& Value::to() const;

    template<>
    sf::RenderWindow& Value::to() const;
    template<>
    const sf::RenderWindow& Value::to() const;
}

#endif // RBSFML_RBRENDERTARGET_HPP_
