/*
 * codebook.h
 *
 *  Created on: Oct 11, 2012
 *      Author: hugo
 */
#include "opencv2/core/core.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/legacy/legacy.hpp"

#ifndef CODEBOOK_H_
#define CODEBOOK_H_

class codebook {
public:
	codebook(int nframesToLearnBG, int nframesPeriod);
	virtual ~codebook();
	void updateAndgetForeground(IplImage* rawImage, IplImage* f, int frameNum);

	CvBGCodeBookModel* model;
	int nframesToLearnBG;
	int nframesPeriod;

};

#endif /* CODEBOOK_H_ */
