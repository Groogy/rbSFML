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

#include "rbrenderstates.hpp"
#include "rbblendmode.hpp"
#include "rbtransform.hpp"
#include "rbtexture.hpp"
#include "rbshader.hpp"
#include "error.hpp"
#include "macros.hpp"
#include "base.hpp"

namespace 
{
	constexpr char symVarBlendMode[] = "@blend_mode";
	constexpr char symVarTransform[] = "@transform";
	constexpr char symVarTexture[] = "@texture";
	constexpr char symVarShader[] = "@shader";
}

rbRenderStatesClass rbRenderStates::ourDefinition;

void rbRenderStates::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbRenderStatesClass::defineClassUnder<rb::RubyObjAllocator>("RenderStates", sfml);
	ourDefinition.defineMethod<0>("initialize", &rbRenderStates::initialize);
	ourDefinition.defineMethod<1>("initialize_copy", &rbRenderStates::initializeCopy);
	ourDefinition.defineMethod<2>("marshal_dump", &rbRenderStates::marshalDump);

	ourDefinition.defineAttribute("blend_mode", true, true);
	ourDefinition.defineAttribute("transform", true, true);
	ourDefinition.defineAttribute("texture", true, true);
	ourDefinition.defineAttribute("shader", true, true);
}

const rbRenderStatesClass& rbRenderStates::getDefinition()
{
	return ourDefinition;
}

rb::Value rbRenderStates::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
    self.setVar<symVarBlendMode>(rbBlendMode::getDefinition().newObject());
    self.setVar<symVarTransform>(rbTransform::getDefinition().newObject());
    self.setVar<symVarTexture>(rb::Nil);
    self.setVar<symVarShader>(rb::Nil);
	switch( args.size() )
    {
        case 0:
            break;
        case 1:
        	if(args[0].isKindOf(rb::Value(rbBlendMode::getDefinition())))
        	{
        		self.setVar<symVarBlendMode>(args[0]);
        	}
        	else if(args[0].isKindOf(rb::Value(rbTransform::getDefinition())))
            {
                self.setVar<symVarTransform>(args[0]);
            }
            else if(args[0].isKindOf(rb::Value(rbTexture::getDefinition())))
            {
                self.setVar<symVarTexture>(args[0]);
            }
            else if(args[0].isKindOf(rb::Value(rbShader::getDefinition())))
            {
                self.setVar<symVarShader>(args[0]);
            }
        	else
        	{
        		rbRenderStates::initializeCopy(self, args[0]);
        	}
            break;
        case 4:
        	self.setVar<symVarBlendMode>(args[0]);
        	self.setVar<symVarTransform>(args[1]);
        	self.setVar<symVarTexture>(args[2]);
        	self.setVar<symVarShader>(args[3]);
            break;
        default:
        	rb::expectedNumArgs( args.size(), "0, 1 or 4" );
        	break;
    }

	return self;
}

rb::Value rbRenderStates::initializeCopy(rb::Value self, const rb::Value& value)
{
	self.setVar<symVarBlendMode>(value.getVar<symVarBlendMode, rb::Value>());
    self.setVar<symVarTransform>(value.getVar<symVarTransform, rb::Value>());
    self.setVar<symVarTexture>(value.getVar<symVarTexture, rb::Value>());
    self.setVar<symVarShader>(value.getVar<symVarShader, rb::Value>());
	return self;
}

rb::Value rbRenderStates::marshalDump() const
{
	rb::raise(rb::TypeError, "can't dump %s", ourDefinition.getName().c_str() );
	return rb::Nil;
}

namespace rb
{

template<>
sf::RenderStates Value::to() const
{
    errorHandling(T_OBJECT);
    sf::RenderStates states(
        getVar<symVarBlendMode, sf::BlendMode>(), getVar<symVarTransform, const sf::Transform&>(),
        nullptr, nullptr
    );
    if(getVar<symVarTexture, rb::Value>() != rb::Nil)
        states.texture = &getVar<symVarTexture, const sf::Texture&>();
    if(getVar<symVarShader, rb::Value>() != rb::Nil)
        states.shader = &getVar<symVarShader, const sf::Shader&>();
    return states;
}

}