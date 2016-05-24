#include <QApplication>
#include <QString>
#include <QStringList>
#include "../Header/solver2x2.h"
#include "../Header/solver.h"

/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Variable Declarations //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// these variables store the scrambled state of the cube used by scrambledialog.cpp
extern QString whiteFace2_scramble, yellowFace2_scramble, greenFace2_scramble,
                blueFace2_scramble, redFace2_scramble, orangeFace2_scramble;

// stores the scramble string inputted by the user
extern QString scramble2;

QString whiteFace2 = "wwww";
QString yellowFace2 = "yyyy";
QString greenFace2 = "gggg";
QString blueFace2 = "bbbb";
QString redFace2 = "rrrr";
QString orangeFace2 = "oooo";

// variables used to create checkpoint locations
QString blueFace2_cp, whiteFace2_cp, greenFace2_cp, orangeFace2_cp, yellowFace2_cp, redFace2_cp;

// variable used to store every move of the solution2 in a list
QStringList solutionList2;

// char variable that stores the colour of the U Face to be solved in the second (final) step
//char c;

// strings that store the solution2 or a reduced solution2
QString solution2;
QString solution2_short;

//variables that store the no. of moves for the respective solution2
int moveCount2;
int moveCount2_short;

// trial2 variable is used to check amount of "y" needed for alg. Used with checkpoint variables. 1 or 0
bool trial2 = false;

/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CubeSolver Implementation /////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// creates a checkpoint to which the current state variables can be restored after determining "y" value
void createCheckpoint2()
{
    blueFace2_cp = blueFace2;
    whiteFace2_cp = whiteFace2;
    greenFace2_cp = greenFace2;
    orangeFace2_cp = orangeFace2;
    yellowFace2_cp = yellowFace2;
    redFace2_cp = redFace2;
}

// resets the current state variables to the checkpoint location
void resetLocation2()
{
    blueFace2 = blueFace2_cp;
    whiteFace2 = whiteFace2_cp;
    greenFace2 = greenFace2_cp;
    orangeFace2 = orangeFace2_cp;
    yellowFace2 = yellowFace2_cp;
    redFace2 = redFace2_cp;
}

// Rotation Functions used to simulate a turn of a face of the cube
void Cw_2(QString &face, QString &face_temp)
{
    face[0] = face_temp[2];
    face[1] = face_temp[0];
    face[2] = face_temp[3];
    face[3] = face_temp[1];
}
void Ccw_2(QString &face, QString &face_temp)
{
    face[0] = face_temp[1];
    face[1] = face_temp[3];
    face[2] = face_temp[0];
    face[3] = face_temp[2];
}
void Cw2_2(QString &face, QString &face_temp)
{
    face[0] = face_temp[3];
    face[1] = face_temp[2];
    face[2] = face_temp[1];
    face[3] = face_temp[0];
}

void L_2()
{
    QString blueFace2_temp, whiteFace2_temp, greenFace2_temp, orangeFace2_temp, yellowFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace2_temp[i] = blueFace2[i];
        whiteFace2_temp[i] = whiteFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
    }

    whiteFace2[0]= blueFace2_temp[3];
    whiteFace2[2]= blueFace2_temp[1];
    greenFace2[0]= whiteFace2_temp[0];
    greenFace2[2]= whiteFace2_temp[2];
    yellowFace2[0]= greenFace2_temp[0];
    yellowFace2[2]= greenFace2_temp[2];
    blueFace2[3]= yellowFace2_temp[0];
    blueFace2[1]= yellowFace2_temp[2];

    Cw_2(orangeFace2, orangeFace2_temp);
    if (trial2 == false)
    {
        solutionList2.append("L");
    }

}
void Li_2()
{
    QString blueFace2_temp, whiteFace2_temp, greenFace2_temp, orangeFace2_temp, yellowFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace2_temp[i] = blueFace2[i];
        whiteFace2_temp[i] = whiteFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
    }

    whiteFace2[0] = greenFace2_temp[0];
    whiteFace2[2] = greenFace2_temp[2];
    greenFace2[0] = yellowFace2_temp[0];
    greenFace2[2] = yellowFace2_temp[2];
    yellowFace2[0] = blueFace2_temp[3];
    yellowFace2[2] = blueFace2_temp[1];
    blueFace2[3] = whiteFace2_temp[0];
    blueFace2[1] = whiteFace2_temp[2];

    Ccw_2(orangeFace2, orangeFace2_temp);

    if (trial2 == false)
    {
        solutionList2.append("L'");
    }
}
void R_2()
{
    QString blueFace2_temp, whiteFace2_temp, greenFace2_temp, redFace2_temp, yellowFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace2_temp[i] = blueFace2[i];
        whiteFace2_temp[i] = whiteFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        redFace2_temp[i] = redFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
    }

    whiteFace2[1] = greenFace2_temp[1];
    whiteFace2[3] = greenFace2_temp[3];
    greenFace2[1] = yellowFace2_temp[1];
    greenFace2[3] = yellowFace2_temp[3];
    yellowFace2[1] = blueFace2_temp[2];
    yellowFace2[3] = blueFace2_temp[0];
    blueFace2[0] = whiteFace2_temp[3];
    blueFace2[2] = whiteFace2_temp[1];

    Cw_2(redFace2, redFace2_temp);
    if (trial2 == false)
    {
        solutionList2.append("R");
    }
}
void Ri_2()
{
    QString blueFace2_temp, whiteFace2_temp, greenFace2_temp, redFace2_temp, yellowFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace2_temp[i] = blueFace2[i];
        whiteFace2_temp[i] = whiteFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        redFace2_temp[i] = redFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
    }
    whiteFace2[1] = blueFace2_temp[2];
    whiteFace2[3] = blueFace2_temp[0];
    greenFace2[1] = whiteFace2_temp[1];
    greenFace2[3] = whiteFace2_temp[3];
    yellowFace2[1] = greenFace2_temp[1];
    yellowFace2[3] = greenFace2_temp[3];
    blueFace2[0] = yellowFace2_temp[3];
    blueFace2[2] = yellowFace2_temp[1];

    Ccw_2(redFace2, redFace2_temp);
    if (trial2 == false)
    {
        solutionList2.append("R'");
    }
}
void U_2()
{
    QString blueFace2_temp, whiteFace2_temp, greenFace2_temp, redFace2_temp, orangeFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace2_temp[i] = blueFace2[i];
        whiteFace2_temp[i] = whiteFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        redFace2_temp[i] = redFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
    }

    redFace2[0] = blueFace2_temp[0];
    redFace2[1] = blueFace2_temp[1];
    greenFace2[0] = redFace2_temp[0];
    greenFace2[1] = redFace2_temp[1];
    orangeFace2[0] = greenFace2_temp[0];
    orangeFace2[1] = greenFace2_temp[1];
    blueFace2[0] = orangeFace2_temp[0];
    blueFace2[1] = orangeFace2_temp[1];


    Cw_2(whiteFace2, whiteFace2_temp);

    if (trial2 == false)
    {
        solutionList2.append("U");
    }
}
void Uinv_2()
{
    QString blueFace2_temp, whiteFace2_temp, greenFace2_temp, redFace2_temp, orangeFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace2_temp[i] = blueFace2[i];
        whiteFace2_temp[i] = whiteFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        redFace2_temp[i] = redFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
    }

    redFace2[0] = greenFace2_temp[0];
    redFace2[1] = greenFace2_temp[1];
    greenFace2[0] = orangeFace2_temp[0];
    greenFace2[1] = orangeFace2_temp[1];
    orangeFace2[0] = blueFace2_temp[0];
    orangeFace2[1] = blueFace2_temp[1];
    blueFace2[0] = redFace2_temp[0];
    blueFace2[1] = redFace2_temp[1];

    Ccw_2(whiteFace2, whiteFace2_temp);

    if (trial2 == false)
    {
        solutionList2.append("U'");
    }
}
void D_2()
{
    QString blueFace2_temp, yellowFace2_temp, greenFace2_temp, redFace2_temp, orangeFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace2_temp[i] = blueFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        redFace2_temp[i] = redFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
    }

    redFace2[2] = greenFace2_temp[2];
    redFace2[3] = greenFace2_temp[3];
    greenFace2[2] = orangeFace2_temp[2];
    greenFace2[3] = orangeFace2_temp[3];
    orangeFace2[2] = blueFace2_temp[2];
    orangeFace2[3] = blueFace2_temp[3];
    blueFace2[2] = redFace2_temp[2];
    blueFace2[3] = redFace2_temp[3];

    Cw_2(yellowFace2, yellowFace2_temp);
    if (trial2 == false)
    {
        solutionList2.append("D");
    }

}
void Di_2()
{
    QString blueFace2_temp, yellowFace2_temp, greenFace2_temp, redFace2_temp, orangeFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace2_temp[i] = blueFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        redFace2_temp[i] = redFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
    }

    redFace2[2] = blueFace2_temp[2];
    greenFace2[2] = redFace2_temp[2];
    orangeFace2[2] = greenFace2_temp[2];
    blueFace2[2] = orangeFace2_temp[2];
    redFace2[3] = blueFace2_temp[3];
    greenFace2[3] = redFace2_temp[3];
    orangeFace2[3] = greenFace2_temp[3];
    blueFace2[3] = orangeFace2_temp[3];

    Ccw_2(yellowFace2, yellowFace2_temp);
    if (trial2 == false)
    {
        //printf("D' ");
        solutionList2.append("D'");

    }
}
void F_2()
{
    QString whiteFace2_temp, yellowFace2_temp, greenFace2_temp, redFace2_temp, orangeFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        whiteFace2_temp[i] = whiteFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        redFace2_temp[i] = redFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
    }

    whiteFace2[2] = orangeFace2_temp[3];
    whiteFace2[3] = orangeFace2_temp[1];
    redFace2[0] = whiteFace2_temp[2];
    redFace2[2] = whiteFace2_temp[3];
    yellowFace2[0] = redFace2_temp[2];
    yellowFace2[1] = redFace2_temp[0];
    orangeFace2[1] = yellowFace2_temp[0];
    orangeFace2[3] = yellowFace2_temp[1];

    Cw_2(greenFace2, greenFace2_temp);
    if (trial2 == false)
    {
        solutionList2.append("F");
    }
}
void Fi_2()
{
    QString whiteFace2_temp, yellowFace2_temp, greenFace2_temp, redFace2_temp, orangeFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        whiteFace2_temp[i] = whiteFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        redFace2_temp[i] = redFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
    }

    whiteFace2[2] = redFace2_temp[0];
    whiteFace2[3] = redFace2_temp[2];
    redFace2[0] = yellowFace2_temp[1];
    redFace2[2] = yellowFace2_temp[0];
    yellowFace2[0] = orangeFace2_temp[1];
    yellowFace2[1] = orangeFace2_temp[3];
    orangeFace2[1] = whiteFace2_temp[3];
    orangeFace2[3] = whiteFace2_temp[2];

    Ccw_2(greenFace2, greenFace2_temp);

    if (trial2 == false)
    {
        solutionList2.append("F'");
    }
}
void B_2()
{
    QString whiteFace2_temp, yellowFace2_temp, blueFace2_temp, redFace2_temp, orangeFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        whiteFace2_temp[i] = whiteFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
        blueFace2_temp[i] = blueFace2[i];
        redFace2_temp[i] = redFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
    }

    whiteFace2[0] = redFace2_temp[1];
    whiteFace2[1] = redFace2_temp[3];
    redFace2[1] = yellowFace2_temp[3];
    redFace2[3] = yellowFace2_temp[2];
    yellowFace2[2] = orangeFace2_temp[0];
    yellowFace2[3] = orangeFace2_temp[2];
    orangeFace2[0] = whiteFace2_temp[1];
    orangeFace2[2] = whiteFace2_temp[0];

    Cw_2(blueFace2, blueFace2_temp);
    if (trial2 == false)
    {
        solutionList2.append("B");
    }
}
void Bi_2()
{
    QString whiteFace2_temp, yellowFace2_temp, blueFace2_temp, redFace2_temp, orangeFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        whiteFace2_temp[i] = whiteFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
        blueFace2_temp[i] = blueFace2[i];
        redFace2_temp[i] = redFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
    }

    whiteFace2[0] = orangeFace2_temp[2];
    whiteFace2[1] = orangeFace2_temp[0];
    redFace2[1] = whiteFace2_temp[0];
    redFace2[3] = whiteFace2_temp[1];
    yellowFace2[2] = redFace2_temp[3];
    yellowFace2[3] = redFace2_temp[1];
    orangeFace2[0] = yellowFace2_temp[2];
    orangeFace2[2] = yellowFace2_temp[3];

    Ccw_2(blueFace2, blueFace2_temp);
    if (trial2 == false)
    {
        solutionList2.append("B'");
    }
}
void L2_2()
{
    QString blueFace2_temp, whiteFace2_temp, greenFace2_temp, orangeFace2_temp, yellowFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace2_temp[i] = blueFace2[i];
        whiteFace2_temp[i] = whiteFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
    }

    whiteFace2[0] = yellowFace2_temp[0];
    whiteFace2[2] = yellowFace2_temp[2];
    greenFace2[0] = blueFace2_temp[3];
    greenFace2[2] = blueFace2_temp[1];
    yellowFace2[0] = whiteFace2_temp[0];
    yellowFace2[2] = whiteFace2_temp[2];
    blueFace2[3] = greenFace2_temp[0];
    blueFace2[1] = greenFace2_temp[2];

    Cw2_2(orangeFace2, orangeFace2_temp);
    if (trial2 == false)
    {
        solutionList2.append("L2");
    }
}
void R2_2()
{
    QString blueFace2_temp, whiteFace2_temp, greenFace2_temp, redFace2_temp, yellowFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace2_temp[i] = blueFace2[i];
        whiteFace2_temp[i] = whiteFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        redFace2_temp[i] = redFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
    }

    whiteFace2[1] = yellowFace2_temp[1];
    whiteFace2[3] = yellowFace2_temp[3];
    greenFace2[1] = blueFace2_temp[2];
    greenFace2[3] = blueFace2_temp[0];
    yellowFace2[1] = whiteFace2_temp[1];
    yellowFace2[3] = whiteFace2_temp[3];
    blueFace2[2] = greenFace2_temp[1];
    blueFace2[0] = greenFace2_temp[3];

    Cw2_2(redFace2, redFace2_temp);
    if (trial2 == false)
    {
        solutionList2.append("R2");
    }
}
void U2_2()
{
    QString blueFace2_temp, whiteFace2_temp, greenFace2_temp, redFace2_temp, orangeFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace2_temp[i] = blueFace2[i];
        whiteFace2_temp[i] = whiteFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        redFace2_temp[i] = redFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
    }

    redFace2[0] = orangeFace2_temp[0];
    redFace2[1] = orangeFace2_temp[1];
    greenFace2[0] = blueFace2_temp[0];
    greenFace2[1] = blueFace2_temp[1];
    orangeFace2[0] = redFace2_temp[0];
    orangeFace2[1] = redFace2_temp[1];
    blueFace2[0] = greenFace2_temp[0];
    blueFace2[1] = greenFace2_temp[1];

    Cw2_2(whiteFace2, whiteFace2_temp);
    if (trial2 == false)
    {
        solutionList2.append("U2");
    }
}
void D2_2()
{
    QString blueFace2_temp, yellowFace2_temp, greenFace2_temp, redFace2_temp, orangeFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        blueFace2_temp[i] = blueFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        redFace2_temp[i] = redFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
    }

    redFace2[2] = orangeFace2_temp[2];
    redFace2[3] = orangeFace2_temp[3];
    greenFace2[2] = blueFace2_temp[2];
    greenFace2[3] = blueFace2_temp[3];
    orangeFace2[2] = redFace2_temp[2];
    orangeFace2[3] = redFace2_temp[3];
    blueFace2[2] = greenFace2_temp[2];
    blueFace2[3] = greenFace2_temp[3];

    Cw2_2(yellowFace2, yellowFace2_temp);
    if (trial2 == false)
    {
        solutionList2.append("D2");
    }
}
void F2_2()
{
    QString whiteFace2_temp, yellowFace2_temp, greenFace2_temp, redFace2_temp, orangeFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        whiteFace2_temp[i] = whiteFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
        greenFace2_temp[i] = greenFace2[i];
        redFace2_temp[i] = redFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
    }

    whiteFace2[2] = yellowFace2_temp[1];
    whiteFace2[3] = yellowFace2_temp[0];
    redFace2[0] = orangeFace2_temp[3];
    redFace2[2] = orangeFace2_temp[1];
    yellowFace2[1] = whiteFace2_temp[2];
    yellowFace2[0] = whiteFace2_temp[3];
    orangeFace2[3] = redFace2_temp[0];
    orangeFace2[1] = redFace2_temp[2];

    Cw2_2(greenFace2, greenFace2_temp);

    if (trial2 == false)
    {
        solutionList2.append("F2");
    }
}
void B2_2()
{
    QString whiteFace2_temp, yellowFace2_temp, blueFace2_temp, redFace2_temp, orangeFace2_temp;
    for (int i = 0; i < 9; i++)
    {
        whiteFace2_temp[i] = whiteFace2[i];
        yellowFace2_temp[i] = yellowFace2[i];
        blueFace2_temp[i] = blueFace2[i];
        redFace2_temp[i] = redFace2[i];
        orangeFace2_temp[i] = orangeFace2[i];
    }

    whiteFace2[0] = yellowFace2_temp[3];
    whiteFace2[1] = yellowFace2_temp[2];
    redFace2[1] = orangeFace2_temp[2];
    redFace2[3] = orangeFace2_temp[0];
    yellowFace2[3] = whiteFace2_temp[0];
    yellowFace2[2] = whiteFace2_temp[1];
    orangeFace2[2] = redFace2_temp[1];
    orangeFace2[0] = redFace2_temp[3];

    Cw2_2(blueFace2, blueFace2_temp);
    if (trial2 == false)
    {
        solutionList2.append("B2");
    }
}

// Identifies the permutation of D Layer (Solved, adj swap or diagonal swap)
int identifyDPerm()
{
    int pairCount = 0;
    char p;

    // counts no of pairs in D Layer
    if (greenFace2[2] == greenFace2[3])
    {
        pairCount++;
        p = 'g';
    }
    if (redFace2[2] == redFace2[3])
    {
        pairCount++;
        p = 'r';
    }
    if (blueFace2[2] == blueFace2[3])
    {
        pairCount++;
        p = 'b';
    }
    if (orangeFace2[2] == orangeFace2[3])
    {
        pairCount++;
        p = 'o';
    }

    //
    if (pairCount == 4)
    {
        return 0;
    }
    else if (pairCount == 1)
    {
        if (p == 'o')
            Di_2();
        else if (p == 'g')
            D2_2();
        else if (p == 'r')
            D_2();

        return 1;
    }
    else if (pairCount == 0)
    {
        QString temp = solutionList2[solutionList2.length() - 1];

        if (temp == "F'" || temp == "F" || temp == "F2")
        {
            F2_2();R2_2();F2_2();
        }
        else if (temp == "R" || temp == "R'" || temp == "R2")
        {
            R2_2();F2_2();R2_2();
        }\
        return 0;
    }
    return -1;
}


// converts a given scramble string into an actual scramble simulation in the program
void convertScramble2(QString &scram)
{
    trial2 = true; // trial2 is true since we don't want the scramble as part of the solution2

    QStringList s = scram.split(" ");

    foreach(QString move, s)
    {
        if (move == "R2")
            R2_2();
        else if (move == "U2")
            U2_2();
        else if (move == "F2")
            F2_2();
        else if (move == "L2")
            L2_2();
        else if (move == "D2")
            D2_2();
        else if (move == "B2")
            B2_2();

        else if (move == "R'")
            Ri_2();
        else if (move == "U'")
            Uinv_2();
        else if (move == "F'")
            Fi_2();
        else if (move == "L'")
            Li_2();
        else if (move == "D'")
            Di_2();
        else if (move == "B'")
            Bi_2();

        else if (move == "R")
            R_2();
        else if (move == "U")
            U_2();
        else if (move == "F")
            F_2();
        else if (move == "L")
            L_2();
        else if (move == "D")
            D_2();
        else if (move == "B")
            B_2();

    }
    trial2 = false; // switch off trial2

    /* assign "_scramble" variables the current scrambled state so that it can be viewed
     * using the "View Scramble" button. Actual usage in scrambledialog.cpp
     */
    blueFace2_scramble = blueFace2;
    whiteFace2_scramble = whiteFace2;
    greenFace2_scramble = greenFace2;
    orangeFace2_scramble = orangeFace2;
    yellowFace2_scramble = yellowFace2;
    redFace2_scramble = redFace2;
}

int firstLayer()
{
    if (yellowFace2[0] == yellowFace2[1] && yellowFace2[0] == yellowFace2[2] &&
            yellowFace2[0] == yellowFace2[3])
        return identifyDPerm(); //returns control so that further combinations aren't checked (unnecessary)


    trial2 = true; // since this brute force attacks every possible solution2, we don't want it to be stored in solutionList2

    QStringList set;
    set << "R" << "F" << "U" << "R'" << "F'" << "U'" << "R2" << "F2" << "U2";
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


            createCheckpoint2(); // in case this is not the correct combination
            convertScramble2(key); // uses convertScramble function to convert string to simulation

            //To check if the current combination solves the first layer
            if (yellowFace2[0] == yellowFace2[1] && yellowFace2[0] == yellowFace2[2] &&
                    yellowFace2[0] == yellowFace2[3])
            {
                trial2 = false; // don't want to affect other parts of the program
                QStringList temp = key.split(" "); // temp list stores each move separately
                temp.removeLast();
                solutionList2 += temp; // adds temp to solutionList2 (solutionList2 doesn't store automatically as trial2 was set to true)
                return identifyDPerm(); //returns control so that further combinations aren't checked (unnecessary)
            }

            resetLocation2(); // if the combination doesn't satisfy "if" condition, current state is reset to try next combination

            /*To provide all possible combinations by "overflowing"
             * the first character to the second character when
             * the last character of the set is reached.
             * Ex: (For a 2 char key) if first char reaches
             * 9 then the second char is set to 'a' and the first
             * char is also set to 'a' and the first char is again
             * cycled through the set (each time the second char is
             * updated until second char reaches 9).
             */

            for(j = 0; j <= i && ++crawler[j] == 9; j++)
            {
                crawler[j] = 0;
            }
        }
        while(j <= i);
    }
    return -1;
}

// Identifies the colour solved on the D layer and assigns c to the opposite colour (to solve the U layer)
char identifyUColour()
{
    if (yellowFace2[0] == 'w')
        return 'y';
    else if (yellowFace2[0] == 'o')
        return 'r';
    else if (yellowFace2[0] == 'g')
        return 'b';
    else if (yellowFace2[0] == 'r')
        return 'o';
    else if (yellowFace2[0] == 'b')
        return 'g';
    else if (yellowFace2[0] == 'y')
        return 'w';

    return 'x'; // Error
}


void secondLayer(int n)
{
    // identifies the colour of the U Face which is to be solved
    char c = identifyUColour();

    int x = 0; //loop variable

    // if the top layer is not solved, control enters loop
    while (!(whiteFace2[0] == c && whiteFace2[1] == c && whiteFace2[2] == c && whiteFace2[3] == c
             && greenFace2[0] == greenFace2[1] && redFace2[0] == redFace2[1] &&
             blueFace2[0] == blueFace2[1] && orangeFace2[0] == orangeFace2[1]))
    {
        // trial2 is OFF
        trial2 = false;

        /* 42 different CLL cases are checked below. */

        // Sune Cases
        if (whiteFace2[2] == c && greenFace2[1] == c && redFace2[1] == c && blueFace2[1] == c)
        {
            if (orangeFace2[0] == whiteFace2[1] && blueFace2[0] == whiteFace2[3])
            {

                switch(n)
                {
                    case 0: R_2();U_2();Ri_2();U_2();R_2();U2_2();Ri_2(); break;
                    case 1: Uinv_2();Fi_2();L_2();U2_2();F2_2();L_2();Fi_2(); break;
                    case 2: break;
                }
            }
            else if (orangeFace2[1] == whiteFace2[3] && redFace2[0] == whiteFace2[1])
            {

                switch(n)
                {
                    case 0: Fi_2();R_2();U2_2();Ri_2();F_2();U2_2();Fi_2();Uinv_2();F2_2(); break;
                    case 1: R_2();U_2();Ri_2();F2_2();U_2();F_2();R_2();U_2();Ri_2(); break;
                    case 2: break;
                }
            }
            else if (orangeFace2[1] == whiteFace2[1] && redFace2[0] == whiteFace2[0])
            {

                switch(n)
                {
                    case 0: R_2();Uinv_2();Ri_2();F_2();Ri_2();Fi_2();R_2(); break;
                    case 1: Fi_2();U_2();R_2();Uinv_2();Ri_2();U_2();F_2();R_2();U_2();Ri_2(); break;
                    case 2: break;
                }
            }
            else if (orangeFace2[1] == whiteFace2[0] && redFace2[0] == whiteFace2[1])
            {

                switch(n)
                {
                    case 0: F_2();Ri_2();Fi_2();R_2();U2_2();R_2();U2_2();Ri_2(); break;
                    case 1: Uinv_2();Ri_2();F_2();R_2();U2_2();R_2();Uinv_2();R2_2();F2_2();R_2();Fi_2(); break;
                    case 2: break;
                }
            }
            else if (orangeFace2[0] == whiteFace2[3] && blueFace2[0] == whiteFace2[0])
            {

                switch(n)
                {
                    case 0: Ri_2();F2_2();R_2();U2_2();R_2();Uinv_2();Ri_2();F_2(); break;
                    case 1: Ri_2();F_2();R2_2();Uinv_2();Ri_2();U_2();R_2();Uinv_2();Ri_2();F_2(); break;
                    case 2: break;
                }
            }
            else if (redFace2[0] == whiteFace2[0] && orangeFace2[0] == whiteFace2[1])
            {

                switch(n)
                {
                    case 0: U2_2();R_2();Uinv_2();R_2();Uinv_2();Ri_2();U_2();
                                Ri_2();Uinv_2();B_2();Uinv_2();Bi_2(); break;
                    case 1: Ri_2();Uinv_2();F_2();R2_2();Uinv_2();R2_2();U2_2();F_2();R_2(); break;
                    case 2: break;
                }
            }
        }

        // Antisune Cases
        else if (whiteFace2[0] == c && greenFace2[0] == c && redFace2[0] == c && blueFace2[0] == c)
        {
            if (orangeFace2[1] == whiteFace2[3] && greenFace2[1] == whiteFace2[1])
            {

                switch(n)
                {
                    case 0: Ri_2();Uinv_2();R_2();Uinv_2();Ri_2();U2_2();R_2(); break;
                    case 1: Uinv_2();B_2();Uinv_2();R2_2();F2_2();Uinv_2();F_2(); break;
                    case 2: break;
                }
            }
            else if (redFace2[1] == whiteFace2[3] && orangeFace2[0] == whiteFace2[1])
            {

                switch(n)
                {
                    case 0: Uinv_2();R2_2();U_2();R_2();U2_2();Li_2();U_2();R2_2();Uinv_2();L_2(); break;
                    case 1: R_2();Uinv_2();F2_2();R_2();U2_2();R_2();Uinv_2();F_2(); break;
                    case 2: break;
                }
            }
            else if (redFace2[1] == whiteFace2[2] && orangeFace2[0] == whiteFace2[3])
            {

                switch(n)
                {
                    case 0: Ri_2();U_2();L_2();Uinv_2();R_2();U_2();Li_2(); break;
                    case 1: R_2();Uinv_2();Ri_2();Fi_2();Uinv_2();R_2();U_2();Ri_2();Uinv_2();F_2(); break;
                    case 2: break;
                }
            }
            else if (redFace2[1] == whiteFace2[3] && orangeFace2[0] == whiteFace2[2])
            {

                switch(n)
                {
                    case 0: Bi_2();R_2();B_2();Ri_2();U2_2();Ri_2();U2_2();R_2(); break;
                    case 1: R_2();U2_2();Ri_2();F2_2();U_2();Fi_2();U2_2();Fi_2(); break;
                    case 2: break;
                }
            }
            else if (orangeFace2[0] == whiteFace2[3] && orangeFace2[1] == whiteFace2[1])
            {

                switch(n)
                {
                    case 0: U2_2();R_2();U2_2();Ri_2();U2_2();Ri_2();F_2();R_2();Fi_2(); break;
                    case 1: Ri_2();U_2();F_2();R_2();F_2();U2_2();Ri_2();F_2();Uinv_2();F2_2(); break;
                    case 2: break;
                }
            }
            else if (orangeFace2[0] == whiteFace2[1] && orangeFace2[1] == whiteFace2[3])
            {

                switch(n)
                {
                    case 0: R2_2();F_2();R_2();U2_2();R_2();Uinv_2();Ri_2();U2_2();Fi_2();R_2(); break;
                    case 1: U_2();F2_2();U_2();Ri_2();U_2();Ri_2();U_2();Fi_2();R2_2(); break;
                    case 2: break;
                }
            }
        }

        // L Case
        else if (whiteFace2[0] == c && greenFace2[0] == c && redFace2[1] == c && whiteFace2[3] == c)
        {
            if (greenFace2[1] == whiteFace2[1] && orangeFace2[0] == whiteFace2[2])
            {

                switch(n)
                {
                    case 0: F_2();Ri_2();Fi_2();R_2();U_2();R_2();Uinv_2();Ri_2(); break;
                    case 1: U_2();Ri_2();F2_2();Ri_2();Fi_2();R_2();F2_2();Ri_2();D_2();R2_2(); break;
                    case 2: break;
                }
            }
            else if (blueFace2[1] == whiteFace2[1] && redFace2[0] == whiteFace2[2])
            {

                switch(n)
                {
                    case 0: F_2();R_2();Uinv_2();Ri_2();Uinv_2();R_2();U_2();Ri_2();Fi_2(); break;
                    case 1: R_2();Uinv_2();Ri_2();U_2();R_2();Uinv_2();R2_2();Fi_2();R_2();F_2(); break;
                    case 2: break;
                }
            }
            else if (blueFace2[1] == whiteFace2[1] && orangeFace2[0] == whiteFace2[2])
            {

                switch(n)
                {
                    case 0: U_2();R2_2();Uinv_2();R_2();U2_2();Ri_2();U2_2();R_2();Uinv_2();R2_2(); break;
                    case 1: Ri_2();F_2();R2_2();U_2();Ri_2();Fi_2();R_2();U2_2();Ri_2(); break;
                    case 2: break;
                }
            }
            else if (greenFace2[1] == whiteFace2[1] && redFace2[0] == whiteFace2[2])
            {

                switch(n)
                {
                    case 0: R_2();U2_2();R2_2();F_2();R_2();Fi_2();R_2();U2_2();Ri_2(); break;
                    case 1: Ri_2();U_2();R2_2();Uinv_2();R2_2();Uinv_2();F_2();R2_2();Uinv_2();Ri_2(); break;
                    case 2: break;
                }
            }
            else if (whiteFace2[2] == whiteFace2[1] && greenFace2[1] == orangeFace2[1])
            {

                switch(n)
                {
                    case 0: U_2();Ri_2();F2_2();R_2();U_2();F2_2();U_2();F_2();Uinv_2();F2_2(); break;
                    case 1: R_2();Uinv_2();Ri_2();Fi_2();U2_2();Fi_2();U_2();F2_2(); break;
                    case 2: break;
                }
            }
            else if (whiteFace2[2] == whiteFace2[1] && greenFace2[1] == orangeFace2[0])
            {

                switch(n)
                {
                    case 0: R_2();U2_2();Ri_2();Uinv_2();F2_2();Uinv_2();Fi_2();U_2();F2_2(); break;
                    case 1: U_2();Li_2();U_2();L_2();F_2();U2_2();F_2();Uinv_2();F2_2(); break;
                    case 2: break;
                }
            }
        }

        //  Chameleon Case
        if (whiteFace2[1] == c && greenFace2[0] == c && blueFace2[1] == c && whiteFace2[3] == c)
        {
            if (redFace2[0] == redFace2[1] && orangeFace2[0] == orangeFace2[1])
            {

                switch(n)
                {
                    case 0: U_2();Ri_2();U_2();R_2();U2_2();R2_2();F_2();R_2();Fi_2();R_2(); break;
                    case 1: Uinv_2();R_2();Uinv_2();Ri_2();U2_2();F_2();R_2();U2_2();Ri_2();F_2(); break;
                    case 2: break;
                }
            }
            else if (blueFace2[0] == greenFace2[1] && orangeFace2[0] == orangeFace2[1])
            {

                switch(n)
                {
                    case 0: U_2();F_2();Uinv_2();R_2();U2_2();Ri_2();Uinv_2();F2_2();R_2();U_2();Ri_2(); break;
                    case 1: U2_2();R_2();Uinv_2();R2_2();F_2();R_2();U_2();R_2();U2_2();Ri_2(); break;
                    case 2: break;
                }
            }
            else if (redFace2[1] == whiteFace2[0] && blueFace2[0] == whiteFace2[2])
            {

                switch(n)
                {
                    case 0: F_2();R_2();Fi_2();R_2();U_2();Ri_2();Uinv_2();Ri_2(); break;
                    case 1: R2_2();Fi_2();U_2();F_2();U2_2();F_2();Uinv_2();Ri_2(); break;
                    case 2: break;
                }
            }
            else if (redFace2[0] == whiteFace2[2] && greenFace2[1] == whiteFace2[0])
            {

                switch(n)
                {
                    case 0: R_2();U_2();Ri_2();Uinv_2();Ri_2();F_2();R_2();Fi_2(); break;
                    case 1: U2_2();R2_2();U_2();R_2();Uinv_2();R2_2();F_2();R_2();U2_2();Ri_2();F_2(); break;
                    case 2: break;
                }
            }
            else if (whiteFace2[2] == whiteFace2[0] && redFace2[0] == redFace2[1])
            {

                switch(n)
                {
                    case 4: U2_2();Ri_2();U_2();Ri_2();F_2();Uinv_2();R_2();U_2();F2_2();R2_2(); break;
                    case 1: R2_2();B2_2();Uinv_2();Ri_2();Uinv_2();R_2();Uinv_2();Ri_2();U_2();Ri_2(); break;
                    case 2: break;
                }
            }
            else if (whiteFace2[2] == whiteFace2[0] && blueFace2[0] == greenFace2[1])
            {

                switch(n)
                {
                    case 0: U2_2();Ri_2();U2_2();Ri_2();F2_2();R_2();F2_2();Ri_2();F2_2();R2_2(); break;
                    case 1: U2_2();R_2();U_2();Li_2();Ri_2();Uinv_2();R_2();U_2();Ri_2();Uinv_2();L_2(); break;
                    case 2: break;
                }
            }
        }

        //  T Case
        else if (whiteFace2[1] == c && orangeFace2[0] == c && orangeFace2[1] == c && whiteFace2[3] == c)
        {
            if (redFace2[0] == redFace2[1] && blueFace2[1] == greenFace2[0])
            {

                switch(n)
                {
                    case 0: Uinv_2();R2_2();F2_2();R_2();U_2();Ri_2();F_2();Uinv_2();R_2();U_2();R2_2(); break;
                    case 1: U2_2();Fi_2();R2_2();Fi_2();R2_2();Fi_2();Uinv_2();F2_2();R2_2(); break;
                    case 2: break;
                }
            }
            else if (redFace2[1] == whiteFace2[2] && redFace2[0] == whiteFace2[0])
            {

                switch(n)
                {
                    case 0: U_2();R_2();Fi_2();R_2();Fi_2();Ri_2();F_2();Li_2();Fi_2();L_2(); break;
                    case 1: U2_2();Ri_2();F_2();R_2();Fi_2();Ri_2();F_2();R2_2();Uinv_2();Ri_2(); break;
                    case 2: break;
                }
            }
            else if (greenFace2[1] == whiteFace2[2] && redFace2[0] == whiteFace2[0])
            {

                switch(n)
                {
                    case 0: Uinv_2();R2_2();U_2();Ri_2();Uinv_2();R2_2();Uinv_2();Fi_2();U2_2();F_2(); break;
                    case 1: Uinv_2();Ri_2();F_2();R2_2();Uinv_2();Ri_2();U_2();F_2();U_2();Fi_2(); break;
                    case 2: break;
                }
            }
            else if (redFace2[1] == whiteFace2[2] && blueFace2[0] == whiteFace2[0])
            {

                switch(n)
                {
                    case 0: Uinv_2();R_2();U2_2();Ri_2();U_2();Ri_2();F2_2();R_2();Fi_2();Ri_2();F2_2();R_2(); break;
                    case 1: U_2();F_2();Uinv_2();Ri_2();F2_2();R_2();Fi_2();U2_2();Fi_2(); break;
                    case 2: break;
                }
            }
            else if (whiteFace2[2] == whiteFace2[0] && redFace2[0] == redFace2[1])
            {

                switch(n)
                {
                    case 0: U2_2();R_2();F_2();R_2();Fi_2();U2_2();Ri_2();F_2();Ri_2();Fi_2();R_2(); break;
                    case 1: U_2();Fi_2();U2_2();R_2();U2_2();Ri_2();U2_2();F_2(); break;
                    case 2: break;
                }
            }
            else if (whiteFace2[2] == whiteFace2[0] && blueFace2[0] == greenFace2[1])
            {

                switch(n)
                {
                    case 0: F_2();R_2();U_2();Ri_2();Uinv_2();Fi_2(); break;
                    case 1: R_2();U_2();Ri_2();U_2();R_2();U_2();R2_2();F_2();R2_2();Uinv_2();Ri_2(); break;
                    case 2: break;
                }
            }
        }

        //  Pi Case
        else if (blueFace2[0] == c && orangeFace2[0] == c && orangeFace2[1] == c && greenFace2[1] == c)
        {
            if (whiteFace2[1] == whiteFace2[3] && blueFace2[1] == greenFace2[0])
            {

                switch(n)
                {
                    case 0: F_2();R_2();U_2();Ri_2();Uinv_2();R_2();U_2();Ri_2();Uinv_2();Fi_2(); break;
                    case 1: Uinv_2();F_2();R_2();F2_2();R_2();F2_2();U2_2();Ri_2();Fi_2(); break;
                    case 2: break;
                }
            }
            else if (whiteFace2[0] == whiteFace2[2] && redFace2[0] == redFace2[1])
            {

                switch(n)
                {
                    case 0: Ri_2();Fi_2();Uinv_2();F_2();Uinv_2();R_2();U_2();Ri_2();U_2();R_2(); break;
                    case 1: Uinv_2();Ri_2();F_2();R2_2();Uinv_2();R2_2();F_2();R_2(); break;
                    case 2: break;
                }
            }
            else if (whiteFace2[0] == whiteFace2[3] && whiteFace2[1] == blueFace2[1])
            {

                switch(n)
                {
                    case 0: Ri_2();F2_2();R_2();Fi_2();U2_2();R_2();Uinv_2();Ri_2();Uinv_2();F_2(); break;
                    case 1: F_2();R_2();Uinv_2();Ri_2();F_2();R_2();U2_2();Ri_2();U_2();Fi_2(); break;
                    case 2: break;
                }
            }
            else if (whiteFace2[1] == whiteFace2[2] && whiteFace2[3] == greenFace2[0])
            {

                switch(n)
                {
                    case 0: R_2();U2_2();Ri_2();Uinv_2();R_2();U_2();Ri_2();U2_2();Ri_2();F_2();R_2();Fi_2(); break;
                    case 1: Ri_2();Uinv_2();Ri_2();F2_2();Uinv_2();R_2();U2_2();F2_2();R_2(); break;
                    case 2: break;
                }
            }
            else if (whiteFace2[2] == whiteFace2[0] && whiteFace2[1] == whiteFace2[3])
            {

                switch(n)
                {
                    case 0: R_2();Uinv_2();Ri_2();F_2();Ri_2();F_2();R_2();U_2();Ri_2();F_2();R_2(); break;
                    case 1: Uinv_2();F_2();Ri_2();F_2();Uinv_2();F2_2();R_2();U_2();R_2(); break;
                    case 2: break;
                }
            }
            else if (whiteFace2[3] == whiteFace2[0] && whiteFace2[1] == whiteFace2[2])
            {

                switch(n)
                {
                    case 0: Uinv_2();R_2();Uinv_2();R_2();Uinv_2();Ri_2();U_2();Ri_2();F_2();R2_2();Fi_2(); break;
                    case 1: Fi_2();R_2();Uinv_2();Ri_2();U_2();Fi_2();U2_2();Fi_2(); break;
                    case 2: break;
                }
            }
        }

        //  H Case
        else if (blueFace2[0] == c && greenFace2[0] == c && blueFace2[1] == c && greenFace2[1] == c)
        {
            if (whiteFace2[1] == whiteFace2[3] && whiteFace2[0] == redFace2[0])
            {

                switch(n)
                {
                    case 0: Ri_2();U2_2();R_2();Bi_2();U_2();Bi_2();Uinv_2();B_2();Uinv_2();B_2(); break;
                    case 1: R_2();U_2();Ri_2();Fi_2();R_2();U_2();Ri_2();Uinv_2();R_2();U_2();Ri_2(); break;
                    case 2: break;
                }
            }
            else if (whiteFace2[0] == whiteFace2[1] && whiteFace2[2] == redFace2[1])
            {

                switch(n)
                {
                    case 0: U_2();R_2();U_2();Ri_2();U_2();R_2();U_2();Ri_2();F_2();Ri_2();Fi_2();R_2(); break;
                    case 1: U_2();Ri_2();Uinv_2();Ri_2();F2_2();U_2();Fi_2();R_2();Fi_2(); break;
                    case 2: break;
                }
            }
            else if (whiteFace2[2] == whiteFace2[0] && whiteFace2[1] == whiteFace2[3])
            {

                switch(n)
                {
                    case 0: R2_2();U2_2();R_2();U2_2();R2_2();break;
                    case 1: Ri_2();F_2();R2_2();Uinv_2();R2_2();Uinv_2();F_2();U_2();R_2(); break;
                    case 2: break;
                }
            }
            else if (whiteFace2[1] == whiteFace2[0] && whiteFace2[2] == whiteFace2[3])
            {

                switch(n)
                {
                    case 0: B2_2();R_2();B2_2();R2_2();U2_2();R_2();B2_2(); break;
                    case 1: Fi_2();U_2();R_2();Uinv_2();R2_2();F2_2();R_2();Uinv_2();F_2(); break;
                    case 2: break;
                }
            }
        }

        // Solved cases (Only Perm)
        else if (whiteFace2[0] == c && whiteFace2[1] == c && whiteFace2[2] == c && whiteFace2[3] == c)
        {
            if (greenFace2[0] == greenFace2[1] && orangeFace2[0] == redFace2[1])
            {

                switch(n)
                {
                    case 0: Ri_2();U_2();Ri_2();F2_2();R_2();Fi_2();Ri_2();F2_2();R2_2(); break;
                    case 1: U2_2();R2_2();Uinv_2();R2_2();U2_2();F2_2();Uinv_2();R2_2(); break;
                    case 2: break;
                }
            }
            else if (greenFace2[0] == blueFace2[1] && greenFace2[1] == blueFace2[0])
            {

                switch(n)
                {
                    case 0: R_2();Uinv_2();Ri_2();Uinv_2();F2_2();Uinv_2();R_2();U_2();Ri_2();D_2();R2_2(); break;
                    case 1: Ri_2();F_2();Uinv_2();R2_2();U_2();Fi_2();R_2(); break;
                    case 2: break;
                }
            }
        }
        U_2(); // tries alg from different angles to match it
        x++;
        if (x > 4)
            return; // This is important as it returns control if CLL is unsolvable (invalid input)
    }
}

// Solves AUF (Adjust U Face) - only one move - aligns U layer to match with the rest of the cube
void auf2()
{
    // 3 possible cases are tested below
    if (greenFace2[1] == redFace2[2])
        Uinv_2();
    else if (greenFace2[1] == blueFace2[2])
        U2_2();
    else if (greenFace2[1] == orangeFace2[2])
        U_2();

    // This block is the main error checker. If the cube is not solvable, it clears the solutionList2 and appends error message
    if (!(greenFace2[0] == greenFace2[2] && redFace2[0] == redFace2[2] && blueFace2[0] ==  blueFace2[2]
          && orangeFace2[0] == orangeFace2[2]))
    {
        solutionList2.clear();
        solutionList2.append("ERROR");
    }
}

void solveCube2x2()
{
    // Everything is cleared and kept empty to store the solution2
    solutionList2.clear();
    solution2 = "";
    solution2_short = "";
    moveCount2 = 0;
    moveCount2_short = 0;

    // executes first layer
    int DPerm = firstLayer();

    solutionList2.append("trash");

    // executes second layer
    secondLayer(DPerm);

    // adjust U face (only 1 move)
    auf2();

    // if cube is unsolvable, returns a message to mainwindow.cpp
    if (solutionList2[0] == "ERROR")
    {
        solution2 = "No solution possible. Please retry with proper scramble/colours.";
        moveCount2 = 0;
        return;
    }

    // stores the list as a string with each element separated by a space
    solution2 = solutionList2.join(" ");

    // create a temp list which stores different parts of the solution2, each, as an element
    QStringList solutionList2_temp = solution2.split("trash");

    // create sub-lists which take solutionList2_temp and store each of its element as a separate list which contains
    // each element as a separate move (similar to solutionList2, only difference being, firstLayer list stores only the
    // solution2 for first layer and lastLayer stores solution2 for last layer
    QStringList firstLayer = solutionList2_temp[0].split(" "), lastLayer = solutionList2_temp[1].split(" ");

    // shortens each list by merging moves like L L2, etc. Any number can be used instead of 10
    // That number signifies how many times the solution2 is shortened
    // Ex: U2 L L2 L U -> U2 U -> U'
    for (int i = 0; i < 10; i++)
    {
        firstLayer = shortSolution(firstLayer);
        lastLayer = shortSolution(lastLayer);
    }

    // solution2 string stores the entire solution2, formatted neatly and displays the solution2 in different steps
    solution2 = "1st Layer: " + firstLayer.join(" ") + '\n';
    switch (DPerm)
    {
        case 4: solution2 += "CLL: "; break;
        case 1: solution2 += "EG1: "; break;
        default: solution2 += "CLL: "; break;
    }
    solution2 += lastLayer.join(" ");

    // this string is the raw concatenation of the cross, f2l1.. pll string
    QString solution2_full = firstLayer.join(" ") + lastLayer.join(" ");

    // the above string is used to find moveCount2
    moveCount2 = findMoveCount(solution2_full);

    // shortens the solution2 multiple times (20 is not required. Can be any number >= 1 )
    for (int i = 0; i < 20; i++)
        solutionList2 = shortSolution(solutionList2);

    // joins all elements (moves) of the solutionList2 to create a string
    solution2_short = solutionList2.join(" ");

    // the string is then used to find the reduced moveCount2
    moveCount2_short = findMoveCount(solution2_short);
}
