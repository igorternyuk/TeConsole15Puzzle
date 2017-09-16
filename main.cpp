#include <QCoreApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Controller *controller = new Controller(0);
    controller->startGame();
    return a.exec();
}
