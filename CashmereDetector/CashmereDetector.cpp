#include "CashmereDetector.h"
#include<opencv2/opencv.hpp>
#include<Windows.h>
#include <opencv2/highgui/highgui_c.h>

CashmereDetector::CashmereDetector(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	ui.resetAction->setEnabled(false);
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
	//if (detector != nullptr) {
	//	delete detector;
	//	detector = nullptr;
	//}

	if (detector == nullptr) {
		detector = new BaseDetector(filePath, ui);
		detector->ShowImage_QWidget();
	}
	else {
		detector->Reset(filePath);
	}
	PushMessage("open file");
	ui.resetAction->setEnabled(true);

}

void CashmereDetector::on_resetAction_triggered(bool checked) {
	//delete detector;
	//detector = nullptr;
}

void CashmereDetector::on_pushButton_pick_clicked() {
	PushMessage("pick mode");
	detector->StartPickMode();
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