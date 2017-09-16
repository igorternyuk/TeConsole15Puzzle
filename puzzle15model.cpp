#include "puzzle15model.h"
#include <time.h>
#include <QObject>
#include <QDebug>

Puzzle15Model::Puzzle15Model(int row, int col, QObject *parent) :
    QObject(parent)
{
    if(isInLimits(row, col))
    {
        rowCount = row;
        colCount = col;
    }else
    {
        row = DEFAULT_ROW_COUNT;
        col = DEFAULT_COL_COUNT;
    }
    reset();
}

void Puzzle15Model::newGame(int row, int col)
{
    rowCount = row;
    colCount = col;
    reset();
}

void Puzzle15Model::reset()
{
    numberOfMoves = 0;
    if(!gameBoard.empty()) gameBoard.clear();
    for(int i = 0; i < getRowCount(); ++i)
    {
        std::vector<int> vTmp;
        for(int j = 0; j < getColumnCount(); ++j)
        {
            vTmp.push_back(0);
        }
        gameBoard.push_back(vTmp);
    }
    isWone = false;
    generateSetup();
}

void Puzzle15Model::makeMoveByCellNumber(int id)
{
    if(isInRange(id))
    {
        for(int i = 0; i < getRowCount(); ++i)
            for(int j = 0; j < getColumnCount(); ++j)
                if(id == getCell(i, j))
                {
                    if(movePossible(i, j))
                    {
                        const int r = getEmptyCellRow();
                        const int c = getEmptyCellCol();
                        gameBoard[r][c] = gameBoard[i][j];
                        gameBoard[i][j] = 0;
                        emptyCell.first = i;
                        emptyCell.second = j;
                        ++numberOfMoves;
                        emit gameBoardChanged();
                        isWin();
                        return;
                     }

                }
    }
}

void Puzzle15Model::makeMoveByDirection(Direction dir)
{
    // Определяем координаты пустой клетки
    int r = getEmptyCellRow();
    int c = getEmptyCellCol();
    int id;
    // И в зависимости от выбранного направления перемещения находим номер нужной фишки
    // и делаем ею ход
    switch(dir)
    {
        case Direction::UP:   id = getCell(r + 1, c);
                              break;
        case Direction::DOWN: id = getCell(r - 1, c);
                              break;
        case Direction::RIGHT:id = getCell(r, c - 1);
                              break;
        case Direction::LEFT: id = getCell(r, c + 1);
                              break;
        default: break;
    }
    makeMoveByCellNumber(id);
}

int Puzzle15Model::getCell(int i, int j) const
{
    return isInRange(i, j) ? gameBoard[i][j] : -1;
}

bool Puzzle15Model::isInLimits(int r, int c) const
{
    return ((r >= MIN_ROW_COUNT) && (r <= MAX_ROW_COUNT) &&
           (c >= MIN_COL_COUNT) && (c <= MAX_COL_COUNT)) ? true : false;
}

void Puzzle15Model::generateSetup()
{
    srand(time(NULL));
    std::vector<int> temp(rowCount * colCount, -1);
    temp[temp.size() - 1] = 0;
    for(int i = 0; i < int(temp.size() - 1); ++i)
    {
        int randNum;
        do
        {
            randNum = rand() % (rowCount * colCount - 1) + 1;
        }while(vectorContains(temp, randNum));
        temp[i] = randNum;
    }
    if(!isSolvable(temp))
        makeSolvable(temp);
    int k = 0;
    if(!gameBoard.empty())
    {
        for(int i = 0; i < rowCount; ++i)
            for(int j = 0; j < colCount; ++j)
                gameBoard[i][j] = temp[k++];
        emptyCell.first = rowCount - 1;
        emptyCell.second = colCount - 1;
    }
}

bool Puzzle15Model::vectorContains(const std::vector<int> &vct, const int &element) const
{
    for(auto e: vct)
        if(e == element) return true;
    return false;
}

bool Puzzle15Model::isSolvable(const std::vector<int> &vct)
{
    int chaosNumber = 0;
    for(int i = 1; i < int(vct.size() - 1); ++i)
        for(int j = 0; j < i; ++j)
        {
            if(vct[j] > vct[i]) ++chaosNumber;
        }
        qDebug() << "Количество беспорядков: " << chaosNumber;
        if((chaosNumber % 2 == 0))
        {
           qDebug() << "Решаемая комбинация";
           return true;
        }
        else
        {
           qDebug() << "Нерешаемая комбинация";
           return false;
        }
}

void Puzzle15Model::makeSolvable(std::vector<int> &vct)
{
    int buf = vct[vct.size() - 2];
    vct[vct.size() - 2] = vct[vct.size() - 3];
    vct[vct.size() - 3] = buf;
    qDebug() << "Сделали комбинацию решаемой";
}

bool Puzzle15Model::isInRange(int id) const
{
    return (id >= 0 && id < getRowCount() * getColumnCount()) ? true : false;
}

bool Puzzle15Model::isInRange(int i, int j) const
{
    return (i >= 0 && i < getRowCount() && j >= 0 && j < getColumnCount()) ? true : false;
}

bool Puzzle15Model::movePossible(int i, int j)
{
    return ((j == getEmptyCellCol() && i == getEmptyCellRow() + 1) ||
            (j == getEmptyCellCol() && i == getEmptyCellRow() - 1) ||
            (i == getEmptyCellRow() && j == getEmptyCellCol() - 1) ||
            (i == getEmptyCellRow() && j == getEmptyCellCol() + 1))  ? true : false;
}

bool Puzzle15Model::isWin()
{
    qDebug() << "Проба на выигрыш!\n";
    int k = 1;
    for(int i = 0; i < getRowCount(); ++i)
        for(int j = 0; j < getColumnCount(); ++j)
        {
            if((i != getRowCount() - 1 || j != getColumnCount() - 1) && gameBoard[i][j] != k++)
                return false;
        }
    emit puzzleSolved();
    isWone = true;
    return true;
}

void Puzzle15Model::printBoard()
{
    for(int i = 0; i < rowCount; ++i)
    {
        qDebug() << "--------------";
        QString str = "";
        for(int j = 0; j < colCount; ++j)
        {
            str += "|" + QString::number(gameBoard[i][j]);
        }
        str += "|";
        qDebug() << str;
    }
    qDebug() << "------------";
}
