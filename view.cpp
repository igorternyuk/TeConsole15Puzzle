#include "view.h"
#include <iostream>
#include <string.h>
using namespace std;

View::View(Puzzle15Model *model, QObject *parent) :
    QObject(parent)
{
    this->model = model;
}

void View::drawBoard()
{
    for(int i = 0; i < model->getRowCount(); ++i)
    {
        cout << "------------\n";
        string str = "";
        for(int j = 0; j < model->getColumnCount(); ++j)
        {
            int tmp = model->getCell(i,j);
            if(tmp > 0 && tmp <= 9)
                str += "| " + QString::number(model->getCell(i,j)).toStdString();
            else if(tmp != 0)
                str += "|" + QString::number(model->getCell(i,j)).toStdString();
            else
                str += "|  ";
        }
        str += "|\n";
        cout << str;
    }
    cout << "------------\n";
    cout << "Количество ходов: " << model->getMovesNumber() << endl;
}

void View::showWinMessage()
{
    cout << "Вы выиграли!!!" << endl;
    cout << "Количество ходов : " << model->getMovesNumber() << endl;
}
