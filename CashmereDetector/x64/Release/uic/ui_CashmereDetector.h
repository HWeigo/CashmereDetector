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
#include <QtWidgets/QHeaderView>
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
    QAction *openFileAction;
    QAction *resetAction;
    QWidget *centralWidget;
    QWidget *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_autoDetect;
    QPushButton *pushButton_pick;
    QSpacerItem *verticalSpacer_2;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_clear;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CashmereDetectorClass)
    {
        if (CashmereDetectorClass->objectName().isEmpty())
            CashmereDetectorClass->setObjectName(QStringLiteral("CashmereDetectorClass"));
        CashmereDetectorClass->resize(1312, 797);
        openFileAction = new QAction(CashmereDetectorClass);
        openFileAction->setObjectName(QStringLiteral("openFileAction"));
        resetAction = new QAction(CashmereDetectorClass);
        resetAction->setObjectName(QStringLiteral("resetAction"));
        centralWidget = new QWidget(CashmereDetectorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(320, 10, 960, 720));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 301, 721));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(7);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_autoDetect = new QPushButton(verticalLayoutWidget);
        pushButton_autoDetect->setObjectName(QStringLiteral("pushButton_autoDetect"));

        verticalLayout->addWidget(pushButton_autoDetect);

        pushButton_pick = new QPushButton(verticalLayoutWidget);
        pushButton_pick->setObjectName(QStringLiteral("pushButton_pick"));

        verticalLayout->addWidget(pushButton_pick);

        verticalSpacer_2 = new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        textBrowser = new QTextBrowser(verticalLayoutWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        pushButton_clear = new QPushButton(verticalLayoutWidget);
        pushButton_clear->setObjectName(QStringLiteral("pushButton_clear"));

        verticalLayout->addWidget(pushButton_clear);

        CashmereDetectorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CashmereDetectorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1312, 26));
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
        textBrowser->setHtml(QApplication::translate("CashmereDetectorClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        pushButton_clear->setText(QApplication::translate("CashmereDetectorClass", "Clear", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("CashmereDetectorClass", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CashmereDetectorClass: public Ui_CashmereDetectorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CASHMEREDETECTOR_H
