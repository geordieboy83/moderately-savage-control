/*Based on the code by Lya (Geckogeek.fr) */

#pragma once

#include <opencv2\opencv.hpp>
#include "MovementDecoder.h"

using namespace std;

// Maths methods
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))  
#define abs(x) ((x) > 0 ? (x) : -(x))
#define sign(x) ((x) > 0 ? 1 : -1)
 
// Step moving for object min & max
#define STEP_MIN 5
#define STEP_MAX 100 

//Tolerance towards colour to track
#define TOLERANCE 10

typedef union{
	struct {
		int h, s, v; 
	};
	int hsv[3];
} HSV;

typedef union{
	struct {
		int r, g, b; 
	};
	int rgb[3];
} RGB;

typedef struct{
	RGB rgb;
	HSV hsv;
} Colour;


class ColourToTrack {
	public:
		ColourToTrack(IplImage* image, int x, int y, float tolerance=e);
		ColourToTrack(int r, int g, int b, float tolerance=e);
		~ColourToTrack();
		void pinpoint(IplImage* image);
		void show(string window_id) { cvShowImage(window_id.c_str(),mask); }
		IplImage* getMask() { return mask; }
		CvPoint getPosition() { return xy; }
		HSV getHSV() { return colour.hsv; }
		RGB getRGB() { return colour.rgb; }
		void setTolerance(float newTolerance) { decoder.setTolerance(newTolerance); }
		unsigned int movementWithTolerance(CvPoint last) { return decoder.movementRegular(last,xy); } 
		unsigned int movementNoTolerance(CvPoint last) { return decoder.movementStrict(last,xy); }
		void decode();
		unsigned int getTolerantMovement() { return lastTolerant; }
		unsigned int getIntolerantMovement() { return lastIntolerant; }
	protected:
		MovementDecoder decoder;
		Colour colour;
		CvPoint xy;
		int nbPixels;
		IplImage* mask;
		CvPoint lastPosition;
		unsigned int lastTolerant;
		unsigned int lastIntolerant;
		CvPoint binarise(IplImage* image);
		void addObjectToVideo(IplImage* image, CvPoint objectNextPos);
};