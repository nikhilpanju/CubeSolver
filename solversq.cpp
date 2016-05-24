#include <QApplication>
#include <QString>
#include <QStringList>
#include "solversq.h"
#include "sq1.h"

/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Variable Declarations //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// gui variables
extern QStringList uF_gui, dF_gui, uL_gui, dL_gui;

// scramble variable
extern QString scrambleSQ;

// current state variables
QStringList uF, uL, dF, dL;

// checkpoint variables
QStringList uF_cp, uL_cp, dF_cp, dL_cp;

// variable to store pbl like J/N, solved/J, etc
QStringList perms;

// solution variable
QStringList solutionListSQ;
QString solutionSQ;
QString solutionSQ_short;

// trial variable
bool trialSQ;

// moveCount variables
int moveCountSQ, moveCountSQ_short;

/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CubeSolver Implementation /////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


int possibleNRotate(QStringList list, int n)
{
    if (n > 6)
        return possibleNRotatei(list, 12 - n);
    else if (n < 0)
        return possibleNRotatei(list, -n);

    int m = 0, p = 0, x = 0, y = 0;

    foreach(QString string, list)
    {
        if (string[1] == '1')
            m += 1;
        else if (string[1] == '2')
            m += 2;
        if (m == 6)
            break;
        p++;
    }

    for (int i = 0; i <= p; i++)
    {
        if (x < n)
        {
            QString temp1 = list[p - i];
            x += temp1[1].digitValue();
        }
        if (x == n)
            x = n;
        else if (x > n)
            return 0;

        if (y < n)
        {
            QString temp2 = list[list.length() - 1 - i];
            y += temp2[1].digitValue();
        }
        if (y == n)
            y = n;
        else if (y > n)
            return 0;
    }
    return 1;
}
int possibleNRotatei(QStringList list, int n)
{
    //if (n > 6)
        //return possibleNRotate(list, 12 - n);

    int m = 0, p = 0, x = 0, y = 0;

    foreach(QString string, list)
    {
        if (string[1] == '1')
            m += 1;
        else if (string[1] == '2')
            m += 2;
        if (m == 6)
            break;
        p++;
    }

    for (int i = 0; i <= p; i++)
    {



        if (x < n)
        {
            QString temp1 = list[p + 1 + i];
            x += temp1[1].digitValue();
        }
        if (x == n)
            x = n;
        else if (x > n)
            return 0;

        if (y < n)
        {
            QString temp2 = list[i];
            y += temp2[1].digitValue();
        }
        if (y == n)
            y = n;
        else if (y > n)
            return 0;
    }
    return 1;
}

void createCheckpointSQ()
{
    uF_cp = uF;
    uL_cp = uL;
    dF_cp = dF;
    dL_cp = dL;
}
void resetLocationSQ()
{
    uF = uF_cp;
    uL = uL_cp;
    dF = dF_cp;
    dL = dL_cp;
}

void U(int n)
{
    if (n == 0)
    {
        if (trialSQ == false)
            solutionListSQ << "(0";
        return;
    }
    if (n > 6)
    {
        Uinv(12 - n);
        return;
    }
    if (!(possibleNRotate(uF, n)))
        return;

    int m = 0, j = 0;
    for (int i = uF.length() - 1; i >= 0; i--)
    {
        if (uF[i][1] == '1')
            m += 1;
        else if (uF[i][1] == '2')
            m += 2;

        j++;

        if (m == n)
            break;
    }

    for (int i = 0; i < j; i++)
    {
        // moves the last element of each variable to the beginning (Cw movement)
        uF.move(uF.length() - 1, 0);
    }
    for (int i = 0; i < n; i++)
    {
        // moves the last element of each variable to the beginning (Cw movement)
        uL.move(uL.length() - 1, 0);
    }

    if (trialSQ == false)
        solutionListSQ << ("(" + QString::number(n,10));
}

void Uinv(int n)
{
    if (n == 0)
    {
        if (trialSQ == false)
            solutionListSQ << "(0";
        return;
    }
    if (n > 5)
    {
        U(12 - n);
        return;
    }

    if (!(possibleNRotatei(uF, n)))
        return;

    int m = 0, j = 0;
    for (int i = 0; i < uF.length(); i++)
    {
        if (uF[i][1] == '1')
            m += 1;
        else if (uF[i][1] == '2')
            m += 2;

        j++;

        if (m == n)
            break;
    }

    for (int i = 0; i < j; i++)
    {
        // moves the last element of each variable to the beginning (Cw movement)
        uF.move(0, uF.length() - 1);
    }
    for (int i = 0; i < n; i++)
    {
        // moves the last element of each variable to the beginning (Cw movement)
        uL.move(0, uL.length() - 1);
    }

    if (trialSQ == false)
        solutionListSQ << ("(-" + QString::number(n,10));
}

void D(int n)
{
    if (n == 0)
    {
        if (trialSQ == false)
            solutionListSQ[solutionListSQ.length() - 1] += ", 0)";
       return;
    }

    if (n > 6)
    {
        Di(12 - n);
        return;
    }

    if (!(possibleNRotate(dF, n)))
        return;

    int m = 0, j = 0;
    for (int i = dF.length() - 1; i >= 0; i--)
    {
        if (dF[i][1] == '1')
            m += 1;
        else if (dF[i][1] == '2')
            m += 2;

        j++;

        if (m == n)
            break;
    }

    for (int i = 0; i < j; i++)
    {
        // moves the last element of each variable to the beginning (Cw movement)
        dF.move(dF.length() - 1, 0);
    }
    for (int i = 0; i < n; i++)
    {
        // moves the last element of each variable to the beginning (Cw movement)
        dL.move(dL.length() - 1, 0);
    }

    if (trialSQ == false)
        solutionListSQ[solutionListSQ.length() - 1] += (", " + QString::number(n,10) + ")");
}
void Di(int n)
{
    if (n == 0)
    {
        if (trialSQ == false)
            solutionListSQ[solutionListSQ.length() - 1] += ", 0)";
        return;
    }
    if (n > 5)
    {
        D(12 - n);
        return;
    }

    if (!(possibleNRotatei(dF, n)))
        return;

    int m = 0, j = 0;
    for (int i = 0; i < dF.length(); i++)
    {
        if (dF[i][1] == '1')
            m += 1;
        else if (dF[i][1] == '2')
            m += 2;

        j++;

        if (m == n)
            break;
    }

    for (int i = 0; i < j; i++)
    {
        // moves the last element of each variable to the beginning (Cw movement)
        dF.move(0, dF.length() - 1);
    }
    for (int i = 0; i < n; i++)
    {
        // moves the last element of each variable to the beginning (Cw movement)
        dL.move(0, dL.length() - 1);
    }

    if (trialSQ == false)
        solutionListSQ[solutionListSQ.length() - 1] += (", -" + QString::number(n,10) + ")");
}
void S()
{
    int m = 0, j = 0, k = 0;
    QStringList temp;
    for (int i = 0; i < uF.length(); i++)
    {
        if (uF[i][1] == '1')
            m += 1;
        else if (uF[i][1] == '2')
            m += 2;

        j++;

        if (m == 6)
            break;
    }

    m = 0;

    for (int i = 0; i < dF.length(); i++)
    {
        if (dF[i][1] == '1')
            m += 1;
        else if (dF[i][1] == '2')
            m += 2;

        k++;

        if (m == 6)
            break;
    }
    for (int i = 0; i < j; i++)
        temp.append(uF.takeFirst());

    for (int i = k - 1; i >= 0; i--)
        uF.prepend(dF[i]);

    for (int i = k - 1; i >= 0; i--)
        dF.takeFirst();

    for (int i = j - 1; i >= 0; i--)
        dF.prepend(temp[i]);

    temp.clear();

    for (int i = 0; i < 6; i++)
        temp.append(uL.takeFirst());

    for (int i = 5; i >= 0; i--)
        uL.prepend(dL[i]);

    for (int i = 5; i >= 0; i--)
        dL.takeFirst();

    for (int i = 5; i >= 0; i--)
        dL.prepend(temp[i]);

    if (trialSQ == false)
        solutionListSQ << ("/");

}

void convertString(QString &scram, int gui)
{
    scram += "trash";

    for (int i = 0; i < scram.length() - 3; i++)
    {
        if (scram[i] == '(')
        {
            if (scram[i + 1] == '-')
                Uinv(scram[i + 2].digitValue());

            else
                U(scram[i + 1].digitValue());
        }
        else if (scram[i] == ' ' && scram[i - 1] == ',')
        {
            if (scram[i + 1] == '-')
                Di(scram[i + 2].digitValue());

            else
                D(scram[i + 1].digitValue());
        }
        else if (scram[i] == '/')
            S();
    }
    scram.chop(5);

    /* assign "_hui" variables the current scrambled state so that it can be viewed
     * using the "View Scramble" button. Actual usage in scrambledialog.cpp
     */

    if (gui == 1)
    {
        uF_gui = uF;
        dF_gui = dF;
        uL_gui = uL;
        dL_gui = dL;
    }

}

void cubeShape()
{
    createCheckpointSQ();

    trialSQ = true;

    QString uf = uF.join("");
    QString df = dF.join("");

    int u = 0, d = 0, m = 0, n = 0, x = 0;
    int u1 = 0, d1 = 0, u2 = 0, d2 = 0;

    for (int i = 1; i < uf.length(); i += 2)
        m += uf[i].digitValue();
    for (int i = 1; i < df.length(); i += 2)
        n += df[i].digitValue();


    while (true)
    {
        trialSQ = false;

        // if no. of blocks in top layer is 8 and bottom layer is 8
        if (uF.length() == 8 && dF.length() == 8)
        {
            /////// Depth 0 ////////

            // Square/Square
            if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                    uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '1' &&
                    dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '2' &&
                    dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                break;
            }

            //////// Depth 1 //////////

            // Kite/Kite
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '1' && uF[3][1] == '2' &&
                    uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '1' &&
                    dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '1' &&
                    dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/";
                convertString(s);
                break;
            }

            //////// Depth 2 /////////

            // Barrel/Barrel
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '2' && uF[3][1] == '1' &&
                    uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '2' && uF[7][1] == '1' &&
                    dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '1' && dF[3][1] == '2' &&
                    dF[4][1] == '2' && dF[5][1] == '1' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-3, -3)/";
                convertString(s);
                break;
            }
            // FistR/FistR
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                    uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '1' && uF[7][1] == '2' &&
                    dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '2' && dF[3][1] == '1' &&
                    dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(3, 0)/";
                convertString(s);
                break;
            }
            // FistL/FistL
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '2' && uF[3][1] == '1' &&
                 uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '2' &&
                 dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '1' &&
                 dF[4][1] == '2' && dF[5][1] == '1' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "";
                convertString(s);
                break;
            }

            ///////// Depth 3 //////////

            // Shield/Square
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '1' && uF[3][1] == '2' &&
                    uF[4][1] == '1' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '2' &&
                    dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '2' &&
                    dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-1, 0)/(-3, 0)/";
                convertString(s);
                break;
            }
            // Square/Shield
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '1' &&
                    dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '1' && dF[3][1] == '2' &&
                    dF[4][1] == '2' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(0, 1)/(0, 3)/";
                convertString(s);
                break;
            }
            // Muffin/Square
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '2' && uF[3][1] == '1' &&
                 uF[4][1] == '1' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '2' &&
                 dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '2' &&
                 dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(2, 0)/(3, 0)/";
                convertString(s);
                break;
            }
            // Square/Muffin
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                 uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '1' &&
                 dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '2' && dF[3][1] == '1' &&
                 dF[4][1] == '2' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(0, -2)/(0, -3)/";
                convertString(s);
                break;
            }
            // Barrel/Kite
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '1' && uF[3][1] == '2' &&
                     uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '1' && uF[7][1] == '2' &&
                     dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '1' &&
                     dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-3, 0)/(-3, 0)/";
                convertString(s);
                break;
            }
            // Kite/Barrel
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '1' && uF[3][1] == '2' &&
                     uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '1' &&
                     dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '1' && dF[3][1] == '2' &&
                     dF[4][1] == '2' && dF[5][1] == '1' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(0, 3)/(0, 3)/";
                convertString(s);
                break;
            }
            // Scallop/Kite
            else if (uF[0][1] == '2' && uF[1][1] == '2' && uF[2][1] == '1' && uF[3][1] == '1' &&
                     uF[4][1] == '1' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '2' &&
                     dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '2' &&
                     dF[4][1] == '2' && dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-1, -2)/(-3, 0)/";
                convertString(s);
                break;
            }
            // Kite/Scallop
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '2' &&
                     dF[0][1] == '1' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '2' &&
                     dF[4][1] == '2' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-1, -2)/(0, -3)/";
                convertString(s);
                break;
            }
            // Scallop/Scallop
            else if (uF[0][1] == '1' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '2' &&
                     uF[4][1] == '2' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '1' &&
                     dF[0][1] == '2' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '1' &&
                     dF[4][1] == '1' && dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(1, 2)/(-3, -3)/";
                convertString(s);
                break;
            }
            // Shield/Shield
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '1' && uF[3][1] == '2' &&
                     uF[4][1] == '2' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '1' &&
                     dF[0][1] == '2' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '1' &&
                     dF[4][1] == '2' && dF[5][1] == '1' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(1, 0)/(-3, -3)/";
                convertString(s);
                break;
            }
            // Muffin/Muffin
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '1' &&
                     dF[0][1] == '2' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '1' &&
                     dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '2' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-2, 0)/(3, 3)/";
                convertString(s);
                break;
            }
            // PawL/PawL
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '1' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '2' &&
                     dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '2' &&
                     dF[4][1] == '2' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-1, 4)/(-3, 0)/";
                convertString(s);
                break;
            }
            // PawR/PawR
            else if (uF[0][1] == '2' && uF[1][1] == '2' && uF[2][1] == '1' && uF[3][1] == '1' &&
                     uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '2' &&
                     dF[0][1] == '1' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '2' &&
                     dF[4][1] == '2' && dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(2, -5)/(0, 3)/";
                convertString(s);
                break;
            }

            ////////// Depth 6 //////////

            // Barrel/Square
            else if (uF[0][1] == '2' && uF[1][1] == '2' && uF[2][1] == '1' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '1' &&
                     dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '2' &&
                     dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(2, 2)/(0, -1)/(2, 2)/(-1, 0)/(-3, -3)/";
                convertString(s);
                break;
            }
            // Square/Barrel
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '1' &&
                     dF[0][1] == '1' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '2' &&
                     dF[4][1] == '1' && dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-2, -2)/(1, 0)/(-2, -2)/(0, 1)/(3, 3)/";
                convertString(s);
                break;
            }
            // FistL/Square
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '1' &&
                     dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '2' &&
                     dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(2, 0)/(0, -1)/(-2, 0)/(1, 0)/(3, 0)/(-1, 1)";
                convertString(s);
                break;
            }
            // Square/FistL
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '1' &&
                     dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '2' &&
                     dF[4][1] == '1' && dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(0, -2)/(1, 0)/(0, 2)/(0, -1)/(0, -3)/(-1, 1)";
                convertString(s);
                break;
            }
            // FistR/Square
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '1' && uF[3][1] == '2' &&
                     uF[4][1] == '1' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '2' &&
                     dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '1' &&
                     dF[4][1] == '2' && dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-2, 0)/(0, 1)/(2, 0)/(-1, 0)/(-3, 0)/";
                convertString(s);
                break;
            }
            // Square/FistR
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '1' && uF[3][1] == '2' &&
                     uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '2' &&
                     dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '1' &&
                     dF[4][1] == '2' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(0, 2)/(-1, 0)/(0, -2)/(0, 1)/(0, 3)/";
                convertString(s);
                break;
            }
            // Muffin/Kite
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '1' &&
                     dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '1' && dF[3][1] == '2' &&
                     dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '2' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(2, -3)/(2, 0)/(-2, 0)/(1, 0)/(-3, -3)/";
                convertString(s);
                break;
            }
            // Kite/Muffin
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '1' && uF[3][1] == '2' &&
                     uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '2' && uF[7][1] == '1' &&
                     dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '2' && dF[3][1] == '1' &&
                     dF[4][1] == '1' && dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(3, -2)/(0, -2)/(0, 2)/(0, -1)/(3, 3)/";
                convertString(s);
                break;
            }
            // FistR/Kite
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '1' && uF[3][1] == '2' &&
                     uF[4][1] == '1' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '2' &&
                     dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '1' &&
                     dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-2, 0)/(0, -1)/(2, 0)/(-1, -2)/(-3, 0)/";
                convertString(s);
                break;
            }
            // Kite/FistR
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '1' && uF[3][1] == '2' &&
                     uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '1' &&
                     dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '1' &&
                     dF[4][1] == '2' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(0, 2)/(1, 0)/(0, -2)/(2, 1)/(0, 3)/";
                convertString(s);
                break;
            }
            // FistL/Kite
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '1' &&
                     dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '2' &&
                     dF[4][1] == '2' && dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(2, 0)/(0, 1)/(-2, 0)/(1, 2)/(3, 0)/(-1, 1)";
                convertString(s);
                break;
            }
            // Kite/FistL
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '2' &&
                     dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '2' &&
                     dF[4][1] == '1' && dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(0, -2)/(-1, 0)/(0, 2)/(-2, -1)/(0, -3)/(-1, 1)";
                convertString(s);
                break;
            }
            // Muffin/Barrel
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '1' &&
                     dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '1' && dF[3][1] == '2' &&
                     dF[4][1] == '2' && dF[5][1] == '1' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(2, -3)/(-2, 0)/(2, 0)/(-1, 0)/(-3, 0)/";
                convertString(s);
                break;
            }
            // Barrel/Muffin
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '1' && uF[3][1] == '2' &&
                     uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '1' && uF[7][1] == '2' &&
                     dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '2' && dF[3][1] == '1' &&
                     dF[4][1] == '1' && dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(3, -2)/(0, 2)/(0, -2)/(0, 1)/(0, 3)/";
                convertString(s);
                break;
            }
            // FistR/Barrel
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '1' &&
                     dF[0][1] == '1' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '2' &&
                     dF[4][1] == '1' && dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-2, 0)/(-1, 0)/(2, 0)/(-2, -1)/(3, 3)/";
                convertString(s);
                break;
            }
            // Barrel/FistR
            else if (uF[0][1] == '2' && uF[1][1] == '2' && uF[2][1] == '1' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '1' &&
                     dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '2' && dF[3][1] == '1' &&
                     dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(0, 2)/(0, 1)/(0, -2)/(1, 2)/(-3, -3)/";
                convertString(s);
                break;
            }
            // FistL/Barrel
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '2' &&
                     dF[0][1] == '2' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '1' &&
                     dF[4][1] == '2' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(2, 0)/(1, 0)/(-2, 0)/(2, 1)/(3, 3)/";
                convertString(s);
                break;
            }
            // Barrel/FistL
            else if (uF[0][1] == '1' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '2' &&
                     uF[4][1] == '1' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '2' &&
                     dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '2' && dF[3][1] == '1' &&
                     dF[4][1] == '2' && dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(0, -2)/(0, -1)/(0, 2)/(-1, -2)/(-3, -3)/";
                convertString(s);
                break;
            }
            // FistR/Muffin
            else if (uF[0][1] == '1' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '2' &&
                     uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '2' &&
                     dF[0][1] == '2' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '1' &&
                     dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '2' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(2, -1)/(1, 0)/(-2, 0)/(2, 1)/(3, 3)/";
                convertString(s);
                break;
            }
            // Muffin/FistR
            else if (uF[0][1] == '1' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '2' &&
                     uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '2' && uF[7][1] == '1' &&
                     dF[0][1] == '2' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '1' &&
                     dF[4][1] == '2' && dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(1, -2)/(0, -1)/(0, 2)/(-1, -2)/(-3, -3)/";
                convertString(s);
                break;
            }
            // FistL/Muffin
            else if (uF[0][1] == '2' && uF[1][1] == '2' && uF[2][1] == '1' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '1' &&
                     dF[0][1] == '1' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '2' &&
                     dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '2' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-2, 1)/(-1, 0)/(2, 0)/(-2, -1)/(3, 3)/";
                convertString(s);
                break;
            }
            // Muffin/FistL
            else if (uF[0][1] == '2' && uF[1][1] == '2' && uF[2][1] == '1' && uF[3][1] == '1' &&
                     uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '2' && uF[7][1] == '1' &&
                     dF[0][1] == '1' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '2' &&
                     dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-1, 2)/(0, 1)/(0, -2)/(1, 2)/(-3, -3)/";
                convertString(s);
                break;
            }
            // FistR/FistL
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '1' && uF[7][1] == '2' &&
                     dF[0][1] == '1' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '2' &&
                     dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(4, 0)/(-2, 0)/(2, 0)/(-1, 0)/(-3, 0)/";
                convertString(s);
                break;
            }
            // FistL/FistR
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '1' &&
                     dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '1' && dF[3][1] == '2' &&
                     dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(2, 0)/(-2, 0)/(2, 0)/(-1, 0)/(-3, 0)/";
                convertString(s);
                break;
            }

            //////////// Depth 7 /////////////

            // Kite/Square
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '1' && uF[3][1] == '2' &&
                     uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '2' && uF[7][1] == '1' &&
                     dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '2' &&
                     dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-1, 0)/(2, 0)/(-2, 0)/(2, 0)/(-1, 0)/(-3, 0)/";
                convertString(s);
                break;
            }
            // Square/Kite
            else if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '1' &&
                     dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '1' && dF[3][1] == '2' &&
                     dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '2' && dF[7][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(0, 1)/(0, -2)/(0, 2)/(0, -2)/(0, 1)/(0, 3)/";
                convertString(s);
                break;
            }

        }
        // if no. of blocks in top layer is 9 and bottom layer is 7
        else if (uF.length() == 9 && dF.length() == 7)
        {
            ///////// Depth 6 /////////

            // Shield+/L
            if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '1' && uF[3][1] == '2' &&
                     uF[4][1] == '1' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '1' &&
                     uF[8][1] == '1' && dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '1' &&
                     dF[3][1] == '2' && dF[4][1] == '2' && dF[5][1] == '2' && dF[6][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(-1, 0)/(2, 0)/(0, -2)/(0, 1)/(0, 3)/";
                convertString(s);
                break;
            }
            // Shield+/Line
            else if (uF[0][1] == '1' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '1' &&
                     uF[8][1] == '2' && dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '2' &&
                     dF[3][1] == '1' && dF[4][1] == '2' && dF[5][1] == '2' && dF[6][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
               QString s = "/(3, 0)/(0, 2)/(0, -2)/(0, 1)/(0, 3)/";
                convertString(s);
                break;
            }
        }
        else if (uF.length() == 7 && dF.length() == 9)
        {
            ///////// Depth 6 /////////

            // L/Shield+
            if (uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '2' && uF[6][1] == '2' && dF[0][1] == '2' &&
                     dF[1][1] == '1' && dF[2][1] == '1' && dF[3][1] == '2' && dF[4][1] == '1' &&
                     dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '1' && dF[8][1] == '1' )
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(0, 1)/(0, -2)/(2, 0)/(-1, 0)/(-3, 0)/";
                convertString(s);
                break;
            }
            // Line/Shield+
            else if (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '2' && uF[3][1] == '1' &&
                     uF[4][1] == '2' && uF[5][1] == '2' && uF[6][1] == '2' && dF[0][1] == '1' &&
                     dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '1' && dF[4][1] == '1' &&
                     dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '1' && dF[8][1] == '2' )
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(0, -3)/(-2, 0)/(2, 0)/(-1, 0)/(-3, 0)/";
                convertString(s);
                break;
            }
        }
        else if (uF.length() == 10 && dF.length() == 6)
        {
            ///////// Depth 6 /////////

            // Oyster/Star
            if (uF[0][1] == '1' && uF[1][1] == '1' && uF[2][1] == '1' && uF[3][1] == '2' &&
                     uF[4][1] == '1' && uF[5][1] == '1' && uF[6][1] == '1' && uF[7][1] == '1' &&
                     uF[8][1] == '1' && uF[9][1] == '2' && dF[0][1] == '2' && dF[1][1] == '2' &&
                     dF[2][1] == '2' && dF[3][1] == '2' && dF[4][1] == '2' && dF[5][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(4, 0)/(1, 2)/(3, -2)/(-1, -2)/(0, -3)/";
                convertString(s);
                break;
            }
            // Church/Star
            else if (uF[0][1] == '1' && uF[1][1] == '1' && uF[2][1] == '1' && uF[3][1] == '2' &&
                     uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '1' &&
                     uF[8][1] == '1' && uF[9][1] == '1' && dF[0][1] == '2' && dF[1][1] == '2' &&
                     dF[2][1] == '2' && dF[3][1] == '2' && dF[4][1] == '2' && dF[5][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(2, 0)/(1, 2)/(3, -2)/(-1, -2)/(0, -3)/";
                convertString(s);
                break;
            }
        }
        else if (uF.length() == 6 && dF.length() == 10)
        {
            ///////// Depth 6 /////////

            // Star/Oyster
            if (uF[0][1] == '2' && uF[1][1] == '2' && uF[2][1] == '2' && uF[3][1] == '2' &&
                     uF[4][1] == '2' && uF[5][1] == '2' && dF[0][1] == '1' && dF[1][1] == '2' &&
                     dF[2][1] == '1' && dF[3][1] == '1' && dF[4][1] == '1' && dF[5][1] == '2' &&
                     dF[6][1] == '1' && dF[7][1] == '1' && dF[8][1] == '1' && dF[9][1] == '1')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(0, -4)/(-2, -1)/(2, -3)/(2, 1)/(3, 0)/";
                convertString(s);
                break;
            }
            // Star/Church
            else if (uF[0][1] == '2' && uF[1][1] == '2' && uF[2][1] == '2' && uF[3][1] == '2' &&
                     uF[4][1] == '2' && uF[5][1] == '2' && dF[0][1] == '1' && dF[1][1] == '2' &&
                     dF[2][1] == '1' && dF[3][1] == '1' && dF[4][1] == '1' && dF[5][1] == '1' &&
                     dF[6][1] == '1' && dF[7][1] == '1' && dF[8][1] == '1' && dF[9][1] == '2')
            {
                resetLocationSQ();
                switch (x)
                {
                    case 0: U(u);D(d); break;
                    case 1: U(u);D(d);S();U(u1);D(d1); break;
                    case 2: U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2); break;
                }
                QString s = "/(0, -2)/(-2, -1)/(2, -3)/(2, 1)/(3, 0)/";
                convertString(s);
                break;
            }
        }


        // if none of the above conditions work, reset location to initial state
        resetLocationSQ();

        // switch on trial
        trialSQ = true;

        // trying all (x, y) combinations
        if (x == 0)
        {
            // trying all y possibilities then incrementing x and restarting y
            d++;

            if (d == n)
            {
                d = 0;
                u++;
            }

            if (u == m)
            {
                x = 1; u = 0; d = 0;
                U(u);D(d);S();U(u1);D(d1);
            }
            else
                U(u);D(d);
        }

        // trying all (x, y)/(x1, y1) possibilities (depth 1)
        else if (x == 1)
        {
            d1++;

            if (d1 == n)
            {
                d1 = 0;
                u1++;
            }
            if (u1 == m)
            {
                u1 = 0; d1 = 0;
                d++;
            }
            if (d == n)
            {
                d = 0;u1 = 0;d1 = 0;
                u++;
            }
            if (u == m)
            {
                x = 2; u = 0; d = 0; u1 = 0; d1 = 0;
            }

            U(u);D(d);S();U(u1);D(d1);
        }

        // trying all (x, y)/(x1, y1)/(x2, y2) possibilities (depth 2)
        else if (x == 2)
        {
            d2++;

            if (d2 == n)
            {
                d2 = 0;
                u2++;
            }
            if (u2 == m)
            {
                u2 = 0; d2 = 0;
                d1++;
            }
            if (d1 == n)
            {
                d1 = 0;u2 = 0;d2 = 0;
                u1++;
            }
            if (u1 == m)
            {
                u1 = 0;d1 = 0;u2 = 0;d2 = 0;
                d++;
            }
            if (d == n)
            {
                d = 0;u1 = 0;d1 = 0;u2 = 0;d2 = 0;
                u++;
            }
            if (u == m)
            {
                u = 0;d = 0;u1 = 0;d1 = 0;u2 = 0;d2 = 0;
                break;
            }
            U(u);D(d);S();U(u1);D(d1);S();U(u2);D(d2);
        }
    }
}

void CO()
{
    createCheckpointSQ();

    trialSQ = true;

    int u = 0, d = 0;

    while (true)
    {
        trialSQ = false;

        // 4w/4y

        if (uF[0][0] == 'w' && uF[2][0] == 'w' && uF[4][0] == 'w' && uF[6][0] == 'w' &&
                dF[1][0] == 'y' && dF[3][0] == 'y' && dF[5][0] == 'y' && dF[7][0] == 'y')
        {
            resetLocationSQ();
            break;
        }
        // 3w1y/3y1w

        // UFL/DFR
        else if (uF[0][0] == 'w' && uF[2][0] == 'w' && uF[4][0] == 'y' && uF[6][0] == 'w' &&
                dF[1][0] == 'w' && dF[3][0] == 'y' && dF[5][0] == 'y' && dF[7][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(-3, 0)/(-1, 0)";
            convertString(s);
            break;
        }
        // UFR/DFL
        else if (uF[0][0] == 'w' && uF[2][0] == 'y' && uF[4][0] == 'w' && uF[6][0] == 'w' &&
                dF[1][0] == 'y' && dF[3][0] == 'y' && dF[5][0] == 'y' && dF[7][0] == 'w')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(0, 3)/(-1, 0)";
            convertString(s);
            break;
        }
        // UBL/DBR
        else if (uF[0][0] == 'w' && uF[2][0] == 'w' && uF[4][0] == 'w' && uF[6][0] == 'y' &&
                dF[1][0] == 'y' && dF[3][0] == 'w' && dF[5][0] == 'y' && dF[7][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(3, 0)/(-1, 0)";
            convertString(s);
            break;
        }
        // UBR/DBL
        else if (uF[0][0] == 'y' && uF[2][0] == 'w' && uF[4][0] == 'w' && uF[6][0] == 'w' &&
                dF[1][0] == 'y' && dF[3][0] == 'y' && dF[5][0] == 'w' && dF[7][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(0, -3)/(-1, 0)";
            convertString(s);
            break;
        }
        // 2w2y/2y2w

        // bars
        else if (uF[0][0] == 'y' && uF[2][0] == 'y' && uF[4][0] == 'w' && uF[6][0] == 'w' &&
                dF[1][0] == 'w' && dF[3][0] == 'w' && dF[5][0] == 'y' && dF[7][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(-1, 0)";
            convertString(s);
            break;
        }
        // diag(BL-TR)/bar
        else if (uF[0][0] == 'y' && uF[2][0] == 'w' && uF[4][0] == 'y' && uF[6][0] == 'w' &&
                dF[1][0] == 'w' && dF[3][0] == 'w' && dF[5][0] == 'y' && dF[7][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(3, 0)/(3, 0)/(-1, 0)";
            convertString(s);
            break;
        }
        // diag(TL-BR)/bar
        else if (uF[0][0] == 'w' && uF[2][0] == 'y' && uF[4][0] == 'w' && uF[6][0] == 'y' &&
                dF[1][0] == 'w' && dF[3][0] == 'w' && dF[5][0] == 'y' && dF[7][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(-3, 0)/(-3, 0)/(-1, 0)";
            convertString(s);
            break;
        }
        // bar/diag(BR-TL when D Facing)
        else if (uF[0][0] == 'y' && uF[2][0] == 'y' && uF[4][0] == 'w' && uF[6][0] == 'w' &&
                dF[1][0] == 'y' && dF[3][0] == 'w' && dF[5][0] == 'y' && dF[7][0] == 'w')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(0, -3)/(0, -3)/(-1, 0)";
            convertString(s);
            break;
        }
        // bar/diag(TR-BL when D Facing)
        else if (uF[0][0] == 'y' && uF[2][0] == 'y' && uF[4][0] == 'w' && uF[6][0] == 'w' &&
                dF[1][0] == 'w' && dF[3][0] == 'y' && dF[5][0] == 'w' && dF[7][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(0, 3)/(0, 3)/(-1, 0)";
            convertString(s);
            break;
        }
        // diag/diag (Yellow on UFR and DFR)
        else if (uF[0][0] == 'w' && uF[2][0] == 'y' && uF[4][0] == 'w' && uF[6][0] == 'y' &&
                dF[1][0] == 'y' && dF[3][0] == 'w' && dF[5][0] == 'y' && dF[7][0] == 'w')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(3, 3)/(-1, 0)";
            convertString(s);
            break;
        }
        // diag/diag (Yellow on UFL and DFL)
        else if (uF[0][0] == 'y' && uF[2][0] == 'w' && uF[4][0] == 'y' && uF[6][0] == 'w' &&
                dF[1][0] == 'w' && dF[3][0] == 'y' && dF[5][0] == 'w' && dF[7][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(-3, -3)/(-1, 0)";
            convertString(s);
            break;
        }

        // 1w3y/1y3w

        // UFL/DFR
        else if (uF[0][0] == 'y' && uF[2][0] == 'y' && uF[4][0] == 'w' && uF[6][0] == 'y' &&
                dF[1][0] == 'y' && dF[3][0] == 'w' && dF[5][0] == 'w' && dF[7][0] == 'w')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(3, 6)/(-1, 0)";
            convertString(s);
            break;
        }
        // UFR/DFL
        else if (uF[0][0] == 'y' && uF[2][0] == 'w' && uF[4][0] == 'y' && uF[6][0] == 'y' &&
                dF[1][0] == 'w' && dF[3][0] == 'w' && dF[5][0] == 'w' && dF[7][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(6, -3)/(-1, 0)";
            convertString(s);
            break;
        }
        // UBL/DBR
        else if (uF[0][0] == 'y' && uF[2][0] == 'y' && uF[4][0] == 'y' && uF[6][0] == 'w' &&
                dF[1][0] == 'w' && dF[3][0] == 'y' && dF[5][0] == 'w' && dF[7][0] == 'w')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(-3, 6)/(-1, 0)";
            convertString(s);
            break;
        }
        // UBR/DBL
        else if (uF[0][0] == 'w' && uF[2][0] == 'y' && uF[4][0] == 'y' && uF[6][0] == 'y' &&
                dF[1][0] == 'w' && dF[3][0] == 'w' && dF[5][0] == 'y' && dF[7][0] == 'w')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(6, 3)/(-1, 0)";
            convertString(s);
            break;
        }

        // 4y/4w

        else if (uF[0][0] == 'y' && uF[2][0] == 'y' && uF[4][0] == 'y' && uF[6][0] == 'y' &&
                dF[1][0] == 'w' && dF[3][0] == 'w' && dF[5][0] == 'w' && dF[7][0] == 'w')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(6, 6)/(-1, 0)";
            convertString(s);
            break;
        }

        // if none of the above conditions work, reset location to initial state
        resetLocationSQ();

        // switch on trial
        trialSQ = true;

        // trying all y possibilities then incrementing x and restarting y
        d += 3;

        if (d == 12)
        {
            d = 0;
            u += 3;
        }

        if (u == 12)
        {
            u = 0; d = 0;
            break;
        }

        U(u);D(d);
    }

}

void EO()
{
    createCheckpointSQ();

    trialSQ = true;

    int u = 0, d = 0;

    while (true)
    {
        trialSQ = false;

        // 4w/4y

        if (uF[1][0] == 'w' && uF[3][0] == 'w' && uF[5][0] == 'w' && uF[7][0] == 'w' &&
                dF[0][0] == 'y' && dF[2][0] == 'y' && dF[4][0] == 'y' && dF[6][0] == 'y')
        {
            resetLocationSQ();
            break;
        }

        // 3w1y/3y1w

        // UB/DF
        else if (uF[1][0] == 'w' && uF[3][0] == 'w' && uF[5][0] == 'w' && uF[7][0] == 'y' &&
                 dF[0][0] == 'w' && dF[2][0] == 'y' && dF[4][0] == 'y' && dF[6][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(0, -1)/(-3, 0)/(4, 1)/(-4, -1)/(3, 0)/(0, 1)";
            convertString(s);
            break;
        }
        // UR/DB
        else if (uF[1][0] == 'y' && uF[3][0] == 'w' && uF[5][0] == 'w' && uF[7][0] == 'w' &&
                 dF[0][0] == 'y' && dF[2][0] == 'y' && dF[4][0] == 'w' && dF[6][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(3, 0)/(3, 0)/(-1, -1)/(-2, 1)/(-3, 0)/(-1, 0)";
            convertString(s);
            break;
        }

        // 2w2y/2y2w

        // Adjs at LF and RF
        else if (uF[1][0] == 'w' && uF[3][0] == 'y' && uF[5][0] == 'y' && uF[7][0] == 'w' &&
                 dF[0][0] == 'w' && dF[2][0] == 'w' && dF[4][0] == 'y' && dF[6][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(3, 0)/(-1, -1)/(-3, 0)/(0, 1)";
            convertString(s);
            break;
        }
        // Adjs at LB and RB
        else if (uF[1][0] == 'w' && uF[3][0] == 'w' && uF[5][0] == 'y' && uF[7][0] == 'y' &&
                 dF[0][0] == 'y' && dF[2][0] == 'w' && dF[4][0] == 'w' && dF[6][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(-3, 0)/(-1, -1)/(4, 1)/(-1, 0)";
            convertString(s);
            break;
        }
        // Adj at LB and opp at FB
        else if (uF[1][0] == 'w' && uF[3][0] == 'w' && uF[5][0] == 'y' && uF[7][0] == 'y' &&
                 dF[0][0] == 'w' && dF[2][0] == 'y' && dF[4][0] == 'w' && dF[6][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(3, 0)/(3, 0)/(-1, -1)/(-2, 1)/(-4, -1)/(0, 1)";
            convertString(s);
            break;
        }
        // Adj at LF and opp at FB
        else if (uF[1][0] == 'w' && uF[3][0] == 'y' && uF[5][0] == 'y' && uF[7][0] == 'w' &&
                 dF[0][0] == 'w' && dF[2][0] == 'y' && dF[4][0] == 'w' && dF[6][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(0, -1)/(3, 0)/(0, -3)/(1, 1)/(0, 3)/(-3, 0)/(-1, 0)";
            convertString(s);
            break;
        }
        // Opp at FB and adj at LF
        else if (uF[1][0] == 'w' && uF[3][0] == 'y' && uF[5][0] == 'w' && uF[7][0] == 'y' &&
                 dF[0][0] == 'w' && dF[2][0] == 'y' && dF[4][0] == 'y' && dF[6][0] == 'w')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(0, -3)/(3, 0)/(-1, -1)/(-3, 0)/(0, 3)/(0, 1)";
            convertString(s);
            break;
        }
        // Opp at FB and opp at FB
        else if (uF[1][0] == 'w' && uF[3][0] == 'y' && uF[5][0] == 'w' && uF[7][0] == 'y' &&
                 dF[0][0] == 'w' && dF[2][0] == 'y' && dF[4][0] == 'w' && dF[6][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(-1, -1)/(0, 1)";
            convertString(s);
            break;
        }

        // 1w3y/1y3w

        // Solved edges at B and L
        else if (uF[1][0] == 'y' && uF[3][0] == 'y' && uF[5][0] == 'y' && uF[7][0] == 'w' &&
                 dF[0][0] == 'w' && dF[2][0] == 'w' && dF[4][0] == 'w' && dF[6][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(3, 0)/(3, 0)/(-1, -1)/(-3, 0)/(-3, 0)/(0, 1)";
            convertString(s);
            break;
        }
        // Solved edges at L and L
        else if (uF[1][0] == 'y' && uF[3][0] == 'y' && uF[5][0] == 'w' && uF[7][0] == 'y' &&
                 dF[0][0] == 'w' && dF[2][0] == 'w' && dF[4][0] == 'w' && dF[6][0] == 'y')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(0, -1)/(3, 0)/(3, 0)/(1, 1)/(-3, 0)/(-3, 0)/(-1, 0)";
            convertString(s);
            break;
        }

        // 4y/4w

        else if (uF[1][0] == 'y' && uF[3][0] == 'y' && uF[5][0] == 'y' && uF[7][0] == 'y' &&
                 dF[0][0] == 'w' && dF[2][0] == 'w' && dF[4][0] == 'w' && dF[6][0] == 'w')
        {
            resetLocationSQ();
            U(u);D(d);
            QString s = "(1, 0)/(-1, -1)/(3, 3)/(1, 1)/(-1, 0)";
            convertString(s);
            break;
        }


        // if none of the above conditions work, reset location to initial state
        resetLocationSQ();

        // switch on trial
        trialSQ = true;

        // trying all y possibilities then incrementing x and restarting y
        d += 3;

        if (d == 12)
        {
            d = 0;
            u += 3;
        }

        if (u == 12)
        {
            u = 0; d = 0;
            break;
        }

        U(u);D(d);
    }
}

int checkPLL(int layer)
{
    createCheckpointSQ();

    QStringList temp;
    trialSQ = true; // trial is ON

    temp << "trash";

    int x = 0; // keeps track of no. of U moves
    int barLoc = 0;

    // checks if Last layer is permuted, if not, control enters loop
    while (x <= 3)
    {
        temp.clear();
        if (layer == 0)
            temp = uL;
        else if (layer == 1)
        {
            temp << dL[5] << dL[4] << dL[3] << dL[2] << dL[1] << dL[0] << dL[11] << dL[10] << dL[9]
                    << dL[8] << dL[7] << dL[6];
        }


        /* 21 different PLL cases are checked below. PLL name is used for checking bugs
         * Section can be overlooked unless there are some bugs and more optimal algs
         * Again, small letters functions are used to change algs according to y value and
         * reduce moveCount.
         */

        // Solved State
        if (temp[6] == temp[5] && temp[5] == temp[4] && temp[9] == temp[8] && temp[8] == temp[7] &&
                temp[0] == temp[11] && temp[11] == temp[10] && temp[3] == temp[2] && temp[2] == temp[1])
        {
            perms << "S";
            break;
        }

        // H Perm
        else if (temp[6] == temp[4] && temp[9] == temp[7] && temp[0] == temp[10]
                && temp[3] == temp[1] && temp[5] == temp[0] && temp[8] == temp[3]
                 && temp[2] == temp[9] && temp[11] == temp[6])
        {
            perms << "S";
            break;
        }
        // U Perm Cw
        else if (temp[6] == temp[4] && temp[9] == temp[7] && temp[0] == temp[10]
                 && temp[3] == temp[1] && temp[2] == temp[6] && temp[5] == temp[9]
                 && temp[8] == temp[1] && temp[11] == temp[0])
        {
            perms << "S";
            break;
        }
        // U Perm Ccw
        else if (temp[6] == temp[4] && temp[9] == temp[7] && temp[0] == temp[10]
                 && temp[3] == temp[1] && temp[3] == temp[5] && temp[6] == temp[8]
                 && temp[2] == temp[9] && temp[11] == temp[0])
        {
            perms << "S";
            break;
        }
        // Z Perm
        else if (temp[6] == temp[4] && temp[9] == temp[7] && temp[0] == temp[10]
                 && temp[3] == temp[1] && temp[8] == temp[6] && temp[5] == temp[9]
                 && temp[2] == temp[10] && temp[11] == temp[3])
        {
            perms << "S";
            break;
        }

        // A Perm Cw
        else if (temp[6] == temp[5] && temp[8] == temp[7] && temp[0] == temp[10]
                 && temp[11] == temp[4] && temp[9] == temp[4] && temp[0] == temp[2]
                 && temp[3] == temp[7] && temp[1] == temp[5])
        {
            perms << "J";
            switch (x)
            {
                case 0: barLoc = 3; break;
                case 1: barLoc = 2; break;
                case 2: barLoc = 1; break;
                case 3: barLoc = 4; break;
            }
            break;
        }
        // A Perm Ccw
        else if (temp[6] == temp[5] && temp[8] == temp[7] && temp[3] == temp[1]
                 && temp[2] == temp[4] && temp[4] == temp[9] && temp[11] == temp[1]
                 && temp[0] == temp[7] && temp[10] == temp[6])
        {
            perms << "J";
            switch (x)
            {
                case 0: barLoc = 4; break;
                case 1: barLoc = 3; break;
                case 2: barLoc = 2; break;
                case 3: barLoc = 1; break;
            }
            break;
        }
        // E Perm
        else if (temp[5] == temp[7] && temp[5] == temp[3] && temp[11] == temp[9]
                 && temp[11] == temp[1] && temp[4] == temp[8] && temp[6] == temp[2]
                 && temp[2] == temp[10] && temp[8] == temp[0])
        {
            perms << "N";
            break;
        }
        // F Perm
        else if (temp[5] == temp[4] && temp[5] == temp[6] && temp[0] == temp[7]
                 && temp[10] == temp[3] && temp[11] == temp[9] && temp[11] == temp[1]
                 && temp[10] == temp[8] && temp[0] == temp[2])
        {
            perms << "J";
            switch (x)
            {
                case 0: barLoc = 1; break;
                case 1: barLoc = 4; break;
                case 2: barLoc = 3; break;
                case 3: barLoc = 2; break;
            }
            break;
        }
        // G Perm 4
        else if (temp[0] == temp[10] && temp[8] == temp[7] && temp[11] == temp[6]
                 && temp[0] == temp[5] && temp[4] == temp[9] && temp[3] == temp[7]
                 && temp[2] == temp[4] && temp[1] == temp[11])
        {
            perms << "J";
            switch (x)
            {
                case 0: barLoc = 3; break;
                case 1: barLoc = 2; break;
                case 2: barLoc = 1; break;
                case 3: barLoc = 4; break;
            }
            break;
        }
        // G Perm 2
        else if (temp[9] == temp[7] && temp[2] == temp[1] && temp[8] == temp[0]
                 && temp[9] == temp[11] && temp[3] == temp[5] && temp[6] == temp[1]
                 && temp[0] == temp[4] && temp[10] == temp[5])
        {
            perms << "J";
            switch (x)
            {
                case 0: barLoc = 2; break;
                case 1: barLoc = 1; break;
                case 2: barLoc = 4; break;
                case 3: barLoc = 3; break;
            }
            break;
        }
        // G Perm 3
        else if (temp[0] == temp[10] && temp[2] ==temp[3] && temp[11] == temp[4]
                 && temp[0] == temp[5] && temp[1] == temp[6] && temp[6] == temp[8]
                 && temp[7] == temp[3] && temp[11] == temp[9])
        {
            perms << "J";
            switch (x)
            {
                case 0: barLoc = 3; break;
                case 1: barLoc = 2; break;
                case 2: barLoc = 1; break;
                case 3: barLoc = 4; break;
            }
            break;
        }
        // G Perm 1
        else if (temp[9] == temp[7] && temp[2] == temp[3] && temp[8] == temp[4]
                 && temp[9] == temp[5] && temp[1] == temp[6] && temp[6] == temp[11]
                 && temp[10] == temp[3] && temp[0] == temp[4])
        {
            perms << "J";
            switch (x)
            {
                case 0: barLoc = 2; break;
                case 1: barLoc = 1; break;
                case 2: barLoc = 4; break;
                case 3: barLoc = 3; break;
            }
            break;
        }
        // J Perm 2-1
        else if (temp[3] == temp[2] && temp[3] == temp[1] && temp[0] == temp[11]
                 && temp[9] == temp[8] && temp[6] == temp[5] && temp[4] == temp[8]
                 && temp[5] == temp[10] && temp[0] == temp[7])
        {
            perms << "J";
            switch (x)
            {
                case 0: barLoc = 4; break;
                case 1: barLoc = 3; break;
                case 2: barLoc = 2; break;
                case 3: barLoc = 1; break;
            }
            break;
        }
        // J Perm 1-2
        else if (temp[3] == temp[2] && temp[3] == temp[1] && temp[10] == temp[11]
                 && temp[7] == temp[8] && temp[4] == temp[5] && temp[4] == temp[9]
                 && temp[7] == temp[0] && temp[10] == temp[6])
        {
            perms << "J";
            switch (x)
            {
                case 0: barLoc = 4; break;
                case 1: barLoc = 3; break;
                case 2: barLoc = 2; break;
                case 3: barLoc = 1; break;
            }
            break;
        }
        // N Perm 1-2
        else if (temp[3] == temp[7] && temp[2] == temp[1] && temp[10] == temp[11]
                 && temp[7] == temp[8] && temp[4] == temp[5] && temp[1] == temp[9]
                 && temp[6] == temp[10] && temp[0] == temp[4])
        {
            perms << "N";
            break;
        }
        // N Perm 2-1
        else if (temp[3] == temp[7] && temp[3] == temp[2] && temp[0] == temp[11]
                 && temp[9] == temp[8] && temp[6] == temp[5] && temp[1] == temp[9]
                 && temp[6] == temp[10] && temp[0] == temp[4])
        {
            perms << "N";
            break;
        }
        // R Perm Right tail
        else if (temp[6] == temp[4] && temp[8] == temp[6] && temp[3] == temp[2]
                 && temp[1] == temp[9] && temp[9] == temp[11] && temp[5] == temp[7]
                 && temp[7] == temp[0] && temp[10] == temp[2])
        {
            perms << "J";
            switch (x)
            {
                case 0: barLoc = 1; break;
                case 1: barLoc = 4; break;
                case 2: barLoc = 3; break;
                case 3: barLoc = 2; break;
            }
            break;
        }
        // R Perm Left tail
        else if (temp[6] == temp[4] && temp[2] == temp[6] && temp[7] == temp[8]
                 && temp[1] == temp[9] && temp[9] == temp[11] && temp[5] == temp[10]
                 && temp[7] == temp[0] && temp[10] == temp[3])
        {
            perms << "J";
            switch (x)
            {
                case 0: barLoc = 1; break;
                case 1: barLoc = 4; break;
                case 2: barLoc = 3; break;
                case 3: barLoc = 2; break;
            }
            break;
        }
        // T Perm
        else if (temp[9] == temp[7] && temp[6] == temp[5] && temp[11] == temp[10]
                 && temp[4] == temp[0] && temp[4] == temp[8] && temp[5] == temp[1]
                 && temp[2] == temp[7] && temp[10] == temp[3])
        {
            perms << "J";
            switch (x)
            {
                case 0: barLoc = 2; break;
                case 1: barLoc = 1; break;
                case 2: barLoc = 4; break;
                case 3: barLoc = 3; break;
            }
            break;
        }
        // V Perm
        else if (temp[6] == temp[5] && temp[8] == temp[7] && temp[4] == temp[2]
                 && temp[9] == temp[11] && temp[2] == temp[0] && temp[11] == temp[1]
                 && temp[7] == temp[3] && temp[10] == temp[6])
        {
            perms << "N";
            break;
        }
        // Y Perm
        else if (temp[6] == temp[5] && temp[2] == temp[1] && temp[4] == temp[8]
                 && temp[3] == temp[11] && temp[4] == temp[0] && temp[3] == temp[7]
                 && temp[9] == temp[1] && temp[10] == temp[6])
        {
            perms << "N";
            break;
        }

        x++;

        if (layer == 0)
            U(3);
        else if (layer == 1)
            Di(3);
    }

    resetLocationSQ();
    temp.clear();
    if (layer == 0)
        temp = uL;
    else if (layer == 1)
    {
        temp << dL[5] << dL[4] << dL[3] << dL[2] << dL[1] << dL[0] << dL[11] << dL[10] << dL[9]
                << dL[8] << dL[7] << dL[6];
    }

    if (perms.length() != layer + 1 && perms.length() <= layer + 1)
    {
        // CP solved
        if (temp[6] == temp[4] && temp[9] == temp[7] && temp[0] == temp[10]
                && temp[3] == temp[1])
        {
            perms << "SP";
        }
        else if (temp[6] == temp[4] && temp[9] != temp[7] && temp[0] != temp[10]
                 && temp[3] != temp[1])
        {
            perms << "JP";
            barLoc = 1;
        }
        else if (temp[6] != temp[4] && temp[9] == temp[7] && temp[0] != temp[10]
                 && temp[3] != temp[1])
        {
            perms << "JP";
            barLoc = 2;
        }
        else if (temp[6] != temp[4] && temp[9] != temp[7] && temp[0] == temp[10]
                 && temp[3] != temp[1])
        {
            perms << "JP";
            barLoc = 3;
        }
        else if (temp[6] != temp[4] && temp[9] != temp[7] && temp[0] != temp[10]
                 && temp[3] == temp[1])
        {
            perms << "JP";
            barLoc = 4;
        }
        else
            perms << "NP";
    }

    trialSQ = false; //switches of trial since it's switched in the final run through the loop
    return barLoc;
}

void CP()
{
    int b1 = checkPLL(0);
    int b2 = checkPLL(1);

    //////////// Solution Stage ////////////

    // Solved/Solved
    if ((perms[0] == "S" && perms[1] == "S") || (perms[0] == "SP" && perms[1] == "SP"))
    {

    }
    // J/J
    else if ((perms[0] == "J" && perms[1] == "J") || (perms[0] == "JP" && perms[1] == "JP"))
    {
        switch (b1)
        {
            case 1: U(6); break;
            case 2: U(3); break;
            case 3: U(0); break;
            case 4: Uinv(3); break;
        }
        switch (b2)
        {
            case 1: D(6); break;
            case 2: Di(3); break;
            case 3: D(0); break;
            case 4: D(3); break;
        }
        QString s = "/(-3, 0)/(3, 3)/(0, -3)/";
        convertString(s);
    }
    // N/N
    else if ((perms[0] == "N" && perms[1] == "N") || (perms[0] == "NP" && perms[1] == "NP"))
    {
        QString s = "/(3, -3)/(-3, 3)/";
        convertString(s);
    }
    // N/J
    else if ((perms[0] == "N" && perms[1] == "J") || (perms[0] == "NP" && perms[1] == "JP"))
    {
        U(0);
        switch (b2)
        {
            case 1: Di(3); break;
            case 2: D(0); break;
            case 3: D(3); break;
            case 4: D(6); break;
        }
        QString s = "/(3, 0)/(-3, 0)/(3, 0)/(-3, 0)/";
        convertString(s);
    }
    // J/N
    else if ((perms[0] == "J" && perms[1] == "N") || (perms[0] == "JP" && perms[1] == "NP"))
    {
        switch (b1)
        {
            case 1: U(3); break;
            case 2: U(0); break;
            case 3: Uinv(3); break;
            case 4: U(6); break;
        }
        D(0);
        QString s = "/(0, -3)/(0, 3)/(0, -3)/(0, 3)/";
        convertString(s);
    }
    // J/Solved
    else if ((perms[0] == "J" && perms[1] == "S") || (perms[0] == "JP" && perms[1] == "SP"))
    {
        switch (b1)
        {
            case 1: Uinv(3); break;
            case 2: U(6); break;
            case 3: U(3); break;
            case 4: U(0); break;
        }
        D(0);
        QString s = "/(0, -3)/(0, 3)/(0, -3)/(3, 0)/(-3, 3)/";
        convertString(s);
    }
    // Solved/J
    else if ((perms[0] == "S" && perms[1] == "J") || (perms[0] == "SP" && perms[1] == "JP"))
    {
        U(0);
        switch (b2)
        {
            case 1: D(3); break;
            case 2: D(6); break;
            case 3: Di(3); break;
            case 4: D(0); break;
        }
        QString s = "/(3, 0)/(-3, 0)/(3, 0)/(0, -3)/(-3, 3)/";
        convertString(s);
    }
    // N/Solved
    else if ((perms[0] == "N" && perms[1] == "S") || (perms[0] == "NP" && perms[1] == "SP"))
    {
        QString s = "/(3, 3)/(3, 0)/(3, 3)/(3, 0)/(3, 3)/";
        convertString(s);
    }
    // Solved/N
    else if ((perms[0] == "S" && perms[1] == "N") || (perms[0] == "SP" && perms[1] == "NP"))
    {
        QString s = "/(3, 3)/(0, 3)/(3, 3)/(0, 3)/(3, 3)/";
        convertString(s);
    }

    ///////// Parity /////////

    // Solved/Solved Parity
    else if ((perms[0] == "S" && perms[1] == "SP") || (perms[0] == "SP" && perms[1] == "S"))
    {
        QString s = "/(3, 3)/(1, 0)/(4, -2)/(2, -4)/(0, -4)/(3, 3)/(3, 0)/(6, 0)/(-3, 3)/";
        convertString(s);
    }
    // J/J
    else if ((perms[0] == "J" && perms[1] == "JP") || (perms[0] == "JP" && perms[1] == "J"))
    {
        switch (b1)
        {
            case 1: Uinv(3); break;
            case 2: U(6); break;
            case 3: U(3); break;
            case 4: U(0); break;
        }
        switch (b2)
        {
            case 1: Di(3); break;
            case 2: D(0); break;
            case 3: D(3); break;
            case 4: D(6); break;
        }
        QString s = "/(-3, 0)/(-3, 0)/(-5, 0)/(-2, 0)/(4, 0)/(-4, 0)/(-2, 0)/(5, 0)/(-3, 0)/";
        convertString(s);
    }
    // N/N
    else if ((perms[0] == "N" && perms[1] == "NP") || (perms[0] == "NP" && perms[1] == "N"))
    {
        QString s = "/(3, 3)/(1, 0)/(4, -2)/(2, -4)/(0, -4)/(3, 3)/(3, 0)/(3, 3)/";

        convertString(s);
    }
    // N/J
    else if ((perms[0] == "NP" && perms[1] == "J") || (perms[0] == "N" && perms[1] == "JP"))
    {
        U(0);
        switch (b2)
        {
            case 1: D(3); break;
            case 2: D(6); break;
            case 3: Di(3); break;
            case 4: D(0); break;
        }
        QString s = "/(3, 3)/(1, 0)/(-2, 0)/(4, 0)/(-4, 0)/(-2, 0)/(5, 0)/(-3, -3)/";
        convertString(s);
    }
    // J/N
    else if ((perms[0] == "JP" && perms[1] == "N") || (perms[0] == "J" && perms[1] == "NP"))
    {
        switch (b1)
        {
            case 1: U(3); break;
            case 2: U(0); break;
            case 3: Uinv(3); break;
            case 4: U(6); break;
        }
        D(0);
        QString s = "/(3, 3)/(-1, 0)/(2, 0)/(-4, 0)/(4, 0)/(2, 0)/(-5, 0)/(-3, -3)/";
        convertString(s);
    }
    // J/Solved
    else if ((perms[0] == "JP" && perms[1] == "S") || (perms[0] == "J" && perms[1] == "SP"))
    {
        switch (b1)
        {
            case 1: Uinv(3); break;
            case 2: U(6); break;
            case 3: U(3); break;
            case 4: U(0); break;
        }
        D(0);
        QString s = "/(3, 3)/(-1, 0)/(2, 0)/(-4, 0)/(4, 0)/(2, 0)/(1, 0)/(-3, -3)/";
        convertString(s);
    }
    // Solved/J
    else if ((perms[0] == "SP" && perms[1] == "J") || (perms[0] == "S" && perms[1] == "JP"))
    {
        U(0);
        switch (b2)
        {
            case 1: Di(3); break;
            case 2: D(0); break;
            case 3: D(3); break;
            case 4: D(6); break;
        }
        QString s = "/(3, 3)/(1, 0)/(-2, 0)/(4, 0)/(-4, 0)/(-2, 0)/(-1, 0)/(-3, -3)/";
        convertString(s);
    }
    // N/Solved
    else if ((perms[0] == "NP" && perms[1] == "S") || (perms[0] == "N" && perms[1] == "SP"))
    {
        QString s = "/(3, 3)/(1, 2)/(4, -2)/(2, -4)/(1, 2)/(-3, -3)/";
        convertString(s);
    }
    // Solved/N
    else if ((perms[0] == "SP" && perms[1] == "N") || (perms[0] == "S" && perms[1] == "NP"))
    {
        QString s = "/(3, 3)/(1, 2)/(2, -4)/(4, -2)/(1, 2)/(-3, -3)/";
        convertString(s);
    }
}

QString checkEP(int layer)
{
    createCheckpointSQ();

    QStringList temp;
    QString pll;

    temp << "trash"; // since it is cleared in the loop

    int x = 0; // keeps track of no. of U/D moves
    int y = 0; // allots variable for U/D move

    // checks if Last layer is permuted, if not, control enters loop
    while (x <= 3)
    {
        trialSQ = false;

        temp.clear();

        if (layer == 0)
            temp = uL;
        else if (layer == 1)
        {
            temp << dL[5] << dL[4] << dL[3] << dL[2] << dL[1] << dL[0] << dL[11] << dL[10] << dL[9]
                    << dL[8] << dL[7] << dL[6];
        }


        // Solved State
        if (temp[6] == temp[5] && temp[5] == temp[4] && temp[9] == temp[8] && temp[8] == temp[7] &&
                temp[0] == temp[11] && temp[11] == temp[10] && temp[3] == temp[2] && temp[2] == temp[1])
        {
            pll = "S";
            break;
        }

        // H Perm
        else if (temp[5] == temp[0] && temp[8] == temp[3] && temp[2] == temp[9] && temp[11] == temp[6])
        {
            pll = "H";
            break;
        }
        // U Perm Cw
        else if (temp[2] == temp[6] && temp[5] == temp[9] && temp[8] == temp[1] && temp[11] == temp[0])
        {
            if (layer == 0)
                pll = "UCw";
            else if (layer == 1)
                pll = "UCcw";
            break;
        }
        // U Perm Ccw
        else if (temp[3] == temp[5] && temp[6] == temp[8] && temp[2] == temp[9] && temp[11] == temp[0])
        {
            if (layer == 0)
                pll = "UCcw";
            else if (layer == 1)
                pll = "UCw";
            break;
        }
        // Z Perm
        else if (temp[8] == temp[6] && temp[5] == temp[9] && temp[2] == temp[10] && temp[11] == temp[3])
        {
            pll = "Z";
            break;
        }
        // O Perm Cw
        else if (temp[2] == temp[6] && temp[5] == temp[9] && temp[8] == temp[0] && temp[11] == temp[1])
        {
            if (layer == 0)
                pll = "OCw";
            else if (layer == 1)
                pll = "OCcw";
            break;
        }
        // O Perm Ccw
        else if (temp[3] == temp[5] && temp[6] == temp[8] && temp[2] == temp[0] && temp[11] == temp[9])
        {
            if (layer == 0)
                pll = "OCcw";
            else if (layer == 1)
                pll = "OCw";
            break;
        }
        // W Perm
        else if (temp[5] == temp[0] && temp[8] == temp[3] && temp[2] == temp[6] && temp[11] == temp[9])
        {
            pll = "W";
            break;
        }
        // adj swap
        else if (temp[8] == temp[6] && temp[5] == temp[9] && temp[2] == temp[1] && temp[11] == temp[10])
        {
            pll = "Adj";
            break;
        }
        // opp Perm
        else if (temp[5] == temp[0] && temp[8] == temp[9] && temp[2] == temp[1] && temp[11] == temp[4])
        {
            pll = "Opp";
            break;
        }


        trialSQ = true;

        x++;
        y += 3;

        resetLocationSQ();

        if (layer == 0)
            U(y);
        else if (layer == 1)
            Di(y);
    }

    resetLocationSQ();
    if (layer == 0)
        U(y);
    else
        Di(y);

    return pll;
}

void EP()
{
    QStringList ep;
    ep << checkEP(0);
    ep << checkEP(1);

    ////// Solution Stage ////////

    if (ep[0] == "UCw" && ep[1] == "S")
    {
        QString s = "(6, 0)/(3, 0)/(1, 0)/(0, -3)/(-1, 0)/(-3, 0)/(1, 0)/(0, 3)/(-1, 0)";
        convertString(s);
    }
    else if (ep[0] == "UCw" && ep[1] == "UCw")
    {
        QString s = "(-2, 3)/(5, -1)/(-3, 0)/(1, 1)/(-3, 0)/(-1, 0)";
        convertString(s);
    }
    else if (ep[0] == "UCw" && ep[1] == "UCcw")
    {
        QString s = "(-5, 3)/(5, -1)/(-2, 1)/(-1, -1)/(3, 0)/(-2, 1)/(-1, -1)/(-2, 1)/(2, 0)";
        convertString(s);
    }
    else if (ep[0] == "UCw" && ep[1] == "Z")
    {
        QString s = "(-2, 0)/(0, 3)/(-1, -1)/(1, -2)/(-3, 0)/(3, 0)/(-1, -1)/(-2, 1)/(2, 0)";
        convertString(s);
    }
    else if (ep[0] == "UCw" && ep[1] == "H")
    {
        QString s = "(-3, 0)/(0, -3)/(0, 3)/(0, -3)/(0, 3)/(1, -1)/(0, 3)/(0, -3)/(0, 3)/(0, -3)/(-1, 1)";
        convertString(s);
    }


    else if (ep[0] == "UCcw" && ep[1] == "S")
    {
        QString s = "(-5, 0)/(0, -3)/(-1, 0)/(3, 0)/(1, 0)/(0, 3)/(-1, 0)/(-3, 0)/";
        convertString(s);
    }
    else if (ep[0] == "UCcw" && ep[1] == "UCw")
    {
        QString s = "(-5, 3)/(3, 0)/(-1, -1)/(3, 0)/(-2, 1)/(-1, -1)/(3, 0)/(-5, 1)/(2, 0)";
        convertString(s);
    }
    else if (ep[0] == "UCcw" && ep[1] == "UCcw")
    {
        QString s = "(4, 3)/(3, 0)/(-1, -1)/(3, 0)/(-5, 1)/(-1, 0)";
        convertString(s);
    }
    else if (ep[0] == "UCcw" && ep[1] == "Z")
    {
        QString s = "(1, 0)/(0, 3)/(-1, -1)/(1, -2)/(3, 0)/(3, 0)/(-1, -1)/(-2, 1)/(-1, 0)";
        convertString(s);
    }
    else if (ep[0] == "UCcw" && ep[1] == "H")
    {
        QString s = "(-2, 0)/(0, -3)/(0, 3)/(0, -3)/(0, 3)/(-1, -1)/(0, 3)/(0, -3)/(0, 3)/(0, -3)/(0, 1)";
        convertString(s);
    }


    else if (ep[0] == "Z" && ep[1] == "S")
    {
        QString s = "(1, 0)/(-1, -1)/(-2, 1)/(-1, -1)/(4, -1)/(-1, -1)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "Z" && ep[1] == "UCw")
    {
        QString s = "(-2, 3)/(3, 0)/(-1, -1)/(-2, 1)/(0, -3)/(0, 3)/(-1, -1)/(1, -2)/(-1, 0)";
        convertString(s);
    }
    else if (ep[0] == "Z" && ep[1] == "UCcw")
    {
        QString s = "(-2, 0)/(0, 3)/(-1, -1)/(1, -2)/(0, 3)/(3, 0)/(-1, -1)/(-2, 1)/(-1, 0)";
        convertString(s);
    }
    else if (ep[0] == "Z" && ep[1] == "Z")
    {
        QString s = "(-2, 0)/(0, 3)/(-1, -1)/(4, -2)/(-1, -1)/(-2, 1)/(-1, 0)";
        convertString(s);
    }
    else if (ep[0] == "Z" && ep[1] == "H")
    {
        QString s = "(3, 0)/(-3, -3)/(3, 0)/(5, -1)/(2, -4)/(-1, 2)/(-3, -3)/";
        convertString(s);
    }


    else if (ep[0] == "H" && ep[1] == "S")
    {
        QString s = "(1, 0)/(-1, -1)/(-2, 1)/(-1, -1)/(-5, 1)/(-1, -1)/(-2, 1)/(-1, -1)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "H" && ep[1] == "UCw")
    {
        QString s = "(0, -2)/(-3, 0)/(3, 0)/(-3, 0)/(3, 0)/(1, 1)/(-3, 0)/(3, 0)/(-3, 0)/(3, 0)/(-1, 0)";
        convertString(s);
    }
    else if (ep[0] == "H" && ep[1] == "UCcw")
    {
        QString s = "(0, 3)/(-3, 0)/(3, 0)/(-3, 0)/(3, 0)/(1, -1)/(-3, 0)/(3, 0)/(-3, 0)/(3, 0)/(-1, 1)";
        convertString(s);
    }
    else if (ep[0] == "H" && ep[1] == "Z")
    {
        QString s = "/(-3, -3)/(3, 0)/(1, -5)/(4, -2)/(-2, 1)/(3, 3)/";
        convertString(s);
    }
    else if (ep[0] == "H" && ep[1] == "H")
    {
        QString s = "(1, 0)/(5, -1)/(-3, -3)/(1, 1)/(-3, 3)/(-1, 0)";
        convertString(s);
    }


    else if (ep[0] == "Opp" && ep[1] == "Opp")
    {
        QString s = "(1, 0)/(5, -1)/(-5, 1)/(-1, 0)";
        convertString(s);
    }
    else if (ep[0] == "Opp" && ep[1] == "Adj")
    {
        QString s = "(1, 6)/(0, -1)/(0, -3)/(5, 0)/(-5, 0)/(0, 3)/(0, 1)/(-1, 0)";
        convertString(s);
    }
    else if (ep[0] == "Opp" && ep[1] == "OCw")
    {
        QString s = "(1, 0)/(-1, -1)/(1, -2)/(-1, -1)/(1, -2)/(-1, -1)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "Opp" && ep[1] == "OCcw")
    {
        QString s = "(1, 0)/(-1, -1)/(1, 4)/(-1, -1)/(1, 4)/(-1, -1)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "Opp" && ep[1] == "W")
    {
        QString s = "(3, 5)/(-3, 0)/(0, 1)/(-3, 0)/(0, -1)/(-2, -2)/(-1, 0)/(-3, 0)/(0, -1)/(0, 3)/(0, 1)";
        convertString(s);
    }


    else if (ep[0] == "Adj" && ep[1] == "Opp")
    {
        QString s = "(6, -1)/(1, 0)/(3, 0)/(0, -5)/(0, 5)/(-3, 0)/(-1, 0)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "Adj" && ep[1] == "Adj")
    {
        QString s = "(0, 2)/(-3, 0)/(1, 1)/(2, -1)/(0, -2)";
        convertString(s);
    }
    else if (ep[0] == "Adj" && ep[1] == "OCw")
    {
        QString s = "(1, 0)/(-3, -3)/(-4, -1)/(-2, 1)/(-4, -1)/(-2, 1)/(-3, 0)/(0, 3)/(-1, 0)";
        convertString(s);
    }
    else if (ep[0] == "Adj" && ep[1] == "OCcw")
    {
        QString s = "(6, 0)/(0, 3)/(0, 2)/(1, -5)/(0, 5)/(0, -3)/(0, 3)/(-1, 0)/(0, 3)/(0, 3)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "Adj" && ep[1] == "W")
    {
        QString s = "(-3, -1)/(0, -3)/(1, 1)/(0, -3)/(0, 3)/(-1, -1)/(0, 3)/(0, 1)";
        convertString(s);
    }


    else if (ep[0] == "OCw" && ep[1] == "Opp")
    {
        QString s = "(1, 0)/(-1, -1)/(-2, 1)/(-1, -1)/(-2, 1)/(-1, -1)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "OCw" && ep[1] == "Adj")
    {
        QString s = "(0, 6)/(-3, 0)/(-2, 0)/(5, -1)/(-5, 0)/(3, 0)/(-3, 0)/(0, 1)/(-3, 0)/(-3, 0)/(-1, 0)";
        convertString(s);
    }
    else if (ep[0] == "OCw" && ep[1] == "OCw")
    {
        QString s = "(1, 0)/(-1, -1)/(-2, 1)/(-1, -1)/(4, -2)/(-1, -1)/(1, -2)/(-1, -1/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "OCw" && ep[1] == "OCcw")
    {
        QString s = "(1, 0)/(-1, -1)/(-2, 1)/(-1, -1)/(4, 4)/(-1, -1)/(1, 4)/(-1, -1)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "OCw" && ep[1] == "W")
    {
        QString s = "(0, 3)/(0, -3)/(0, -1)/(3, 0)/(0, 1)/(0, 3)/(0, -1)/(-2, 1)/(-3, 0)/(-1, -1)/(-3, 0)/(1, 1)/(-1, 0)";
        convertString(s);
    }


    else if (ep[0] == "OCcw" && ep[1] == "Opp")
    {
        QString s = "(1, 0)/(-1, -1)/(4, 1)/(-1, -1)/(4, 1)/(-1, -1)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "OCcw" && ep[1] == "Adj")
    {
        QString s = "(1, 6)/(3, 0)/(3, 0)/(0, -1)/(3, 0)/(-3, 0)/(5, 0)/(-5, 1)/(2, 0)/(3, 0)/";
        convertString(s);
    }
    else if (ep[0] == "OCcw" && ep[1] == "OCw")
    {
        QString s = "(1, 0)/(-1, -1)/(4, 1)/(-1, -1)/(-2, -2)/(-1, -1)/(1, -2)/(-1, -1)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "OCcw" && ep[1] == "OCcw")
    {
        QString s = "(1, 0)/(-1, -1)/(4, 1)/(-1, -1)/(-2, 4)/(-1, -1)/(1, 4)/(-1, -1)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "OCcw" && ep[1] == "W")
    {
        QString s = "(0, 3)/(0, -3)/(0, -1)/(3, 0)/(0, 1)/(0, 3)/(0, -1)/(-2, 1)/(3, 0)/(-1, -1)/(3, 0)/(1, 1)/(-1, 0)";
        convertString(s);
    }


    else if (ep[0] == "W" && ep[1] == "Opp")
    {
        QString s = "(-5, 3)/(0, 3)/(-1, 0)/(0, 3)/(1, 0)/(2, 2)/(0, 1)/(0, 3)/(1, 0)/(-3, 0)/(-1, 0)";
        convertString(s);
    }
    else if (ep[0] == "W" && ep[1] == "Adj")
    {
        QString s = "(1, 3)/(3, 0)/(-1, -1)/(3, 0)/(-2, 1)/(-1, -1)/(-2, 1)/(-1, 0)";
        convertString(s);
    }
    else if (ep[0] == "W" && ep[1] == "OCw")
    {
        QString s = "(-3, 0)/(3, 0)/(1, 0)/(0, -3)/(-1, 0)/(-3, 0)/(1, 0)/(-1, 2)/(0, -3)/(1, 1)/(0, -3)/(-1, -1)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "W" && ep[1] == "OCcw")
    {
        QString s = "(-3, 0)/(3, 0)/(1, 0)/(0, -3)/(-1, 0)/(-3, 0)/(1, 0)/(-1, 2)/(0, 3)/(1, 1)/(0, 3)/(-1, -1)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "W" && ep[1] == "W")
    {
        QString s = "(1, -3)/(5, -1)/(-3, 0)/(1, 1)/(0, -3)/(-1, -1)/(-2, 4)/(-1, 0)";
        convertString(s);
    }


    else if (ep[0] == "S" && ep[1] == "UCw")
    {
        QString s = "(0, 5)/(3, 0)/(0, 1)/(0, -3)/(0, -1)/(-3, 0)/(0, 1)/(0, 3)/";
        convertString(s);
    }
    else if (ep[0] == "S" && ep[1] == "UCcw")
    {
        QString s = "(0, 6)/(0, -3)/(0, -1)/(3, 0)/(0, 1)/(0, 3)/(0, -1)/(-3, 0)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "S" && ep[1] == "Z")
    {
        QString s = "(1, 0)/(-1, -1)/(1, 4)/(-1, -1)/(1, -2)/(-1, -1)/(0, 1)";
        convertString(s);
    }
    else if (ep[0] == "S" && ep[1] == "H")
    {
        QString s = "(1, 0)/(-1, -1)/(-5, 1)/(-1, -1)/(1, -2)/(-1, -1)/(-5, 1)/(-1, -1)/(0, 4)";
        convertString(s);
    }

}

void finalAdjusts()
{
    QString temp = scrambleSQ + solutionListSQ.join("");
    QString tail = "";
    int middleLayerFlip = 0, m, x, y;

    foreach (QChar c, temp)
    {
        if (c == '/')
            middleLayerFlip++;
    }

    ////// Middle Layer Flip //////

    if (middleLayerFlip % 2 == 1)
    {
        if (solutionListSQ[solutionListSQ.length() - 1] == "/")
            solutionListSQ.removeLast();
        else if (solutionListSQ[solutionListSQ.length() - 2] == "/")
        {
            tail = solutionListSQ[solutionListSQ.length() - 1];
            tail.remove(QChar('(')).remove(QChar(')')).remove(QChar(','));
            QStringList temp = tail.split(" ");
            x = temp[0][0].digitValue();
            y = temp[1][0].digitValue();
            trialSQ = true;
            if (x <= 0)
                U(-x);
            else
                Uinv(x);
            if (y <= 0)
                D(-y);
            else
                Di(y);

            S();

            trialSQ = false;
            solutionListSQ.removeLast();
            solutionListSQ.removeLast();
        }

        m = solutionListSQ.length() - 1;

        if (solutionListSQ[m][1] == '0')
        {
            U(0);D(6);S();U(0);D(6);S();
        }
        else
        {
            U(6);D(0);S();U(6);D(0);S();
        }
        if (tail != "")
        {
            if (x < 0)
                Uinv(-x);
            else
                U(x);
            if (y < 0)
                Di(-y);
            else
                D(y);
        }
    }

    ////// AUF/ADF ////////

    if (uL[5] == "g")
        U(0);
    else if (uL[5] == "o")
        U(3);
    else if (uL[5] == "b")
        U(6);
    else if (uL[5] == "r")
        Uinv(3);

    if (dL[0] == "g")
        D(0);
    else if (dL[0] == "o")
        Di(3);
    else if (dL[0] == "b")
        D(6);
    else if (dL[0] == "r")
        D(3);
}

QStringList shortSolutionSQ(QStringList &list)
{
    // if list contains only (0, 0) (doesn't get removed in loop because condition doesn't allow
    // lists of length 1
    if (list.length() == 1 && list[0] == "(0, 0)")
        list[0] = "trash";

    // for every element in the list
    for (int i = 0; i < list.length() - 1; i++)
    {
        if (list[i] == "(0, 0)")
            list[i] = "trash";

        // if two consequitive list items don't have "/", then modify them
        if (list[i] != "trash" && list[i] != "/" && list[i + 1] != "/" && list[i + 1] != "trash")
        {
            QString item1 = list[i], item2 = list[i + 1];
            item1.remove(QChar('(')).remove(QChar(')')).remove(QChar(','));
            item2.remove(QChar('(')).remove(QChar(')')).remove(QChar(','));
            QStringList temp1 = item1.split(" "), temp2 = item2.split(" ");
            int x1, y1, x2, y2;

            if (temp1[0][0] == '-')
                x1 = 0 - temp1[0][1].digitValue();
            else
                x1 = temp1[0][0].digitValue();

            if (temp1[1][0] == '-')
                y1 = 0 - temp1[1][1].digitValue();
            else
                y1 = temp1[1][0].digitValue();

            if (temp2[0][0] == '-')
                x2 = 0 - temp2[0][1].digitValue();
            else
                x2 = temp2[0][0].digitValue();

            if (temp2[1][0] == '-')
                y2 = 0 - temp2[1][1].digitValue();
            else
                y2 = temp2[1][0].digitValue();

            list[i] = "trash";

            int x, y;

            if ((x1 + x2) > 6)
                x = (x1 + x2) - 12;
            else if ((x1 + x2) < -5)
                x = 12 + (x1 + x2);
            else
                x = x1 + x2;

            if ((y1 + y2) > 6)
                y = (y1 + y2) - 12;
            else if ((y1 + y2) < -5)
                y = 12 + (y1 + y2);
            else
                y = y1 + y2;

            list[i + 1] = "(" + QString::number(x) + ", " + QString::number(y) + ")";
        }
        else if (list[i] != "trash" && list[i] == "/" && list[i + 1] == "/")
        {
            list[i] = "trash";
            list[i + 1] = "trash";
        }
    }
    list.removeAll("trash"); // all trash values are removed
    return list;
}

// function that accepts a string and returns the move count as an integer
int findMoveCountSQ(QString &s)
{
    int mc = 0;
    for (int i = 0; i < s.length(); i++)
    {
        // move count is incremented every time an alphabet is encountered in the string
        if (s[i] == '/')
            mc++;
    }
    return mc;
}

void solveCubeSQ()
{

    perms.clear();
    solutionListSQ.clear();
    solutionSQ = "";
    moveCountSQ = 0;
    moveCountSQ_short = 0;

    cubeShape();
    solutionListSQ << "trash";

    CO();
    solutionListSQ << "trash";

    EO();
    solutionListSQ << "trash";

    CP();
    solutionListSQ << "trash";

    EP();
    finalAdjusts();

    /*if ( uFt == uF && dFt == dF && uLt == uL && dLt == dL)
        qDebug() << "Solved";
    else
        qDebug() << "NOT SOLVED";*/

    QList<int> ind;
    ind << 0;

    for (int i = 0; i < 4; i++)
        ind << solutionListSQ.indexOf("trash", ind[i]) + 1;

    QStringList cubeShape, co ,eo, cp, ep;

    for (int i = 0; i < solutionListSQ.length(); i++)
    {
        if (i < ind[1] - 1)
            cubeShape << solutionListSQ[i];
        else  if (i < ind[2] - 1 && i >= ind[1])
            co << solutionListSQ[i];
        else  if (i < ind[3] - 1 && i >= ind[2])
            eo << solutionListSQ[i];
        else  if (i < ind[4] - 1 && i >= ind[3])
            cp << solutionListSQ[i];
        else  if (i >= ind[4])
            ep << solutionListSQ[i];
    }

    for (int i = 0; i < 10; i++)
    {
        cubeShape = shortSolutionSQ(cubeShape);
        co = shortSolutionSQ(co);
        eo = shortSolutionSQ(eo);
        cp = shortSolutionSQ(cp);
        ep = shortSolutionSQ(ep);
    }

    // solution string stores the entire solution, formatted neatly and displays the solution in different steps
    solutionSQ = "CubeShape: " + cubeShape.join("") + '\n' + "CO: " + co.join("") + '\n' + "EO: " + eo.join("") + '\n' +
            "CP: " + cp.join("") + '\n' + "EP: " + ep.join("");

    QString solutionSQ_full = cubeShape.join("") + co.join("") + eo.join("") + cp.join("") + ep.join("");

    moveCountSQ = findMoveCountSQ(solutionSQ_full);

    // shortens the solution multiple times (20 is not required. Can be any number >= 1 )
    for (int i = 0; i < 20; i++)
    {
        solutionListSQ = shortSolutionSQ(solutionListSQ);
    }

    // Combines all elements of the solution array into one string
    solutionSQ_short = solutionListSQ.join("");

    moveCountSQ_short = findMoveCountSQ(solutionSQ_short);
}
