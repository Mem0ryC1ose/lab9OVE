#include <QApplication>
#include "mainwindow2.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    if(argc == 2) {
        MainWindow2 mainWindow(atoi(argv[1]));
        mainWindow.show();
        int numberOfIdeas = std::stoi(mainWindow.readFromPipe());
        mainWindow.setNumberOfIdeas(numberOfIdeas);
        std::thread thread1 (&MainWindow2::vote, &mainWindow);
        thread1.detach();
        QApplication::exec();
    }
    return 0;
}
