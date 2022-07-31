#pragma once
#include "BaseDetector.h"
#include "CashmereDetector.h"


class CashmereDetector;

class VideoDetector :
	public BaseDetector
{
private:
	Mat currImg_;
	VideoCapture capture_;

	string autoCropsRoot = "./videoCrops/";

	int pixelDiffTresh_ = 2.5e6;
	int frameCntTresh_ = 30;
public:
	VideoDetector(Ui::CashmereDetectorClass ui);

	void LoadVideo(string filePath);

	void ShowVideo();

	//int VideoAutoCrop();
	int VideoAutoCrop(CashmereDetector *ui);

	//int update(CashmereDetector *ui);

	string GetCropsRoot() { return autoCropsRoot; };

	void SetVideoParams(int pixelDiffTresh, int frameCntTresh);
};

