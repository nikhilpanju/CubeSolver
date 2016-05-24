#include <QApplication>
#include <QString>
#include <QStringList>
#include "../Header/solverpyra.h"

/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Variable Declarations //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// these variables store the scrambled state of the cube used by scrambledialog.cpp
extern QString yellowFaceP_scramble, greenFaceP_scramble, blueFaceP_scramble, orangeFaceP_scramble;

// stores the scramble string inputted by the user
extern QString scrambleP;

// current state variables
QString blueFaceP = "bbbbbbbbb";
QString orangeFaceP = "ooooooooo";
QString greenFaceP = "ggggggggg";
QString yellowFaceP = "yyyyyyyyy";

// location of first block (12 possible cases)
int blockLocation;

// colour of block formed
QChar blockColour;

// colour of the other colours of the block
QString blockTailColour;

// variables used to create checkpoint locations
QString blueFaceP_cp, whiteFaceP_cp, greenFaceP_cp, orangeFaceP_cp, yellowFaceP_cp, redFaceP_cp;

// variable used to store every move of the solution in a list
QStringList solutionListP;

// strings that store the solution or a reduced solution
QString solutionP;
QString solutionP_short;

//variables that store the no. of moves for the respective solution
int moveCountP;
int moveCountP_short;

// trialP variable is used to check amount of "y" needed for alg. Used with checkpoint variables. 1 or 0
bool trialP = false;

/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CubeSolver Implementation /////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// creates a checkpoint to which the current state variables can be restored after determining "y" value
void createCheckpointP()
{
    blueFaceP_cp = blueFaceP;
    greenFaceP_cp = greenFaceP;
    orangeFaceP_cp = orangeFaceP;
    yellowFaceP_cp = yellowFaceP;
}

// resets the current state variables to the checkpoint location
void resetLocationP()
{
    blueFaceP = blueFaceP_cp;
    greenFaceP = greenFaceP_cp;
    orangeFaceP = orangeFaceP_cp;
    yellowFaceP = yellowFaceP_cp;
}

void L_P()
{
    QString greenFaceP_temp, orangeFaceP_temp, yellowFaceP_temp;

    greenFaceP_temp = greenFaceP;
    orangeFaceP_temp = orangeFaceP;
    yellowFaceP_temp = yellowFaceP;

    greenFaceP[0] = orangeFaceP_temp[4];
    greenFaceP[3] = orangeFaceP_temp[5];
    greenFaceP[4] = orangeFaceP_temp[2];

    yellowFaceP[0] = greenFaceP_temp[3];
    yellowFaceP[1] = greenFaceP_temp[0];
    yellowFaceP[3] = greenFaceP_temp[4];

    orangeFaceP[2] = yellowFaceP_temp[3];
    orangeFaceP[4] = yellowFaceP_temp[1];
    orangeFaceP[5] = yellowFaceP_temp[0];

    greenFaceP[7] = orangeFaceP_temp[8];
    yellowFaceP[6] = greenFaceP_temp[7];
    orangeFaceP[8] = yellowFaceP_temp[6];

    if (trialP == false)
    {
        solutionListP.append("L");
    }
}
void Li_P()
{
    QString greenFaceP_temp, orangeFaceP_temp, yellowFaceP_temp;

    greenFaceP_temp = greenFaceP;
    orangeFaceP_temp = orangeFaceP;
    yellowFaceP_temp = yellowFaceP;

    greenFaceP[0] = yellowFaceP_temp[1];
    greenFaceP[3] = yellowFaceP_temp[0];
    greenFaceP[4] = yellowFaceP_temp[3];

    yellowFaceP[0] = orangeFaceP_temp[5];
    yellowFaceP[1] = orangeFaceP_temp[4];
    yellowFaceP[3] = orangeFaceP_temp[2];

    orangeFaceP[2] = greenFaceP_temp[4];
    orangeFaceP[4] = greenFaceP_temp[0];
    orangeFaceP[5] = greenFaceP_temp[3];

    greenFaceP[7] = yellowFaceP_temp[6];
    yellowFaceP[6] = orangeFaceP_temp[8];
    orangeFaceP[8] = greenFaceP_temp[7];

    if (trialP == false)
    {
        solutionListP.append("L'");
    }
}
void R_P()
{
    QString greenFaceP_temp, blueFaceP_temp, yellowFaceP_temp;

    greenFaceP_temp = greenFaceP;
    blueFaceP_temp = blueFaceP;
    yellowFaceP_temp = yellowFaceP;

    greenFaceP[2] = yellowFaceP_temp[1];
    greenFaceP[4] = yellowFaceP_temp[5];
    greenFaceP[5] = yellowFaceP_temp[2];

    yellowFaceP[1] = blueFaceP_temp[4];
    yellowFaceP[2] = blueFaceP_temp[3];
    yellowFaceP[5] = blueFaceP_temp[0];

    blueFaceP[0] = greenFaceP_temp[4];
    blueFaceP[3] = greenFaceP_temp[5];
    blueFaceP[4] = greenFaceP_temp[2];

    greenFaceP[8] = yellowFaceP_temp[7];
    yellowFaceP[7] = blueFaceP_temp[7];
    blueFaceP[7] = greenFaceP_temp[8];

    if (trialP == false)
    {
        solutionListP.append("R");
    }
}
void Ri_P()
{
    QString greenFaceP_temp, blueFaceP_temp, yellowFaceP_temp;

    greenFaceP_temp = greenFaceP;
    blueFaceP_temp = blueFaceP;
    yellowFaceP_temp = yellowFaceP;

    greenFaceP[2] = blueFaceP_temp[4];
    greenFaceP[4] = blueFaceP_temp[0];
    greenFaceP[5] = blueFaceP_temp[3];

    yellowFaceP[1] = greenFaceP_temp[2];
    yellowFaceP[2] = greenFaceP_temp[5];
    yellowFaceP[5] = greenFaceP_temp[4];

    blueFaceP[0] = yellowFaceP_temp[5];
    blueFaceP[3] = yellowFaceP_temp[2];
    blueFaceP[4] = yellowFaceP_temp[1];

    greenFaceP[8] = blueFaceP_temp[7];
    yellowFaceP[7] = greenFaceP_temp[8];
    blueFaceP[7] = yellowFaceP_temp[7];

    if (trialP == false)
    {
        solutionListP.append("R'");
    }
}
void U_P()
{
    QString greenFaceP_temp, orangeFaceP_temp, blueFaceP_temp;

    greenFaceP_temp = greenFaceP;
    orangeFaceP_temp = orangeFaceP;
    blueFaceP_temp = blueFaceP;

    greenFaceP[0] = blueFaceP_temp[0];
    greenFaceP[1] = blueFaceP_temp[1];
    greenFaceP[2] = blueFaceP_temp[2];

    blueFaceP[0] = orangeFaceP_temp[0];
    blueFaceP[1] = orangeFaceP_temp[1];
    blueFaceP[2] = orangeFaceP_temp[2];

    orangeFaceP[0] = greenFaceP_temp[0];
    orangeFaceP[1] = greenFaceP_temp[1];
    orangeFaceP[2] = greenFaceP_temp[2];

    greenFaceP[6] = blueFaceP_temp[6];
    blueFaceP[6] = orangeFaceP_temp[6];
    orangeFaceP[6] = greenFaceP_temp[6];

    if (trialP == false)
    {
        solutionListP.append("U");
    }
}
void Ui_P()
{
    QString greenFaceP_temp, orangeFaceP_temp, blueFaceP_temp;

    greenFaceP_temp = greenFaceP;
    orangeFaceP_temp = orangeFaceP;
    blueFaceP_temp = blueFaceP;

    greenFaceP[0] = orangeFaceP_temp[0];
    greenFaceP[1] = orangeFaceP_temp[1];
    greenFaceP[2] = orangeFaceP_temp[2];

    blueFaceP[0] = greenFaceP_temp[0];
    blueFaceP[1] = greenFaceP_temp[1];
    blueFaceP[2] = greenFaceP_temp[2];

    orangeFaceP[0] = blueFaceP_temp[0];
    orangeFaceP[1] = blueFaceP_temp[1];
    orangeFaceP[2] = blueFaceP_temp[2];

    greenFaceP[6] = orangeFaceP_temp[6];
    blueFaceP[6] = greenFaceP_temp[6];
    orangeFaceP[6] = blueFaceP_temp[6];

    if (trialP == false)
    {
        solutionListP.append("U'");
    }
}
void B_P()
{
    QString yellowFaceP_temp, orangeFaceP_temp, blueFaceP_temp;

    yellowFaceP_temp = yellowFaceP;
    orangeFaceP_temp = orangeFaceP;
    blueFaceP_temp = blueFaceP;

    orangeFaceP[0] = blueFaceP_temp[4];
    orangeFaceP[3] = blueFaceP_temp[5];
    orangeFaceP[4] = blueFaceP_temp[2];

    blueFaceP[2] = yellowFaceP_temp[5];
    blueFaceP[4] = yellowFaceP_temp[3];
    blueFaceP[5] = yellowFaceP_temp[4];

    yellowFaceP[3] = orangeFaceP_temp[0];
    yellowFaceP[4] = orangeFaceP_temp[3];
    yellowFaceP[5] = orangeFaceP_temp[4];

    orangeFaceP[7] = blueFaceP_temp[8];
    blueFaceP[8] = yellowFaceP_temp[8];
    yellowFaceP[8] = orangeFaceP_temp[7];

    if (trialP == false)
    {
        solutionListP.append("B");
    }
}
void Bi_P()
{
    QString yellowFaceP_temp, orangeFaceP_temp, blueFaceP_temp;

    yellowFaceP_temp = yellowFaceP;
    orangeFaceP_temp = orangeFaceP;
    blueFaceP_temp = blueFaceP;

    orangeFaceP[0] = yellowFaceP_temp[3];
    orangeFaceP[3] = yellowFaceP_temp[4];
    orangeFaceP[4] = yellowFaceP_temp[5];

    blueFaceP[2] = orangeFaceP_temp[4];
    blueFaceP[4] = orangeFaceP_temp[0];
    blueFaceP[5] = orangeFaceP_temp[3];

    yellowFaceP[3] = blueFaceP_temp[4];
    yellowFaceP[4] = blueFaceP_temp[5];
    yellowFaceP[5] = blueFaceP_temp[2];

    orangeFaceP[7] = yellowFaceP_temp[8];
    blueFaceP[8] = orangeFaceP_temp[7];
    yellowFaceP[8] = blueFaceP_temp[8];

    if (trialP == false)
    {
        solutionListP.append("B'");
    }
}

// tip rotation functions

void lT()
{
    QString greenFaceP_temp, orangeFaceP_temp, yellowFaceP_temp;

    greenFaceP_temp = greenFaceP;
    orangeFaceP_temp = orangeFaceP;
    yellowFaceP_temp = yellowFaceP;

    greenFaceP[7] = orangeFaceP_temp[8];
    yellowFaceP[6] = greenFaceP_temp[7];
    orangeFaceP[8] = yellowFaceP_temp[6];

    if (trialP == false)
    {
        solutionListP.append("l");
    }
}

void liT()
{
    QString greenFaceP_temp, orangeFaceP_temp, yellowFaceP_temp;

    greenFaceP_temp = greenFaceP;
    orangeFaceP_temp = orangeFaceP;
    yellowFaceP_temp = yellowFaceP;

    greenFaceP[7] = yellowFaceP_temp[6];
    yellowFaceP[6] = orangeFaceP_temp[8];
    orangeFaceP[8] = greenFaceP_temp[7];

    if (trialP == false)
    {
        solutionListP.append("l'");
    }
}
void rT()
{
    QString greenFaceP_temp, blueFaceP_temp, yellowFaceP_temp;

    greenFaceP_temp = greenFaceP;
    blueFaceP_temp = blueFaceP;
    yellowFaceP_temp = yellowFaceP;

    greenFaceP[8] = yellowFaceP_temp[7];
    yellowFaceP[7] = blueFaceP_temp[7];
    blueFaceP[7] = greenFaceP_temp[8];

    if (trialP == false)
    {
        solutionListP.append("r");
    }
}
void riT()
{
    QString greenFaceP_temp, blueFaceP_temp, yellowFaceP_temp;

    greenFaceP_temp = greenFaceP;
    blueFaceP_temp = blueFaceP;
    yellowFaceP_temp = yellowFaceP;

    greenFaceP[8] = blueFaceP_temp[7];
    yellowFaceP[7] = greenFaceP_temp[8];
    blueFaceP[7] = yellowFaceP_temp[7];

    if (trialP == false)
    {
        solutionListP.append("r'");
    }
}
void uT()
{
    QString greenFaceP_temp, orangeFaceP_temp, blueFaceP_temp;

    greenFaceP_temp = greenFaceP;
    orangeFaceP_temp = orangeFaceP;
    blueFaceP_temp = blueFaceP;

    greenFaceP[6] = blueFaceP_temp[6];
    blueFaceP[6] = orangeFaceP_temp[6];
    orangeFaceP[6] = greenFaceP_temp[6];

    if (trialP == false)
    {
        solutionListP.append("u");
    }
}
void uiT()
{
    QString greenFaceP_temp, orangeFaceP_temp, blueFaceP_temp;

    greenFaceP_temp = greenFaceP;
    orangeFaceP_temp = orangeFaceP;
    blueFaceP_temp = blueFaceP;

    greenFaceP[6] = orangeFaceP_temp[6];
    blueFaceP[6] = greenFaceP_temp[6];
    orangeFaceP[6] = blueFaceP_temp[6];

    if (trialP == false)
    {
        solutionListP.append("u'");
    }
}
void bT()
{
    QString yellowFaceP_temp, orangeFaceP_temp, blueFaceP_temp;

    yellowFaceP_temp = yellowFaceP;
    orangeFaceP_temp = orangeFaceP;
    blueFaceP_temp = blueFaceP;

    orangeFaceP[7] = blueFaceP_temp[8];
    blueFaceP[8] = yellowFaceP_temp[8];
    yellowFaceP[8] = orangeFaceP_temp[7];

    if (trialP == false)
    {
        solutionListP.append("b");
    }
}
void biT()
{
    QString yellowFaceP_temp, orangeFaceP_temp, blueFaceP_temp;

    yellowFaceP_temp = yellowFaceP;
    orangeFaceP_temp = orangeFaceP;
    blueFaceP_temp = blueFaceP;

    orangeFaceP[7] = yellowFaceP_temp[8];
    blueFaceP[8] = orangeFaceP_temp[7];
    yellowFaceP[8] = blueFaceP_temp[8];

    if (trialP == false)
    {
        solutionListP.append("b'");
    }
}

// rotation modifier functions - used to change alg based on "y" value

void l_P()
{
    switch(blockLocation)
    {
        case 1: L_P(); break;
        case 2: U_P(); break;
        case 3: R_P(); break;
        case 4: R_P(); break;
        case 5: B_P(); break;
        case 6: U_P(); break;
        case 7: B_P(); break;
        case 8: U_P(); break;
        case 9: L_P(); break;
        case 10: R_P(); break;
        case 11: L_P(); break;
        case 12: B_P(); break;
    }
}
void li_P()
{
    switch(blockLocation)
    {
        case 1: Li_P(); break;
        case 2: Ui_P(); break;
        case 3: Ri_P(); break;
        case 4: Ri_P(); break;
        case 5: Bi_P(); break;
        case 6: Ui_P(); break;
        case 7: Bi_P(); break;
        case 8: Ui_P(); break;
        case 9: Li_P(); break;
        case 10: Ri_P(); break;
        case 11: Li_P(); break;
        case 12: Bi_P(); break;
    }
}
void r_P()
{
    switch(blockLocation)
    {
        case 1: R_P(); break;
        case 2: L_P(); break;
        case 3: U_P(); break;
        case 4: B_P(); break;
        case 5: U_P(); break;
        case 6: R_P(); break;
        case 7: L_P(); break;
        case 8: B_P(); break;
        case 9: U_P(); break;
        case 10: L_P(); break;
        case 11: B_P(); break;
        case 12: R_P(); break;
    }
}
void ri_P()
{
    switch(blockLocation)
    {
        case 1: Ri_P(); break;
        case 2: Li_P(); break;
        case 3: Ui_P(); break;
        case 4: Bi_P(); break;
        case 5: Ui_P(); break;
        case 6: Ri_P(); break;
        case 7: Li_P(); break;
        case 8: Bi_P(); break;
        case 9: Ui_P(); break;
        case 10: Li_P(); break;
        case 11: Bi_P(); break;
        case 12: Ri_P(); break;
    }
}
void u_P()
{
    switch(blockLocation)
    {
        case 1: U_P(); break;
        case 2: R_P(); break;
        case 3: L_P(); break;
        case 4: U_P(); break;
        case 5: R_P(); break;
        case 6: B_P(); break;
        case 7: U_P(); break;
        case 8: L_P(); break;
        case 9: B_P(); break;
        case 10: B_P(); break;
        case 11: R_P(); break;
        case 12: L_P(); break;
    }
}
void ui_P()
{
    switch(blockLocation)
    {
        case 1: Ui_P(); break;
        case 2: Ri_P(); break;
        case 3: Li_P(); break;
        case 4: Ui_P(); break;
        case 5: Ri_P(); break;
        case 6: Bi_P(); break;
        case 7: Ui_P(); break;
        case 8: Li_P(); break;
        case 9: Bi_P(); break;
        case 10: Bi_P(); break;
        case 11: Ri_P(); break;
        case 12: Li_P(); break;
    }
}
void b_P()
{
    switch(blockLocation)
    {
        case 1: B_P(); break;
        case 2: B_P(); break;
        case 3: B_P(); break;
        case 4: L_P(); break;
        case 5: L_P(); break;
        case 6: L_P(); break;
        case 7: R_P(); break;
        case 8: R_P(); break;
        case 9: R_P(); break;
        case 10: U_P(); break;
        case 11: U_P(); break;
        case 12: U_P(); break;
    }
}
void bi_P()
{
    switch(blockLocation)
    {
        case 1: Bi_P(); break;
        case 2: Bi_P(); break;
        case 3: Bi_P(); break;
        case 4: Li_P(); break;
        case 5: Li_P(); break;
        case 6: Li_P(); break;
        case 7: Ri_P(); break;
        case 8: Ri_P(); break;
        case 9: Ri_P(); break;
        case 10: Ui_P(); break;
        case 11: Ui_P(); break;
        case 12: Ui_P(); break;
    }
}

// converts a given scramble string into an actual scramble simulation in the program
void convertScrambleP(QString &scram)
{
    trialP = true; // trialP is true since we don't want the scramble as part of the solution

    QStringList s = scram.split(" ");

    foreach(QString move, s)
    {
        if (move == "L")
            L_P();
        else if (move == "L'")
            Li_P();
        else if (move == "R")
            R_P();
        else if (move == "R'")
            Ri_P();
        else if (move == "U")
            U_P();
        else if (move == "U'")
            Ui_P();
        else if (move == "B")
            B_P();
        else if (move == "B'")
            Bi_P();
        else if (move == "l")
            lT();
        else if (move == "l'")
            liT();
        else if (move == "r")
            rT();
        else if (move == "r'")
            riT();
        else if (move == "u")
            uT();
        else if (move == "u'")
            uiT();
        else if (move == "b")
            bT();
        else if (move == "b'")
            biT();
    }
    trialP = false; // switch off trialP

    /* assign "_scramble" variables the current scrambled state so that it can be viewed
     * using the "View Scramble" button. Actual usage in scrambledialog.cpp
     */
    blueFaceP_scramble = blueFaceP;
    greenFaceP_scramble = greenFaceP;
    orangeFaceP_scramble = orangeFaceP;
    yellowFaceP_scramble = yellowFaceP;
}

void tips()
{
    if (greenFaceP[6] == orangeFaceP[1] && orangeFaceP[6] ==  blueFaceP[1]
                && blueFaceP[6] == greenFaceP[1])
            uT();
    else if (greenFaceP[6] == blueFaceP[1] && orangeFaceP[6] ==  greenFaceP[1]
                 && blueFaceP[6] == orangeFaceP[1])
            uiT();

    if (greenFaceP[7] == yellowFaceP[0] && orangeFaceP[8] ==  greenFaceP[3]
            && yellowFaceP[6] == orangeFaceP[5])
        lT();
    else if (greenFaceP[7] == orangeFaceP[5] && orangeFaceP[8] ==  yellowFaceP[0]
             && yellowFaceP[6] == greenFaceP[3])
        liT();

    if (greenFaceP[8] == blueFaceP[3] && blueFaceP[7] ==  yellowFaceP[2]
            && yellowFaceP[7] == greenFaceP[5])
        rT();
    else if (greenFaceP[8] == yellowFaceP[2] && blueFaceP[7] ==  greenFaceP[5]
             && yellowFaceP[7] == blueFaceP[3])
        riT();

    if (orangeFaceP[7] == yellowFaceP[4] && blueFaceP[8] ==  orangeFaceP[3]
             && yellowFaceP[8] == blueFaceP[5])
        bT();
    else if (orangeFaceP[7] == blueFaceP[5] && blueFaceP[8] ==  yellowFaceP[4]
             && yellowFaceP[8] == orangeFaceP[3])
        biT();
}

int blockPresent()
{
    // block in B block
    if (yellowFaceP[3] == yellowFaceP[4] && yellowFaceP[4] == yellowFaceP[5] && orangeFaceP[3] == orangeFaceP[4]
        && blueFaceP[4] == blueFaceP[5])
    {
        blockLocation = 1;
        blockColour = yellowFaceP[4]; // centre associated with the block (can be edge too)
        blockTailColour[0] = orangeFaceP[3];
        blockTailColour[1] = blueFaceP[5];
        return 1;
    }
    else if (orangeFaceP[3] == orangeFaceP[4] && orangeFaceP[3] == orangeFaceP[0] && yellowFaceP[3] == yellowFaceP[4]
        && blueFaceP[2] == blueFaceP[5])
    {
        blockLocation = 2;
        blockColour = orangeFaceP[3];
        blockTailColour[0] = blueFaceP[5];
        blockTailColour[1] = yellowFaceP[4];
        return 1;
    }
    else if (blueFaceP[2] == blueFaceP[5] && blueFaceP[4] == blueFaceP[5] && orangeFaceP[3] == orangeFaceP[0]
        && yellowFaceP[4] == yellowFaceP[5])
    {
        blockLocation = 3;
        blockColour = blueFaceP[5];
        blockTailColour[0] = yellowFaceP[4];
        blockTailColour[1] = orangeFaceP[3];
        return 1;
    }

    // block in L block
    else if (yellowFaceP[3] == yellowFaceP[0] && yellowFaceP[0] == yellowFaceP[1] && orangeFaceP[5] == orangeFaceP[4]
        && greenFaceP[4] == greenFaceP[3])
    {
        blockLocation = 4;
        blockColour = yellowFaceP[0];
        blockTailColour[0] = greenFaceP[3];
        blockTailColour[1] = orangeFaceP[5];
        return 1;
    }
    else if (orangeFaceP[5] == orangeFaceP[4] && orangeFaceP[5] == orangeFaceP[2] && yellowFaceP[0] == yellowFaceP[3]
        && greenFaceP[0] == greenFaceP[3])
    {
        blockLocation = 5;
        blockColour = orangeFaceP[5];
        blockTailColour[0] = yellowFaceP[0];
        blockTailColour[1] = greenFaceP[3];
        return 1;
    }
    else if (greenFaceP[0] == greenFaceP[3] && greenFaceP[4] == greenFaceP[3] && orangeFaceP[2] == orangeFaceP[5]
        && yellowFaceP[1] == yellowFaceP[0])
    {
        blockLocation = 6;
        blockColour = greenFaceP[3];
        blockTailColour[0] = orangeFaceP[5];
        blockTailColour[1] = yellowFaceP[0];
        return 1;
    }

    // block in R block
    else if (yellowFaceP[1] == yellowFaceP[2] && yellowFaceP[2] == yellowFaceP[5] && blueFaceP[3] == blueFaceP[4]
        && greenFaceP[4] == greenFaceP[5])
    {
        blockLocation = 7;
        blockColour = yellowFaceP[2];
        blockTailColour[0] = blueFaceP[3];
        blockTailColour[1] = greenFaceP[5];
        return 1;
    }
    else if (blueFaceP[3] == blueFaceP[4] && blueFaceP[0] == blueFaceP[3] && yellowFaceP[5] == yellowFaceP[2]
        && greenFaceP[2] == greenFaceP[5])
    {
        blockLocation = 8;
        blockColour = blueFaceP[3];
        blockTailColour[0] = greenFaceP[5];
        blockTailColour[1] = yellowFaceP[2];
        return 1;
    }
    else if (greenFaceP[2] == greenFaceP[5] && greenFaceP[4] == greenFaceP[5] && blueFaceP[0] == blueFaceP[3]
        && yellowFaceP[1] == yellowFaceP[2])
    {
        blockLocation = 9;
        blockColour = greenFaceP[5];
        blockTailColour[0] = yellowFaceP[2];
        blockTailColour[1] = blueFaceP[3];
        return 1;
    }

    // block in U block
    else if (greenFaceP[0] == greenFaceP[1] && greenFaceP[1] == greenFaceP[2] && blueFaceP[0] == blueFaceP[1]
        && orangeFaceP[1] == orangeFaceP[2])
    {
        blockLocation = 10;
        blockColour = greenFaceP[1];
        blockTailColour[0] = blueFaceP[1];
        blockTailColour[1] = orangeFaceP[1];
        return 1;
    }
    else if (orangeFaceP[1] == orangeFaceP[2] && orangeFaceP[0] == orangeFaceP[1] && blueFaceP[1] == blueFaceP[2]
        && greenFaceP[0] == greenFaceP[1])
    {
        blockLocation = 11;
        blockColour = orangeFaceP[1];
        blockTailColour[0] = greenFaceP[1];
        blockTailColour[1] = blueFaceP[1];
        return 1;
    }
    else if (blueFaceP[0] == blueFaceP[1] && blueFaceP[1] == blueFaceP[2] && orangeFaceP[0] == orangeFaceP[1]
        && greenFaceP[1] == greenFaceP[2])
    {
        blockLocation = 12;
        blockColour = blueFaceP[1];
        blockTailColour[0] = orangeFaceP[1];
        blockTailColour[1] = greenFaceP[1];
        return 1;
    }

    return 0; // if no block exists
}

void firstBlock()
{
    if (blockPresent())
        return;

    trialP = true; // since this brute force attacks every possible solution, we don't want it to be stored in solutionList

    QStringList set;
    set << "R" << "R'" << "U" << "U'" << "L" << "L'" << "B" << "B'";
    int i, j;
    for(i = 0; i < 6; i++)
    {

        int crawler[i + 1]; //crawler is used to crawl through the set

        for(j = 0; j <= i; j++)
            crawler[j] = 0;

        do
        {
            QString key = "";

            // sets key variable to store the current combination with spaces in between
            for(j = 0; j <= i; j++)
                key = key + set[crawler[j]] + " ";


            createCheckpointP(); // in case this is not the correct combination
            convertScrambleP(key); // uses convertScramble function to convert string to simulation

            //To check if the current combination solves the first layer
            if (blockPresent())
            {
                trialP = false; // don't want to affect other parts of the program
                QStringList temp = key.split(" "); // temp list stores each move separately
                solutionListP += temp; // adds temp to solutionList (solutionList doesn't store automatically as trialP was set to true)
                return;
            }

            resetLocationP(); // if the combination doesn't satisfy "if" condition, current state is reset to try next combination

            /*To provide all possible combinations by "overflowing"
             * the first character to the second character when
             * the last character of the set is reached.
             * Ex: (For a 2 char key) if first char reaches
             * 9 then the second char is set to 'a' and the first
             * char is also set to 'a' and the first char is again
             * cycled through the set (each time the second char is
             * updated until second char reaches 9).
             */

            for(j = 0; j <= i && ++crawler[j] == 8; j++) // 8 is length of the set
            {
                crawler[j] = 0;
            }
        }
        while(j <= i);
    }
}

void centreLocation(int n[2])
{
    int i = 0;

    // U block
    if (greenFaceP[1] == blockColour && blockLocation > 0 && blockLocation < 10)
    {
        n[i] = 1;
        i++;
    }
    if (orangeFaceP[1] == blockColour && blockLocation > 0 && blockLocation < 10)
    {
        n[i] = 2;
        i++;
    }
    if (blueFaceP[1] == blockColour && blockLocation > 0 && blockLocation < 10)
    {
        n[i] = 3;
        i++;
    }

    // L block
    if (greenFaceP[3] == blockColour && (blockLocation > 6 || blockLocation < 4))
    {
        n[i] = 4;
        i++;
    }
    if (orangeFaceP[5] == blockColour && (blockLocation > 6 || blockLocation < 4))
    {
        n[i] = 5;
        i++;
    }
    if (yellowFaceP[0] == blockColour && (blockLocation > 6 || blockLocation < 4))
    {
        n[i] = 6;
        i++;
    }

    // R block
    if (greenFaceP[5] == blockColour && (blockLocation > 9 || blockLocation < 7))
    {
        n[i] = 7;
        i++;
    }
    if (blueFaceP[3] == blockColour && (blockLocation > 9 || blockLocation < 7))
    {
        n[i] = 8;
        i++;
    }
    if (yellowFaceP[2] == blockColour && (blockLocation > 9 || blockLocation < 7))
    {
        n[i] = 9;
        i++;
    }

    // B block
    if (orangeFaceP[3] == blockColour && blockLocation > 3 && blockLocation < 13)
    {
        n[i] = 10;
        i++;
    }
    if (yellowFaceP[4] == blockColour && blockLocation > 3 && blockLocation < 13)
    {
        n[i] = 11;
        i++;
    }
    if (blueFaceP[5] == blockColour && blockLocation > 3 && blockLocation < 13)
    {
        n[i] = 12;
        i++;
    }
}

int mapNewCentreLocation(int n)
{
    if (blockLocation == 1)
    {
        switch(n)
        {
            case 1: return 1;
            case 2: return 2;
            case 3: return 3;
            case 4: return 4;
            case 5: return 5;
            case 6: return 6;
            case 7: return 7;
            case 8: return 8;
            case 9: return 9;
        }
    }
    else if (blockLocation == 2)
    {
        switch(n)
        {
            case 1: return 4;
            case 2: return 6;
            case 3: return 5;
            case 4: return 7;
            case 5: return 9;
            case 6: return 8;
            case 7: return 1;
            case 8: return 2;
            case 9: return 3;
        }
    }
    else if (blockLocation == 3)
    {
        switch(n)
        {
            case 1: return 7;
            case 2: return 8;
            case 3: return 9;
            case 4: return 1;
            case 5: return 3;
            case 6: return 2;
            case 7: return 4;
            case 8: return 6;
            case 9: return 5;
        }
    }
    else if (blockLocation == 4)
    {
        switch(n)
        {
            case 1: return 2;
            case 2: return 3;
            case 3: return 1;
            case 7: return 5;
            case 8: return 4;
            case 9: return 6;
            case 10: return 8;
            case 11: return 9;
            case 12: return 7;
        }
    }
    else if (blockLocation == 5)
    {
        switch(n)
        {
            case 1: return 8;
            case 2: return 9;
            case 3: return 7;
            case 7: return 3;
            case 8: return 1;
            case 9: return 2;
            case 10: return 6;
            case 11: return 5;
            case 12: return 4;
        }
    }
    else if (blockLocation == 6)
    {
        switch(n)
        {
            case 1: return 6;
            case 2: return 5;
            case 3: return 4;
            case 7: return 9;
            case 8: return 7;
            case 9: return 8;
            case 10: return 2;
            case 11: return 3;
            case 12: return 1;
        }
    }
    else if (blockLocation == 7)
    {
        switch(n)
        {
            case 1: return 3;
            case 2: return 1;
            case 3: return 2;
            case 4: return 8;
            case 5: return 7;
            case 6: return 6;
            case 10: return 4;
            case 11: return 6;
            case 12: return 5;
        }
    }
    else if (blockLocation == 8)
    {
        switch(n)
        {
            case 1: return 5;
            case 2: return 4;
            case 3: return 6;
            case 4: return 2;
            case 5: return 1;
            case 6: return 3;
            case 10: return 7;
            case 11: return 8;
            case 12: return 9;
        }
    }
    else if (blockLocation == 9)
    {
        switch(n)
        {
            case 1: return 9;
            case 2: return 7;
            case 3: return 8;
            case 4: return 6;
            case 5: return 4;
            case 6: return 5;
            case 10: return 1;
            case 11: return 2;
            case 12: return 3;
        }
    }
    else if (blockLocation == 10)
    {
        switch(n)
        {
            case 4: return 9;
            case 5: return 8;
            case 6: return 7;
            case 7: return 6;
            case 8: return 5;
            case 9: return 4;
            case 10: return 3;
            case 11: return 1;
            case 12: return 2;
        }
    }
    else if (blockLocation == 11)
    {
        switch(n)
        {
            case 4: return 5;
            case 5: return 6;
            case 6: return 4;
            case 7: return 2;
            case 8: return 3;
            case 9: return 1;
            case 10: return 9;
            case 11: return 7;
            case 12: return 8;
        }
    }
    else if (blockLocation == 12)
    {
        switch(n)
        {
            case 4: return 3;
            case 5: return 2;
            case 6: return 1;
            case 7: return 8;
            case 8: return 9;
            case 9: return 7;
            case 10: return 5;
            case 11: return 4;
            case 12: return 6;
        }
    }

    return 0; // error

}

int newBlockLocation(int n)
{
    if (blockLocation == 1)
    {
        switch(n)
        {
            case 1: return 3;
            case 2: return 2;
        }
    }
    else if (blockLocation == 2)
    {
        switch(n)
        {
            case 1: return 1;
            case 2: return 3;
        }
    }
    else if (blockLocation == 3)
    {
        switch(n)
        {
            case 1: return 2;
            case 2: return 1;
        }
    }
    else if (blockLocation == 4)
    {
        switch(n)
        {
            case 1: return 5;
            case 2: return 6;
        }
    }
    else if (blockLocation == 5)
    {
        switch(n)
        {
            case 1: return 6;
            case 2: return 4;
        }
    }
    else if (blockLocation == 6)
    {
        switch(n)
        {
            case 1: return 4;
            case 2: return 5;
        }
    }
    else if (blockLocation == 7)
    {
        switch(n)
        {
            case 1: return 9;
            case 2: return 8;
        }
    }
    else if (blockLocation == 8)
    {
        switch(n)
        {
            case 1: return 7;
            case 2: return 9;
        }
    }
    else if (blockLocation == 9)
    {
        switch(n)
        {
            case 1: return 8;
            case 2: return 7;
        }
    }
    else if (blockLocation == 10)
    {
        switch(n)
        {
            case 1: return 11;
            case 2: return 12;
        }
    }
    else if (blockLocation == 11)
    {
        switch(n)
        {
            case 1: return 12;
            case 2: return 10;
        }
    }
    else if (blockLocation == 12)
    {
        switch(n)
        {
            case 1: return 10;
            case 2: return 11;
        }
    }
    return blockLocation; // no change
}

void lastCentre()
{
    if (blockLocation == 1 || blockLocation == 4 || blockLocation == 7)
    {
        if (greenFaceP[1] == orangeFaceP[3])
            U_P();
        else if (greenFaceP[1] == blueFaceP[3])
            Ui_P();
    }
    else if (blockLocation == 2 || blockLocation == 5 || blockLocation == 11)
    {
        if (greenFaceP[5] == blueFaceP[1])
            R_P();
        else if (greenFaceP[5] == yellowFaceP[0])
            Ri_P();
    }
    else if (blockLocation == 3 || blockLocation == 8 || blockLocation == 12)
    {
        if (greenFaceP[3] == orangeFaceP[1])
            Li_P();
        else if (greenFaceP[3] == yellowFaceP[2])
            L_P();
    }
    else if (blockLocation == 6 || blockLocation == 9 || blockLocation == 10)
    {
        if (orangeFaceP[3] == yellowFaceP[0])
            B_P();
        else if (orangeFaceP[3] == blueFaceP[1])
            Bi_P();
    }
}

void centres()
{
    int cL[2];
    int blockRotation = 0; // 1 if Cw, 2 if Ccw
    centreLocation(cL);
    cL[0] = mapNewCentreLocation(cL[0]);
    cL[1] = mapNewCentreLocation(cL[1]);

    // sorting by swapping
    if (cL[0] > cL[1])
    {
        int temp = cL[0];
        cL[0] = cL[1];
        cL[1] = temp;
    }

    // solution for first two centres (same colour as block)

    // if a centre is in 1 and all other possibilites
    if (cL[0] == 1 && cL[1] == 4)
    {
        u_P();b_P();li_P();b_P();
        blockRotation = 2;
    }
    else if (cL[0] == 1 && cL[1] == 5)
    {
        u_P();bi_P();
        blockRotation = 2;
    }
    else if (cL[0] == 1 && cL[1] == 6)
    {
        u_P();b_P();l_P();b_P();
        blockRotation = 2;
    }
    else if (cL[0] == 1 && cL[1] == 7)
    {
        ui_P();bi_P();r_P();bi_P();
        blockRotation = 1;
    }
    else if (cL[0] == 1 && cL[1] == 8)
    {
        ui_P();b_P();
        blockRotation = 1;
    }
    else if (cL[0] == 1 && cL[1] == 9)
    {
        ui_P();bi_P();ri_P();bi_P();
        blockRotation = 1;
    }

    // if a centre is in 2 and all other possibilities
    else if (cL[0] == 2 && cL[1] == 4)
    {
        b_P();li_P();b_P();
        blockRotation = 2;
    }
    else if (cL[0] == 2 && cL[1] == 5)
    {
        bi_P();
        blockRotation = 2;
    }
    else if (cL[0] == 2 && cL[1] == 6)
    {
        b_P();l_P();b_P();
        blockRotation = 2;
    }
    else if (cL[0] == 2 && cL[1] == 7)
    {
        u_P();bi_P();r_P();bi_P();
        blockRotation = 1;
    }
    else if (cL[0] == 2 && cL[1] == 8)
    {
        u_P();b_P();
        blockRotation = 1;
    }
    else if (cL[0] == 2 && cL[1] == 9)
    {
        u_P();bi_P();ri_P();bi_P();
        blockRotation = 1;
    }

    // if a centre is in 3 and all other possibilities
    else if (cL[0] == 3 && cL[1] == 4)
    {
        ui_P();b_P();li_P();b_P();
        blockRotation = 2;
    }
    else if (cL[0] == 3 && cL[1] == 5)
    {
        ui_P();bi_P();
        blockRotation = 2;
    }
    else if (cL[0] == 3 && cL[1] == 6)
    {
        ui_P();b_P();l_P();b_P();
        blockRotation = 2;
    }
    else if (cL[0] == 3 && cL[1] == 7)
    {
        bi_P();r_P();bi_P();
        blockRotation = 1;
    }
    else if (cL[0] == 3 && cL[1] == 8)
    {
        b_P();
        blockRotation = 1;
    }
    else if (cL[0] == 3 && cL[1] == 9)
    {
        bi_P();ri_P();bi_P();
        blockRotation = 1;
    }

    // if a centre is in 4 and all other possibilities
    else if (cL[0] == 4 && cL[1] == 7)
    {
        b_P();l_P();b_P();ri_P();b_P();
    }
    else if (cL[0] == 4 && cL[1] == 8)
    {
        b_P();l_P();b_P();r_P();b_P();
    }
    else if (cL[0] == 4 && cL[1] == 9)
    {
        b_P();l_P();bi_P();
    }

    // if a centre is in 5 and all other possibilities
    else if (cL[0] == 5 && cL[1] == 7)
    {
        b_P();li_P();b_P();ri_P();b_P();
    }
    else if (cL[0] == 5 && cL[1] == 8)
    {
        b_P();li_P();b_P();r_P();b_P();
    }
    else if (cL[0] == 5 && cL[1] == 9)
    {
        b_P();li_P();bi_P();
    }

    // if a centre is in 6 and all other possibilities
    else if (cL[0] == 6 && cL[1] == 7)
    {
        bi_P();ri_P();b_P();
    }
    else if (cL[0] == 6 && cL[1] == 8)
    {
        bi_P();r_P();b_P();
    }
    else if (cL[0] == 6 && cL[1] == 9)
    {
        // solved
    }

    blockLocation = newBlockLocation(blockRotation);

    lastCentre();
}

int edgeLocation(QString &edgeColour)
{
    if (orangeFaceP[0] == edgeColour[0] && blueFaceP[2] == edgeColour[1])
    {
        return 1;
    }
    else if (orangeFaceP[0] == edgeColour[1] && blueFaceP[2] == edgeColour[0])
    {
        return 2;
    }
    else if (greenFaceP[0] == edgeColour[0] && orangeFaceP[2] == edgeColour[1])
    {
        return 3;
    }
    else if (greenFaceP[0] == edgeColour[1] && orangeFaceP[2] == edgeColour[0])
    {
        return 4;
    }
    else if (greenFaceP[2] == edgeColour[0] && blueFaceP[0] == edgeColour[1])
    {
        return 5;
    }
    else if (greenFaceP[2] == edgeColour[1] && blueFaceP[0] == edgeColour[0])
    {
        return 6;
    }
    else if (greenFaceP[4] == edgeColour[0] && yellowFaceP[1] == edgeColour[1])
    {
        return 7;
    }
    else if (greenFaceP[4] == edgeColour[1] && yellowFaceP[1] == edgeColour[0])
    {
        return 8;
    }
    else if (orangeFaceP[4] == edgeColour[0] && yellowFaceP[3] == edgeColour[1])
    {
        return 9;
    }
    else if (orangeFaceP[4] == edgeColour[1] && yellowFaceP[3] == edgeColour[0])
    {
        return 10;
    }
    else if (blueFaceP[4] == edgeColour[0] && yellowFaceP[5] == edgeColour[1])
    {
        return 11;
    }
    else if (blueFaceP[4] == edgeColour[1] && yellowFaceP[5] == edgeColour[0])
    {
        return 12;
    }

    return 0; // error
}

int mapNewEdgeLocation(int n)
{
    if (blockLocation == 1)
    {
        switch(n)
        {
            case 1: return 1;
            case 2: return 2;
            case 3: return 3;
            case 4: return 4;
            case 5: return 5;
            case 6: return 6;
            case 7: return 7;
            case 8: return 8;
        }
    }
    else if (blockLocation == 2)
    {
        switch(n)
        {
            case 3: return 7;
            case 4: return 8;
            case 5: return 3;
            case 6: return 4;
            case 7: return 5;
            case 8: return 6;
            case 11: return 1;
            case 12: return 2;
        }
    }
    else if (blockLocation == 3)
    {
        switch(n)
        {
            case 3: return 5;
            case 4: return 6;
            case 5: return 7;
            case 6: return 8;
            case 7: return 3;
            case 8: return 4;
            case 9: return 2;
            case 10: return 1;
        }
    }
    else if (blockLocation == 4)
    {
        switch(n)
        {
            case 1: return 6;
            case 2: return 5;
            case 3: return 1;
            case 4: return 2;
            case 5: return 4;
            case 6: return 3;
            case 11: return 7;
            case 12: return 8;
        }
    }
    else if (blockLocation == 5)
    {
        switch(n)
        {
            case 1: return 8;
            case 2: return 7;
            case 5: return 6;
            case 6: return 5;
            case 7: return 2;
            case 8: return 1;
            case 11: return 3;
            case 12: return 4;
        }
    }
    else if (blockLocation == 6)
    {
        switch(n)
        {
            case 1: return 4;
            case 2: return 3;
            case 5: return 8;
            case 6: return 7;
            case 9: return 1;
            case 10: return 2;
            case 11: return 5;
            case 12: return 6;
        }
    }
    else if (blockLocation == 7)
    {
        switch(n)
        {
            case 1: return 3;
            case 2: return 4;
            case 3: return 6;
            case 4: return 5;
            case 5: return 2;
            case 6: return 1;
            case 9: return 7;
            case 10: return 8;
        }
    }
    else if (blockLocation == 8)
    {
        switch(n)
        {
            case 1: return 7;
            case 2: return 8;
            case 3: return 4;
            case 4: return 3;
            case 7: return 1;
            case 8: return 2;
            case 9: return 5;
            case 10: return 6;
        }
    }
    else if (blockLocation == 9)
    {
        switch(n)
        {
            case 1: return 5;
            case 2: return 6;
            case 3: return 8;
            case 4: return 7;
            case 9: return 3;
            case 10: return 4;
            case 11: return 2;
            case 12: return 1;
        }
    }
    else if (blockLocation == 10)
    {
        switch(n)
        {
            case 1: return 2;
            case 2: return 1;
            case 7: return 8;
            case 8: return 7;
            case 9: return 6;
            case 10: return 5;
            case 11: return 4;
            case 12: return 3;
        }
    }
    else if (blockLocation == 11)
    {
        switch(n)
        {
            case 5: return 1;
            case 6: return 2;
            case 7: return 4;
            case 8: return 3;
            case 9: return 8;
            case 10: return 7;
            case 11: return 6;
            case 12: return 5;
        }
    }
    else if (blockLocation == 12)
    {
        switch(n)
        {
            case 3: return 2;
            case 4: return 1;
            case 7: return 6;
            case 8: return 5;
            case 9: return 4;
            case 10: return 3;
            case 11: return 8;
            case 12: return 7;
        }
    }

    return 0; // error
}

void backEdge()
{
    int bEL = mapNewEdgeLocation(edgeLocation(blockTailColour));

    // solution

    if (bEL == 1)
    {
        // solved
    }
    else if (bEL == 2)
    {
        li_P();b_P();l_P();bi_P();u_P();bi_P();ui_P();b_P();
    }
    else if (bEL == 3)
    {
        li_P();ui_P();l_P();u_P();
    }
    else if (bEL == 4)
    {
        ui_P();l_P();ri_P();li_P();r_P();u_P();
    }
    else if (bEL == 5)
    {
        u_P();ri_P();l_P();r_P();li_P();ui_P();
    }
    else if (bEL == 6)
    {
        r_P();u_P();ri_P();ui_P();
    }
    else if (bEL == 7)
    {
        u_P();r_P();ui_P();ri_P();
    }
    else if (bEL == 8)
    {
        ui_P();li_P();u_P();l_P();
    }
}

QStringList identifyLastThreeEdges()
{
    QStringList temp;
    QString temp1, temp2, temp3;

    if (blockColour != 'g' && blockTailColour[0] != 'g' && blockTailColour[1] != 'g')
    {
        temp1 = 'g' + blockColour;
        temp2 = "g" + blockTailColour[0];
        temp3 = "g" + blockTailColour[1];
        temp << temp1 << temp2 << temp3;
    }
    else if (blockColour != 'y' && blockTailColour[0] != 'y' && blockTailColour[1] != 'y')
    {
        temp1 = 'y' + blockColour;
        temp2 = "y" + blockTailColour[0];
        temp3 = "y" + blockTailColour[1];
        temp << temp1 << temp2 << temp3;
    }
    else if (blockColour != 'o' && blockTailColour[0] != 'o' && blockTailColour[1] != 'o')
    {
        temp1 = 'o' + blockColour;
        temp2 = "o" + blockTailColour[0];
        temp3 = "o" + blockTailColour[1];
        temp << temp1 << temp2 << temp3;
    }
    else if (blockColour != 'b' && blockTailColour[0] != 'b' && blockTailColour[1] != 'b')
    {
        temp1 = 'b' + blockColour;
        temp2 = "b" + blockTailColour[0];
        temp3 = "b" + blockTailColour[1];
        temp << temp1 << temp2 << temp3;
    }

    return temp;
}

void lastThreeEdges()
{
    QStringList lastEdge = identifyLastThreeEdges();
    int e1 = mapNewEdgeLocation(edgeLocation(lastEdge[0]));
    int e2 = mapNewEdgeLocation(edgeLocation(lastEdge[1]));
    int e3 = mapNewEdgeLocation(edgeLocation(lastEdge[2]));

    // solution

    // normal insertions (R U' R' / L U L' type)
    if (e1 == 3 && e2 == 6 && e3 == 8)
    {
        r_P();ui_P();ri_P();u_P();
    }
    else if (e1 == 5 && e2 == 8 && e3 == 4)
    {
        li_P();u_P();l_P();ui_P();
    }

    // normal insertions (U' R U R' / U L' U' L type)
    else if (e1 == 6 && e2 == 7 && e3 == 4)
    {
        ui_P();r_P();u_P();ri_P();
    }
    else if (e1 == 4 && e2 == 6 && e3 == 7)
    {
        u_P();li_P();ui_P();l_P();
    }

    // sledgehammer insertions (R' L R L' / L R' L' R type)
    else if (e1 == 6 && e2 == 8 && e3 == 3)
    {
        ri_P();l_P();r_P();li_P();
    }
    else if (e1 == 4 && e2 == 5 && e3 == 8)
    {
        l_P();ri_P();li_P();r_P();
    }

    // two edge flip
    else if (e1 == 7 && e2 == 4 && e3 == 6)
    {
        ri_P();l_P();r_P();li_P();u_P();li_P();ui_P();l_P();
    }
    else if (e1 == 8 && e2 == 4 && e3 == 5)
    {
        ui_P();r_P();u_P();ri_P();l_P();ri_P();li_P();r_P();
    }
    else if (e1 == 8 && e2 == 3 && e3 == 6)
    {
         u_P();li_P();ui_P();l_P();ri_P();l_P();r_P();li_P();
    }

    // three cycle - same colour facing
    else if (e1 == 3 && e2 == 5 && e3 == 7)
    {
        ui_P();r_P();u_P();r_P();l_P();r_P();li_P();
    }
    else if (e1 == 5 && e2 == 7 && e3 == 3)
    {
        u_P();li_P();ui_P();li_P();ri_P();li_P();r_P();
    }
}

/* This function takes any list (array of strings which contain each move of the solution in a different block)
 * and "reduces" it. "Reducing" means shortening segments like "U2 U'" which can simply be written as "U", etc.
 * Sometimes, it does not reduce the move count at all but usually reduces around 2-5 moves.
 */
QStringList shortSolutionP(QStringList &list)
{
    // for every element in the list
    for (int i = 0; i < list.length() - 1; i++)
    {
        // if the first letter in a string equals the first letter in the next string (Ex: "U U2")
        if (list[i] != "" && (list[i][0] == list[i + 1][0]))
        {
            /* different possible cases for the second letter in each string such as
             * U2 U' or U U or U' U, etc. 9 possible cases.
             * These if blocks copy the result into the second string and store the
             * value "trash" in the first string which is later removed
             */

            if (list[i][1] == '\0' && list[i + 1][1] == '\0')
            {
                list[i + 1] = list[i][0] + "'";
                list[i] = "trash";
            }
            else if (list[i][1] == 39 && list[i + 1][1] == 39)
            {
                list[i + 1] = list[i][0];
                list[i] = "trash";
            }
            else if (list[i][1] == '\0' && list[i + 1][1] == 39)
            {
                list[i] = "trash";
                list[i + 1] = "trash";
            }
            else if (list[i][1] == 39 && list[i + 1][1] == '\0')
            {
                list[i] = "trash";
                list[i + 1] = "trash";
            }
        }
    }
    list.removeAll("trash"); // all trash values are removed
    return list;
}

// function that accepts a string and returns the move count as an integer
int findMoveCountP(QString &s)
{
    int mc = 0;
    for (int i = 0; i < s.length(); i++)
    {
        // move count is incremented every time an alphabet is encountered in the string
        if (s[i] == 'L' || s[i] == 'R' || s[i] == 'U' || s[i] == 'B')
            mc++;
    }
    return mc;
}

void solveCubePyra()
{
    // Everything is cleared and kept empty to store the solution
    solutionListP.clear();
    solutionP = "";
    solutionP_short = "";
    moveCountP = 0;
    moveCountP_short = 0;

    // solve tips
    tips();
    solutionListP.append("trash");

    // executes first layer
    firstBlock();
    solutionListP.append("trash");

    centres();
    solutionListP.append("trash");

    backEdge();
    solutionListP.append("trash");

    lastThreeEdges();
    solutionListP.append("trash");

    // stores the list as a string with each element separated by a space
    solutionP = solutionListP.join(" ");

    // create a temp list which stores different parts of the solution2, each, as an element
    QStringList solutionListP_temp = solutionP.split("trash");

    // create sub-lists which take solutionList2_temp and store each of its element as a separate list which contains
    // each element as a separate move (similar to solutionList2, only difference being, firstLayer list stores only the
    // solution2 for first layer and lastLayer stores solution2 for last layer
    QStringList tips = solutionListP_temp[0].split(" "), fB = solutionListP_temp[1].split(" "),
            cen = solutionListP_temp[2].split(" "), bE = solutionListP_temp[3].split(" "),
            l3 = solutionListP_temp[4].split(" ");

    // shortens each list by merging moves like L L2, etc. Any number can be used instead of 10
    // That number signifies how many times the solution2 is shortened
    // Ex: U2 L L2 L U -> U2 U -> U'
    for (int i = 0; i < 10; i++)
    {
        fB = shortSolutionP(fB);
        cen = shortSolutionP(cen);
        bE = shortSolutionP(bE);
        l3 = shortSolutionP(l3);
    }

    // solutionP string stores the entire solution2, formatted neatly and displays the solution2 in different steps
    solutionP =  "Tips: " + tips.join(" ") + '\n' + "First Block: " + fB.join(" ") + '\n' +
            "Centres: " + cen.join(" ") + '\n' + "Back Edge: " + bE.join(" ") + '\n' + "Last 3 Edges: " + l3.join(" ");

    // this string is the raw concatenation of different steps
    QString solutionP_full = tips.join(" ") + fB.join(" ") + cen.join(" ") + bE.join(" ") + l3.join(" ");

    // the above string is used to find moveCount2
    moveCountP = findMoveCountP(solutionP_full);

    // shortens the solution2 multiple times (20 is not required. Can be any number >= 1 )
    for (int i = 0; i < 20; i++)
        solutionListP = shortSolutionP(solutionListP);

    // joins all elements (moves) of the solutionList2 to create a string
    solutionP_short = solutionListP.join(" ");

    // the string is then used to find the reduced moveCount2
    moveCountP_short = findMoveCountP(solutionP_short);
}
