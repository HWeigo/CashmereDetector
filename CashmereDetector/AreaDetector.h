#pragma once
#include "BaseDetector.h"
class AreaDetector :
	public BaseDetector
{
private:
	Mat rotImg_;
	float scale;
	
	static void on_mouse(int event, int x, int y, int flags, void *ustc);

public:
	AreaDetector(Ui::CashmereDetectorClass ui) : BaseDetector(ui) {};
	~AreaDetector();

	// Register mouse select event
	void StartSelectMode();

	// Cancel registration of mouse select event
	void EndSelectMode();

	// Rotate image
	void RotateImage(int deg);

	// Draw rectangle based on center point
	void DrawRectangle(Point center, int width, int height);

	// Compute rectangle's top left and buttom right point
	void ComputeArea(Point center, int width, int height, Point &topleft, Point &buttomright);

};

