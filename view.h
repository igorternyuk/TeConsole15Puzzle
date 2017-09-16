#ifndef VIEW_H
#define VIEW_H
#include "puzzle15model.h"

class View : public QObject
{
  Q_OBJECT

  public:
  View(Puzzle15Model* model, QObject *parent = nullptr);

public slots:
   void drawBoard();
   void showWinMessage();
private:
   Puzzle15Model *model;

};

#endif // VIEW_H
