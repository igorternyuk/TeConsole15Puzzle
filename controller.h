#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include "puzzle15model.h"
#include "view.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QObject *parent = nullptr);
    //virtual ~Controller();
public slots:
    void newGame();
    void startGame();
    void showMenu();
private:
    Puzzle15Model *model;
    View *view;
};

#endif // CONTROLLER_H
