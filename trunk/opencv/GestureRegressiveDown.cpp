#include "GestureRegressiveDown.h"

GestureRegressiveDown :: GestureRegressiveDown(unsigned int levelOfStrictness,
	unsigned int irrelevantTolerance, unsigned int lostTolerance, unsigned int stillTolerance,
			unsigned int Length_Y,	ColourToTrack* primary):
GestureSequence(levelOfStrictness,irrelevantTolerance,lostTolerance,stillTolerance)
{
	colours[0]=primary;
	regression[0]=new GestureDown(levelOfStrictness, lostTolerance, stillTolerance,Length_Y,primary);
	regression[1]=new GestureUp(levelOfStrictness,	lostTolerance, stillTolerance,Length_Y,primary);

}

GestureRegressiveDown::~GestureRegressiveDown()
{
	delete regression[0];
	delete regression[1];
}
	