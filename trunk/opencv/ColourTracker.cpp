#include "ColourTracker.h"

extern CvFont font;

bool ColourTracker::sample()
{
	clock_t now=clock();
	if(((now-lastProcess)*1000/(float)CLOCKS_PER_SEC)>=msPerFrame){
		lastProcess=now;
		return true;
	}
	else {
		return false;
	}
}

ColourTracker::ColourTracker(int maxFPS):colours(vector<ColourToTrack*>()), colourwindows(vector<string>()), tracks(vector<ColourRoute>()),
	lastProcess(clock()),msPerFrame(1000/(float)maxFPS),recording(false), active(-1)
{
	cvNamedWindow("All Routes", CV_WINDOW_AUTOSIZE);		
}

ColourTracker::~ColourTracker()
{
	for(int i=0; i<colours.size(); i++){
		delete colours[i];
		cvDestroyWindow(colourwindows[i].c_str());
	}
	cvDestroyWindow("All Routes");
	for(int i=0; i<gesturesToDetect.size(); i++) {
		delete gesturesToDetect[i];
	}
}

void ColourTracker::showAllMasks()
{
	for(int i=0; i<colours.size(); i++){		
		IplImage* testrgb=cvCreateImage(cvGetSize(colours[i]->getMask()),IPL_DEPTH_8U, 3);
		cvCvtColor(colours[i]->getMask(),testrgb,CV_BayerBG2RGB);
		cvShowImage(colourwindows[i].c_str(), testrgb);
		cvReleaseImage(&testrgb);
	}
}

void ColourTracker::showOneMask(int index)
{
	if(index<0||index>=colours.size()) return;
	cvShowImage(colourwindows[index].c_str(), colours[index]->getMask());	
}

void ColourTracker::addColour(IplImage* image, int x, int y)
{
	//colours.push_back(new ColourToTrack(image,x,y));
	CvScalar pixel=cvGet2D(image,y,x);
	colours.push_back(new ColourToTrack((int)pixel.val[2],(int)pixel.val[1],(int)pixel.val[0]));
	
	char windowname[WINDOW_NAME_LENGTH];

	if(colours.size()==1){
		gesturesToDetect.push_back(new GestureRight());
		gesturesToDetect.push_back(new GestureLeft());
		gesturesToDetect.push_back(new GestureDown());
		gesturesToDetect.push_back(new GestureUp());
		for(int i=0; i<gesturesToDetect.size(); i++) gesturesToDetect[i]->setColour(colours.back(),0);
	}

	if(colours.size()==2) {
		//vector<BasicGesture*> v;
		/*gesturesToDetect.push_back(new SpringGesture());
		v.push_back(new GestureDown(GESTURE_LIBERAL,5,5,5,colours[0]));
		((SpringGesture*)gesturesToDetect.back())->setPrimaryGesture(v.back());
		v.push_back(new GestureDown(GESTURE_LIBERAL,5,5,5,colours[1]));
		((SpringGesture*)gesturesToDetect.back())->setSecondaryGesture(v.back());*/
		
	/*	gesturesToDetect.push_back(new GestureJointDown());
		((GestureJointDown*)gesturesToDetect.back())->setPrimaryColour(colours[0]);
		((GestureJointDown*)gesturesToDetect.back())->setSecondaryColour(colours[1]); */

		/*gesturesToDetect.push_back(new GestureJointUp());
		((GestureJointUp*)gesturesToDetect.back())->setPrimaryColour(colours[0]);
		((GestureJointUp*)gesturesToDetect.back())->setSecondaryColour(colours[1]);*/
		
		/*gesturesToDetect.push_back(new SpringGesture());
		v.push_back(new GestureUp(GESTURE_LIBERAL,5,5,5,colours[0]));
		((SpringGesture*)gesturesToDetect.back())->setPrimaryGesture(v.back());
		v.push_back(new GestureUp(GESTURE_LIBERAL,5,5,5,colours[1]));
		((SpringGesture*)gesturesToDetect.back())->setSecondaryGesture(v.back());*/

		/*gesturesToDetect.push_back(new SpringGesture());
		v.push_back(new GestureRight(GESTURE_LIBERAL,5,5,5,colours[0]));
		((SpringGesture*)gesturesToDetect.back())->setPrimaryGesture(v.back());
		v.push_back(new GestureDown(GESTURE_LIBERAL,5,5,5,colours[1]));
		((SpringGesture*)gesturesToDetect.back())->setSecondaryGesture(v.back());*/


		gesturesToDetect.push_back(new GestureRotateRightDown());
		((GestureRotateRightDown*)gesturesToDetect.back())->setPrimaryColour(colours[0]);
		((GestureRotateRightDown*)gesturesToDetect.back())->setSecondaryColour(colours[1]);

		/*gesturesToDetect.push_back(new SpringGesture());
		v.push_back(new GestureRight(GESTURE_LIBERAL,5,5,5,colours[0]));
		((SpringGesture*)gesturesToDetect.back())->setPrimaryGesture(v.back());
		v.push_back(new GestureDown(GESTURE_LIBERAL,5,5,5,colours[1]));
		((SpringGesture*)gesturesToDetect.back())->setSecondaryGesture(v.back());*/

		gesturesToDetect.push_back(new GestureRotateLeftUp());
		((GestureRotateLeftUp*)gesturesToDetect.back())->setPrimaryColour(colours[0]);
		((GestureRotateLeftUp*)gesturesToDetect.back())->setSecondaryColour(colours[1]);


		/*gesturesToDetect.push_back(new SpringGesture());
		v.push_back(new GestureLeft(GESTURE_LIBERAL,5,5,5,colours[0]));
		((SpringGesture*)gesturesToDetect.back())->setPrimaryGesture(v.back());
		v.push_back(new GestureUp(GESTURE_LIBERAL,5,5,5,colours[1]));
		((SpringGesture*)gesturesToDetect.back())->setSecondaryGesture(v.back());*/

		/*gesturesToDetect.push_back(new SpringGesture());
		v.push_back(new GestureRegressiveRight(GESTURE_LIBERAL,2,5,5,5,colours[0]));
		((SpringGesture*)gesturesToDetect.back())->setPrimaryGesture(v.back());
		v.push_back(new GestureRegressiveDown(GESTURE_LIBERAL,2,5,5,5,colours[1]));
		((SpringGesture*)gesturesToDetect.back())->setSecondaryGesture(v.back());*/
		
	/*	gesturesToDetect.push_back(new GestureScurry());
		((GestureScurry*)gesturesToDetect.back())->setPrimaryColour(colours[0]);
		((GestureScurry*)gesturesToDetect.back())->setSecondaryColour(colours[1]); */

		/*gesturesToDetect.push_back(new GestureSequence(GESTURE_LIBERAL,2,5,5,gesturesToDetect[4], gesturesToDetect[5]));
		gesturesToDetect.back()->setColour(colours[0],0);*/
		gesturesToDetect.push_back(new GestureRotateRegressiveRightDown(colours[0],colours[1]));
		

		////Add component gestures to database so we can delete them.
		//for(int i=0; i<v.size(); i++) gesturesToDetect.push_back(v[i]);
	}
	
	sprintf(windowname,"Mask %d",colours.size());
	colourwindows.push_back(windowname);
	cvNamedWindow(windowname, CV_WINDOW_AUTOSIZE);
	
	RGB rgb=colours.back()->getRGB();
	tracks.push_back(ColourRoute(image,rgb.r,rgb.g,rgb.b));
}

string detectedString;
string stateString;
void ColourTracker::pinpointAll(IplImage* image)
{
	
	for(int i=0; i<colours.size(); i++){
		colours[i]->pinpoint(image);
		if(sample()){	
				colours[i]->decode();
				
				if(active>=0&&active<=6&&active<=gesturesToDetect.size()-1){
					gesturesToDetect[active]->update();
					if(gesturesToDetect[active]->getState()==GESTURE_END) gesturesToDetect[active]->reset();
					char blah[15]="";
					sprintf(blah,"%d detected",gesturesToDetect[active]->timesDetected());
					detectedString=gesturesToDetect[active]->getType()+": "+blah;
					stateString=gesturesToDetect[active]->getStateString();
				}
				
		}
		if(recording){
			tracks[i].add(colours[i]->getPosition());
			cvAdd(image,tracks[i].getRoute(),image);
		}		
	}
	cvPutText(image,stateString.c_str(),cvPoint(5,20),&font,cvScalar(128,255,0));
	cvPutText(image,detectedString.c_str(),cvPoint(5,image->height-5),&font,cvScalar(255,0,255));
}

void ColourTracker::pinpointOne(IplImage* image, int index)
{
	if(index<0||index>=colours.size()) return;
	colours[index]->pinpoint(image);	
	if(recording) tracks[index].add(colours[index]->getPosition());		
}


void ColourTracker::drawAllRoutes(IplImage* image)
{
	IplImage* routes = cvCloneImage(image);
	cvRectangle(routes,cvPoint(0,0),cvPoint(routes->width,routes->height),CV_RGB(0,0,0),CV_FILLED);
	for(int i=0; i<colours.size(); i++){
		cvAdd(routes,tracks[i].getRoute(),routes);
	}
	cvShowImage("All Routes", routes);
	cvReleaseImage(&routes);

}
