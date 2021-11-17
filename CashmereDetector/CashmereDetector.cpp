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
	areaDetector = new AreaDetector(ui);


	ui.resetAction->setEnabled(false);
	//ui.pushButton_autoDetect->setEnabled(false);
	// Set timer
	fTimer = new QTimer(this);
	fTimer->stop();
	fTimer->setInterval(10); // unit: ms
	connect(fTimer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
	connect(ui.spin_rotate, SIGNAL(valueChanged(int)), ui.slider_rotate, SLOT(setValue(int)));
	connect(ui.slider_rotate, SIGNAL(valueChanged(int)), ui.spin_rotate, SLOT(setValue(int)));

}

void CashmereDetector::on_timer_timeout() {
	if (isPickModeOn) {
		manuDetector->ShowCurrImg();
		
		double length = manuDetector->CalcMeanLength();
		//ui.label_mean->setText("-");
		//ui.label_length->setText("-");
		
		if (manuDetector->GetLengthNum() > 0 && isPickModeOn) {
			ui.label_mean->setText(QString::number(manuDetector->GetMeanLength()));
			ui.label_length->setText(QString::number(manuDetector->GetCurrLength()));
		}
	}
	else {
		areaDetector->ShowCurrImg();
	}

}

void CashmereDetector::on_openFileAction_triggered(bool checked)
{
	QString curPath = QDir::currentPath();
	QString dlgTitle = "打开文件"; //对话框标题
	QString filter = "jpg文件(*.jpg);;所有文件(*.*)"; //文件过滤器
	QString fileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

	if (fileName.isEmpty())
	{
		return;
	}

	QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
	string filePath = code->fromUnicode(fileName).data();


	cout << filePath << endl;

	manuDetector->LoadImg(filePath);
	autoDetector->LoadImg(filePath);
	areaDetector->LoadImg(filePath);
	areaDetector->ShowCurrImg();

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

void CashmereDetector::on_pushButton_areaSelect_clicked()
{
	if (areaDetector->GetCurrImgRef().empty())
		return;

	if (!isSelectModeOn) {
		PushMessage("select mode on");
		areaDetector->StartSelectMode();
	}
	else {
		PushMessage("select mode off");
		areaDetector->EndSelectMode();
	}

	isSelectModeOn = !isSelectModeOn;

}

void CashmereDetector::on_spin_rotate_valueChanged(int val) {
	areaDetector->RotateImage(val);
	areaDetector->ShowCurrImg();
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