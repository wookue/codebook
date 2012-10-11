/*
 * test.cpp
 *
 *  Created on: Oct 11, 2012
 *      Author: hugo
 */

#include "codebook.h"
int main(int argc, const char** argv) {

	int nframesToLearnBG = 100;
	int nframesPeriod = 300;
	IplImage* rawImage = 0;
	IplImage *foreground;
	CvCapture* capture = 0;
	bool run = true;

	int nframes = 0;

	codebook* codeBookModel = new codebook(nframesToLearnBG, nframesPeriod);
	capture = cvCaptureFromCAM(0);

	//MAIN PROCESSING LOOP:
	for (; run;) {

		rawImage = cvQueryFrame(capture);
		++nframes;

		//First time: init some variables
		if (nframes == 1) {
			foreground = cvCreateImage(cvGetSize(rawImage), IPL_DEPTH_8U, 1);
			cvSet(foreground, cvScalar(255));

			cvNamedWindow("Raw", 1);
			cvNamedWindow("ForegroundCodeBook", 1);
		}

		//Display
		codeBookModel->updateAndgetForeground(rawImage, foreground, nframes);
		cvShowImage("Raw", rawImage);
		cvShowImage("ForegroundCodeBook", foreground);

		// User input:
		if (cv::waitKey(30) >= 0)
			run = false;

	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("Raw");
	cvDestroyWindow("ForegroundCodeBook");
	return 0;
}

