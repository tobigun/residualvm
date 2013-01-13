/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "common/mutex.h"
#include "common/str.h"
#include "common/stream.h"
#include "audio/mixer.h"
#include "audio/audiostream.h"
#include "engines/grim/emi/sound/track.h"

namespace Grim {

SoundTrack::SoundTrack() {
	_stream = NULL;
	_handle = NULL;
	_paused = false;
	_disposeAfterPlaying = DisposeAfterUse::YES;
}

SoundTrack::~SoundTrack() {
	if (_stream && (_disposeAfterPlaying == DisposeAfterUse::NO || !_handle))
		delete _stream;
}
	
Common::String SoundTrack::getSoundName() {
	return _soundName;
}

void SoundTrack::setSoundName(Common::String name) {
	_soundName = name;
}

bool SoundTrack::play() {
	if (_stream) {
		// If _disposeAfterPlaying is NO, the destructor will take care of the stream.
		g_system->getMixer()->playStream(_soundType, _handle, _stream, -1, Audio::Mixer::kMaxChannelVolume, 0, _disposeAfterPlaying);
		return true;
	}
	return false;
}

void SoundTrack::pause() {
	_paused = !_paused;
	if (_stream) {
		g_system->getMixer()->pauseHandle(*_handle, _paused);
	}
}

void SoundTrack::stop() {
	if (_handle)
		g_system->getMixer()->stopHandle(*_handle);
}

} // end of namespace Grim
