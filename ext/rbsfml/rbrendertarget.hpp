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

#ifndef RBSFML_RBRENDERTARGET_HPP_
#define RBSFML_RBRENDERTARGET_HPP_

#include <SFML/Graphics/RenderTarget.hpp>
#include "class.hpp"
#include "object.hpp"

class rbView;
class rbRenderTarget;

typedef rb::Module<rbRenderTarget> rbRenderTargetModule;

class rbRenderTarget : public rb::Object
{
public:
	static void defineModule(const rb::Value& sfml);
	static rbRenderTargetModule& getDefinition();

	rbRenderTarget();
	virtual ~rbRenderTarget();

	static rb::Value clear(rb::Value self, const std::vector<rb::Value>& args);

	void setView(const rbView* view);
	rbView* getView() const;
	rbView* getDefaultView() const;

	sf::IntRect getViewport(const rbView* view);

	static rb::Value mapPixelToCoords(rb::Value self, const std::vector<rb::Value>& args);
	static rb::Value mapCoordsToPixel(rb::Value self, const std::vector<rb::Value>& args);

	sf::Vector2u getSize() const;

	void pushGLStates();
	void popGLStates();
	void resetGLStates();

	static rb::Value draw(rb::Value self, const std::vector<rb::Value>& args);

protected:
    virtual sf::RenderTarget& getRenderTarget() = 0;
    virtual const sf::RenderTarget& getRenderTarget() const = 0;

private:
    friend class rb::Value;
	static rbRenderTargetModule ourDefinition;
};

namespace rb
{
	template<>
	rbRenderTarget* Value::to() const;
	template<>
	const rbRenderTarget* Value::to() const;
	template<>
    sf::RenderTarget& Value::to() const;
    template<>
    const sf::RenderTarget& Value::to() const;
}

#endif // RBSFML_RBRENDERTARGET_HPP_
