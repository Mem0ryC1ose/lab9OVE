/********************************************************************************
** Form generated from reading UI file 'mainwindow2.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW2_H
#define UI_MAINWINDOW2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow2
{
public:
    QTextEdit *textEdit;
    QPushButton *bProcessVoteYes;
    QPushButton *bProcessVoteNo;

    void setupUi(QWidget *MainWindow2)
    {
        if (MainWindow2->objectName().isEmpty())
            MainWindow2->setObjectName(QString::fromUtf8("MainWindow2"));
        MainWindow2->resize(490, 213);
        textEdit = new QTextEdit(MainWindow2);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 10, 471, 151));
        QFont font;
        font.setPointSize(16);
        textEdit->setFont(font);
        textEdit->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        textEdit->setReadOnly(true);
        bProcessVoteYes = new QPushButton(MainWindow2);
        bProcessVoteYes->setObjectName(QString::fromUtf8("bProcessVoteYes"));
        bProcessVoteYes->setEnabled(false);
        bProcessVoteYes->setGeometry(QRect(10, 170, 221, 31));
        QFont font1;
        font1.setPointSize(12);
        bProcessVoteYes->setFont(font1);
        bProcessVoteYes->setCursor(QCursor(Qt::PointingHandCursor));
        bProcessVoteNo = new QPushButton(MainWindow2);
        bProcessVoteNo->setObjectName(QString::fromUtf8("bProcessVoteNo"));
        bProcessVoteNo->setEnabled(false);
        bProcessVoteNo->setGeometry(QRect(240, 170, 241, 31));
        bProcessVoteNo->setFont(font1);
        bProcessVoteNo->setCursor(QCursor(Qt::PointingHandCursor));

        retranslateUi(MainWindow2);

        QMetaObject::connectSlotsByName(MainWindow2);
    } // setupUi

    void retranslateUi(QWidget *MainWindow2)
    {
        MainWindow2->setWindowTitle(QCoreApplication::translate("MainWindow2", "Dialog", nullptr));
        bProcessVoteYes->setText(QCoreApplication::translate("MainWindow2", "Yes", nullptr));
        bProcessVoteNo->setText(QCoreApplication::translate("MainWindow2", "No", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow2: public Ui_MainWindow2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW2_H
