#include "MovementDecoder.h"

MovementDecoder::MovementDecoder(float tolerance):
minTolerance(1-tolerance), maxTolerance(1+tolerance)
{
}

unsigned int MovementDecoder::movementRegular(CvPoint previous, CvPoint current)
{
	if(current.x<0||current.y<0) return LOST;
	int x=current.x-previous.x, y=current.y-previous.y;
	float minxe=previous.x*minTolerance, maxxe=previous.x*maxTolerance,
		minye=previous.y*minTolerance, maxye=previous.y*maxTolerance;
	
	if(x==0){
		//Horizontal movement with tolerance
		if(minye<=current.y&&current.y<=maxye){ return STILLe;	}
		if(y>0) { return S; }
		if(y<0) { return N; }
		if(y==0) { return STILL; }
	}
	if(x>0) {
		//Right
		if(y==0) { return E; }
		if(minye<=current.y&&current.y<=maxye){ return Ee;	}
		if(y>0) { return SE; }
		if (y<0){ return NE; }
	}
	if (x<0) {
		//Left
		if(y==0) { return W; }
		if(minye<=current.y&&current.y<=maxye){ return We;	}
		if(y>0) { return SW; }
		if(y<0) { return NW; }
		
	}
	return LOST;
}


unsigned int MovementDecoder::movementStrict(CvPoint previous, CvPoint current)
{
	if(current.x<0||current.y<0) return LOST;
	int x=current.x-previous.x, y=current.y-previous.y;

	if(x==0){
		//Horizontal movement		
		if(y>0) { return S; }
		if(y<0) { return N; }
		if(y==0) { return STILL; }
	}
	if(x>0) {
		//Right
		if(y==0) { return E; }		
		if(y>0) { return SE; }
		if (y<0){ return NE; }
	}
	if (x<0) {
		//Left
		if(y==0) { return W; }		
		if(y>0) { return SW; }
		if(y<0) { return NW; }
		
	}
	return LOST;
}

void MovementDecoder::printState(unsigned int state)
{
	switch(state){
		case START: cout << "Start" << endl; break;
		case END : cout << "End" << endl; break;
		case LOST : cout << "Lost" << endl; break;
		case N : cout << "Up" << endl; break;
		case Ne : cout << "Up more or less" << endl; break;
		case NE : cout << "Up right" << endl; break;
		case NEe : cout << "Up right more or less" << endl; break;
		case E : cout << "Right" << endl; break;
		case Ee : cout << "Right more or less" << endl; break;
		case SE : cout << "Down right" << endl; break;
		case SEe : cout << "Down right more or less" << endl; break;
		case S : cout << "Down" << endl; break;
		case Se : cout << "Down more or less" << endl; break;
		case SW : cout << "Down left" << endl; break;
		case SWe : cout << "Down left more or less" << endl; break;
		case W : cout << "Left" << endl; break;
		case We : cout << "Left more or less" << endl; break;
		case NW : cout << "Up left" << endl; break;
		case NWe : cout << "Up left more or less" << endl; break;
		case STILL : cout << "Still" << endl; break;
		case STILLe : cout << "Still more or less" << endl; break;
		default: break;
	}
}