#include "scrambledialog.h"
#include "ui_scrambledialog.h"

// Initialize the scramble variables which store the scrambled state of the cube
QString whiteFace_scramble = "wwwwwwwww", yellowFace_scramble = "yyyyyyyyy", greenFace_scramble = "ggggggggg",
            blueFace_scramble = "bbbbbbbbb", redFace_scramble = "rrrrrrrrr", orangeFace_scramble = "ooooooooo";

/* This function takes a character from the "_scramble" strings and converts it into a stylesheet string
 * based on the colour (r, w, y, g, b, o) which can then be applied to the buttons to display the
 * scrambled state
 */
QString convertToStyleSheet(QChar s)
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

scrambleDialog::scrambleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scrambleDialog)
{
    ui->setupUi(this);

    /* All the buttons in this dialog are set to show the colour as specified
     * in the "_scramble" variable which is derived from the convertScramble function
     * from solver.cpp
     */

    ui->ws0->setStyleSheet(convertToStyleSheet(whiteFace_scramble[0]));
    ui->ws1->setStyleSheet(convertToStyleSheet(whiteFace_scramble[1]));
    ui->ws2->setStyleSheet(convertToStyleSheet(whiteFace_scramble[2]));
    ui->ws3->setStyleSheet(convertToStyleSheet(whiteFace_scramble[3]));
    ui->ws5->setStyleSheet(convertToStyleSheet(whiteFace_scramble[5]));
    ui->ws6->setStyleSheet(convertToStyleSheet(whiteFace_scramble[6]));
    ui->ws7->setStyleSheet(convertToStyleSheet(whiteFace_scramble[7]));
    ui->ws8->setStyleSheet(convertToStyleSheet(whiteFace_scramble[8]));

    ui->ys0->setStyleSheet(convertToStyleSheet(yellowFace_scramble[0]));
    ui->ys1->setStyleSheet(convertToStyleSheet(yellowFace_scramble[1]));
    ui->ys2->setStyleSheet(convertToStyleSheet(yellowFace_scramble[2]));
    ui->ys3->setStyleSheet(convertToStyleSheet(yellowFace_scramble[3]));
    ui->ys5->setStyleSheet(convertToStyleSheet(yellowFace_scramble[5]));
    ui->ys6->setStyleSheet(convertToStyleSheet(yellowFace_scramble[6]));
    ui->ys7->setStyleSheet(convertToStyleSheet(yellowFace_scramble[7]));
    ui->ys8->setStyleSheet(convertToStyleSheet(yellowFace_scramble[8]));

    ui->os0->setStyleSheet(convertToStyleSheet(orangeFace_scramble[0]));
    ui->os1->setStyleSheet(convertToStyleSheet(orangeFace_scramble[1]));
    ui->os2->setStyleSheet(convertToStyleSheet(orangeFace_scramble[2]));
    ui->os3->setStyleSheet(convertToStyleSheet(orangeFace_scramble[3]));
    ui->os5->setStyleSheet(convertToStyleSheet(orangeFace_scramble[5]));
    ui->os6->setStyleSheet(convertToStyleSheet(orangeFace_scramble[6]));
    ui->os7->setStyleSheet(convertToStyleSheet(orangeFace_scramble[7]));
    ui->os8->setStyleSheet(convertToStyleSheet(orangeFace_scramble[8]));

    ui->gs0->setStyleSheet(convertToStyleSheet(greenFace_scramble[0]));
    ui->gs1->setStyleSheet(convertToStyleSheet(greenFace_scramble[1]));
    ui->gs2->setStyleSheet(convertToStyleSheet(greenFace_scramble[2]));
    ui->gs3->setStyleSheet(convertToStyleSheet(greenFace_scramble[3]));
    ui->gs5->setStyleSheet(convertToStyleSheet(greenFace_scramble[5]));
    ui->gs6->setStyleSheet(convertToStyleSheet(greenFace_scramble[6]));
    ui->gs7->setStyleSheet(convertToStyleSheet(greenFace_scramble[7]));
    ui->gs8->setStyleSheet(convertToStyleSheet(greenFace_scramble[8]));

    ui->rs0->setStyleSheet(convertToStyleSheet(redFace_scramble[0]));
    ui->rs1->setStyleSheet(convertToStyleSheet(redFace_scramble[1]));
    ui->rs2->setStyleSheet(convertToStyleSheet(redFace_scramble[2]));
    ui->rs3->setStyleSheet(convertToStyleSheet(redFace_scramble[3]));
    ui->rs5->setStyleSheet(convertToStyleSheet(redFace_scramble[5]));
    ui->rs6->setStyleSheet(convertToStyleSheet(redFace_scramble[6]));
    ui->rs7->setStyleSheet(convertToStyleSheet(redFace_scramble[7]));
    ui->rs8->setStyleSheet(convertToStyleSheet(redFace_scramble[8]));

    ui->bs0->setStyleSheet(convertToStyleSheet(blueFace_scramble[0]));
    ui->bs1->setStyleSheet(convertToStyleSheet(blueFace_scramble[1]));
    ui->bs2->setStyleSheet(convertToStyleSheet(blueFace_scramble[2]));
    ui->bs3->setStyleSheet(convertToStyleSheet(blueFace_scramble[3]));
    ui->bs5->setStyleSheet(convertToStyleSheet(blueFace_scramble[5]));
    ui->bs6->setStyleSheet(convertToStyleSheet(blueFace_scramble[6]));
    ui->bs7->setStyleSheet(convertToStyleSheet(blueFace_scramble[7]));
    ui->bs8->setStyleSheet(convertToStyleSheet(blueFace_scramble[8]));
}

scrambleDialog::~scrambleDialog()
{
    delete ui;
}
