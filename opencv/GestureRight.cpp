#include "GestureRight.h"

GestureRight::GestureRight(unsigned int levelOfStrictness,
	unsigned int lostTolerance, unsigned int stillTolerance,
	unsigned int Length_X, ColourToTrack* primary): 
BasicGesture(RIGHT, levelOfStrictness,
	lostTolerance, stillTolerance, Length_X, MOVEMENT_LENGTH_Y, primary)
{
}

bool GestureRight::validLiberalMovement(unsigned int movement)
{
	if(movement==E||movement==Ee||
		movement==NE||movement==NEe||
		movement==SE||movement==SEe)
		return true;
	return false;
}

bool GestureRight::validAverageMovement(unsigned int movement)
{ 
	if(movement==E||movement==Ee) return true;
	return false; 
}

bool GestureRight::validStrictMovement(unsigned int movement)
{
	if(movement==E) return true;
	return false; 
}

