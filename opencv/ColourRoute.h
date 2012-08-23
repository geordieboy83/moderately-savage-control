#pragma once

#include <opencv2\opencv.hpp>

using namespace std;

class ColourRoute{
	public:
		ColourRoute(IplImage* img, int r=255, int g=255, int b=255);
		~ColourRoute();
		void add(CvPoint position);
		void reset();
		IplImage* getRoute() { return &route; }
	protected:
		struct { int r; int g; int b; } colour;
		CvPoint last;
		IplImage route;
};