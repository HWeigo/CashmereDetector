#pragma once
#include "BaseDetector.h"
class AreaDetector :
	public BaseDetector
{
public:
	AreaDetector(Ui::CashmereDetectorClass ui) : BaseDetector(ui) {};
	~AreaDetector();

	// Register mouse select event
	void StartSelectMode();

	// Cancel registration of mouse select event
	void EndSelectMode();

};

