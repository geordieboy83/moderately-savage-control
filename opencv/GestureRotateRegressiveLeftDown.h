#pragma once

#include "SpringGesture.h"
#include "GestureRotateRightUp.h"
#include "GestureRotateLeftDown.h"

class GestureRotateRegressiveLeftDown : public GestureSequence{
	public:
		GestureRotateRegressiveLeftDown(ColourToTrack* primary=NULL, ColourToTrack* secondary=NULL,
			float distanceTolerance=Dd,
			unsigned int irrelevantTolerance=TOLERANCE_IRRELEVANT,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
			unsigned int movementLength=MOVEMENT_LENGTH_Y/2);
		~GestureRotateRegressiveLeftDown() { delete regression[0]; delete regression[1]; }
	protected:
};