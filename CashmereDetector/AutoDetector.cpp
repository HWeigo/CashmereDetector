#include "AutoDetector.h"
//#include "HalconWidthCalc.cpp"


void HObject2Mat(const HObject &_Hobj, cv::Mat &outMat)
{
	HTuple htCh = HTuple();
	HString cType;
	cv::Mat Image;
	HObject Hobj;
	ConvertImageType(_Hobj, &Hobj, "byte");
	CountChannels(Hobj, &htCh);
	Hlong w;
	Hlong h;
	if (htCh[0].I() == 1)
	{
		void* ptr = ((HImage)Hobj).GetImagePointer1(&cType, &w, &h);
		Image.create(h, w, CV_8UC1);
		uchar *pdata = static_cast<unsigned char *>(ptr);
		memcpy(Image.data, pdata, w * h);
	}
	else if (htCh[0].I() == 3)
	{
		void** pr = nullptr;
		void** pg = nullptr;
		void** pb = nullptr;
		((HImage)Hobj).GetImagePointer3(pr, pg, pb, &cType, &w, &h);
		Image.create(h, w, CV_8UC3);
		std::vector<cv::Mat> vecM(3);
		vecM[2].create(h, w, CV_8UC1);
		vecM[1].create(h, w, CV_8UC1);
		vecM[0].create(h, w, CV_8UC1);
		memcpy(vecM[2].data, pr, w * h);
		memcpy(vecM[1].data, pg, w * h);
		memcpy(vecM[0].data, pb, w * h);
		merge(vecM, Image);
	}
	outMat = Image;
}

HalconCpp::HObject MatToHObject(const cv::Mat &image) {
	HObject Hobj = HObject();
	int hgt = image.rows;
	int wid = image.cols;
	int i;
	//  CV_8UC3  
	if (image.type() == CV_8UC3)
	{
		vector<cv::Mat> imgchannel;
		split(image, imgchannel);
		cv::Mat imgB = imgchannel[0];
		cv::Mat imgG = imgchannel[1];
		cv::Mat imgR = imgchannel[2];
		uchar* dataR = new uchar[hgt*wid];
		uchar* dataG = new uchar[hgt*wid];
		uchar* dataB = new uchar[hgt*wid];
		for (i = 0; i<hgt; i++)
		{
			memcpy(dataR + wid*i, imgR.data + imgR.step*i, wid);
			memcpy(dataG + wid*i, imgG.data + imgG.step*i, wid);
			memcpy(dataB + wid*i, imgB.data + imgB.step*i, wid);
		}
		GenImage3(&Hobj, "byte", wid, hgt, (Hlong)dataR, (Hlong)dataG, (Hlong)dataB);
		delete[]dataR;
		delete[]dataG;
		delete[]dataB;
		dataR = NULL;
		dataG = NULL;
		dataB = NULL;
	}
	//  CV_8UCU1  
	else if (image.type() == CV_8UC1)
	{
		uchar* data = new uchar[hgt*wid];
		for (i = 0; i<hgt; i++)
			memcpy(data + wid*i, image.data + image.step*i, wid);
		GenImage1(&Hobj, "byte", wid, hgt, (Hlong)data);
		delete[] data;
		data = NULL;
	}
	return Hobj;
}

HalconCpp::HImage MatToHImage(const cv::Mat &image) {
	HalconCpp::HImage hImg(MatToHObject(image));
	return hImg;
}

AutoDetector::AutoDetector(Ui::CashmereDetectorClass ui) : BaseDetector(ui) {
}

void AutoDetector::AutoDetect() {

	EdgeDetect();
}

// Procedures 
// Chapter: Develop
// Short Description: Open a new graphics window that preserves the aspect ratio of the given image. 
void dev_open_window_fit_image(HObject ho_Image, HTuple hv_Row, HTuple hv_Column,
	HTuple hv_WidthLimit, HTuple hv_HeightLimit, HTuple *hv_WindowHandle)
{

	// Local iconic variables

	// Local control variables
	HTuple  hv_MinWidth, hv_MaxWidth, hv_MinHeight;
	HTuple  hv_MaxHeight, hv_ResizeFactor, hv_ImageWidth, hv_ImageHeight;
	HTuple  hv_TempWidth, hv_TempHeight, hv_WindowWidth, hv_WindowHeight;

	//This procedure opens a new graphics window and adjusts the size
	//such that it fits into the limits specified by WidthLimit
	//and HeightLimit, but also maintains the correct image aspect ratio.
	//
	//If it is impossible to match the minimum and maximum extent requirements
	//at the same time (f.e. if the image is very long but narrow),
	//the maximum value gets a higher priority,
	//
	//Parse input tuple WidthLimit
	if (0 != (HTuple((hv_WidthLimit.TupleLength()) == 0).TupleOr(hv_WidthLimit<0)))
	{
		hv_MinWidth = 500;
		hv_MaxWidth = 800;
	}
	else if (0 != ((hv_WidthLimit.TupleLength()) == 1))
	{
		hv_MinWidth = 0;
		hv_MaxWidth = hv_WidthLimit;
	}
	else
	{
		hv_MinWidth = ((const HTuple&)hv_WidthLimit)[0];
		hv_MaxWidth = ((const HTuple&)hv_WidthLimit)[1];
	}
	//Parse input tuple HeightLimit
	if (0 != (HTuple((hv_HeightLimit.TupleLength()) == 0).TupleOr(hv_HeightLimit<0)))
	{
		hv_MinHeight = 400;
		hv_MaxHeight = 600;
	}
	else if (0 != ((hv_HeightLimit.TupleLength()) == 1))
	{
		hv_MinHeight = 0;
		hv_MaxHeight = hv_HeightLimit;
	}
	else
	{
		hv_MinHeight = ((const HTuple&)hv_HeightLimit)[0];
		hv_MaxHeight = ((const HTuple&)hv_HeightLimit)[1];
	}
	//
	//Test, if window size has to be changed.
	hv_ResizeFactor = 1;
	GetImageSize(ho_Image, &hv_ImageWidth, &hv_ImageHeight);
	//First, expand window to the minimum extents (if necessary).
	if (0 != (HTuple(hv_MinWidth>hv_ImageWidth).TupleOr(hv_MinHeight>hv_ImageHeight)))
	{
		hv_ResizeFactor = (((hv_MinWidth.TupleReal()) / hv_ImageWidth).TupleConcat((hv_MinHeight.TupleReal()) / hv_ImageHeight)).TupleMax();
	}
	hv_TempWidth = hv_ImageWidth*hv_ResizeFactor;
	hv_TempHeight = hv_ImageHeight*hv_ResizeFactor;
	//Then, shrink window to maximum extents (if necessary).
	if (0 != (HTuple(hv_MaxWidth<hv_TempWidth).TupleOr(hv_MaxHeight<hv_TempHeight)))
	{
		hv_ResizeFactor = hv_ResizeFactor*((((hv_MaxWidth.TupleReal()) / hv_TempWidth).TupleConcat((hv_MaxHeight.TupleReal()) / hv_TempHeight)).TupleMin());
	}
	hv_WindowWidth = hv_ImageWidth*hv_ResizeFactor;
	hv_WindowHeight = hv_ImageHeight*hv_ResizeFactor;
	//Resize window
	SetWindowAttr("background_color", "black");
	OpenWindow(hv_Row, hv_Column, hv_WindowWidth, hv_WindowHeight, 0, "visible", "", &(*hv_WindowHandle));
	HDevWindowStack::Push((*hv_WindowHandle));
	if (HDevWindowStack::IsOpen())
		SetPart(HDevWindowStack::GetActive(), 0, 0, hv_ImageHeight - 1, hv_ImageWidth - 1);
	return;
}

// Chapter: Develop
// Short Description: Switch dev_update_pc, dev_update_var and dev_update_window to 'off'. 
void dev_update_off()
{

	//This procedure sets different update settings to 'off'.
	//This is useful to get the best performance and reduce overhead.
	//
	// dev_update_pc(...); only in hdevelop
	// dev_update_var(...); only in hdevelop
	// dev_update_window(...); only in hdevelop
	return;
}


void AutoDetector::EdgeDetect() {

	// Local iconic variables

	HObject  ho_Image11, ho_Image2, ho_Region;
	HObject  ho_ConnectedRegions, ho_RegionFillUp, ho_SelectedRegions2;
	HObject  ho_SelectedRegions1, ho_RegionClosing, ho_Skeleton;
	HObject  ho_Contours;
	
	// Local control variables
	HTuple  hv_Width, hv_Height, hv_WindowHandle;
	HTuple  hv_Channels, hv_Grayval, hv_Area, hv_Row, hv_Column;
	HTuple  hv_Number;

	HObject ho_Image1;
	ho_Image1 = MatToHObject(GetCurrImg());

	//Image Acquisition 01: Do something
	 if (HDevWindowStack::IsOpen())
	   CloseWindow(HDevWindowStack::Pop());
	 GetImageSize(ho_Image1, &hv_Width, &hv_Height); // DONT COMMENT THIS!!!!!!
	 
	 //dev_open_window_fit_image(ho_Image1, 0, 0, -1, -1, &hv_WindowHandle);
	 //dev_update_off();


	//blob分析挑选出测量区域（形状特征的选择）
	
	//判断通道数，若为3通道，则对图像灰度化
	CountChannels(ho_Image1, &hv_Channels);
	if (0 != (hv_Channels==3))
	{
	  Decompose3(ho_Image1, &ho_Image11, &ho_Image2, &ho_Image1);
	}
	GetGrayval(ho_Image1, 0, 0, &hv_Grayval);
	
	Threshold(ho_Image1, &ho_Region, 0, hv_Grayval-1);
	
	
	Connection(ho_Region, &ho_ConnectedRegions);
	
	
	FillUp(ho_ConnectedRegions, &ho_RegionFillUp);
	
	//形状选择
	SelectShape(ho_RegionFillUp, &ho_SelectedRegions2, "circularity", "and", 0, 0.1676);
	AreaCenter(ho_SelectedRegions2, &hv_Area, &hv_Row, &hv_Column);
	SelectShape(ho_SelectedRegions2, &ho_SelectedRegions1, "area", "and", hv_Area.TupleMax(), 
	    9999999);
	ClosingCircle(ho_SelectedRegions1, &ho_RegionClosing, 35);
	
	Skeleton(ho_RegionClosing, &ho_Skeleton);
	GenContourRegionXld(ho_RegionClosing, &ho_Contours, "border");
	
	
	CountObj(ho_SelectedRegions1, &hv_Number);
	
	if (0 != (hv_Number!=1))
	{
	  // stop(...); only in hdevelop
	}
	//显示结果
	HObject ho_BinImage;
	RegionToBin(ho_RegionClosing, &ho_BinImage, 255, 0, hv_Width, hv_Height);
	WriteImage(ho_BinImage, "bmp", 0, 
				  "D:/OneDrive@sjtu.edu.cn/ALGO/wool cashmere/CashmereDetector/CashmereDetector/1.bmp");	
	Mat temp;
	HObject2Mat(ho_BinImage, temp);
	imshow("temp", temp);

	//if (HDevWindowStack::IsOpen())
	//	DispObj(ho_Image1, HDevWindowStack::GetActive());
	//if (HDevWindowStack::IsOpen())
	//	DispObj(ho_Skeleton, HDevWindowStack::GetActive());
	//if (HDevWindowStack::IsOpen())
	//	DispObj(ho_Contours, HDevWindowStack::GetActive());

	//system("pause");
}

AutoDetector::~AutoDetector()
{
}


