#pragma once

#include "SpringGesture.h"

class GestureJointUp : public SpringGesture {
	public:
		GestureJointUp(float distanceTolerance=Dd,			
			unsigned int levelOfStrictness=GESTURE_LIBERAL,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
			unsigned int Length_Y=MOVEMENT_LENGTH_Y,
			ColourToTrack* primary=NULL, ColourToTrack* secondary=NULL
			);
		~GestureJointUp();
		virtual string getType() { return "JOINT UP"; }
	protected:
};