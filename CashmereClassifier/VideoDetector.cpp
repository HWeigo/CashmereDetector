#include "VideoDetector.h"

VideoDetector::VideoDetector(Ui::CashmereDetectorClass ui) : BaseDetector(ui) {

}

void VideoDetector::LoadVideo(string filePath)
{
	capture_.open(filePath);
	ShowVideo();
}

void VideoDetector::ShowVideo()
{
	Mat currFrame;
	while (capture_.read(currFrame)) {
		BaseDetector::LoadImg(currFrame);
		ShowCurrImg();
		//imshow("frame", currFrame);
		waitKey(1);
	}
}
