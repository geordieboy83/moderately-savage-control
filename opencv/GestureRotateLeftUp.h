#pragma once

#include "SpringGesture.h"

class GestureRotateLeftUp : public SpringGesture {
	public:
		GestureRotateLeftUp(float distanceTolerance=Dd,
			unsigned int irrelevantTolerance=TOLERANCE_IRRELEVANT,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
			unsigned int movementLength=MOVEMENT_LENGTH_Y/2, ColourToTrack* primary=NULL, ColourToTrack* secondary=NULL);
		~GestureRotateLeftUp();
		virtual string getType() { return "LEFT o UP"; }
	protected:
};