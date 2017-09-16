#include "controller.h"
#include <iostream>

using namespace std;

Controller::Controller(QObject *parent) : QObject(parent)
{
    showMenu();
}

void Controller::newGame()
{
   int row, col;
   cout << "Введите размеры игрового поля (количество фишек) : " << endl;
   cin  >> row >> col;
   model = new Puzzle15Model(row, col);
   view = new View(model);
   view->drawBoard();
   connect(this->model, SIGNAL(gameBoardChanged()), view, SLOT(drawBoard()));
   connect(this->model, SIGNAL(puzzleSolved()), view, SLOT(showWinMessage()));
}

void Controller::startGame()
{
    while(!model->isWone)
    {
        cout << "Введите номер фишки: " << endl;
        int cellNumber;
        cin >> cellNumber;
        if(cellNumber == -1) break;
        model->makeMoveByCellNumber(cellNumber);
    }
    showMenu();
}

void Controller::showMenu()
{
    cout << "Для начала новой игры введите 1: " << endl;
    cout << "Для начала выхода введите 0: " << endl;
    int k;
    cin >> k;
    if(k == 1)
    {
        newGame();
        startGame();
    }else
    {
        system("exit");
    }
}
