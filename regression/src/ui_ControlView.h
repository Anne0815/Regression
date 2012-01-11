/********************************************************************************
** Form generated from reading UI file 'ControlView.ui'
**
** Created: Tue 10. Jan 15:44:05 2012
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLVIEW_H
#define UI_CONTROLVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionGenerate;
    QAction *actionSimple;
    QAction *actionOptimal_M;
    QAction *actionLambda;
    QAction *actionCramer_Rule;
    QAction *actionGauss;
    QAction *actionGauss_Big_Number;
    QAction *actionOperator_overload_Big_Float;
    QAction *actionError_Mean_Square;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuData;
    QMenu *menuRegression;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(240, 180);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionGenerate = new QAction(MainWindow);
        actionGenerate->setObjectName(QString::fromUtf8("actionGenerate"));
        actionSimple = new QAction(MainWindow);
        actionSimple->setObjectName(QString::fromUtf8("actionSimple"));
        actionOptimal_M = new QAction(MainWindow);
        actionOptimal_M->setObjectName(QString::fromUtf8("actionOptimal_M"));
        actionLambda = new QAction(MainWindow);
        actionLambda->setObjectName(QString::fromUtf8("actionLambda"));
        actionCramer_Rule = new QAction(MainWindow);
        actionCramer_Rule->setObjectName(QString::fromUtf8("actionCramer_Rule"));
        actionGauss = new QAction(MainWindow);
        actionGauss->setObjectName(QString::fromUtf8("actionGauss"));
        actionGauss_Big_Number = new QAction(MainWindow);
        actionGauss_Big_Number->setObjectName(QString::fromUtf8("actionGauss_Big_Number"));
        actionOperator_overload_Big_Float = new QAction(MainWindow);
        actionOperator_overload_Big_Float->setObjectName(QString::fromUtf8("actionOperator_overload_Big_Float"));
        actionError_Mean_Square = new QAction(MainWindow);
        actionError_Mean_Square->setObjectName(QString::fromUtf8("actionError_Mean_Square"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 240, 21));
        menuData = new QMenu(menubar);
        menuData->setObjectName(QString::fromUtf8("menuData"));
        menuRegression = new QMenu(menubar);
        menuRegression->setObjectName(QString::fromUtf8("menuRegression"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuData->menuAction());
        menubar->addAction(menuRegression->menuAction());
        menuData->addAction(actionOpen);
        menuData->addAction(actionGenerate);
        menuRegression->addAction(actionSimple);
        menuRegression->addAction(actionOptimal_M);
        menuRegression->addAction(actionLambda);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Control", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "open", 0, QApplication::UnicodeUTF8));
        actionGenerate->setText(QApplication::translate("MainWindow", "generate", 0, QApplication::UnicodeUTF8));
        actionSimple->setText(QApplication::translate("MainWindow", "simple", 0, QApplication::UnicodeUTF8));
        actionOptimal_M->setText(QApplication::translate("MainWindow", "optimal M", 0, QApplication::UnicodeUTF8));
        actionLambda->setText(QApplication::translate("MainWindow", "lambda", 0, QApplication::UnicodeUTF8));
        actionCramer_Rule->setText(QApplication::translate("MainWindow", "Cramer Rule", 0, QApplication::UnicodeUTF8));
        actionGauss->setText(QApplication::translate("MainWindow", "Gauss", 0, QApplication::UnicodeUTF8));
        actionGauss_Big_Number->setText(QApplication::translate("MainWindow", "Gauss Big Number", 0, QApplication::UnicodeUTF8));
        actionOperator_overload_Big_Float->setText(QApplication::translate("MainWindow", "Operator Overload Big Float", 0, QApplication::UnicodeUTF8));
        actionError_Mean_Square->setText(QApplication::translate("MainWindow", "Error Mean Square", 0, QApplication::UnicodeUTF8));
        menuData->setTitle(QApplication::translate("MainWindow", "Data", 0, QApplication::UnicodeUTF8));
        menuRegression->setTitle(QApplication::translate("MainWindow", "Regression", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLVIEW_H
