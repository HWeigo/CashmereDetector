#include "CashmereDetector.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CashmereDetector w;
	w.show();
	return a.exec();
}


//#include <opencv2/opencv.hpp>
//#include<string>
//using namespace cv;
//RNG g_rng(12345);//毛大大的博客里看到的生成随机数，用于生成随机颜色
//bool 是否画矩形 = false;//不可避免地还是要定义几个全局变量，伤心
//Point 左击顶点 = Point(-1, -1);
//Point 鼠标位置 = Point(-1, -1);
//
//void on_mouse(int event, int x, int y, int flags, void *ustc)
////event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号    
//{
//	Mat& image = *(cv::Mat*) ustc;//这样就可以传递Mat信息了，很机智
//	char temp[16];
//	switch (event) {
//	case EVENT_LBUTTONDOWN://按下左键
//	{
//		sprintf(temp, "(%d,%d)", x, y);
//		putText(image, temp, Point(x, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
//		是否画矩形 = true;
//		左击顶点 = Point(x, y);
//	}	break;
//	case EVENT_MOUSEMOVE://移动鼠标
//	{
//		鼠标位置 = Point(x, y);
//		if (是否画矩形)
//		{
//		}
//	}break;
//	case EVENT_LBUTTONUP:
//	{
//		是否画矩形 = false;
//		sprintf(temp, "(%d,%d)", x, y);
//		putText(image, temp, Point(x, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
//		//调用函数进行绘制
//		cv::rectangle(image, 左击顶点, 鼠标位置, cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));//随机颜色  
//	}break;
//	}
//}
//
//int main()
//{
//
//	system("color 9F");//毛大大程序里的，改变console颜色	
//	Mat org = imread("test.jpg"), temp1, temp2;
//	while (waitKey(30) != 27) {
//		org.copyTo(temp1);//用来显示点的坐标以及临时的方框
//		namedWindow("img");//定义一个img窗口 
//		setMouseCallback("img", on_mouse, (void*)&org);//调用回调函数    
//		if (是否画矩形)rectangle(temp1, 左击顶点, 鼠标位置, cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));//随机颜色  
//		putText(temp1, "(" + std::to_string(鼠标位置.x) + "," + std::to_string(鼠标位置.y) + ")", 鼠标位置, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
//		imshow("img", temp1);
//	}
//}