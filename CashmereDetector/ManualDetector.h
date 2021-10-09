#pragma once
#include "BaseDetector.h"

class ManualDetector : public BaseDetector
{
private:
	double meanLength;
	double stdLength;

	vector<Point> selectedPoints;
	static void on_mouse(int event, int x, int y, int flags, void *ustc);
	
public:
	ManualDetector(Ui::CashmereDetectorClass ui) : BaseDetector(ui) {};
	ManualDetector(string filePath, Ui::CashmereDetectorClass ui) : BaseDetector(filePath, ui) {};


	void StartPickMode();
	void EndPickMode();

	~ManualDetector();
};

