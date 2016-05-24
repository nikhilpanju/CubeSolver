#include "ui_mainwindow.h"
#include "../Header/mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab3x3->setStyleSheet("QWidget#tab3x3 { background-color: rgb(240, 240, 240);}");
    ui->tab2x2->setStyleSheet("QWidget#tab2x2 { background-color: rgb(240, 240, 240);}");
    ui->tabPyra->setStyleSheet("QWidget#tabPyra { background-color: rgb(240, 240, 240);}");
    ui->tabSQ->setStyleSheet("QWidget#tabSQ { background-color: rgb(240, 240, 240);}");

    // shortSolution button is initially invisible unless there is a shorter solution than the one provided
    ui->shortSolutionButton->setVisible(false);
    ui->shortSolutionButton_2->setVisible(false);
    ui->shortSolutionButton_P->setVisible(false);
    ui->shortSolutionButton_SQ->setVisible(false);

    ui->scrambleLineEdit_SQ->installEventFilter(this);

    initpyr();

    int x = 35;

    // create a scene to add polygons to
    sceneSQ_uF = new QGraphicsScene(this);
    sceneSQ_dF = new QGraphicsScene(this);
    sceneSQ_eL = new QGraphicsScene(this);

    // add scene to the graphicsView
    ui->graphicsView_SQ_uF->setScene(sceneSQ_uF);
    ui->graphicsView_SQ_dF->setScene(sceneSQ_dF);
    ui->graphicsView_SQ_eL->setScene(sceneSQ_eL);

    // set rectangle of the scene
    ui->graphicsView_SQ_uF->setSceneRect(-(2.71 * x) - 28.28, -(2.71 * x) - 28.28,
                                         ((2.71 * x) + 28.28) * 2, ((2.71 * x) + 28.28) * 2);
    ui->graphicsView_SQ_dF->setSceneRect(-(2.71 * x) - 28.28, -(2.71 * x) - 28.28,
                                         ((2.71 * x) + 28.28) * 2, ((2.71 * x) + 28.28) * 2);

    // for smooth lines
    ui->graphicsView_SQ_uF->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_SQ_dF->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_SQ_eL->setRenderHint(QPainter::Antialiasing);

    initSQ1();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/////////////////////////////////////// Menu bar Actions //////////////////////////////////////////

///////////// Instructions Button ////////////////

void MainWindow::on_actionInstructions_triggered()
{
    // display the title and the body in a message box
    QMessageBox::information(this, "Instructions", "<b>GUI Input:</b>"
                             "<br>- Fill the entire layout correctly using the colour buttons"
                             "<br>- Flipped edges, twisted corners and partially filled layouts are unsolvable"
                             "<br>- Select <b>GUI Input</b> radio button and click solve"
                             "<br><br><b>Scramble Input:</b>"
                             "<br>- Type or paste a scramble into the Scramble field and press return"
                             "<br>- Alternatively select <b>Scramble Input</b> radio button and click solve"
                             "<br>- Only valid scrambles are accepted. Ex: D U2 B' U L2 R L' D2 U'"
                             "<br>- Use 'View Scramble' button to display the scrambled state"
                             "<br><br>Use the <b>clear</b> button to revert to original state"
                             "<br>A <b>reduced solution</b> checkbox may appear which shows a slightly shorter solution"
                             " by combining moves like U U2, L L', etc");

}

///////////// About Button ////////////////

void MainWindow::on_actionAbout_triggered()
{
    // display the title and the body in a message box
    QMessageBox::about(this, "About", "<b>CubeSolver 1.0</b>"
                       "<br> Based on Qt 5.5.0 (MSVC 2013, 32 bit)"
                       "<br> Made in Qt Creator 3.4.2 (opensource)"
                       "<br> Made by Nikhil Panju");
}
