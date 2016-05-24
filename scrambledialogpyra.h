#ifndef SCRAMBLEDIALOGPYRA_H
#define SCRAMBLEDIALOGPYRA_H

class pyra;

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "pyra.h"


namespace Ui {
class scrambleDialogPyra;
}

class scrambleDialogPyra : public QDialog
{
    Q_OBJECT

public:
    explicit scrambleDialogPyra(QWidget *parent = 0);

    pyra *os6, *os0, *os1, *os2, *os7, *os3, *os4, *os5, *os8;
    pyra *bs6, *bs0, *bs1, *bs2, *bs7, *bs3, *bs4, *bs5, *bs8;
    pyra *ys6, *ys0, *ys1, *ys2, *ys7, *ys3, *ys4, *ys5, *ys8;
    pyra *gs6, *gs0, *gs1, *gs2, *gs7, *gs3, *gs4, *gs5, *gs8;



    ~scrambleDialogPyra();

private:
    Ui::scrambleDialogPyra *ui;
    QGraphicsScene *sceneS;

    void updateScrambleGUI();


};

#endif // SCRAMBLEDIALOGPYRA_H
