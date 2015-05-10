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

void findArrow(int pos, void* userdata) {

	Mat afterCanny, afterContours;
	vector<vector<Point> > contours;
	vector<Point> approxPoly, approxPloySorted;
	Point leftmost;
	Scalar color;

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
			cout << "Contour " << i << " could be an arrow" << endl;

			approxPloySorted = approxPoly;

			sort(approxPloySorted.begin(), approxPloySorted.end(), SortPointByY);

			int y0 = approxPloySorted[0].y;
			int y1 = approxPloySorted[1].y;
			int y2 = approxPloySorted[2].y;
			int y3 = approxPloySorted[3].y;
			int y4 = approxPloySorted[4].y;
			int y5 = approxPloySorted[5].y;
			int y6 = approxPloySorted[6].y;

			// either left , right or up
			if (y0 != y1) {
				// either left or right
				if (((y1 == y2) || (y1 == (y2 + 3)) || (y1 == (y2 - 3))) && (!(y3 == y4))) {
					leftmost = approxPloySorted[0];
					for (uint j = 0; j < approxPloySorted.size(); j++) {
						if (approxPloySorted[j].x < leftmost.x)
							leftmost = approxPloySorted[j];
					}

					cout << "Left Most ..." << leftmost << endl;
					cout << "y3 ..." << y3 << endl;
					cout << "Left Most ..." << leftmost.y << endl;

					if (y3 == leftmost.y) {
						cout << "Left Arrow.. " << endl;
					} else {
						cout << "Right Arrow.. " << endl;
					}

				}
			}
		}
	}
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
