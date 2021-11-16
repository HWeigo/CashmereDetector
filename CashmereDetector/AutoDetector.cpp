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
	double timer_start = double(clock() / 1000.0);
	RegionDetect();
	double timer_mid = double(clock() / 1000.0);
	skeletonPoints.swap(vector<Point>());
	SkeletonDetect();
	double timer_end = double(clock() / 1000.0);
	cout << "auto detect time use: " << timer_end - timer_start << " s" << endl;
}

void AutoDetector::RegionDetect() {

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
	
	//显示结果
	HObject ho_BinImage;
	RegionToBin(ho_RegionClosing, &ho_BinImage, 255, 0, hv_Width, hv_Height);
	//WriteImage(ho_BinImage, "bmp", 0, 
	//			  "D:/OneDrive@sjtu.edu.cn/ALGO/wool cashmere/CashmereDetector/CashmereDetector/region.bmp");	
	HObject2Mat(ho_BinImage, regionImg_);

}

// Reference: https://github.com/krishraghuram/Zhang-Suen-Skeletonization/blob/master/skeletonization.hpp
void AutoDetector::thinningIteration(Mat& im, int iter)
{
    Mat marker = Mat::zeros(im.size(), CV_8UC1);

    for (int i = 1; i < im.rows-1; i++)
    {
        for (int j = 1; j < im.cols-1; j++)
        {
            uchar p2 = im.at<uchar>(i-1, j);
            uchar p3 = im.at<uchar>(i-1, j+1);
            uchar p4 = im.at<uchar>(i, j+1);
            uchar p5 = im.at<uchar>(i+1, j+1);
            uchar p6 = im.at<uchar>(i+1, j);
            uchar p7 = im.at<uchar>(i+1, j-1);
            uchar p8 = im.at<uchar>(i, j-1);
            uchar p9 = im.at<uchar>(i-1, j-1);

            int A  = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) +
                     (p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
                     (p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
                     (p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
            int B  = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
            int m1 = iter == 0 ? (p2 * p4 * p6) : (p2 * p4 * p8);
            int m2 = iter == 0 ? (p4 * p6 * p8) : (p2 * p6 * p8);

            if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
                marker.at<uchar>(i,j) = 1;
        }
    }

    im &= ~marker;
}

void AutoDetector::thinning(Mat& im)
{
    im /= 255;

    Mat prev = Mat::zeros(im.size(), CV_8UC1);
    Mat diff;
	int cnt = 0;
    do {
        thinningIteration(im, 0);
        thinningIteration(im, 1);
        absdiff(im, prev, diff);
        im.copyTo(prev);
		cnt += 2;
    }
    while (countNonZero(diff) > 0);
	cout << "iter num: " << cnt << endl;
    im *= 255;
}

Mat AutoDetector::skeletonization(Mat inputImage)
{
    if (inputImage.empty())
    	cout<<"Inside skeletonization, Source empty"<<endl;

	//cout << inputImage.type() << endl;
    Mat outputImage(inputImage);

    thinning(outputImage);
 	//imshow("thres", outputImage);
#if 1
	imwrite("skeletonization.bmp", outputImage);
	Mat draw = GetCurrImg();
	for (int u = 0; u < inputImage.cols; ++u) {
		for (int v = 0; v < inputImage.rows; ++v) {
			if (outputImage.at<uchar>(v, u) == 255) {
				draw.at<Vec3b>(v, u)[2] = 255;
			}
		}
	}
	imshow("d", draw);
	imwrite("skeletonization.bmp", draw);
#endif   
	return outputImage;
}


#define ZHANG_SUEN_SKELETONIZATION
#define EDGE_DILATE

//#define SKELETON_IMSHOW
void AutoDetector::SkeletonDetect() {

#ifdef ZHANG_SUEN_SKELETONIZATION
	skeletonImg_ = skeletonization(regionImg_);
#endif // ZHANG_SUEN_SKELETONIZATION

#ifdef EDGE_DILATE
	// --- A simpele demo implementation based onf OpenCV dilate function ---	
	//Canny(regionImg_, edgeImg_, 100, 100);
	//imshow("edge", edgeImg_);
	//Mat element = getStructuringElement(MORPH_ELLIPSE, Size(3, 3)); 	
	//for (int i = 0; i < 14; ++i) {
	//	string name = "dilate_" + to_string(i*5) + ".bmp";
	//	
	//	imwrite(name, edgeImg_);
	//	dilate(edgeImg_, edgeImg_, element, Point(-1, -1), 5);
	//}
	//imshow("dilate", edgeImg_);
	// -----------------------------------------------------------------------

	Canny(regionImg_, edgeImg_, 100, 100);
	//imshow("edge", edgeImg_);
	rows_ = edgeImg_.rows;
	cols_ = edgeImg_.cols;
	vector<Point> edgePoints;
	cout << cols_ << " " << rows_ << endl;
	Mat bfsMap(edgeImg_.size(), CV_8UC1);
	for (int u = 0; u < cols_; ++u) {
		for (int v = 0; v < rows_; ++v) {
			if (edgeImg_.at<uchar>(v, u) == 255) {
				bfsMap.at<uchar>(v, u) = 1;
				edgePoints.emplace_back(Point(u, v));
			}
		}
	}

#ifdef SKELETON_IMSHOW
	Mat draw(GetCurrImg());
	for (Point point : edgePoints) {
		draw.at<Vec3b>(point.y, point.x)[1] = 255;
	}
#endif // SKELETON_IMSHOW

	int layer = 2;
	int lastEdgeSize = edgePoints.size();
	int toThrowCnt = 0;
	while (!edgePoints.empty()) {
		int currEdgeSize = edgePoints.size();
		double ratio = (double)currEdgeSize / (double)lastEdgeSize;
		cout << "layer: " << layer << " point size: " << currEdgeSize << " ratio: " << ratio << endl;
		lastEdgeSize = currEdgeSize;
		vector<Point> tempEdgePoints;
		for (Point point : edgePoints) {
			FillNeighbor(bfsMap, point, layer*3, tempEdgePoints);
		}
		tempEdgePoints.swap(edgePoints);
		++layer;

		// Check if most of the edges have already shrink
		if (ratio < 0.96) {
#if  1
			string name = "./throw_" + to_string(layer) + "_" + to_string(ratio * 100) + ".bmp";
			imwrite(name, bfsMap);
#endif
			++toThrowCnt;
			if (toThrowCnt >= 3)
				break;
		}
	} 

	//imshow("bfsMap", bfsMap);
	length_ = layer * 2;

	cout << "thickness: " << length_ << endl;


#ifdef SKELETON_IMSHOW
	for (Point point : skeletonPoints) {
		draw.at<Vec3b>(point.y, point.x)[2] = 255;
	}
	imshow("draw", draw);
#endif //SKELETON_IMSHOW


#endif // EDGE_DILATE
}

void AutoDetector::FillNeighbor(Mat &img, Point point, int layer, vector<Point> &list) {
	int expandCnt = 0;
	int x = point.x;
	int y = point.y;
	for (pair<int, int> dir : directions) {
		int u = x + dir.first;
		int v = y + dir.second;
		if (u < 0 || u >= cols_ || v < 0 || v >= rows_) {
			continue;
		} 
		if (img.at<uchar>(v, u) == 0 && regionImg_.at<uchar>(v, u) != 0) {
			img.at<uchar>(v, u) = layer;
			list.emplace_back(Point(u, v));
			++expandCnt;
		}
	}
	if (expandCnt == 0)
		skeletonPoints.emplace_back(Point(x, y));
}

void AutoDetector::ScalesDetect() {
	// Local iconic variables
	HObject  ho_Image11, ho_Image2, ho_Image13;
	HObject  ho_Region, ho_ConnectedRegions, ho_RegionFillUp;
	HObject  ho_SelectedRegions2, ho_SelectedRegions1, ho_RegionClosing;
	HObject  ho_Contours, ho_ImageEmphasize1, ho_RegionErosion;
	HObject  ho_ImageReduced2, ho_ImageReduced, ho_ImageMean;
	HObject  ho_Edges, ho_Image;

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

	CountChannels(ho_Image1, &hv_Channels);
	if (0 != (hv_Channels==3))
	{
	  Decompose3(ho_Image1, &ho_Image11, &ho_Image2, &ho_Image13);
	}
	GetGrayval(ho_Image13, 0, 0, &hv_Grayval);

	Threshold(ho_Image13, &ho_Region, 0, hv_Grayval-1);


	Connection(ho_Region, &ho_ConnectedRegions);


	FillUp(ho_ConnectedRegions, &ho_RegionFillUp);

	//形状选择
	SelectShape(ho_RegionFillUp, &ho_SelectedRegions2, "circularity", "and", 0, 0.1676);
	AreaCenter(ho_SelectedRegions2, &hv_Area, &hv_Row, &hv_Column);
	SelectShape(ho_SelectedRegions2, &ho_SelectedRegions1, "area", "and", hv_Area.TupleMax(), 
	    9999999);
	ClosingCircle(ho_SelectedRegions1, &ho_RegionClosing, 35);

	GenContourRegionXld(ho_RegionClosing, &ho_Contours, "border");
	CountObj(ho_RegionClosing, &hv_Number);

	if (0 != (hv_Number!=1))
	{
	  // stop(...); only in hdevelop
	}
	Emphasize(ho_Image1, &ho_ImageEmphasize1, hv_Width, hv_Height, 2);
	ErosionCircle(ho_RegionClosing, &ho_RegionErosion, 1);

	ReduceDomain(ho_Image1, ho_RegionErosion, &ho_ImageReduced2);
	ReduceDomain(ho_ImageEmphasize1, ho_RegionErosion, &ho_ImageReduced);
	MeanImage(ho_ImageReduced, &ho_ImageMean, 1, 1);

	EdgesSubPix(ho_ImageMean, &ho_Edges, "canny", 3, 25, 35);

	if (HDevWindowStack::IsOpen())
	  DispObj(ho_Image1, HDevWindowStack::GetActive());
	if (HDevWindowStack::IsOpen())
	  DispObj(ho_Edges, HDevWindowStack::GetActive());
	HObject  ho_Region1, ho_BinImage;
	GenRegionContourXld(ho_Edges, &ho_Region1, "margin");
	RegionToBin(ho_Region1, &ho_BinImage, 255, 0, hv_Width, hv_Height);

	Mat temp;
	HObject2Mat(ho_BinImage, temp);

	cout << temp.size << endl;
	cout << temp.type() << endl;
	Mat draw = GetCurrImg();
	for (int u = 0; u < draw.cols; ++u) {
		for (int v = 0; v < draw.rows; ++v) {
			if (temp.at<uchar>(v, u) == 255) {
				draw.at<Vec3b>(v, u)[2] = 255;
			}
		}
	}
	imshow("draw", draw);
}

double AutoDetector::GetLength() {
	return length_;
}

AutoDetector::~AutoDetector()
{
}


