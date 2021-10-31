#pragma once
#include "BaseDetector.h"
#include "HalconCpp.h"

using namespace HalconCpp;

class AutoDetector : public BaseDetector
{
private:
	HObject oriHImg_;
	Mat regionImg_;
	Mat edgeImg_;
	Mat skeletonImg_;
	vector<Point> skeletonPoints;

	int cols_;
	int rows_;
	double length_;

	void FillNeighbor(Mat &img, Point point, int layer, vector<Point> &list);
	void thinningIteration(Mat& im, int iter);
	void thinning(Mat& im);
	Mat skeletonization(Mat inputImage);
	vector<pair<int, int>> directions{\
	{ 0, 1 }, { 0,-1 }, { 1,0 }, { -1,0 }, \
	{ 1, 1 }, { 1,-1 }, { -1,-1 }, { -1, 1 } };
public:
	AutoDetector(Ui::CashmereDetectorClass ui);
	~AutoDetector();

	// Run auto-detect function
	void AutoDetect();

	void RegionDetect();
	void SkeletonDetect();

	double GetLength();
};

