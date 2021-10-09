#pragma once

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QStandardItem>
//#include <QLable>

#include<Windows.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

#include <string>
#include <vector>

#include "ui_CashmereDetector.h"


using namespace cv;
using namespace std;

class BaseDetector
{
private:
	Mat oriImg_;
	Mat currImg_;
	Ui::CashmereDetectorClass ui_;
	string winName = "img";
	HWND parent;
	bool isFirstShow = true;

public:
	BaseDetector(Ui::CashmereDetectorClass ui);
	BaseDetector(string filePath, Ui::CashmereDetectorClass ui);
	~BaseDetector();

	void ShowCurrImg();
	//void ShowImage_QLable();
	void LoadImg(string filepath);
	void LoadImg(Mat newImg);
	void ResetCurrImg();
	Mat GetCurrImg();
	Mat& GetCurrImgRef();
	void SaveCurrImg(string filepath = "./output/curr.jpg");
};

