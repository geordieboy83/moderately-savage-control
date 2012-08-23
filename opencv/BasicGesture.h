#pragma once

#include "ColourToTrack.h"
#include <string>

using namespace std;

#define GESTURE_LOST -1
#define GESTURE_START 0
#define GESTURE_STEP_1 1 
#define GESTURE_STEP_2 2
#define GESTURE_STEP_3 3
#define GESTURE_STEP_4 4
#define GESTURE_STEP_5 5
#define GESTURE_STEP_6 6
#define GESTURE_STEP_7 7
#define GESTURE_STEP_8 8
#define GESTURE_END 9

#define MOVEMENT_LENGTH_X 10
#define MOVEMENT_LENGTH_Y 10

#define TOLERANCE_LOST 5
#define TOLERANCE_STILL 5

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3
#define CLENCH 4
#define UNCLENCH 5
#define ROTATE 6
#define SCURRY 7
#define GENERIC 8

#define FIRST_GESTURE RIGHT
#define LAST_GESTURE SCURRY
#define FIRST_SIMPLE_GESTURE RIGHT
#define LAST_SIMPLE_GESTURE DOWN
#define FIRST_COMPOUND_GESTURE CLENCH
#define LAST_COMPOUND_GESTURE SCURRY

#define GESTURE_LIBERAL 0
#define GESTURE_AVERAGE 1
#define GESTURE_STRICT 2

class BasicGesture {
	public:
		BasicGesture(unsigned int gestureType, unsigned int levelOfStrictness=GESTURE_AVERAGE,
			unsigned int lostTolerance=TOLERANCE_LOST, unsigned int stillTolerance=TOLERANCE_STILL,			
			unsigned int Length_X=MOVEMENT_LENGTH_X, unsigned int Length_Y=MOVEMENT_LENGTH_Y,
			ColourToTrack* primary=NULL);
		~BasicGesture() {}
		virtual void update();
		virtual void reset() { currentState=GESTURE_START; counter=0; counterSTILL=0; counterLOST=0; }
		virtual string getType();
		unsigned int getState() { return currentState; }
		string getStateString();
		virtual void setColour(ColourToTrack* c, unsigned int index) { if(index>=colours.size()) colours.push_back(c); else colours[index]=c; }
		bool opposite(unsigned int movement1, unsigned int movement2);
		bool same(unsigned int movement1, unsigned int movement2);
		bool horizontal(unsigned int movement);
		bool vertical(unsigned int movement);
		bool stillness(unsigned int movement) { if(movement==STILL||movement==STILLe) return true; else return false; }
		unsigned int timesDetected() { return detected; }
		bool movementDetected() { return (detected>0&&currentState==GESTURE_END); }
		unsigned int getToleranceOfLost() { return toleranceLost; }
		unsigned int getToleranceOfStill() { return toleranceStill; }
		void setToleranceOfLost(unsigned int tolerance) { toleranceLost=tolerance; }
		void setToleranceOfStill(unsigned int tolerance) { toleranceStill=tolerance; }
		unsigned int getCounterOfLost() { return counterLOST; }
		unsigned int getCounterOfStill() { return counterSTILL; }
		unsigned int getLastMovement() { return lastMovement; }
		ColourToTrack* getColour(unsigned int index) { if(index>(colours.size()-1)) return NULL; else return colours[index]; }
		void zero() { detected=0; }
	protected:
		unsigned int strictness;
		unsigned int type;
		unsigned int steps;
		unsigned int currentState;
		unsigned int counter, counterSTILL, counterLOST;
		unsigned int toleranceStill, toleranceLost;
		unsigned int lastMovement;
		vector<ColourToTrack*> colours;
		vector<CvPoint> firstAppearance, lastAppearance;
		unsigned int Lx, Ly;
		unsigned int detected;
		virtual void updateLiberal();
		virtual void updateAverage();
		virtual void updateStrict();
		virtual bool validLiberalMovement(unsigned int movement) =0;
		virtual bool validAverageMovement(unsigned int movement) =0;
		virtual bool validStrictMovement(unsigned int movement) =0;
		virtual bool endCondition() =0;
};