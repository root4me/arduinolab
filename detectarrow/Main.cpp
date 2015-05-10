#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat input;
int sliderinit = 0;

void findArrow(int pos, void* userdata) {

	cout << pos << endl;

	// canny
	// contour
	// loop contours
	// get approx poly
	// if possible arrow find direction
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

	imshow("Input Image",input);
	createTrackbar("Refine", "Input Image", &sliderinit, 255, findArrow);

	waitKey(0);
	return (0);
}
