#include "ManualDetector.h"


ManualDetector::~ManualDetector()
{
}

bool drawRectangle = false;//���ɱ���ػ���Ҫ���弸��ȫ�ֱ���������
Point leftClickPoint = Point(-1, -1);
Point mousePoint = Point(-1, -1);
void ManualDetector::on_mouse(int event, int x, int y, int flags, void *ustc)
//event����¼����ţ�x,y������꣬flags��ק�ͼ��̲����Ĵ���    
{
	//Mat& image = *(cv::Mat*) ustc;//�����Ϳ��Դ���Mat��Ϣ�ˣ��ܻ���
	//Mat* image = (Mat*)ustc;
	Mat &image = *((Mat*)ustc);
	char temp[16];
	switch (event) {
		case EVENT_LBUTTONDOWN://�������
		{
			sprintf(temp, "(%d,%d)", x, y);
			cout << "mouse click: " << x << " " << y << endl;
			//putText(image, "here", Point(x, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
			circle(image, Point(x, y), 5, Scalar(0, 0, 255), -1);
			drawRectangle = true;
			leftClickPoint = Point(x, y);
		}	break;
		case EVENT_MOUSEMOVE://�ƶ����
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
	//	//���ú������л���
	//	cv::rectangle(image, leftClickPoint, mousePoint, cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));//�����ɫ  
	//}break;
	}
}

void ManualDetector::StartPickMode() {
	setMouseCallback("img", ManualDetector::on_mouse, (void*)&GetCurrImgRef());
}

void ManualDetector::EndPickMode() {
	setMouseCallback("img", NULL, NULL);
}