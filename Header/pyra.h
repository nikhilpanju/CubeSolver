#ifndef PYRA_H
#define PYRA_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "solverpyra.h"
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QPainter>
#include <QGraphicsItem>

void updateGUIVariables();

class pyra : public QGraphicsItem
{

public:
    pyra(float a, float b, bool inv); // constructor

    QRectF boundingRect() const; // overriding boundingrect
    QPainterPath shape() const; // overriding shape function so that clickable area is a triangle
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // overriding paint function
    void updateState(QString state, QChar col);

    bool isPressed, isInverted; // variables that check if mouse button is pressed and if triangle should be inverted
    float x1, y1, x2, y2, x3, y3; // co-ordinates for the triangle
    char cP; // stores the value of the colour applied to the triangle
    QColor sP; // variable used to change brush colour which fills the triangle

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PYRA_H
