#include "ColourRoute.h"

ColourRoute::ColourRoute(IplImage* img, int r, int g, int b):last(cvPoint(-1,-1))
{
	colour.b=b; colour.g=g; colour.r=r;
	route=*(cvCloneImage(img));	
	cvRectangle(&route,cvPoint(0,0),cvPoint(route.width,route.height),CV_RGB(0,0,0),CV_FILLED);

}

ColourRoute::~ColourRoute()
{
}

void ColourRoute::add(CvPoint position) 
{
	 if(last.x>=0&&
		 last.y>=0&&
		 position.x>=0&&
		 position.y>=0){
		 cvLine(&route,last,position,CV_RGB(colour.r,colour.g,colour.b));
	 }
	 last=position;
}

void ColourRoute::reset()
{
	cvRectangle(&route,cvPoint(0,0),cvPoint(route.width,route.height),CV_RGB(0,0,0),CV_FILLED);
	last=cvPoint(-1,-1);
}
