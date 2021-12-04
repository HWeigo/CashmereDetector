#pragma once
#include "BaseDetector.h"
#include <omp.h>
#include "HalconCpp.h"

using namespace HalconCpp;

class AutoDetector : public BaseDetector
{
private:
	HObject oriHImg_;
	Mat oriImg_;
	Mat regionImg_;
	Mat regionImgStore_;
	Mat edgeImg_;
	Mat skeletonImg_;
	Mat straightenImg_;
	vector<Point> skeletonPoints_;
	vector<Point> skeletonPointsSort_;

	int cols_;
	int rows_;
	double length_;
	int levelNum_ = 5;

	void FillNeighbor(Mat &img, Point point, int layer, vector<Point> &list);
	void thinningIteration(Mat& im, int iter);
	void thinning(Mat& im);
	void straightenImg();
	void Clear();

	void cartesianToFrenet1D(double rs, double rx, double ry, double rtheta, int x, int y, double& dstS, double& dstD);
	double findNearestRs(const vector<double>& funcX, const vector<double>& funcY, int x, int y, const vector<double>& snew);
	int findNearestRs(const vector<double>& vecSX, const vector<double>& vecSY, int x, int y, const vector<double>& snew, double disThresh);
	vector<double> polyfit(vector<Point>& srcPoints);
	double calFunc(vector<double> funcX, double x);
	Mat skeletonization(Mat inputImage);
	const vector<pair<int, int>> directions{\
	{ 0, 1 }, { 0,-1 }, { 1,0 }, { -1,0 }, \
	{ 1, 1 }, { 1,-1 }, { -1,-1 }, { -1, 1 } };

public:
	AutoDetector(Ui::CashmereDetectorClass ui);
	~AutoDetector();

	// Run auto-detect function
	void AutoDetect();

	void RegionDetect();
	void SkeletonDetect();

	void OutputSkeleton();



	double GetLength();
	void ScalesDetect();
};

