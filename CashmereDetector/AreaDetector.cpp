#include "AreaDetector.h"

void AreaDetector::on_mouse(int event, int x, int y, int flags, void * ustc)
{
	AreaDetector *detector = (AreaDetector*)ustc;
	switch (event) {
		case EVENT_LBUTTONDOWN://按下左键
		{
			cout << "mouse click: " << x << " " << y << endl;
			break;
		}	
		case EVENT_MOUSEMOVE://移动鼠标
		{
			Point mousePoint = Point(x, y);
			detector->DrawRectangle(mousePoint, 60, 30);
			break;
		}
	}

}

AreaDetector::~AreaDetector()
{
}

void AreaDetector::StartSelectMode()
{
	setMouseCallback(winName, AreaDetector::on_mouse, (void*)this);
}

void AreaDetector::EndSelectMode()
{
	setMouseCallback(winName, NULL, NULL);
}

void AreaDetector::RotateImage(int deg) {
	Mat src = GetOriImg();
	double angle = deg;

    // get rotation matrix for rotating the image around its center in pixel coordinates
    cv::Point2f center((src.cols-1)/2.0, (src.rows-1)/2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
    // determine bounding rectangle, center not relevant
    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
    // adjust transformation matrix
    rot.at<double>(0,2) += bbox.width/2.0 - src.cols/2.0;
    rot.at<double>(1,2) += bbox.height/2.0 - src.rows/2.0;

    cv::Mat &dst = GetCurrImgRef();
    cv::warpAffine(src, rotImg_, rot, bbox.size());
	dst = rotImg_;
	//imshow("r", src);
}

void AreaDetector::DrawRectangle(Point center, int width, int height){
	Point topleft, buttomright;
	ComputeArea(center, width, height, topleft, buttomright);
	Mat draw(rotImg_);
	resize(draw, draw, Size(dispImgWidth_, dispImgHeight_));
	rectangle(draw, topleft, buttomright, Scalar(0, 255, 0));
	Mat &currImgRef = GetCurrImgRef();
	draw.copyTo(currImgRef);
}

void AreaDetector::ComputeArea(Point center, int width, int height, Point &topleft, Point &buttomright){
	int x = center.x, y = center.y;
	topleft.x = ((x - width / 2) < 0) ? 0 : (x - width / 2);
	topleft.y = ((y - height / 2) < 0) ? 0 : (y - height / 2);
	buttomright.x = ((x + width / 2) >= dispImgWidth_) ? dispImgWidth_ : (x + width / 2);
	buttomright.y = ((y + height / 2) >= dispImgHeight_) ? dispImgHeight_ : (y + height / 2);
}

