#include "AreaDetector.h"

void AreaDetector::on_mouse(int event, int x, int y, int flags, void * ustc)
{
	AreaDetector *detector = (AreaDetector*)ustc;
	Point mousePoint = Point(x, y);
	switch (event) {
		case EVENT_LBUTTONDOWN://按下左键
		{
			cout << "mouse click at: " << x << " " << y << endl;
			detector->CropRectangle(mousePoint);
			++detector->cropCnt;
			cout << "[INFO] image crop and save" << endl;
			break;
		}	
		case EVENT_MOUSEMOVE://移动鼠标
		{
			detector->DrawRectangle(mousePoint);
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

void AreaDetector::LoadImg(string filepath){
	BaseDetector::LoadImg(filepath);
	rotImg_ = GetCurrImg();
	cropCnt = 0;
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
	rectangle(draw, topleft, buttomright, Scalar(255, 0, 0));
	Mat &currImgRef = GetCurrImgRef();
	draw.copyTo(currImgRef);

	lastPoint_ = center;
}

void AreaDetector::DrawRectangle(Point center){
	DrawRectangle(center, rectWidth_, rectHeight_);
}

void AreaDetector::DrawRactangle(){
	DrawRectangle(lastPoint_);
}

void AreaDetector::CropRectangle(Point center){
	string filepath = "./output/" + imgID_ + "_" + to_string(cropCnt) + ".jpg";
	CropRectangle(filepath, center);
}

void AreaDetector::CropRectangle(string filepath, Point center)
{
	int x = center.x, y = center.y;
	if ((x - rectWidth_ / 2) < 0 || (y - rectHeight_ / 2) < 0 || \
		(x + rectWidth_ / 2) >= dispImgWidth_ || (y + rectHeight_ / 2) >= dispImgHeight_) {
		cerr << "on the boundary" << endl;
		return;
	}

	Point topleft((int)((x - rectWidth_ / 2) / scale_), (int)((y - rectHeight_ / 2) / scale_));
	Point buttomright((int)((x + rectWidth_ / 2) / scale_), (int)((y + rectHeight_ / 2) / scale_));
	Rect cropRect(topleft, buttomright);
	Mat cropImg;
	resize(rotImg_, cropImg, Size(imgWidth_, imgHeight_));
	//imwrite("./output/rotate.jpg", cropImg);
	cropImg(cropRect).copyTo(cropImg);

	Size outputSize((int)50 * rectScale_, 50);
	resize(cropImg, cropImg, outputSize);
	imwrite(filepath, cropImg);
}
void AreaDetector::ComputeArea(Point center, int width, int height, Point &topleft, Point &buttomright){
	int x = center.x, y = center.y;
	topleft.x = ((x - width / 2) < 0) ? 0 : (x - width / 2);
	topleft.y = ((y - height / 2) < 0) ? 0 : (y - height / 2);
	buttomright.x = ((x + width / 2) >= dispImgWidth_) ? dispImgWidth_ : (x + width / 2);
	buttomright.y = ((y + height / 2) >= dispImgHeight_) ? dispImgHeight_ : (y + height / 2);
}

void AreaDetector::SetRectSize(int height){
	rectHeight_ = height;
	rectWidth_ = (int)(height * rectScale_);
}

int AreaDetector::GetRectHeight()
{
	return rectHeight_;
}

int AreaDetector::GetRectWidth()
{
	return rectWidth_;
}

