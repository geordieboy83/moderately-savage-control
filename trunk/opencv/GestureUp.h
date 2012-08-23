#pragma once

#include "BasicGesture.h"

class GestureUp : public BasicGesture {
	public:
		GestureUp(unsigned int levelOfStrictness=GESTURE_LIBERAL,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
			unsigned int Length_Y=MOVEMENT_LENGTH_Y, ColourToTrack* primary=NULL);
		~GestureUp() {}		
	protected:
		virtual bool validLiberalMovement(unsigned int movement);
		virtual bool validAverageMovement(unsigned int movement);
		virtual bool validStrictMovement(unsigned int movement);
		virtual bool endCondition() { return counter==Ly; }
};