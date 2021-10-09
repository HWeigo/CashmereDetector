#include "ManualDetector.h"


ManualDetector::~ManualDetector()
{
}

bool drawRectangle = false;//不可避免地还是要定义几个全局变量，伤心
Point leftClickPoint = Point(-1, -1);
Point mousePoint = Point(-1, -1);
void ManualDetector::on_mouse(int event, int x, int y, int flags, void *ustc)
//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号    
{
	//Mat& image = *(cv::Mat*) ustc;//这样就可以传递Mat信息了，很机智
	//Mat* image = (Mat*)ustc;
	Mat &image = *((Mat*)ustc);
	char temp[16];
	switch (event) {
		case EVENT_LBUTTONDOWN://按下左键
		{
			sprintf(temp, "(%d,%d)", x, y);
			cout << "mouse click: " << x << " " << y << endl;
			//putText(image, "here", Point(x, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
			circle(image, Point(x, y), 5, Scalar(0, 0, 255), -1);
			drawRectangle = true;
			leftClickPoint = Point(x, y);
		}	break;
		case EVENT_MOUSEMOVE://移动鼠标
		{
			mousePoint = Point(x, y);
			if (drawRectangle)
			{
			}
		}break;
	//case EVENT_LBUTTONUP:
	//{
	//	drawRectangle = false;
	//	sprintf(temp, "(%d,%d)", x, y);
	//	putText(image, temp, Point(x, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
	//	//调用函数进行绘制
	//	cv::rectangle(image, leftClickPoint, mousePoint, cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));//随机颜色  
	//}break;
	}
}

void ManualDetector::StartPickMode() {
	setMouseCallback("img", ManualDetector::on_mouse, (void*)&GetCurrImgRef());
}

void ManualDetector::EndPickMode() {
	setMouseCallback("img", NULL, NULL);
}