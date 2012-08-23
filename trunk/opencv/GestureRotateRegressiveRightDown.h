#pragma once

#include "GestureSequence.h"
#include "GestureRotateRightDown.h"
#include "GestureRotateLeftUp.h"

class GestureRotateRegressiveRightDown : public GestureSequence{
	public:
		GestureRotateRegressiveRightDown(ColourToTrack* primary, ColourToTrack* secondary,float distanceTolerance=Dd,
			unsigned int irrelevantTolerance=TOLERANCE_IRRELEVANT,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
			unsigned int movementLength=MOVEMENT_LENGTH_Y/2);
		~GestureRotateRegressiveRightDown() { delete regression[0]; delete regression[1]; }
	protected:
};