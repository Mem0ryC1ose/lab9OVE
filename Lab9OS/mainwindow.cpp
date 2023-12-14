#include <fstream>
#include <sstream>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: rgb(51, 63, 77);");
    connect(ui->bBeginVoting, SIGNAL(clicked(bool)), this, SLOT(beginVotingPushed()));
    connect(ui->bNextIdea, SIGNAL(clicked(bool)), this, SLOT(nextIdea()));

    ui->lBorderLeft->setStyleSheet("color: rgb(95, 146, 222); background-color: rgb(0,0,0); border: 2px solid rgb(95, 146, 222)");
    ui->lBorderLeft->setFont(QFont("Montserrat, 12"));

    ui->lBorderRight->setStyleSheet("color: rgb(95, 146, 222); background-color: rgb(0,0,0); border: 2px solid rgb(95, 146, 222)");
    ui->lBorderLeft->setFont(QFont("Montserrat, 12"));

    ui->bProcessCount->setStyleSheet("color: rgb(95, 146, 222); background-color: rgb(0,0,0);");
    ui->lBorderLeft->setFont(QFont("Montserrat, 12"));

    ui->lProcessCount->setStyleSheet("color: rgb(95, 146, 222); background-color: rgb(0,0,0);");
    ui->lBorderLeft->setFont(QFont("Montserrat, 12"));

    ui->lProcessCount->setStyleSheet("color: rgb(95, 146, 222); background-color: rgb(0,0,0);");
    ui->lBorderLeft->setFont(QFont("Montserrat, 12"));

    ui->bProcessCountSet->setStyleSheet("color: rgb(95, 146, 222); background-color: rgb(0,0,0); border: 2px solid rgb(95, 146, 222)");
    ui->lBorderLeft->setFont(QFont("Montserrat, 12"));

    ui->bBeginVoting->setStyleSheet("color: rgb(95, 146, 222); background-color: rgb(0,0,0); border: 2px solid rgb(95, 146, 222)");
    ui->lBorderLeft->setFont(QFont("Montserrat, 12"));

    ui->bNextIdea->setStyleSheet("color: rgb(95, 146, 222); background-color: rgb(0,0,0); border: 2px solid rgb(95, 146, 222)");
    ui->lBorderLeft->setFont(QFont("Montserrat, 12"));

    ui->textEdit->setStyleSheet("color: rgb(28, 30, 33); background-color: rgb(128, 169, 217); border: 2px solid rgb(95, 146, 222)");
}

MainWindow::~MainWindow()
{
    UnmapViewOfFile(mappingPointer);
    CloseHandle(fileMapping);
    for(std::pair<_PROCESS_INFORMATION, HANDLE> process : processes){
        DisconnectNamedPipe(process.second);
        CloseHandle(process.second);
    }
    delete ui;
}

void MainWindow::startProcesses() {
    HANDLE file = CreateFile(
            L"\\\\.\\mapping\\ideas",
            GENERIC_READ | GENERIC_WRITE,
            0,
            nullptr,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
            );
    fileMapping = CreateFileMapping(
            file,
            nullptr,
            PAGE_READWRITE,
            0,
            50,
            L"ideasMapping"
            );
    mappingPointer = (LPTSTR) MapViewOfFile(
            fileMapping,
            FILE_MAP_ALL_ACCESS,
            0,
            0,
            0
            );
    for(int i = 0; i < mode; i++) {
        STARTUPINFOA si;
        PROCESS_INFORMATION pinfo;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        std::string cmdLine =
                "E://CLionProjects//Lab9OSSubProcesses//cmake-build-debug//Lab9OSSubProcesses.exe " + std::to_string(i);
        char *temp = new char[cmdLine.size()];
        strcpy(temp, cmdLine.c_str());
        CreateProcessA("E://CLionProjects//Lab9OSSubProcesses//cmake-build-debug//Lab9OSSubProcesses.exe",
                       temp,
                       nullptr,
                       nullptr,
                       FALSE,
                       NORMAL_PRIORITY_CLASS,
                       nullptr,
                       nullptr,
                       &si,
                       &pinfo);
        std::string temp3("\\\\.\\pipe\\pipe" + std::to_string(i));
        std::wstring temp2 = std::wstring(temp3.begin(), temp3.end());
        HANDLE pipe = CreateNamedPipeW(temp2.c_str(),
                                       PIPE_ACCESS_DUPLEX,
                                       PIPE_TYPE_MESSAGE,
                                       1,
                                       0,
                                       0,
                                       INFINITE,
                                       nullptr);
        if (pipe == nullptr || pipe == INVALID_HANDLE_VALUE) {
            printMsg("Pipe not created");
            break;
        }
        if (!ConnectNamedPipe(pipe, nullptr)) {
            printMsg("Pipe not connected");
            break;
        }

        processes.emplace_back(pinfo, pipe);
    }
    printMsg("Ideas generating started");
    std::thread thread1(&MainWindow::wait3MinutesAndBeginVote, this);
    thread1.detach();
}
void MainWindow::wait3MinutesAndBeginVote() {
    Sleep(THREE_MINUTES_IN_MILLIS); // Три хвилини на створення ідей
    printMsg("Ideas generating has finished\n---------------------------------------------");
    for(std::pair<_PROCESS_INFORMATION, HANDLE> process : processes){
        writeToPipe(process.second, L"1");
    }
    generatingFinished = true;
}
void MainWindow::beginVotingPushed() {
    if(!generatingFinished) {
        QMessageBox::critical(nullptr, "Error", "Attempted to start voting before idea generating finished");
        return;
    }
    beginVoting();
}
void MainWindow::voteOnCurrentIdea() {
    printIdea((ideas[currentIdea]).first, (ideas[currentIdea]).second, currentIdea + 1);
    for(std::pair<_PROCESS_INFORMATION, HANDLE> process : processes){
        std::wstring messageToWrite(std::wstring(ideas[currentIdea].first.begin(), ideas[currentIdea].first.end()) + L"\nStudent #" + std::to_wstring(ideas[currentIdea].second));
        std::string temp(messageToWrite.begin(), messageToWrite.end());
        writeToPipe(process.second, messageToWrite.c_str());
    }
    votesForIdeas.emplace_back(std::pair(ideas[currentIdea], 0));
    for(int i = 0; i < processes.size(); i++){
        boolean choice = std::stoi(readFromPipe(processes[i].second)) == 1;
        if(choice){
            votesForIdeas[currentIdea].second++;
        }
        buttonStateChanged(choice, i);
    }
    if(currentIdea + 1 == ideas.size()){
        findTop3Ideas();
    }
}
void MainWindow::nextIdea() {
    if(!generatingFinished){
        QMessageBox::critical(nullptr, "Error", "Attempted to go to next idea before idea generating finished");
        return;
    }
    setColourDefault();
    QCoreApplication::processEvents();
    currentIdea++;
    voteOnCurrentIdea();
}
void MainWindow::on_bProcessCountSet_clicked()
{
    //Видаляє старі лейбли у випадку повторого нажаття
    for(int i = 0; i < labelvector.size(); i++)
    {
        labelvector[i]->deleteLater();
    }
    labelvector.clear();


    //Створення та розміщення нових лейблів
    mode = ui->bProcessCount->currentText().toInt();

    int xPos = 36+(608/(mode*2));

    for(int i = 0; i < mode; i++)
    {
        QLabel *label = new QLabel(this);
        labelvector.push_back(label);
        labelvector[i]->setStyleSheet("color: rgb(14, 254, 146); background-color: rgb(0, 0, 0); border: 2px solid rgb(14, 254, 146)");//("color: rgb(14,254,146); background-color: rgb(0,0,0); border: 2px solid rgb(14,254,146)");
        labelvector[i]->setFont(QFont("fixedsys, 12"));
        labelvector[i]->setText(QString::number(i+1));
        labelvector[i]->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        labelvector[i]->setGeometry(xPos, 460, 30, 30);

        QGraphicsDropShadowEffect * dse = new QGraphicsDropShadowEffect();
        dse->setBlurRadius(15);
        dse->setColor(QColor(14, 254, 146));
        dse->setOffset(0);
        labelvector[i]->setGraphicsEffect(dse);

        labelvector[i]->setAutoFillBackground(true);

        labelvector[i]->setVisible(true);

        xPos+=(608/mode);
    }
    startProcesses();
}


void MainWindow::buttonStateChanged(bool tmpState, int tmpIndex)
{
    QGraphicsDropShadowEffect * dse = new QGraphicsDropShadowEffect();
    dse->setBlurRadius(15);
    dse->setOffset(0);
    if(tmpState)
    {
        labelvector[tmpIndex]->setStyleSheet("color: rgb(0, 0, 0); background-color: rgb(44, 219, 73); border: 2px solid rgb(44, 219, 73)");
        dse->setColor(QColor(44, 219, 73));//14,254,146
        labelvector[tmpIndex]->setGraphicsEffect(dse);
    }
    else
    {
        labelvector[tmpIndex]->setStyleSheet("color: rgb(0,0,0); background-color: rgb(219, 44, 91); border: 2px solid rgb(219, 44, 91)");
        dse->setColor(QColor(219, 44, 91));
        labelvector[tmpIndex]->setGraphicsEffect(dse);
    }
}

void MainWindow::printIdea(std::string tmpString, int tmpStudentIndex, int tmpIdeaNumber)
{
    QString tmpQStr = QString::number(tmpIdeaNumber) + ". " + "Student's idea: " + QString::fromStdString(tmpString)
            + "\nStudent's number: " + QString::number(tmpStudentIndex) + "\n";
    ui->textEdit->append(tmpQStr);
}

void MainWindow::printVotingResults(int tmpVoteCount)
{
    QString tmpQStr = "Votes: " + QString::number(tmpVoteCount) + "\n";
    ui->textEdit->append(tmpQStr);
}

void MainWindow::printMsg(std::string tmpString)
{
    ui->textEdit->append(QString::fromStdString(tmpString));
}

void MainWindow::writeToPipe(HANDLE pipe, const wchar_t* data) {
    DWORD bytesWritten = 0;
    WriteFile(
            pipe,
            data,
            wcslen(data) * sizeof(wchar_t),
            &bytesWritten,
            nullptr
    );
}
std::wstring MainWindow::readFromPipe(HANDLE pipe) {
    wchar_t buffer[128];
    DWORD bytesRead = 0;
    ReadFile(
            pipe,
            buffer,
            127 * sizeof(wchar_t ),
            &bytesRead,
            nullptr
    );
    return std::wstring(buffer);
}

void MainWindow::beginVoting() {
    std::string currentIdea;
    std::wstring ideaFromMapping = mappingPointer;
    std::string temp (ideaFromMapping.begin(), ideaFromMapping.end());
    std::istringstream istringstream(temp);
    printMsg("List of all ideas:\n");
    while(std::getline(istringstream, currentIdea)){
        size_t delimiterIndex = currentIdea.find('\t');
        ideas.emplace_back(currentIdea.substr(0, delimiterIndex),
                           atoi(currentIdea.substr(currentIdea.find("ID") + 2, currentIdea.length() - delimiterIndex - 2).c_str()));
        printMsg(ideas[ideas.size() - 1].first + "\nStudent #" + std::to_string(ideas[ideas.size() - 1].second) + "\n");
    }
    QCoreApplication::processEvents();
    printMsg("---------------------------------------------\n");
    for(std::pair<_PROCESS_INFORMATION, HANDLE> process : processes){
        writeToPipe(process.second, std::to_wstring(ideas.size()).c_str());
    }
    voteOnCurrentIdea();
}
void MainWindow::setColourDefault()
{
    for(int i = 0; i < mode; i++)
    {
        labelvector[i]->setStyleSheet("color: rgb(14, 254, 146);");//("color: rgb(14,254,146); background-color: rgb(0,0,0); border: 2px solid rgb(14,254,146)");
    }
}

void MainWindow::findTop3Ideas() {
    std::sort(votesForIdeas.begin(), votesForIdeas.end(), [](const std::pair<std::pair<std::string, int>, int>& first, const std::pair<std::pair<std::string, int>, int>& second){
        return first.second > second.second;
    });
    if(votesForIdeas.size() > 3) {
        votesForIdeas.erase(votesForIdeas.begin() + 3, votesForIdeas.end());
    }
    printMsg("---------------------------------------------\nTop 3 ideas are :\n");
    std::ofstream ofstream("ideasResult.txt");
    for(const std::pair<std::pair<std::string, int>, int>& idea : votesForIdeas){
        std::string result(idea.first.first + " from student #" + std::to_string(idea.first.second) + "\nwith " + std::to_string(idea.second) + " votes\n");
        printMsg(result);
        ofstream << result;
    }
    ofstream.close();
}