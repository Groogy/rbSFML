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

#include "rbdrawable.hpp"
#include "rbrendertarget.hpp"
#include "rbrenderstates.hpp"
#include "error.hpp"
#include "macros.hpp"

#include <SFML/Graphics/Drawable.hpp>

namespace
{
    constexpr char symVarInternalDrawStack[] = "@@__internal_draw_stack";

    constexpr char symDraw[] = "draw";
    constexpr char symLast[] = "last";
    constexpr char symDup[] = "dup";
}

class rbDrawableBridge;

class rbDrawableImpl : public sf::Drawable
{
public:
    rbDrawableImpl(rbDrawableBridge& owner);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    rbDrawableBridge& myOwner;
};

class rbDrawableBridge : public rbDrawable
{
public:
    rbDrawableBridge();
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    sf::Drawable* getDrawable();
    const sf::Drawable* getDrawable() const;

private:
    rbDrawableImpl myObject;
};

rbDrawableImpl::rbDrawableImpl(rbDrawableBridge& owner)
: myOwner(owner)
{
}

void rbDrawableImpl::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    myOwner.onDraw(target, states);
}

rbDrawableBridge::rbDrawableBridge()
: myObject(*this)
{
}

#include <iostream>

void rbDrawableBridge::onDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
    rb::Value drawStack = rb::Value(rbRenderTarget::getDefinition()).getVar<symVarInternalDrawStack>();
    rb::Value self(myValue);
    rb::Value targetRef = rbRenderTarget::getRefDefinition().newObject();
    targetRef.to<rbRenderTargetRef*>()->setRef(&target);
    self.call<symDraw>(targetRef, drawStack.call<symLast>().call<symDup>());
}

sf::Drawable* rbDrawableBridge::getDrawable()
{
    return &myObject;
}

const sf::Drawable* rbDrawableBridge::getDrawable() const
{
    return &myObject;
}

rbDrawableModule rbDrawable::ourDefinition;

void rbDrawable::defineModule(const rb::Value& sfml)
{
	ourDefinition = rbDrawableModule::defineModuleUnder("Drawable", sfml);
}

void rbDrawable::defineIncludeFunction()
{
    ourDefinition.defineFunction<0>("included", &rbDrawable::included);
}

rbDrawableModule& rbDrawable::getDefinition()
{
    return ourDefinition;
}

void rbDrawable::included(const rb::Value& base)
{
    if(base.getType() == rb::ValueType::Class)
    {
        rb::defineAllocator<rb::DefaultAllocator<rbDrawableBridge>>(base);
    }
}
