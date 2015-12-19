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

#include "rbrendertarget.hpp"
#include "rbnoncopyable.hpp"
#include "rbview.hpp"
#include "rbvector2.hpp"
#include "rbrect.hpp"
#include "error.hpp"
#include "macros.hpp"

rbRenderTargetModule rbRenderTarget::ourDefinition;

void rbRenderTarget::defineModule(const rb::Value& sfml)
{
	ourDefinition = rbRenderTargetModule::defineModuleUnder("RenderTarget", sfml);
	ourDefinition.includeModule(rb::Value(rbNonCopyable::getDefinition()));
	ourDefinition.defineMethod<0>("clear", &rbRenderTarget::clear);
	ourDefinition.defineMethod<1>("view=", &rbRenderTarget::setView);
	ourDefinition.defineMethod<2>("view", &rbRenderTarget::getView);
	ourDefinition.defineMethod<3>("default_view", &rbRenderTarget::getDefaultView);
	ourDefinition.defineMethod<4>("get_viewport", &rbRenderTarget::getViewport);
	ourDefinition.defineMethod<5>("map_pixel_to_coords", &rbRenderTarget::mapPixelToCoords);
	ourDefinition.defineMethod<6>("map_coords_to_pixel", &rbRenderTarget::mapCoordsToPixel);
	ourDefinition.defineMethod<7>("push_gl_states", &rbRenderTarget::pushGLStates);
	ourDefinition.defineMethod<8>("pop_gl_states", &rbRenderTarget::popGLStates);
	ourDefinition.defineMethod<9>("reset_gl_states", &rbRenderTarget::resetGLStates);
}

rbRenderTargetModule& rbRenderTarget::getDefinition()
{
    return ourDefinition;
}

rbRenderTarget::rbRenderTarget()
: rb::Object()
{
}

rbRenderTarget::~rbRenderTarget()
{
}

rb::Value rbRenderTarget::clear(rb::Value self, const std::vector<rb::Value>& args)
{
    sf::Color color = sf::Color::Black;
    switch(args.size())
    {
        case 1:
            color = args[0].to<sf::Color>();
        case 0:
            break;
        default:
            rb::expectedNumArgs( args.size(), 0, 1 );
    }
    self.to<sf::RenderTarget&>().clear(color);
    return rb::Nil;
}

void rbRenderTarget::setView(const rbView* view)
{
    const sf::View& val = rb::Value::create(view).to<const sf::View&>();
    getRenderTarget().setView(val);
}

rbView* rbRenderTarget::getView() const
{
    rb::Value object = rbView::getDefinition().newObject();
    object.to<sf::View&>() = getRenderTarget().getView();
    return object.to<rbView*>();
}

rbView* rbRenderTarget::getDefaultView() const
{
    rb::Value object = rbView::getDefinition().newObject();
    object.to<sf::View&>() = getRenderTarget().getDefaultView();
    return object.to<rbView*>();
}

sf::IntRect rbRenderTarget::getViewport(const rbView* view)
{
    return getRenderTarget().getViewport(view->myObject);
}

rb::Value rbRenderTarget::mapPixelToCoords(rb::Value self, const std::vector<rb::Value>& args)
{
    const sf::RenderTarget& target = self.to<const sf::RenderTarget&>();
    sf::Vector2f result;
    switch(args.size())
    {
        case 1:
            result = target.mapPixelToCoords(args[0].to<sf::Vector2i>());
            break;
        case 2:
            result = target.mapPixelToCoords(args[0].to<sf::Vector2i>(), args[1].to<const sf::View&>());
            break;
    }
    return rb::Value::create(result);
}

rb::Value rbRenderTarget::mapCoordsToPixel(rb::Value self, const std::vector<rb::Value>& args)
{
    const sf::RenderTarget& target = self.to<const sf::RenderTarget&>();
    sf::Vector2i result;
    switch(args.size())
    {
        case 1:
            result = target.mapCoordsToPixel(args[0].to<sf::Vector2f>());
            break;
        case 2:
            result = target.mapCoordsToPixel(args[0].to<sf::Vector2f>(), args[1].to<const sf::View&>());
            break;
    }
    return rb::Value::create(result);
}

sf::Vector2u rbRenderTarget::getSize() const
{
    return getRenderTarget().getSize();
}

void rbRenderTarget::pushGLStates()
{
    return getRenderTarget().pushGLStates();
}

void rbRenderTarget::popGLStates()
{
    return getRenderTarget().popGLStates();
}

void rbRenderTarget::resetGLStates()
{
    return getRenderTarget().resetGLStates();
}

namespace rb
{

template<>
rbRenderTarget* Value::to() const
{
	errorHandling(T_DATA);
	rbRenderTarget* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbRenderTarget, object);
	return object;
}

template<>
const rbRenderTarget* Value::to() const
{
	errorHandling(T_DATA);
	const rbRenderTarget* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbRenderTarget, object);
	return object;
}

template<>
sf::RenderTarget& Value::to() const
{
    return to<rbRenderTarget*>()->getRenderTarget();
}

template<>
const sf::RenderTarget& Value::to() const
{
    return to<const rbRenderTarget*>()->getRenderTarget();
}

}