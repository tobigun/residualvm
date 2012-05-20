/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef COMMON_VIRTUAL_JOYSTICK_H
#define COMMON_VIRTUAL_JOYSTICK_H

#include "common/scummsys.h"

#ifdef ENABLE_VJOY

class OSystem;

#include "common/events.h"
#include "common/hashmap.h"
#include "common/hash-str.h"
#include "common/keyboard.h"
#include "common/list.h"
#include "common/str.h"
#include "common/fs.h"

#include "backends/vkeybd/image-map.h"
#include "graphics/surface.h"


namespace Common {

class Archive;

class VirtualKeyboardGUI;
class VirtualKeyboardParser;

/**
 * Class that handles the functionality of the virtual joystick.
 */
class VirtualJoystick {
public:

	VirtualJoystick();

	virtual ~VirtualJoystick();

	/**
	 * Shows the keyboard, starting an event loop that will intercept all
	 * user input (like a modal GUI dialog).
	 * It is assumed that the game has been paused, before this is called
	 */
	virtual void show();

	/**
	 * Hides the keyboard, ending the event loop.
	 * @param submit    if true all accumulated key presses are submitted to
	 *                  the event manager
	 */
	virtual void close(bool submit);

	/**
	 * Returns true if the keyboard is currently being shown
	 */
	virtual bool isDisplaying();

protected:

	void reset();
	void deleteEvents();
	bool checkModeResolutions();
	void switchMode(Mode *newMode);
	void switchMode(const String &newMode);
	virtual void processAreaClick(const String &area);
};

} // End of namespace Common

#endif // #ifdef ENABLE_VJOY

#endif // #ifndef COMMON_VIRTUAL_JOYSTICK_H
