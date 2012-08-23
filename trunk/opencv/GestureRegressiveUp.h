#pragma once

#include "GestureSequence.h"

class GestureRegressiveUp : public GestureSequence {
	public:
		GestureRegressiveUp(unsigned int levelOfStrictness=GESTURE_LIBERAL,
			unsigned int irrelevantTolerance=TOLERANCE_IRRELEVANT,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
			unsigned int Length_Y=MOVEMENT_LENGTH_Y/2,
			ColourToTrack* primary=NULL);
		~GestureRegressiveUp();
	protected:
};