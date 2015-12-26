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
#include "rbrenderbasetype.hpp"

class rbView;
class rbRenderTarget;
class rbRenderTargetRef;

typedef rb::Module<rbRenderTarget> rbRenderTargetModule;
typedef rb::Class<rbRenderTargetRef> rbRenderTargetRefClass;

class rbRenderTarget : public virtual rbRenderBaseType
{
public:
	static void defineModule(const rb::Value& sfml);
	static rbRenderTargetModule& getDefinition();
	static rbRenderTargetRefClass& getRefDefinition();

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

private:
    friend class rb::Value;
	static rbRenderTargetModule ourDefinition;
	static rbRenderTargetRefClass ourRefDefinition;
};

class rbRenderTargetRef : public rbRenderTarget
{
public:
    rbRenderTargetRef();

    void setRef(sf::RenderTarget* object);

protected:
    virtual sf::RenderTarget* getRenderTarget();
    virtual const sf::RenderTarget* getRenderTarget() const;

private:
    sf::RenderTarget* myObject;
};

namespace rb
{
	template<>
	rbRenderTarget* Value::to() const;
	template<>
	const rbRenderTarget* Value::to() const;

	template<>
    rbRenderTargetRef* Value::to() const;
    template<>
    const rbRenderTargetRef* Value::to() const;
}

#endif // RBSFML_RBRENDERTARGET_HPP_
