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

#ifndef COMMON_VIRTUAL_INPUT_H
#define COMMON_VIRTUAL_INPUT_H

#include "common/scummsys.h"

class OSystem;

namespace Common {

class VirtualInput {
protected:

	/**
	 * Enum to describe the different types of events that can be associated
	 * with an area of the virtual keyboard bitmap.
	 */
	enum VKEventType {
		/** Standard key press event */
		kVKEventKey,
		/** Modifier key press event */
		kVKEventModifier,
		/** Switch the mode of the keyboard */
		kVKEventSwitchMode,
		/** Close the keyboard, submitting all keypresses */
		kVKEventSubmit,
		/** Close the keyboard, without submitting keypresses */
		kVKEventCancel,
		/** Clear the virtual keypress queue */
		kVKEventClear,
		/** Move the keypress queue insert position backwards */
		kVKEventMoveLeft,
		/** Move the keypress queue insert position forwards */
		kVKEventMoveRight,
		/** Delete keypress from queue at the current insert position */
		kVKEventDelete
	};

	/** VKEvent struct encapsulates data on a virtual keyboard event */
	struct VKEvent {
		String name;
		VKEventType type;
		/**
		 * Void pointer that will point to different types of data depending
		 * on the type of the event, these are:
		 * - KeyState struct for kVKEventKey events
		 * - a flags byte for kVKEventModifier events
		 * - c-string stating the name of the new mode for kSwitchMode events
		 */
		void *data;

		VKEvent() : data(0) {}
		~VKEvent() {
			if (data)
				free(data);
		}
	};

	typedef HashMap<String, VKEvent *> VKEventMap;

	typedef HashMap<String, Mode, IgnoreCase_Hash, IgnoreCase_EqualTo> ModeMap;

	/**
	 * Mode struct encapsulates all the data for each mode of the keyboard
	 */
	struct Mode {
		String              name;
		String              resolution;
		String              bitmapName;
		Graphics::Surface   *image;
		OverlayColor        transparentColor;
		ImageMap            imageMap;
		VKEventMap          events;
		Rect                displayArea;
		OverlayColor        displayFontColor;

		Mode() : image(0) {}
		~Mode() {
			if (image) {
				image->free();
				delete image;
				image = 0;
			}
		}
	};

public:

	/**
	 * Loads the keyboard pack with the given name.
	 * The system first looks for an uncompressed keyboard pack by searching
	 * for packName.xml in the filesystem, if this does not exist then it
	 * searches for a compressed keyboard pack by looking for packName.zip.
	 * @param packName  name of the keyboard pack
	 */
	bool loadKeyboardPack(const String &packName);

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

	/**
	 * Returns true if the keyboard is loaded and ready to be shown
	 */
	virtual bool isLoaded() {
		return _loaded;
	}

protected:

	friend class VirtualKeyboardGUI;
	VirtualKeyboardGUI *_kbdGUI;

	friend class VirtualKeyboardParser;
	VirtualKeyboardParser *_parser;

	OSystem *_system;
	Archive *_fileArchive;

	bool _loaded;

	ModeMap _modes;
	Mode *_initialMode;
	Mode *_currentMode;

	String _areaDown;

	virtual void processAreaClick(const String &area);
};

} // End of namespace Common

#endif // #ifndef COMMON_VIRTUAL_INPUT_H
