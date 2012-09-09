/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
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

#ifndef VARIABLES_H_
#define VARIABLES_H_

#include "common/hashmap.h"
#include "common/savefile.h"
#include "common/serializer.h"

#include "engines/myst3/myst3.h"

namespace Myst3 {

// View type
enum ViewType {
	kCube = 1,
	kFrame = 2,
	kMenu = 3
};

#define DECLARE_VAR(num, name) \
	void set##name(int32 value) { engineSet(num, value); } \
	int32 get##name() { return engineGet(num); }

class GameState {
public:
	GameState(Myst3Engine *vm);
	virtual ~GameState();

	void newGame();
	bool load(const Common::String &file);
	bool save(Common::OutSaveFile *save);

	int32 getVar(uint16 var);
	void setVar(uint16 var, int32 value);
	bool evaluate(int16 condition);
	int32 valueOrVarValue(int16 value);

	const Common::String describeVar(uint16 var);
	const Common::String describeCondition(int16 condition);

	DECLARE_VAR(14, CursorTransparency)

	DECLARE_VAR(47, ProjectorAngleX)
	DECLARE_VAR(48, ProjectorAngleY)
	DECLARE_VAR(49, ProjectorAngleZoom)
	DECLARE_VAR(50, ProjectorAngleBlur)
	DECLARE_VAR(51, DraggedWeight)

	DECLARE_VAR(57, DragEnded)
	DECLARE_VAR(58, DragLeverSpeed)
	DECLARE_VAR(59, DragPositionFound)
	DECLARE_VAR(60, DragLeverPositionChanged)

	DECLARE_VAR(61, LocationAge)
	DECLARE_VAR(62, LocationRoom)
	DECLARE_VAR(63, LocationNode)
	DECLARE_VAR(64, BookSavedAge)
	DECLARE_VAR(65, BookSavedRoom)
	DECLARE_VAR(66, BookSavedNode)
	DECLARE_VAR(67, MenuSavedAge)
	DECLARE_VAR(68, MenuSavedRoom)
	DECLARE_VAR(69, MenuSavedNode)

	DECLARE_VAR(70, SecondsCountdown)
	DECLARE_VAR(71, FrameCountdown)

	DECLARE_VAR(84, InputMousePressed)
	DECLARE_VAR(88, InputEscapePressed)
	DECLARE_VAR(89, InputTildePressed)
	DECLARE_VAR(90, InputSpacePressed)

	DECLARE_VAR(92, HotspotActiveRect)

	DECLARE_VAR(115, SunspotIntensity)
	DECLARE_VAR(116, SunspotColor)
	DECLARE_VAR(117, SunspotRadius)

	DECLARE_VAR(119, AmbiantFadeOutDelay)
	DECLARE_VAR(120, AmbiantPreviousFadeOutDelay)

	DECLARE_VAR(131, CursorLocked)
	DECLARE_VAR(132, CursorHidden)

	DECLARE_VAR(136, CameraPitch)
	DECLARE_VAR(137, CameraHeading)
	DECLARE_VAR(140, CameraMinPitch)
	DECLARE_VAR(141, CameraMaxPitch)

	DECLARE_VAR(142, MovieStartFrame)
	DECLARE_VAR(143, MovieEndFrame)
	DECLARE_VAR(146, MovieOverrideSubtitles)
	DECLARE_VAR(149, MovieConditionBit)
	DECLARE_VAR(150, MoviePreloadToMemory)
	DECLARE_VAR(151, MovieScriptDriven)
	DECLARE_VAR(152, MovieNextFrameSetVar)
	DECLARE_VAR(153, MovieNextFrameGetVar)
	DECLARE_VAR(154, MovieStartFrameVar)
	DECLARE_VAR(155, MovieEndFrameVar)
	DECLARE_VAR(156, MovieForce2d)
	DECLARE_VAR(160, MovieSynchronized)
	DECLARE_VAR(163, MovieOverrideCondition)
	DECLARE_VAR(164, MovieUVar)
	DECLARE_VAR(165, MovieVVar)
	DECLARE_VAR(166, MovieOverridePosition)
	DECLARE_VAR(167, MovieOverridePosU)
	DECLARE_VAR(168, MovieOverridePosV)
	DECLARE_VAR(173, MoviePlayingVar)

	DECLARE_VAR(178, MovieUseBackground)
	DECLARE_VAR(179, CameraSkipAnimation)

	DECLARE_VAR(185, CameraMoveSpeed)

	DECLARE_VAR(189, LocationNextNode)
	DECLARE_VAR(190, LocationNextRoom)
	DECLARE_VAR(191, LocationNextAge)

	DECLARE_VAR(195, BallPosition)
	DECLARE_VAR(196, BallFrame)
	DECLARE_VAR(197, BallLeverLeft)
	DECLARE_VAR(198, BallLeverRight)

	DECLARE_VAR(228, BallDoorOpen)

	DECLARE_VAR(243, ProjectorX)
	DECLARE_VAR(244, ProjectorY)
	DECLARE_VAR(245, ProjectorZoom)
	DECLARE_VAR(246, ProjectorBlur)
	DECLARE_VAR(247, ProjectorAngleXOffset)
	DECLARE_VAR(248, ProjectorAngleYOffset)
	DECLARE_VAR(249, ProjectorAngleZoomOffset)
	DECLARE_VAR(250, ProjectorAngleBlurOffset)

	DECLARE_VAR(277, JournalAtrusState)
	DECLARE_VAR(279, JournalSaavedroState)
	DECLARE_VAR(280, JournalSaavedroClosed)
	DECLARE_VAR(281, JournalSaavedroOpen)
	DECLARE_VAR(282, JournalSaavedroLastPage)
	DECLARE_VAR(283, JournalSaavedroChapter)
	DECLARE_VAR(284, JournalSaavedroPageInChapter)

	DECLARE_VAR(329, TeslaAllAligned)
	DECLARE_VAR(330, TeslaTopAligned)
	DECLARE_VAR(331, TeslaMiddleAligned)
	DECLARE_VAR(332, TeslaBottomAligned)
	DECLARE_VAR(333, TeslaMovieStart)

	DECLARE_VAR(444, ResonanceRingsSolved)

	DECLARE_VAR(460, PinballRemainingPegs)

	DECLARE_VAR(480, BookStateTomahna)
	DECLARE_VAR(481, BookStateReleeshahn)

	DECLARE_VAR(489, SymbolCode2Solved)
	DECLARE_VAR(495, SymbolCode1AllSolved)
	DECLARE_VAR(496, SymbolCode1CurrentSolved)
	DECLARE_VAR(497, SymbolCode1TopSolved)
	DECLARE_VAR(502, SymbolCode1LeftSolved)
	DECLARE_VAR(507, SymbolCode1RightSolved)

	DECLARE_VAR(1322, ZipModeEnabled)
	DECLARE_VAR(1323, SubtitlesEnabled)
	DECLARE_VAR(1324, WaterEffects)
	DECLARE_VAR(1325, TransitionSpeed)
	DECLARE_VAR(1326, MouseSpeed)
	DECLARE_VAR(1327, DialogResult)

	DECLARE_VAR(1337, MenuEscapePressed)
	DECLARE_VAR(1338, MenuNextAction)
	DECLARE_VAR(1339, MenuLoadBack)
	DECLARE_VAR(1340, MenuSaveBack)
	DECLARE_VAR(1341, MenuSaveAction)
	DECLARE_VAR(1342, MenuOptionsBack)

	DECLARE_VAR(1350, MenuSaveLoadPageLeft)
	DECLARE_VAR(1351, MenuSaveLoadPageRight)
	DECLARE_VAR(1352, MenuSaveLoadSelectedItem)
	DECLARE_VAR(1353, MenuSaveLoadCurrentPage)

	DECLARE_VAR(1374, OverallVolume)
	DECLARE_VAR(1377, MusicVolume)
	DECLARE_VAR(1380, MusicFrequency)
	DECLARE_VAR(1393, LanguageAudio)
	DECLARE_VAR(1394, LanguageText)

	DECLARE_VAR(1396, HotspotHovered)
	DECLARE_VAR(1397, SpotSubtitle)

	DECLARE_VAR(1399, DragLeverLimited)
	DECLARE_VAR(1400, DragLeverLimitMin)
	DECLARE_VAR(1401, DragLeverLimitMax)

	void updateFrameCounters();
	uint getFrameCount() { return _data.currentFrame; }

	ViewType getViewType() { return static_cast<ViewType>(_data.currentNodeType); }
	void setViewType(ViewType t) { _data.currentNodeType = t; }

	float getLookAtFOV() { return _data.lookatFOV; }
	void setLookAtFOV(float fov) { _data.lookatFOV = fov; }
	float getLookAtPitch() { return _data.lookatPitch; }
	float getLookAtHeading() { return _data.lookatHeading; }
	void lookAt(float pitch, float heading) { _data.lookatPitch = pitch; _data.lookatHeading = heading; }

	void limitCubeCamera(float minPitch, float maxPitch, float minHeading, float maxHeading);
	void freeCubeCamera() { _data.limitCubeCamera = false; }
	bool isCameraLimited() { return _data.limitCubeCamera != 0; }
	float getMinPitch() { return _data.minPitch; }
	float getMaxPitch() { return _data.maxPitch; }
	float getMinHeading() { return _data.minHeading; }
	float getMaxHeading() { return _data.maxHeading; }

	Common::Array<uint16> getInventory();
	void updateInventory(const Common::Array<uint16> &items);

private:
	Myst3Engine *_vm;

	static const uint32 kSaveVersion = 148;

	struct StateData {
		uint32 version;
		uint32 gameRunning;
		uint32 currentFrame;
		uint32 nextSecondsUpdate;
		uint32 secondsPlayed;
		uint32 dword_4C2C44;
		uint32 dword_4C2C48;
		uint32 dword_4C2C4C;
		uint32 dword_4C2C50;
		uint32 dword_4C2C54;
		uint32 dword_4C2C58;
		uint32 dword_4C2C5C;
		uint32 dword_4C2C60;
		uint32 currentNodeType;
		float lookatPitch;
		float lookatHeading;
		float lookatFOV;
		float pitchOffset;
		float headingOffset;
		uint32 limitCubeCamera;
		float minPitch;
		float maxPitch;
		float minHeading;
		float maxHeading;
		uint32  dword_4C2C90;
		int32 vars[2048];
		uint32 inventoryCount;
		uint32 inventoryList[7];
		int8 zipDestinations[256];
	};

	StateData _data;

	struct Description {
		Description() {}
		Description(uint16 v, const char *n, bool u) : var(v), name(n), unknown(u) {}

		uint16 var;
		const char *name;
		bool unknown;
	};

	Common::HashMap<uint16, Description> _descriptions;

	void syncWithSaveGame(Common::Serializer &s);

	void checkRange(uint16 var);

	int32 engineGet(uint16 var);
	void engineSet(uint16 var, int32 value);
};

} /* namespace Myst3 */
#endif /* VARIABLES_H_ */
