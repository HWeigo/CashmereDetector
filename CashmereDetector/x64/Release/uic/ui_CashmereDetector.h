/********************************************************************************
** Form generated from reading UI file 'CashmereDetector.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CASHMEREDETECTOR_H
#define UI_CASHMEREDETECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CashmereDetectorClass
{
public:
    QAction *openFileAction;
    QAction *resetAction;
    QWidget *centralWidget;
    QWidget *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_autoDetect;
    QPushButton *pushButton_pick;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_saveCurr;
    QGridLayout *gridLayout;
    QPushButton *pushButton_saveLength;
    QLabel *label_lengthText;
    QLabel *label_mean;
    QLabel *label_lengthText_2;
    QLabel *label_length;
    QFrame *line;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_areaSelect;
    QLabel *label;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QSlider *slider_rotate;
    QSpinBox *spin_rotate;
    QLabel *label_2;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QSlider *slider_selectorSize;
    QDoubleSpinBox *spin_selectorSize;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_info;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_clear;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CashmereDetectorClass)
    {
        if (CashmereDetectorClass->objectName().isEmpty())
            CashmereDetectorClass->setObjectName(QStringLiteral("CashmereDetectorClass"));
        CashmereDetectorClass->resize(1355, 788);
        openFileAction = new QAction(CashmereDetectorClass);
        openFileAction->setObjectName(QStringLiteral("openFileAction"));
        resetAction = new QAction(CashmereDetectorClass);
        resetAction->setObjectName(QStringLiteral("resetAction"));
        centralWidget = new QWidget(CashmereDetectorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(370, 10, 960, 720));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 332, 822));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(7);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_autoDetect = new QPushButton(verticalLayoutWidget);
        pushButton_autoDetect->setObjectName(QStringLiteral("pushButton_autoDetect"));
        pushButton_autoDetect->setMinimumSize(QSize(330, 0));

        verticalLayout->addWidget(pushButton_autoDetect);

        pushButton_pick = new QPushButton(verticalLayoutWidget);
        pushButton_pick->setObjectName(QStringLiteral("pushButton_pick"));

        verticalLayout->addWidget(pushButton_pick);

        pushButton_reset = new QPushButton(verticalLayoutWidget);
        pushButton_reset->setObjectName(QStringLiteral("pushButton_reset"));

        verticalLayout->addWidget(pushButton_reset);

        pushButton_saveCurr = new QPushButton(verticalLayoutWidget);
        pushButton_saveCurr->setObjectName(QStringLiteral("pushButton_saveCurr"));

        verticalLayout->addWidget(pushButton_saveCurr);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_saveLength = new QPushButton(verticalLayoutWidget);
        pushButton_saveLength->setObjectName(QStringLiteral("pushButton_saveLength"));

        gridLayout->addWidget(pushButton_saveLength, 1, 2, 1, 1);

        label_lengthText = new QLabel(verticalLayoutWidget);
        label_lengthText->setObjectName(QStringLiteral("label_lengthText"));

        gridLayout->addWidget(label_lengthText, 1, 0, 1, 1);

        label_mean = new QLabel(verticalLayoutWidget);
        label_mean->setObjectName(QStringLiteral("label_mean"));

        gridLayout->addWidget(label_mean, 1, 1, 1, 1);

        label_lengthText_2 = new QLabel(verticalLayoutWidget);
        label_lengthText_2->setObjectName(QStringLiteral("label_lengthText_2"));

        gridLayout->addWidget(label_lengthText_2, 0, 0, 1, 1);

        label_length = new QLabel(verticalLayoutWidget);
        label_length->setObjectName(QStringLiteral("label_length"));

        gridLayout->addWidget(label_length, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 3);
        gridLayout->setColumnStretch(2, 1);

        verticalLayout->addLayout(gridLayout);

        line = new QFrame(verticalLayoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        widget_2 = new QWidget(verticalLayoutWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pushButton_areaSelect = new QPushButton(widget_2);
        pushButton_areaSelect->setObjectName(QStringLiteral("pushButton_areaSelect"));

        verticalLayout_2->addWidget(pushButton_areaSelect);

        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        slider_rotate = new QSlider(widget_3);
        slider_rotate->setObjectName(QStringLiteral("slider_rotate"));
        slider_rotate->setMaximum(180);
        slider_rotate->setOrientation(Qt::Horizontal);
        slider_rotate->setTickPosition(QSlider::TicksAbove);

        horizontalLayout->addWidget(slider_rotate);

        spin_rotate = new QSpinBox(widget_3);
        spin_rotate->setObjectName(QStringLiteral("spin_rotate"));
        spin_rotate->setMaximum(180);

        horizontalLayout->addWidget(spin_rotate);


        verticalLayout_2->addWidget(widget_3);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        slider_selectorSize = new QSlider(widget_4);
        slider_selectorSize->setObjectName(QStringLiteral("slider_selectorSize"));
        slider_selectorSize->setValue(53);
        slider_selectorSize->setOrientation(Qt::Horizontal);
        slider_selectorSize->setTickPosition(QSlider::NoTicks);

        horizontalLayout_3->addWidget(slider_selectorSize);

        spin_selectorSize = new QDoubleSpinBox(widget_4);
        spin_selectorSize->setObjectName(QStringLiteral("spin_selectorSize"));

        horizontalLayout_3->addWidget(spin_selectorSize);


        verticalLayout_2->addWidget(widget_4);


        verticalLayout->addWidget(widget_2);

        verticalSpacer_2 = new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, -1, -1, -1);
        horizontalSpacer = new QSpacerItem(110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_info = new QLabel(verticalLayoutWidget);
        label_info->setObjectName(QStringLiteral("label_info"));

        horizontalLayout_2->addWidget(label_info);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_clear = new QPushButton(verticalLayoutWidget);
        pushButton_clear->setObjectName(QStringLiteral("pushButton_clear"));

        horizontalLayout_2->addWidget(pushButton_clear);

        horizontalLayout_2->setStretch(0, 6);
        horizontalLayout_2->setStretch(1, 3);
        horizontalLayout_2->setStretch(2, 1);
        horizontalLayout_2->setStretch(3, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        textBrowser = new QTextBrowser(verticalLayoutWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        CashmereDetectorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CashmereDetectorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1355, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        CashmereDetectorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CashmereDetectorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CashmereDetectorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CashmereDetectorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CashmereDetectorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(openFileAction);
        menuFile->addAction(resetAction);

        retranslateUi(CashmereDetectorClass);
        QObject::connect(pushButton_clear, SIGNAL(clicked()), textBrowser, SLOT(clear()));

        QMetaObject::connectSlotsByName(CashmereDetectorClass);
    } // setupUi

    void retranslateUi(QMainWindow *CashmereDetectorClass)
    {
        CashmereDetectorClass->setWindowTitle(QApplication::translate("CashmereDetectorClass", "CashmereDetector", Q_NULLPTR));
        openFileAction->setText(QApplication::translate("CashmereDetectorClass", "Open File", Q_NULLPTR));
        resetAction->setText(QApplication::translate("CashmereDetectorClass", "Reset", Q_NULLPTR));
        pushButton_autoDetect->setText(QApplication::translate("CashmereDetectorClass", "Auto Detect", Q_NULLPTR));
        pushButton_pick->setText(QApplication::translate("CashmereDetectorClass", "Manual Pick", Q_NULLPTR));
        pushButton_reset->setText(QApplication::translate("CashmereDetectorClass", "Reset Current Image", Q_NULLPTR));
        pushButton_saveCurr->setText(QApplication::translate("CashmereDetectorClass", "Save Current Iamge", Q_NULLPTR));
        pushButton_saveLength->setText(QApplication::translate("CashmereDetectorClass", "Save Data", Q_NULLPTR));
        label_lengthText->setText(QApplication::translate("CashmereDetectorClass", "mean: ", Q_NULLPTR));
        label_mean->setText(QString());
        label_lengthText_2->setText(QApplication::translate("CashmereDetectorClass", "length: ", Q_NULLPTR));
        label_length->setText(QString());
        pushButton_areaSelect->setText(QApplication::translate("CashmereDetectorClass", "Area Select", Q_NULLPTR));
        label->setText(QApplication::translate("CashmereDetectorClass", "- Rotation -", Q_NULLPTR));
        label_2->setText(QApplication::translate("CashmereDetectorClass", "- Selector Size -", Q_NULLPTR));
        label_info->setText(QApplication::translate("CashmereDetectorClass", "Info", Q_NULLPTR));
        pushButton_clear->setText(QApplication::translate("CashmereDetectorClass", "Clear", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("CashmereDetectorClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("CashmereDetectorClass", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CashmereDetectorClass: public Ui_CashmereDetectorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CASHMEREDETECTOR_H
