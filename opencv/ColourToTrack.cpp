#include "ColourToTrack.h"




/*
 * Transform the image into a two colored image, one color for the color we want to track, another color for the others colors
 * From this image, we get two datas : the number of pixel detected, and the center of gravity of these pixel
 */
CvPoint ColourToTrack::binarise(IplImage* image)
{
	int x, y;
	IplImage *hsv;
	IplConvKernel *kernel;
	int sommeX = 0, sommeY = 0;
	nbPixels = 0;
 
	if(mask==NULL) mask = cvCreateImage(cvGetSize(image), image->depth, 1);

	// Create the hsv image
	hsv = cvCloneImage(image);
	//cvCvtColor(image, hsv, CV_BGR2HSV);
	cvCvtColor(image, hsv, CV_BGR2Lab);
 
	// We create the mask
	//cvInRangeS(hsv, cvScalar(colour.hsv.h - TOLERANCE -1, colour.hsv.s - TOLERANCE, 0), cvScalar(colour.hsv.h + TOLERANCE -1, colour.hsv.s + TOLERANCE, 255), mask);
	cvInRangeS(hsv, cvScalar(0, colour.hsv.s - TOLERANCE -1, colour.hsv.v - TOLERANCE), cvScalar(255, colour.hsv.s + TOLERANCE -1, colour.hsv.v + TOLERANCE), mask);
 
	// Create kernels for the morphological operation
	kernel = cvCreateStructuringElementEx(5, 5, 2, 2, CV_SHAPE_ELLIPSE);
 
	// Morphological closing (inverse because we have white pixels on black background)
	cvDilate(mask, mask, kernel, 1);
	cvErode(mask, mask, kernel, 1);  
 
	// We go through the mask to look for the tracked object and get its gravity center
	for(x = 0; x < mask->width; x++) {
		for(y = 0; y < mask->height; y++) { 
 
			// If it's a tracked pixel, count it to the center of gravity's calcul
			if(((uchar *)(mask->imageData + y*mask->widthStep))[x] == 255) {
				sommeX += x;
				sommeY += y;
				nbPixels++;
			}
		}
	}
 
	// We release the memory of kernels
	cvReleaseStructuringElement(&kernel);
 
	// We release the memory of the hsv image
    	cvReleaseImage(&hsv);
 
	// If there is no pixel, we return a center outside the image, else we return the center of gravity
	if(nbPixels > 0)
		return cvPoint((int)(sommeX / (nbPixels)), (int)(sommeY / (nbPixels)));
	else
		return cvPoint(-1, -1);
}


/*
 * Add a circle on the video that fellow your colored object
 */
void ColourToTrack::addObjectToVideo(IplImage* image, CvPoint objectNextPos) {
 
	int objectNextStepX, objectNextStepY;
 
	// Calculate circle next position (if there is enough pixels)
	if (nbPixels > 10) {
 
		// Reset position if no pixel were found
		if (xy.x == -1 || xy.y == -1) {
			xy.x = objectNextPos.x;
			xy.y = objectNextPos.y;
		}
 
		// Move step by step the object position to the desired position
		if (abs(xy.x - objectNextPos.x) > STEP_MIN) {
			objectNextStepX = max(STEP_MIN, min(STEP_MAX, abs(xy.x - objectNextPos.x) / 2));
			xy.x += (-1) * sign(xy.x - objectNextPos.x) * objectNextStepX;
		}
		if (abs(xy.y - objectNextPos.y) > STEP_MIN) {
			objectNextStepY = max(STEP_MIN, min(STEP_MAX, abs(xy.y - objectNextPos.y) / 2));
			xy.y += (-1) * sign(xy.y - objectNextPos.y) * objectNextStepY;
		}
 
	// -1 = object isn't within the camera range
	} else {
 
		xy.x = -1;
		xy.y = -1;
 
	}
 
	// Draw an object (circle) centered on the calculated center of gravity
	if (nbPixels > 10)
		cvDrawCircle(image, xy, 15,
			//CV_RGB(colour.hsv.h,colour.hsv.s,colour.hsv.v),
			CV_RGB(colour.rgb.r,colour.rgb.g,colour.rgb.b),
			-1);
  
}
 
void ColourToTrack::pinpoint(IplImage* image)
{
	addObjectToVideo(image,binarise(image));
}

void ColourToTrack::decode()
{
	lastTolerant=movementWithTolerance(lastPosition);
	lastIntolerant=movementNoTolerance(lastPosition);
	lastPosition=xy;
}

ColourToTrack::ColourToTrack(int r, int g, int b, float tolerance):xy(CvPoint()),decoder(MovementDecoder(tolerance)),
	lastPosition(cvPoint(-1,-1)),lastTolerant(LOST), lastIntolerant(LOST)
{
	// Create the mask & initialize it to white (no color detected)
	mask = NULL;
 
	colour.rgb.r=r;
	colour.rgb.g=g;
	colour.rgb.b=b;
	
	// Get the hsv image
	IplImage* hsv = cvCreateImage(cvSize(10,10),IPL_DEPTH_8U,3);
	cvSet(hsv,cvScalar(b,g,r));
	//cvCvtColor(image, hsv, CV_BGR2HSV);
	cvCvtColor(hsv, hsv, CV_BGR2Lab);
 
	// Get the selected pixel
	CvScalar pixel = cvGet2D(hsv, 5, 5);
 
	// Change the value of the tracked color with the color of the selected pixel
	colour.hsv.h = (int)pixel.val[0];
	colour.hsv.s = (int)pixel.val[1];
	colour.hsv.v = (int)pixel.val[2];
 
	// Release the memory of the hsv image
    cvReleaseImage(&hsv);
}

ColourToTrack::ColourToTrack(IplImage* image, int x, int y, float tolerance):xy(CvPoint()),decoder(MovementDecoder(tolerance)),
	lastPosition(cvPoint(-1,-1)),lastTolerant(LOST), lastIntolerant(LOST)
{
	// Create the mask & initialize it to white (no color detected)
	mask = cvCreateImage(cvGetSize(image), image->depth, 1);
 
	CvScalar pixel=cvGet2D(image,y,x);
	colour.rgb.r=(int)pixel.val[2];
	colour.rgb.g=(int)pixel.val[1];
	colour.rgb.b=(int)pixel.val[0];
	
	// Get the hsv image
	IplImage* hsv = cvCloneImage(image);
	//cvCvtColor(image, hsv, CV_BGR2HSV);
	cvCvtColor(image, hsv, CV_BGR2Lab);
 
	// Get the selected pixel
	pixel = cvGet2D(hsv, y, x);
 
	// Change the value of the tracked color with the color of the selected pixel
	colour.hsv.h = (int)pixel.val[0];
	colour.hsv.s = (int)pixel.val[1];
	colour.hsv.v = (int)pixel.val[2];
 
	// Release the memory of the hsv image
    cvReleaseImage(&hsv);
}

ColourToTrack::~ColourToTrack()
{
	cvReleaseImage(&mask);
}