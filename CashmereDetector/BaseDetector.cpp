#include "BaseDetector.h"

// This definitions in the cpp file, otherwise, once you include your header file into more than one C++ file
bool BaseDetector::isFirstShow = true; 

BaseDetector::BaseDetector(string filePath, Ui::CashmereDetectorClass ui) : ui_(ui)
{
	LoadImg(filePath);
}

BaseDetector::BaseDetector(Ui::CashmereDetectorClass ui) : ui_(ui) {
	oriImg_.release();
	currImg_.release();
	dispImgWidth_ = ui_.widget->width();
	dispImgHeight_ = ui_.widget->height();
}


BaseDetector::~BaseDetector()
{
}

void BaseDetector::ShowCurrImg() {
	if (currImg_.empty()) {
		cout << "[ERROR] image is empty" << endl;
		return;
	}

	cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
	cv::resizeWindow(winName, cv::Size(ui_.widget->width(), ui_.widget->height()));
	resize(currImg_, currImg_, Size(ui_.widget->width(), ui_.widget->height()));
	cv::imshow(winName, currImg_);
	//cv::imshow("test", currImg_);

	//Qt控件上显示cv::nameWindow窗口
	if (isFirstShow) {
		HWND hwnd = (HWND)cvGetWindowHandle(winName.c_str());
		parent = GetParent(hwnd);
		SetParent(hwnd, (HWND)ui_.widget->winId());//设置ui控件的句柄是父句柄
		ShowWindow(parent, SW_HIDE);//隐藏掉nameWindow窗口
		isFirstShow = false;
	}
}

void BaseDetector::LoadImg(string filepath) {
	Mat newImg = imread(filepath);
	if (newImg.empty()) {
		cerr << "[ERROR] cannot open file" << endl;
	}
	oriImg_.release();
	currImg_.release();
	newImg.copyTo(oriImg_);
	newImg.copyTo(currImg_);

	imgWidth_ = oriImg_.cols;
	imgHeight_ = oriImg_.rows;
	scale_ = (float)ui_.widget->width() / (float)imgWidth_;

	vector<string> tempId1 = split(filepath, "/"); // "home/img/a.jpg" -> {"home", "img", "a.jpg"}
	vector<string> tempId2 = split(tempId1.back(), "."); // "a.jpg" -> {"a", "jpg"}
    imgID_ = tempId2.front(); // "a"
	cout << "id: " << imgID_ << endl;


}

void BaseDetector::LoadImg(Mat newImg) {
	oriImg_.release();
	currImg_.release();
	newImg.copyTo(oriImg_);
	newImg.copyTo(currImg_);
}

void BaseDetector::LoadCurrImg(Mat newImg) {
	currImg_.release();
	newImg.copyTo(currImg_);
}


void BaseDetector::ResetCurrImg() {
	oriImg_.copyTo(currImg_);
	ShowCurrImg();
}

Mat BaseDetector::GetOriImg()
{
	return oriImg_;
}


Mat BaseDetector::GetCurrImg() {
	return currImg_;
}

Mat& BaseDetector::GetCurrImgRef() {
	Mat &ref = currImg_;
	return ref;
}

void BaseDetector::SaveCurrImg(string filepath) {
	imwrite("./output/ori.jpg", oriImg_);

	imwrite(filepath, currImg_);
}

string BaseDetector::GetImgID()
{
	return imgID_;
}

vector<string> BaseDetector::split(const string& str, const string& delim)
{
    vector<string> res;
    if ("" == str) return res;
    //先将要切割的字符串从string类型转换为char*类型  
    char * strs = new char[str.length() + 1]; //不要忘了  
    strcpy(strs, str.c_str());

    char * d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while (p) {
        string s = p; //分割得到的字符串转换为string类型  
        res.push_back(s); //存入结果数组  
        p = strtok(NULL, d);
    }
    return res;
}

//void BaseDetector::ShowImage_QLable()
//{
//	//cout << " 111111111111111\n  ";
//	Mat Left;
//	currImg_.copyTo(Left);
//
//
//	//cout << " 2222222222222\n  ";
//	int pWidth = ui_.label->width();
//	int pHigh = ui_.label->height();
//
//	//int pWidth, pHigh;
//	//if (float(w) / float(h) > 4.0 / 3.0)
//	//{
//	//	pWidth = int(h*4.0 / 3.0);
//	//	pHigh = h;
//	//}
//	//else
//	//{
//	//	pWidth = w;
//	//	pHigh = int(w*3.0 / 4.0);
//	//}
//	//	cout << " 333333333333\n  ";
//
//	//	cout << " 444444444444444\n  ";
//
//	QImage imgL = QImage((const unsigned char*)(Left.data), Left.cols, Left.rows, QImage::Format_RGB888);
//	QPixmap pixmapL = QPixmap::fromImage(imgL);
//	QPixmap fitpixmapL = pixmapL.scaled(pWidth, pHigh, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
//	ui_.label->setPixmap(fitpixmapL);
//
//	ui_.label->show();
//	waitKey(1);
//	//	cout << " 66666666666666\n  ";
//}