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

#include "backends/vkeybd/virtual-input.h"

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

bool VirtualInput::openPack(const String &packName, const FSNode &node) {
	if (node.getChild(packName + ".xml").exists()) {
		_fileArchive = new FSDirectory(node, 1);

		// uncompressed keyboard pack
		if (!_parser->loadFile(node.getChild(packName + ".xml"))) {
			delete _fileArchive;
			_fileArchive = 0;
			return false;
		}

		return true;
	}

	_fileArchive = 0;
	// compressed keyboard pack
	if (node.getChild(packName + ".zip").exists()) {
		_fileArchive = makeZipArchive(node.getChild(packName + ".zip"));
	} else {
		Common::ArchiveMemberPtr member = SearchMan.getMember(packName + ".zip");
		if (member) {
			_fileArchive = makeZipArchive(member->createReadStream());
		}
	}

	if (_fileArchive) {
		if (_fileArchive && _fileArchive->hasFile(packName + ".xml")) {
			if (!_parser->loadStream(_fileArchive->createReadStreamForMember(packName + ".xml"))) {
				delete _fileArchive;
				_fileArchive = 0;
				return false;
			}
		} else {
			warning("Could not find %s.xml file in %s.zip keyboard pack", packName.c_str(), packName.c_str());
			delete _fileArchive;
			_fileArchive = 0;
			return false;
		}

		return true;
	}

	return false;
}

bool VirtualKeyboard::loadKeyboardPack(const String &packName) {
	_kbdGUI->initSize(_system->getOverlayWidth(), _system->getOverlayHeight());

	delete _fileArchive;
	_fileArchive = 0;
	_loaded = false;

	bool opened = false;
	if (ConfMan.hasKey("vkeybdpath"))
		opened = openPack(packName, FSNode(ConfMan.get("vkeybdpath")));
	else if (ConfMan.hasKey("extrapath"))
		opened = openPack(packName, FSNode(ConfMan.get("extrapath")));

	// fallback to the current dir
	if (!opened)
		opened = openPack(packName, FSNode("."));

	if (opened) {
		_parser->setParseMode(VirtualKeyboardParser::kParseFull);
		_loaded = _parser->parse();

		if (_loaded) {
			debug("Keyboard pack '%s' loaded successfully", packName.c_str());
		} else {
			warning("Error parsing the keyboard pack '%s'", packName.c_str());

			delete _fileArchive;
			_fileArchive = 0;
		}
	} else {
		warning("Keyboard pack not found");
	}

	return _loaded;
}

bool VirtualKeyboard::checkModeResolutions() {
	_parser->setParseMode(VirtualKeyboardParser::kParseCheckResolutions);
	_loaded = _parser->parse();
	if (_currentMode)
		_kbdGUI->initMode(_currentMode);
	return _loaded;
}

String VirtualKeyboard::findArea(int16 x, int16 y) {
	return _currentMode->imageMap.findMapArea(x, y);
}

void VirtualKeyboard::processAreaClick(const String &area) {
	if (!_currentMode->events.contains(area))
		return;

	VKEvent *evt = _currentMode->events[area];

	switch (evt->type) {
	case kVKEventKey:
		// add virtual keypress to queue
		_keyQueue.insertKey(*(KeyState *)evt->data);
		break;
	case kVKEventModifier:
		_keyQueue.toggleFlags(*(byte *)(evt->data));
		break;
	case kVKEventSwitchMode:
		// switch to new mode
		switchMode((char *)evt->data);
		_keyQueue.clearFlags();
		break;
	case kVKEventSubmit:
		close(true);
		break;
	case kVKEventCancel:
		close(false);
		break;
	case kVKEventClear:
		_keyQueue.clear();
		break;
	case kVKEventDelete:
		_keyQueue.deleteKey();
		break;
	case kVKEventMoveLeft:
		_keyQueue.moveLeft();
		break;
	case kVKEventMoveRight:
		_keyQueue.moveRight();
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

void VirtualKeyboard::handleMouseDown(int16 x, int16 y) {
	_areaDown = findArea(x, y);
	if (_areaDown.empty())
		_kbdGUI->startDrag(x, y);
}

void VirtualKeyboard::handleMouseUp(int16 x, int16 y) {
	if (!_areaDown.empty() && _areaDown == findArea(x, y)) {
		processAreaClick(_areaDown);
		_areaDown.clear();
	}
	_kbdGUI->endDrag();
}

void VirtualKeyboard::show() {
	if (!_loaded) {
		warning("Virtual keyboard not loaded");
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
