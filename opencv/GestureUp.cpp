#include "GestureUp.h"

GestureUp::GestureUp(unsigned int levelOfStrictness,
	unsigned int lostTolerance, unsigned int stillTolerance,
	unsigned int Length_Y, ColourToTrack* primary): 
BasicGesture(UP, levelOfStrictness,
	lostTolerance, stillTolerance, MOVEMENT_LENGTH_X, Length_Y, primary)
{
}

bool GestureUp::validLiberalMovement(unsigned int movement)
{
	if(movement==N||movement==Ne||
		movement==NW||movement==NWe||
		movement==NE||movement==NEe)
		return true;
	return false;
}

bool GestureUp::validAverageMovement(unsigned int movement)
{ 
	if(movement==N||movement==Ne) return true;
	return false; 
}

bool GestureUp::validStrictMovement(unsigned int movement)
{
	if(movement==N) return true;
	return false; 
}

