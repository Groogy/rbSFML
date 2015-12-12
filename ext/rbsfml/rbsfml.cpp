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

#include <ruby.h>
#include <SFML/System/Sleep.hpp>
#include "module.hpp"
#include "class.hpp"
#include "rbtime.hpp"
#include "rbclock.hpp"
#include "rbnoncopyable.hpp"
#include "rbvector2.hpp"
#include "rbvector3.hpp"
#include "rbvideomode.hpp"
#include "rbcontextsettings.hpp"
#include "rbcontext.hpp"
#include "rbwindow.hpp"
#include "rbevent.hpp"
#include "rbjoystick.hpp"
#include "rbkeyboard.hpp"
#include "rbmouse.hpp"
#include "rbsensor.hpp"
#include "rbtouch.hpp"
#include "rbcolor.hpp"
#include "rbblendmode.hpp"

class rbSFML
{
public:
	static void sleep(rbTime* time)
	{
		sf::sleep(time->getObject());
	}
};

extern "C" void Init_rbsfml() {
	auto sfml = rb::Module<rbSFML>::defineModule("SFML");

	sfml.defineFunction<0>("seconds", &rbTime::seconds);
	sfml.defineFunction<1>("milliseconds", &rbTime::milliseconds);
	sfml.defineFunction<2>("microseconds", &rbTime::microseconds);
	sfml.defineFunction<3>("sleep", &rbSFML::sleep);

	// System
	rbNonCopyable::defineModule(rb::Value(sfml));
	rbVector2::defineClass(rb::Value(sfml));
	rbVector3::defineClass(rb::Value(sfml));
	rbTime::defineClass(rb::Value(sfml));
	rbClock::defineClass(rb::Value(sfml));

	// Window
	rbVideoMode::defineClass(rb::Value(sfml));
	rbContextSettings::defineClass(rb::Value(sfml));
	rbContext::defineClass(rb::Value(sfml));
	rbWindow::defineClass(rb::Value(sfml));
	rbEvent::defineClass(rb::Value(sfml));
	rbJoystick::defineModule(rb::Value(sfml));
	rbKeyboard::defineModule(rb::Value(sfml));
	rbMouse::defineModule(rb::Value(sfml));
	rbSensor::defineModule(rb::Value(sfml));
	rbTouch::defineModule(rb::Value(sfml));

	// Graphics
	rbColor::defineClass(rb::Value(sfml));
	rbBlendMode::defineClass(rb::Value(sfml));
}
