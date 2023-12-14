//
// Created by Admin on 22.11.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow2.h" resolved

#include "mainwindow2.h"
#include "D:\unik\OS\lab9\Lab9OSSubProcesses\cmake-build-debug\Lab9OSSubProcesses_autogen\include\ui_MainWindow2.h"
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <mutex>

std::mutex ideasMutex;


MainWindow2::MainWindow2(int id, QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow2) {
    ui->setupUi(this);
    connect(ui->bProcessVoteYes, SIGNAL(clicked(bool)), this, SLOT(onbProcessVoteYes_clicked()));
    connect(ui->bProcessVoteNo, SIGNAL(clicked(bool)), this, SLOT(onbProcessVoteNo_clicked()));
    this->setStyleSheet("background-color: rgb(51, 63, 77);");

    ui->bProcessVoteYes->setStyleSheet("color: rgb(28, 30, 33); background-color: rgb(0,0,0); border: 2px solid rgb(28, 30, 33)");
    ui->bProcessVoteYes->setFont(QFont("fixedsys, 12"));

    ui->bProcessVoteNo->setStyleSheet("color: rgb(28, 30, 33); background-color: rgb(0,0,0); border: 2px solid rgb(28, 30, 33)");
    ui->bProcessVoteNo->setFont(QFont("fixedsys, 12"));

    ui->textEdit->setStyleSheet("color: rgb(28, 30, 33); background-color: rgb(128, 169, 217); border: 2px solid rgb(28, 30, 33)");
    this->id = id;
    std::string temp3(R"(\\.\pipe\pipe)" + std::to_string(id));
    std::wstring temp2 = std::wstring(temp3.begin(), temp3.end());
    pipe = CreateFile(temp2.c_str(),
                      GENERIC_READ | GENERIC_WRITE,
                      FILE_SHARE_READ | FILE_SHARE_WRITE,
                      nullptr,
                      OPEN_EXISTING,
                      FILE_ATTRIBUTE_NORMAL,
                      nullptr);

    srand(time(nullptr) + id);
    std::ifstream ifstream(R"(E:\CLionProjects\Lab9OSSubProcesses\ideasBase.txt)");
    std::string currentIdea;
    while(std::getline(ifstream, currentIdea)){
        ideasMutex.lock();
        ideas.push_back(currentIdea);
        ideasMutex.unlock();
    }
    if(ideas.empty()){
        QMessageBox::critical(nullptr, "Error", "Empty ideas base file");
    }
    ifstream.close();
    std::thread waitingThread(&MainWindow2::waitForSignal, this);
    waitingThread.detach();
    HANDLE fileMapping = CreateFileMapping(
            fileMapping,
            nullptr,
            PAGE_READWRITE,
            0,
            50,
            L"ideasMapping"
            );
    LPCTSTR fileMappingPointer = (LPTSTR) MapViewOfFile(
            fileMapping,
            FILE_MAP_WRITE,
            0,
            0,
            0
            );
    while(true){
        if(toStopGenerating){
            break;
        }
        std::wstring ideaFromMapping = fileMappingPointer;
        std::string ideaString = ideas[rand() % ideas.size()] + "\tID" + std::to_string(id) + "\n";
        std::wstring idea (ideaString.begin(), ideaString.end());
        CopyMemory((PVOID) (fileMappingPointer + ideaFromMapping.size()), idea.c_str(), sizeof(wchar_t ) * idea.size());
        Sleep((rand() % 5000) + 2500);
    }
    UnmapViewOfFile(fileMappingPointer);
    CloseHandle(fileMapping);
}

MainWindow2::~MainWindow2() {
    CloseHandle(pipe);
    delete ui;
}

std::wstring MainWindow2::readFromPipe() {
    wchar_t buffer[128];
    DWORD bytesRead = 0;
    ReadFile(
            pipe,
            buffer,
            127 * sizeof(wchar_t ),
            &bytesRead,
            nullptr
    );
    buffer[bytesRead / sizeof(wchar_t )] = '\0';
    return std::wstring(buffer);
}

void MainWindow2::waitForSignal() {
    readFromPipe();
    toStopGenerating = true;
}

void MainWindow2::log(const std::string& text) {
    std::ofstream ofstream("log" + std::to_string(id) + ".txt", std::ios_base::app);
    ofstream << text << std::endl;
    ofstream.close();
}
void MainWindow2::writeToPipe(const wchar_t* data) {
    DWORD bytesWritten = 0;
    WriteFile(
            pipe,
            data,
            wcslen(data) * sizeof(wchar_t),
            &bytesWritten,
            nullptr
    );
}

int MainWindow2::getId() {
    return id;
}
void MainWindow2::onbProcessVoteYes_clicked()
{
    ideaNumber++;
    writeToPipe(L"1");
    ui->bProcessVoteYes->setStyleSheet("color: rgb(0,0,0); background-color: rgb(219, 44, 91); border: 2px solid rgb(219, 44, 91)");

    ui->bProcessVoteNo->setEnabled(false);
    ui->bProcessVoteYes->setEnabled(false);
    if(ideaNumber == numberOfIdeas){
        this->close();
    }else{
        std::wstring messageToDisplay = readFromPipe();
        printMsg(std::string(messageToDisplay.begin(), messageToDisplay.end()));
        setColourDefault();
    }
}
void MainWindow2::onbProcessVoteNo_clicked()
{
    ui->bProcessVoteNo->setStyleSheet("color: rgb(0, 0, 0); background-color: rgb(44, 219, 73); border: 2px solid rgb(44, 219, 73)");
    ideaNumber++;
    writeToPipe(L"0");
    ui->bProcessVoteNo->setEnabled(false);
    ui->bProcessVoteYes->setEnabled(false);
    if(ideaNumber == numberOfIdeas){
        this->close();
    }else{
        std::wstring messageToDisplay = readFromPipe();
        printMsg(std::string(messageToDisplay.begin(), messageToDisplay.end()));
        setColourDefault();
    }
}
void MainWindow2::setColourDefault()
{
    ui->bProcessVoteYes->setStyleSheet("color: rgb(14,254,146); background-color: rgb(0,0,0); border: 2px solid rgb(14,254,146)");
    ui->bProcessVoteNo->setStyleSheet("color: rgb(14,254,146); background-color: rgb(0,0,0); border: 2px solid rgb(14,254,146)");

    ui->bProcessVoteNo->setEnabled(true);
    ui->bProcessVoteYes->setEnabled(true);
}

void MainWindow2::vote() {
    std::wstring messageToDisplay = readFromPipe();
    printMsg(std::string(messageToDisplay.begin(), messageToDisplay.end()));
    setColourDefault();
}

void MainWindow2::setNumberOfIdeas(int numberOfIdeas) {
    this->numberOfIdeas = numberOfIdeas;
}
void MainWindow2::printMsg(std::string tmpString)
{
    log(tmpString);
    ui->textEdit->append(QString::fromStdString(tmpString));
}