#pragma once

#include "AsynchronousCompoundGesture.h"
#include "GestureRegressiveDown.h"

class GestureScurry: public AsynchronousCompoundGesture {
	public:
		GestureScurry(unsigned int detectionsRequired=1,
				unsigned int irrelevantTolerance=TOLERANCE_IRRELEVANT,
				unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
				unsigned int Length_Y=MOVEMENT_LENGTH_Y/2,
				ColourToTrack* primary=NULL, ColourToTrack* secondary=NULL);
		~GestureScurry();
		virtual string getType() { return "SCURRY"; }
};