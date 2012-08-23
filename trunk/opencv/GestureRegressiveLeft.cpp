#include "GestureRegressiveLeft.h"

GestureRegressiveLeft :: GestureRegressiveLeft(unsigned int levelOfStrictness,
	unsigned int irrelevantTolerance, unsigned int lostTolerance, unsigned int stillTolerance,
			unsigned int Length_X,	ColourToTrack* primary):
GestureSequence(levelOfStrictness,irrelevantTolerance,lostTolerance,stillTolerance)
{
	colours[0]=primary;
	regression[0]=new GestureLeft(levelOfStrictness, lostTolerance, stillTolerance,Length_X,primary);
	regression[1]=new GestureRight(levelOfStrictness,	lostTolerance, stillTolerance,Length_X,primary);

}

GestureRegressiveLeft::~GestureRegressiveLeft()
{
	delete regression[0];
	delete regression[1];
}
	