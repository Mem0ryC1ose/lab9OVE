#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QRectF>
#include <QGraphicsDropShadowEffect>
#include <vector>
#include <windows.h>
#include <thread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startProcesses();
    void beginVoting();

private slots:

    void on_bProcessCountSet_clicked();



public slots:
    void beginVotingPushed();
    void voteOnCurrentIdea();
    void nextIdea();
    //Для зміни кольору лейблу студента, приймає стан (0 для червоного кольору, 1 для зеленого) і індекс студента для доступу до лейблу
    void buttonStateChanged(bool tmpState, int tmpIndex);

    //Для виводу ідеї на екран, приймає назву ідеї, індекс студня, а також порядковий номер ідеї для виводу
    void printIdea(std::string tmpString, int tmpStudentIndex, int tmpIdeaNumber);

    //Для додаткового виводу голосів (етап голосування)
    void printVotingResults(int tmpVoteCount);

    //Для виводу повідомлень, таких як закінчення етапу пропонування голосів
    void printMsg(std::string tmpString);
    void setColourDefault();
    void findTop3Ideas();

private:
    const int THREE_MINUTES_IN_MILLIS = 8000;//TODO change in prod to 180000
    void wait3MinutesAndBeginVote();
    boolean toTerminateWaiting = false;
    boolean generatingFinished = false;
    Ui::MainWindow *ui;

    //Містить всі лейбли зі студнями
    std::vector<QLabel*> labelvector;
    HANDLE fileMapping;
    LPTSTR mappingPointer;
    //Містить к-кість процесів (ака студнів)
    int mode;
    std::vector<std::pair<_PROCESS_INFORMATION, HANDLE>> processes;
    int currentIdea = 0;
    std::vector<std::pair<std::string, int>> ideas;
    std::vector<std::pair<std::pair<std::string, int>, int>> votesForIdeas;
    void writeToPipe(HANDLE pipe, const wchar_t* data);
    std::wstring readFromPipe(HANDLE pipe);
};
#endif // MAINWINDOW_H
