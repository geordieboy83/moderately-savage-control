#include "GestureScurry.h"

GestureScurry::GestureScurry(unsigned int detectionsRequired,
				unsigned int irrelevantTolerance,
				unsigned int lostTolerance, unsigned int stillTolerance,
				unsigned int Length_Y,
				ColourToTrack* primary, ColourToTrack* secondary):
AsynchronousCompoundGesture(GESTURE_LIBERAL,irrelevantTolerance,lostTolerance,stillTolerance,detectionsRequired)
{
	type=SCURRY;
	regression[0]=new GestureRegressiveDown(GESTURE_LIBERAL,irrelevantTolerance,lostTolerance,stillTolerance,Length_Y,primary);
	regression[1]=new GestureRegressiveDown(GESTURE_LIBERAL,irrelevantTolerance,lostTolerance,stillTolerance,Length_Y,secondary);
}

GestureScurry::~GestureScurry()
{
	delete regression[0];
	delete regression[1];
}