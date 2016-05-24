#include "ui_mainwindow.h"
#include "scrambledialog.h"
#include "solver.h"
#include "mainwindow.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// External Variables //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/* "_scramble" variables contain the state of the cube after the scramble has been applied.
 * These are used to display the scrambled state using the "View Scramble" button
 * Used in scrambledialog.cpp
 */
extern QString whiteFace_scramble, yellowFace_scramble, greenFace_scramble,
                blueFace_scramble, redFace_scramble, orangeFace_scramble;

// variables used in solver.cpp
extern QString whiteFace, yellowFace, greenFace, blueFace, redFace, orangeFace; // current state variables
extern QString solution_short;
extern QString solution;
extern int moveCount;
extern int moveCount_short;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Internal Variables //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// "_gui" variables contain the state of the cube as defined by the user in the GUI
QString whiteFace_gui = "wwwwwwwww", yellowFace_gui = "yyyyyyyyy", greenFace_gui = "ggggggggg",
            blueFace_gui = "bbbbbbbbb", redFace_gui = "rrrrrrrrr", orangeFace_gui = "ooooooooo";

// stores the scramble provided by the user in the "Scramble" field
QString scramble = "";

// stores the stylesheet string used to modify the colours of the cube layout
QString s = ("background-color: rgba(0, 0, 0, 50);");

// stores the colour specified by the stylesheet choice. Used to modify "_gui" variables
char colour = 'x';

// stores the choice of the user for the radio button, 1 for GUI, 2 for scramble
int radioButtonInput = 0;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// GUI Implementation //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/* This function checks if the colours applied to the cube layout in the GUI are valid.
 * Only if there are 9 of each colour, this function returns 1, otherwise 0.
 */
int GUICheck()
{
    QString GUIString = whiteFace_gui + yellowFace_gui + greenFace_gui
                        + blueFace_gui + redFace_gui + orangeFace_gui;
    int w = 0, y = 0, r = 0, o = 0, g = 0, b = 0;

    for (int i = 0; GUIString[i] != '\0'; i++)
    {
        if (GUIString[i] == 'w')
            w++;
        else if (GUIString[i] == 'y')
            y++;
        else if (GUIString[i] == 'g')
            g++;
        else if (GUIString[i] == 'b')
            b++;
        else if (GUIString[i] == 'r')
            r++;
        else if (GUIString[i] == 'o')
            o++;
    }

    if (w == 9 && y == 9 && g == 9 && b == 9 && r == 9 && o == 9)
        return 1;
    return 0;
}

/* This function checks if the scramble inputted by the user is valid or not.
 * If it contains any move (string) other than the ones accepted (specified), it returns 0
 */
int scrambleCheck()
{
    QStringList scrambleList = scramble.split(" ");

    foreach(QString move, scrambleList)
    {
        if (move != "L" && move != "R" && move != "U" && move != "D" && move != "F" && move != "B" &&
                move != "L'" && move != "R'" && move != "U'" && move != "D'" && move != "F'" && move != "B'" &&
                move != "L2" && move != "R2" && move != "U2" && move != "D2" && move != "F2" && move != "B2" &&
                move != " " && move != "")
            return 0;
    }
    return 1;
}

////////////////////////////////////// Choice button commands /////////////////////////////////////////

/* When these buttons are clicked (top right corner in window), the style sheet string, s is set to
 * the CSS string for that specific colour. Also the "colour" variable stores that respective colour.
 */

void MainWindow::on_cwhite_clicked()
{
    s = ("background-color: rgb(255, 255, 255);");
    colour = 'w';
}

void MainWindow::on_cy_clicked()
{
    s = ("background-color: rgb(255, 255, 0);");
    colour = 'y';
}

void MainWindow::on_cg_clicked()
{
    s = ("background-color: rgb(85, 255, 0);");
    colour = 'g';
}

void MainWindow::on_cb_clicked()
{
    s = ("background-color: rgb(0, 0, 255);");
    colour = 'b';
}

void MainWindow::on_co_clicked()
{
    s = ("background-color: rgb(255, 170, 0);");
    colour = 'o';
}

void MainWindow::on_cr_clicked()
{
    s = ("background-color: rgb(255, 0, 0);");
    colour = 'r';
}

////////////////////////////////////////// Cube button commands ///////////////////////////////////////

/* When these buttons are clicked, their style sheet is changed to the current style sheet set by the
 * choice button commands. Also the "_gui" variable is updated with the "colour" choice
 */

// White Face Buttons
void MainWindow::on_w0_clicked()
{
    ui->w0->setStyleSheet(s);
    whiteFace_gui[0] = colour;
}
void MainWindow::on_w1_clicked()
{
    ui->w1->setStyleSheet(s);
    whiteFace_gui[1] = colour;
}
void MainWindow::on_w2_clicked()
{
    ui->w2->setStyleSheet(s);
    whiteFace_gui[2] = colour;
}
void MainWindow::on_w3_clicked()
{
    ui->w3->setStyleSheet(s);
    whiteFace_gui[3] = colour;
}
void MainWindow::on_w5_clicked()
{
    ui->w5->setStyleSheet(s);
    whiteFace_gui[5] = colour;
}
void MainWindow::on_w6_clicked()
{
    ui->w6->setStyleSheet(s);
    whiteFace_gui[6] = colour;
}
void MainWindow::on_w7_clicked()
{
    ui->w7->setStyleSheet(s);
    whiteFace_gui[7] = colour;
}
void MainWindow::on_w8_clicked()
{
    ui->w8->setStyleSheet(s);
    whiteFace_gui[8] = colour;
}

// orange Face Buttons
void MainWindow::on_o0_clicked()
{
    ui->o0->setStyleSheet(s);
    orangeFace_gui[0] = colour;
}
void MainWindow::on_o1_clicked()
{
    ui->o1->setStyleSheet(s);
    orangeFace_gui[1] = colour;
}
void MainWindow::on_o2_clicked()
{
    ui->o2->setStyleSheet(s);
    orangeFace_gui[2] = colour;
}
void MainWindow::on_o3_clicked()
{
    ui->o3->setStyleSheet(s);
    orangeFace_gui[3] = colour;
}
void MainWindow::on_o5_clicked()
{
    ui->o5->setStyleSheet(s);
    orangeFace_gui[5] = colour;
}
void MainWindow::on_o6_clicked()
{
    ui->o6->setStyleSheet(s);
    orangeFace_gui[6] = colour;
}
void MainWindow::on_o7_clicked()
{
    ui->o7->setStyleSheet(s);
    orangeFace_gui[7] = colour;
}
void MainWindow::on_o8_clicked()
{
    ui->o8->setStyleSheet(s);
    orangeFace_gui[8] = colour;
}

// green Face Buttons
void MainWindow::on_g0_clicked()
{
    ui->g0->setStyleSheet(s);
    greenFace_gui[0] = colour;
}
void MainWindow::on_g1_clicked()
{
    ui->g1->setStyleSheet(s);
    greenFace_gui[1] = colour;
}
void MainWindow::on_g2_clicked()
{
    ui->g2->setStyleSheet(s);
    greenFace_gui[2] = colour;
}
void MainWindow::on_g3_clicked()
{
    ui->g3->setStyleSheet(s);
    greenFace_gui[3] = colour;
}
void MainWindow::on_g5_clicked()
{
    ui->g5->setStyleSheet(s);
    greenFace_gui[5] = colour;
}
void MainWindow::on_g6_clicked()
{
    ui->g6->setStyleSheet(s);
    greenFace_gui[6] = colour;
}
void MainWindow::on_g7_clicked()
{
    ui->g7->setStyleSheet(s);
    greenFace_gui[7] = colour;
}
void MainWindow::on_g8_clicked()
{
    ui->g8->setStyleSheet(s);
    greenFace_gui[8] = colour;
}

// red Face Buttons
void MainWindow::on_r0_clicked()
{
    ui->r0->setStyleSheet(s);
    redFace_gui[0] = colour;
}
void MainWindow::on_r1_clicked()
{
    ui->r1->setStyleSheet(s);
    redFace_gui[1] = colour;
}
void MainWindow::on_r2_clicked()
{
    ui->r2->setStyleSheet(s);
    redFace_gui[2] = colour;
}
void MainWindow::on_r3_clicked()
{
    ui->r3->setStyleSheet(s);
    redFace_gui[3] = colour;
}
void MainWindow::on_r5_clicked()
{
    ui->r5->setStyleSheet(s);
    redFace_gui[5] = colour;
}
void MainWindow::on_r6_clicked()
{
    ui->r6->setStyleSheet(s);
    redFace_gui[6] = colour;
}
void MainWindow::on_r7_clicked()
{
    ui->r7->setStyleSheet(s);
    redFace_gui[7] = colour;
}
void MainWindow::on_r8_clicked()
{
    ui->r8->setStyleSheet(s);
    redFace_gui[8] = colour;
}

// blue Face Buttons
void MainWindow::on_b0_clicked()
{
    ui->b0->setStyleSheet(s);
    blueFace_gui[0] = colour;
}
void MainWindow::on_b1_clicked()
{
    ui->b1->setStyleSheet(s);
    blueFace_gui[1] = colour;
}
void MainWindow::on_b2_clicked()
{
    ui->b2->setStyleSheet(s);
    blueFace_gui[2] = colour;
}
void MainWindow::on_b3_clicked()
{
    ui->b3->setStyleSheet(s);
    blueFace_gui[3] = colour;
}
void MainWindow::on_b5_clicked()
{
    ui->b5->setStyleSheet(s);
    blueFace_gui[5] = colour;
}
void MainWindow::on_b6_clicked()
{
    ui->b6->setStyleSheet(s);
    blueFace_gui[6] = colour;
}
void MainWindow::on_b7_clicked()
{
    ui->b7->setStyleSheet(s);
    blueFace_gui[7] = colour;
}
void MainWindow::on_b8_clicked()
{
    ui->b8->setStyleSheet(s);
    blueFace_gui[8] = colour;
}

// yellow Face Buttons
void MainWindow::on_y0_clicked()
{
    ui->y0->setStyleSheet(s);
    yellowFace_gui[0] = colour;
}
void MainWindow::on_y1_clicked()
{
    ui->y1->setStyleSheet(s);
    yellowFace_gui[1] = colour;
}
void MainWindow::on_y2_clicked()
{
    ui->y2->setStyleSheet(s);
    yellowFace_gui[2] = colour;
}
void MainWindow::on_y3_clicked()
{
    ui->y3->setStyleSheet(s);
    yellowFace_gui[3] = colour;
}
void MainWindow::on_y5_clicked()
{
    ui->y5->setStyleSheet(s);
    yellowFace_gui[5] = colour;
}
void MainWindow::on_y6_clicked()
{
    ui->y6->setStyleSheet(s);
    yellowFace_gui[6] = colour;
}
void MainWindow::on_y7_clicked()
{
    ui->y7->setStyleSheet(s);
    yellowFace_gui[7] = colour;
}
void MainWindow::on_y8_clicked()
{
    ui->y8->setStyleSheet(s);
    yellowFace_gui[8] = colour;
}

////////////////////////////////////// Other GUI elements //////////////////////////////////////

///// Radio Buttons /////

//stores the choice of the user as an integer
void MainWindow::on_GUIInputButton_clicked()
{
    radioButtonInput = 1;
}

void MainWindow::on_scrambleInputButton_clicked()
{
    radioButtonInput = 2;
}
////// Solve Button //////

void MainWindow::on_solveButton_clicked()
{
    ui->shortSolutionButton->setChecked(false);

    // If the scramble input radio button is selected AND the scramble is valid,
    if (radioButtonInput == 2 && scrambleCheck())
    {

        if (scramble == "")
        {
            solution = "No scramble found";
            moveCount = 0;
        }
        else
        {
            // restore the current state variables to a solved state
            whiteFace = "wwwwwwwww";
            yellowFace = "yyyyyyyyy";
            greenFace = "ggggggggg";
            blueFace = "bbbbbbbbb";
            redFace = "rrrrrrrrr";
            orangeFace = "ooooooooo";

            // scramble the cube based on the inputted scramble
            convertScramble(scramble);

            // and solve the cube
            solveCube();
        }
    }
    // else if the GUI input radio button is selected and the GUI is valid,
    else if (radioButtonInput == 1 && GUICheck())
    {
        // update the current state variables to the state provided by the GUI
        whiteFace = whiteFace_gui;
        yellowFace = yellowFace_gui;
        redFace = redFace_gui;
        orangeFace = orangeFace_gui;
        greenFace = greenFace_gui;
        blueFace = blueFace_gui;

        // and solve the cube
        solveCube();
    }
    // else if no radio button is selected, throw error
    else if (radioButtonInput == 0)
    {
        solution = "Input Method not selected";
        moveCount = 0;
    }
    // else if either of the two check functions return 0, display error message
    else
    {
        solution = "No Solution Possible. Please retry with proper scramble/colours.";
        moveCount = 0;
    }

    ui->movesLabel->setText(solution); // set the movesLabel to display the solution
    ui->movesLabel->setWordWrap(true); // enable word wrap for the movesLabel
    ui->moveCountLabel->setText(QString::number(moveCount)); // display the move count as an integer

    // if a shorter solution exists (determined by solveCube function)
    if (moveCount_short < moveCount)
    {
        // change the text of the shortSolution check box
        QString shortSolutionButtonText = "View " + QString::number(moveCount_short) + " move solution";
        // set the movesLabel text to the shorter solution
        ui->shortSolutionButton->setText(shortSolutionButtonText);
        // make the shortSolution checkbox visible
        ui->shortSolutionButton->setVisible(true);
    }
    // else if no shorter solution exists
    else
        // make the shortSolution check box invisible
        ui->shortSolutionButton->setVisible(false);
}

/////////////// Clear Button //////////////////

//sets all GUI elements to default position
void MainWindow::on_clearButton_clicked()
{
    // set stylesheet string to initial gray colour
    s = ("background-color: rgba(0, 0, 0, 50);");

    // set all the cube buttons to this stylesheet
    ui->w0->setStyleSheet(s);
    ui->w1->setStyleSheet(s);
    ui->w2->setStyleSheet(s);
    ui->w3->setStyleSheet(s);
    ui->w5->setStyleSheet(s);
    ui->w6->setStyleSheet(s);
    ui->w7->setStyleSheet(s);
    ui->w8->setStyleSheet(s);

    ui->o0->setStyleSheet(s);
    ui->o1->setStyleSheet(s);
    ui->o2->setStyleSheet(s);
    ui->o3->setStyleSheet(s);
    ui->o5->setStyleSheet(s);
    ui->o6->setStyleSheet(s);
    ui->o7->setStyleSheet(s);
    ui->o8->setStyleSheet(s);

    ui->g0->setStyleSheet(s);
    ui->g1->setStyleSheet(s);
    ui->g2->setStyleSheet(s);
    ui->g3->setStyleSheet(s);
    ui->g5->setStyleSheet(s);
    ui->g6->setStyleSheet(s);
    ui->g7->setStyleSheet(s);
    ui->g8->setStyleSheet(s);

    ui->r0->setStyleSheet(s);
    ui->r1->setStyleSheet(s);
    ui->r2->setStyleSheet(s);
    ui->r3->setStyleSheet(s);
    ui->r5->setStyleSheet(s);
    ui->r6->setStyleSheet(s);
    ui->r7->setStyleSheet(s);
    ui->r8->setStyleSheet(s);

    ui->b0->setStyleSheet(s);
    ui->b1->setStyleSheet(s);
    ui->b2->setStyleSheet(s);
    ui->b3->setStyleSheet(s);
    ui->b5->setStyleSheet(s);
    ui->b6->setStyleSheet(s);
    ui->b7->setStyleSheet(s);
    ui->b8->setStyleSheet(s);

    ui->y0->setStyleSheet(s);
    ui->y1->setStyleSheet(s);
    ui->y2->setStyleSheet(s);
    ui->y3->setStyleSheet(s);
    ui->y5->setStyleSheet(s);
    ui->y6->setStyleSheet(s);
    ui->y7->setStyleSheet(s);
    ui->y8->setStyleSheet(s);

    // re-initialize all internal variables

    whiteFace_gui = "wwwwwwwww", yellowFace_gui = "yyyyyyyyy", greenFace_gui = "ggggggggg",
                blueFace_gui = "bbbbbbbbb", redFace_gui = "rrrrrrrrr", orangeFace_gui = "ooooooooo";

    radioButtonInput = 0;
    colour = 'x';
    scramble = "";

    // set all labels and text field to display nothing
    ui->scrambleLineEdit->setText("");
    ui->movesLabel->setText("");
    ui->moveCountLabel->setText("");

    // set autoexclusivity to false so that the radio butons can be un-checked
    ui->scrambleInputButton->setAutoExclusive(false);
    ui->GUIInputButton->setAutoExclusive(false);

    // uncheck both radio buttons
    ui->scrambleInputButton->setChecked(false);
    ui->GUIInputButton->setChecked(false);

    // set autoexclusivity back to true
    ui->scrambleInputButton->setAutoExclusive(true);
    ui->GUIInputButton->setAutoExclusive(true);

    // make the shortSolution check box invisible
    ui->shortSolutionButton->setVisible(false);
}

//////////////// Scramble Field ///////////////////////

// if the position of the cursor changes, "scramble" variable stores the string in the field
void MainWindow::on_scrambleLineEdit_cursorPositionChanged()
{
    scramble = ui->scrambleLineEdit->text();
}

// if "return" key is pressed when cursor is focused on the scramble field
void MainWindow::on_scrambleLineEdit_returnPressed()
{
    // "Scramble Input" radio button click is simulated
    MainWindow::on_scrambleInputButton_clicked();

    // "Scramble Input" radio button is checked
    ui->scrambleInputButton->setChecked(true);

    // "Solve Button" click is simulated
    MainWindow::on_solveButton_clicked();
}

//////////////////// shortSolution Button //////////////////////

void MainWindow::on_shortSolutionButton_toggled(bool checked)
{
    if (checked)
    {
        ui->movesLabel->setText(solution_short); // sets movesLabel to the shorter solution
        ui->movesLabel->setWordWrap(true);
        ui->moveCountLabel->setText(QString::number(moveCount_short)); // sets moveCountLabel to the shorter move count
        QString shortSolutionButtonText = "View " + QString::number(moveCount) + " move solution";
        ui->shortSolutionButton->setText(shortSolutionButtonText); // alters button text to the above QString
    }
    else
    {
        ui->movesLabel->setText(solution); // sets movesLabel to the original solution
        ui->movesLabel->setWordWrap(true);
        ui->moveCountLabel->setText(QString::number(moveCount)); // sets moveCountLabel to the original move count
        QString shortSolutionButtonText = "View " + QString::number(moveCount_short) + " move solution";
        ui->shortSolutionButton->setText(shortSolutionButtonText); // alters button text to the above QString
    }
}

////////////////////////// View Scramble Button /////////////////////////////////

void MainWindow::on_viewScrambleButton_clicked()
{
    // if "Scramble" field has some text AND if the text is a valid scramble,
    if (ui->scrambleLineEdit->text() != "" && scrambleCheck())
    {
        // restore the current state variables to solved state
        whiteFace = "wwwwwwwww";
        yellowFace = "yyyyyyyyy";
        greenFace = "ggggggggg";
        blueFace = "bbbbbbbbb";
        redFace = "rrrrrrrrr";
        orangeFace = "ooooooooo";

        // scramble the cube according to the string in the "Scramble" field
        convertScramble(scramble);

        // creates a new dialog from scrambleDialog class and opens it
        scrambleDialog scrambledialog;
        scrambledialog.setModal(true); // Modal approach denies the user to interact with both windows at the same time
        scrambledialog.exec(); // executes the scrambleDialog which is defined in scrambledialog.cpp

    }
    // else if there is no text in the field or if the text is an invalid scramble
    else
        // throw error
        ui->movesLabel->setText("Invalid Scramble");
}

//////////////////////// Provide Scramble Button //////////////////////////////////

QString scrambleString()
{
    QStringList set, mod;
    QString s;
    set << "R" << "F" << "U" << "L" << "D" << "B";
    mod << "" << "'" << "2";

    int low = 0, high1 = 5, high2 = 2, m, n, checker;

    for (int i = 0; i < 20; i++)
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
    return s;
}

void MainWindow::on_provideScrambleButton_clicked()
{
    ui->scrambleLineEdit->setText(scrambleString());
}

