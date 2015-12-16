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

#include "rbshader.hpp"
#include "rbvector2.hpp"
#include "rbvector3.hpp"
#include "rbcolor.hpp"
#include "rbtexture.hpp"
#include "rbtransform.hpp"
#include "rbnoncopyable.hpp"
#include "error.hpp"
#include "macros.hpp"

rbShaderClass rbShader::ourDefinition;
rb::Module<sf::Shader::CurrentTextureType> rbShader::ourCurrentTextureTypeDefinition;

void rbShader::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbShaderClass::defineClassUnder("Shader", sfml);
	ourDefinition.includeModule(rb::Value(rbNonCopyable::getDefinition()));
	ourDefinition.defineMethod<0>("load_from_file", &rbShader::loadFromFile);
    ourDefinition.defineMethod<1>("load_from_memory", &rbShader::loadFromMemory);
    ourDefinition.defineMethod<2>("set_parameter", &rbShader::setParameter);
    ourDefinition.defineMethod<3>("native_handle", &rbShader::getNativeHandle);

    ourDefinition.defineFunction<4>("bind", &rbShader::bind);
    ourDefinition.defineFunction<5>("available?", &rbShader::isAvailable);

    ourDefinition.aliasMethod("set_parameter", "[]=");

    ourDefinition.defineConstant("Vertex", rb::Value(sf::Shader::Vertex));
    ourDefinition.defineConstant("Fragment", rb::Value(sf::Shader::Fragment));

    ourCurrentTextureTypeDefinition = rb::Module<sf::Shader::CurrentTextureType>::defineModuleUnder("CurrentTexture", rb::Value(ourDefinition));
}

rbShader::rbShader()
: rb::Object()
, myObject()
{
}

rbShader::~rbShader()
{
}

bool rbShader::loadFromFile(rb::Value arg1, rb::Value arg2)
{
    if(arg2.getType() == rb::ValueType::Fixnum)
        return myObject.loadFromFile(arg1.to<std::string>(), arg2.to<sf::Shader::Type>());
    else
        return myObject.loadFromFile(arg1.to<std::string>(), arg2.to<std::string>());
}

bool rbShader::loadFromMemory(rb::Value arg1, rb::Value arg2)
{
    if(arg2.getType() == rb::ValueType::Fixnum)
        return myObject.loadFromMemory(arg1.to<std::string>(), arg2.to<sf::Shader::Type>());
    else
        return myObject.loadFromMemory(arg1.to<std::string>(), arg2.to<std::string>());
}

rb::Value rbShader::setParameter(rb::Value self, const std::vector<rb::Value>& args)
{
    sf::Shader& shader = self.to<sf::Shader&>();
    switch(args.size())
    {
        case 2:
            if(args[1].isKindOf(rb::Value(rbVector2::getDefinition())))
            {
                shader.setParameter(args[0].to<std::string>(), args[1].to<sf::Vector2f>());
            }
            else if(args[1].isKindOf(rb::Value(rbVector3::getDefinition())))
            {
                shader.setParameter(args[0].to<std::string>(), args[1].to<sf::Vector3f>());
            }
            else if(args[1].isKindOf(rb::Value(rbColor::getDefinition())))
            {
                shader.setParameter(args[0].to<std::string>(), args[1].to<sf::Color>());
            }
            else if(args[1].isKindOf(rb::Value(rbTransform::getDefinition())))
            {
                shader.setParameter(args[0].to<std::string>(), args[1].to<const sf::Transform&>());
            }
            else if(args[1].isKindOf(rb::Value(rbTexture::getDefinition())))
            {
                shader.setParameter(args[0].to<std::string>(), args[1].to<const sf::Texture&>());
            }
            else if(args[1] == rb::Value(ourCurrentTextureTypeDefinition))
            {
                shader.setParameter(args[0].to<std::string>(), sf::Shader::CurrentTexture);
            }
            else
            {
                shader.setParameter(args[0].to<std::string>(), args[1].to<float>());
            }
            break;
        case 3:
            shader.setParameter(args[0].to<std::string>(), args[1].to<float>(), args[2].to<float>());
            break;
        case 4:
            shader.setParameter(args[0].to<std::string>(), args[1].to<float>(), args[2].to<float>(), args[3].to<float>());
            break;
        case 5:
            shader.setParameter(args[0].to<std::string>(), args[1].to<float>(), args[2].to<float>(), args[3].to<float>(), args[4].to<float>());
            break;
        default:
            rb::expectedNumArgs( args.size(), 2, 5);
            break;
    }
    return rb::Nil;
}

unsigned int rbShader::getNativeHandle() const
{
    return myObject.getNativeHandle();
}

void rbShader::bind(const rbShader* shader)
{
    if(shader)
        sf::Shader::bind(&shader->myObject);
    else
        sf::Shader::bind(nullptr);
}

bool rbShader::isAvailable()
{
    return sf::Shader::isAvailable();
}

namespace rb
{

template<>
rbShader* Value::to() const
{
	errorHandling(T_DATA);
	rbShader* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbShader, object);
	return object;
}

template<>
const rbShader* Value::to() const
{
	errorHandling(T_DATA);
	const rbShader* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbShader, object);
	return object;
}

template<>
sf::Shader& Value::to() const
{
    return to<rbShader*>()->myObject;
}

template<>
const sf::Shader& Value::to() const
{
    return to<const rbShader*>()->myObject;
}

template<>
sf::Shader::Type Value::to() const
{
    errorHandling(T_FIXNUM);
    return static_cast<sf::Shader::Type>(to<unsigned int>());
}
template<>
Value Value::create(sf::Shader::Type value)
{
    return create(static_cast<unsigned int>(value));
}

}