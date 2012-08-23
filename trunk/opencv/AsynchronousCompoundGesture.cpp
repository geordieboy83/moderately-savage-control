#include "AsynchronousCompoundGesture.h"

string AsynchronousCompoundGesture::getType()
{
	if(!regression[0]||!regression[1]) return "EMPTY COMPOUND";
	else return regression[0]->getType() + " & " + regression[1]->getType();
}


AsynchronousCompoundGesture::AsynchronousCompoundGesture(unsigned int levelOfStrictness,
			unsigned int irrelevantTolerance,
			unsigned int lostTolerance, unsigned int stillTolerance,
			unsigned int detectionsRequired,
			BasicGesture *first, BasicGesture* second):
GestureSequence(levelOfStrictness,irrelevantTolerance,lostTolerance,stillTolerance)
{
	regression[0]=first;
	regression[1]=second;
	steps=detectionsRequired;
	reset();
}

bool AsynchronousCompoundGesture::endCondition()
{
	return (regression[0]->timesDetected()>0 && regression[1]->timesDetected()>0);
}

bool AsynchronousCompoundGesture::resetCondition()
{
	return (abs((int)regression[0]->timesDetected()-(int)regression[1]->timesDetected())>toleranceIrrelevant);
}

void AsynchronousCompoundGesture::update()
{
	if(!regression[0]||!regression[1]) return;
	
	regression[0]->update();
	regression[1]->update();

	if(endCondition()) {
		counter++;
		for(int i=0;i<2;i++) {
			regression[i]->reset();
			regression[i]->zero();
		}
		if(counter==steps){
			currentState=GESTURE_END;
			detected++;
			counter=0;		
		}
	}
	else if (resetCondition()){
		currentState=GESTURE_START;
		counter=0;
		for(int i=0;i<2;i++) {
			regression[i]->reset();
			regression[i]->zero();
		}
	}
	for(int i=0;i<2;i++) if(regression[i]->getState()==GESTURE_END) regression[i]->reset();
	if(currentState!=GESTURE_END) currentState=(bool)(max(regression[0]->getState(),regression[1]->getState()));	
}
