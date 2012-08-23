#include "BasicGesture.h"

BasicGesture::BasicGesture(unsigned int gestureType, unsigned int levelOfStrictness,
	unsigned int lostTolerance, unsigned int stillTolerance,
	unsigned int Length_X, unsigned int Length_Y, ColourToTrack* primary
	):
colours(vector<ColourToTrack*>(1,primary)), firstAppearance(vector<CvPoint>(1,cvPoint(-1,-1))),lastAppearance(vector<CvPoint>(1,cvPoint(-1,-1))),
counter(0),counterSTILL(0),counterLOST(0),
currentState(LOST),detected(0),
	strictness(levelOfStrictness),Lx(Length_X), Ly(Length_Y),
	steps(1),
	toleranceStill(stillTolerance), toleranceLost(lostTolerance),lastMovement(LOST)
{
	if(gestureType<FIRST_SIMPLE_GESTURE) gestureType=FIRST_SIMPLE_GESTURE;
	else if(gestureType>LAST_SIMPLE_GESTURE) gestureType=LAST_SIMPLE_GESTURE;
	type=gestureType;
	reset();
}

string BasicGesture::getType()
{
	switch(type){
		case RIGHT: return("RIGHT");
		case LEFT: return("LEFT");
		case UP: return("UP");
		case DOWN: return("DOWN");
		case CLENCH: return("CLENCH");
		case UNCLENCH: return("UNCLENCH");
		case ROTATE: return("ROTATE");
		case SCURRY: return("SCURRY");
	}
}

string BasicGesture::getStateString()
{
	char state[40]="";
	switch(currentState){
		case GESTURE_LOST: return("LOST");
		case GESTURE_START: return("START");
		case GESTURE_STEP_1: sprintf(state,"STEP 1 of %d, %d", (int)steps, (int)counter); return(state);
		case GESTURE_STEP_2: sprintf(state,"STEP 2 of %d, %d", (int)steps, (int)counter); return(state);
		case GESTURE_STEP_3: sprintf(state,"STEP 3 of %d, %d", (int)steps, (int)counter); return(state);
		case GESTURE_STEP_4: sprintf(state,"STEP 4 of %d, %d", (int)steps, (int)counter); return(state);
		case GESTURE_STEP_5: sprintf(state,"STEP 5 of %d, %d", (int)steps, (int)counter); return(state);
		case GESTURE_STEP_6: sprintf(state,"STEP 6 of %d, %d", (int)steps, (int)counter); return(state);
		case GESTURE_STEP_7: sprintf(state,"STEP 7 of %d, %d", (int)steps, (int)counter); return(state);
		case GESTURE_STEP_8: sprintf(state,"STEP 8 of %d, %d", (int)steps, (int)counter); return(state);
		case GESTURE_END: return("END");
	}
}

bool BasicGesture::opposite(unsigned int movement1, unsigned int movement2)
{
	if(((movement1==N||movement1==Ne)&&(movement2==S||movement2==Se))||
		((movement1==S||movement1==Se)&&(movement2==N||movement2==Ne))) return true;
	if(((movement1==E||movement1==Ee)&&(movement2==W||movement2==We))||
		((movement1==W||movement1==We)&&(movement2==E||movement2==Ee))) return true;
	if(((movement1==NW||movement1==NWe)&&(movement2==SE||movement2==SEe))||
		((movement1==SE||movement1==SEe)&&(movement2==NW||movement2==NWe))) return true;
	if(((movement1==NE||movement1==NEe)&&(movement2==SW||movement2==SWe))||
		((movement1==SW||movement1==SWe)&&(movement2==NE||movement2==NEe))) return true;
	return false;
}

bool BasicGesture::same(unsigned int movement1, unsigned int movement2)
{
	if(((movement1==N||movement1==Ne)&&(movement2==N||movement2==Ne))||
		((movement1==S||movement1==Se)&&(movement2==S||movement2==Se))) return true;
	if(((movement1==E||movement1==Ee)&&(movement2==E||movement2==Ee))||
		((movement1==W||movement1==We)&&(movement2==W||movement2==We))) return true;
	if(((movement1==NW||movement1==NWe)&&(movement2==NW||movement2==NWe))||
		((movement1==SW||movement1==SWe)&&(movement2==SW||movement2==SWe))) return true;
	if(((movement1==NE||movement1==NEe)&&(movement2==NW||movement2==NWe))||
		((movement1==SE||movement1==SEe)&&(movement2==SE||movement2==SEe))) return true;
	if(((movement1==STILL||movement1==STILLe)&&(movement2==STILL||movement2==STILLe))) return true;
	return false;
}

bool BasicGesture::horizontal(unsigned int movement)
{
	if(movement==E||movement==Ee||movement==W||movement==We) return true;
	else return false;
}

bool BasicGesture::vertical(unsigned int movement)
{
	if(movement==N||movement==Ne||movement==S||movement==Se) return true;
	else return false;
}

void BasicGesture::update()
{
	if(!colours[0]) return;
	switch(strictness){
		case GESTURE_AVERAGE:
			updateAverage();
			break;
		case GESTURE_LIBERAL:
			updateLiberal();
			break;
		default:
			updateStrict();
			break;
	}
	lastAppearance[0]=colours[0]->getPosition();
}


void BasicGesture::updateAverage()
{
	lastMovement=colours[0]->getTolerantMovement();

	if(currentState==GESTURE_STEP_1){
		if(validAverageMovement(lastMovement)){
			counter++;
			if(endCondition()){
				counter=0;
				counterSTILL=0;
				counterLOST=0;
				currentState=GESTURE_END;
				detected++;
			}
		}
		else switch(lastMovement){
			case STILL: case STILLe:
				counterSTILL++;
				if(counterSTILL==toleranceStill){
					counter=0;
					counterSTILL=0;
					counterLOST=0;
					currentState=GESTURE_START;
				}
				return;
			case LOST:
				counterLOST++;
				if(counterLOST==toleranceLost){
					counter=0;
					counterSTILL=0;
					counterLOST=0;
					currentState=GESTURE_START;
				}
				return;
			default: 
				counter=0;
				counterSTILL=0;
				counterLOST=0;
				currentState=GESTURE_START;
				return;
		}
	}

	if(currentState==GESTURE_START){
		if(validAverageMovement(lastMovement)){
			currentState=GESTURE_STEP_1;
			counter++;
		}
		return;
	}
}

void BasicGesture::updateLiberal()
{
	lastMovement=colours[0]->getTolerantMovement();

	if(currentState==GESTURE_STEP_1){
		if(validLiberalMovement(lastMovement)){
			counter++;
			if(endCondition()){
				counter=0;
				counterSTILL=0;
				counterLOST=0;
				currentState=GESTURE_END;
				detected++;
			}
		}
		else switch(lastMovement){
			case STILL: case STILLe:
				counterSTILL++;
				if(counterSTILL==toleranceStill){
					counter=0;
					counterSTILL=0;
					counterLOST=0;
					currentState=GESTURE_START;
				}
				return;
			case LOST:
				counterLOST++;
				if(counterLOST==toleranceLost){
					counter=0;
					counterSTILL=0;
					counterLOST=0;
					currentState=GESTURE_START;
				}
				return;
			default: 
				counter=0;				
				counterSTILL=0;
				counterLOST=0;
				currentState=GESTURE_START;
				return;
		}
	}

	if(currentState==GESTURE_START){
		if(validLiberalMovement(lastMovement)){
			currentState=GESTURE_STEP_1;
			counter++;
		}
		return;
	}
}

void BasicGesture::updateStrict()
{
	lastMovement=colours[0]->getIntolerantMovement();

	if(currentState==GESTURE_STEP_1){
		if(validStrictMovement(lastMovement)){
			counter++;
			if(endCondition()){
				counter=0;
				counterSTILL=0;
				counterLOST=0;
				currentState=GESTURE_END;
				detected++;
			}
		}
		else switch(lastMovement){
			case STILL: case STILLe:
				counterSTILL++;
				if(counterSTILL==toleranceStill){
					counter=0;
					counterSTILL=0;
					counterLOST=0;
					currentState=GESTURE_START;
				}
				return;
			case LOST:
				counterLOST++;
				if(counterLOST==toleranceLost){
					counter=0;
					counterSTILL=0;
					counterLOST=0;
					currentState=GESTURE_START;
				}
				return;
			default: 
				counter=0;
				counterSTILL=0;
				counterLOST=0;
				currentState=GESTURE_START;
				return;
		}
	}

	if(currentState==GESTURE_START){
		if(validStrictMovement(lastMovement)){
			currentState=GESTURE_STEP_1;
			counter++;
		}
		return;
	}
}