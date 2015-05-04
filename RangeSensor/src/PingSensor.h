/*
 * PingSensor.h
 *
 *  Created on: May 3, 2015
 *      Author: harish
 */

#ifndef SRC_PINGSENSOR_H_
#define SRC_PINGSENSOR_H_

class PingSensor {

private:

public:
	void init(int pin);
	long distance();
};


#endif /* SRC_PINGSENSOR_H_ */
