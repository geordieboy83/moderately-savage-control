#pragma once

#include "GestureSequence.h"

using namespace std;

class AsynchronousCompoundGesture : public GestureSequence {
	public:
		AsynchronousCompoundGesture(unsigned int levelOfStrictness=GESTURE_AVERAGE,
			unsigned int irrelevantTolerance=TOLERANCE_IRRELEVANT,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
			unsigned int detectionsRequired=1,
			BasicGesture *first=NULL, BasicGesture* second=NULL);
		~AsynchronousCompoundGesture() {}
		virtual void update();
		virtual string getType();
		virtual void setPrimaryColour(ColourToTrack* primary) { if(regression[0]) regression[0]->setColour(primary,0); }
		virtual void setSecondaryColour(ColourToTrack* secondary) { if(regression[1]) regression[1]->setColour(secondary,0); }
	protected:
		virtual bool endCondition();
		virtual bool resetCondition();
};
