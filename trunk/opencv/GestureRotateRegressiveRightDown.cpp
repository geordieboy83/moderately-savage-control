#include "GestureRotateRegressiveRightDown.h"

GestureRotateRegressiveRightDown::GestureRotateRegressiveRightDown(ColourToTrack* primary, ColourToTrack* secondary,float distanceTolerance,
			unsigned int irrelevantTolerance,
			unsigned int lostTolerance, unsigned int stillTolerance,
			unsigned int movementLength):
GestureSequence(GESTURE_LIBERAL,irrelevantTolerance,lostTolerance,stillTolerance)
{
	colours[0]=primary;
	regression[0]=new GestureRotateRightDown(distanceTolerance,irrelevantTolerance,lostTolerance,stillTolerance,movementLength,primary,secondary);
	regression[1]=new GestureRotateLeftUp(distanceTolerance,irrelevantTolerance,lostTolerance,stillTolerance,movementLength,primary,secondary);
}