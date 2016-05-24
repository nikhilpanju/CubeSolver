#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class pyra;
class sq1;

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTime>
#include "pyra.h"
#include "sq1.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void udpateGUIVariables();

    pyra *o6, *o0, *o1, *o2, *o7, *o3, *o4, *o5, *o8;
    pyra *b6, *b0, *b1, *b2, *b7, *b3, *b4, *b5, *b8;
    pyra *y6, *y0, *y1, *y2, *y7, *y3, *y4, *y5, *y8;
    pyra *g6, *g0, *g1, *g2, *g7, *g3, *g4, *g5, *g8;

    sq1 *uf0, *uf1, *uf2, *uf3, *uf4, *uf5, *uf6, *uf7, *uf8, *uf9;
    sq1 *df0, *df1, *df2, *df3, *df4, *df5, *df6, *df7, *df8, *df9;


    ~MainWindow();

private slots:

    //// button action functions ////
    // note: w4, y4, etc are not included because they do not move (center pieces)

    // choice buttons
    void on_cwhite_clicked();
    void on_cy_clicked();
    void on_cg_clicked();
    void on_cb_clicked();
    void on_co_clicked();
    void on_cr_clicked();

    // white face buttons
    void on_w0_clicked();
    void on_w1_clicked();
    void on_w2_clicked();
    void on_w3_clicked();
    void on_w5_clicked();
    void on_w6_clicked();
    void on_w7_clicked();
    void on_w8_clicked();

    // orange face buttons
    void on_o0_clicked();
    void on_o1_clicked();
    void on_o2_clicked();
    void on_o3_clicked();
    void on_o5_clicked();
    void on_o6_clicked();
    void on_o7_clicked();
    void on_o8_clicked();

    // green face buttons
    void on_g0_clicked();
    void on_g1_clicked();
    void on_g2_clicked();
    void on_g3_clicked();
    void on_g5_clicked();
    void on_g6_clicked();
    void on_g7_clicked();
    void on_g8_clicked();

    // red face buttons
    void on_r0_clicked();
    void on_r1_clicked();
    void on_r2_clicked();
    void on_r3_clicked();
    void on_r5_clicked();
    void on_r6_clicked();
    void on_r7_clicked();
    void on_r8_clicked();

    // blue face buttons
    void on_b0_clicked();
    void on_b1_clicked();
    void on_b2_clicked();
    void on_b3_clicked();
    void on_b5_clicked();
    void on_b6_clicked();
    void on_b7_clicked();
    void on_b8_clicked();

    // yellow face buttons
    void on_y0_clicked();
    void on_y1_clicked();
    void on_y2_clicked();
    void on_y3_clicked();
    void on_y5_clicked();
    void on_y6_clicked();
    void on_y7_clicked();
    void on_y8_clicked();

    // "Solve" button
    void on_solveButton_clicked();

    // "Clear" button
    void on_clearButton_clicked();

    // "GUI Input" radio button
    void on_GUIInputButton_clicked();

    // "Scramble Input" radio button
    void on_scrambleInputButton_clicked();

    // 'Short solution' check box
    void on_shortSolutionButton_toggled(bool checked);

    // "View Scramble" button
    void on_viewScrambleButton_clicked();

    // "Scramble" text field (return pressed action)
    void on_scrambleLineEdit_returnPressed();

    // "Scramble" text field (cursor moved action)
    void on_scrambleLineEdit_cursorPositionChanged();

    // "Provide Scramble" button
    void on_provideScrambleButton_clicked();

    // "Instructions" button (Menu bar)
    void on_actionInstructions_triggered();

    // "About" button (Menu bar)
    void on_actionAbout_triggered();

    ////////////////// 2x2 Tab //////////////////////////

    // choice buttons
    void on_cwhite_2_clicked();
    void on_cy_2_clicked();
    void on_cg_2_clicked();
    void on_cb_2_clicked();
    void on_co_2_clicked();
    void on_cr_2_clicked();

    // white face buttons
    void on_w0_2_clicked();
    void on_w1_2_clicked();
    void on_w2_2_clicked();
    void on_w3_2_clicked();

    // orange face buttons
    void on_o0_2_clicked();
    void on_o1_2_clicked();
    void on_o2_2_clicked();
    void on_o3_2_clicked();

    // green face buttons
    void on_g0_2_clicked();
    void on_g1_2_clicked();
    void on_g2_2_clicked();
    void on_g3_2_clicked();

    // red face buttons
    void on_r0_2_clicked();
    void on_r1_2_clicked();
    void on_r2_2_clicked();
    void on_r3_2_clicked();

    // blue face buttons
    void on_b0_2_clicked();
    void on_b1_2_clicked();
    void on_b2_2_clicked();
    void on_b3_2_clicked();

    // yellow face buttons
    void on_y0_2_clicked();
    void on_y1_2_clicked();
    void on_y2_2_clicked();
    void on_y3_2_clicked();

    // "Solve" button
    void on_solveButton_2_clicked();

    // "Clear" button
    void on_clearButton_2_clicked();

    // "GUI Input" radio button
    void on_GUIInputButton_2_clicked();

    // "Scramble Input" radio button
    void on_scrambleInputButton_2_clicked();

    // 'Short solution' check box
    void on_shortSolutionButton_2_toggled(bool checked);

    // "View Scramble" button
    void on_viewScrambleButton_2_clicked();

    // "Scramble" text field (return pressed action)
    void on_scrambleLineEdit_2_returnPressed();

    // "Scramble" text field (cursor moved action)
    void on_scrambleLineEdit_2_cursorPositionChanged();

    // "Provide Scramble" button
    void on_provideScrambleButton_2_clicked();

    ////////////////////// Pyraminx //////////////////////////

    // initializes the triangles in GraphicView in Pyra Tab
    void initpyr();

    // choice buttons
    void on_cy_P_clicked();
    void on_cg_P_clicked();
    void on_cb_P_clicked();
    void on_co_P_clicked();

    // "Solve" button
    void on_solveButton_P_clicked();

    // "Clear" button
    void on_clearButton_P_clicked();

    // "GUI Input" radio button
    void on_GUIInputButton_P_clicked();

    // "Scramble Input" radio button
    void on_scrambleInputButton_P_clicked();

    // 'Short solution' check box
    void on_shortSolutionButton_P_toggled(bool checked);

    // "View Scramble" button
    void on_viewScrambleButton_P_clicked();

    // "Scramble" text field (return pressed action)
    void on_scrambleLineEdit_P_returnPressed();

    // "Scramble" text field (cursor moved action)
    void on_scrambleLineEdit_P_cursorPositionChanged();

    // "Provide Scramble" button
    void on_provideScrambleButton_P_clicked();

    ////////////////// SQ 1 Tab //////////////////////////

    // function to initialize the polygons
    void initSQ1();

    // "Solve" button
    void on_solveButton_SQ_clicked();

    // "Clear" button
    //void on_clearButton_2_clicked();

    // "GUI Input" radio button
    void on_GUIInputButton_SQ_clicked();

    // "Scramble Input" radio button
    void on_scrambleInputButton_SQ_clicked();

    // 'Short solution' check box
    void on_shortSolutionButton_SQ_toggled(bool checked);

    // "View Scramble" button
    //void on_viewScrambleButton_2_clicked();

    // "Scramble" text field (return pressed action)
    bool eventFilter(QObject *object, QEvent *event);

    // "Scramble" text field (cursor moved action)
    void on_scrambleLineEdit_SQ_cursorPositionChanged();

    // "Provide Scramble" button
    void on_provideScrambleButton_SQ_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *sceneP, *sceneSQ_uF, *sceneSQ_dF, *sceneSQ_eL;


};

// verifies if entered Cube state in GUI is valid or not
int GUICheck();
int GUICheck_2();
int GUICheck_P();

// verifies if entered scramble text in scramble field is valid or not
int scrambleCheck();
int scrambleCheck_2();
int scrambleCheck_P();
int scrambleCheck_SQ();

// scramble provider functions
QString scrambleString();
QString scrambleString_2();
QString scrambleString_P();
bool checkIfSquare(int u, int d);
QString scrambleString_SQ();

#endif // MAINWINDOW_H
