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

#ifndef RBSFML_RBRENDERTEXTURE_HPP_
#define RBSFML_RBRENDERTEXTURE_HPP_

#include <SFML/Graphics/RenderTexture.hpp>
#include "class.hpp"
#include "rbrendertarget.hpp"

class rbRenderTexture;
class rbTexture;

typedef rb::Class<rbRenderTexture> rbRenderTextureClass;

class rbRenderTexture : public rbRenderTarget
{
public:
	static void defineClass(const rb::Value& sfml);
	static rbRenderTextureClass& getDefinition();

	rbRenderTexture();
	~rbRenderTexture();

    static rb::Value initialize(rb::Value self, const std::vector<rb::Value>& args);
	static rb::Value create(rb::Value self, const std::vector<rb::Value>& args);

	void setSmooth(bool smooth);
	bool isSmooth() const;

    void setRepeated(bool repeated);
    bool isRepeated() const;

    static rb::Value setActive(rb::Value self, const std::vector<rb::Value>& args);

    void display();

	sf::Vector2u getSize() const;

	rb::Value getTexture() const;

protected:
    sf::RenderTarget* getRenderTarget();
    const sf::RenderTarget* getRenderTarget() const;

private:
	friend class rb::Value;

	static rbRenderTextureClass ourDefinition;

	sf::RenderTexture myObject;
};

namespace rb
{
	template<>
	rbRenderTexture* Value::to() const;
	template<>
	const rbRenderTexture* Value::to() const;
}

#endif // RBSFML_RBRENDERTEXTURE_HPP_
