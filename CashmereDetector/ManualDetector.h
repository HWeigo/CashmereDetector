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
	vector<Point> selectedPoints;
	static void on_mouse(int event, int x, int y, int flags, void *ustc);

	int numLength = 0;
	double sumLength = 0;
	
public:
	ManualDetector(Ui::CashmereDetectorClass ui) : BaseDetector(ui) {};
	ManualDetector(string filePath, Ui::CashmereDetectorClass ui) : BaseDetector(filePath, ui) {};


	void StartPickMode();
	void EndPickMode();
	vector<Point>& GetSelectedPoints();
	double CalcLength();
	double CalcMeanLength();
	void ResetManualDetector();

	double GetCurrLength();
	double GetMeanLength();
	int GetLengthNum();
	~ManualDetector();
};

