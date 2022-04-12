/********************************************************************************
** Form generated from reading UI file 'CashmereClassifier.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CASHMERECLASSIFIER_H
#define UI_CASHMERECLASSIFIER_H

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

class Ui_CashmereClassifierClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CashmereClassifierClass)
    {
        if (CashmereClassifierClass->objectName().isEmpty())
            CashmereClassifierClass->setObjectName(QStringLiteral("CashmereClassifierClass"));
        CashmereClassifierClass->resize(600, 400);
        menuBar = new QMenuBar(CashmereClassifierClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CashmereClassifierClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CashmereClassifierClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CashmereClassifierClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CashmereClassifierClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CashmereClassifierClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CashmereClassifierClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CashmereClassifierClass->setStatusBar(statusBar);

        retranslateUi(CashmereClassifierClass);

        QMetaObject::connectSlotsByName(CashmereClassifierClass);
    } // setupUi

    void retranslateUi(QMainWindow *CashmereClassifierClass)
    {
        CashmereClassifierClass->setWindowTitle(QApplication::translate("CashmereClassifierClass", "CashmereClassifier", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CashmereClassifierClass: public Ui_CashmereClassifierClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CASHMERECLASSIFIER_H
