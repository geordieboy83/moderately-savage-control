#pragma once

#include "BasicGesture.h"

class GestureRight : public BasicGesture {
	public:
		GestureRight(unsigned int levelOfStrictness=GESTURE_AVERAGE,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
			unsigned int Length_X=MOVEMENT_LENGTH_X, ColourToTrack* primary=NULL);
		~GestureRight() {}		
	protected:
		virtual bool validLiberalMovement(unsigned int movement);
		virtual bool validAverageMovement(unsigned int movement);
		virtual bool validStrictMovement(unsigned int movement);
		virtual bool endCondition() { return counter==Lx; }
};