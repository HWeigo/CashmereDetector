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

	float rectScale_ = 2.5; // rectWidth_ / rectHeight_
	int rectHeight_ = 50;
	int rectWidth_ = rectHeight_ * rectScale_; // 125


	vector<Point> skeletonPoints_;
	vector<Point> skeletonPointsSort_;

	int cols_;
	int rows_;
	double length_;
	int levelNum_ = 5;

	void FillNeighbor(Mat &img, Point point, int layer, vector<Point> &list);
	void ThinningIteration(Mat& im, int iter);
	void Thinning(Mat& im);
	void StraightenImg();
	void Clear();

	void cartesianToFrenet1D(double rs, double rx, double ry, double rtheta, int x, int y, double& dstS, double& dstD);
	double findNearestRs(const vector<double>& funcX, const vector<double>& funcY, int x, int y, const vector<double>& snew);
	int findNearestRs(const vector<double>& vecSX, const vector<double>& vecSY, int x, int y, const vector<double>& snew, double disThresh);
	vector<double> polyfit(vector<Point>& srcPoints);
	double calFunc(vector<double> funcX, double x);
	Mat Skeletonization(Mat inputImage);
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

	void CropImage();

	double GetLength();
	void ScalesDetect();
};

