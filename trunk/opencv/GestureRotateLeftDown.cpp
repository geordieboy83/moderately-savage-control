#include "GestureRotateLeftDown.h"

GestureRotateLeftDown::GestureRotateLeftDown(float distanceTolerance,
			unsigned int irrelevantTolerance,
			unsigned int lostTolerance, unsigned int stillTolerance,
			unsigned int movementLength, ColourToTrack* primary, ColourToTrack* secondary):
SpringGesture(distanceTolerance,irrelevantTolerance)
{
	regression[0]=new GestureLeft(GESTURE_LIBERAL,lostTolerance,stillTolerance,movementLength,primary);
	regression[1]=new GestureDown(GESTURE_LIBERAL,lostTolerance,stillTolerance,movementLength,secondary);

}

GestureRotateLeftDown::~GestureRotateLeftDown()
{
	delete regression[0];
	delete regression[1];
}