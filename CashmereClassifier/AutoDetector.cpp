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

bool AutoDetector::AutoDetect() {
	Clear();
	double timer_start = double(clock() / 1000.0);
#ifdef INPUT_ORI
	#ifdef HALCON_REGION_DETECT
	RegionDetect();
	#else
	//regionImg_ = Mat::zeros(GetCurrImg().size(), CV_8UC1);
	RegionDetectOpenCV(GetCurrImg(), regionImg_);
	regionImg_.copyTo(regionImgStore_);
	#endif
#else
	BinaryDetect();
#endif // INPUT_ORI

	imwrite("result/regionImg.bmp", regionImg_);
	double timer_mid = double(clock() / 1000.0);
	//skeletonPoints_.swap(vector<Point>());
	skeletonPoints_.clear();
	
	bool isSuccess = SkeletonDetect();
	double timer_end = double(clock() / 1000.0);
	cout << "auto detect time use: " << timer_end - timer_mid << " s" << endl;
	//DiameterStdCompute();

	ResNetClassify("./resnet164.pt");
	return isSuccess;
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

	regionImg_.copyTo(regionImgStore_);
}

int AutoDetector::OtsuAlgThreshold(const Mat image)
{
	if (image.channels() != 1)
	{
		cout << "请输入灰度图" << endl;
		return 0;
	}
	int T = 0; //Otsu算法阈值
	double varValue = 0; //类间方差中间值保存
	double w0 = 0; //前景像素点数所占比例
	double w1 = 0; //背景像素点数所占比例
	double u0 = 0; //前景平均灰度
	double u1 = 0; //背景平均灰度
	double Histogram[256] = { 0 }; //灰度直方图，下标是灰度值，保存内容是灰度值对应的像素点总数
	uchar *data = image.data;
	double totalNum = image.rows*image.cols; //像素总数
											 //计算灰度直方图分布，Histogram数组下标是灰度值，保存内容是灰度值对应像素点数
	for (int i = 0; i<image.rows; i++)   //为表述清晰，并没有把rows和cols单独提出来
	{
		for (int j = 0; j<image.cols; j++)
		{
			Histogram[data[i*image.step + j]]++;
		}
	}
	for (int i = 0; i<255; i++)
	{
		//每次遍历之前初始化各变量
		w1 = 0;		u1 = 0;		w0 = 0;		u0 = 0;
		//***********背景各分量值计算**************************
		for (int j = 0; j <= i; j++) //背景部分各值计算
		{
			w1 += Histogram[j];  //背景部分像素点总数
			u1 += j*Histogram[j]; //背景部分像素总灰度和
		}
		if (w1 == 0) //背景部分像素点数为0时退出
		{
			continue;
		}
		u1 = u1 / w1; //背景像素平均灰度
		w1 = w1 / totalNum; // 背景部分像素点数所占比例
							//***********背景各分量值计算**************************

		for (int k = i + 1; k<255; k++)
		{
			w0 += Histogram[k];  //前景部分像素点总数
			u0 += k*Histogram[k]; //前景部分像素总灰度和
		}
		if (w0 == 0) //前景部分像素点数为0时退出
		{
			break;
		}
		u0 = u0 / w0; //前景像素平均灰度
		w0 = w0 / totalNum; // 前景部分像素点数所占比例
							//***********前景各分量值计算**************************

		// 计算类间方差
		double varValueI = w0*w1*(u1 - u0)*(u1 - u0); //当前类间方差计算
		if (varValue<varValueI)
		{
			varValue = varValueI;
			T = i;
		}
	}
	return T;
}

void AutoDetector::RegionDetectOpenCV(Mat srcImg, Mat& dstImg) {
	Mat src, bw, bwTriangle, bwOtsu;
	vector<vector<Point>> contours;

	if (srcImg.channels() == 3)
		cv::cvtColor(srcImg, src, COLOR_RGB2GRAY);
	else
		srcImg.copyTo(src);
	int grayVal = srcImg.at<uchar>(0, 0);
	cout << "The gray value of position (0,0) is: " << grayVal << endl;
	
	int thresholdValue = OtsuAlgThreshold(src);
	int elementsize = 7;
	cv::threshold(src, bwTriangle, thresholdValue - 1, 255, THRESH_TRIANGLE | THRESH_BINARY_INV); // THRESH_TRIANGLE
	cv::threshold(src, bwOtsu, thresholdValue - 1, 255, THRESH_BINARY_INV); // THRESH_OTSU
	bwTriangle.copyTo(bw);
	bw = bwTriangle & bwOtsu;
	// 先过滤掉小的连通域后再做闭运算，能减少粘连的情况
	int minAreaLimit = 100;
	vector<vector<Point>> removeContours;
	cv::findContours(bw, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	
	for (size_t i = 0; i < contours.size(); i++){
		double area = cv::contourArea(contours[i]);

		if (area <= minAreaLimit){
			removeContours.push_back(contours[i]);
		}
	}
	Mat remMask = Mat::zeros(src.size(), CV_8UC1);
	for (int i = 0; i < removeContours.size(); i++) {
		drawContours(remMask, removeContours, i, Scalar(255), -1);
	}
	bw = bw ^ remMask;

	Mat kernel = getStructuringElement(MORPH_RECT, Size(elementsize * 2 + 1, elementsize * 2 + 1));
	
	morphologyEx(bw, bw, MORPH_CLOSE, kernel);
	cout << "类间方差为： " << thresholdValue << endl;
	cv::findContours(bw, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	double maxArea = 0;
	double minAreaRatio = 0.00;
	double maxAreaRatio = 0.08;
	int maxContourIdx = 0;
	vector<cv::Point> maxContour;

	int maxAreaLimit = maxAreaRatio*srcImg.rows*srcImg.cols;

	for (size_t i = 0; i < contours.size(); i++)
	{
		double area = cv::contourArea(contours[i]);
		
		if (area < minAreaLimit || area > maxAreaLimit)
			continue;
		if (area > maxArea)
		{
			maxArea = area;
			maxContour = contours[i];
			maxContourIdx = i;
		}
	}
	
	Mat region = Mat::zeros(srcImg.size(), CV_8UC1);
	drawContours(bw, contours, -1, Scalar(255, 255, 255), -1);
	drawContours(region, contours, maxContourIdx, Scalar(255), -1);
	cout << maxArea*1.f/(srcImg.rows*srcImg.cols) << endl;
	cv::Rect maxRect = cv::boundingRect(maxContour);	
	cv::Mat result1, result2, bw3c;
	cvtColor(bw, bw3c, COLOR_GRAY2BGR);
	bw3c.copyTo(result1); // 展示所有轮廓的bbox
	bw3c.copyTo(result2); // 仅展示限定范围内最大轮廓的bbox

	for (size_t i = 0; i < contours.size(); i++)
	{
		cv::Rect r = cv::boundingRect(contours[i]);
		cv::rectangle(result1, r, cv::Scalar(rand()%255, rand() % 255, rand() % 255));
	}
	
	cv::rectangle(result2, maxRect, cv::Scalar(0, 0, 255));
	Mat tmp(maxContour);
	Moments moment = moments(tmp, false);
	int x = cvRound(moment.m10 / moment.m00); // 计算重心横坐标
	int y = cvRound(moment.m01 / moment.m00); // 计算重心纵坐标
	
	cv::circle(result2, Point(x, y), 8, Scalar(0,255,0));

	//srcImg.copyTo(dstImg);
	//imshow("region", region);
	//waitKey(0);
	dstImg = Mat::zeros(srcImg.size(), CV_8UC1);
	for (int v = 0; v < srcImg.rows; ++v) {
		for (int u = 0; u < srcImg.cols; ++u) {
			if (region.at<uchar>(v, u) == 0)
				continue;
			dstImg.at<uchar>(v, u) = srcImg.at<uchar>(v, u);
		}
	}

	imshow("dst2", dstImg);
	waitKey(0);
}

void AutoDetector::BinaryDetect() {
	// Local iconic variables
	HObject  ho_Image, ho_Region, ho_BinImage;
	
	// Local control variables
	HTuple  hv_Width, hv_Height;
	
	//ReadImage(&ho_Image, "C:/Users/sunzc/Desktop/\311\275\321\362\310\33620211202/0.bmp");
	ho_Image = MatToHObject(GetCurrImg());
	GetImageSize(ho_Image, &hv_Width, &hv_Height);
	Threshold(ho_Image, &ho_Region, 1, 255);
	RegionToBin(ho_Region, &ho_BinImage, 255, 0, hv_Width, hv_Height);
	//WriteImage(ho_BinImage, "bmp", 0, HTuple(HTuple("C:/Users/sunzc/Desktop/")+1)+".bmp");
	HObject2Mat(ho_BinImage, regionImg_);

	regionImg_.copyTo(regionImgStore_);
}

void AutoDetector::cartesianToFrenet1D(double rs, double rx, double ry, double rtheta, int x, int y, double& dstS, double& dstD) {
	double dx = x - rx;
	double dy = y - ry;
	double cos_theta_r = cos(rtheta);
	double sin_theta_r = sin(rtheta);
	double cross_rd_nd = cos_theta_r * dy - sin_theta_r * dx;
	if (cross_rd_nd <0)
		dstD = -1 * sqrt(dx * dx + dy * dy);
	else
		dstD = sqrt(dx * dx + dy * dy);
	
	dstS = rs;
}


double AutoDetector::findNearestRs(const vector<double>& funcX, const vector<double>& funcY, int x, int y, const vector<double>& snew) {
	double minDis = 99999.0;
	double rs = 0.0;
	double dx, dy, dist;
	for (double s : snew) {
		// 代入参数方程进行计算
		dx = x - calFunc(funcX, s);
		if (fabs(dx) > 200)
			continue;
		dy = y - calFunc(funcY, s);
		if (fabs(dy) > 200)
			continue;
		dist = sqrt(dx*dx + dy*dy);
		if (minDis > dist) {
			minDis = dist;
			rs = s;
		}
	}
	return rs;
}

int AutoDetector::findNearestRs(const vector<double>& vecSX, const vector<double>& vecSY, int x, int y, const vector<double>& snew, double disThresh) {
	double minDis = 99999.0;
	int retI = -1;
	double dx, dy, dist;
	for (int i = 0; i < vecSX.size(); i++) {
		// 代入参数方程进行计算
		dx = x - vecSX[i];
		if (fabs(dx) > disThresh)
			continue;
		dy = y - vecSY[i];
		if (fabs(dy) > disThresh)
			continue;
		dist = sqrt(dx*dx + dy*dy);
		if (minDis > dist) {
			minDis = dist;
			retI = i;
		}
	}
	return retI;
}

double AutoDetector::calFunc(vector<double> funcX, double x) {
	double res = 0;
	for (int j = 0; j < funcX.size(); ++j)
	{
		res += funcX[j]*pow(x, j);
	}
	return res;
}

void AutoDetector::StraightenImg() {
	//imwrite("result/regionImg.bmp", regionImgStore_);
	// step1: 拟合曲线
	//cout << "p1 start polyfit" << endl;
	int lenLimit = skeletonPointsSort_.size();
	int elemLimit = skeletonPointsSort_.size();
	//cout << "p2 size is: " << lenLimit << endl;
	vector<double> theta;
	vector<double> coorX, coorY;
	vector<Point> ptsX, ptsY;

	for (int i = 0; i < elemLimit; i++) {
		theta.push_back(i*lenLimit*1.f / elemLimit);
		ptsX.push_back(Point(theta.back(), skeletonPointsSort_[i].x));
		ptsY.push_back(Point(theta.back(), skeletonPointsSort_[i].y));
	}

	vector<double> fX = polyfit(ptsX);
	vector<double> fY = polyfit(ptsY);
	vector<double> dfX, dfY;

	//Mat drawTemp(GetOriImg());
	//for (int i = 0; i < 2000; ++i) {
	//	int x = (int)calFunc(fX, i);
	//	int y = (int)calFunc(fY, i);
	//	circle(drawTemp, Point(x, y), 2, Scalar(0, 0, 255), -1);
	//}
	//resize(drawTemp, drawTemp, Size(), .5, .5);
	//imwrite("./result/polyfit.jpg", drawTemp);
	
	for (int i = 1; i < fX.size(); i++) {
		dfX.push_back(fX[i] * i);
		dfY.push_back(fY[i] * i);
	}

	// step2: 逐一映射
	int step = 1;
	int cnt = 0;


	vector<double> snew(theta.begin(), theta.end());

	int threadNum = omp_get_max_threads();
	omp_set_num_threads(threadNum);


	vector<vector<int>> colorVecVec(threadNum);
	vector<vector<double>> sVecVec(threadNum);
	vector<vector<double>> dVecVec(threadNum);
	//cout << "size==" << sVecVec.size() << "  "<<threadNum << endl;

	Mat tempRegionImg;
	Mat tempDrawImg = GetOriImg();
	Mat grayImg;
	cvtColor(tempDrawImg, grayImg, CV_BGR2GRAY);
	imwrite("result/gray.bmp", grayImg);
	regionImgStore_.copyTo(tempRegionImg);

	vector<int> rVec, cVec;
	for (int r = 0; r < rows_; r++) {
		for (int c = 0; c < cols_; c++) {
			if (tempRegionImg.at<uchar>(r, c) == 255) {
				rVec.push_back(r);
				cVec.push_back(c);
			}
		}
	}

	vector<double> vecSX(snew.size());
	vector<double> vecSY(snew.size());
	for (int i = 0; i < snew.size(); i++) {
		vecSX[i] = calFunc(fX, snew[i]);
		vecSY[i] = calFunc(fY, snew[i]);
	}

#pragma omp parallel for
	for (int i = 0; i < rVec.size(); i++) {
		int r = rVec[i];
		int c = cVec[i];

		int tid = omp_get_thread_num();

		double rs, rx, ry, rtheta;
		
		int retI = findNearestRs(vecSX, vecSY, c, r, snew, 200);
		rs = snew[retI];
		rx = vecSX[retI];
		ry = vecSY[retI];
		rtheta = atan2(calFunc(dfY, rs), calFunc(dfX, rs));
				
		double curS, curD;
		cartesianToFrenet1D(rs, rx, ry, rtheta, c, r, curS, curD);

				
		sVecVec[tid].push_back(curS);
		dVecVec[tid].push_back(curD);
		// cout << curS << " | " << curD << endl;
			
		colorVecVec[tid].push_back(grayImg.at<uchar>(r, c));
				
		// circle(tempDrawImg, Point(c, r), 1, (0, 0, 255), 3);

	}


	vector<int> colorVec;
	vector<double> sVec, dVec;

	for (int i = 0; i < threadNum; ++i) {
		colorVec.insert(colorVec.end(), colorVecVec[i].begin(), colorVecVec[i].end());
		sVec.insert(sVec.end(), sVecVec[i].begin(), sVecVec[i].end());
		dVec.insert(dVec.end(), dVecVec[i].begin(), dVecVec[i].end());
	}

	double sMin = INT_MAX, sMax = INT_MIN, dMin = INT_MAX, dMax = INT_MIN;

	for (int i = 0; i < sVec.size(); ++i) {
		double curS = sVec[i];
		double curD = dVec[i];
		curS < sMin ? sMin = curS : sMin = sMin;
		curS > sMax ? sMax = curS : sMax = sMax;
		curD < dMin ? dMin = curD : dMin = dMin;
		curD > dMax ? dMax = curD : dMax = dMax;
	}

	

	//cout << "end" << endl;
	int padding = 1;
	int outputHt = rectHeight_ - padding;
	double ratioY = outputHt*1.f / (dMax - dMin);
	//cout << "ratioY: " << ratioY << endl;
	vector<double> newSVec, newDVec;
	//newSVec.reserve(sVec.size());
	newSVec.resize(sVec.size());
	//newDVec.reserve(dVec.size());
	newDVec.resize(dVec.size());
	double maxNewS = INT_MIN;
	for (int i = 0; i < sVec.size(); i++) {
		newSVec[i] = (sVec[i] - sMin)*ratioY;
		newDVec[i] = (dVec[i] - dMin)*ratioY;
		maxNewS = max(maxNewS, newSVec[i]);
	}
	//cout << sMax << " " << sMin << " " << dMax << " " << dMin << endl;
	int outputWd = ceil(maxNewS);
	//cout << outputHt + padding << " " << outputWd + padding << endl;
	Mat dstImg=Mat::zeros(Size(outputWd + padding, outputHt + padding), CV_8U);

	for (int i = 0; i < newSVec.size(); i++) {
		int curX = floor(newSVec[i]);
		int curY = floor(newDVec[i]);
		// cout << curX << "," << curY << "," << colorVec[i] << endl;
		dstImg.at<uchar>(curY, curX) = uchar(colorVec[i]);
		//circle(dstImg, Point(curX, curY), 1, Scalar(colorVec[i]), 2);
	}
	imwrite("result/dstImg.bmp", dstImg);
	dstImg.copyTo(strightImg_);
}

void AutoDetector::Clear()
{
	length_ = 0;
	skeletonPoints_.clear(); 
	skeletonPointsSort_.clear();
}

// Reference: https://github.com/krishraghuram/Zhang-Suen-Skeletonization/blob/master/skeletonization.hpp
void AutoDetector::ThinningIteration(Mat& im, int iter)
{
    Mat marker = Mat::zeros(im.size(), CV_8UC1);

//#pragma omp parallel for schedule(dynamic, 50)
#pragma omp parallel for schedule(dynamic, 50)
    for (int j = 1; j < im.rows-1; j++)
    {
        for (int i = 1; i < im.cols-1; i++)
        {
			if (im.at<uchar>(j, i) == 0)
				continue;
            uchar p2 = im.at<uchar>(j-1, i);
            uchar p3 = im.at<uchar>(j-1, i+1);
            uchar p4 = im.at<uchar>(j, i+1);
            uchar p5 = im.at<uchar>(j+1, i+1);
            uchar p6 = im.at<uchar>(j+1, i);
            uchar p7 = im.at<uchar>(j+1, i-1);
            uchar p8 = im.at<uchar>(j, i-1);
            uchar p9 = im.at<uchar>(j-1, i-1);

            int A  = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) +
                     (p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
                     (p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
                     (p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
            int B  = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
            int m1 = iter == 0 ? (p2 * p4 * p6) : (p2 * p4 * p8);
            int m2 = iter == 0 ? (p4 * p6 * p8) : (p2 * p6 * p8);

            if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
                marker.at<uchar>(j,i) = 1;
        }
    }

    im &= ~marker;
}

void AutoDetector::Thinning(Mat& im)
{
    im /= 255;

    Mat prev = Mat::zeros(im.size(), CV_8UC1);
    Mat diff;
	int cnt = 0;

    do {
        ThinningIteration(im, 0);
        ThinningIteration(im, 1);
        absdiff(im, prev, diff);
        im.copyTo(prev);
		cnt += 2;
    } while (countNonZero(diff) > 0);
    im *= 255;
}


Mat AutoDetector::Skeletonization(Mat inputImage)
{	
    if (inputImage.empty())
    	cout<<"Inside skeletonization, Source empty"<<endl;
	//cout << inputImage.type() << endl;
    Mat outputImage;
	inputImage.copyTo(outputImage);

    Thinning(outputImage);
 	imwrite("result/skeleon.bmp", outputImage);
#if 1
	Mat draw = GetCurrImg();
	for (int u = 0; u < inputImage.cols; ++u) {
		for (int v = 0; v < inputImage.rows; ++v) {
			if (outputImage.at<uchar>(v, u) == 255) {
				//cout << v << "," << u << endl;
				draw.at<Vec3b>(v, u)[2] = 255;
			}
		}
	}
	imwrite("result/skeletonization.bmp", draw);
#endif   
	return outputImage;
}

#define ZHANG_SUEN_SKELETONIZATION
#define EDGE_DILATE

//#define SKELETON_IMSHOW
bool AutoDetector::SkeletonDetect() {
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
	//cout << cols_ << " " << rows_ << endl;
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
		//cout << "layer: " << layer << " point size: " << currEdgeSize << " ratio: " << ratio << endl;
		lastEdgeSize = currEdgeSize;
		vector<Point> tempEdgePoints;
		for (Point point : edgePoints) {
			FillNeighbor(bfsMap, point, layer, tempEdgePoints);
		}
		tempEdgePoints.swap(edgePoints);
		++layer;

		// Check if most of the edges have already shrink
		if (ratio < 0.96) {
#if  0
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

	//cout << "thickness: " << length_ << endl;


#ifdef SKELETON_IMSHOW
	for (Point point : skeletonPoints) {
		draw.at<Vec3b>(point.y, point.x)[2] = 255;
	}
	imshow("draw", draw);
#endif //SKELETON_IMSHOW


#endif // EDGE_DILATE

#ifdef ZHANG_SUEN_SKELETONIZATION
	double timer_start = double(clock() / 1000.0);
	skeletonImg_ = Skeletonization(regionImg_);
	OutputSkeleton();
	if (skeletonPointsSort_.size() < 50)
		return false;

	double timer_mid = double(clock() / 1000.0);
	StraightenImg();
	double timer_end = double(clock() / 1000.0);
	cout << "Skeletonization time use: " << timer_mid - timer_start << " s" << endl;
	cout << "Straighten time use: " << timer_end - timer_mid << " s" << endl;

	//medianBlur(straightenImg_, straightenImg_, 3);
	//GaussianBlur(straightenImg_, straightenImg_, Size(3, 3), 15);
	
	CropImage();
#endif // ZHANG_SUEN_SKELETONIZATION


	ofstream dout1("./strightImg/result.txt", ios::out | ios::app);
	double stdev = DiameterStdCompute(strightImg_, 30);
	dout1 << stdev << endl;
	dout1.close();

	ofstream dout2("./CheckList.txt", ios::out | ios::app);
	if (stdev < 3.5 && stdev > 0) {
		imwrite("./strightImg/" + imgID_ + "_" + to_string(stdev) + ".bmp", strightImg_);
	} else {
		// Wrong stdev image
		if (stdev >= 3.5) {
			dout2 << imgID_ << " " << stdev << " " << filePath_ << endl;
		}
	}
	dout2.close();

	ofstream dout3("./std.txt", ios::out | ios::app);
	if (stdev > 0)
		dout3 << stdev << endl;
	dout3.close();
}

vector<double> AutoDetector::polyfit(vector<Point>& srcPoints)
{
	int size = srcPoints.size();
	//所求未知数个数
	int x_num = levelNum_ + 1;
	Mat mat_u(size, x_num, CV_64F);
	Mat mat_y(size, 1, CV_64F);

	for (int i = 0; i < mat_u.rows; ++i)
		for (int j = 0; j < mat_u.cols; ++j){
			mat_u.at<double>(i, j) = pow(srcPoints[i].x, j);
		}

	for (int i = 0; i < mat_y.rows; ++i){
		mat_y.at<double>(i, 0) = srcPoints[i].y;
	}

	//矩阵运算，获得系数矩阵K
	Mat mat_k(x_num, 1, CV_64F);
	mat_k = (mat_u.t()*mat_u).inv()*mat_u.t()*mat_y;
	//cout << mat_k << endl;
	vector<double> coeffsVec;
	for (int i = 0; i < x_num; i++) {
		coeffsVec.push_back(mat_k.at<double>(i, 0));
	}
	return coeffsVec;
}

void AutoDetector::OutputSkeleton()
{
	Point2i pointStart;
	rows_ = skeletonImg_.rows;
	cols_ = skeletonImg_.cols;
	for (int u = 0; u < cols_; ++u) {
		for (int v = 0; v < rows_; ++v) {
			//cout << skeletonImg_.at<uchar>(v, u) << endl;
			if (skeletonImg_.at<uchar>(v, u) == 0)
				continue;
			int cnt = 0;
			for (pair<int, int> dir : directions) {
				int x = u + dir.first;
				int y = v + dir.second;
				if (x < 0 || x >= cols_ || y < 0 || y >= rows_) {
					continue;
				}
				if (skeletonImg_.at<uchar>(y, x) == 255)
					++cnt;
			}
			if (cnt == 1) {
				pointStart.x = u;
				pointStart.y = v;
				break;
			}
		}
	}

	queue<Point2i> pointQueue;
	pointQueue.push(pointStart);
	skeletonImg_.at<uchar>(pointStart.y, pointStart.x) = 0;
	skeletonPointsSort_.push_back(pointStart);
	int layer = 0;

	while (!pointQueue.empty()) {
		int sz = pointQueue.size();

		for (int i = 0; i < sz; ++i) {
			Point2i currPoint = pointQueue.front();
			pointQueue.pop();

			skeletonPointsSort_.push_back(currPoint);

			for (pair<int, int> dir : directions) {
				int x = currPoint.x + dir.first;
				int y = currPoint.y + dir.second;
				if (x < 0 || x >= cols_ || y < 0 || y >= rows_) {
					continue;
				}
				if (skeletonImg_.at<uchar>(y, x) == 255) {
					Point2i temp;
					temp.x = x;
					temp.y = y;
					pointQueue.push(temp);
					skeletonImg_.at<uchar>(y, x) = 0;
				}
			}
		}
	}
	//cout << "start output" << endl;
	
	// 打印坐标
	/*for (Point2i &p : skeletonPointsSort_) {
		cout << p.y << "," << p.x << endl;
	}*/
}

void AutoDetector::CropImage() {
	cropImgs.clear();
	int straightenWidth = strightImg_.cols;
	
	int x = 0;
	int step = 50;
	int cropCnt = 0;
	while (x + rectWidth_ < straightenWidth) {
		Point topleft(x, 0);
		Point buttomright(x + rectWidth_, rectHeight_);
		Rect cropRect(topleft, buttomright);
		Mat cropImg(strightImg_);
		cropImg(cropRect).copyTo(cropImg);
		
		bool isSuccess = DefectDetection(cropImg);
		//if (!isSuccess && x == 0) {
		//	// Do not save the first image if failed defect detection
		//	x += step;
		//	++cropCnt;
		//	continue;
		//}

		if (cropImg.rows != 50) {
			resize(cropImg, cropImg, Size(50 * rectScale_, 50));
		}
		
		cropImgs.push_back(cropImg);

		string filepath = "./output/" + imgID_ + "_auto_" + to_string(cropImgs.size()) + ".jpg";
		imwrite(filepath, cropImg);
		
		x += step;
		++cropCnt;
	}

	// Ensure odd crops number to avoid ambiguous classify result
	while (cropImgs.size() % 2 == 0) {
		x = (rand() % (straightenWidth - rectWidth_ - 0)) + 0; // [0, straightenWidth - rectWidth_)

		Point topleft(x, 0);
		Point buttomright(x + rectWidth_, rectHeight_);
		Rect cropRect(topleft, buttomright);
		Mat cropImg(strightImg_);
		cropImg(cropRect).copyTo(cropImg);
		
		bool isSuccess = DefectDetection(cropImg);

		if (cropImg.rows != 50) {
			resize(cropImg, cropImg, Size(50 * rectScale_, 50));
		}
		
		cropImgs.push_back(cropImg);

		string filepath = "./output/" + imgID_ + "_auto_" + to_string(cropImgs.size()) + ".jpg";
		imwrite(filepath, cropImg);
	}

}

int AutoDetector::ResNetClassify(string &&filename) {
	torch::jit::script::Module module = torch::jit::load(filename);

	clock_t start, end;
	start = clock();
	std::vector<std::string> type = { "Cashmere", "Wool" };
	int typeNum = type.size();
	int n = cropImgs.size();
	vector<vector<double>> scores(n);
	vector<int> vote(2, 0);
	for (int i = 0; i < n; ++i) {
		//std::string filename = "./input/wool_" + std::to_string(i) + ".jpg";
		//Mat image = imread(filename);
		Mat image = cropImgs[i];
		cvtColor(image, image, COLOR_GRAY2BGR);
		//cout << image.type() << endl;
		resize(image, image, cv::Size(224, 224));
		torch::Tensor img_tensor = torch::from_blob(
			image.data, { 1, image.rows, image.cols, 3 }, torch::kByte);
		img_tensor = img_tensor.permute({ 0, 3, 1, 2 });
		img_tensor = img_tensor.toType(torch::kFloat);
		img_tensor = img_tensor.div(255);
		torch::Tensor output = module.forward({ img_tensor }).toTensor();
		std::cout << "[OUTPUT] " << output << std::endl;
		auto max_result = output.max(1, true);
		auto max_index = std::get<1>(max_result).item<float>();
		std::cout << "[RESULT] " << type[max_index] << std::endl;
		++vote[max_index];
		//for (int j = 0; j < typeNum; ++j) {
		//	scores[i].push_back(output[0][i].item<double>());
		//}
		scores[i].push_back(output[0][0].item<double>());
		scores[i].push_back(output[0][1].item<double>());
		
	}

	if (vote[CASHMERE] == vote[WOOL]) {
		result_ = UNKNOWN;
	} else if (vote[CASHMERE] > vote[WOOL]) {
		result_ = CASHMERE;
	} else {
		result_ = WOOL;
	}



	end = clock();
	std::cout << "Total time use: " << double(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "Average time use: " << double(end - start) / CLOCKS_PER_SEC / n << "s" << std::endl;


	return 0;
}

double AutoDetector::DiameterStdCompute() {
	int slice = 30;
	int straightenWidth = strightImg_.cols;
	int straightenHeight = strightImg_.rows;
	int padding = 30;

	vector<int> diameters;
	for (int i = padding; i < straightenWidth - padding; i += (straightenWidth - 2 * padding) / slice) {
		int firstPixel = -1;
		int lastPixel = -1;
		for (int j = 0; j < straightenHeight; ++j) {
			if (strightImg_.at<uchar>(j, i) == 0)
				continue;
			if (firstPixel < 0)
				firstPixel = j;
			lastPixel = j;
		}
		if (lastPixel <= firstPixel) {
			cerr << "[ERROR] Wrong diameter" << endl;
			continue;
		}
		diameters.push_back(lastPixel - firstPixel);
	}
	
	double sum = std::accumulate(std::begin(diameters), std::end(diameters), 0.0);  
	double mean =  sum / diameters.size();   // Cannot use as diameter
	
	double accum  = 0.0;  
	std::for_each (std::begin(diameters), std::end(diameters), [&](const double d) {  
	    accum  += (d-mean)*(d-mean);  
	});  
	
	double stdev = sqrt(accum/(diameters.size()-1));   

	cout << "std: " << stdev << endl;
	return stdev;
}

double AutoDetector::DiameterStdCompute(Mat img, int slice) {
	int straightenWidth = img.cols;
	int straightenHeight = img.rows;
	int padding = 20;

	medianBlur(img, img, 3);

	vector<int> diameters;
	//cout << "height" << straightenHeight << endl;
	if (straightenWidth < 100 || straightenWidth - 2 * padding < padding)
		return 0.0;
	for (int i = padding; i < straightenWidth - padding; i += (straightenWidth - 2 * padding) / slice) {
		int firstPixel = -1;
		int lastPixel = -1;
		for (int j = 0; j < straightenHeight; ++j) {
			if (img.at<uchar>(j, i) == 0)
				continue;
			if (firstPixel < 0)
				firstPixel = j;
			lastPixel = j;
		}
		if (lastPixel <= firstPixel) {
			cerr << "[ERROR] Wrong diameter" << endl;
			continue;
		}
		diameters.push_back(lastPixel - firstPixel);
	}
	
	double sum = std::accumulate(std::begin(diameters), std::end(diameters), 0.0);  
	double mean =  sum / diameters.size();   // Cannot use as diameter
	
	double accum  = 0.0;  
	std::for_each (std::begin(diameters), std::end(diameters), [&](const double d) {  
	    accum  += (d-mean)*(d-mean);  
	});  
	
	double stdev = sqrt(accum/(diameters.size()-1));   

	cout << "std: " << stdev << endl;

	return stdev;
}

bool AutoDetector::DefectDetection(Mat &img) {
	int cols = img.cols;
	int rows = img.rows;
	int padding = 1;
	int backgroundCnt = 0;
	for (int i = padding; i < cols - padding; ++i) {
		for (int j = padding; j < rows - padding; ++j) {
			if (img.at<uchar>(j, i) != 0)
				continue;
			
			++backgroundCnt;
			//int sumIntensity = 0;
			vector<int> intensities;
			for (pair<int, int> dir : directions) {
				int u = i + dir.first;
				int v = j + dir.second;
				if (img.at<uchar>(v, u) != 0) {
					//sumIntensity += straightenImg_.at<uchar>(v, u);
					intensities.push_back(img.at<uchar>(v, u));
				}
			}
			if (intensities.size() >= 6) {
				sort(intensities.begin(), intensities.end());
				int mid = intensities.size() / 2;
				img.at<uchar>(j, i) = intensities.size() % 2 == 0 ? (intensities[mid] + intensities[mid-1]) / 2 : intensities[mid];
				--backgroundCnt;
			}
		}
	}

	float ratio = (float)(backgroundCnt) / (float)(cols * rows);
	cout << "Backgound ratio: " << ratio << endl;
	if (ratio > 0.4) {
		cout << "------ Fail defect detection -------" << endl;
		return false;
	}
	return true;
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
		skeletonPoints_.emplace_back(Point(x, y));
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

	//cout << temp.size << endl;
	//cout << temp.type() << endl;
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


