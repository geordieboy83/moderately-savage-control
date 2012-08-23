#pragma once

#include "SpringGesture.h"

class GestureRotateRightUp : public SpringGesture {
	public:
		GestureRotateRightUp(float distanceTolerance=Dd,
			unsigned int irrelevantTolerance=TOLERANCE_IRRELEVANT,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
			unsigned int movementLength=MOVEMENT_LENGTH_Y/2, ColourToTrack* primary=NULL, ColourToTrack* secondary=NULL);
		~GestureRotateRightUp();
		virtual string getType() { return "RIGHT o UP"; }
	protected:
};