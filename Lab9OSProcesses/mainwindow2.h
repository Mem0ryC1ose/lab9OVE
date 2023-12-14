//
// Created by Admin on 22.11.2022.
//

#ifndef LAB9OSSUBPROCESSES_MAINWINDOW2_H
#define LAB9OSSUBPROCESSES_MAINWINDOW2_H

#include <QWidget>
#include <windows.h>
#include <thread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow2; }
QT_END_NAMESPACE

class MainWindow2 : public QWidget {
Q_OBJECT

public:
    explicit MainWindow2(int id, QWidget *parent = nullptr);
    std::wstring readFromPipe();
    void writeToPipe(const wchar_t* data);
    int getId();
    ~MainWindow2() override;
    void vote();
    void log(const std::string& text);
    void setNumberOfIdeas(int numberOfIdeas);
    void printMsg(std::string tmpString);
private:
    Ui::MainWindow2 *ui;
    HANDLE pipe;
    int id;
    std::vector<std::string> ideas;
    boolean toStopGenerating = false;
    void waitForSignal();
    int numberOfIdeas;
    int ideaNumber = 0;
public slots:
    void setColourDefault();
    void onbProcessVoteYes_clicked();
    void onbProcessVoteNo_clicked();

};


#endif //LAB9OSSUBPROCESSES_MAINWINDOW2_H
