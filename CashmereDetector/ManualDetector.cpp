#include "ManualDetector.h"


ManualDetector::~ManualDetector()
{
}

//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号    
void ManualDetector::on_mouse(int event, int x, int y, int flags, void *ustc)
{
	//Mat &image = *((Mat*)ustc);
	ManualDetector *detector = (ManualDetector*)ustc;
	Mat &image = detector->GetCurrImgRef();
	vector<Point> &points = detector->GetSelectedPoints();
	switch (event) {
		case EVENT_LBUTTONDOWN://按下左键
		{
			cout << "mouse click: " << x << " " << y << endl;
			circle(image, Point(x, y), POINT_RADIUS, Scalar(0, 0, 255), -1);
			points.push_back(Point(x, y));
			image.copyTo(detector->cacheImg_);
			if (points.size() == 2) {
				cout << "length: " << detector->CalcLength() << endl;
				vector<Point>().swap(points);
			}
			//putText(image, "here", Point(x, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
			break;
		}	
		case EVENT_MOUSEMOVE://移动鼠标
		{
			Point mousePoint = Point(x, y);
			if (points.size() != 1)
				break;
			detector->LoadCurrImg(detector->cacheImg_);
			Point lastPoint = points.back();
			line(image, mousePoint, lastPoint, Scalar(0, 0, 255), LINE_THICKNESS);
			break;
		}
	}
}

void ManualDetector::StartPickMode() {
	setMouseCallback("img", ManualDetector::on_mouse, (void*)this);
}

void ManualDetector::EndPickMode() {
	setMouseCallback("img", NULL, NULL);
}

vector<Point>& ManualDetector::GetSelectedPoints() {
	//vector<Point> temp = selectedPoints;
	return selectedPoints;
}

double ManualDetector::CalcLength() {
	double length;
	length = powf((selectedPoints[0].x - selectedPoints[1].x), 2) + \
		powf((selectedPoints[0].y - selectedPoints[1].y), 2);
	length = sqrtf(length);
	++numLength;
	sumLength += length;
	currLength = length;
	return length;
}

double ManualDetector::CalcMeanLength() {
	meanLength = sumLength / numLength;
	return meanLength;
}

void ManualDetector::ResetManualDetector() {
	numLength = 0;
	sumLength = 0;
	meanLength = 0;
	cacheImg_.release();
	vector<Point>().swap(selectedPoints);
	ResetCurrImg();
	ShowCurrImg();
}

double ManualDetector::GetCurrLength() {
	return currLength;
}

double ManualDetector::GetMeanLength() {
	return meanLength;
}

int ManualDetector::GetLengthNum() {
	return numLength;
}

