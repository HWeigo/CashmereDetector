#include "BaseDetector.h"



BaseDetector::BaseDetector(string filePath, Ui::CashmereDetectorClass ui)
{
	oriImg_ = imread(filePath);
	if (oriImg_.empty()) {
		cerr << "[ERROR] cannot open file" << endl;
	}
	oriImg_.copyTo(currImg_);

	ui_ = ui;

	
}


BaseDetector::~BaseDetector()
{
}

void BaseDetector::ShowImage_QWidget() {
	//string winName = "img";
	cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
	cv::resizeWindow(winName, cv::Size(ui_.widget->width(), ui_.widget->height()));
	resize(currImg_, currImg_, Size(ui_.widget->width(), ui_.widget->height()));
	cv::imshow(winName, currImg_);

	//��Qt�ؼ�����ʾcv::nameWindow����
	HWND hwnd = (HWND)cvGetWindowHandle(winName.c_str());
	//HWND paraent = GetParent(hwnd);//�õ�nameWindow���ڵĸ����
	parent = GetParent(hwnd);
	SetParent(hwnd, (HWND)ui_.widget->winId());//����ui�ؼ��ľ���Ǹ����

	ShowWindow(parent, SW_HIDE);//���ص�nameWindow����
}



void BaseDetector::Reset(string filePath) {
	Mat newImg = imread(filePath);
	if (newImg.empty()) {
		cerr << "[ERROR] cannot open file" << endl;
	}
	oriImg_.release();
	currImg_.release();
	newImg.copyTo(oriImg_);
	newImg.copyTo(currImg_);

	cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
	cv::resizeWindow(winName, cv::Size(ui_.widget->width(), ui_.widget->height()));
	resize(currImg_, currImg_, Size(ui_.widget->width(), ui_.widget->height()));
	cv::imshow(winName, currImg_);

	ShowWindow(parent, SW_HIDE);//���ص�nameWindow����
}

void BaseDetector::Reset(Mat newImg) {
	oriImg_ = newImg;
	currImg_ = newImg;
	ShowImage_QWidget();
}

bool drawRectangle = false;//���ɱ���ػ���Ҫ���弸��ȫ�ֱ���������
Point leftClickPoint = Point(-1, -1);
Point mousePoint = Point(-1, -1);
void on_mouse(int event, int x, int y, int flags, void *ustc)
//event����¼����ţ�x,y������꣬flags��ק�ͼ��̲����Ĵ���    
{
	Mat& image = *(cv::Mat*) ustc;//�����Ϳ��Դ���Mat��Ϣ�ˣ��ܻ���
	char temp[16];
	switch (event) {
	case EVENT_LBUTTONDOWN://�������
	{
		sprintf(temp, "(%d,%d)", x, y);
		cout << "mouse click: " <<  x << " " << y << endl;
		putText(image, temp, Point(x, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		drawRectangle = true;
		leftClickPoint = Point(x, y);
	}	break;
	case EVENT_MOUSEMOVE://�ƶ����
	{
		mousePoint = Point(x, y);
		cout << x << " " << y << endl;
		if (drawRectangle)
		{
		}
	}break;
	//case EVENT_LBUTTONUP:
	//{
	//	drawRectangle = false;
	//	sprintf(temp, "(%d,%d)", x, y);
	//	putText(image, temp, Point(x, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
	//	//���ú������л���
	//	cv::rectangle(image, leftClickPoint, mousePoint, cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));//�����ɫ  
	//}break;
	}
}

void BaseDetector::StartPickMode() {
	setMouseCallback("img", on_mouse, (void*)&currImg_);
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
//	QPixmap fitpixmapL = pixmapL.scaled(pWidth, pHigh, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // �������
//	ui_.label->setPixmap(fitpixmapL);
//
//	ui_.label->show();
//	waitKey(1);
//	//	cout << " 66666666666666\n  ";
//}