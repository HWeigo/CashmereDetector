#pragma once

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QStandardItem>
#include <QDateTime>
#include <QFileDialog>
#include <QTextCodec>
#include <QFormLayout>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QColorDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QTimer>

#include <iostream>

//#include <QtWidgets/QMainWindow>
#include "ui_CashmereDetector.h"

#include "BaseDetector.h"
#include "ManualDetector.h"
#include "AutoDetector.h"

using namespace std;

class CashmereDetector : public QMainWindow
{
    Q_OBJECT

public:
    CashmereDetector(QWidget *parent = Q_NULLPTR);

	void PushMessage(string msg);

public slots:
	void on_openFileAction_triggered(bool checked);
	//void on_resetAction_triggered();
	void on_pushButton_pick_clicked();
	void on_pushButton_autoDetect_clicked();
	void on_pushButton_reset_clicked();
	void on_pushButton_saveCurr_clicked();
	void on_pushButton_scalesDetect_clicked();
	void on_timer_timeout();

private:
    Ui::CashmereDetectorClass ui;
	ManualDetector *manuDetector = nullptr;
	AutoDetector *autoDetector = nullptr;

	QTimer *fTimer; // Qt timer

	bool isPickModeOn = false;
};
