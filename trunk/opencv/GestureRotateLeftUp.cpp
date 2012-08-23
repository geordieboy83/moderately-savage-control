#include "GestureRotateLeftUp.h"

GestureRotateLeftUp::GestureRotateLeftUp(float distanceTolerance,
			unsigned int irrelevantTolerance,
			unsigned int lostTolerance, unsigned int stillTolerance,
			unsigned int movementLength, ColourToTrack* primary, ColourToTrack* secondary):
SpringGesture(distanceTolerance,irrelevantTolerance)
{
	regression[0]=new GestureLeft(GESTURE_LIBERAL,lostTolerance,stillTolerance,movementLength,primary);
	regression[1]=new GestureUp(GESTURE_LIBERAL,lostTolerance,stillTolerance,movementLength,secondary);

}

GestureRotateLeftUp::~GestureRotateLeftUp()
{
	delete regression[0];
	delete regression[1];
}