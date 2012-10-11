/*
 * codebook.cpp
 *
 *  Created on: Oct 11, 2012
 *      Author: hugo
 */

#include "codebook.h"

codebook::codebook(int nframesToLearnBG, int nframesPeriod) {
	this->model = cvCreateBGCodeBookModel();
	this->model->modMin[0] = 3;
	this->model->modMin[1] = this->model->modMin[2] = 3;
	this->model->modMax[0] = 10;
	this->model->modMax[1] = this->model->modMax[2] = 10;
	this->model->cbBounds[0] = this->model->cbBounds[1] =
			this->model->cbBounds[2] = 10;
	this->nframesPeriod = nframesPeriod;
	this->nframesToLearnBG = nframesToLearnBG;
}

codebook::~codebook() {
	// TODO Auto-generated destructor stub
}

void codebook::updateAndgetForeground(IplImage* rawImage, IplImage* foreground,
		int frameNum) {
	int nframe = frameNum % this->nframesPeriod;
	IplImage* yuvImage = cvCloneImage(rawImage);
	cvCvtColor(rawImage, yuvImage, CV_BGR2YCrCb);
	if (nframe < this->nframesToLearnBG)
		cvBGCodeBookUpdate(this->model, yuvImage);
	if (nframe == this->nframesToLearnBG)
		cvBGCodeBookClearStale(this->model, this->model->t / 2);
	if (frameNum > this->nframesToLearnBG)
		cvBGCodeBookDiff(model, yuvImage, foreground);
}

