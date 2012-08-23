#include "GestureDown.h"

GestureDown::GestureDown(unsigned int levelOfStrictness,
	unsigned int lostTolerance, unsigned int stillTolerance,
	unsigned int Length_Y, ColourToTrack* primary): 
BasicGesture(DOWN, levelOfStrictness,
	lostTolerance, stillTolerance, MOVEMENT_LENGTH_X, Length_Y, primary)
{
}

bool GestureDown::validLiberalMovement(unsigned int movement)
{
	if(movement==S||movement==Se||
		movement==SW||movement==SWe||
		movement==SE||movement==SEe)
		return true;
	return false;
}

bool GestureDown::validAverageMovement(unsigned int movement)
{ 
	if(movement==S||movement==Se) return true;
	return false; 
}

bool GestureDown::validStrictMovement(unsigned int movement)
{
	if(movement==S) return true;
	return false; 
}

