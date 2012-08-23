#include "GestureJointDown.h"

GestureJointDown ::	GestureJointDown(float distanceTolerance, 
			//unsigned int irrelevantTolerance,
			//unsigned int detectionsRequired,
			
			unsigned int levelOfStrictness,
			unsigned int lostTolerance, unsigned int stillTolerance,
			unsigned int Length_Y,
			ColourToTrack* primary, ColourToTrack* secondary):
SpringGesture(distanceTolerance)
{
	regression[0]=new GestureDown(levelOfStrictness,lostTolerance,stillTolerance,Length_Y,primary);
	regression[1]=new GestureDown(levelOfStrictness,lostTolerance,stillTolerance,Length_Y,secondary);
}
		
GestureJointDown::~GestureJointDown()
{
	delete regression[0];
	delete regression[1];
}

