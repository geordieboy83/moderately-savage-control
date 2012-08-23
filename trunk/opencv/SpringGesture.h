#pragma once

#include "AsynchronousCompoundGesture.h"

#define Dd 0.15

class SpringGesture : public AsynchronousCompoundGesture {
	public:
		SpringGesture(float distanceTolerance=Dd, 
			unsigned int irrelevantTolerance=TOLERANCE_IRRELEVANT,
			unsigned int detectionsRequired=1,
			BasicGesture *first=NULL, BasicGesture* second=NULL);
		~SpringGesture() {}
		virtual void update();
		virtual string getType();
	protected:
		int lastDistance;
		float toleranceDistance;
		virtual bool inRange();
};