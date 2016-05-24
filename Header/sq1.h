#ifndef SQ1_H
#define SQ1_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QPainter>
#include <QGraphicsItem>

class sq1 : public QGraphicsItem
{
public:
    sq1(QString str, int offset, int lay, QStringList face);

    QRectF boundingRect() const; // overriding boundingrect
    QPainterPath shape() const; // overriding shape function
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // overriding paint function
    QColor setBrushColour(QChar);

    float x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8, x9, y9, x10, y10; // co-ordinates for the polygon
    QColor brushColourFace, brushColourLayer, brushColourLayer1; // variable used to change brush colour which fills the polygon
    int blockSize, angleModifier, layer;
};

#endif // SQ1_H
