#ifndef PUZZLE15MODEL_H
#define PUZZLE15MODEL_H
#include <stdlib.h>
#include <vector>
#include <QObject>
#include "defines.h"


class Puzzle15Model : public QObject
{
    Q_OBJECT

public:
    Puzzle15Model(int row = DEFAULT_ROW_COUNT, int col = DEFAULT_COL_COUNT, QObject *parent = nullptr);
    void newGame(int rowCount, int colCount);
    void reset();
    void makeMoveByCellNumber(int id);
    void makeMoveByDirection(Direction dir);
    int getRowCount() const {return rowCount;}
    int getColumnCount() const {return colCount;}
    int getCell(int i, int j) const;
    int getMovesNumber() const {return numberOfMoves;}
    void printBoard();
    bool isWone;
signals:
    void gameBoardChanged();
    void puzzleSolved();
private:
    bool isInLimits(int r, int c) const;
    void generateSetup();
    bool vectorContains(const std::vector<int> &vct, const int &element) const;
    bool isSolvable(const std::vector<int> &vct);
    void makeSolvable(std::vector<int> &vct);
    bool isInRange(int id) const;
    bool isInRange(int x, int y) const;
    bool movePossible(int i, int j);
    int getEmptyCellRow() const {return emptyCell.first;}
    int getEmptyCellCol() const {return emptyCell.second;}
    bool isWin();
private:
    std::vector<std::vector<int>> gameBoard;
    std::pair<int, int> emptyCell;
    int rowCount;
    int colCount;
    int numberOfMoves;
};

#endif // PUZZLE15MODEL_H
