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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CashmereDetectorClass
{
public:
    QAction *openFileAction_image;
    QAction *resetAction;
    QAction *openFileAction_video;
    QWidget *centralWidget;
    QWidget *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *label_videoProcess;
    QFrame *line_3;
    QPushButton *pushButton_pick;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_saveCurr;
    QGridLayout *gridLayout;
    QLabel *label_lengthText;
    QLabel *label_mean;
    QLabel *label_lengthText_2;
    QLabel *label_length;
    QLabel *label_lengthText_3;
    QPushButton *pushButton_saveLength;
    QLabel *label_std;
    QFrame *line;
    QFrame *line_2;
    QPushButton *pushButton_autoDetect;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLabel *label_result;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_info;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_clear;
    QTextBrowser *textBrowser;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_back;
    QPushButton *pushButton_autoBack;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_autoStop;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_autoNext;
    QPushButton *pushButton_next;
    QLabel *label_filename;
    QLabel *label_filename_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CashmereDetectorClass)
    {
        if (CashmereDetectorClass->objectName().isEmpty())
            CashmereDetectorClass->setObjectName(QStringLiteral("CashmereDetectorClass"));
        CashmereDetectorClass->resize(1355, 860);
        openFileAction_image = new QAction(CashmereDetectorClass);
        openFileAction_image->setObjectName(QStringLiteral("openFileAction_image"));
        resetAction = new QAction(CashmereDetectorClass);
        resetAction->setObjectName(QStringLiteral("resetAction"));
        openFileAction_video = new QAction(CashmereDetectorClass);
        openFileAction_video->setObjectName(QStringLiteral("openFileAction_video"));
        centralWidget = new QWidget(CashmereDetectorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(350, 50, 960, 720));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 332, 781));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(7);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_videoProcess = new QPushButton(verticalLayoutWidget);
        label_videoProcess->setObjectName(QStringLiteral("label_videoProcess"));

        verticalLayout->addWidget(label_videoProcess);

        line_3 = new QFrame(verticalLayoutWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

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
        label_lengthText = new QLabel(verticalLayoutWidget);
        label_lengthText->setObjectName(QStringLiteral("label_lengthText"));
        label_lengthText->setMinimumSize(QSize(0, 29));

        gridLayout->addWidget(label_lengthText, 1, 0, 1, 1);

        label_mean = new QLabel(verticalLayoutWidget);
        label_mean->setObjectName(QStringLiteral("label_mean"));

        gridLayout->addWidget(label_mean, 1, 1, 1, 1);

        label_lengthText_2 = new QLabel(verticalLayoutWidget);
        label_lengthText_2->setObjectName(QStringLiteral("label_lengthText_2"));
        label_lengthText_2->setMinimumSize(QSize(0, 29));

        gridLayout->addWidget(label_lengthText_2, 0, 0, 1, 1);

        label_length = new QLabel(verticalLayoutWidget);
        label_length->setObjectName(QStringLiteral("label_length"));

        gridLayout->addWidget(label_length, 0, 1, 1, 1);

        label_lengthText_3 = new QLabel(verticalLayoutWidget);
        label_lengthText_3->setObjectName(QStringLiteral("label_lengthText_3"));
        label_lengthText_3->setMinimumSize(QSize(0, 29));

        gridLayout->addWidget(label_lengthText_3, 2, 0, 1, 1);

        pushButton_saveLength = new QPushButton(verticalLayoutWidget);
        pushButton_saveLength->setObjectName(QStringLiteral("pushButton_saveLength"));

        gridLayout->addWidget(pushButton_saveLength, 2, 2, 1, 1);

        label_std = new QLabel(verticalLayoutWidget);
        label_std->setObjectName(QStringLiteral("label_std"));

        gridLayout->addWidget(label_std, 2, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 3);
        gridLayout->setColumnStretch(2, 1);

        verticalLayout->addLayout(gridLayout);

        line = new QFrame(verticalLayoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        line_2 = new QFrame(verticalLayoutWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        pushButton_autoDetect = new QPushButton(verticalLayoutWidget);
        pushButton_autoDetect->setObjectName(QStringLiteral("pushButton_autoDetect"));
        pushButton_autoDetect->setMinimumSize(QSize(330, 0));

        verticalLayout->addWidget(pushButton_autoDetect);

        widget_7 = new QWidget(verticalLayoutWidget);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        horizontalLayout_5 = new QHBoxLayout(widget_7);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(widget_7);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(140, 16777215));

        horizontalLayout_5->addWidget(label_3);

        label_result = new QLabel(widget_7);
        label_result->setObjectName(QStringLiteral("label_result"));

        horizontalLayout_5->addWidget(label_result);


        verticalLayout->addWidget(widget_7);

        verticalSpacer_2 = new QSpacerItem(20, 67, QSizePolicy::Minimum, QSizePolicy::Expanding);

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

        widget_5 = new QWidget(centralWidget);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setGeometry(QRect(350, 0, 961, 50));
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton_back = new QPushButton(widget_5);
        pushButton_back->setObjectName(QStringLiteral("pushButton_back"));

        horizontalLayout_4->addWidget(pushButton_back);

        pushButton_autoBack = new QPushButton(widget_5);
        pushButton_autoBack->setObjectName(QStringLiteral("pushButton_autoBack"));

        horizontalLayout_4->addWidget(pushButton_autoBack);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        pushButton_autoStop = new QPushButton(widget_5);
        pushButton_autoStop->setObjectName(QStringLiteral("pushButton_autoStop"));

        horizontalLayout_4->addWidget(pushButton_autoStop);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        pushButton_autoNext = new QPushButton(widget_5);
        pushButton_autoNext->setObjectName(QStringLiteral("pushButton_autoNext"));

        horizontalLayout_4->addWidget(pushButton_autoNext);

        pushButton_next = new QPushButton(widget_5);
        pushButton_next->setObjectName(QStringLiteral("pushButton_next"));

        horizontalLayout_4->addWidget(pushButton_next);

        label_filename = new QLabel(centralWidget);
        label_filename->setObjectName(QStringLiteral("label_filename"));
        label_filename->setGeometry(QRect(830, 770, 111, 28));
        label_filename->setAlignment(Qt::AlignCenter);
        label_filename_2 = new QLabel(centralWidget);
        label_filename_2->setObjectName(QStringLiteral("label_filename_2"));
        label_filename_2->setGeometry(QRect(720, 770, 111, 28));
        label_filename_2->setAlignment(Qt::AlignCenter);
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
        menuFile->addAction(openFileAction_image);
        menuFile->addAction(openFileAction_video);
        menuFile->addAction(resetAction);

        retranslateUi(CashmereDetectorClass);
        QObject::connect(pushButton_clear, SIGNAL(clicked()), textBrowser, SLOT(clear()));

        QMetaObject::connectSlotsByName(CashmereDetectorClass);
    } // setupUi

    void retranslateUi(QMainWindow *CashmereDetectorClass)
    {
        CashmereDetectorClass->setWindowTitle(QApplication::translate("CashmereDetectorClass", "CashmereDetector", Q_NULLPTR));
        openFileAction_image->setText(QApplication::translate("CashmereDetectorClass", "\346\211\223\345\274\200\345\233\276\347\211\207", Q_NULLPTR));
        resetAction->setText(QApplication::translate("CashmereDetectorClass", "\351\207\215\347\275\256\346\226\207\344\273\266", Q_NULLPTR));
        openFileAction_video->setText(QApplication::translate("CashmereDetectorClass", "\346\211\223\345\274\200\350\247\206\351\242\221", Q_NULLPTR));
        label_videoProcess->setText(QApplication::translate("CashmereDetectorClass", "\345\233\276\345\203\217\350\207\252\345\212\250\351\207\207\351\233\206", Q_NULLPTR));
        pushButton_pick->setText(QApplication::translate("CashmereDetectorClass", "\347\233\264\345\276\204\346\265\213\351\207\217", Q_NULLPTR));
        pushButton_reset->setText(QApplication::translate("CashmereDetectorClass", "\351\207\215\347\275\256\345\233\276\345\203\217", Q_NULLPTR));
        pushButton_saveCurr->setText(QApplication::translate("CashmereDetectorClass", "\344\277\235\345\255\230\345\233\276\345\203\217", Q_NULLPTR));
        label_lengthText->setText(QApplication::translate("CashmereDetectorClass", "\345\271\263\345\235\207\347\233\264\345\276\204: ", Q_NULLPTR));
        label_mean->setText(QString());
        label_lengthText_2->setText(QApplication::translate("CashmereDetectorClass", "\346\265\213\351\207\217\347\233\264\345\276\204: ", Q_NULLPTR));
        label_length->setText(QString());
        label_lengthText_3->setText(QApplication::translate("CashmereDetectorClass", "\345\210\206\345\270\203\346\226\271\345\267\256: ", Q_NULLPTR));
        pushButton_saveLength->setText(QApplication::translate("CashmereDetectorClass", "Save Data", Q_NULLPTR));
        label_std->setText(QString());
        pushButton_autoDetect->setText(QApplication::translate("CashmereDetectorClass", "AI\345\233\276\345\203\217\350\257\206\345\210\253", Q_NULLPTR));
        label_3->setText(QApplication::translate("CashmereDetectorClass", "AI\347\273\274\345\220\210\351\242\204\346\265\213\347\273\223\346\236\234\357\274\232", Q_NULLPTR));
        label_result->setText(QApplication::translate("CashmereDetectorClass", "-", Q_NULLPTR));
        label_info->setText(QApplication::translate("CashmereDetectorClass", "\344\277\241\346\201\257", Q_NULLPTR));
        pushButton_clear->setText(QApplication::translate("CashmereDetectorClass", "\346\270\205\347\251\272", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("CashmereDetectorClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        pushButton_back->setText(QApplication::translate("CashmereDetectorClass", "\345\211\215\344\270\200\345\274\240", Q_NULLPTR));
        pushButton_autoBack->setText(QApplication::translate("CashmereDetectorClass", "\350\207\252\345\212\250\345\220\216\346\273\232", Q_NULLPTR));
        pushButton_autoStop->setText(QApplication::translate("CashmereDetectorClass", "\346\232\202\345\201\234", Q_NULLPTR));
        pushButton_autoNext->setText(QApplication::translate("CashmereDetectorClass", "\350\207\252\345\212\250\345\211\215\346\273\232", Q_NULLPTR));
        pushButton_next->setText(QApplication::translate("CashmereDetectorClass", "\344\270\213\344\270\200\345\274\240", Q_NULLPTR));
        label_filename->setText(QApplication::translate("CashmereDetectorClass", "-", Q_NULLPTR));
        label_filename_2->setText(QApplication::translate("CashmereDetectorClass", "\345\275\223\345\211\215\346\226\207\344\273\266\357\274\232", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("CashmereDetectorClass", "\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CashmereDetectorClass: public Ui_CashmereDetectorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CASHMEREDETECTOR_H
