/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *bProcessCount;
    QPushButton *bProcessCountSet;
    QLabel *lBorderLeft;
    QLabel *lBorderRight;
    QLabel *lProcessCount;
    QPushButton *bBeginVoting;
    QPushButton *bNextIdea;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(712, 558);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        bProcessCount = new QComboBox(centralwidget);
        bProcessCount->addItem(QString());
        bProcessCount->addItem(QString());
        bProcessCount->addItem(QString());
        bProcessCount->addItem(QString());
        bProcessCount->setObjectName(QString::fromUtf8("bProcessCount"));
        bProcessCount->setGeometry(QRect(160, 500, 51, 31));
        QFont font;
        font.setPointSize(14);
        bProcessCount->setFont(font);
        bProcessCount->setCursor(QCursor(Qt::PointingHandCursor));
        bProcessCount->setLayoutDirection(Qt::LeftToRight);
        bProcessCount->setMaxVisibleItems(4);
        bProcessCount->setInsertPolicy(QComboBox::NoInsert);
        bProcessCountSet = new QPushButton(centralwidget);
        bProcessCountSet->setObjectName(QString::fromUtf8("bProcessCountSet"));
        bProcessCountSet->setGeometry(QRect(220, 500, 151, 31));
        QFont font1;
        font1.setPointSize(12);
        bProcessCountSet->setFont(font1);
        bProcessCountSet->setCursor(QCursor(Qt::PointingHandCursor));
        lBorderLeft = new QLabel(centralwidget);
        lBorderLeft->setObjectName(QString::fromUtf8("lBorderLeft"));
        lBorderLeft->setGeometry(QRect(20, 460, 31, 31));
        lBorderLeft->setFont(font1);
        lBorderLeft->setFrameShape(QFrame::WinPanel);
        lBorderLeft->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lBorderRight = new QLabel(centralwidget);
        lBorderRight->setObjectName(QString::fromUtf8("lBorderRight"));
        lBorderRight->setGeometry(QRect(660, 460, 31, 31));
        lBorderRight->setFont(font1);
        lBorderRight->setFrameShape(QFrame::WinPanel);
        lProcessCount = new QLabel(centralwidget);
        lProcessCount->setObjectName(QString::fromUtf8("lProcessCount"));
        lProcessCount->setGeometry(QRect(20, 500, 131, 31));
        lProcessCount->setFont(font);
        lProcessCount->setFrameShape(QFrame::WinPanel);
        lProcessCount->setAlignment(Qt::AlignCenter);
        bBeginVoting = new QPushButton(centralwidget);
        bBeginVoting->setObjectName(QString::fromUtf8("bBeginVoting"));
        bBeginVoting->setGeometry(QRect(380, 500, 151, 31));
        bBeginVoting->setFont(font1);
        bBeginVoting->setCursor(QCursor(Qt::PointingHandCursor));
        bNextIdea = new QPushButton(centralwidget);
        bNextIdea->setObjectName(QString::fromUtf8("bNextIdea"));
        bNextIdea->setGeometry(QRect(540, 500, 151, 31));
        bNextIdea->setFont(font1);
        bNextIdea->setCursor(QCursor(Qt::PointingHandCursor));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 10, 671, 441));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(24);
        textEdit->setFont(font2);
        textEdit->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        textEdit->setReadOnly(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 712, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        bProcessCount->setItemText(0, QCoreApplication::translate("MainWindow", "2", nullptr));
        bProcessCount->setItemText(1, QCoreApplication::translate("MainWindow", "4", nullptr));
        bProcessCount->setItemText(2, QCoreApplication::translate("MainWindow", "8", nullptr));
        bProcessCount->setItemText(3, QCoreApplication::translate("MainWindow", "16", nullptr));

        bProcessCountSet->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        lBorderLeft->setText(QCoreApplication::translate("MainWindow", "->", nullptr));
        lBorderRight->setText(QCoreApplication::translate("MainWindow", "<-", nullptr));
        lProcessCount->setText(QCoreApplication::translate("MainWindow", "Process count", nullptr));
        bBeginVoting->setText(QCoreApplication::translate("MainWindow", "Begin voting", nullptr));
        bNextIdea->setText(QCoreApplication::translate("MainWindow", "Next idea", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
