#pragma once

#include <vector>
#include <string>
#include <time.h>
#include "ColourToTrack.h"
#include "ColourRoute.h"
#include "Gestures.h"

#define WINDOW_NAME_LENGTH 10
#define MAX_FPS 10

using namespace std;

class ColourTracker {
	public:
		ColourTracker(int maxFPS=MAX_FPS);
		~ColourTracker();
		void showAllMasks();
		void showOneMask(int index);
		void drawAllRoutes(IplImage* image);
		void addColour(IplImage* image, int x, int y);
		void pinpointAll(IplImage* image);
		void pinpointOne(IplImage* image, int index);
		int getColours() { return colours.size(); }
		CvPoint getColour(int index) { if(index<0||index>=colours.size()) return cvPoint(-1,-1); else return colours[index]->getPosition(); }
		void triggerRecording() { if(colours.size()!=0) recording=!recording; if(recording) clearRecordings(); }
		void clearRecordings() { for(int i=0; i<colours.size(); i++) tracks[i].reset(); }
		bool isRecording() { return recording; }
		void setActive(unsigned int index) { active=index; }
	protected:
		clock_t lastProcess;
		int active;
		float msPerFrame;
		bool sample();
		bool recording;
		vector<ColourToTrack*> colours;
		vector<ColourRoute> tracks;
		vector<string> colourwindows;
		vector<BasicGesture*> gesturesToDetect;
};

