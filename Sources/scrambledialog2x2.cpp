#include "../Header/scrambledialog2x2.h"
#include "ui_scrambledialog2x2.h"

// Initialize the scramble variables which store the scrambled state of the cube
QString whiteFace2_scramble = "wwww", yellowFace2_scramble = "yyyy", greenFace2_scramble = "gggg",
            blueFace2_scramble = "bbbb", redFace2_scramble = "rrrr", orangeFace2_scramble = "oooo";

/* This function takes a character from the "_scramble" strings and converts it into a stylesheet string
 * based on the colour (r, w, y, g, b, o) which can then be applied to the buttons to display the
 * scrambled state
 */
QString convertToStyleSheet2(QChar s)
{
    if (s == 'w')
        return "background-color: rgb(255, 255, 255);";
    else if (s == 'y')
        return "background-color: rgb(255, 255, 0);";
    else if (s == 'g')
        return "background-color: rgb(85, 255, 0);";
    else if (s == 'b')
        return "background-color: rgb(0, 0, 255);";
    else if (s == 'r')
        return "background-color: rgb(255, 0, 0);";
    else if (s == 'o')
        return "background-color: rgb(255, 170, 0);";

    return "background-color: rgb(0, 0, 0, 50);";
}

scrambleDialog2x2::scrambleDialog2x2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scrambleDialog2x2)
{
    ui->setupUi(this);

    /* All the buttons in this dialog are set to show the colour as specified
     * in the "_scramble" variable which is derived from the convertScramble function
     * from solver.cpp
     */

    ui->ws0_2->setStyleSheet(convertToStyleSheet2(whiteFace2_scramble[0]));
    ui->ws1_2->setStyleSheet(convertToStyleSheet2(whiteFace2_scramble[1]));
    ui->ws2_2->setStyleSheet(convertToStyleSheet2(whiteFace2_scramble[2]));
    ui->ws3_2->setStyleSheet(convertToStyleSheet2(whiteFace2_scramble[3]));

    ui->ys0_2->setStyleSheet(convertToStyleSheet2(yellowFace2_scramble[0]));
    ui->ys1_2->setStyleSheet(convertToStyleSheet2(yellowFace2_scramble[1]));
    ui->ys2_2->setStyleSheet(convertToStyleSheet2(yellowFace2_scramble[2]));
    ui->ys3_2->setStyleSheet(convertToStyleSheet2(yellowFace2_scramble[3]));

    ui->os0_2->setStyleSheet(convertToStyleSheet2(orangeFace2_scramble[0]));
    ui->os1_2->setStyleSheet(convertToStyleSheet2(orangeFace2_scramble[1]));
    ui->os2_2->setStyleSheet(convertToStyleSheet2(orangeFace2_scramble[2]));
    ui->os3_2->setStyleSheet(convertToStyleSheet2(orangeFace2_scramble[3]));

    ui->gs0_2->setStyleSheet(convertToStyleSheet2(greenFace2_scramble[0]));
    ui->gs1_2->setStyleSheet(convertToStyleSheet2(greenFace2_scramble[1]));
    ui->gs2_2->setStyleSheet(convertToStyleSheet2(greenFace2_scramble[2]));
    ui->gs3_2->setStyleSheet(convertToStyleSheet2(greenFace2_scramble[3]));

    ui->rs0_2->setStyleSheet(convertToStyleSheet2(redFace2_scramble[0]));
    ui->rs1_2->setStyleSheet(convertToStyleSheet2(redFace2_scramble[1]));
    ui->rs2_2->setStyleSheet(convertToStyleSheet2(redFace2_scramble[2]));
    ui->rs3_2->setStyleSheet(convertToStyleSheet2(redFace2_scramble[3]));

    ui->bs0_2->setStyleSheet(convertToStyleSheet2(blueFace2_scramble[0]));
    ui->bs1_2->setStyleSheet(convertToStyleSheet2(blueFace2_scramble[1]));
    ui->bs2_2->setStyleSheet(convertToStyleSheet2(blueFace2_scramble[2]));
    ui->bs3_2->setStyleSheet(convertToStyleSheet2(blueFace2_scramble[3]));
}

scrambleDialog2x2::~scrambleDialog2x2()
{
    delete ui;
}
