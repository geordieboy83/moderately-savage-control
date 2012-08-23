#pragma once

#include "SpringGesture.h"

class GestureJointDown : public SpringGesture {
	public:
		GestureJointDown(float distanceTolerance=Dd, 
			//unsigned int irrelevantTolerance=TOLERANCE_IRRELEVANT,
			//unsigned int detectionsRequired=1,
			
			unsigned int levelOfStrictness=GESTURE_LIBERAL,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
			unsigned int Length_Y=MOVEMENT_LENGTH_Y,
			ColourToTrack* primary=NULL, ColourToTrack* secondary=NULL
			);
		~GestureJointDown();
		virtual string getType() { return "JOINT DOWN"; }
	protected:
};