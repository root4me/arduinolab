#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat input;
int sliderinit = 0;

bool SortPointByY(Point a, Point b) {
	return a.y < b.y;
}

bool SortPointByX(Point a, Point b) {
	return a.x < b.x;
}

enum direction {
	horizontal, vertical, angular
};

struct orientation {
	direction d;
	double angle;
};

double angleInDegree(Point p1, Point p2) {
	double rad = atan2(fabs(p1.y - p2.y), fabs(p1.x - p2.x)); // radians
	return (rad * 180) / M_PI; // convert to degree
}

orientation lineSlope(Point p1, Point p2) {

	double angle = angleInDegree(p1, p2);

	orientation o;
	o.angle = angle;

	if (angle < 20)
		o.d = horizontal;
	else if (angle > 80 && angle < 100)
		o.d = vertical;
	else
		o.d = angular;

	return o;
}

void findArrow(int pos, void* userdata) {

	Mat afterCanny, afterContours;
	vector<vector<Point> > contours;
	vector<Point> approxPoly, approxPloySorted;
	Point leftmost;
	Scalar color;
	int lineSum; // each horizontal = 0 , vertical = 1, angular = 3

	// canny
	Canny(input, afterCanny, pos, pos * 3);
	imshow("After Canny", afterCanny);
	moveWindow("After Canny", 800, 800);
	// contour
	findContours(afterCanny, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

	/// Draw contours
	afterContours = Mat::zeros(afterCanny.size(), CV_8UC3);
	color = Scalar(0, 180, 0);
	drawContours(afterContours, contours, -1, color, 1, 8);
	imshow("After Contour", afterContours);
	moveWindow("After Contour", 800, 0);

	// loop contours
	cout << "==================================" << endl;
	for (uint i = 0; i < contours.size(); i++) {

		// get approx poly
		approxPolyDP(contours[i], approxPoly, 3, true);
		if (approxPoly.size() == 7) {
			//check if this is an arrow
			//cout << "Contour " << i << " could be an arrow" << endl;

			lineSum = 0;
			leftmost = approxPoly[0];
			for (uint j = 0; j < approxPoly.size(); j++) {
				if (approxPoly[j].x < leftmost.x)
					leftmost = approxPoly[j];

				lineSum += lineSlope(approxPoly[j], approxPoly[j + 1]).d;
				//cout << "edge weight  " << lineSum << endl;
			}

			if (lineSum == 6 || lineSum == 7) {
				//cout << "Contour  " << i << " is an arrow " << endl;

				Rect bound;
				bound = boundingRect(Mat(approxPoly));
				Scalar color = Scalar(200, 200, 200);
				drawContours(afterContours, contours, i, color, 1, 4, vector<Vec4i>(), 0, Point());
				rectangle(afterContours, bound.tl(), bound.br(), color, 1, 4, 0);

				if (lineSum == 7) // left or right pointing arrow
				{
					approxPloySorted = approxPoly;
					sort(approxPloySorted.begin(), approxPloySorted.end(), SortPointByX);
					if (lineSlope(approxPloySorted[0], approxPloySorted[1]).d == vertical)
					{
						cout << "Contour  " << i << " is a Right arrow " << endl;
						putText(afterContours, "Right Arrow", bound.tl(), FONT_HERSHEY_COMPLEX, .5, Scalar(128, 128, 0), 1);
					}
					else
					{
						cout << "Contour  " << i << " is a Left arrow " << endl;
						putText(afterContours, "Left Arrow", bound.tl(), FONT_HERSHEY_COMPLEX, .5, Scalar(128, 128, 0), 1);
					}
				}
			}
		}
	}

	imshow("Arrow Marked", afterContours);
}


/** @function main */
int main(int argc, char** argv) {
	/// Load source image and convert it to gray
	input = imread(argv[1]);

	if (input.empty()) {
		cout << "-> file not found !" << endl;
		cout << "-> usage : detectarrow {file name}" << endl;
		return -1;
	}

	imshow("Input Image", input);
	moveWindow("Input Image", 0, 0);
	createTrackbar("Refine", "Input Image", &sliderinit, 255, findArrow);

	waitKey(0);
	return (0);
}
