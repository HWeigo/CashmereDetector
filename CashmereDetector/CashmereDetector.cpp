#include "CashmereDetector.h"
#include<opencv2/opencv.hpp>
#include<Windows.h>
#include <opencv2/highgui/highgui_c.h>

CashmereDetector::CashmereDetector(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	connect(ui.pushButton_clear, SIGNAL(clicked()), ui.textBrowser, SLOT(clear()));

	manuDetector = new ManualDetector(ui);
	autoDetector = new AutoDetector(ui);

	ui.resetAction->setEnabled(false);
	//ui.pushButton_autoDetect->setEnabled(false);
	// Set timer
	fTimer = new QTimer(this);
	fTimer->stop();
	fTimer->setInterval(10); // unit: ms
	connect(fTimer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));

}

void CashmereDetector::on_timer_timeout() {
	manuDetector->ShowCurrImg();
	
	double length = manuDetector->CalcMeanLength();
	//ui.label_mean->setText("-");
	//ui.label_length->setText("-");
	
	if (manuDetector->GetLengthNum() > 0 && isPickModeOn) {
		ui.label_mean->setText(QString::number(manuDetector->GetMeanLength()));
		ui.label_length->setText(QString::number(manuDetector->GetCurrLength()));
	}



}

void CashmereDetector::on_openFileAction_triggered(bool checked)
{
	QString curPath = QDir::currentPath();
	QString dlgTitle = "���ļ�"; //�Ի������
	QString filter = "jpg�ļ�(*.jpg);;�����ļ�(*.*)"; //�ļ�������
	QString fileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

	if (fileName.isEmpty())
	{
		return;
	}

	QTextCodec *code = QTextCodec::codecForName("GB2312");//�������·������
	string filePath = code->fromUnicode(fileName).data();


	cout << filePath << endl;

	manuDetector->LoadImg(filePath);
	autoDetector->LoadImg(filePath);
	manuDetector->ShowCurrImg();

	PushMessage("open file");
	fTimer->start();
	ui.resetAction->setEnabled(true);


	ui.label_mean->setText("-");
	ui.label_length->setText("-");
}

void CashmereDetector::on_pushButton_reset_clicked() {
	if (manuDetector->GetCurrImgRef().empty())
		return;
	if (isPickModeOn) {
		manuDetector->ResetManualDetector();
		return;
	}
	manuDetector->ResetCurrImg();
}

void CashmereDetector::on_pushButton_pick_clicked() {
	if (manuDetector->GetCurrImgRef().empty())
		return;

	if (!isPickModeOn) {
		PushMessage("pick mode on");
		manuDetector->StartPickMode();
	}
	else {
		PushMessage("pick mode off");
		manuDetector->EndPickMode();
	}

	isPickModeOn = !isPickModeOn;
}


void CashmereDetector::on_pushButton_autoDetect_clicked() {
	if (autoDetector->GetCurrImgRef().empty())
		return;

	if (isPickModeOn) {
		manuDetector->EndPickMode();
		isPickModeOn = false;
	}
	autoDetector->AutoDetect();

	ui.label_length->setText("-");
	ui.label_mean->setText(QString::number(autoDetector->GetLength()));
	
	PushMessage("auto detect done");
}

void CashmereDetector::on_pushButton_scalesDetect_clicked() {
	//Mat curr = autoDetector->GetCurrImg();
	//imshow("t", curr);
	autoDetector->ScalesDetect();
}

void CashmereDetector::on_pushButton_saveCurr_clicked() {
	if (manuDetector->GetCurrImgRef().empty())
		return;
	manuDetector->SaveCurrImg();
}

void CashmereDetector::PushMessage(string msg)
{
	ui.textBrowser->moveCursor(QTextCursor::End);

	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("hh:mm:ss: ");
	ui.textBrowser->insertPlainText(current_date);

	if (msg.back() != '\n')
		msg += '\n';
	QString qmsg = QString::fromStdString(msg);
	ui.textBrowser->insertPlainText(qmsg);
}