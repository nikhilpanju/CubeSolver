#include "ui_mainwindow.h"
#include "solversq.h"
#include "mainwindow.h"
#include "sq1.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// External Variables //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/* "_scramble" variables contain the state of the cube after the scramble has been applied.
 * These are used to display the scrambled state using the "View Scramble" button
 * Used in scrambledialog.cpp
 */
//extern QString whiteFace_scramble, yellowFace_scramble, greenFace_scramble,
                //blueFace_scramble, redFace_scramble, orangeFace_scramble;

// variables used in solversq.cpp
extern QStringList uF, uL, dF, dL; // current state variables
extern QStringList uF_cP, dF_cP, uL_cP, dL_cP;
extern QString solutionSQ_short;
extern QString solutionSQ;
extern int moveCountSQ;
extern int moveCountSQ_short;
extern bool trialSQ;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Internal Variables //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// "_gui" variables contain the state of the cube as defined by the user in the GUI
QStringList uF_gui, dF_gui, uL_gui, dL_gui;

// stores the scramble provided by the user in the "Scramble" field
QString scrambleSQ = "";

// stores the stylesheet string used to modify the colours of the cube layout
//QString s = ("background-color: rgba(0, 0, 0, 50);");

// stores the colour specified by the stylesheet choice. Used to modify "_gui" variables
//char colour = 'x';

// stores the choice of the user for the radio button, 1 for GUI, 2 for scramble
int radioButtonInputSQ = 0;


/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Class Implementation //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

sq1::sq1(QString str, int offset, int lay, QStringList face)
{
    layer = lay;

    brushColourFace = setBrushColour(str[0]);

    blockSize = str[1].digitValue();
    angleModifier = offset;

    int baseSize = 35;
    x1 = 0;
    y1 = 0;

    if (blockSize == 2)
    {
        brushColourLayer = setBrushColour(face[offset][0]);
        brushColourLayer1 = setBrushColour(face[offset + 1][0]);

        x2 = - baseSize;
        y2 = - (1.72 * baseSize);
        x3 = 0;
        y3 =  - (2.71 * baseSize);
        x4 = - x2;
        y4 = y2;

        x5 = - (((10 - y2) * baseSize) / (-y2));
        y5 = y2 - 8.5;
        x6 = - (((20 - y2) * baseSize) / (-y2));
        y6 = y2 - 17;
        x7 = x3;
        y7 = y3 - 28.28;
        x8 = x3;
        y8 = y3 - 14.14;
        x9 = - x6;
        y9 = y6;
        x10 = - x5;
        y10 = y5;
    }
    else
    {
        brushColourLayer = setBrushColour(face[offset][0]);

        x2 = - (baseSize / 1.95);
        y2 = - (1.922 * baseSize);
        x3 = - x2;
        y3 = y2;

        x5  =  - ((10 - y2) * baseSize) / (1.95 * (-y2));
        y5 = y2 - 10;
        x6 = - ((20 - y2) * baseSize) / (1.95 * (-y2));
        y6 = y2 - 20;
        x7 = - x6;
        y7 = y6;
        x8 =  - x5;
        y8 = y5;

    }
}

QRectF sq1::boundingRect() const
{
    if (blockSize == 2)
        return QRectF(x1, y1, x3, y3);
    else
        return QRectF(x1, y1, x3, y3);
}


QPainterPath sq1::shape() const
{
    // overrides the shape function and returns a polygon (triangle) equal to the one created in the
    // paint function so that the interactable area is only inside the triangle

    QPolygonF poly;

    if (blockSize == 2)
        poly << QPointF(x1,y1) << QPointF(x2, y2) << QPointF(x3, y3) << QPointF(x4, y4);
    else
        poly << QPointF(x1,y1) << QPointF(x2, y2) << QPointF(x3, y3);

    QPainterPath path;
    path.addPolygon(poly);

    return path;
}

void sq1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // pen is created
    QPen linepen(QColor(0,0,0,255));

    // set colour to black and width as 3
    linepen.setWidth(3);

    // set linpen to painter
    painter->setPen(linepen);

    int mod = 30;

    if (layer == 1)
        mod = 0;

    // rotates polygon based on angleModifier
    if (blockSize == 2)
    {
        QPolygonF poly, poly1, poly2;

        poly << QPointF(x1,y1) << QPointF(x2, y2) << QPointF(x3, y3) << QPointF(x4, y4);
        poly1 << QPointF(x5, y5) << QPointF(x6, y6) << QPointF(x7, y7) << QPointF(x8, y8);
        poly2 << QPointF(x8, y8) << QPointF(x7, y7) << QPointF(x9, y9) << QPointF(x10, y10);

        QPainterPath path, path1, path2;
        path.addPolygon(poly);
        path1.addPolygon(poly1);
        path2.addPolygon(poly2);

        // creates a brush and copies member sP which is initailly (0,0,0,50) from colourSelectedP
        QBrush brush(brushColourFace);
        QBrush brush1(brushColourLayer);
        QBrush brush2(brushColourLayer1);

        painter->rotate((angleModifier * 30) + mod + 15);

        // polygon is coloured
        painter->fillPath(path, brush);
        painter->fillPath(path1, brush1);
        painter->fillPath(path2, brush2);

        // polygon is drawn
        painter->drawPolygon(poly);
        painter->drawPolygon(poly1);
        painter->drawPolygon(poly2);
    }
    else
    {
        QPolygonF poly, poly1;

        poly << QPointF(x1,y1) << QPointF(x2, y2) << QPointF(x3, y3);
        poly1 << QPointF(x5, y5) << QPointF(x6, y6) << QPointF(x7, y7) << QPointF(x8, y8);

        QPainterPath path, path1;
        path.addPolygon(poly);
        path1.addPolygon(poly1);

        // creates a brush and copies member sP which is initailly (0,0,0,50) from colourSelectedP
        QBrush brush(brushColourFace);
        QBrush brush1(brushColourLayer);

        painter->rotate((angleModifier * 30) + mod);

        // polygon is coloured
        painter->fillPath(path, brush);
        painter->fillPath(path1, brush1);

        // polygon is drawn
        painter->drawPolygon(poly);
        painter->drawPolygon(poly1);
    }
}

QColor sq1::setBrushColour(QChar c)
{
    if (c == 'w')
        return QColor(255,255,255,255);
    else if (c == 'y')
        return QColor(255,255,0,255);
    else if (c == 'g')
        return QColor(85,255,0,255);
    else if (c == 'r')
        return QColor(255,0,0,255);
    else if (c == 'b')
        return QColor(0,0,255,255);
    else if (c == 'o')
        return QColor(255,170,0,255);

    return QColor(0, 0, 0, 255); // error
}

///////////// Class instance initializations /////////////////

void MainWindow::initSQ1()
{
    int m = 0;
    float x = 35;
    QString temp;

    uF_gui.clear();
    dF_gui.clear();
    uL_gui.clear();
    dL_gui.clear();

    // restore the current state variables to a solved state
    uF.clear();
    uL.clear();
    dF.clear();
    dL.clear();

    uF << "w2" << "w1" << "w2" << "w1" << "w2" << "w1" << "w2" << "w1";
    dF << "y1" << "y2" << "y1" << "y2" << "y1" << "y2" << "y1" << "y2";
    uL << "b" << "r" << "r" << "r" << "g" << "g" << "g" << "o" << "o"
       << "o" << "b" << "b";
    dL << "g" << "g" << "r" << "r" << "r" << "b" << "b" << "b"
       << "o" << "o" << "o" << "g";

    // scramble the cube based on the inputted scramble
    trialSQ = true; //trial is used because convertString is used by many functions
    convertString(scrambleSQ, 1);
    trialSQ = false;

    sceneSQ_dF->clear();
    sceneSQ_uF->clear();
    sceneSQ_eL->clear();


    ////////// U Face //////////////

    uf0 = new sq1(uF_gui[0], m, 0, uL_gui);
    sceneSQ_uF->addItem(uf0);
    temp = uF_gui[0];
    m += temp[1].digitValue();

    uf1 = new sq1(uF_gui[1], m, 0, uL_gui);
    sceneSQ_uF->addItem(uf1);
    temp = uF_gui[1];
    m += temp[1].digitValue();

    uf2 = new sq1(uF_gui[2], m, 0, uL_gui);
    sceneSQ_uF->addItem(uf2);
    temp = uF_gui[2];
    m += temp[1].digitValue();

    uf3 = new sq1(uF_gui[3], m, 0, uL_gui);
    sceneSQ_uF->addItem(uf3);
    temp = uF_gui[3];
    m += temp[1].digitValue();

    uf4 = new sq1(uF_gui[4], m, 0, uL_gui);
    sceneSQ_uF->addItem(uf4);
    temp = uF_gui[4];
    m += temp[1].digitValue();

    uf5 = new sq1(uF_gui[5], m, 0, uL_gui);
    sceneSQ_uF->addItem(uf5);
    temp = uF_gui[5];
    m += temp[1].digitValue();

    if (uF_gui.length() > 6)
    {
        uf6 = new sq1(uF_gui[6], m, 0, uL_gui);
        sceneSQ_uF->addItem(uf6);
        temp = uF_gui[6];
        m += temp[1].digitValue();
    }
    if (uF_gui.length() > 7)
    {
        uf7 = new sq1(uF_gui[7], m, 0, uL_gui);
        sceneSQ_uF->addItem(uf7);
        temp = uF_gui[7];
        m += temp[1].digitValue();
    }
    if (uF_gui.length() > 8)
    {
        uf8 = new sq1(uF_gui[8], m, 0, uL_gui);
        sceneSQ_uF->addItem(uf8);
        temp = uF_gui[8];
        m += temp[1].digitValue();
    }
    if (uF_gui.length() > 9)
    {
        uf9 = new sq1(uF_gui[9], m, 0, uL_gui);
        sceneSQ_uF->addItem(uf9);
    }

    m = 0;

    ////////// D Face //////////////

    df0 = new sq1(dF_gui[0], m, 1, dL_gui);
    sceneSQ_dF->addItem(df0);
    temp = dF_gui[0];
    m += temp[1].digitValue();

    df1 = new sq1(dF_gui[1], m, 1, dL_gui);
    sceneSQ_dF->addItem(df1);
    temp = dF_gui[1];
    m += temp[1].digitValue();

    df2 = new sq1(dF_gui[2], m, 1, dL_gui);
    sceneSQ_dF->addItem(df2);
    temp = dF_gui[2];
    m += temp[1].digitValue();

    df3 = new sq1(dF_gui[3], m, 1, dL_gui);
    sceneSQ_dF->addItem(df3);
    temp = dF_gui[3];
    m += temp[1].digitValue();

    df4 = new sq1(dF_gui[4], m, 1, dL_gui);
    sceneSQ_dF->addItem(df4);
    temp = dF_gui[4];
    m += temp[1].digitValue();

    df5 = new sq1(dF_gui[5], m, 1, dL_gui);
    sceneSQ_dF->addItem(df5);
    temp = dF_gui[5];
    m += temp[1].digitValue();

    if (dF_gui.length() > 6)
    {
        df6 = new sq1(dF_gui[6], m, 1, dL_gui);
        sceneSQ_dF->addItem(df6);
        temp = dF_gui[6];
        m += temp[1].digitValue();
    }
    if (dF_gui.length() > 7)
    {
        df7 = new sq1(dF_gui[7], m, 1, dL_gui);
        sceneSQ_dF->addItem(df7);
        temp = dF_gui[7];
        m += temp[1].digitValue();
    }
    if (dF_gui.length() > 8)
    {
        df8 = new sq1(dF_gui[8], m, 1, dL_gui);
        sceneSQ_dF->addItem(df8);
        temp = dF_gui[8];
        m += temp[1].digitValue();
    }
    if (dF_gui.length() > 9)
    {
        df9 = new sq1(dF_gui[9], m, 1, dL_gui);
        sceneSQ_dF->addItem(df9);
    }

    sceneSQ_uF->update(-(2.71 * x) - 28.28, -(2.71 * x) - 28.28,
                       ((2.71 * x) + 28.28) * 2, ((2.71 * x) + 28.28) * 2);
    sceneSQ_dF->update(-(2.71 * x) - 28.28, -(2.71 * x) - 28.28,
                       ((2.71 * x) + 28.28) * 2, ((2.71 * x) + 28.28) * 2);
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// GUI Implementation //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
///
/* This function checks if the scramble inputted by the user is valid or not.
 * If it contains any move (string) other than the ones accepted (specified), it returns 0
 */
int scrambleCheck_SQ()
{
    QStringList scrambleList = scrambleSQ.split("/", QString::SkipEmptyParts);

    foreach(QString move, scrambleList)
    {
        int len = move.length();

        if(len == 6 && (move[0] != '(' || move[1].digitValue() == -1 || move[2] != ',' || move[3] != ' '
                || move[4].digitValue() == -1 || move[5] != ')'))
            return 0;

        if(len == 7 && (move[0] != '(' || move[1].digitValue() == -1 || move[2] != ',' || move[3] != ' '
                || move[4] != '-' || move[5].digitValue() == -1 || move[6] != ')'))

            if(len == 7 && (move[0] != '(' || move[1] != '-' || move[2].digitValue() == -1 || move[3] != ','
                || move[4] != ' ' || move[5].digitValue() == -1 || move[6] != ')'))

                return 0;

        if(len == 8 && (move[0] != '(' || move[1] != '-' || move[2].digitValue() == -1 || move[3] != ','
                || move[4] != ' '  || move[5] != '-' || move[6].digitValue() == -1 || move[7] != ')'))
            return 0;
        if (len > 8 || len < 6)
            return 0;
    }
    return 1;
}

////////////////////////////////////// Other GUI elements //////////////////////////////////////

///// Radio Buttons /////

//stores the choice of the user as an integer
void MainWindow::on_GUIInputButton_SQ_clicked()
{
    radioButtonInputSQ = 1;
}

void MainWindow::on_scrambleInputButton_SQ_clicked()
{
    radioButtonInputSQ = 2;
}
////// Solve Button //////

void MainWindow::on_solveButton_SQ_clicked()
{
    ui->shortSolutionButton_SQ->setChecked(false);
    //scrambleSQ = ui->scrambleLineEdit_SQ->toPlainText();

    // If the scramble input radio button is selected AND the scramble is valid,
    if (radioButtonInputSQ == 2 && scrambleCheck_SQ())
    {
        if (scrambleSQ == "")
        {
            solutionSQ = "No scramble found";
            moveCountSQ = 0;
        }
        else
        {
            // restore the current state variables to a solved state
            uF.clear();
            uL.clear();
            dF.clear();
            dL.clear();

            uF << "w2" << "w1" << "w2" << "w1" << "w2" << "w1" << "w2" << "w1";
            dF << "y1" << "y2" << "y1" << "y2" << "y1" << "y2" << "y1" << "y2";
            uL << "b" << "r" << "r" << "r" << "g" << "g" << "g" << "o" << "o"
               << "o" << "b" << "b";
            dL << "g" << "g" << "r" << "r" << "r" << "b" << "b" << "b"
               << "o" << "o" << "o" << "g";

            // scramble the cube based on the inputted scramble
            trialSQ = true; //trial is used because convertString is used by many functions
            convertString(scrambleSQ);
            trialSQ = false;


            // and solve the cube
            solveCubeSQ();

        }
    }
    /*
    // else if the GUI input radio button is selected and the GUI is valid,
    else if (radioButtonInput2 == 1 && GUICheck_2())
    {
        // update the current state variables to the state provided by the GUI
        whiteFace2 = whiteFace2_gui;
        yellowFace2 = yellowFace2_gui;
        redFace2 = redFace2_gui;
        orangeFace2 = orangeFace2_gui;
        greenFace2 = greenFace2_gui;
        blueFace2 = blueFace2_gui;

        // and solve the cube
        solveCube2x2();
    }
    */
    // else if no radio button is selected, throw error
    else if (radioButtonInputSQ == 0)
    {
        solutionSQ = "Input Method not selected";
        moveCountSQ = 0;
    }
    // else if either of the two check functions return 0, display error message
    else
    {
        solutionSQ = "No solution possible. Please retry with proper scramble/colours.";
        moveCountSQ = 0;
    }

    ui->movesLabel_SQ->setText(solutionSQ); // set the movesLabel to display the solution
    ui->movesLabel_SQ->setWordWrap(true); // enable word wrap for the movesLabel
    ui->moveCountLabel_SQ->setText(QString::number(moveCountSQ)); // display the move count as an integer

    // if a shorter solution exists (determined by solveCube function)
    if (moveCountSQ_short < moveCountSQ)
    {
        // change the text of the shortSolution check box
        QString shortSolutionButtonText = "View " + QString::number(moveCountSQ_short) + " move solution";
        // set the movesLabel text to the shorter solution
        ui->shortSolutionButton_SQ->setText(shortSolutionButtonText);
        // make the shortSolution checkbox visible
        ui->shortSolutionButton_SQ->setVisible(true);
    }
    // else if no shorter solution exists
    else
        // make the shortSolution check box invisible
        ui->shortSolutionButton_SQ->setVisible(false);
}

//////////////// Scramble Field ///////////////////////

// if the position of the cursor changes, "scramble" variable stores the string in the field
void MainWindow::on_scrambleLineEdit_SQ_cursorPositionChanged()
{
    scrambleSQ = ui->scrambleLineEdit_SQ->toPlainText();

    //if (scrambleCheck_SQ())
        initSQ1();
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->scrambleLineEdit_SQ && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            // get text from textedit
            scrambleSQ = ui->scrambleLineEdit_SQ->toPlainText();

            // "Scramble Input" radio button click is simulated
            MainWindow::on_scrambleInputButton_SQ_clicked();

            // "Scramble Input" radio button is checked
            ui->scrambleInputButton_SQ->setChecked(true);

            // "Solve Button" click is simulated
            MainWindow::on_solveButton_SQ_clicked();

            return true;
        }
        else
            return QMainWindow::eventFilter(object, event);
    }
    else
        return QMainWindow::eventFilter(object, event);
}

//////////////////// shortSolution Button //////////////////////

void MainWindow::on_shortSolutionButton_SQ_toggled(bool checked)
{
    if (checked)
    {
        ui->movesLabel_SQ->setText(solutionSQ_short); // sets movesLabel to the shorter solution
        ui->movesLabel_SQ->setWordWrap(true);
        ui->moveCountLabel_SQ->setText(QString::number(moveCountSQ_short)); // sets moveCountLabel to the shorter move count
        QString shortSolutionButtonText = "View " + QString::number(moveCountSQ) + " move solution";
        ui->shortSolutionButton_SQ->setText(shortSolutionButtonText); // alters button text to the above QString
    }
    else
    {
        ui->movesLabel_SQ->setText(solutionSQ); // sets movesLabel to the original solution
        ui->movesLabel_SQ->setWordWrap(true);
        ui->moveCountLabel_SQ->setText(QString::number(moveCountSQ)); // sets moveCountLabel to the original move count
        QString shortSolutionButtonText = "View " + QString::number(moveCountSQ_short) + " move solution";
        ui->shortSolutionButton_SQ->setText(shortSolutionButtonText); // alters button text to the above QString
    }
}

//////////////////////// Provide Scramble Button //////////////////////////////////

bool checkIfSquare(int u, int d)
{
    createCheckpointSQ();

    trialSQ = true;
    QString s = "(" + QString::number(u) + ", " + QString::number(d) + ")/";
    convertString(s);
    trialSQ = false;

    if (((uF[0][1] == '2' && uF[1][1] == '1' && uF[2][1] == '2' && uF[3][1] == '1' &&
            uF[4][1] == '2' && uF[5][1] == '1' && uF[6][1] == '2' && uF[7][1] == '1') ||
            (uF[0][1] == '1' && uF[1][1] == '2' && uF[2][1] == '1' && uF[3][1] == '2' &&
             uF[4][1] == '1' && uF[5][1] == '2' && uF[6][1] == '1' && uF[7][1] == '2')) &&
            ((dF[0][1] == '2' && dF[1][1] == '1' && dF[2][1] == '2' && dF[3][1] == '1' &&
                        dF[4][1] == '2' && dF[5][1] == '1' && dF[6][1] == '2' && dF[7][1] == '1') ||
                        (dF[0][1] == '1' && dF[1][1] == '2' && dF[2][1] == '1' && dF[3][1] == '2' &&
                         dF[4][1] == '1' && dF[5][1] == '2' && dF[6][1] == '1' && dF[7][1] == '2')))
        return true;
    else
    {
        resetLocationSQ();
        return false;
    }
}

QString scrambleString_SQ()
{

    uF.clear();
    uL.clear();
    dF.clear();
    dL.clear();

    uF << "w2" << "w1" << "w2" << "w1" << "w2" << "w1" << "w2" << "w1";
    dF << "y1" << "y2" << "y1" << "y2" << "y1" << "y2" << "y1" << "y2";
    uL << "b" << "r" << "r" << "r" << "g" << "g" << "g" << "o" << "o"
       << "o" << "b" << "b";
    dL << "g" << "g" << "r" << "r" << "r" << "b" << "b" << "b"
       << "o" << "o" << "o" << "g";


    QString s = "", s_temp;
    int slashes = qrand() % 4 + 11;
    int stayInSquare = qrand() % 3 + 4;

    int m, n;

    for (int i = 0; i < slashes; i++)
    {
        if (i < stayInSquare)
        {
            do
            {
                do
                {
                    m =  qrand() % 12 - 5;
                }while(!possibleNRotate(uF, m));

                do
                {
                    n =  qrand() % 12 - 5;
                }while(!possibleNRotate(dF, n));
            }
            while(!checkIfSquare(m, n) || (m == 0 && n == 0) || (m == 6 && n == 6));
        }
        else
        {
            do
            {
                do
                {
                    m =  qrand() % 12 - 5;
                }while(!possibleNRotate(uF, m));

                do
                {
                    n =  qrand() % 12 - 5;
                }while(!possibleNRotate(dF, n));
            }
            while((m == 0 && n == 0) || (m == 6 && n == 6));
        }

        s += "(" + QString::number(m) + ", " + QString::number(n) + ")/";
        trialSQ = true;
        s_temp = "(" + QString::number(m) + ", " + QString::number(n) + ")/";
        convertString(s_temp);
        trialSQ = false;
    }
    return s;
}

void MainWindow::on_provideScrambleButton_SQ_clicked()
{
    ui->scrambleLineEdit_SQ->setPlainText(scrambleString_SQ());
}


