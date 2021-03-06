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
#include <unordered_map>

#include "ui_CashmereDetector.h"


using namespace cv;
using namespace std;

class BaseDetector
{
private:
	Mat oriImg_;
	Mat currImg_;

	Ui::CashmereDetectorClass ui_;
	HWND parent;


protected:
	int dispImgWidth_;
	int dispImgHeight_;
	int imgWidth_;
	int imgHeight_;
	float scale_;
	string winName = "img";
	string imgID_;
	string filePath_;

public:
	BaseDetector(Ui::CashmereDetectorClass ui);
	BaseDetector(string filePath, Ui::CashmereDetectorClass ui);
	~BaseDetector();

	static bool isFirstShow;

	// Show currImg_ on ui
	void ShowCurrImg();

	// Load image and reset oriImg_ and currImg_
	void LoadImg(string filepath);
	void LoadImg(Mat newImg);

	// Load image and reset currImg_ only
	void LoadCurrImg(Mat newImg);

	// Reset currImg_ with currImg_
	void ResetCurrImg();

	// Return oriImg_
	Mat GetOriImg();

	// Return currImg_
	Mat GetCurrImg();

	// Return currImg_ reference
	Mat& GetCurrImgRef();

	// Save currImg_ to filepath
	void SaveCurrImg(string filepath = "./output/curr.jpg"); 

	// Get img ID
	string GetImgID();
	
	// Get filepath
	string GetImgFilePath() { return filePath_; };

	// For spliting filepath
	static vector<string> split(const string& str, const string& delim);
	//void ShowImage_QLable();
};


