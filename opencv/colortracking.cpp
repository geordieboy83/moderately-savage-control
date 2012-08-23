/*
 * Adapted from code written by Lya (GeckoGeek.fr)
 */
#include <Windows.h>

#include "ColourTracker.h"
 
#include <iostream>
#include <stdlib.h>
#include <stdio.h>



ColourTracker colourdb;
IplImage *image;

bool hidden=false;

void getObjectColor(int event, int x, int y, int flags, void *param = NULL) {
 
	if(colourdb.getColours()>=2) return;

	if(event == CV_EVENT_LBUTTONUP)	{
		colourdb.addColour(image,x,y);
		return;
	} 
}

CvFont font;
int main()
{
	
    cvInitFont(&font, CV_FONT_HERSHEY_SCRIPT_COMPLEX, 0.5, 0.5, 0, 1, CV_AA);
    
	// Video Capture
	CvCapture *capture;
	// Key for keyboard event
	char key='a';
 
	// Initialize the video Capture (200 => CV_CAP_V4L2)
	capture = cvCreateCameraCapture(0);
 
	// Check if the capture is ok
    	if (!capture) {
		printf("Can't initialize the video capture.\n");
        	return -1;
 	}
 
	cout << "While the camera window is in focus, press" << endl;
	cout << "1 to 4 for basic swipe detection (at least one colour must have been selected)" << endl;
	cout << "5 to 7 for compound gesture detection (both colours must have been selected)" << endl;
	cout << "R to draw selected colour routes" << endl;

	// Create the windows
   	cvNamedWindow("GeckoGeek Color Tracking", CV_WINDOW_NORMAL);
	cvSetWindowProperty("GeckoGeek Color Tracking",CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);
	 
	// Mouse event to select the tracked color on the original image
	cvSetMouseCallback("GeckoGeek Color Tracking", getObjectColor);
 
	// While we don't want to quit
	while(key != 27) {
 
		
		// We get the current image
		image = cvQueryFrame(capture);
 
		// If there is no image, we exit the loop
		if(!image)
			continue;
 
		cvFlip(image, NULL, 1);
		colourdb.pinpointAll(image);
		colourdb.showAllMasks();
		colourdb.drawAllRoutes(image);

		if(colourdb.getColours()>0){
			CvPoint p=colourdb.getColour(0);
			int nx=((65536*1.1*p.x)/image->width)-65536*0.05;
			int ny=((65536*1.1*p.y)/image->height)-65536*0.05;
			//cout << "Normalised coordinates: " <<nx<<", "<<ny<<endl;
			if(p.x>0&&p.y>0) mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, nx, ny, 0, NULL);
		}
 
		// We wait 10 ms
		key = cvWaitKey(10);

		//This will trigger the drawing of the tracked colour movements
		if(key=='r'||key=='R'){
			colourdb.triggerRecording();
			cout << "Recording: "<< colourdb.isRecording() << endl;
		}
		else if (key>='1'&&key<='7'){
			cout << "ACTIVE: " << (int)(key-'1') << endl;
			colourdb.setActive((int)(key-'1'));
		}
		else if(key=='h'||key=='H'){
			hidden=!hidden;
			ShowWindow( GetConsoleWindow(), hidden?SW_HIDE:SW_SHOW ); 
		}
		
		cvShowImage("GeckoGeek Color Tracking",image); 
	}
 
	// Destroy the capture
	cvReleaseCapture(&capture);

	return 0;
 
}