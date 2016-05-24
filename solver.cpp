#include <QApplication>
#include <QString>
#include <QStringList>
#include "solver.h"

/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Variable Declarations //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// these variables store the scrambled state of the cube used by scrambledialog.cpp
extern QString whiteFace_scramble, yellowFace_scramble, greenFace_scramble,
                blueFace_scramble, redFace_scramble, orangeFace_scramble;

// stores the scramble string inputted by the user
extern QString scramble;

// current state variables
QString whiteFace = "wwwwwwwww";
QString yellowFace = "yyyyyyyyy";
QString greenFace = "ggggggggg";
QString blueFace = "bbbbbbbbb";
QString redFace = "rrrrrrrrr";
QString orangeFace = "ooooooooo";

// variables used to create checkpoint locations
QString blueFace_cp, whiteFace_cp, greenFace_cp, orangeFace_cp, yellowFace_cp, redFace_cp;

// variables used to find orientation and colours of F2L corners
QString orient,c;

// variable used to store every move of the solution in a list
QStringList solutionList;

// strings that store the solution or a reduced solution
QString solution;
QString solution_short;

//variables that store the no. of moves for the respective solution
int moveCount;
int moveCount_short;

// y determines amount of "y" (clockwise rotation of cube) required for an alg (to reduce moveCount)
int y;

// trial variable is used to check amount of "y" needed for alg. Used with checkpoint variables. 1 or 0
bool trial = false;

/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CubeSolver Implementation /////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// creates a checkpoint to which the current state variables can be restored after determining "y" value
void createCheckpoint()
{
    blueFace_cp = blueFace;
    whiteFace_cp = whiteFace;
    greenFace_cp = greenFace;
    orangeFace_cp = orangeFace;
    yellowFace_cp = yellowFace;
    redFace_cp = redFace;
}

// resets the current state variables to the checkpoint location
void resetLocation()
{
    blueFace = blueFace_cp;
    whiteFace = whiteFace_cp;
    greenFace = greenFace_cp;
    orangeFace = orangeFace_cp;
    yellowFace = yellowFace_cp;
    redFace = redFace_cp;
}

// Rotation Functions used to simulate a turn of a face of the cube
void Cw(QString &face, QString &face_temp)
{
    face[0] = face_temp[6];
    face[1] = face_temp[3];
    face[2] = face_temp[0];
    face[3] = face_temp[7];
    face[4] = face_temp[4];
    face[5] = face_temp[1];
    face[6] = face_temp[8];
    face[7] = face_temp[5];
    face[8] = face_temp[2];

}
void Ccw(QString &face, QString &face_temp)
{
    face[0] = face_temp[2];
    face[1] = face_temp[5];
    face[2] = face_temp[8];
    face[3] = face_temp[1];
    face[4] = face_temp[4];
    face[5] = face_temp[7];
    face[6] = face_temp[0];
    face[7] = face_temp[3];
    face[8] = face_temp[6];

}
void Cw2(QString &face, QString &face_temp)
{
    face[0] = face_temp[8];
    face[1] = face_temp[7];
    face[2] = face_temp[6];
    face[3] = face_temp[5];
    face[4] = face_temp[4];
    face[5] = face_temp[3];
    face[6] = face_temp[2];
    face[7] = face_temp[1];
    face[8] = face_temp[0];

}
void L()
{
    QString blueFace_temp, whiteFace_temp, greenFace_temp, orangeFace_temp, yellowFace_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace_temp[i] = blueFace[i];
        whiteFace_temp[i] = whiteFace[i];
        greenFace_temp[i] = greenFace[i];
        orangeFace_temp[i] = orangeFace[i];
        yellowFace_temp[i] = yellowFace[i];
    }

    for (int i = 0; i < 9; i += 3)
    {
        whiteFace[i] = blueFace_temp[8 - i];
        greenFace[i] = whiteFace_temp[i];
        yellowFace[i] = greenFace_temp[i];
        blueFace[8 - i] = yellowFace_temp[i];
    }

    Cw(orangeFace, orangeFace_temp);
    if (trial == false)
    {
        solutionList.append("L");
    }

}
void Li()
{
    QString blueFace_temp, whiteFace_temp, greenFace_temp, orangeFace_temp, yellowFace_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace_temp[i] = blueFace[i];
        whiteFace_temp[i] = whiteFace[i];
        greenFace_temp[i] = greenFace[i];
        orangeFace_temp[i] = orangeFace[i];
        yellowFace_temp[i] = yellowFace[i];
    }
    for (int i = 0; i < 9; i += 3)
    {
        whiteFace[i] = greenFace_temp[i];
        greenFace[i] = yellowFace_temp[i];
        yellowFace[i] = blueFace_temp[8 - i];
        blueFace[8 - i] = whiteFace_temp[i];
    }

    Ccw(orangeFace, orangeFace_temp);
    if (trial == false)
    {
        solutionList.append("L'");
    }
}
void R()
{
    QString blueFace_temp, whiteFace_temp, greenFace_temp, redFace_temp, yellowFace_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace_temp[i] = blueFace[i];
        whiteFace_temp[i] = whiteFace[i];
        greenFace_temp[i] = greenFace[i];
        redFace_temp[i] = redFace[i];
        yellowFace_temp[i] = yellowFace[i];
    }
    for (int i = 2; i < 9; i += 3)
    {
        whiteFace[i] = greenFace_temp[i];
        greenFace[i] = yellowFace_temp[i];
        yellowFace[i] = blueFace_temp[8 - i];
        blueFace[8 - i] = whiteFace_temp[i];
    }

    Cw(redFace, redFace_temp);
    if (trial == false)
    {
        solutionList.append("R");
    }
}
void Ri()
{
    QString blueFace_temp, whiteFace_temp, greenFace_temp, redFace_temp, yellowFace_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace_temp[i] = blueFace[i];
        whiteFace_temp[i] = whiteFace[i];
        greenFace_temp[i] = greenFace[i];
        redFace_temp[i] = redFace[i];
        yellowFace_temp[i] = yellowFace[i];
    }
    for (int i = 2; i < 9; i += 3)
    {
        whiteFace[i] = blueFace_temp[8 - i];
        greenFace[i] = whiteFace_temp[i];
        yellowFace[i] = greenFace_temp[i];
        blueFace[8 - i] = yellowFace_temp[i];
    }

    Ccw(redFace, redFace_temp);
    if (trial == false)
    {
        solutionList.append("R'");
    }
}
void U()
{
    QString blueFace_temp, whiteFace_temp, greenFace_temp, redFace_temp, orangeFace_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace_temp[i] = blueFace[i];
        whiteFace_temp[i] = whiteFace[i];
        greenFace_temp[i] = greenFace[i];
        redFace_temp[i] = redFace[i];
        orangeFace_temp[i] = orangeFace[i];
    }
    for (int i = 0; i < 3; i++)
    {
        redFace[i] = blueFace_temp[i];
        greenFace[i] = redFace_temp[i];
        orangeFace[i] = greenFace_temp[i];
        blueFace[i] = orangeFace_temp[i];
    }

    Cw(whiteFace, whiteFace_temp);

    if (trial == false)
    {
        solutionList.append("U");
    }
}
void Uinv()
{
    QString blueFace_temp, whiteFace_temp, greenFace_temp, redFace_temp, orangeFace_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace_temp[i] = blueFace[i];
        whiteFace_temp[i] = whiteFace[i];
        greenFace_temp[i] = greenFace[i];
        redFace_temp[i] = redFace[i];
        orangeFace_temp[i] = orangeFace[i];
    }
    for (int i = 0; i < 3; i++)
    {
        redFace[i] = greenFace_temp[i];
        greenFace[i] = orangeFace_temp[i];
        orangeFace[i] = blueFace_temp[i];
        blueFace[i] = redFace_temp[i];
    }

    Ccw(whiteFace, whiteFace_temp);
    if (trial == false)
    {
        solutionList.append("U'");
    }
}
void D()
{
    QString blueFace_temp, yellowFace_temp, greenFace_temp, redFace_temp, orangeFace_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace_temp[i] = blueFace[i];
        yellowFace_temp[i] = yellowFace[i];
        greenFace_temp[i] = greenFace[i];
        redFace_temp[i] = redFace[i];
        orangeFace_temp[i] = orangeFace[i];
    }
    for (int i = 6; i < 9; i++)
    {
        redFace[i] = greenFace_temp[i];
        greenFace[i] = orangeFace_temp[i];
        orangeFace[i] = blueFace_temp[i];
        blueFace[i] = redFace_temp[i];
    }

    Cw(yellowFace, yellowFace_temp);
    if (trial == false)
    {
        solutionList.append("D");
    }

}
void Di()
{
    QString blueFace_temp, yellowFace_temp, greenFace_temp, redFace_temp, orangeFace_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace_temp[i] = blueFace[i];
        yellowFace_temp[i] = yellowFace[i];
        greenFace_temp[i] = greenFace[i];
        redFace_temp[i] = redFace[i];
        orangeFace_temp[i] = orangeFace[i];
    }
    for (int i = 6; i < 9; i++)
    {
        redFace[i] = blueFace_temp[i];
        greenFace[i] = redFace_temp[i];
        orangeFace[i] = greenFace_temp[i];
        blueFace[i] = orangeFace_temp[i];
    }

    Ccw(yellowFace, yellowFace_temp);
    if (trial == false)
    {
        //printf("D' ");
        solutionList.append("D'");

    }
}
void F()
{
    QString whiteFace_temp, yellowFace_temp, greenFace_temp, redFace_temp, orangeFace_temp;
    for (int i = 0; i < 9; i++)
    {
        whiteFace_temp[i] = whiteFace[i];
        yellowFace_temp[i] = yellowFace[i];
        greenFace_temp[i] = greenFace[i];
        redFace_temp[i] = redFace[i];
        orangeFace_temp[i] = orangeFace[i];
    }
    for (int i = 0, j = 0; i < 3; i++, j += 3)
    {
        whiteFace[8 - i] = orangeFace_temp[j + 2];
        redFace[j] = whiteFace_temp[i + 6];
        yellowFace[2 - i] = redFace_temp[j];
        orangeFace[j + 2] = yellowFace_temp[i];
    }

    Cw(greenFace, greenFace_temp);
    if (trial == false)
    {
        solutionList.append("F");
    }
}
void Fi()
{
    QString whiteFace_temp, yellowFace_temp, greenFace_temp, redFace_temp, orangeFace_temp;
    for (int i = 0; i < 9; i++)
    {
        whiteFace_temp[i] = whiteFace[i];
        yellowFace_temp[i] = yellowFace[i];
        greenFace_temp[i] = greenFace[i];
        redFace_temp[i] = redFace[i];
        orangeFace_temp[i] = orangeFace[i];
    }
    for (int i = 0, j = 0; i < 3; i++, j += 3)
    {
        whiteFace[i + 6] = redFace_temp[j];
        redFace[j] = yellowFace_temp[2 - i];
        yellowFace[i] = orangeFace_temp[j + 2];
        orangeFace[j + 2] = whiteFace_temp[8 - i];
    }

    Ccw(greenFace, greenFace_temp);
    if (trial == false)
    {
        solutionList.append("F'");
    }
}
void B()
{
    QString whiteFace_temp, yellowFace_temp, blueFace_temp, redFace_temp, orangeFace_temp;
    for (int i = 0; i < 9; i++)
    {
        whiteFace_temp[i] = whiteFace[i];
        yellowFace_temp[i] = yellowFace[i];
        blueFace_temp[i] = blueFace[i];
        redFace_temp[i] = redFace[i];
        orangeFace_temp[i] = orangeFace[i];
    }
    for (int i = 0, j = 0; i < 3; i++, j += 3)
    {
        whiteFace[i] = redFace_temp[j + 2];
        redFace[j + 2] = yellowFace_temp[8 - i];
        yellowFace[i + 6] = orangeFace_temp[j];
        orangeFace[j] = whiteFace_temp[2 - i];
    }

    Cw(blueFace, blueFace_temp);
    if (trial == false)
    {
        solutionList.append("B");
    }
}
void Bi()
{
    QString whiteFace_temp, yellowFace_temp, blueFace_temp, redFace_temp, orangeFace_temp;
    for (int i = 0; i < 9; i++)
    {
        whiteFace_temp[i] = whiteFace[i];
        yellowFace_temp[i] = yellowFace[i];
        blueFace_temp[i] = blueFace[i];
        redFace_temp[i] = redFace[i];
        orangeFace_temp[i] = orangeFace[i];
    }
    for (int i = 0, j = 0; i < 3; i++, j += 3)
    {
        whiteFace[2 - i] = orangeFace_temp[j];
        redFace[j + 2] = whiteFace_temp[i];
        yellowFace[8 - i] = redFace_temp[j + 2];
        orangeFace[j] = yellowFace_temp[i + 6];
    }

    Ccw(blueFace, blueFace_temp);
    if (trial == false)
    {
        solutionList.append("B'");
    }
}
void L2()
{
    QString blueFace_temp, whiteFace_temp, greenFace_temp, orangeFace_temp, yellowFace_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace_temp[i] = blueFace[i];
        whiteFace_temp[i] = whiteFace[i];
        greenFace_temp[i] = greenFace[i];
        orangeFace_temp[i] = orangeFace[i];
        yellowFace_temp[i] = yellowFace[i];
    }

    for (int i = 0; i < 9; i += 3)
    {
        whiteFace[i] = yellowFace_temp[i];
        greenFace[i] = blueFace_temp[8 - i];
        yellowFace[i] = whiteFace_temp[i];
        blueFace[8 - i] = greenFace_temp[i];
    }

    Cw2(orangeFace, orangeFace_temp);
    if (trial == false)
    {
        solutionList.append("L2");
    }
}
void R2()
{
    QString blueFace_temp, whiteFace_temp, greenFace_temp, redFace_temp, yellowFace_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace_temp[i] = blueFace[i];
        whiteFace_temp[i] = whiteFace[i];
        greenFace_temp[i] = greenFace[i];
        redFace_temp[i] = redFace[i];
        yellowFace_temp[i] = yellowFace[i];
    }
    for (int i = 2; i < 9; i += 3)
    {
        whiteFace[i] = yellowFace_temp[i];
        greenFace[i] = blueFace_temp[8 - i];
        yellowFace[i] = whiteFace_temp[i];
        blueFace[8 - i] = greenFace_temp[i];
    }

    Cw2(redFace, redFace_temp);
    if (trial == false)
    {
        solutionList.append("R2");
    }
}
void U2()
{
    QString blueFace_temp, whiteFace_temp, greenFace_temp, redFace_temp, orangeFace_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace_temp[i] = blueFace[i];
        whiteFace_temp[i] = whiteFace[i];
        greenFace_temp[i] = greenFace[i];
        redFace_temp[i] = redFace[i];
        orangeFace_temp[i] = orangeFace[i];
    }
    for (int i = 0; i < 3; i++)
    {
        redFace[i] = orangeFace_temp[i];
        greenFace[i] = blueFace_temp[i];
        orangeFace[i] = redFace_temp[i];
        blueFace[i] = greenFace_temp[i];
    }

    Cw2(whiteFace, whiteFace_temp);
    if (trial == false)
    {
        solutionList.append("U2");
    }
}
void D2()
{
    QString blueFace_temp, yellowFace_temp, greenFace_temp, redFace_temp, orangeFace_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace_temp[i] = blueFace[i];
        yellowFace_temp[i] = yellowFace[i];
        greenFace_temp[i] = greenFace[i];
        redFace_temp[i] = redFace[i];
        orangeFace_temp[i] = orangeFace[i];
    }
    for (int i = 6; i < 9; i++)
    {
        redFace[i] = orangeFace_temp[i];
        greenFace[i] = blueFace_temp[i];
        orangeFace[i] = redFace_temp[i];
        blueFace[i] = greenFace_temp[i];
    }

    Cw2(yellowFace, yellowFace_temp);
    if (trial == false)
    {
        solutionList.append("D2");
    }
}
void F2()
{
    QString whiteFace_temp, yellowFace_temp, greenFace_temp, redFace_temp, orangeFace_temp;
    for (int i = 0; i < 9; i++)
    {
        whiteFace_temp[i] = whiteFace[i];
        yellowFace_temp[i] = yellowFace[i];
        greenFace_temp[i] = greenFace[i];
        redFace_temp[i] = redFace[i];
        orangeFace_temp[i] = orangeFace[i];
    }
    for (int i = 0, j = 0; i < 3; i++, j += 3)
    {
        whiteFace[i + 6] = yellowFace_temp[2 - i];
        redFace[j] = orangeFace_temp[8 - j];
        yellowFace[2 - i] = whiteFace_temp[i + 6];
        orangeFace[8 - j] = redFace_temp[j];
    }

    Cw2(greenFace, greenFace_temp);
    if (trial == false)
    {
        solutionList.append("F2");
    }
}
void B2()
{
    QString whiteFace_temp, yellowFace_temp, blueFace_temp, redFace_temp, orangeFace_temp;
    for (int i = 0; i < 9; i++)
    {
        whiteFace_temp[i] = whiteFace[i];
        yellowFace_temp[i] = yellowFace[i];
        blueFace_temp[i] = blueFace[i];
        redFace_temp[i] = redFace[i];
        orangeFace_temp[i] = orangeFace[i];
    }
    for (int i = 0, j = 0; i < 3; i++, j += 3)
    {
        whiteFace[i] = yellowFace_temp[8 - i];
        redFace[8 - j] = orangeFace_temp[j];
        yellowFace[8 - i] = whiteFace_temp[i];
        orangeFace[j] = redFace_temp[8 - j];
    }

    Cw2(blueFace, blueFace_temp);
    if (trial == false)
    {
        solutionList.append("B2");
    }
}

// rotation modifier functions - used to change alg based on "y" value

void l()
{
    switch(y)
    {
        case 1: F(); break;
        case 2: R(); break;
        case -1: B(); break;
        case 0: L(); break;
    }
}
void li()
{
    switch(y)
    {
        case 1: Fi(); break;
        case 2: Ri(); break;
        case -1: Bi(); break;
        case 0: Li(); break;
    }
}
void r()
{
    switch(y)
    {
        case 1: B(); break;
        case 2: L(); break;
        case -1: F(); break;
        case 0: R(); break;
    }
}
void ri()
{
    switch(y)
    {
        case 1: Bi(); break;
        case 2: Li(); break;
        case -1: Fi(); break;
        case 0: Ri(); break;
    }
}
void u()
{
    switch(y)
    {
        case 1: U(); break;
        case 2: U(); break;
        case -1: U(); break;
        case 0: U(); break;
    }
}
void uinv()
{
    switch(y)
    {
        case 1: Uinv(); break;
        case 2: Uinv(); break;
        case -1: Uinv(); break;
        case 0: Uinv(); break;
    }
}
void d()
{
    switch(y)
    {
        case 1: D(); break;
        case 2: D(); break;
        case -1: D(); break;
        case 0: D(); break;
    }
}
void di()
{
    switch(y)
    {
        case 1: Di(); break;
        case 2: Di(); break;
        case -1: Di(); break;
        case 0: Di(); break;
    }
}
void f()
{
    switch(y)
    {
        case 1: R(); break;
        case 2: B(); break;
        case -1: L(); break;
        case 0: F(); break;
    }
}
void fi()
{
    switch(y)
    {
        case 1: Ri(); break;
        case 2: Bi(); break;
        case -1: Li(); break;
        case 0: Fi(); break;
    }
}
void b()
{
    switch(y)
    {
        case 1: L(); break;
        case 2: F(); break;
        case -1: R(); break;
        case 0: B(); break;
    }
}
void bi()
{
    switch(y)
    {
        case 1: Li(); break;
        case 2: Fi(); break;
        case -1: Ri(); break;
        case 0: Bi(); break;
    }
}
void l2()
{
    switch(y)
    {
        case 1: F2(); break;
        case 2: R2(); break;
        case -1: B2(); break;
        case 0: L2(); break;
    }
}
void r2()
{
    switch(y)
    {
        case 1: B2(); break;
        case 2: L2(); break;
        case -1: F2(); break;
        case 0: R2(); break;
    }
}
void u2()
{
    switch(y)
    {
        case 1: U2(); break;
        case 2: U2(); break;
        case -1: U2(); break;
        case 0: U2(); break;
    }
}
void d2()
{
    switch(y)
    {
        case 1: D2(); break;
        case 2: D2(); break;
        case -1: D2(); break;
        case 0: D2(); break;
    }
}
void f2()
{
    switch(y)
    {
        case 1: R2(); break;
        case 2: B2(); break;
        case -1: L2(); break;
        case 0: F2(); break;
    }
}
void b2()
{
    switch(y)
    {
        case 1: L2(); break;
        case 2: F2(); break;
        case -1: R2(); break;
        case 0: B2(); break;
    }
}

// converts a given scramble string into an actual scramble simulation in the program
void convertScramble(QString &scram)
{
    trial = false; // trial is true since we don't want the scramble as part of the solution

    QStringList s = scram.split(" ");

    foreach(QString move, s)
    {
        if (move == "L2")
            L2();
        else if (move == "R2")
            R2();
        else if (move == "U2")
            U2();
        else if (move == "D2")
            D2();
        else if (move == "F2")
            F2();
        else if (move == "B2")
            B2();
        else if (move == "L'")
            Li();
        else if (move == "R'")
            Ri();
        else if (move == "U'")
            Uinv();
        else if (move == "D'")
            Di();
        else if (move == "F'")
            Fi();
        else if (move == "B'")
            Bi();
        else if (move == "L")
            L();
        else if (move == "R")
            R();
        else if (move == "U")
            U();
        else if (move == "D")
            D();
        else if (move == "F")
            F();
        else if (move == "B")
            B();
    }
    trial = false; // switch off trial

    /* assign "_scramble" variables the current scrambled state so that it can be viewed
     * using the "View Scramble" button. Actual usage in scrambledialog.cpp
     */
    blueFace_scramble = blueFace;
    whiteFace_scramble = whiteFace;
    greenFace_scramble = greenFace;
    orangeFace_scramble = orangeFace;
    yellowFace_scramble = yellowFace;
    redFace_scramble = redFace;
}

// solves bottom layer cross (yellow face)
void cross()
{
    // checks if all 4 yellow edges are in place. If not, then enters loop
    while(!(yellowFace[1] == 'y' && yellowFace[3] == 'y' && yellowFace[5] == 'y' && yellowFace[7] == 'y'))
    {
        // checks all possible locations for a yellow edge and moves it to an empty spot in the bottom layer

        if (greenFace[3] == 'y')
        {
            if (yellowFace[1] != 'y' && yellowFace[3] == 'y')
            {
                Di();
            }
            else if (yellowFace[5] != 'y' && yellowFace[3] == 'y')
            {
                D2();
            }
            else if(yellowFace[7] != 'y' && yellowFace[3] == 'y')
            {
                D();
            }
            L();
        }

        if (whiteFace[3] == 'y')
        {
            if (yellowFace[1] != 'y' && yellowFace[3] == 'y')
            {
                Di();
            }
            else if (yellowFace[5] != 'y' && yellowFace[3] == 'y')
            {
                D2();
            }
            else if(yellowFace[7] != 'y' && yellowFace[3] == 'y')
            {
                D();
            }
            L2();
        }

        if (blueFace[5] == 'y')
        {
            if (yellowFace[1] != 'y' && yellowFace[3] == 'y')
            {
                Di();
            }
            else if (yellowFace[5] != 'y' && yellowFace[3] == 'y')
            {
                D2();
            }
            else if(yellowFace[7] != 'y' && yellowFace[3] == 'y')
            {
                D();
            }
            Li();
        }
        if (greenFace[5] == 'y')
        {
            if (yellowFace[1] != 'y' && yellowFace[5] == 'y')
            {
                D();
            }
            else if (yellowFace[3] != 'y' && yellowFace[5] == 'y')
            {
                D2();
            }
            else if(yellowFace[7] != 'y' && yellowFace[5] == 'y')
            {
                Di();
            }
            Ri();
        }
        if (whiteFace[5] == 'y')
        {
            if (yellowFace[1] != 'y' && yellowFace[5] == 'y')
            {
                D();
            }
            else if (yellowFace[3] != 'y' && yellowFace[5] == 'y')
            {
                D2();
            }
            else if(yellowFace[7] != 'y' && yellowFace[5] == 'y')
            {
                Di();
            }
            R2();
        }
        if (blueFace[3] == 'y')
        {
            if (yellowFace[1] != 'y' && yellowFace[5] == 'y')
            {
                D();
            }
            else if (yellowFace[3] != 'y' && yellowFace[5] == 'y')
            {
                D2();
            }
            else if(yellowFace[7] != 'y' && yellowFace[5] == 'y')
            {
                Di();
            }
            R();
        }
        if (orangeFace[5] == 'y')
        {
            if (yellowFace[3] != 'y' && yellowFace[1] == 'y')
            {
                D();
            }
            else if (yellowFace[5] != 'y' && yellowFace[1] == 'y')
            {
                Di();
            }
            else if(yellowFace[7] != 'y' && yellowFace[1] == 'y')
            {
                D2();
            }
            Fi();
        }
        if (whiteFace[7] == 'y')
        {
            if (yellowFace[3] != 'y' && yellowFace[1] == 'y')
            {
                D();
            }
            else if (yellowFace[5] != 'y' && yellowFace[1] == 'y')
            {
                Di();
            }
            else if(yellowFace[7] != 'y' && yellowFace[1] == 'y')
            {
                D2();
            }
            F2();
        }
        if (redFace[3] == 'y')
        {
            if (yellowFace[3] != 'y' && yellowFace[1] == 'y')
            {
                D();
            }
            else if (yellowFace[5] != 'y' && yellowFace[1] == 'y')
            {
                Di();
            }
            else if(yellowFace[7] != 'y' && yellowFace[1] == 'y')
            {
                D2();
            }
            F();
        }
        if (orangeFace[3] == 'y')
        {
            if (yellowFace[1] != 'y' && yellowFace[7] == 'y')
            {
                D2();
            }
            else if (yellowFace[3] != 'y' && yellowFace[7] == 'y')
            {
                Di();
            }
            else if(yellowFace[5] != 'y' && yellowFace[7] == 'y')
            {
                D();
            }
            B();
        }
        if (whiteFace[1] == 'y')
        {
            if (yellowFace[1] != 'y' && yellowFace[7] == 'y')
            {
                D2();
            }
            else if (yellowFace[3] != 'y' && yellowFace[7] == 'y')
            {
                Di();
            }
            else if(yellowFace[5] != 'y' && yellowFace[7] == 'y')
            {
                D();
            }
            B2();
        }
        if (redFace[5] == 'y')
        {
            if (yellowFace[1] != 'y' && yellowFace[7] == 'y')
            {
                D2();
            }
            else if (yellowFace[3] != 'y' && yellowFace[7] == 'y')
            {
                Di();
            }
            else if(yellowFace[5] != 'y' && yellowFace[7] == 'y')
            {
                D();
            }
            Bi();
        }

        // if yellow sticker is in U layer
        if (greenFace[1] == 'y')
        {
            if (yellowFace[1] != 'y' && yellowFace[3] != 'y')
            {
                Fi();L();
            }
            else if (yellowFace[1] != 'y' && yellowFace[5] != 'y')
            {
                F();Ri();
            }
            else if(yellowFace[5] != 'y')
            {
                F();Ri();Fi();
            }
            else if(yellowFace[3] != 'y')
            {
                Fi();L();F();
            }
            else if(yellowFace[1] != 'y')
            {
                Uinv();Ri();F();R();
            }
            else if(yellowFace[7] != 'y')
            {
                Uinv();R();Bi();Ri();
            }
        }
        if (redFace[1] == 'y')
        {
            if (yellowFace[5] != 'y' && yellowFace[1] != 'y')
            {
                Ri();F();
            }
            else if (yellowFace[5] != 'y' && yellowFace[7] != 'y')
            {
                R();Bi();
            }
            else if(yellowFace[7] != 'y')
            {
                R();Bi();Ri();
            }
            else if(yellowFace[1] != 'y')
            {
                Ri();F();R();
            }
            else if(yellowFace[5] != 'y')
            {
                Uinv();Bi();R();B();
            }
            else if(yellowFace[3] != 'y')
            {
                U();Fi();L();F();
            }
        }
        if (blueFace[1] == 'y')
        {
            if (yellowFace[7] != 'y' && yellowFace[5] != 'y')
            {
                Bi();R();
            }
            else if (yellowFace[7] != 'y' && yellowFace[3] != 'y')
            {
                B();Li();
            }
            else if(yellowFace[3] != 'y')
            {
                B();Li();Bi();
            }
            else if(yellowFace[5] != 'y')
            {
                Bi();R();B();
            }
            else if(yellowFace[7] != 'y')
            {
                U();R();Bi();Ri();
            }
            else if(yellowFace[1] != 'y')
            {
                U();Ri();F();R();
            }
        }
        if (orangeFace[1] == 'y')
        {
            if (yellowFace[3] != 'y' && yellowFace[7] != 'y')
            {
                Li();B();
            }
            else if (yellowFace[3] != 'y' && yellowFace[1] != 'y')
            {
                L();Fi();
            }
            else if(yellowFace[1] != 'y')
            {
                L();Fi();Li();
            }
            else if(yellowFace[7] != 'y')
            {
                Li();B();L();
            }
            else if(yellowFace[3] != 'y')
            {
                Uinv();Fi();L();F();
            }
            else if(yellowFace[5] != 'y')
            {
                Uinv();F();Ri();Fi();
            }
        }

        // if yellow sticker is on D layer
        if (greenFace[7] == 'y')
        {
            if (yellowFace[5] != 'y')
            {
                Fi();Ri();
            }
            else if (yellowFace[3] != 'y')
            {
                F();L();
            }
            else
            {
                Fi();D();Ri();
            }
        }
        if (redFace[7] == 'y')
        {
            if (yellowFace[7] != 'y')
            {
                Ri();Bi();
            }
            else if (yellowFace[1] != 'y')
            {
                R();F();
            }
            else
            {
                R();Di();F();
            }
        }
        if (blueFace[7] == 'y')
        {
            if (yellowFace[3] != 'y')
            {
                Bi();Li();
            }
            else if (yellowFace[5] != 'y')
            {
                B();R();
            }
            else
            {
                Bi();Di();R();
            }
        }
        if (orangeFace[7] == 'y')
        {
            if (yellowFace[1] != 'y')
            {
                Li();Fi();
            }
            else if (yellowFace[7] != 'y')
            {
                L();B();
            }
            else
            {
                Li();D();Fi();
            }
        }
    }

    // checks if all the cross pieces are aligned properly with corresponding center
    if (!(greenFace[7] == 'g' && redFace[7] == 'r' && blueFace[7] == 'b' && orangeFace[7] == 'o'))
    {
        // checks all possible combinations of cross pieces and permutes them correctly

        //if greenFace[7] is green and permutations for other 3 cross pieces
        if (greenFace[7] == 'g' && redFace[7] == 'r' && blueFace[7] == 'o' && orangeFace[7] == 'b')
        {
            Li();D();L();Di();Li();
        }
        else if (greenFace[7] == 'g' && redFace[7] == 'b' && blueFace[7] == 'r' && orangeFace[7] == 'o')
        {
            R();Di();Ri();D();R();
        }
        else if (greenFace[7] == 'g' && redFace[7] == 'b' && blueFace[7] == 'o' && orangeFace[7] == 'r')
        {
            F();D();Fi();Di();F();D();
        }
        else if (greenFace[7] == 'g' && redFace[7] == 'o' && blueFace[7] == 'r' && orangeFace[7] == 'b')
        {
            R();D();Ri();Di();R();Di();
        }
        else if (greenFace[7] == 'g' && redFace[7] == 'o' && blueFace[7] == 'b' && orangeFace[7] == 'r')
        {
            R2();D2();R2();D2();R2();
        }

        //if greenFace[7] is red and permutations for other 3 cross pieces
        if (greenFace[7] == 'r' && redFace[7] == 'g' && blueFace[7] == 'b' && orangeFace[7] == 'o')
        {
            R();D();Ri();Di();R();
        }
        else if (greenFace[7] == 'r' && redFace[7] == 'g' && blueFace[7] == 'o' && orangeFace[7] == 'b')
        {
            B2();D2();B2();D2();B2();Di();
        }
        else if (greenFace[7] == 'r' && redFace[7] == 'b' && blueFace[7] == 'g' && orangeFace[7] == 'o')
        {
            Li();D();L();Di();Li();D();
        }
        else if (greenFace[7] == 'r' && redFace[7] == 'b' && blueFace[7] == 'o' && orangeFace[7] == 'g')
        {
            D();
        }
        else if (greenFace[7] == 'r' && redFace[7] == 'o' && blueFace[7] == 'g' && orangeFace[7] == 'b')
        {
            F();D();Fi();Di();F();D2();
        }
        else if (greenFace[7] == 'r' && redFace[7] == 'o' && blueFace[7] == 'b' && orangeFace[7] == 'g')
        {
            R();Di();Ri();D();R();D();
        }
        //if greenFace[7] is blue and permutations for other 3 cross pieces
        if (greenFace[7] == 'b' && redFace[7] == 'g' && blueFace[7] == 'r' && orangeFace[7] == 'o')
        {
            F();D();Fi();Di();F();Di();
        }
        else if (greenFace[7] == 'b' && redFace[7] == 'g' && blueFace[7] == 'o' && orangeFace[7] == 'r')
        {
            R();Di();Ri();D();R();D2();
        }
        else if (greenFace[7] == 'b' && redFace[7] == 'r' && blueFace[7] == 'g' && orangeFace[7] == 'o')
        {
            B2();D2();B2();D2();B2();
        }
        else if (greenFace[7] == 'b' && redFace[7] == 'r' && blueFace[7] == 'o' && orangeFace[7] == 'g')
        {
            R();D();Ri();Di();R();D();
        }
        else if (greenFace[7] == 'b' && redFace[7] == 'o' && blueFace[7] == 'g' && orangeFace[7] == 'r')
        {
            D2();
        }
        else if(greenFace[7] == 'b' && redFace[7] == 'o' && blueFace[7] == 'r' && orangeFace[7] == 'g')
        {
            Li();D();L();Di();Li();D2();
        }

        //if greenFace[7] is orange and permutations for other 3 cross pieces
        if (greenFace[7] == 'o' && redFace[7] == 'g' && blueFace[7] == 'r' && orangeFace[7] == 'b')
        {
            Di();
        }
        else if (greenFace[7] == 'o' && redFace[7] == 'g' && blueFace[7] == 'b' && orangeFace[7] == 'r')
        {
            Li();D();L();Di();Li();Di();
        }
        else if (greenFace[7] == 'o' && redFace[7] == 'r' && blueFace[7] == 'g' && orangeFace[7] == 'b')
        {
            R();Di();Ri();D();R();Di();
        }
        else if (greenFace[7] == 'o' && redFace[7] == 'r' && blueFace[7] == 'b' && orangeFace[7] == 'g')
        {
            F();D();Fi();Di();F();
        }
        else if (greenFace[7] == 'o' && redFace[7] == 'b' && blueFace[7] == 'g' && orangeFace[7] == 'r')
        {
            R();D();Ri();Di();R();D2();
        }
        else if (greenFace[7] == 'o' && redFace[7] == 'b' && blueFace[7] == 'r' && orangeFace[7] == 'g')
        {
            B2();D2();B2();D2();B2();D();
        }
    }
}

/* brings any yellow corner to the UFR location and returns its original location
 * UFL is 1, UBL is 2, UBR is 3, UFR is 4, DFL is 5, DBL is 6, DBR is 7, DFR is 8.
 * If all F2L pairs are already in place, it returns 0.
 */
int bringToTop_trial()
{

    if (greenFace[0] == 'y' || whiteFace[6] == 'y' || orangeFace[2] == 'y')
    {
        Uinv();
        return 1;
    }
    if (orangeFace[0] == 'y' || whiteFace[0] == 'y' || blueFace[2] == 'y')
    {
        U2();
        return 2;
    }
    if (blueFace[0] == 'y' || whiteFace[2] == 'y' || redFace[2] == 'y')
    {
        U();
        return 3;
    }
    if(greenFace[2] == 'y' || whiteFace[8] == 'y' || redFace[0] == 'y')
    {
        return 4;
    }
    if (orangeFace[8] == 'y' || yellowFace[0] == 'y' || greenFace[6] == 'y')
    {
        if (!(yellowFace[0] == 'y' && greenFace[3] == 'g' && greenFace[6] == 'g'
              && orangeFace[5] == 'o' && orangeFace[8] == 'o'))
        {
            Li();Uinv();L();
            return 5;
        }

    }
    if (orangeFace[6] == 'y' || yellowFace[6] == 'y' || blueFace[8] == 'y')
    {
        if (!(yellowFace[6] == 'y' && blueFace[5] == 'b' && blueFace[8] == 'b'
              && orangeFace[3] == 'o' && orangeFace[6] == 'o'))
        {
            L();U2();Li();
            return 6;
        }
    }
    if (redFace[8] == 'y' || yellowFace[8] == 'y' || blueFace[6] == 'y')
    {
        if (!(yellowFace[8] == 'y' && blueFace[3] == 'b' && blueFace[6] == 'b'
              && redFace[5] == 'r' && redFace[8] == 'r'))
        {
            B();U();Bi();
            return 7;
        }
    }
    if (redFace[6] == 'y' || yellowFace[2] == 'y' || greenFace[8] == 'y')
    {
         if (!(yellowFace[2] == 'y' && greenFace[5] == 'g' && greenFace[8] == 'g'
              && redFace[3] == 'r' && redFace[6] == 'r'))
        {
            R();Uinv();Ri();
            return 8;
        }
    }
    return 0;
}
/* the yellow corner brought to UFR location previously has it's other 2 colours identified
 * and stored in c[]
 */
void identifyCornerColours()
{
    if (greenFace[2] == 'y')
    {
        c[0] = redFace[0];
        c[1] = whiteFace[8];
    }
    else if (redFace[0] == 'y')
    {
        c[0] = whiteFace[8];
        c[1] = greenFace[2];
    }
    else if (whiteFace[8] == 'y')
    {
        c[0] = greenFace[2];
        c[1] = redFace[0];
    }
}
/* According to the appropriate cornerCode and c[], the corner is brought to the appropriate location
 * between the 3 centres having the same colours as the corner piece
 */
void bringToTop(int n)
{
    if (n == 1)
    {
        if ((c[0] == 'o' && c[1] == 'g') || (c[1] == 'o' && c[0] == 'g'))
        {

        }
        else if ((c[0] == 'o' && c[1] == 'b') || (c[1] == 'o' && c[0] == 'b'))
        {
            U();
        }
        else if ((c[0] == 'b' && c[1] == 'r') || (c[1] == 'b' && c[0] == 'r'))
        {
           U2();
        }
        else if ((c[0] == 'r' && c[1] == 'g') || (c[1] == 'r' && c[0] == 'g'))
        {
            Uinv();
        }
    }
    else if (n == 2)
    {
        if ((c[0] == 'o' && c[1] == 'g') || (c[1] == 'o' && c[0] == 'g'))
        {
            Uinv();
        }
        else if ((c[0] == 'o' && c[1] == 'b') || (c[1] == 'o' && c[0] == 'b'))
        {

        }
        else if ((c[0] == 'b' && c[1] == 'r') || (c[1] == 'b' && c[0] == 'r'))
        {
            U();
        }
        else if ((c[0] == 'r' && c[1] == 'g') || (c[1] == 'r' && c[0] == 'g'))
        {
            U2();
        }
    }
    else if (n == 3)
    {
        if ((c[0] == 'o' && c[1] == 'g') || (c[1] == 'o' && c[0] == 'g'))
        {
            U2();
        }
        else if ((c[0] == 'o' && c[1] == 'b') || (c[1] == 'o' && c[0] == 'b'))
        {
            Uinv();
        }
        else if ((c[0] == 'b' && c[1] == 'r') || (c[1] == 'b' && c[0] == 'r'))
        {

        }
        else if ((c[0] == 'r' && c[1] == 'g') || (c[1] == 'r' && c[0] == 'g'))
        {
            U();
        }
    }
    else if (n == 4)
    {
        if ((c[0] == 'o' && c[1] == 'g') || (c[1] == 'o' && c[0] == 'g'))
        {
            U();
        }
        else if ((c[0] == 'o' && c[1] == 'b') || (c[1] == 'o' && c[0] == 'b'))
        {
            U2();
        }
        else if ((c[0] == 'b' && c[1] == 'r') || (c[1] == 'b' && c[0] == 'r'))
        {
            Uinv();
        }
        else if ((c[0] == 'r' && c[1] == 'g') || (c[1] == 'r' && c[0] == 'g'))
        {

        }
    }
    else if (n == 5)
    {
        if ((c[0] == 'o' && c[1] == 'g') || (c[1] == 'o' && c[0] == 'g'))
        {
            Li();U();L();
        }
        else if ((c[0] == 'o' && c[1] == 'b') || (c[1] == 'o' && c[0] == 'b'))
        {
            F();U();Fi();
        }
        else if ((c[0] == 'b' && c[1] == 'r') || (c[1] == 'b' && c[0] == 'r'))
        {
            Li();U2();L();
        }
        else if ((c[0] == 'r' && c[1] == 'g') || (c[1] == 'r' && c[0] == 'g'))
        {
            Li();Uinv();L();
        }
    }
    else if (n == 6)
    {
        if ((c[0] == 'o' && c[1] == 'g') || (c[1] == 'o' && c[0] == 'g'))
        {
            Bi();Uinv();B();
        }
        else if ((c[0] == 'o' && c[1] == 'b') || (c[1] == 'o' && c[0] == 'b'))
        {
            Bi();U();B();
        }
        else if ((c[0] == 'b' && c[1] == 'r') || (c[1] == 'b' && c[0] == 'r'))
        {
            L();U();Li();
        }
        else if ((c[0] == 'r' && c[1] == 'g') || (c[1] == 'r' && c[0] == 'g'))
        {
            Bi();U2();B();
        }
    }
    else if (n == 7)
    {
        if ((c[0] == 'o' && c[1] == 'g') || (c[1] == 'o' && c[0] == 'g'))
        {
            B();U2();Bi();
        }
        else if ((c[0] == 'o' && c[1] == 'b') || (c[1] == 'o' && c[0] == 'b'))
        {
            Ri();Uinv();R();
        }
        else if ((c[0] == 'b' && c[1] == 'r') || (c[1] == 'b' && c[0] == 'r'))
        {
            B();Uinv();Bi();
        }
        else if ((c[0] == 'r' && c[1] == 'g') || (c[1] == 'r' && c[0] == 'g'))
        {
            B();U();Bi();
        }
    }
    else if (n == 8)
    {
        if ((c[0] == 'o' && c[1] == 'g') || (c[1] == 'o' && c[0] == 'g'))
        {
            R();U();Ri();
        }
        else if ((c[0] == 'o' && c[1] == 'b') || (c[1] == 'o' && c[0] == 'b'))
        {
            R();U2();Ri();
        }
        else if ((c[0] == 'b' && c[1] == 'r') || (c[1] == 'b' && c[0] == 'r'))
        {
            Fi();Uinv();F();
        }
        else if ((c[0] == 'r' && c[1] == 'g') || (c[1] == 'r' && c[0] == 'g'))
        {
            R();Uinv();Ri();
        }
    }
}
/* Brings the corner to UFR position (trial) and checks whether the yellow sticker on the yellow corner
 * is facing up(u), right(r) or front(f). This character value is assigned to "orient" variable.
 */
void identifyCornerOrientation()
{
    if ((c[0] == 'o' && c[1] == 'g') || (c[1] == 'o' && c[0] == 'g'))
    {
        Uinv();
    }
    else if ((c[0] == 'o' && c[1] == 'b') || (c[1] == 'o' && c[0] == 'b'))
    {
        U2();
    }
    else if ((c[0] == 'b' && c[1] == 'r') || (c[1] == 'b' && c[0] == 'r'))
    {
        U();
    }
    else if ((c[0] == 'r' && c[1] == 'g') || (c[1] == 'r' && c[0] == 'g'))
    {

    }

    if(greenFace[2] == 'y')
    {
        orient = 'f';
    }
    else if (redFace[0] == 'y')
    {
        orient = 'r';
    }
    else if (whiteFace[8] == 'y')
    {
        orient = 'u';
    }
}
/* determines no. of clockwise turns of cube required to bring the corner to UFR location (no trial)
 * 1 = clockwise turn 90 deg
 * 2 = 180 deg turn
 * -1 = counter clockwise turn 90 deg
 */
void determineY()
{
    if ((c[0] == 'o' && c[1] == 'g') || (c[1] == 'o' && c[0] == 'g'))
    {
        y = -1;
    }
    else if ((c[0] == 'o' && c[1] == 'b') || (c[1] == 'o' && c[0] == 'b'))
    {
        y = 2;
    }
    else if ((c[0] == 'b' && c[1] == 'r') || (c[1] == 'b' && c[0] == 'r'))
    {
        y = 1;
    }
    else if ((c[0] == 'r' && c[1] == 'g') || (c[1] == 'r' && c[0] == 'g'))
    {
        y = 0;
    }
}
/* For the corner currently being tracked, the corresponding edge is located in the cube out of the
 * possible 16 locations (4 on top layer, 4 in middle layer and 2 possible orientations/flipped edges)
 * (4 + 4) * 2 = 16 possible return values. Also, based on the y value, the edgeCode is subject to change.
 * Since a clockwise rotation changes the location of the edge, y value determines the edgeCode.
 * 1 UF, 2 UL, 3 UB, 4 UR, 5 FU, 6 LU, 7 BU, 8 RU, 9 FL, 10 FR, 11 BL, 12 BR, 13 LF, 14 RF, 15 LB, 16, RB.
 */
int identifyEdge()
{
    if (whiteFace[7] == c[0] && greenFace[1] == c[1])
    {
        switch(y)
        {
            case 1: return 2;
            case 2: return 3;
            case -1: return 4;
            default: return 1;
        }
    }
    else if (whiteFace[3] == c[0] && orangeFace[1] == c[1])
    {
        switch(y)
        {
            case 1: return 3;
            case 2: return 4;
            case -1: return 1;
            default: return 2;
        }
    }
    else if (whiteFace[1] == c[0] && blueFace[1] == c[1])
    {
        switch(y)
        {
            case 1: return 4;
            case 2: return 1;
            case -1: return 2;
            default: return 3;
        }
    }
    else if (whiteFace[5] == c[0] && redFace[1] == c[1])
    {
        switch(y)
        {
            case 1: return 1;
            case 2: return 2;
            case -1: return 3;
            case 0: return 4;
        }
    }

    else if (whiteFace[7] == c[1] && greenFace[1] == c[0])
    {
        switch(y)
        {
            case 1: return 6;
            case 2: return 7;
            case -1: return 8;
            case 0: return 5;
        }
    }
    else if (whiteFace[3] == c[1] && orangeFace[1] == c[0])
    {
        switch(y)
        {
            case 1: return 7;
            case 2: return 8;
            case -1: return 5;
            case 0: return 6;
        }
    }
    else if (whiteFace[1] == c[1] && blueFace[1] == c[0])
    {
        switch(y)
        {
            case 1: return 8;
            case 2: return 5;
            case -1: return 6;
            case 0: return 7;
        }
    }
    else if (whiteFace[5] == c[1] && redFace[1] == c[0])
    {
        switch(y)
        {
            case 1: return 5;
            case 2: return 6;
            case -1: return 7;
            case 0: return 8;
        }
    }

    else if (greenFace[3] == c[0] && orangeFace[5] == c[1])
    {
        switch(y)
        {
            case 1: return 15;
            case 2: return 12;
            case -1: return 14;
            case 0: return 9;
        }
    }
    else if (greenFace[5] == c[0] && redFace[3] == c[1])
    {
        switch(y)
        {
            case 1: return 13;
            case 2: return 11;
            case -1: return 16;
            case 0: return 10;
        }
    }
    else if (blueFace[5] == c[0] && orangeFace[3] == c[1])
    {
        switch(y)
        {
            case 1: return 16;
            case 2: return 10;
            case -1: return 13;
            case 0: return 11;
        }
    }
    else if (blueFace[3] == c[0] && redFace[5] == c[1])
    {
        switch(y)
        {
            case 1: return 14;
            case 2: return 9;
            case -1: return 15;
            case 0: return 12;
        }
    }

    else if (greenFace[3] == c[1] && orangeFace[5] == c[0])
    {
        switch(y)
        {
            case 1: return 11;
            case 2: return 16;
            case -1: return 10;
            case 0: return 13;
        }
    }
    else if (greenFace[5] == c[1] && redFace[3] == c[0])
    {
        switch(y)
        {
            case 1: return 9;
            case 2: return 15;
            case -1: return 12;
            case 0: return 14;
        }
    }
    else if (blueFace[5] == c[1] && orangeFace[3] == c[0])
    {
        switch(y)
        {
            case 1: return 12;
            case 2: return 14;
            case -1: return 9;
            case 0: return 15;
        }
    }
    else if (blueFace[3] == c[1] && redFace[5] == c[0])
    {
        switch(y)
        {
            case 1: return 10;
            case 2: return 13;
            case -1: return 11;
            case 0: return 16;
        }
    }
    return 0;
}
/* The following 3 functions solves the F2L pair based on "y" value and location of edge (edgeCode).
 * The difference between the 3 functions are the orientation of the corner piece using "orient" variable
 * Note: Small letters are used because of rotation modifier functions which change the rotation based on
 * 'y' value. 16 possible cases (edgeCode ranges from 1 to 16) for each function.
 */
void cornerFacingF(int n)
{
    if (n == 1)
    {
        u();fi();u();f();uinv();fi();uinv();f();
    }
    else if (n == 2)
    {
        fi();uinv();f();
    }
    else if (n == 3)
    {
        r2();u();b();uinv();bi();r2();
    }
    else if (n == 4)
    {
        f();u2();f2();uinv();f2();uinv();fi();
    }
    else if (n == 5)
    {
        fi();u();f();u2();r();u();ri();
    }
    else if (n == 6)
    {
        r();u();b();u2();bi();u();ri();
    }
    else if (n == 7)
    {
        f2();li();uinv();l();u();f2();
    }
    else if (n == 8)
    {
        u();r();uinv();ri();
    }

    else if (n == 9)
    {
        f();uinv();fi();u();r();uinv();ri();
    }
    else if (n == 10)
    {
        u2();r();uinv();ri();uinv();fi();uinv();f();
    }
    else if (n == 11)
    {
        l();uinv();li();u();fi();uinv();f();
    }
    else if (n == 12)
    {
        u2();b();uinv();bi();r();u2();ri();
    }

    else if (n == 13)
    {
        uinv();f();uinv();fi();u2();fi();uinv();f();
    }
    else if (n == 14)
    {
        uinv();r();uinv();ri();u2();r();uinv();ri();
    }
    else if (n == 15)
    {
        u();l();uinv();li();r();uinv();ri();
    }
    else if (n == 16)
    {
        u();b();uinv();bi();fi();uinv();f();
    }
}
void cornerFacingR(int n)
{
    if (n == 1)
    {
        uinv();fi();u();f();
    }
    else if (n == 2)
    {
        r2();b();u();bi();uinv();r2();
    }
    else if (n == 3)
    {
        fi();uinv();li();u2();l();uinv();f();
    }
    else if (n == 4)
    {
        r();uinv();ri();u2();fi();uinv();f();
    }
    else if (n == 5)
    {
        r();uinv();b();u2();bi();u2();ri();
    }
    else if (n == 6)
    {
        f2();uinv();li();u();l();f2();
    }
    else if (n == 7)
    {
        r();u();ri();
    }
    else if (n == 8)
    {
        uinv();r();uinv();ri();u();r();u();ri();
    }

    else if (n == 9)
    {
        u2();li();u();l();fi();u2();f();
    }
    else if (n == 10)
    {
        u();fi();uinv();f();uinv();r();u();ri();
    }
    else if (n == 11)
    {
        bi();u();b();uinv();r();u();ri();
    }
    else if (n == 12)
    {
        ri();u();r();uinv();fi();u();f();
    }

    else if (n == 13)
    {
        uinv();li();u();l();r();u();ri();
    }
    else if (n == 14)
    {
        u();r();u();ri();u2();r();u();ri();
    }
    else if (n == 15)
    {
        uinv();l();u();li();r();u();ri();
    }
    else if (n == 16)
    {
        ri();uinv();r2();u();ri();
    }
}
void cornerFacingU(int n)
{
    if (n == 1)
    {
        fi();u2();f();u();fi();uinv();f();
    }
    else if (n == 2)
    {
        uinv();fi();u2();f2();ri();fi();r();
    }
    else if (n == 3)
    {
        fi();li();u2();l();f();
    }
    else if (n == 4)
    {
        u2();f2();u2();f();u();fi();u();f2();
    }
    else if (n == 5)
    {
        u2();r2();u2();ri();uinv();r();uinv();r2();
    }
    else if (n == 6)
    {
        r();b();u2();bi();ri();
    }
    else if (n == 7)
    {
        u();r();u2();r2();f();r();fi();
    }
    else if (n == 8)
    {
        r();u2();ri();uinv();r();u();ri();
    }

    else if (n == 9)
    {
        li();uinv();l();fi();u2();f2();ri();fi();r();
    }
    else if (n == 10)
    {
        r();uinv();r();bi();ri();b();ri();
    }
    else if (n == 11)
    {
        u2();l();uinv();li();uinv();fi();u();f();
    }
    else if (n == 12)
    {
        b();u();bi();r();u2();r2();f();r();fi();
    }
    else if (n == 13)
    {
        u();f();uinv();f2();u();f();
    }
    else if (n == 14)
    {
        r2();u();r2();u();r2();u2();r2();
    }
    else if (n == 15)
    {
        r2();d();b2();di();r2();
    }
    else if (n == 16)
    {
        uinv();ri();u();r2();uinv();ri();
    }
}
// Executes the order of functions, keeps track of a corner and edge pair and solves them in place
void f2l()
{
    // brings a corner to UFR (trial) and checks for other colours. If all pairs are in place, control returned to main
    trial = true;
    createCheckpoint();
    int cornerCode = bringToTop_trial();
    if (cornerCode == 0)
    {
        trial = false;
        return;
    }
    identifyCornerColours();
    resetLocation();

    // brings the appropriate corner to it's location between it's centres
    trial = false;
    bringToTop(cornerCode);

    // brings newly brought out corner piece to UFR location and checks orientation (u, f or r)
    trial = true;
    createCheckpoint();
    identifyCornerOrientation();
    resetLocation();

    // determines y value(clockwise rotation) required to bring the corner to UFR location
    trial = false;
    determineY();

    // determines location and orientation of edge corresponding to the corner (F2L pair)
    int edgeCode = identifyEdge();


    // solves the F2L pair based on the orientation of the corner piece (u, f or r)
    if (orient == "f")
    {
        cornerFacingF(edgeCode);
    }
    else if (orient == "r")
    {
        cornerFacingR(edgeCode);
    }
    else if (orient == "u")
    {
        cornerFacingU(edgeCode);
    }
}
// Solves the OLL (Orientation of Last Layer) case (57 algs)
void oll()
{
    y = 0;
    int x = 0; // keeps track of no. of U moves
    createCheckpoint();

    // if any of the top layer is not oriented correctly, control enters loop
    while (whiteFace[0] != 'w' || whiteFace[1] != 'w' || whiteFace[2] != 'w'
           || whiteFace[3] != 'w' || whiteFace[5] != 'w' || whiteFace[6] != 'w'
           || whiteFace[7] != 'w' || whiteFace[8] != 'w')
    {
        // trial is OFF
        trial = false;

        /* 57 different OLL cases are checked below. OLL number is used for checking bugs
         * Section can be overlooked unless there are some bugs and more optimal algs
         * Again, small letters functions are used to change algs according to y value and
         * reduce moveCount.
         */

        // all edges flipped correctly
        if (whiteFace[1] == 'w' && whiteFace[3] == 'w' && whiteFace[5] == 'w' && whiteFace[7] == 'w')
        {
            // OLL 27 Sune
            if (blueFace[2] == 'w' && redFace[2] == 'w' && whiteFace[6] == 'w' && greenFace[2] == 'w')
            {
                resetLocation();
                r();u();ri();u();r();u2();ri();
            }
            //OLL 26 Antisune
            else if (orangeFace[0] == 'w' && blueFace[0] == 'w' && whiteFace[8] == 'w' && greenFace[0] == 'w')
            {
                resetLocation();
                li();u();r();uinv();l();u();ri();
            }
            // OLL 21 Double Sune
            else if (orangeFace[0] == 'w' && orangeFace[2] == 'w' && redFace[0] == 'w' && redFace[2] == 'w')
            {
                resetLocation();
                r();u();ri();u();r();uinv();ri();u();r();u2();ri();
            }
            // OLL 22 Pi
            else if (orangeFace[0] == 'w' && orangeFace[2] == 'w' && blueFace[0] == 'w' && greenFace[2] == 'w')
            {
                resetLocation();
                r();u2();r2();uinv();r2();uinv();r2();u2();r();
            }
            // OLL 23 Headlights
            else if (whiteFace[6] == 'w' && whiteFace[8] == 'w' && blueFace[0] == 'w' && blueFace[2] == 'w')
            {
                resetLocation();
                ri();u2();r();f();uinv();ri();uinv();r();u();fi();
            }
            // OLL 24 Chameleon
            else if (greenFace[0] == 'w' && whiteFace[2] == 'w' && whiteFace[8] == 'w' && blueFace[2] == 'w')
            {
                resetLocation();
                f();r();fi();l();f();ri();fi();li();
            }
            // OLL 25 Triple-Sune
            else if (blueFace[0] == 'w' && whiteFace[0] == 'w' && whiteFace[8] == 'w' && orangeFace[2] == 'w')
            {
                resetLocation();
                b();li();bi();r();b();l();bi();ri();
            }
        }

        // no edges flipped

        else if (whiteFace[1] != 'w' && whiteFace[3] != 'w' && whiteFace[5] != 'w' && whiteFace[7] != 'w')
        {
            // OLL 1
            if (orangeFace[0] == 'w' && orangeFace[2] == 'w' && redFace[0] == 'w' && redFace[2] == 'w')
            {
                resetLocation();
                r();u();bi();r();b();r2();uinv();ri();f();r();fi();
            }
            // OLL 2
            else if (greenFace[0] == 'w' && blueFace[2] == 'w' && redFace[0] == 'w' && redFace[2] == 'w')
            {
                resetLocation();
                f();ri();fi();r();u();r2();bi();ri();b();uinv();ri();
            }
            // OLL 3
            else if (whiteFace[6] == 'w' && blueFace[2] == 'w' && redFace[2] == 'w' && greenFace[2] == 'w')
            {
                resetLocation();
                li();r2();b();ri();b();l();u2();li();b();l();ri();
            }
            // OLL 4
            else if (whiteFace[2] == 'w' && greenFace[0] == 'w' && redFace[0] == 'w' && orangeFace[0] == 'w')
            {
                resetLocation();
                ri();u2();ri();f();r();fi();uinv();fi();uinv();f();uinv();r();
            }
            // OLL 17
            else if (whiteFace[0] == 'w' && whiteFace[8] == 'w' && blueFace[0] == 'w' && orangeFace[2] == 'w')
            {
                resetLocation();
                fi();r();u2();li();b();u2();bi();l();u2();ri();f();
            }
            // OLL 18
            else if (whiteFace[6] == 'w' && whiteFace[8] == 'w' && blueFace[0] == 'w' && blueFace[2] == 'w')
            {
                resetLocation();
                f();r();u();ri();u();fi();u2();fi();l();f();li();
            }
            // OLL 19
            else if (whiteFace[0] == 'w' && whiteFace[2] == 'w' && redFace[0] == 'w' && orangeFace[2] == 'w')
            {
                resetLocation();
                ri();u2();f();r();u();ri();uinv();f2();u2();f();r();
            }
            // OLL 20
            else if (whiteFace[0] == 'w' && whiteFace[2] == 'w' && whiteFace[6] == 'w' && whiteFace[8] == 'w')
            {
                resetLocation();
                li();ri();fi();u2();l2();u2();l2();u2();l2();f();l();r();
            }
        }

        // two edges flipped in L shape

        else if ((whiteFace[1] == 'w' && whiteFace[3] == 'w') || (whiteFace[5] == 'w' && whiteFace[7] == 'w')
                 || (whiteFace[3] == 'w' && whiteFace[7] == 'w') || (whiteFace[1] == 'w' && whiteFace[5] == 'w'))
        {
            // P Shapes

            // OLL 31 Left Bad P
            if (blueFace[2] == 'w' && whiteFace[2] == 'w' && orangeFace[1] == 'w' && greenFace[0] == 'w'
                && greenFace[1] == 'w' && whiteFace[8] == 'w')
            {
                resetLocation();
                ri();uinv();f();u();r();uinv();ri();fi();r();
            }
            // OLL 32 Right Bad P
            else if (blueFace[2] == 'w' && whiteFace[2] == 'w' && orangeFace[1] == 'w' && greenFace[0] == 'w'
                && blueFace[1] == 'w' && whiteFace[8] == 'w')
            {
                resetLocation();
                r();u();bi();uinv();ri();u();r();b();ri();
            }
            // OLL 43 Left Good P
            else if (redFace[2] == 'w' && whiteFace[0] == 'w' && redFace[1] == 'w' && redFace[0] == 'w'
                && blueFace[1] == 'w' && whiteFace[6] == 'w')
            {
                resetLocation();
                bi();uinv();ri();u();r();b();
            }
            // OLL 44 Right Good P
            else if (redFace[2] == 'w' && whiteFace[0] == 'w' && redFace[1] == 'w' && redFace[0] == 'w'
                && greenFace[1] == 'w' && whiteFace[6] == 'w')
            {
                resetLocation();
                f();u();r();uinv();ri();fi();
            }

            // W Shapes

            // OLL 36 Wario
            else if (blueFace[1] == 'w' && whiteFace[0] == 'w' && redFace[1] == 'w' && redFace[2] == 'w'
                && greenFace[0] == 'w' && whiteFace[8] == 'w')
            {
                resetLocation();
                r();u();ri();uinv();fi();u2();f();u();r();u();ri();
            }
            // OLL 38 Mario
            else if (blueFace[1] == 'w' && whiteFace[2] == 'w' && orangeFace[1] == 'w' && orangeFace[0] == 'w'
                && greenFace[2] == 'w' && whiteFace[6] == 'w')
            {
                resetLocation();
                li();uinv();l();u();f();u2();fi();uinv();li();uinv();l();
            }

            // L Shapes

            // OLL 48 L
            else if (blueFace[0] == 'w' && redFace[1] == 'w' && orangeFace[2] == 'w' && orangeFace[0] == 'w'
                && greenFace[1] == 'w' && greenFace[2] == 'w')
            {
                resetLocation();
                f();r();u();ri();uinv();r();u();ri();uinv();fi();
            }
            // OLL 47 L
            else if (blueFace[2] == 'w' && redFace[0] == 'w' && redFace[2] == 'w' && orangeFace[1] == 'w'
                && greenFace[1] == 'w' && greenFace[0] == 'w')
            {
                resetLocation();
                fi();li();uinv();l();u();li();uinv();l();u();f();
            }
            // OLL 53 L
            else if (redFace[0] == 'w' && redFace[1] == 'w' && orangeFace[2] == 'w' && orangeFace[0] == 'w'
                && greenFace[1] == 'w' && redFace[2] == 'w')
            {
                resetLocation();
                ri();fi();l();fi();li();f();l();fi();li();f2();r();
            }
            // OLL 54 L
            else if (orangeFace[1] == 'w' && redFace[0] == 'w' && orangeFace[2] == 'w' && orangeFace[0] == 'w'
                && redFace[2] == 'w' && greenFace[1] == 'w')
            {
                resetLocation();
                l();f();ri();f();r();fi();ri();f();r();f2();li();
            }
            // OLL 49 L
            else if (redFace[0] == 'w' && redFace[1] == 'w' && blueFace[2] == 'w' && blueFace[1] == 'w'
                && greenFace[0] == 'w' && redFace[2] == 'w')
            {
                resetLocation();
                r();bi();r2();f();r2();b();r2();fi();r();
            }
            // OLL 50 L
            else if (redFace[0] == 'w' && redFace[1] == 'w' && blueFace[2] == 'w' && greenFace[1] == 'w'
                && greenFace[0] == 'w' && redFace[2] == 'w')
            {
                resetLocation();
                ri();f();r2();bi();r2();fi();r2();b();ri();
            }

            // Square Shapes

            // OLL 5 Right bottom square
            else if (redFace[2] == 'w' && orangeFace[1] == 'w' && blueFace[2] == 'w' && blueFace[1] == 'w'
                && whiteFace[8] == 'w' && orangeFace[2] == 'w')
            {
                resetLocation();
                li();b2();r();b();ri();b();l();
            }
            // OLL 6 Right top square
            else if (redFace[0] == 'w' && orangeFace[1] == 'w' && greenFace[0] == 'w' && greenFace[1] == 'w'
                && whiteFace[2] == 'w' && orangeFace[0] == 'w')
            {
                resetLocation();
                l();f2();ri();fi();r();fi();li();
            }

            // Small lightning bolt shapes

            // OLL 7
            else if (redFace[2] == 'w' && redFace[1] == 'w' && greenFace[2] == 'w' && greenFace[1] == 'w'
                && whiteFace[6] == 'w' && blueFace[2] == 'w')
            {
                resetLocation();
                l();f();ri();f();r();f2();li();
            }
            // OLL 8
            else if (redFace[0] == 'w' && redFace[1] == 'w' && greenFace[0] == 'w' && blueFace[1] == 'w'
                && whiteFace[0] == 'w' && blueFace[0] == 'w')
            {
                resetLocation();
                li();bi();r();bi();ri();b2();l();
            }
            // OLL 11
            else if (orangeFace[1] == 'w' && redFace[2] == 'w' && greenFace[2] == 'w' && blueFace[1] == 'w'
                && whiteFace[6] == 'w' && blueFace[2] == 'w')
            {
                resetLocation();
                li();r2();b();ri();b();r();b2();ri();b();l();ri();
            }
            // OLL 12
            else if (orangeFace[1] == 'w' && redFace[0] == 'w' && greenFace[0] == 'w' && blueFace[1] == 'w'
                && whiteFace[2] == 'w' && orangeFace[0] == 'w')
            {
                resetLocation();
                r();b();u();b2();r();b();r2();u();r();u2();ri();
            }

            // Fish Shapes

            // OLL 9
            else if (orangeFace[1] == 'w' && redFace[0] == 'w' && greenFace[1] == 'w' && blueFace[0] == 'w'
                && whiteFace[6] == 'w' && orangeFace[0] == 'w')
            {
                resetLocation();
                fi();uinv();f();l();fi();li();u();l();f();li();
            }
            // OLL 10
            else if (redFace[1] == 'w' && redFace[2] == 'w' && greenFace[1] == 'w' && blueFace[2] == 'w'
                && whiteFace[8] == 'w' && orangeFace[2] == 'w')
            {
                resetLocation();
                f();u();fi();ri();f();r();uinv();ri();fi();r();
            }
            // OLL 35
            else if (whiteFace[0] == 'w' && redFace[2] == 'w' && greenFace[0] == 'w' && blueFace[1] == 'w'
                && whiteFace[8] == 'w' && orangeFace[1] == 'w')
            {
                resetLocation();
                r();u2();r2();f();r();fi();r();u2();ri();
            }
            // OLL 37
            else if (whiteFace[0] == 'w' && redFace[2] == 'w' && greenFace[0] == 'w' && greenFace[1] == 'w'
                && whiteFace[8] == 'w' && redFace[1] == 'w')
            {
                resetLocation();
                ri();f();r();fi();uinv();fi();u();f();
            }

            // Awkward Shapes

            // OLL 29
            else if (whiteFace[0] == 'w' && redFace[0] == 'w' && orangeFace[2] == 'w' && blueFace[1] == 'w'
                && whiteFace[2] == 'w' && redFace[1] == 'w')
            {
                resetLocation();
                bi();ri();b();li();bi();r2();bi();ri();b2();l();
            }
            // OLL 30
            else if (whiteFace[0] == 'w' && redFace[0] == 'w' && orangeFace[2] == 'w' && blueFace[1] == 'w'
                && whiteFace[2] == 'w' && orangeFace[1] == 'w')
            {
                resetLocation();
                bi();r();u();r2();u();r2();u2();ri();u();b();
            }
            // OLL 41
            else if (whiteFace[6] == 'w' && blueFace[0] == 'w' && blueFace[2] == 'w' && greenFace[1] == 'w'
                && whiteFace[8] == 'w' && redFace[1] == 'w')
            {
                resetLocation();
                l();r2();di();fi();d();f();r();fi();r();li();
            }
            // OLL 42
            else if (whiteFace[0] == 'w' && greenFace[0] == 'w' && greenFace[2] == 'w' && blueFace[1] == 'w'
                && whiteFace[2] == 'w' && redFace[1] == 'w')
            {
                resetLocation();
                li();r2();d();b();di();bi();ri();b();ri();l();
            }
            // OLL 28 All corners oriented
            else if (whiteFace[0] == 'w' && greenFace[1] == 'w' && whiteFace[6] == 'w' && whiteFace[8] == 'w'
                && whiteFace[2] == 'w' && redFace[1] == 'w')
            {
                resetLocation();
                ri();f();r();fi();b();uinv();fi();u();f();bi();
            }
        }

        // 2 edges flipped correctly in a line

        else if ((whiteFace[1] == 'w' && whiteFace[7] == 'w') || (whiteFace[3] == 'w' && whiteFace[5] == 'w'))
        {

            // C Shapes

            // OLL 34 City
            if (whiteFace[6] == 'w' && whiteFace[8] == 'w' && orangeFace[0] == 'w'
                && redFace[2] == 'w' && blueFace[1] == 'w' && greenFace[1] == 'w')
            {
                resetLocation();
                r();u();ri();uinv();bi();ri();f();r();fi();b();
            }
            // OLL 46 Left C
            else if (whiteFace[6] == 'w' && whiteFace[0] == 'w' && orangeFace[1] == 'w'
                && redFace[2] == 'w' && redFace[1] == 'w' && redFace[0] == 'w')
            {
                resetLocation();
                ri();uinv();ri();f();r();fi();u();r();
            }

            // T Shapes

            // OLL 33 Chameleon T
            else if (whiteFace[2] == 'w' && whiteFace[8] == 'w' && greenFace[1] == 'w'
                && greenFace[0] == 'w' && blueFace[1] == 'w' && blueFace[2] == 'w')
            {
                resetLocation();
                r();u();ri();uinv();ri();f();r();fi();
            }
            // OLL 45 T
            else if (whiteFace[2] == 'w' && whiteFace[8] == 'w' && greenFace[1] == 'w'
                && orangeFace[0] == 'w' && blueFace[1] == 'w' && orangeFace[2] == 'w')
            {
                resetLocation();
                f();r();u();ri();uinv();fi();
            }

            // I Shapes

            // OLL 55 Highway
            else if (orangeFace[0] == 'w' && orangeFace[1] == 'w' && orangeFace[2] == 'w'
                && redFace[2] == 'w' && redFace[1] == 'w' && redFace[0] == 'w')
            {
                resetLocation();
                r();u2();r2();uinv();r();uinv();ri();u2();f();r();fi();
            }
            // OLL 56
            else if (orangeFace[0] == 'w' && blueFace[1] == 'w' && orangeFace[2] == 'w'
                && redFace[2] == 'w' && greenFace[1] == 'w' && redFace[0] == 'w')
            {
                resetLocation();
                f();r();u();ri();uinv();r();fi();l();f();ri();fi();li();
            }
             // OLL 51
            else if (greenFace[0] == 'w' && blueFace[1] == 'w' && blueFace[2] == 'w'
                && redFace[2] == 'w' && greenFace[1] == 'w' && redFace[0] == 'w')
            {
                resetLocation();
                f();u();r();uinv();ri();u();r();uinv();ri();fi();
            }
            // OLL 52 Rice Cooker
            else if (greenFace[0] == 'w' && orangeFace[1] == 'w' && blueFace[2] == 'w'
                && redFace[2] == 'w' && redFace[1] == 'w' && redFace[0] == 'w')
            {
                resetLocation();
                ri();uinv();r();uinv();ri();u();fi();u();f();r();
            }

            // Big Lightning Bolt Shapes

            // OLL 39
            else if (whiteFace[2] == 'w' && whiteFace[6] == 'w' && greenFace[1] == 'w'
                && redFace[0] == 'w' && blueFace[1] == 'w' && blueFace[2] == 'w')
            {
                resetLocation();
                l();fi();li();uinv();l();u();f();uinv();li();
            }
            // OLL 40
            else if (whiteFace[0] == 'w' && whiteFace[8] == 'w' && greenFace[1] == 'w'
                && orangeFace[2] == 'w' && blueFace[1] == 'w' && blueFace[0] == 'w')
            {
                resetLocation();
                ri();f();r();u();ri();uinv();fi();u();r();
            }

            // Knight Move Shapes

            // OLL 13
            else if (greenFace[2] == 'w' && whiteFace[6] == 'w' && greenFace[1] == 'w'
                && redFace[2] == 'w' && blueFace[1] == 'w' && blueFace[2] == 'w')
            {
                resetLocation();
                f();u();r();u2();ri();uinv();r();u();ri();fi();
            }
            // OLL 14
            else if (greenFace[0] == 'w' && whiteFace[8] == 'w' && greenFace[1] == 'w'
                && orangeFace[0] == 'w' && blueFace[1] == 'w' && blueFace[0] == 'w')
            {
                resetLocation();
                ri();f();r();u();ri();fi();r();f();uinv();fi();
            }
            // OLL 15
            else if (greenFace[2] == 'w' && whiteFace[0] == 'w' && greenFace[1] == 'w'
                && orangeFace[2] == 'w' && blueFace[1] == 'w' && redFace[2] == 'w')
            {
                resetLocation();
                ri();fi();r();li();uinv();l();u();ri();f();r();
            }
            // OLL 16
            else if (greenFace[0] == 'w' && whiteFace[2] == 'w' && greenFace[1] == 'w'
                && orangeFace[0] == 'w' && blueFace[1] == 'w' && redFace[0] == 'w')
            {
                resetLocation();
                l();f();li();r();u();ri();uinv();l();fi();li();
            }

            // OLL 57 All corners oriented
            else if (whiteFace[0] == 'w' && greenFace[1] == 'w' && whiteFace[6] == 'w' && whiteFace[8] == 'w'
                && whiteFace[2] == 'w' && blueFace[1] == 'w')
            {
                resetLocation();
                r();u();ri();uinv();l();ri();f();r();fi();li();
            }

        }

        /////////// END OF 57 OLL ALGORITHMS ///////////

        /* This portion is used to determine how much y is needed to execute the OLL algs. Since
         * it's only a determination segment, trial is ON. This is why in each alg, resetLocation
         * function is used to reset the cube to initial OLL state and solve it.
         */
        trial = true;
        U(); // This is the reason checkpoint is used - to avoid unwanted U turns which increases moveCount.
        x++; // keeps track of no. of U moves done and sets y value accordingly
        if (x == 1)
            y = 1;
        else if (x == 2)
            y = 2;
        else if (x == 3)
            y = -1;
        else if (x > 4)
            return; // This is important as it returns control if OLL is unsolvable (invalid input)

    }
    if (x != 0) // only if OLL is unsolved
        Uinv(); // counters the unwanted U done in the final run through the loop.
    trial = false; //switches of trial since it's switched in the final run through the loop
}
// Solves the PLL (Permutation of Last Layer) case (21 algs) [similar to OLL function]
void pll()
{
    y = 0;
    int x = 0; // keeps track of no. of U moves
    createCheckpoint();

    // checks if Last layer is permuted, if not, control enters loop
    while (!(greenFace[0] == greenFace[1] && greenFace[1] == greenFace[2] && orangeFace[0] == orangeFace[1]
           && orangeFace[1] == orangeFace[2] && blueFace[0] == blueFace[1] && blueFace[1] == blueFace[2]
           && redFace[0] == redFace[1] && redFace[1] == redFace[2]))
    {
        trial = false; // trial is OFF

        /* 21 different PLL cases are checked below. PLL name is used for checking bugs
         * Section can be overlooked unless there are some bugs and more optimal algs
         * Again, small letters functions are used to change algs according to y value and
         * reduce moveCount.
         */

        // Edge cycle PLLs

        if (greenFace[0] == greenFace[2] && orangeFace[0] == orangeFace[2] && blueFace[0] == blueFace[2]
             && redFace[0] == redFace[2])
        {
            // H Perm
            if (greenFace [1] == blueFace[0] && orangeFace[1] == redFace[0])
            {
                resetLocation();
                l();r();u2();li();ri();fi();bi();u2();f();b();
                // L2 B2 F2 R2 D L2 B2 F2 R2 (9 move) but too many half turns (depends on robot)
            }
            // U Perm Cw
            else if (redFace[1] == greenFace[0] && greenFace[1] == orangeFace[0])
            {
                resetLocation();
                f2();u();l();ri();f2();li();r();u();f2();
            }
            // U Perm Ccw
            else if (redFace[0] == greenFace[1] && greenFace[0] == orangeFace[1])
            {
                resetLocation();
                f2();uinv();l();ri();f2();li();r();uinv();f2();
            }
            // Z Perm
            else if (orangeFace[1] == greenFace[0] && greenFace[1] == orangeFace[0])
            {
                resetLocation();
                r2();f();l();fi();r();li();fi();r();l();fi();li();f();
            }
        }
        // A Perm Cw
        else if (greenFace[0] == greenFace[1] && orangeFace[1] == orangeFace[2] && blueFace[0] == blueFace[2]
                 && blueFace[1] == greenFace[2])
        {
            resetLocation();
            ri();f();ri();b2();r();fi();ri();b2();r2();
        }
        // A Perm Ccw
        else if (greenFace[0] == greenFace[1] && orangeFace[1] == orangeFace[2] && redFace[0] == redFace[2]
                 && redFace[1] == greenFace[2])
        {
            resetLocation();
            r2();b2();r();f();ri();b2();r();fi();r();
        }
        // E Perm
        else if (greenFace[1] == orangeFace[2] && greenFace[1] == redFace[0] && blueFace[1] == orangeFace[0]
                 && blueFace[1] == redFace[2])
        {
            resetLocation();
            d();ri();d2();fi();d();l();di();f();d2();r();di();fi();li();f();
        }
        // F Perm
        else if (greenFace[1] == greenFace[2] && greenFace[1] == greenFace[0] && orangeFace[1] != orangeFace[2]
                 && redFace[1] != redFace[0])
        {
            resetLocation();
            ri();u();r();uinv();r2();fi();uinv();f();u();r();f();ri();fi();r2();
        }
        // G Perm 4
        else if (blueFace[0] == blueFace[2] && orangeFace[1] == orangeFace[2] && blueFace[1] == greenFace[0]
                 && blueFace[0] == greenFace[1])
        {
            resetLocation();
            f2();d();ri();u();ri();uinv();r();di();f2();li();u();l();
        }
        // G Perm 2
        else if (orangeFace[0] == orangeFace[2] && redFace[1] == redFace[2] && orangeFace[1] == blueFace[0]
                 && orangeFace[0] == blueFace[1])
        {
            resetLocation();
            ri();uinv();r();b2();d();li();u();l();uinv();l();di();b2();
        }
        // G Perm 3
        else if (blueFace[0] == blueFace[2] && redFace[1] ==redFace[0] && blueFace[1] == greenFace[2]
                 && blueFace[0] == greenFace[1])
        {
            resetLocation();
            f2();di();l();uinv();l();u();li();d();f2();r();uinv();ri();
        }
        // G Perm 1
        else if (orangeFace[0] == orangeFace[2] && redFace[1] == redFace[0] && orangeFace[1] == greenFace[2]
                 && orangeFace[0] == greenFace[1])
        {
            resetLocation();
            r();u();ri();f2();di();l();uinv();li();u();li();d();f2();
        }
        // J Perm 2-1
        else if (redFace[0] == redFace[1] && redFace[0] == redFace[2] && blueFace[0] == blueFace[1]
                 && orangeFace[0] == orangeFace[1] && greenFace[0] == greenFace[1])
        {
            resetLocation();
            ri();li();u2();l();u();li();u2();r();uinv();l();
        }
        // J Perm 1-2
        else if (redFace[0] == redFace[1] && redFace[0] == redFace[2] && blueFace[2] == blueFace[1]
                 && orangeFace[2] == orangeFace[1] && greenFace[2] == greenFace[1])
        {
            resetLocation();
            r();l();u2();li();uinv();l();u2();ri();u();li();
        }
        // N Perm 1-2
        else if (redFace[0] == orangeFace[2] && redFace[1] == redFace[2] && blueFace[2] == blueFace[1]
                 && orangeFace[2] == orangeFace[1] && greenFace[2] == greenFace[1] && redFace[2] == orangeFace[0])
        {
            resetLocation();
            r();uinv();l();u2();ri();u();li();r();uinv();l();u2();ri();u();li();
        }
        // N Perm 2-1
        else if (redFace[0] == orangeFace[2] && redFace[0] == redFace[1] && blueFace[0] == blueFace[1]
                 && orangeFace[0] == orangeFace[1] && greenFace[0] == greenFace[1] && redFace[2] == orangeFace[0])
        {
            resetLocation();
            ri();u();li();u2();r();uinv();l();ri();u();li();u2();r();uinv();l();
        }
        // R Perm Right tail
        else if (greenFace[0] == greenFace[2] && orangeFace[1] == greenFace[0] && redFace[0] == redFace[1]
                 && redFace[2] == orangeFace[0])
        {
            resetLocation();
            l();u2();li();u2();l();fi();li();uinv();l();u();l();f();l2();
        }
        // R Perm Left tail
        else if (greenFace[0] == greenFace[2] && redFace[1] == greenFace[0] && orangeFace[2] == orangeFace[1]
                 && redFace[2] == orangeFace[0])
        {
            resetLocation();
            ri();u2();r();u2();ri();f();r();u();ri();uinv();ri();fi();r2();
        }
        // T Perm
        else if (orangeFace[0] == orangeFace[2] && greenFace[0] == greenFace[1] && blueFace[1] == blueFace[2]
                 && greenFace[2] == blueFace[0])
        {
            resetLocation();
            r();u();ri();uinv();ri();f();r2();uinv();ri();uinv();r();u();ri();fi();
            //F2 U' F2 D R2 B2 U B2 D' R2 (10 move)
        }
        // V Perm
        else if (greenFace[0] == greenFace[1] && orangeFace[1] == orangeFace[2] && greenFace[2] == redFace[1]
                 && orangeFace[0] == blueFace[1])
        {
            resetLocation();
            ri();u();ri();uinv();bi();ri();b2();uinv();bi();u();bi();r();b();r();
        }
        // Y Perm
        else if (greenFace[0] == greenFace[1] && redFace[1] == redFace[2] && greenFace[2] == orangeFace[1]
                 && redFace[0] == blueFace[1])
        {
            resetLocation();
            f2();u();f();uinv();fi();u();l();f();ri();f();r();f();li();fi();
            // F2 U F2 U F2 U' R' U' R F2 R' U R  (13 Move)
        }

        /////////// END OF 21 PLL ALGORITHMS ///////////

        /* This portion is used to determine how much y is needed to execute the OLL algs. Since
         * it's only a determination segment, trial is ON. This is why in each alg, resetLocation
         * function is used to reset the cube to initial OLL state and solve it.
         */
        trial = true;
        U();
        x++;
        if (x == 1)
            y = 1;
        else if (x == 2)
            y = 2;
        else if (x == 3)
            y = -1;
        else if (x > 4)
            return; // This is important as it returns control if PLL is unsolvable (invalid input)
    }
    if (x != 0)
        Uinv(); // counters the unwanted U done in the final run through the loop.
    trial = false; //switches of trial since it's switched in the final run through the loop
}
// Solves AUF (Adjust U Face) - only one move - aligns U layer to match with the rest of the cube
void auf()
{
    // 3 possible cases are tested below
    if (greenFace[1] == redFace[4])
        Uinv();
    else if (greenFace[1] == blueFace[4])
        U2();
    else if (greenFace[1] == orangeFace[4])
        U();

    // This block is the main error checker. If the cube is not solvable, it clears the solutionList and appends error message
    if (!(greenFace[0] == 'g' && greenFace[1] == 'g' && greenFace[2] == 'g'
            && redFace[0] == 'r' && redFace[1] == 'r' && redFace[2] == 'r'
            && blueFace[0] == 'b' && blueFace[1] == 'b' && blueFace[2] == 'b'
            && orangeFace[0] == 'o' && orangeFace[1] == 'o' && orangeFace[2] == 'o'))
    {
        solutionList.clear();
        solutionList.append("ERROR");
    }
}
/* This function takes any list (array of strings which contain each move of the solution in a different block)
 * and "reduces" it. "Reducing" means shortening segments like "U2 U'" which can simply be written as "U", etc.
 * Sometimes, it does not reduce the move count at all but usually reduces around 2-5 moves.
 */
QStringList shortSolution(QStringList &list)
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
                list[i + 1] = list[i][0] + "2";
                list[i] = "trash";
            }
            else if (list[i][1] == 39 && list[i + 1][1] == 39)
            {
                list[i + 1] = list[i][0] + "2";
                list[i] = "trash";
            }
            else if (list[i][1] == '2' && list[i + 1][1] == '2')
            {
                list[i] = "trash";
                list[i + 1] = "trash";
            }
            else if (list[i][1] == '\0' && list[i + 1][1] == 39)
            {
                list[i] = "trash";
                list[i + 1] = "trash";
            }
            else if (list[i][1] == '\0' && list[i + 1][1] == '2')
            {
                list[i + 1] = list[i][0] + "'";
                list[i] = "trash";
            }
            else if (list[i][1] == 39 && list[i + 1][1] == '\0')
            {
                list[i] = "trash";
                list[i + 1] = "trash";
            }
            else if (list[i][1] == 39 && list[i + 1][1] == '2')
            {
                list[i + 1] = list[i][0];
                list[i] = "trash";
            }
            else if (list[i][1] == '2' && list[i + 1][1] == '\0')
            {
                list[i + 1] = list[i][0] + "'";
                list[i] = "trash";
            }
            else if (list[i][1] == '2' && list[i + 1][1] == 39)
            {
                list[i + 1] = list[i][0];
                list[i] = "trash";
            }
        }
    }
    list.removeAll("trash"); // all trash values are removed
    return list;
}

// function that accepts a string and returns the move count as an integer
int findMoveCount(QString &s)
{
    int mc = 0;
    for (int i = 0; i < s.length(); i++)
    {
        // move count is incremented every time an alphabet is encountered in the string
        if (s[i] == 'L' || s[i] == 'R' || s[i] == 'U' || s[i] == 'D' || s[i] == 'F' || s[i] == 'B')
            mc++;
    }
    return mc;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// CONTROL FUNCTION////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// This function is main control function which solves the cube
void solveCube()
{
    // Everything is cleared and kept empty to store the solution
    solutionList.clear();
    solution = "";
    solution_short = "";
    moveCount = 0;
    moveCount_short = 0;

    // prints and executes bottom layer (yellow) cross
    cross();
    solutionList.append("trash"); // this is done so that, the list can be split into parts easily

    // prints and executes F2L. Since there are 4 pairs, it is executed 4 times.
    for (int i = 0; i < 4; i++)
    {
        f2l();
        solutionList.append("trash");
    }

    // prints and executes OLL (white) layer
    oll();
    solutionList.append("trash");

    // prints and executes PLL
    pll();

    // adjust U face
    auf();

    // if cube is unsolvable, returns a message to mainwindow.cpp
    if (solutionList[0] == "ERROR")
    {
        solution = "No Solution Possible. Please retry with proper scramble/colours.";
        moveCount = 0;
        return;
    }

    // stores the list as a string with each element separated by a space
    solution = solutionList.join(" ");

    // create a temp list which stores different parts of the solution, each, as an element
    QStringList solutionList_temp = solution.split("trash");

    // create sub-lists which take solutionList_temp and store each of its element as a separate list which contains
    // each element as a separate move (similar to solutionList, only difference being, cross list stores only the
    // solution for cross, etc.
    QStringList cross = solutionList_temp[0].split(" "), f2l1 = solutionList_temp[1].split(" "),
            f2l2 = solutionList_temp[2].split(" "), f2l3 = solutionList_temp[3].split(" "),
            f2l4 = solutionList_temp[4].split(" "), oll = solutionList_temp[5].split(" "),
             pll = solutionList_temp[6].split(" ");

    // shortens each list by merging moves like L L2, etc. Any number can be used instead of 10
    // That number signifies how many times the solution is shortened
    // Ex: U2 L L2 L U -> U2 U -> U'
    for (int i = 0; i < 10; i++)
    {
        cross = shortSolution(cross);
        f2l1 = shortSolution(f2l1);
        f2l2 = shortSolution(f2l2);
        f2l3 = shortSolution(f2l3);
        f2l4 = shortSolution(f2l4);
        oll = shortSolution(oll);
        pll = shortSolution(pll);
    }


    // solution string stores the entire solution, formatted neatly and displays the solution in different steps
    solution = "Cross: " + cross.join(" ") + '\n' + "F2L 1: " + f2l1.join(" ") + '\n' + "F2L 2: " + f2l2.join(" ") + '\n' +
            "F2L 3: " + f2l3.join(" ") + '\n' + "F2L 4: " + f2l4.join(" ") + '\n' + "OLL: " + oll.join(" ") + '\n' +
            "PLL: " + pll.join(" ");

    QString solution_full = cross.join(" ") + f2l1.join(" ") + f2l2.join(" ") + f2l3.join(" ")
                                    + f2l4.join(" ") + oll.join(" ") + pll.join(" ");

    moveCount = findMoveCount(solution_full);

    // shortens the solution multiple times (20 is not required. Can be any number >= 1 )
    for (int i = 0; i < 20; i++)
        solutionList = shortSolution(solutionList);


    // Combines all elements of the solution array into one string
    solution_short = solutionList.join(" ");

    moveCount_short = findMoveCount(solution_short);
}

// L2 B2 L' F R' F' D B D R2 D2 U2 L2 R L R L U' F2 D'
