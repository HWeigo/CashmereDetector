#pragma once
#include "BaseDetector.h"
class VideoDetector :
	public BaseDetector
{
private:
	Mat currImg_;
	VideoCapture capture_;

public:
	VideoDetector(Ui::CashmereDetectorClass ui);

	void LoadVideo(string filePath);

	void ShowVideo();
};

