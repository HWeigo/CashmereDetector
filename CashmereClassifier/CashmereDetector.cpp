#include "CashmereDetector.h"
#include<opencv2/opencv.hpp>
#include<Windows.h>
#include <opencv2/highgui/highgui_c.h>

#include <io.h>
#include <fstream>

CashmereDetector::CashmereDetector(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	connect(ui.pushButton_clear, SIGNAL(clicked()), ui.textBrowser, SLOT(clear()));

	manuDetector_ = new ManualDetector(ui);
	autoDetector_ = new AutoDetector(ui);
	areaDetector_ = new AreaDetector(ui);
	videoDetector_ = new VideoDetector(ui);
	

	ui.resetAction->setEnabled(false);
	
	// Set timer
	fTimer = new QTimer(this);
	fTimer->stop();
	fTimer->setInterval(10); // unit: ms
	connect(fTimer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));

#ifdef AREA_SELECTOR
	// Set slider and spin box
	connect(ui.spin_rotate, SIGNAL(valueChanged(int)), ui.slider_rotate, SLOT(setValue(int)));
	connect(ui.slider_rotate, SIGNAL(valueChanged(int)), ui.spin_rotate, SLOT(setValue(int)));
	ui.slider_rotate->setMinimum(-180);
	ui.spin_rotate->setMinimum(-180);
	ui.slider_rotate->setMaximum(180);
	ui.spin_rotate->setMaximum(180);
	ui.spin_rotate->setValue(0);
	
	connect(ui.spin_selectorSize, SIGNAL(valueChanged(int)), ui.slider_selectorSize, SLOT(setValue(int)));
	connect(ui.slider_selectorSize, SIGNAL(valueChanged(int)), ui.spin_selectorSize, SLOT(setValue(int)));
	ui.slider_selectorSize->setMinimum(0);
	ui.spin_selectorSize->setMinimum(0);
	ui.slider_selectorSize->setMaximum(60);
	ui.spin_selectorSize->setMaximum(60);
	ui.spin_selectorSize->setValue(30);
#endif // AREA_SELECTOR

	// Clear result txt
	ofstream file_writer("./log/result.txt", ios_base::out);
}

void CashmereDetector::on_timer_timeout() {
	if (isPickModeOn_) {
		manuDetector_->ShowCurrImg();
		
		double length = manuDetector_->CalcMeanLength();
		//ui.label_mean->setText("-");
		//ui.label_length->setText("-");
		
		if (manuDetector_->GetLengthNum() > 0 && isPickModeOn_) {
			ui.label_mean->setText(QString::number(manuDetector_->GetMeanLength()));
			ui.label_length->setText(QString::number(manuDetector_->GetCurrLength()));
		}
	} else {
		areaDetector_->ShowCurrImg();
	}

}

void CashmereDetector::wheelEvent(QWheelEvent * event)
{
#ifdef AREA_SELECTOR
	if (!isSelectModeOn_)
		return;
	int val = ui.spin_selectorSize->value();
	int step = 5;
	if (event->delta() > 0) {
		ui.spin_selectorSize->setValue(val + step);
	}
	else {
		ui.spin_selectorSize->setValue(val - step);
	}
	areaDetector_->DrawRactangle();
#endif //AREA_SELECTOR
}

void CashmereDetector::keyPressEvent(QKeyEvent * event){
#ifdef AREA_SELECTOR
	if (event->key() == Qt::Key_Q) {
		int val = ui.spin_rotate->value();
		int step = 5;
		ui.spin_rotate->setValue(val - step);
	}
	else if (event->key() == Qt::Key_E) {
		int val = ui.spin_rotate->value();
		int step = 5;
		ui.spin_rotate->setValue(val + step);
	}
#endif //AREA_SELECTOR
}

// Helper function to sort string in natual order
bool compareNat(const std::string& a, const std::string& b)
{
    if (a.empty())
        return true;
    if (b.empty())
        return false;
    if (std::isdigit(a[0]) && !std::isdigit(b[0]))
        return true;
    if (!std::isdigit(a[0]) && std::isdigit(b[0]))
        return false;
    if (!std::isdigit(a[0]) && !std::isdigit(b[0]))
    {
        if (std::toupper(a[0]) == std::toupper(b[0]))
            return compareNat(a.substr(1), b.substr(1));
        return (std::toupper(a[0]) < std::toupper(b[0]));
    }

    // Both strings begin with digit --> parse both numbers
    std::istringstream issa(a);
    std::istringstream issb(b);
    int ia, ib;
    issa >> ia;
    issb >> ib;
    if (ia != ib)
        return ia < ib;

    // Numbers are the same --> remove numbers and recurse
    std::string anew, bnew;
    std::getline(issa, anew);
    std::getline(issb, bnew);
    return (compareNat(anew, bnew));
}

void getFileNames(string path, vector<string>& files)
{
	//�ļ����
	//ע�⣺�ҷ�����Щ���´���˴���long���ͣ�ʵ�������лᱨ������쳣
	intptr_t hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
        do
        {            
			//�����Ŀ¼,�ݹ����
            //�������,���ļ�����·������vector��
            if ((fileinfo.attrib & _A_SUBDIR))
            {
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFileNames(p.assign(path).append("/").append(fileinfo.name), files);
            }
            else
            {               
				files.push_back(p.assign(path).append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
	}
}

void CashmereDetector::on_openFileAction_image_triggered(bool checked)
{
	QString curPath = QDir::currentPath();
	QString dlgTitle = "���ļ�"; //�Ի������
	QString filter = "jpg�ļ�(*.jpg);;�����ļ�(*.*)"; //�ļ�������
	QString fileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

	if (fileName.isEmpty()) {
		PushMessage("no crop image found");
		return;
	}

	QTextCodec *code = QTextCodec::codecForName("GB2312");//�������·������
	string filePath = code->fromUnicode(fileName).data();


	cout << filePath << endl;

	manuDetector_->LoadImg(filePath);
	autoDetector_->LoadImg(filePath);
	areaDetector_->LoadImg(filePath);
	areaDetector_->ShowCurrImg();

	PushMessage("load crop images");
	fTimer->start();
	ui.resetAction->setEnabled(true);
	ui.label_filename->setText(QString::fromStdString(areaDetector_->GetImgID()));
	
	string filename = BaseDetector::split(filePath, "/").back(); // "home/img/a.jpg" -> {"home", "img", "a.jpg"}
	string root = filePath;
	root.erase(root.end() - filename.size(), root.end());
	cout << "root: " << root << endl;
	filepaths_.clear();
	getFileNames(root, filepaths_);
	// Natural order sort 
	sort(filepaths_.begin(), filepaths_.end(), compareNat);

	//for (const auto &name : m_filepaths) {
	//	cout << name << endl;
	//	if (name == filePath) {
	//		cout << "HERE!!!!" << endl;
	//	}
	//}
	for (int i = 0; i < filepaths_.size(); ++i) {
		if (filePath == filepaths_[i]) {
			currIdx_ = i;
			break;
		}
	}

#ifdef AREA_SELECTOR
	ui.spin_rotate->setValue(0);
#endif
	ui.label_mean->setText("-");
	ui.label_length->setText("-");
	ui.label_std->setText("-");
}

void CashmereDetector::on_pushButton_reset_clicked() {
	if (manuDetector_->GetCurrImgRef().empty())
		return;
	if (isPickModeOn_) {
		manuDetector_->ResetManualDetector();
		return;
	}
	manuDetector_->ResetCurrImg();
}

void CashmereDetector::on_openFileAction_video_triggered(bool checked)
{
	QString curPath = QDir::currentPath();
	QString dlgTitle = "���ļ�"; //�Ի������
	QString filter = "mp4�ļ�(*.mp4);;�����ļ�(*.*)"; //�ļ�������
	QString fileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

	if (fileName.isEmpty())
	{
		return;
	}

	QTextCodec *code = QTextCodec::codecForName("GB2312");//�������·������
	string filePath = code->fromUnicode(fileName).data();


	cout << filePath << endl;
	videoDetector_->LoadVideo(filePath);


	PushMessage("open video file");

}

void CashmereDetector::on_pushButton_pick_clicked() {
	if (manuDetector_->GetCurrImgRef().empty())
		return;

	if (!isPickModeOn_) {
		PushMessage("pick mode on");
		manuDetector_->StartPickMode();
	}
	else {
		PushMessage("pick mode off");
		manuDetector_->EndPickMode();
	}

	isPickModeOn_ = !isPickModeOn_;
}

void CashmereDetector::on_pushButton_autoDetect_clicked() {
	if (autoDetector_->GetCurrImgRef().empty())
		return;

	if (isPickModeOn_) {
		manuDetector_->EndPickMode();
		isPickModeOn_ = false;
	}

	autoDetector_->AutoDetect(ui.checkBox_targetMode->isChecked());

	ui.label_length->setText("-");
	ui.label_mean->setText(QString::number(autoDetector_->GetLength()));
	
	vector<TYPE> results = autoDetector_->GetResults();
	string outputMessage = "classify result:\n";
	vector<string> resultList = { "Cashmere", "Wool", "Unknown" };
	vector<string> resultListOutput = { "����", "��ë", "δ֪" };

	// Output result
	ofstream dout("./log/result.txt", ios::out | ios::app);

	if (results.empty()) {
		string resultMessage;
		dout << autoDetector_->GetImgFilePath() << " ";
		resultMessage += to_string(0) + ": " + resultList[UNKNOWN];
		dout << 0 << ": ";
		dout << resultListOutput[UNKNOWN] << " ";
		ui.label_result->setText(QString::fromStdString(resultMessage));
		outputMessage += resultMessage;
	}
	else {
		int num = results.size();

		string resultMessage;
		dout << autoDetector_->GetImgFilePath() << " ";
		for (int i = 0; i < num; ++i) {
			resultMessage += to_string(i) + ": " + resultList[results[i]];
			resultMessage += "\n";
			dout << i << ": ";
			dout << resultListOutput[results[i]] << " ";
		}
		resultMessage.pop_back();

		ui.label_result->setText(QString::fromStdString(resultMessage));
		outputMessage += resultMessage;
	}
	//ui.label_result->setText(QString::fromStdString(resultList[autoDetector_->GetResult()]));
	//outputMessage += resultList[autoDetector_->GetResult()];

	PushMessage("auto detect done");
	PushMessage(outputMessage);

	//dout << autoDetector_->GetImgFilePath() << " ";
	//dout << resultListOutput[autoDetector_->GetResult()] << endl;
	dout << endl;
	dout.close();
}

void CashmereDetector::on_pushButton_videoProcess_clicked()
{
	int cnt = videoDetector_->VideoAutoCrop(this);
	if (cnt == -1)
		return;
	PushMessage("finish auto crop");
	PushMessage("total: " + to_string(cnt) + " images");
	PushMessage("save files to folder: " + videoDetector_->GetCropsRoot());
}

void CashmereDetector::on_pushButton_loadCropImgs_clicked() {
	string root = videoDetector_->GetCropsRoot();
	cout << "root: " << root << endl;
	filepaths_.clear();
	getFileNames(root, filepaths_);
	if (filepaths_.empty())
		return;
	// Natural order sort 
	sort(filepaths_.begin(), filepaths_.end(), compareNat);

	currIdx_ = 0;
	string filePath = filepaths_[0];

	cout << filePath << endl;

	manuDetector_->LoadImg(filePath);
	autoDetector_->LoadImg(filePath);
	areaDetector_->LoadImg(filePath);
	areaDetector_->ShowCurrImg();

	PushMessage("open image file");
	fTimer->start();
	ui.resetAction->setEnabled(true);
	ui.label_filename->setText(QString::fromStdString(areaDetector_->GetImgID()));
	
#ifdef AREA_SELECTOR
	ui.spin_rotate->setValue(0);
#endif
	ui.label_mean->setText("-");
	ui.label_length->setText("-");
	ui.label_std->setText("-");

}

void CashmereDetector::on_pushButton_scalesDetect_clicked() {
	//Mat curr = autoDetector->GetCurrImg();
	//imshow("t", curr);
	autoDetector_->ScalesDetect();
}

void CashmereDetector::on_pushButton_next_clicked() {
	if (filepaths_.empty())
		return;
	int idx = currIdx_ + 1;
	if (idx >= filepaths_.size())
		return;
	string filePath = filepaths_[idx];
	manuDetector_->LoadImg(filePath);
	autoDetector_->LoadImg(filePath);
	areaDetector_->LoadImg(filePath);
	areaDetector_->ShowCurrImg();

	PushMessage("open file - " + autoDetector_->GetImgID());
	fTimer->start();
	ui.resetAction->setEnabled(true);
	ui.label_filename->setText(QString::fromStdString(areaDetector_->GetImgID()));

#ifdef AREA_SELECTOR
	ui.spin_rotate->setValue(0);
#endif
	ui.label_mean->setText("-");
	ui.label_length->setText("-");
	ui.label_result->setText("-");
	currIdx_ = idx;
}

void CashmereDetector::on_pushButton_back_clicked() {
	if (filepaths_.empty())
		return;
	int idx = currIdx_ - 1;
	if (idx < 0)
		return;
	string filePath = filepaths_[idx];
	manuDetector_->LoadImg(filePath);
	autoDetector_->LoadImg(filePath);
	areaDetector_->LoadImg(filePath);
	areaDetector_->ShowCurrImg();

	PushMessage("open file");
	fTimer->start();
	ui.resetAction->setEnabled(true);
	ui.label_filename->setText(QString::fromStdString(areaDetector_->GetImgID()));

#ifdef AREA_SELECTOR
	ui.spin_rotate->setValue(0);
#endif
	ui.label_mean->setText("-");
	ui.label_length->setText("-");
	ui.label_result->setText("-");
	currIdx_ = idx;
}

void CashmereDetector::on_pushButton_autoNext_clicked() {
	isAutoDetecting_ = true;
	int successCnt = 0, failedCnt = 0;;
	while (currIdx_ < filepaths_.size()) {
		QCoreApplication::processEvents();
		if (!isAutoDetecting_) {
			break;
		}
		string filePath = filepaths_[currIdx_];
		manuDetector_->LoadImg(filePath);
		autoDetector_->LoadImg(filePath);
		areaDetector_->LoadImg(filePath);
		areaDetector_->ShowCurrImg();

		PushMessage("open file: " + autoDetector_->GetImgID());
		ui.resetAction->setEnabled(true);
		ui.label_filename->setText(QString::fromStdString(areaDetector_->GetImgID()));

		if (autoDetector_->AutoDetect(ui.checkBox_targetMode->isChecked())) {
			++successCnt;

			ui.label_length->setText("-");
			ui.label_mean->setText(QString::number(autoDetector_->GetLength()));
			
			vector<TYPE> results = autoDetector_->GetResults();
			string outputMessage = "classify result:\n";
			vector<string> resultList = { "Cashmere", "Wool", "Unknown" };
			vector<string> resultListOutput = { "����", "��ë", "δ֪" };

			// Output result
			ofstream dout("./log/result.txt", ios::out | ios::app);

			if (results.empty()) {
				string resultMessage;
				dout << autoDetector_->GetImgFilePath() << " ";
				resultMessage += to_string(0) + ": " + resultList[UNKNOWN];
				dout << 0 << ": ";
				dout << resultListOutput[UNKNOWN] << " ";
				ui.label_result->setText(QString::fromStdString(resultMessage));
				outputMessage += resultMessage;
			}
			else {
				int num = results.size();

				string resultMessage;
				dout << autoDetector_->GetImgFilePath() << " ";
				for (int i = 0; i < num; ++i) {
					resultMessage += to_string(i) + ": " + resultList[results[i]];
					resultMessage += "\n";
					dout << i << ": ";
					dout << resultListOutput[results[i]] << " ";
				}
				resultMessage.pop_back();

				ui.label_result->setText(QString::fromStdString(resultMessage));
				outputMessage += resultMessage;
			}

			PushMessage("auto detect done");
			PushMessage(outputMessage);

			dout << endl;
			dout.close();

		} else {
			++failedCnt;
			PushMessage("auto detect failed");
		}
		++currIdx_;

		cout << "-------------------------" << currIdx_ << "-------------------------" << endl;
	}
	PushMessage("stop auto detect");
	PushMessage("success: " + to_string(successCnt) + " failed: " + to_string(failedCnt));
	isAutoDetecting_ = false;
	return;
}

void CashmereDetector::on_pushButton_autoBack_clicked() {
	isAutoDetecting_ = true;
	int successCnt = 0, failedCnt = 0;;
	while (currIdx_ >= 0) {
		QCoreApplication::processEvents();
		if (!isAutoDetecting_) {
			PushMessage("stop auto detect");
			return;
		}
		string filePath = filepaths_[currIdx_];
		manuDetector_->LoadImg(filePath);
		autoDetector_->LoadImg(filePath);
		areaDetector_->LoadImg(filePath);
		areaDetector_->ShowCurrImg();

		PushMessage("open file: " + autoDetector_->GetImgID());
		ui.resetAction->setEnabled(true);
		ui.label_filename->setText(QString::fromStdString(areaDetector_->GetImgID()));

		if (autoDetector_->AutoDetect(ui.checkBox_targetMode->isChecked())) {
			++successCnt;

			ui.label_length->setText("-");
			ui.label_mean->setText(QString::number(autoDetector_->GetLength()));
			
			vector<TYPE> results = autoDetector_->GetResults();
			string outputMessage = "classify result:\n";
			vector<string> resultList = { "Cashmere", "Wool", "Unknown" };
			vector<string> resultListOutput = { "����", "��ë", "δ֪" };

			// Output result
			ofstream dout("./log/result.txt", ios::out | ios::app);

			if (results.empty()) {
				string resultMessage;
				dout << autoDetector_->GetImgFilePath() << " ";
				resultMessage += to_string(0) + ": " + resultList[UNKNOWN];
				dout << 0 << ": ";
				dout << resultListOutput[UNKNOWN] << " ";
				ui.label_result->setText(QString::fromStdString(resultMessage));
				outputMessage += resultMessage;
			}
			else {
				int num = results.size();

				string resultMessage;
				dout << autoDetector_->GetImgFilePath() << " ";
				for (int i = 0; i < num; ++i) {
					resultMessage += to_string(i) + ": " + resultList[results[i]];
					resultMessage += "\n";
					dout << i << ": ";
					dout << resultListOutput[results[i]] << " ";
				}
				resultMessage.pop_back();

				ui.label_result->setText(QString::fromStdString(resultMessage));
				outputMessage += resultMessage;
			}

			PushMessage("auto detect done");
			PushMessage(outputMessage);

			dout << endl;
			dout.close();

		} else {
			++failedCnt;
			PushMessage("auto detect failed");
		}
		--currIdx_;

		cout << "-------------------------" << currIdx_ << "-------------------------" << endl;
	}

	PushMessage("stop auto detect");
	PushMessage("success: " + to_string(successCnt) + " failed: " + to_string(failedCnt));
	isAutoDetecting_ = false;
	return;
}

void CashmereDetector::on_pushButton_autoStop_clicked() {
	isAutoDetecting_ = false;
}

void CashmereDetector::on_pushButton_areaSelect_clicked()
{
#ifdef AREA_SELECTOR
	if (areaDetector_->GetCurrImgRef().empty())
		return;

	if (!isSelectModeOn_) {
		PushMessage("select mode on");
		areaDetector_->SetRectSize(ui.spin_selectorSize->value());
		areaDetector_->StartSelectMode();
	}
	else {
		PushMessage("select mode off");
		areaDetector_->EndSelectMode();
	}

	isSelectModeOn_ = !isSelectModeOn_;
#endif
}

void CashmereDetector::on_spin_rotate_valueChanged(int val) {
	areaDetector_->RotateImage(val);
	areaDetector_->ShowCurrImg();
}

void CashmereDetector::on_spin_selectorSize_valueChanged(int val){
	areaDetector_->SetRectSize(val);
}

void CashmereDetector::on_pushButton_saveCurr_clicked() {
	if (manuDetector_->GetCurrImgRef().empty())
		return;
	manuDetector_->SaveCurrImg();
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

void WorkerThread::stop() {
    threadStop = true;
    qDebug("[%d] Thread stop", number);
}

void WorkerThread::run() {
    threadStop = false;
    int i = 0;
 
    while(!threadStop)
    {
        mutex.lock();
        qDebug("[%d] MyThread %d", number, i);
		cout << "thread running " << i << endl;
        i++;
        sleep(1);
        mutex.unlock();
    }
}
