#include "../Header/pyra.h"
#include "../Header/scrambledialogpyra.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// External Variables //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/* "_scramble" variables contain the state of the cube after the scramble has been applied.
 * These are used to display the scrambled state using the "View Scramble" button
 * Used in scrambledialog.cpp
 */
extern QString yellowFaceP_scramble, greenFaceP_scramble, blueFaceP_scramble, orangeFaceP_scramble;

// variables used in solver.cpp
extern QString whiteFaceP, yellowFaceP, greenFaceP, blueFaceP, redFaceP, orangeFaceP; // current state variables
extern QString solutionP_short;
extern QString solutionP;
extern int moveCountP;
extern int moveCountP_short;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Internal Variables //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// "_gui" variables contain the state of the cube as defined by the user in the GUI
QString yellowFaceP_gui = "yyyyyyyyy", greenFaceP_gui = "ggggggggg",
            blueFaceP_gui = "bbbbbbbbb", orangeFaceP_gui = "ooooooooo";

// stores the scramble provided by the user in the "Scramble" field
QString scrambleP = "";

// stores the colour selected as a QColor variable
QColor colourSelectedP = QColor(0,0,0,50); //initial colour is the semi gray colour

// stores the colour specified by the stylesheet choice. Used to modify "_gui" variables
char colourP = 'x';

// stores the choice of the user for the radio button, 1 for GUI, P for scramble
int radioButtonInputP = 0;


/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Class Implementation //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

pyra::pyra(float a, float b, bool inv)
{
    isInverted = inv; // stores state of triangle

    // initializes cP so that GUI_check function can execute properly
    cP = 'x';

    // variables used to change the width and height of each triangle
    int dx = 40;
    int dy = 70;

    // alters the co-ordinates based on inv state
    if (inv)
    {
        x1 = a - dx;
        y1 = b;
        x2 = a + dx;
        y2 = y1;
        x3 = a;
        y3 = b + dy;
    }
    else
    {
        x1 = a;
        y1 = b;
        x2 = a + dx;
        y2 = b + dy;
        x3 = a - dx;
        y3 = y2;
    }

    // mouse is not being pressed initially
    isPressed = false;

    // copies global variable into class member
    sP = colourSelectedP;
}

QRectF pyra::boundingRect() const
{
    //returns bounding rect of either state of triangle
    if (isInverted)
        return QRectF(x1, y1, x2, y3);
    else
        return QRectF(x3, y1, x2, y3);
}

QPainterPath pyra::shape() const
{
    // overrides the shape function and returns a polygon (triangle) equal to the one created in the
    // paint function so that the interactable area is only inside the triangle

    QPolygonF poly;

    poly << QPointF(x1,y1) << QPointF(x2, y2) << QPointF(x3, y3);
    QPainterPath path;
    path.addPolygon(poly);
    return path;
}

void pyra::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    // creates the triangle
    QPolygonF poly;
    poly << QPointF(x1,y1) << QPointF(x2, y2) << QPointF(x3, y3);

    // creates a path to add the triangle (so that it can be filled)
    QPainterPath path;
    path.addPolygon(poly);

    // creates a brush and copies member sP which is initailly (0,0,0,50) from colourSelectedP
    QBrush brush(sP);

    // brush colour is changed according to the colour selected if mouse is pressed
    //if (isPressed)
        brush.setColor(sP);

    // pen is created
    QPen linepen;

    // same colour as brush so that there are no borders
    linepen.setColor(sP);
    if (isPressed)
        linepen.setColor(QColor(0,0,0,70));

    painter->setPen(linepen);

    // triangle is coloured
    painter->fillPath(path, brush);

    // triangle is drawn
    painter->drawPolygon(poly);
}

void pyra::updateState(QString state, QChar col = 'x')
{
    if (state == "clear")
    {
        // set sP to default gray colour
        sP = QColor(0,0,0,50);

        // set cP to default value
        cP = 'x';

        isPressed = false;
    }
    else if (state == "scramble")
    {
        if (col == 'g')
            sP = QColor(85,255,0,255);
        else if (col == 'y')
            sP = QColor(255,255,0,255);
        else if (col == 'o')
            sP = QColor(255,170,0,255);
        else if (col == 'b')
            sP = QColor(0,0,255,255);

        // to get border
        isPressed = true;
    }

    // update the drawing
    update();
}

void pyra::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // if mouse is pressed, store colourSelectedP in class member sP
    sP = colourSelectedP;

    // bool state changed so that paint function will change brush colour
    isPressed = true;

    // update the drawing
    update();

    // store the colour selected char variable colourP in class member cP
    cP = colourP;

    QGraphicsItem::mousePressEvent(event);
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// GUI Implementation //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/* This function checks if the colours applied to the cube layout in the GUI are valid.
 * Only if there are 9 of each colour, this function returns 1, otherwise 0.
 */
int GUICheck_P()
{
    QString GUIString = yellowFaceP_gui + greenFaceP_gui + blueFaceP_gui + orangeFaceP_gui;
    int y = 0, o = 0, g = 0, b = 0;

    for (int i = 0; GUIString[i] != '\0'; i++)
    {
        if (GUIString[i] == 'y')
            y++;
        else if (GUIString[i] == 'g')
            g++;
        else if (GUIString[i] == 'b')
            b++;
        else if (GUIString[i] == 'o')
            o++;
    }

    if (y == 9 && g == 9 && b == 9 && o == 9)
        return 1;
    return 0;
}

/* This function checks if the scramble inputted by the user is valid or not.
 * If it contains any move (string) other than the ones accepted (specified), it returns 0
 */
int scrambleCheck_P()
{
    QStringList scrambleList = scrambleP.split(" ");

    foreach(QString move, scrambleList)
    {
        if (move != "R" && move != "U" && move != "B" && move != "R'" && move != "U'" &&
                move != "B'" && move != "L" && move != "L'" && move != "r" && move != "u"
                && move != "b" && move != "r'" && move != "u'" &&
                move != "b'" && move != "l" && move != "l'" && move != " " && move != "")
            return 0;
    }
    return 1;
}



/////////////////////////// Class instance initialization ////////////////////////

void MainWindow::initpyr()
{
    // x is base length of triangle, y is height, g is gap and m alters x value for each face
    float x = 80, y = 69, g = 5, m = 5;

    // create a scene to add triangles to
    sceneP = new QGraphicsScene(this);

    // add scene to the graphicsView_P
    ui->graphicsView_P->setScene(sceneP);

    // for smooth lines
    ui->graphicsView_P->setRenderHint(QPainter::Antialiasing);

    // the rectangle encompassing the scene is the size of the bounding rectangle of the 4 faces
    sceneP->setSceneRect(0, 0, (9*x + 20*g), (6*y + 9*g));

    // orange face initialization
    o6 = new pyra(m + (1.5*x + 2*g), 2*g, false);
    sceneP->addItem(o6);

    o0 = new pyra(m + (x + g), (y + 3*g), false);
    sceneP->addItem(o0);

    o1 = new pyra(m + (1.5*x + 2*g), (y + 3*g), true);
    sceneP->addItem(o1);

    o2 = new pyra(m + (2*x + 3*g), (y + 3*g), false);
    sceneP->addItem(o2);

    o7 = new pyra(m + (0.5*x), (2*y + 4*g), false);
    sceneP->addItem(o7);

    o3 = new pyra(m + (x + g), (2*y + 4*g), true);
    sceneP->addItem(o3);

    o4 = new pyra(m + (1.5*x + 2*g), (2*y + 4*g), false);
    sceneP->addItem(o4);

    o5 = new pyra(m + (2*x + 3*g), (2*y + 4*g), true);
    sceneP->addItem(o5);

    o8 = new pyra(m + (2.5*x + 4*g), (2*y + 4*g), false);
    sceneP->addItem(o8);

    m += (3*x + 7*g);

    // green face initialization
    g6 = new pyra(m + (1.5*x + 2*g), 2*g, false);
    sceneP->addItem(g6);

    g0 = new pyra(m + (x + g), (y + 3*g), false);
    sceneP->addItem(g0);

    g1 = new pyra(m + (1.5*x + 2*g), (y + 3*g), true);
    sceneP->addItem(g1);

    g2 = new pyra(m + (2*x + 3*g), (y + 3*g), false);
    sceneP->addItem(g2);

    g7 = new pyra(m + (0.5*x), (2*y + 4*g), false);
    sceneP->addItem(g7);

    g3 = new pyra(m + (x + g), (2*y + 4*g), true);
    sceneP->addItem(g3);

    g4 = new pyra(m + (1.5*x + 2*g), (2*y + 4*g), false);
    sceneP->addItem(g4);

    g5 = new pyra(m + (2*x + 3*g), (2*y + 4*g), true);
    sceneP->addItem(g5);

    g8 = new pyra(m + (2.5*x + 4*g), (2*y + 4*g), false);
    sceneP->addItem(g8);

    // yellow face initialization
    y6 = new pyra(m + (0.5*x), (3*y + 6*g), true);
    sceneP->addItem(y6);

    y0 = new pyra(m + (x + g), (3*y + 6*g), false);
    sceneP->addItem(y0);

    y1 = new pyra(m + (1.5*x + 2*g), (3*y + 6*g), true);
    sceneP->addItem(y1);

    y2 = new pyra(m + (2*x + 3*g), (3*y + 6*g), false);
    sceneP->addItem(y2);

    y7 = new pyra(m + (2.5*x + 4*g), (3*y + 6*g), true);
    sceneP->addItem(y7);

    y3 = new pyra(m + (x + g), (4*y + 7*g), true);
    sceneP->addItem(y3);

    y4 = new pyra(m + (1.5*x + 2*g), (4*y + 7*g), false);
    sceneP->addItem(y4);

    y5 = new pyra(m + (2*x + 3*g), (4*y + 7*g), true);
    sceneP->addItem(y5);

    y8 = new pyra(m + (1.5*x + 2*g), (5*y + 8*g), true);
    sceneP->addItem(y8);

    m += (3*x + 7*g);

    // blue face initialization
    b6 = new pyra(m + (1.5*x + 2*g), 2*g, false);
    sceneP->addItem(b6);

    b0 = new pyra(m + (x + g), (y + 3*g), false);
    sceneP->addItem(b0);

    b1 = new pyra(m + (1.5*x + 2*g), (y + 3*g), true);
    sceneP->addItem(b1);

    b2 = new pyra(m + (2*x + 3*g), (y + 3*g), false);
    sceneP->addItem(b2);

    b7 = new pyra(m + (0.5*x), (2*y + 4*g), false);
    sceneP->addItem(b7);

    b3 = new pyra(m + (x + g), (2*y + 4*g), true);
    sceneP->addItem(b3);

    b4 = new pyra(m + (1.5*x + 2*g), (2*y + 4*g), false);
    sceneP->addItem(b4);

    b5 = new pyra(m + (2*x + 3*g), (2*y + 4*g), true);
    sceneP->addItem(b5);

    b8 = new pyra(m + (2.5*x + 4*g), (2*y + 4*g), false);
    sceneP->addItem(b8);
}

/////////////// Update GUI Variables /////////////////

// receives theGUI state inputted by the user
void MainWindow::udpateGUIVariables()
{
    blueFaceP_gui[0] = b0->cP;
    blueFaceP_gui[1] = b1->cP;
    blueFaceP_gui[2] = b2->cP;
    blueFaceP_gui[3] = b3->cP;
    blueFaceP_gui[4] = b4->cP;
    blueFaceP_gui[5] = b5->cP;
    blueFaceP_gui[6] = b6->cP;
    blueFaceP_gui[7] = b7->cP;
    blueFaceP_gui[8] = b8->cP;

    greenFaceP_gui[0] = g0->cP;
    greenFaceP_gui[1] = g1->cP;
    greenFaceP_gui[2] = g2->cP;
    greenFaceP_gui[3] = g3->cP;
    greenFaceP_gui[4] = g4->cP;
    greenFaceP_gui[5] = g5->cP;
    greenFaceP_gui[6] = g6->cP;
    greenFaceP_gui[7] = g7->cP;
    greenFaceP_gui[8] = g8->cP;

    orangeFaceP_gui[0] = o0->cP;
    orangeFaceP_gui[1] = o1->cP;
    orangeFaceP_gui[2] = o2->cP;
    orangeFaceP_gui[3] = o3->cP;
    orangeFaceP_gui[4] = o4->cP;
    orangeFaceP_gui[5] = o5->cP;
    orangeFaceP_gui[6] = o6->cP;
    orangeFaceP_gui[7] = o7->cP;
    orangeFaceP_gui[8] = o8->cP;

    yellowFaceP_gui[0] = y0->cP;
    yellowFaceP_gui[1] = y1->cP;
    yellowFaceP_gui[2] = y2->cP;
    yellowFaceP_gui[3] = y3->cP;
    yellowFaceP_gui[4] = y4->cP;
    yellowFaceP_gui[5] = y5->cP;
    yellowFaceP_gui[6] = y6->cP;
    yellowFaceP_gui[7] = y7->cP;
    yellowFaceP_gui[8] = y8->cP;
}


////////////////////////////////////// Choice button commands /////////////////////////////////////////

/* When these buttons are clicked (top right corner in window), the style sheet string, s is set to
 * the CSS string for that specific colour. Also the "colour" variable stores that respective colour.
 */

void MainWindow::on_cy_P_clicked()
{
    colourSelectedP.setRgb(255,255,0,255);
    colourP = 'y';
}

void MainWindow::on_cg_P_clicked()
{
    colourSelectedP.setRgb(85,255,0,255);
    colourP = 'g';
}

void MainWindow::on_cb_P_clicked()
{
    colourSelectedP.setRgb(0,0,255,255);
    colourP = 'b';
}

void MainWindow::on_co_P_clicked()
{
    colourSelectedP.setRgb(255,170,0,255);
    colourP = 'o';
}

////////////////////////////////////// Other GUI elements //////////////////////////////////////

///// Radio Buttons /////

//stores the choice of the user as an integer
void MainWindow::on_GUIInputButton_P_clicked()
{
    radioButtonInputP = 1;
}

void MainWindow::on_scrambleInputButton_P_clicked()
{
    radioButtonInputP = 2;
}
////// Solve Button //////

void MainWindow::on_solveButton_P_clicked()
{
    udpateGUIVariables();
    ui->shortSolutionButton_P->setChecked(false);

    // If the scramble input radio button is selected AND the scramble is valid,
    if (radioButtonInputP == 2 && scrambleCheck_P())
    {
        if (scrambleP == "")
        {
            solutionP = "No scramble found";
            moveCountP = 0;
        }
        else
        {
            // restore the current state variables to a solved state
            yellowFaceP = "yyyyyyyyy";
            greenFaceP = "ggggggggg";
            blueFaceP = "bbbbbbbbb";
            orangeFaceP = "ooooooooo";

            // scramble the cube based on the inputted scramble
            convertScrambleP(scrambleP);

            // and solve the cube
            solveCubePyra();
        }
    }
    // else if the GUI input radio button is selected and the GUI is valid,
    else if (radioButtonInputP == 1 && GUICheck_P())
    {
        // update the current state variables to the state provided by the GUI
        yellowFaceP = yellowFaceP_gui;
        orangeFaceP = orangeFaceP_gui;
        greenFaceP = greenFaceP_gui;
        blueFaceP = blueFaceP_gui;

        // and solve the cube
        solveCubePyra();
    }
    // else if no radio button is selected, throw error
    else if (radioButtonInputP == 0)
    {
        solutionP = "Input Method not selected";
        moveCountP = 0;
    }
    // else if any of the above check functions return 0, display error message
    else
    {
        solutionP = "No solution possible. Please retry with proper scramble/colours.";
        moveCountP = 0;
    }

    ui->movesLabel_P->setText(solutionP); // set the movesLabel to display the solution
    ui->movesLabel_P->setWordWrap(true); // enable word wrap for the movesLabel
    ui->moveCountLabel_P->setText(QString::number(moveCountP)); // display the move count as an integer

    // if a shorter solution exists (determined by solveCube function)
    if (moveCountP_short < moveCountP)
    {
        // change the text of the shortSolution check box
        QString shortSolutionButtonText = "View " + QString::number(moveCountP_short) + " move solution";
        // set the movesLabel text to the shorter solution
        ui->shortSolutionButton_P->setText(shortSolutionButtonText);
        // make the shortSolution checkbox visible
        ui->shortSolutionButton_P->setVisible(true);
    }
    // else if no shorter solution exists
    else
        // make the shortSolution check box invisible
        ui->shortSolutionButton_P->setVisible(false);
}


/////////////// Clear Button //////////////////

//sets all GUI elements to default position
void MainWindow::on_clearButton_P_clicked()
{
    o0->updateState("clear");
    o1->updateState("clear");
    o2->updateState("clear");
    o3->updateState("clear");
    o4->updateState("clear");
    o5->updateState("clear");
    o6->updateState("clear");
    o7->updateState("clear");
    o8->updateState("clear");

    g0->updateState("clear");
    g1->updateState("clear");
    g2->updateState("clear");
    g3->updateState("clear");
    g4->updateState("clear");
    g5->updateState("clear");
    g6->updateState("clear");
    g7->updateState("clear");
    g8->updateState("clear");

    y0->updateState("clear");
    y1->updateState("clear");
    y2->updateState("clear");
    y3->updateState("clear");
    y4->updateState("clear");
    y5->updateState("clear");
    y6->updateState("clear");
    y7->updateState("clear");
    y8->updateState("clear");

    b0->updateState("clear");
    b1->updateState("clear");
    b2->updateState("clear");
    b3->updateState("clear");
    b4->updateState("clear");
    b5->updateState("clear");
    b6->updateState("clear");
    b7->updateState("clear");
    b8->updateState("clear");

    // re-initialize all  internal variables
    yellowFaceP_gui = "yyyyyyyyy", greenFaceP_gui = "ggggggggg",
                blueFaceP_gui = "bbbbbbbbb", orangeFaceP_gui = "ooooooooo";

    colourSelectedP = QColor(0,0,0,50);
    radioButtonInputP = 0;
    colourP = 'x';
    scrambleP = "";

    // set all labels and text field to display nothing
    ui->scrambleLineEdit_P->setText("");
    ui->movesLabel_P->setText("");
    ui->moveCountLabel_P->setText("");

    // set autoexclusivity to false so that the radio butons can be un-checked
    ui->scrambleInputButton_P->setAutoExclusive(false);
    ui->GUIInputButton_P->setAutoExclusive(false);

    // uncheck both radio buttons
    ui->scrambleInputButton_P->setChecked(false);
    ui->GUIInputButton_P->setChecked(false);

    // set autoexclusivity back to true
    ui->scrambleInputButton_P->setAutoExclusive(true);
    ui->GUIInputButton_P->setAutoExclusive(true);

    // make the shortSolution check box invisible
    ui->shortSolutionButton_P->setVisible(false);
}

//////////////// Scramble Field ///////////////////////

// if the position of the cursor changes, "scramble" variable stores the string in the field
void MainWindow::on_scrambleLineEdit_P_cursorPositionChanged()
{
    scrambleP = ui->scrambleLineEdit_P->text();
}

// if "return" key is pressed when cursor is focused on the scramble field
void MainWindow::on_scrambleLineEdit_P_returnPressed()
{
    // "Scramble Input" radio button click is simulated
    MainWindow::on_scrambleInputButton_P_clicked();

    // "Scramble Input" radio button is checked
    ui->scrambleInputButton_P->setChecked(true);

    // "Solve Button" click is simulated
    MainWindow::on_solveButton_P_clicked();
}

//////////////////// shortSolution Button //////////////////////

void MainWindow::on_shortSolutionButton_P_toggled(bool checked)
{
    if (checked)
    {
        ui->movesLabel_P->setText(solutionP_short); // sets movesLabel to the shorter solution
        ui->movesLabel_P->setWordWrap(true);
        ui->moveCountLabel_P->setText(QString::number(moveCountP_short)); // sets moveCountLabel to the shorter move count
        QString shortSolutionButtonText = "View " + QString::number(moveCountP) + " move solution";
        ui->shortSolutionButton_P->setText(shortSolutionButtonText); // alters button text to the above QString
    }
    else
    {
        ui->movesLabel_P->setText(solutionP); // sets movesLabel to the original solution
        ui->movesLabel_P->setWordWrap(true);
        ui->moveCountLabel_P->setText(QString::number(moveCountP)); // sets moveCountLabel to the original move count
        QString shortSolutionButtonText = "View " + QString::number(moveCountP_short) + " move solution";
        ui->shortSolutionButton_P->setText(shortSolutionButtonText); // alters button text to the above QString
    }
}

////////////////////////// View Scramble Button /////////////////////////////////

void MainWindow::on_viewScrambleButton_P_clicked()
{
    // if "Scramble" field has some text AND if the text is a valid scramble,
    if (ui->scrambleLineEdit_P->text() != "" && scrambleCheck_P())
    {
        // restore the current state variables to solved state
        yellowFaceP = "yyyyyyyyy";
        greenFaceP = "ggggggggg";
        blueFaceP = "bbbbbbbbb";
        orangeFaceP = "ooooooooo";

        // scramble the cube according to the string in the "Scramble" field
        convertScrambleP(scrambleP);

        // creates a new dialog from scrambleDialog class and opens it
        scrambleDialogPyra scrambledialogpyra;
        scrambledialogpyra.setModal(true); // Modal approach denies the user to interact with both windows at the same time
        scrambledialogpyra.exec(); // executes the scrambleDialog which is defined in scrambledialog.cpp

    }
    // else if there is no text in the field or if the text is an invalid scramble
    else
        // throw error
        ui->movesLabel_P->setText("Invalid Scramble");
}

//////////////////////// Provide Scramble Button //////////////////////////////////

QString scrambleString_P()
{
    QStringList set, mod;
    QString s;
    set << "R" << "B" << "U" << "L" << "r" << "b" << "u" << "l";
    mod << "" << "'";

    int low = 0, high1 = 3, high2 = 1, m, n, checker;

    for (int i = 0; i < 10; i++)
    {
        do
        {
            m =  qrand() % ((high1 + 1) - low) + low;
            n =  qrand() % ((high2 + 1) - low) + low;
        }
        while(m == checker);

        s += set[m] + mod[n] + " ";

        checker = m;
    }

    int low1 = 4;
    high1 = 7;
    checker = 3;

    for (int i = 0; i < 4; i++)
    {
        do
        {
            m =  qrand() % ((high1 + 1) - low1) + low1;
            n =  qrand() % ((high2 + 1) - low) + low;
        }
        while(m == checker);

        if (m % 2 == 1)
        {
            s += set[m] + mod[n] + " ";
            checker = m;
        }
    }
    return s;
}

void MainWindow::on_provideScrambleButton_P_clicked()
{
    ui->scrambleLineEdit_P->setText(scrambleString_P());
}
