#pragma once
#include "BaseDetector.h"
#include <omp.h>
#include "HalconCpp.h"

#include<fstream>

#undef slots//不加这两句会报错
#include <torch/torch.h>
#include<torch/script.h>
#include<memory>
#define slots Q_SLOTS//不加这两句会报错

using namespace HalconCpp;

enum TYPE {CASHMERE = 0, WOOL, UNKNOWN, NONE};

#define INPUT_ORI
#define HALCON_REGION_DETECT

void HObject2Mat(const HObject &_Hobj, cv::Mat &outMat);
HalconCpp::HObject MatToHObject(const cv::Mat &image);
HalconCpp::HImage MatToHImage(const cv::Mat &image);
vector<Mat> MultiRegionDetect(Mat &srcImg);

class AutoDetector : public BaseDetector
{
private:
	HObject oriHImg_;
	Mat oriImg_;
	Mat regionImg_;
	Mat regionImgStore_;
	Mat edgeImg_;
	Mat skeletonImg_;
	Mat strightImg_;

	float rectScale_ = 3.5; // rectWidth_ / rectHeight_
	int rectHeight_ = 32;
	int rectWidth_ = rectHeight_ * rectScale_; // 112


	vector<Point> skeletonPoints_;
	vector<Point> skeletonPointsSort_;

	vector<Mat> cropImgs;

	int cols_;
	int rows_;
	double length_;
	int levelNum_ = 5;
	
	TYPE result_ = NONE;

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
	bool AutoDetect();

	void RegionDetect();

	int OtsuAlgThreshold(const Mat image);
	void RegionDetectOpenCV(Mat srcImg, Mat& dstImg);

	void BinaryDetect();

	bool SkeletonDetect();

	void OutputSkeleton();

	void CropImage();

	int ResNetClassify(string &&filename);

	double DiameterStdCompute();
	double DiameterStdCompute(Mat img, int slice);

	bool DefectDetection(Mat &img);

	double GetLength();
	TYPE GetResult() { return result_; };
	void ScalesDetect();
};

