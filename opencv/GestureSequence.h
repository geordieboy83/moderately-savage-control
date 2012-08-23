#pragma once

#include "SimpleGestures.h"

#define TOLERANCE_IRRELEVANT 2

class GestureSequence : public BasicGesture {
	public:
		GestureSequence(unsigned int levelOfStrictness=GESTURE_AVERAGE,
			unsigned int irrelevantTolerance=TOLERANCE_IRRELEVANT,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,
			BasicGesture *first=NULL, BasicGesture* second=NULL);		
		~GestureSequence();
		void setPrimaryGesture(BasicGesture* G) { regression[0]=G; }
		void setSecondaryGesture(BasicGesture* G) { regression[1]=G; }
		string getType();

		virtual void update();
		virtual void reset() {	BasicGesture::reset(); if(regression[0]) regression[0]->reset(); if(regression[1]) regression[1]->reset(); counterIRRELEVANT=0;	}
		virtual void setColour(ColourToTrack* c, unsigned int index) { BasicGesture::setColour(c,index); regression[0]->setColour(c,index); regression[1]->setColour(c,index); }
	protected:
		unsigned int toleranceIrrelevant, counterIRRELEVANT;
		BasicGesture* regression[2];
		virtual bool validLiberalMovement(unsigned int movement) { return false; }
		virtual bool validAverageMovement(unsigned int movement) { return false; }
		virtual bool validStrictMovement(unsigned int movement) { return false; }
		virtual bool endCondition() { return true; }
};