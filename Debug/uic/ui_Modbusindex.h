/********************************************************************************
** Form generated from reading UI file 'Modbusindex.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODBUSINDEX_H
#define UI_MODBUSINDEX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModbusindexClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ModbusindexClass)
    {
        if (ModbusindexClass->objectName().isEmpty())
            ModbusindexClass->setObjectName(QString::fromUtf8("ModbusindexClass"));
        ModbusindexClass->resize(639, 353);
        centralWidget = new QWidget(ModbusindexClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(9);
        pushButton->setFont(font);

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font);

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        ModbusindexClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ModbusindexClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 639, 18));
        ModbusindexClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ModbusindexClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ModbusindexClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ModbusindexClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ModbusindexClass->setStatusBar(statusBar);

        retranslateUi(ModbusindexClass);

        QMetaObject::connectSlotsByName(ModbusindexClass);
    } // setupUi

    void retranslateUi(QMainWindow *ModbusindexClass)
    {
        ModbusindexClass->setWindowTitle(QApplication::translate("ModbusindexClass", "Modbusindex", nullptr));
        pushButton->setText(QApplication::translate("ModbusindexClass", "\346\267\273\345\212\240", nullptr));
        pushButton_2->setText(QApplication::translate("ModbusindexClass", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModbusindexClass: public Ui_ModbusindexClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODBUSINDEX_H
