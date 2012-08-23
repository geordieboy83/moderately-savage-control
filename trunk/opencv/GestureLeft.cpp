#include "GestureLeft.h"

GestureLeft::GestureLeft(unsigned int levelOfStrictness,
	unsigned int lostTolerance, unsigned int stillTolerance,
	unsigned int Length_X, ColourToTrack* primary): 
BasicGesture(LEFT, levelOfStrictness,
	lostTolerance, stillTolerance, Length_X, MOVEMENT_LENGTH_Y, primary)
{
}

bool GestureLeft::validLiberalMovement(unsigned int movement)
{
	if(movement==W||movement==We||
		movement==NW||movement==NWe||
		movement==SW||movement==SWe)
		return true;
	return false;
}

bool GestureLeft::validAverageMovement(unsigned int movement)
{ 
	if(movement==W||movement==We) return true;
	return false; 
}

bool GestureLeft::validStrictMovement(unsigned int movement)
{
	if(movement==W) return true;
	return false; 
}

