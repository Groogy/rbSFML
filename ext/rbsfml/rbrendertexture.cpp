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

#include "rbrendertexture.hpp"
#include "rbtexture.hpp"
#include "rbvector2.hpp"
#include "error.hpp"
#include "macros.hpp"
#include "base.hpp"

namespace
{
    constexpr char symVarInternalOwnerRef[] = "@__internal__owner_ref";

    class rbTextureRefAllocator
    {
    public:
        static rbTexture* allocate(sf::Texture* texture)
        {
            void* memory = xmalloc(sizeof(rbTexture));
            if(memory == nullptr) rb_memerror();
            rbTexture* object = new(memory) rbTexture(texture);
            return object;
        }

        static void free(void* memory)
        {
            rbTexture* object = static_cast<rbTexture*>(memory);
            object->~rbTexture();
            xfree(memory);
        }
    };
}

rbRenderTextureClass rbRenderTexture::ourDefinition;

void rbRenderTexture::defineClass(const rb::Value& sfml)
{
	ourDefinition = rbRenderTextureClass::defineClassUnder("RenderTexture", sfml);
	ourDefinition.includeModule(rb::Value(rbRenderTarget::getDefinition()));
	ourDefinition.defineMethod<0>("initialize", &rbRenderTexture::initialize);
	ourDefinition.defineMethod<1>("create", &rbRenderTexture::create);
	ourDefinition.defineMethod<2>("smooth=", &rbRenderTexture::setSmooth);
	ourDefinition.defineMethod<3>("smooth?", &rbRenderTexture::isSmooth);
	ourDefinition.defineMethod<4>("repeated=", &rbRenderTexture::setRepeated);
    ourDefinition.defineMethod<5>("repeated?", &rbRenderTexture::isRepeated);
    ourDefinition.defineMethod<6>("set_active", &rbRenderTexture::setActive);
    ourDefinition.defineMethod<7>("display", &rbRenderTexture::display);
	ourDefinition.defineMethod<8>("size", &rbRenderTexture::getSize);
	ourDefinition.defineMethod<9>("texture", &rbRenderTexture::getTexture);

	ourDefinition.aliasMethod("set_active", "active=");
}

rbRenderTextureClass& rbRenderTexture::getDefinition()
{
    return ourDefinition;
}

rbRenderTexture::rbRenderTexture()
: rbRenderTarget()
, myObject()
{
}

rbRenderTexture::~rbRenderTexture()
{
}

rb::Value rbRenderTexture::initialize(rb::Value self, const std::vector<rb::Value>& args)
{
    unsigned int width;
    unsigned int height;
    bool depthBuffer = false;
    switch(args.size())
    {
        case 0:
            return self;
        case 3:
            depthBuffer = args[2].to<bool>();
        case 2:
            width = args[0].to<unsigned int>();
            height = args[1].to<unsigned int>();
            break;
        default:
            rb::expectedNumArgs(args.size(), "0, 2 or 3");
            break;
    }
    self.to<rbRenderTexture*>()->myObject.create(width, height, depthBuffer);
    return self;
}

rb::Value rbRenderTexture::create(rb::Value self, const std::vector<rb::Value>& args)
{
    unsigned int width = 0;
    unsigned int height = 0;
    bool depthBuffer = false;
    switch(args.size())
    {
        case 3:
            depthBuffer = args[2].to<bool>();
        case 2:
            width = args[0].to<unsigned int>();
            height = args[1].to<unsigned int>();
            break;
        default:
            rb::expectedNumArgs(args.size(), 2, 3);
            break;
    }
    self.to<rbRenderTexture*>()->myObject.create(width, height, depthBuffer);
    return self;
}

void rbRenderTexture::setSmooth(bool smooth)
{
    myObject.setSmooth(smooth);
}

bool rbRenderTexture::isSmooth() const
{
    return myObject.isSmooth();
}

void rbRenderTexture::setRepeated(bool repeated)
{
    myObject.setRepeated(repeated);
}

bool rbRenderTexture::isRepeated() const
{
    return myObject.isRepeated();
}

rb::Value rbRenderTexture::setActive(rb::Value self, const std::vector<rb::Value>& args)
{
    bool flag = true;
    switch(args.size())
    {
        case 1:
            flag = args[0].to<bool>();
        case 0:
            break;
        default:
            rb::expectedNumArgs(args.size(), 0, 1);
            break;
    }
    self.to<rbRenderTexture*>()->myObject.setActive(flag);
    return self;
}

void rbRenderTexture::display()
{
    myObject.display();
}

sf::Vector2u rbRenderTexture::getSize() const
{
    return myObject.getSize();
}

rb::Value rbRenderTexture::getTexture() const
{
    rb::Value self(this);
    rbTexture* object = rbTextureRefAllocator::allocate(const_cast<sf::Texture*>(&myObject.getTexture()));
    rb::Value value = rbTexture::getDefinition().newObjectWithObject<rbTextureRefAllocator>(object);
    value.setVar<symVarInternalOwnerRef>(self);
    value.freeze();
    return value;
}

sf::RenderTarget* rbRenderTexture::getRenderTarget()
{
    return &myObject;
}

const sf::RenderTarget* rbRenderTexture::getRenderTarget() const
{
    return &myObject;
}

namespace rb
{

template<>
rbRenderTexture* Value::to() const
{
	errorHandling(T_DATA);
	rbRenderTexture* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbRenderTexture, object);
	return object;
}

template<>
const rbRenderTexture* Value::to() const
{
	errorHandling(T_DATA);
	const rbRenderTexture* object = nullptr;
	if(myValue != Qnil)
	    Data_Get_Struct(myValue, rbRenderTexture, object);
	return object;
}

}