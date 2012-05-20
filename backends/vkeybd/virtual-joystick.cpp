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

#include "common/scummsys.h"

#ifdef ENABLE_VJOY

#include "backends/vkeybd/virtual-joystick.h"

#include "backends/vkeybd/virtual-keyboard-gui.h"
#include "backends/vkeybd/virtual-keyboard-parser.h"
#include "backends/vkeybd/keycode-descriptions.h"
#include "common/config-manager.h"
#include "common/unzip.h"

namespace Common {

VirtualJoystick::VirtualJoystick() : _currentMode(0) {
	assert(g_system);
	_system = g_system;

	_parser = new VirtualKeyboardParser(this);
	_kbdGUI = new VirtualKeyboardGUI(this);
	_submitKeys = _loaded = false;
	_fileArchive = 0;
}

VirtualKeyboard::~VirtualKeyboard() {
	deleteEvents();
	delete _kbdGUI;
	delete _parser;
	delete _fileArchive;
}

void VirtualKeyboard::deleteEvents() {
	for (ModeMap::iterator it_m = _modes.begin(); it_m != _modes.end(); ++it_m) {
		VKEventMap &evt = it_m->_value.events;
		for (VKEventMap::iterator it_e = evt.begin(); it_e != evt.end(); ++it_e)
			delete it_e->_value;
	}
}

void VirtualKeyboard::reset() {
	deleteEvents();
	_modes.clear();
	_initialMode = _currentMode = 0;
	_keyQueue.clear();
	_loaded = false;
	_kbdGUI->reset();
}

bool VirtualKeyboard::checkModeResolutions() {
	_parser->setParseMode(VirtualKeyboardParser::kParseCheckResolutions);
	_loaded = _parser->parse();
	if (_currentMode)
		_kbdGUI->initMode(_currentMode);
	return _loaded;
}

void VirtualKeyboard::processAreaClick(const String &area) {
	if (!_currentMode->events.contains(area))
		return;

	VKEvent *evt = _currentMode->events[area];

	switch (evt->type) {
	case kVKEventKey:
		break;
	case kVKEventModifier:
		break;
	case kVKEventSwitchMode:
		break;
	case kVKEventSubmit:
		break;
	case kVKEventCancel:
		break;
	case kVKEventClear:
		break;
	case kVKEventDelete:
		break;
	case kVKEventMoveLeft:
		break;
	case kVKEventMoveRight:
		break;
	}
}

void VirtualKeyboard::switchMode(Mode *newMode) {
	_kbdGUI->initMode(newMode);
	_currentMode = newMode;
}

void VirtualKeyboard::switchMode(const String &newMode) {
	if (!_modes.contains(newMode)) {
		warning("Keyboard mode '%s' unknown", newMode.c_str());
	} else {
		switchMode(&_modes[newMode]);
	}
}

void VirtualKeyboard::show() {
	if (!_loaded) {
		warning("Virtual joystick not loaded");
		return;
	} else {
		_kbdGUI->checkScreenChanged();
	}

	switchMode(_initialMode);
	_kbdGUI->run();

	if (_submitKeys) {
		EventManager *eventMan = _system->getEventManager();
		assert(eventMan);

		// push keydown & keyup events into the event manager
		Event evt;
		evt.synthetic = false;
		while (!_keyQueue.empty()) {
			evt.kbd = _keyQueue.pop();
			evt.type = EVENT_KEYDOWN;
			eventMan->pushEvent(evt);
			evt.type = EVENT_KEYUP;
			eventMan->pushEvent(evt);
		}
	} else {
		_keyQueue.clear();
	}
}

void VirtualKeyboard::close(bool submit) {
	_submitKeys = submit;
	_kbdGUI->close();
}

bool VirtualKeyboard::isDisplaying() {
	return _kbdGUI->isDisplaying();
}

} // End of namespace Common

#endif // #ifdef ENABLE_VKEYBD
