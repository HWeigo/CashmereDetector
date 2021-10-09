#pragma once
#include "BaseDetector.h"

class ManualDetector : public BaseDetector
{
private:
	double meanLength;
	double stdLength;
	
public:
	ManualDetector(Ui::CashmereDetectorClass ui) : BaseDetector(ui) {};
	ManualDetector(string filePath, Ui::CashmereDetectorClass ui) : BaseDetector(filePath, ui) {};


	void StartPickMode();

	~ManualDetector();
};

