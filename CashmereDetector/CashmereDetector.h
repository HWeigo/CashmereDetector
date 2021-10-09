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

#include <iostream>

//#include <QtWidgets/QMainWindow>
#include "ui_CashmereDetector.h"

#include "BaseDetector.h"

using namespace std;

class CashmereDetector : public QMainWindow
{
    Q_OBJECT

public:
    CashmereDetector(QWidget *parent = Q_NULLPTR);

	void PushMessage(string msg);

public slots:
	void on_openFileAction_triggered(bool checked);
	void on_resetAction_triggered(bool checked);
	void on_pushButton_pick_clicked();

private:
    Ui::CashmereDetectorClass ui;
	BaseDetector *detector;
};
