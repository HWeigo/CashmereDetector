#pragma once
#include "BaseDetector.h"
class AreaDetector :
	public BaseDetector
{
private:
	Mat rotImg_;
	int cropCnt = 0;

	float rectScale_ = 2.5;
	int rectWidth_;
	int rectHeight_;

	Point lastPoint_;
	
	static void on_mouse(int event, int x, int y, int flags, void *ustc);

public:
	AreaDetector(Ui::CashmereDetectorClass ui) : BaseDetector(ui) {};
	~AreaDetector();

	// Register mouse select event
	void StartSelectMode();

	// Cancel registration of mouse select event
	void EndSelectMode();

	// Overwrite load image
	void LoadImg(string filepath);

	// Rotate image
	void RotateImage(int deg);

	// Draw rectangle based on center point
	void DrawRactangle();
	void DrawRectangle(Point center);
	void DrawRectangle(Point center, int width, int height);

	// Crop image in original image
	void CropRectangle(Point center);
	void CropRectangle(string filepath, Point center);

	// Compute rectangle's top left and buttom right point
	void ComputeArea(Point center, int width, int height, Point &topleft, Point &buttomright);

	void SetRectSize(int height);
	int GetRectHeight();
	int GetRectWidth();
};

