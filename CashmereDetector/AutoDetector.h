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

public:
	AutoDetector(Ui::CashmereDetectorClass ui);
	~AutoDetector();

	// Run auto-detect function
	void AutoDetect();


	void RegionDetect();
	void SkeletonDetect();
};

