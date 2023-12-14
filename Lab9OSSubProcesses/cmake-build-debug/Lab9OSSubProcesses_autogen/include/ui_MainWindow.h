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
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ProcVoting
{
public:
    QTextEdit *textEdit;
    QPushButton *bProcessVoteYes;
    QPushButton *bProcessVoteNo;

    void setupUi(QDialog *ProcVoting)
    {
        if (ProcVoting->objectName().isEmpty())
            ProcVoting->setObjectName(QString::fromUtf8("ProcVoting"));
        ProcVoting->resize(490, 213);
        textEdit = new QTextEdit(ProcVoting);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 10, 471, 151));
        QFont font;
        font.setPointSize(16);
        textEdit->setFont(font);
        textEdit->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        textEdit->setReadOnly(true);
        bProcessVoteYes = new QPushButton(ProcVoting);
        bProcessVoteYes->setObjectName(QString::fromUtf8("bProcessVoteYes"));
        bProcessVoteYes->setGeometry(QRect(10, 170, 221, 31));
        QFont font1;
        font1.setPointSize(12);
        bProcessVoteYes->setFont(font1);
        bProcessVoteYes->setCursor(QCursor(Qt::PointingHandCursor));
        bProcessVoteNo = new QPushButton(ProcVoting);
        bProcessVoteNo->setObjectName(QString::fromUtf8("bProcessVoteNo"));
        bProcessVoteNo->setGeometry(QRect(240, 170, 241, 31));
        bProcessVoteNo->setFont(font1);
        bProcessVoteNo->setCursor(QCursor(Qt::PointingHandCursor));

        retranslateUi(ProcVoting);

        QMetaObject::connectSlotsByName(ProcVoting);
    } // setupUi

    void retranslateUi(QDialog *ProcVoting)
    {
        ProcVoting->setWindowTitle(QCoreApplication::translate("ProcVoting", "Dialog", nullptr));
        bProcessVoteYes->setText(QCoreApplication::translate("ProcVoting", "Yes", nullptr));
        bProcessVoteNo->setText(QCoreApplication::translate("ProcVoting", "No", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProcVoting: public Ui_ProcVoting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
