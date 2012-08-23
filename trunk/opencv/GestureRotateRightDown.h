#pragma once

#include "SpringGesture.h"

class GestureRotateRightDown : public SpringGesture {
	public:
		GestureRotateRightDown(float distanceTolerance=Dd,
			unsigned int irrelevantTolerance=TOLERANCE_IRRELEVANT,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
			unsigned int movementLength=MOVEMENT_LENGTH_Y/2, ColourToTrack* primary=NULL, ColourToTrack* secondary=NULL);
		~GestureRotateRightDown();
		virtual string getType() { return "RIGHT o DOWN"; }
	protected:
};