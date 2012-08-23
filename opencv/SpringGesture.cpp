#include "SpringGesture.h"

string SpringGesture::getType()
{
	if(!regression[0]||!regression[1]) return "EMPTY SPRING";
	else return regression[0]->getType() + " ->|<- " +regression[1]->getType();
}

SpringGesture::SpringGesture(float distanceTolerance, 
			unsigned int irrelevantTolerance,
			unsigned int detectionsRequired,
			BasicGesture *first, BasicGesture* second):
AsynchronousCompoundGesture(), toleranceDistance(distanceTolerance),lastDistance(-1)
{
	steps=detectionsRequired;
	regression[0]=first; regression[1]=second;
}

bool SpringGesture::inRange()
{
	ColourToTrack *c1=regression[0]->getColour(0), *c2=regression[1]->getColour(0);
	int distance=MovementDecoder::distance(c1->getPosition(),c2->getPosition());	
	float minD=(1-toleranceDistance)*lastDistance, maxD=(1+toleranceDistance)*lastDistance;

	//printf("this: %d, last: %d, %f <= %d <= %f\n",distance, lastDistance, minD, distance, maxD);

	lastDistance=distance;	
	return (minD<=distance&&distance<=maxD);
}

void SpringGesture::update()
{
	if(!regression[0]||!regression[1]) return;
		
	bool flag=inRange();

		

	if(!flag){
		currentState=GESTURE_START;
		counter=0;
		for(int i=0;i<2;i++) {
			regression[i]->reset();
			regression[i]->zero();
		}
		return;
	}

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