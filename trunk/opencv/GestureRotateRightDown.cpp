#include "GestureRotateRightDown.h"

GestureRotateRightDown::GestureRotateRightDown(float distanceTolerance,
			unsigned int irrelevantTolerance,
			unsigned int lostTolerance, unsigned int stillTolerance,
			unsigned int movementLength, ColourToTrack* primary, ColourToTrack* secondary):
SpringGesture(distanceTolerance,irrelevantTolerance)
{
	regression[0]=new GestureRight(GESTURE_LIBERAL,lostTolerance,stillTolerance,movementLength,primary);
	regression[1]=new GestureDown(GESTURE_LIBERAL,lostTolerance,stillTolerance,movementLength,secondary);

}

GestureRotateRightDown::~GestureRotateRightDown()
{
	delete regression[0];
	delete regression[1];
}