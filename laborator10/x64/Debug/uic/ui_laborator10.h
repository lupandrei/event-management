/********************************************************************************
** Form generated from reading UI file 'laborator10.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABORATOR10_H
#define UI_LABORATOR10_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_laborator10Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *laborator10Class)
    {
        if (laborator10Class->objectName().isEmpty())
            laborator10Class->setObjectName(QString::fromUtf8("laborator10Class"));
        laborator10Class->resize(600, 400);
        menuBar = new QMenuBar(laborator10Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        laborator10Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(laborator10Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        laborator10Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(laborator10Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        laborator10Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(laborator10Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        laborator10Class->setStatusBar(statusBar);

        retranslateUi(laborator10Class);

        QMetaObject::connectSlotsByName(laborator10Class);
    } // setupUi

    void retranslateUi(QMainWindow *laborator10Class)
    {
        laborator10Class->setWindowTitle(QCoreApplication::translate("laborator10Class", "laborator10", nullptr));
    } // retranslateUi

};

namespace Ui {
    class laborator10Class: public Ui_laborator10Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABORATOR10_H
