#include "CashmereDetector.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CashmereDetector w;
	w.show();
	return a.exec();
}

