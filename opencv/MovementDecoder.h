#pragma once

#include <opencv2\opencv.hpp>
#include "Movements.h"

using namespace std;

class MovementDecoder {
	public:
		MovementDecoder(float tolerance=e);
		void printState(unsigned int state);
		static int distance(CvPoint pt1, CvPoint pt2) { if(pt1.x<0||pt1.y<0||pt2.x<0||pt2.y<0) return -1; int x=pt2.x-pt1.x, y=pt2.y-pt1.y; return x*x+y*y; }
		static int distanceVert(CvPoint pt1, CvPoint pt2) { return pt2.y-pt1.y; }
		static int distanceHor(CvPoint pt1, CvPoint pt2) { return pt2.x-pt1.x; }
		void setTolerance(float tol) { minTolerance=1-tol; maxTolerance=1+tol; }
		unsigned int movementRegular(CvPoint previous, CvPoint current);
		unsigned int movementStrict(CvPoint previous, CvPoint current);
	protected:
		float minTolerance, maxTolerance;
};