/*
 * shapes.cpp
 *
 *  Created on: May 20, 2015
 *      Author: harish
 */

#include "shapes.h"
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc.hpp>

cv::Mat inputImg, afterCanny, afterContours;
std::vector<std::vector<cv::Point> > contours;
int arrowcount = 0;

shapes::shapes() {
	// TODO Auto-generated constructor stub
}

shapes::shapes(cv::Mat img) {
	inputImg = img;
	std::cout << "-> in constructor" << std::endl;
}

shapes::~shapes() {

	inputImg.deallocate();
	afterCanny.deallocate();
	afterContours.deallocate();
}

bool sortpointbyy(cv::Point a, cv::Point b) {
	return a.y < b.y;
}

bool sortpointbyx(cv::Point a, cv::Point b) {
	return a.x < b.x;
}

enum linedirection {
	horizontal, vertical, angular
};

struct lineorientation {
	linedirection d;
	double angle;
};

double angleindegrees(cv::Point p1, cv::Point p2) {
	double rad = atan2(fabs(p1.y - p2.y), fabs(p1.x - p2.x)); // radians
	std::cout << "-> angle  " << p1 << " : " << p2 << " : " << (rad * 180) / M_PI << std::endl;
	return (rad * 180) / M_PI; // convert to degree
}

lineorientation lineslope(cv::Point p1, cv::Point p2) {

	double angle = angleindegrees(p1, p2);

	lineorientation o;
	o.angle = angle;

	if (angle < 20)
		o.d = horizontal;
	else if (angle > 80 && angle < 100)
		o.d = vertical;
	else
		o.d = angular;

	return o;
}

void prepareimage()
{
	int threshold = 100;
	cv::Mat src_gray, detected_edges;

	cv::cvtColor( inputImg, src_gray, CV_BGR2GRAY );
	cv::blur( src_gray, detected_edges, cv::Size(3,3) );
	cv::Canny(detected_edges, afterCanny, threshold, threshold * 3);
	cv::findContours(afterCanny, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
	//afterContours = cv::Mat::zeros(afterCanny.size(), CV_8UC3);
}

bool isarrow(std::vector<cv::Point> approxPoly)
{
	int lineSum=0;
	cv::Point leftmost;
	std::vector<cv::Point> approxPloySorted;

	std::cout << "-> inside isArrow ..poly size " << approxPoly.size() << std::endl;

	//given a polygon, is this an arrow
	if (approxPoly.size() == 7) {
		//check if this is an arrow

		lineSum = 0;
		leftmost = approxPoly[0];
		for (uint j = 0; j < approxPoly.size(); j++) {
			if (approxPoly[j].x < leftmost.x)
				leftmost = approxPoly[j];

			if (j == (approxPoly.size() -1))
			{
				lineSum += lineslope(approxPoly[j], approxPoly[0]).d;
			}
			else
			{
				lineSum += lineslope(approxPoly[j], approxPoly[j + 1]).d;
			}
		}

		std::cout << "-> lineSum " << lineSum << std::endl;

		if (lineSum == 6 || lineSum == 7) {
			return true;
		}
	}

	return false;
}

arrowdirection getdirection(std::vector<cv::Point> approxPoly)
{
	std::vector<cv::Point> approxPloySorted;


	approxPloySorted = approxPoly;
	sort(approxPloySorted.begin(), approxPloySorted.end(), sortpointbyx);
	if (lineslope(approxPloySorted[0], approxPloySorted[1]).d == vertical)
	{
		return right;
	}
	else
	{
		return left;
	}

	return unknown;
}


//return a struct with vectors and direction
std::vector<arrow> shapes::arrows()
{
	//process the input image to find out all the arrows and return the number of arrows

	std::cout << "-> in shapes::arrows()" << std::endl;

	std::vector<arrow> a;
	arrow ar;

	// prepareImage if not prepared already
	prepareimage();

	std::cout << "-> after prepareimage()" << std::endl;

	std::vector<cv::Point> approxPoly;

	std::cout << "-> contours size " << contours.size() << std::endl;

	for (uint i = 0; i < contours.size(); i++) {
		// get approx poly
		cv::approxPolyDP(contours[i], approxPoly,3, true);

		if (isarrow(approxPoly))
		{
			ar.polygon = approxPoly;
			ar.direction = getdirection(approxPoly);
			a.push_back(ar);
		}

	}

	// return arrow count
	return a;
}
