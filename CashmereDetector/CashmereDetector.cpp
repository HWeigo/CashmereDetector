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

	manuDetector = new ManualDetector(ui);
	autoDetector = new AutoDetector(ui);
	areaDetector = new AreaDetector(ui);


	ui.resetAction->setEnabled(false);
	
	// Set timer
	fTimer = new QTimer(this);
	fTimer->stop();
	fTimer->setInterval(10); // unit: ms
	connect(fTimer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));

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
	//ui.slider_selectorSize->setSingleStep(5);
	//ui.spin_selectorSize->setSingleStep(5);
	ui.spin_selectorSize->setValue(30);
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

void CashmereDetector::wheelEvent(QWheelEvent * event)
{
	if (!isSelectModeOn)
		return;
	int val = ui.spin_selectorSize->value();
	int step = 5;
	if (event->delta() > 0) {
		ui.spin_selectorSize->setValue(val + step);
	}
	else {
		ui.spin_selectorSize->setValue(val - step);
	}
	areaDetector->DrawRactangle();
}

void CashmereDetector::keyPressEvent(QKeyEvent * event){
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
	//文件句柄
	//注意：我发现有些文章代码此处是long类型，实测运行中会报错访问异常
	intptr_t hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
        do
        {            
			//如果是目录,递归查找
            //如果不是,把文件绝对路径存入vector中
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
	ui.label_filename->setText(QString::fromStdString(areaDetector->GetImgID()));
	
	if (m_filepaths.empty()) {
		string filename = BaseDetector::split(filePath, "/").back(); // "home/img/a.jpg" -> {"home", "img", "a.jpg"}
		string root = filePath;
		root.erase(root.end() - filename.size(), root.end());
		cout << "root: " << root << endl;
		getFileNames(root, m_filepaths);
		// Natural order sort 
		sort(m_filepaths.begin(), m_filepaths.end(), compareNat);

		//for (const auto &name : m_filepaths) {
		//	cout << name << endl;
		//	if (name == filePath) {
		//		cout << "HERE!!!!" << endl;
		//	}
		//}
		for (int i = 0; i < m_filepaths.size(); ++i) {
			if (filePath == m_filepaths[i]) {
				m_currIdx = i;
				break;
			}
		}
	}

	ui.spin_rotate->setValue(0);
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

void CashmereDetector::on_pushButton_next_clicked() {
	if (m_filepaths.empty())
		return;
	int idx = m_currIdx + 1;
	if (idx >= m_filepaths.size())
		return;
	string filePath = m_filepaths[idx];
	manuDetector->LoadImg(filePath);
	autoDetector->LoadImg(filePath);
	areaDetector->LoadImg(filePath);
	areaDetector->ShowCurrImg();

	PushMessage("open file");
	fTimer->start();
	ui.resetAction->setEnabled(true);
	ui.label_filename->setText(QString::fromStdString(areaDetector->GetImgID()));
	ui.spin_rotate->setValue(0);
	ui.label_mean->setText("-");
	ui.label_length->setText("-");
	m_currIdx = idx;
}

void CashmereDetector::on_pushButton_back_clicked() {
	if (m_filepaths.empty())
		return;
	int idx = m_currIdx - 1;
	if (idx < 0)
		return;
	string filePath = m_filepaths[idx];
	manuDetector->LoadImg(filePath);
	autoDetector->LoadImg(filePath);
	areaDetector->LoadImg(filePath);
	areaDetector->ShowCurrImg();

	PushMessage("open file");
	fTimer->start();
	ui.resetAction->setEnabled(true);
	ui.label_filename->setText(QString::fromStdString(areaDetector->GetImgID()));
	ui.spin_rotate->setValue(0);
	ui.label_mean->setText("-");
	ui.label_length->setText("-");
	m_currIdx = idx;

}

void CashmereDetector::on_pushButton_areaSelect_clicked()
{
	if (areaDetector->GetCurrImgRef().empty())
		return;

	if (!isSelectModeOn) {
		PushMessage("select mode on");
		areaDetector->SetRectSize(ui.spin_selectorSize->value());
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

void CashmereDetector::on_spin_selectorSize_valueChanged(int val){
	areaDetector->SetRectSize(val);
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