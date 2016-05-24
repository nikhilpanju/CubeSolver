#include "../Header/scrambledialogpyra.h"
#include "ui_scrambledialogpyra.h"

// Initialize the scramble variables which store the scrambled state of the cube
QString yellowFaceP_scramble = "yyyyyyyyy", greenFaceP_scramble = "ggggggggg",
            blueFaceP_scramble = "bbbbbbbbb", orangeFaceP_scramble = "ooooooooo";

scrambleDialogPyra::scrambleDialogPyra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scrambleDialogPyra)
{
    ui->setupUi(this);

    // x is base length of triangle, y is height, g is gap and m alters x value for each face
    float x = 66, y = 57, g = 5, m = 5;

    // create a scene to add triangles to
    sceneS = new QGraphicsScene(this);

    // add scene to the graphicsView
    ui->graphicsViewS->setScene(sceneS);

    // for smooth lines
    ui->graphicsViewS->setRenderHint(QPainter::Antialiasing);

    // the rectangle encompassing the scene is the size of the bounding rectangle of the 4 faces
    sceneS->setSceneRect(0, 0, (9*x + 20*g), (6*y + 9*g));

    // orange face initialization
    os6 = new pyra(m + (1.5*x + 2*g), 2*g, false);
    sceneS->addItem(os6);

    os0 = new pyra(m + (x + g), (y + 3*g), false);
    sceneS->addItem(os0);

    os1 = new pyra(m + (1.5*x + 2*g), (y + 3*g), true);
    sceneS->addItem(os1);

    os2 = new pyra(m + (2*x + 3*g), (y + 3*g), false);
    sceneS->addItem(os2);

    os7 = new pyra(m + (0.5*x), (2*y + 4*g), false);
    sceneS->addItem(os7);

    os3 = new pyra(m + (x + g), (2*y + 4*g), true);
    sceneS->addItem(os3);

    os4 = new pyra(m + (1.5*x + 2*g), (2*y + 4*g), false);
    sceneS->addItem(os4);

    os5 = new pyra(m + (2*x + 3*g), (2*y + 4*g), true);
    sceneS->addItem(os5);

    os8 = new pyra(m + (2.5*x + 4*g), (2*y + 4*g), false);
    sceneS->addItem(os8);

    m += (3*x + 7*g);

    // green face initialization
    gs6 = new pyra(m + (1.5*x + 2*g), 2*g, false);
    sceneS->addItem(gs6);

    gs0 = new pyra(m + (x + g), (y + 3*g), false);
    sceneS->addItem(gs0);

    gs1 = new pyra(m + (1.5*x + 2*g), (y + 3*g), true);
    sceneS->addItem(gs1);

    gs2 = new pyra(m + (2*x + 3*g), (y + 3*g), false);
    sceneS->addItem(gs2);

    gs7 = new pyra(m + (0.5*x), (2*y + 4*g), false);
    sceneS->addItem(gs7);

    gs3 = new pyra(m + (x + g), (2*y + 4*g), true);
    sceneS->addItem(gs3);

    gs4 = new pyra(m + (1.5*x + 2*g), (2*y + 4*g), false);
    sceneS->addItem(gs4);

    gs5 = new pyra(m + (2*x + 3*g), (2*y + 4*g), true);
    sceneS->addItem(gs5);

    gs8 = new pyra(m + (2.5*x + 4*g), (2*y + 4*g), false);
    sceneS->addItem(gs8);

    // yellow face initialization
    ys6 = new pyra(m + (0.5*x), (3*y + 6*g), true);
    sceneS->addItem(ys6);

    ys0 = new pyra(m + (x + g), (3*y + 6*g), false);
    sceneS->addItem(ys0);

    ys1 = new pyra(m + (1.5*x + 2*g), (3*y + 6*g), true);
    sceneS->addItem(ys1);

    ys2 = new pyra(m + (2*x + 3*g), (3*y + 6*g), false);
    sceneS->addItem(ys2);

    ys7 = new pyra(m + (2.5*x + 4*g), (3*y + 6*g), true);
    sceneS->addItem(ys7);

    ys3 = new pyra(m + (x + g), (4*y + 7*g), true);
    sceneS->addItem(ys3);

    ys4 = new pyra(m + (1.5*x + 2*g), (4*y + 7*g), false);
    sceneS->addItem(ys4);

    ys5 = new pyra(m + (2*x + 3*g), (4*y + 7*g), true);
    sceneS->addItem(ys5);

    ys8 = new pyra(m + (1.5*x + 2*g), (5*y + 8*g), true);
    sceneS->addItem(ys8);

    m += (3*x + 7*g);

    // blue face initialization
    bs6 = new pyra(m + (1.5*x + 2*g), 2*g, false);
    sceneS->addItem(bs6);

    bs0 = new pyra(m + (x + g), (y + 3*g), false);
    sceneS->addItem(bs0);

    bs1 = new pyra(m + (1.5*x + 2*g), (y + 3*g), true);
    sceneS->addItem(bs1);

    bs2 = new pyra(m + (2*x + 3*g), (y + 3*g), false);
    sceneS->addItem(bs2);

    bs7 = new pyra(m + (0.5*x), (2*y + 4*g), false);
    sceneS->addItem(bs7);

    bs3 = new pyra(m + (x + g), (2*y + 4*g), true);
    sceneS->addItem(bs3);

    bs4 = new pyra(m + (1.5*x + 2*g), (2*y + 4*g), false);
    sceneS->addItem(bs4);

    bs5 = new pyra(m + (2*x + 3*g), (2*y + 4*g), true);
    sceneS->addItem(bs5);

    bs8 = new pyra(m + (2.5*x + 4*g), (2*y + 4*g), false);
    sceneS->addItem(bs8);

    updateScrambleGUI();
}

scrambleDialogPyra::~scrambleDialogPyra()
{
    delete ui;
}

void scrambleDialogPyra::updateScrambleGUI()
{
    os0->updateState("scramble", orangeFaceP_scramble[0]);
    os1->updateState("scramble", orangeFaceP_scramble[1]);
    os2->updateState("scramble", orangeFaceP_scramble[2]);
    os3->updateState("scramble", orangeFaceP_scramble[3]);
    os4->updateState("scramble", orangeFaceP_scramble[4]);
    os5->updateState("scramble", orangeFaceP_scramble[5]);
    os6->updateState("scramble", orangeFaceP_scramble[6]);
    os7->updateState("scramble", orangeFaceP_scramble[7]);
    os8->updateState("scramble", orangeFaceP_scramble[8]);

    gs0->updateState("scramble", greenFaceP_scramble[0]);
    gs1->updateState("scramble", greenFaceP_scramble[1]);
    gs2->updateState("scramble", greenFaceP_scramble[2]);
    gs3->updateState("scramble", greenFaceP_scramble[3]);
    gs4->updateState("scramble", greenFaceP_scramble[4]);
    gs5->updateState("scramble", greenFaceP_scramble[5]);
    gs6->updateState("scramble", greenFaceP_scramble[6]);
    gs7->updateState("scramble", greenFaceP_scramble[7]);
    gs8->updateState("scramble", greenFaceP_scramble[8]);

    ys0->updateState("scramble", yellowFaceP_scramble[0]);
    ys1->updateState("scramble", yellowFaceP_scramble[1]);
    ys2->updateState("scramble", yellowFaceP_scramble[2]);
    ys3->updateState("scramble", yellowFaceP_scramble[3]);
    ys4->updateState("scramble", yellowFaceP_scramble[4]);
    ys5->updateState("scramble", yellowFaceP_scramble[5]);
    ys6->updateState("scramble", yellowFaceP_scramble[6]);
    ys7->updateState("scramble", yellowFaceP_scramble[7]);
    ys8->updateState("scramble", yellowFaceP_scramble[8]);

    bs0->updateState("scramble", blueFaceP_scramble[0]);
    bs1->updateState("scramble", blueFaceP_scramble[1]);
    bs2->updateState("scramble", blueFaceP_scramble[2]);
    bs3->updateState("scramble", blueFaceP_scramble[3]);
    bs4->updateState("scramble", blueFaceP_scramble[4]);
    bs5->updateState("scramble", blueFaceP_scramble[5]);
    bs6->updateState("scramble", blueFaceP_scramble[6]);
    bs7->updateState("scramble", blueFaceP_scramble[7]);
    bs8->updateState("scramble", blueFaceP_scramble[8]);
}
