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
//RNG g_rng(12345);//ë���Ĳ����￴����������������������������ɫ
//bool �Ƿ񻭾��� = false;//���ɱ���ػ���Ҫ���弸��ȫ�ֱ���������
//Point ������� = Point(-1, -1);
//Point ���λ�� = Point(-1, -1);
//
//void on_mouse(int event, int x, int y, int flags, void *ustc)
////event����¼����ţ�x,y������꣬flags��ק�ͼ��̲����Ĵ���    
//{
//	Mat& image = *(cv::Mat*) ustc;//�����Ϳ��Դ���Mat��Ϣ�ˣ��ܻ���
//	char temp[16];
//	switch (event) {
//	case EVENT_LBUTTONDOWN://�������
//	{
//		sprintf(temp, "(%d,%d)", x, y);
//		putText(image, temp, Point(x, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
//		�Ƿ񻭾��� = true;
//		������� = Point(x, y);
//	}	break;
//	case EVENT_MOUSEMOVE://�ƶ����
//	{
//		���λ�� = Point(x, y);
//		if (�Ƿ񻭾���)
//		{
//		}
//	}break;
//	case EVENT_LBUTTONUP:
//	{
//		�Ƿ񻭾��� = false;
//		sprintf(temp, "(%d,%d)", x, y);
//		putText(image, temp, Point(x, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
//		//���ú������л���
//		cv::rectangle(image, �������, ���λ��, cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));//�����ɫ  
//	}break;
//	}
//}
//
//int main()
//{
//
//	system("color 9F");//ë��������ģ��ı�console��ɫ	
//	Mat org = imread("test.jpg"), temp1, temp2;
//	while (waitKey(30) != 27) {
//		org.copyTo(temp1);//������ʾ��������Լ���ʱ�ķ���
//		namedWindow("img");//����һ��img���� 
//		setMouseCallback("img", on_mouse, (void*)&org);//���ûص�����    
//		if (�Ƿ񻭾���)rectangle(temp1, �������, ���λ��, cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));//�����ɫ  
//		putText(temp1, "(" + std::to_string(���λ��.x) + "," + std::to_string(���λ��.y) + ")", ���λ��, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
//		imshow("img", temp1);
//	}
//}