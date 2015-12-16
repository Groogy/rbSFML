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

#ifndef RBSFML_RBSHADER_HPP_
#define RBSFML_RBSHADER_HPP_

#include <SFML/Graphics/Shader.hpp>
#include "class.hpp"
#include "object.hpp"

class rbShader;

typedef rb::Class<rbShader> rbShaderClass;

class rbShader : public rb::Object
{
public:
	static void defineClass(const rb::Value& sfml);

	rbShader();
	~rbShader();

	bool loadFromFile(rb::Value arg1, rb::Value arg2);
	bool loadFromMemory(rb::Value arg1, rb::Value arg2);

	static rb::Value setParameter(rb::Value self, const std::vector<rb::Value>& args);

private:
    friend class rb::Value;
	static rbShaderClass ourDefinition;
	static rb::Module<sf::Shader::CurrentTextureType> ourCurrentTextureTypeDefinition;

	sf::Shader myObject;
};

namespace rb
{
	template<>
	rbShader* Value::to() const;
	template<>
	const rbShader* Value::to() const;
	template<>
    sf::Shader& Value::to() const;
    template<>
    const sf::Shader& Value::to() const;

    template<>
    sf::Shader::Type Value::to() const;
    template<>
    Value Value::create(sf::Shader::Type value);
}

#endif // RBSFML_RBSHADER_HPP_
