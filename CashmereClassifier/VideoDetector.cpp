#include "VideoDetector.h"
#include "AutoDetector.h"

VideoDetector::VideoDetector(Ui::CashmereDetectorClass ui) : BaseDetector(ui) {

}

void VideoDetector::LoadVideo(string filePath)
{
	capture_.open(filePath);
	Mat firstFrame;
	capture_.read(firstFrame);
	BaseDetector::LoadImg(firstFrame);
	ShowCurrImg();
	//ShowVideo();
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

double calLaplacian(cv::Mat &image)
{
	cv::Mat grayImg, lapImage;
	if (image.channels() == 3) {
		cv::cvtColor(image, grayImg, COLOR_BGR2GRAY);
	}

	cv::Laplacian(grayImg, lapImage, CV_32FC1);
	lapImage = cv::abs(lapImage);

	return cv::mean(lapImage)[0];
}

Mat RegionDetect(Mat srcImg) {

	// Local iconic variables
	HObject  ho_Image11, ho_Image2, ho_Region;
	HObject  ho_ConnectedRegions, ho_RegionFillUp, ho_SelectedRegions2;
	HObject  ho_SelectedRegions1, ho_RegionClosing, ho_Skeleton;
	HObject  ho_Contours;

	// Local control variables
	HTuple  hv_Width, hv_Height, hv_WindowHandle;
	HTuple  hv_Channels, hv_Grayval, hv_Area, hv_Row, hv_Column;
	HTuple  hv_Number;

	HObject ho_Image1;
	ho_Image1 = MatToHObject(srcImg);

	//Image Acquisition 01: Do something
	if (HDevWindowStack::IsOpen())
		CloseWindow(HDevWindowStack::Pop());
	GetImageSize(ho_Image1, &hv_Width, &hv_Height); // DONT COMMENT THIS!!!!!!


													//blob分析挑选出测量区域（形状特征的选择）

													//判断通道数，若为3通道，则对图像灰度化
	CountChannels(ho_Image1, &hv_Channels);
	if (0 != (hv_Channels == 3))
	{
		Decompose3(ho_Image1, &ho_Image11, &ho_Image2, &ho_Image1);
	}
	GetGrayval(ho_Image1, 0, 0, &hv_Grayval);
	Threshold(ho_Image1, &ho_Region, 0, hv_Grayval - 1);
	Connection(ho_Region, &ho_ConnectedRegions);
	FillUp(ho_ConnectedRegions, &ho_RegionFillUp);

	//形状选择
	SelectShape(ho_RegionFillUp, &ho_SelectedRegions2, "circularity", "and", 0, 0.1676);
	AreaCenter(ho_SelectedRegions2, &hv_Area, &hv_Row, &hv_Column);
	SelectShape(ho_SelectedRegions2, &ho_SelectedRegions1, "area", "and", hv_Area.TupleMax(),
		9999999);
	ClosingCircle(ho_SelectedRegions1, &ho_RegionClosing, 35);

	Skeleton(ho_RegionClosing, &ho_Skeleton);
	GenContourRegionXld(ho_RegionClosing, &ho_Contours, "border");


	CountObj(ho_SelectedRegions1, &hv_Number);

	//显示结果
	HObject ho_BinImage;
	RegionToBin(ho_RegionClosing, &ho_BinImage, 255, 0, hv_Width, hv_Height);
	//WriteImage(ho_BinImage, "bmp", 0, 
	//			  "D:/OneDrive@sjtu.edu.cn/ALGO/wool cashmere/CashmereDetector/CashmereDetector/region.bmp");
	Mat dstImg;
	HObject2Mat(ho_BinImage, dstImg);
	return dstImg;
}

int frameIdx = 0;
Mat getBestFrame(vector<Mat>& frameVec) {
	// select the best frame from the vector
	vector<double> scoreVec;
	int bestIdx = 0;
	int maxScore = 0;
	const int Q = 1e2;

	int step = 2;
	for (int i = 0; i < frameVec.size(); i += step) {
		Mat tempFrame;
		frameVec[i].copyTo(tempFrame);
		//Mat regionImg = RegionDetect(tempFrame);
		double lapVal = calLaplacian(tempFrame);	
		vector<Mat> regionImgs = MultiRegionDetect(tempFrame);
		
		//imwrite("./debug_" + to_string(frameIdx) + ".jpg", tempFrame);

		double curScore = 0;
		for (int j = 0; j < regionImgs.size(); ++j) {
			Mat regionImg;
			regionImgs[j].copyTo(regionImg);
			//imwrite("./region__" + to_string(frameIdx) + "_" + to_string(j) + ".jpg", regionImg);
			//imshow("win", regionImg);
			//waitKey(0);

			vector<vector<Point>> contours;
			vector<Vec4i> hierarchy;
			findContours(regionImg, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
			int contoursNum = contours.size();

			curScore += Q*lapVal*1.f / contoursNum; // improve
			//curScore += Q*lapVal*1.f ; // improve
		}
		cout << "num: " << regionImgs.size() << endl;
		cout << "i: " << i << " score: " << curScore << endl;
		if (curScore > maxScore) {
			maxScore = curScore;
			bestIdx = i;
		}
	}
	++frameIdx;
	cout << "best: " << bestIdx << "/" << frameVec.size() << endl;

	return frameVec[bestIdx];
}

int VideoDetector::VideoAutoCrop(CashmereDetector *ui) {
	if (!capture_.isOpened())
		return -1;

	Mat tempFrame;
	Mat preFrame;
	int frameCnt = 0;
	int cropCnt = 0;

	capture_.read(tempFrame);

	vector<int> frameDiffVec;	
	fstream file;	
	file.open("result.txt", ios_base::out);

	int contFrameThresh = 30;
	double updateThresh = 0.5;
	int numThresh = 1.5e6;
	//int numThresh = 3e6;

	Mat tmpStore;
	int conFrameCnt = 0;
	bool storedFlag = false;
	
	int storeCnt = 0;

	vector<Mat> tmpFrameVec;

	while (capture_.read(tempFrame))
	{
		Mat currFrame;
		tempFrame.copyTo(currFrame);
		BaseDetector::LoadImg(currFrame);
		ShowCurrImg();
		++frameCnt;

		if (frameCnt >= 2) {
			Mat frameDiff;

			//imshow("origin", currFrame);
			//imshow("prev", preFrame);
			absdiff(currFrame, preFrame, frameDiff);
			Scalar channleDiff = sum(frameDiff);
			int pixelDiffSum = channleDiff[0]+ channleDiff[1] + channleDiff[2];
			frameDiffVec.push_back(pixelDiffSum);

			++conFrameCnt;
			if (!storedFlag) {
				currFrame.copyTo(tmpStore);
				tmpFrameVec.push_back(currFrame);
				storedFlag = true;
			}
			else {
				double randNum = rand() / double(RAND_MAX);
				if (randNum < updateThresh) {
					currFrame.copyTo(tmpStore);
					tmpFrameVec.push_back(currFrame);
				}		
			}
			if (pixelDiffSum > numThresh) {
				int cropIdx = 5;
				if (conFrameCnt > contFrameThresh && tmpFrameVec.size() > cropIdx) {
					//imwrite(storeFileName + "best_" + to_string(++storeCnt) + ".png", getBestFrame(tmpFrameVec));
					Mat toStoreImg = tmpFrameVec[tmpFrameVec.size() - cropIdx];
					vector<Mat> regionImgs = MultiRegionDetect(toStoreImg);
					if (!regionImgs.empty()) {
						imwrite(autoCropsRoot + "autocrop_" + to_string(storeCnt) + ".jpg", toStoreImg);
						ui->PushMessage("detect " + to_string(regionImgs.size()) + " fiber");
						ui->PushMessage("save as: autocrop_" + to_string(storeCnt) + ".jpg");
						cout << "img save" << endl;
						++storeCnt;
						++cropCnt;
					}
					//for (int j = 0; j < tmpFrameVec.size(); ++j) {
					//	imwrite(storeFileName + "store_" + to_string(storeCnt) + "_" + to_string(j) + ".png", tmpFrameVec[j]);
					//}
					//imwrite(storeFileName + to_string(++storeCnt) + ".png", currFrame);
				}
				tmpFrameVec.clear();
				tmpFrameVec.resize(0);
				conFrameCnt = 0;
				storedFlag = false;
			}

			file << pixelDiffSum << endl;
			 //imshow("diff", frameDiff);
		}
		currFrame.copyTo(preFrame);
		waitKey(1);
	}
	file.close();
	//capture_.release();
	return cropCnt;
}

//int VideoDetector::update(CashmereDetector * ui) {
//	ui->PushMessage("msg");
//	return 0;
//}


