#pragma once

#include "GestureSequence.h"

class GestureRegressiveLeft : public GestureSequence {
	public:
		GestureRegressiveLeft(unsigned int levelOfStrictness=GESTURE_AVERAGE,
			unsigned int irrelevantTolerance=TOLERANCE_IRRELEVANT,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
			unsigned int Length_X=MOVEMENT_LENGTH_X,
			ColourToTrack* primary=NULL);
		~GestureRegressiveLeft();
	protected:
};