#pragma once
#include "BaseDetector.h"


#define POINT_RADIUS 3
#define LINE_THICKNESS 1.8

class ManualDetector : public BaseDetector
{
private:
	double currLength = -1;
	double meanLength = -1;
	double stdLength;

	Mat cacheImg_;

	// Size should be two, store two selected points to calculate length
	vector<Point> selectedPoints;
	static void on_mouse(int event, int x, int y, int flags, void *ustc);

	int numLength = 0;
	double sumLength = 0;
	
public:
	ManualDetector(Ui::CashmereDetectorClass ui) : BaseDetector(ui) {};
	ManualDetector(string filePath, Ui::CashmereDetectorClass ui) : BaseDetector(filePath, ui) {};

	// Register mouse pick event
	void StartPickMode();

	// Cancel registration of mouse pick event
	void EndPickMode();

	// Return reference of selectedPoints, use to store points in call back function
	vector<Point>& GetSelectedPoints();

	// Calculate the distance of two points stored in selectedPoints, and update numLength and sumLength
	double CalcLength();

	// Calculate mean length
	double CalcMeanLength();

	// Reset detector
	void ResetManualDetector();

	double GetCurrLength();
	double GetMeanLength();
	int GetLengthNum();
	~ManualDetector();
};

