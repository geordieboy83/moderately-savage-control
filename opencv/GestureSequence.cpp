#include "GestureSequence.h"

string GestureSequence::getType()
{
	if(!regression[0]||!regression[1]) return "EMPTY SEQUENCE";
	else return regression[0]->getType()+ " -> " +regression[1]->getType();
	
}

GestureSequence::GestureSequence(unsigned int levelOfStrictness,
	unsigned int irrelevantTolerance,
	unsigned int lostTolerance, unsigned int stillTolerance,
	BasicGesture* first, BasicGesture* second):
BasicGesture(GENERIC, levelOfStrictness,
	lostTolerance, stillTolerance),
	toleranceIrrelevant(irrelevantTolerance),counterIRRELEVANT(0) 
{
	regression[0]=first;
	regression[1]=second;	
	steps=2;
	reset();
}


GestureSequence::~GestureSequence()
{
}

void GestureSequence::update()
{
	if(!colours[0]) return;	

	cout << detected << "| <" << counterLOST << ", "<< counterSTILL << ", " << counterIRRELEVANT << "> "
		<< getStateString() << ": 1-" << regression[0]->getStateString() << " 2-"<< regression[1]->getStateString() << endl;

	switch(currentState) {
		case GESTURE_START:
			regression[0]->update();
			if(regression[0]->getState()==GESTURE_STEP_1){
				currentState=GESTURE_STEP_1;
			}
			break;
		case GESTURE_STEP_1:
			regression[0]->update();
			switch(regression[0]->getState()){
				case GESTURE_START:
					currentState=GESTURE_START;
					break;				
				case GESTURE_END:
					currentState=GESTURE_STEP_2;
					regression[0]->reset();					
					break;
				case GESTURE_STEP_1:
					break;
			};
			break;
		case GESTURE_STEP_2:
			regression[0]->update();
			regression[1]->update();
			switch(regression[1]->getState()){
				case GESTURE_START:
					if(regression[0]->getState()==GESTURE_START){

						switch(regression[1]->getLastMovement()){
							case LOST: counterLOST++; break;
							case STILL: case STILLe: counterSTILL++; break;
							default: counterIRRELEVANT++; break;
						};
						if(counterIRRELEVANT==toleranceIrrelevant||
							counterLOST==toleranceLost||
							counterSTILL==toleranceStill){
								currentState=GESTURE_START;
								counterIRRELEVANT=0;
								counterLOST=0;
								counterSTILL=0;
						}

					} else if(regression[0]->getState()==GESTURE_END){
						regression[0]->reset();
					}					
					break;
				case GESTURE_END:
					currentState=GESTURE_END;					
					counterIRRELEVANT=0;
					counterLOST=0;
					counterSTILL=0;
					detected++;
					break;
				case GESTURE_STEP_1:					
					break;
			};
			break;
		case GESTURE_END:
			break;
		case GESTURE_LOST:
			break;
	};
	
}