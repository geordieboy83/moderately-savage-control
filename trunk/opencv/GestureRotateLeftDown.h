#pragma once

#include "SpringGesture.h"

class GestureRotateLeftDown : public SpringGesture {
	public:
		GestureRotateLeftDown(float distanceTolerance=Dd,
			unsigned int irrelevantTolerance=TOLERANCE_IRRELEVANT,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
			unsigned int movementLength=MOVEMENT_LENGTH_Y/2, ColourToTrack* primary=NULL, ColourToTrack* secondary=NULL);
		~GestureRotateLeftDown();
		virtual string getType() { return "LEFT o DOWN"; }
	protected:
};