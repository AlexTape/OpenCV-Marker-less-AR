/*
 * main.h
 *
 *  Created on: 27.05.2015
 *      Author: thinker
 */

#ifndef SRC_MAIN_MAIN_H_
#define SRC_MAIN_MAIN_H_

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

#include "commonCvFunctions.h"
#include <opencv2/highgui/highgui.hpp>
#include "cameraCalibration.h"
#include "guiAR.h"

#include "../ObjRecog/controlOR.h"

using namespace cvar::orns;

int main(int argc, char *argv[]);
void doMainLoop(int argc, char *argv[]);
void doConsole(int argc, char *argv[], controlOR &ctrlOR);

#endif /* SRC_MAIN_MAIN_H_ */
