#include "GestureRegressiveRight.h"

GestureRegressiveRight :: GestureRegressiveRight(unsigned int levelOfStrictness,
	unsigned int irrelevantTolerance, unsigned int lostTolerance, unsigned int stillTolerance,
			unsigned int Length_X,	ColourToTrack* primary):
GestureSequence(levelOfStrictness,irrelevantTolerance,lostTolerance,stillTolerance)
{
	colours[0]=primary;
	regression[0]=new GestureRight(levelOfStrictness, lostTolerance, stillTolerance,Length_X,primary);
	regression[1]=new GestureLeft(levelOfStrictness,	lostTolerance, stillTolerance,Length_X,primary);

}

GestureRegressiveRight::~GestureRegressiveRight()
{
	delete regression[0];
	delete regression[1];
}
	