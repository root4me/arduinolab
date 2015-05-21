/*
 * shapes.h
 *
 *  Created on: May 20, 2015
 *      Author: harish
 */

#ifndef SHAPES_H_
#define SHAPES_H_

#include <stdio.h>

#include <opencv2/imgproc.hpp>

enum arrowdirection {
	left, right, up, down, unknown
};

struct arrow
{
	std::vector<cv::Point> polygon;
	arrowdirection direction;
};

class shapes {
private:
	//cv::Mat input;

public:
	shapes();
	shapes(cv::Mat img);
	std::vector<arrow> arrows();

};

#endif /* SHAPES_H_ */
