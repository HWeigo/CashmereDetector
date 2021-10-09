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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CashmereDetectorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CashmereDetectorClass)
    {
        if (CashmereDetectorClass->objectName().isEmpty())
            CashmereDetectorClass->setObjectName(QStringLiteral("CashmereDetectorClass"));
        CashmereDetectorClass->resize(600, 400);
        menuBar = new QMenuBar(CashmereDetectorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CashmereDetectorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CashmereDetectorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CashmereDetectorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CashmereDetectorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CashmereDetectorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CashmereDetectorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CashmereDetectorClass->setStatusBar(statusBar);

        retranslateUi(CashmereDetectorClass);

        QMetaObject::connectSlotsByName(CashmereDetectorClass);
    } // setupUi

    void retranslateUi(QMainWindow *CashmereDetectorClass)
    {
        CashmereDetectorClass->setWindowTitle(QApplication::translate("CashmereDetectorClass", "CashmereDetector", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CashmereDetectorClass: public Ui_CashmereDetectorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CASHMEREDETECTOR_H
