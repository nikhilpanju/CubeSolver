#include "../Header/mainwindow.h"
#include "ui_mainwindow.h"
#include "../Header/scrambledialog2x2.h"
#include "../Header/solver2x2.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// External Variables //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/* "_scramble" variables contain the state of the cube after the scramble has been applied.
 * These are used to display the scrambled state using the "View Scramble" button
 * Used in scrambledialog.cpp
 */
extern QString whiteFace2_scramble, yellowFace2_scramble, greenFace2_scramble,
                blueFace2_scramble, redFace2_scramble, orangeFace2_scramble;

// variables used in solver.cpp
extern QString whiteFace2, yellowFace2, greenFace2, blueFace2, redFace2, orangeFace2; // current state variables
extern QString solution2_short;
extern QString solution2;
extern int moveCount2;
extern int moveCount2_short;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Internal Variables //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// "_gui" variables contain the state of the cube as defined by the user in the GUI
QString whiteFace2_gui = "wwww", yellowFace2_gui = "yyyy", greenFace2_gui = "gggg",
            blueFace2_gui = "bbbb", redFace2_gui = "rrrr", orangeFace2_gui = "oooo";

// stores the scramble provided by the user in the "Scramble" field
QString scramble2 = "";

// stores the stylesheet string used to modify the colours of the cube layout
QString s2 = ("background-color: rgba(0, 0, 0, 50);");

// stores the colour specified by the stylesheet choice. Used to modify "_gui" variables
char colour2 = 'x';

// stores the choice of the user for the radio button, 1 for GUI, 2 for scramble
int radioButtonInput2 = 0;



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// GUI Implementation //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/* This function checks if the colours applied to the cube layout in the GUI are valid.
 * Only if there are 9 of each colour, this function returns 1, otherwise 0.
 */
int GUICheck_2()
{
    QString GUIString = whiteFace2_gui + yellowFace2_gui + greenFace2_gui
                        + blueFace2_gui + redFace2_gui + orangeFace2_gui;
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

    if (w == 4 && y == 4 && g == 4 && b == 4 && r == 4 && o == 4)
        return 1;
    return 0;
}

/* This function checks if the scramble inputted by the user is valid or not.
 * If it contains any move (string) other than the ones accepted (specified), it returns 0
 */
int scrambleCheck_2()
{
    QStringList scrambleList = scramble2.split(" ");

    foreach(QString move, scrambleList)
    {
        if (move != "R" && move != "U" && move != "F" && move != "R'" && move != "U'" &&
                move != "F'" && move != "R2" && move != "U2" &&
                move != "F2" && move != " " && move != "")
            return 0;
    }
    return 1;
}

////////////////////////////////////// Choice button commands /////////////////////////////////////////

/* When these buttons are clicked (top right corner in window), the style sheet string, s is set to
 * the CSS string for that specific colour. Also the "colour" variable stores that respective colour.
 */

void MainWindow::on_cwhite_2_clicked()
{
    s2 = ("background-color: rgb(255, 255, 255);");
    colour2 = 'w';
}

void MainWindow::on_cy_2_clicked()
{
    s2 = ("background-color: rgb(255, 255, 0);");
    colour2 = 'y';
}

void MainWindow::on_cg_2_clicked()
{
    s2 = ("background-color: rgb(85, 255, 0);");
    colour2 = 'g';
}

void MainWindow::on_cb_2_clicked()
{
    s2 = ("background-color: rgb(0, 0, 255);");
    colour2 = 'b';
}

void MainWindow::on_co_2_clicked()
{
    s2 = ("background-color: rgb(255, 170, 0);");
    colour2 = 'o';
}

void MainWindow::on_cr_2_clicked()
{
    s2 = ("background-color: rgb(255, 0, 0);");
    colour2 = 'r';
}

////////////////////////////////////////// Cube button commands ///////////////////////////////////////

/* When these buttons are clicked, their style sheet is changed to the current style sheet set by the
 * choice button commands. Also the "_gui" variable is updated with the "colour" choice
 */

// White Face Buttons
void MainWindow::on_w0_2_clicked()
{
    ui->w0_2->setStyleSheet(s2);
    whiteFace2_gui[0] = colour2;
}
void MainWindow::on_w1_2_clicked()
{
    ui->w1_2->setStyleSheet(s2);
    whiteFace2_gui[1] = colour2;
}
void MainWindow::on_w2_2_clicked()
{
    ui->w2_2->setStyleSheet(s2);
    whiteFace2_gui[2] = colour2;
}
void MainWindow::on_w3_2_clicked()
{
    ui->w3_2->setStyleSheet(s2);
    whiteFace2_gui[3] = colour2;
}

// orange Face Buttons
void MainWindow::on_o0_2_clicked()
{
    ui->o0_2->setStyleSheet(s2);
    orangeFace2_gui[0] = colour2;
}
void MainWindow::on_o1_2_clicked()
{
    ui->o1_2->setStyleSheet(s2);
    orangeFace2_gui[1] = colour2;
}
void MainWindow::on_o2_2_clicked()
{
    ui->o2_2->setStyleSheet(s2);
    orangeFace2_gui[2] = colour2;
}
void MainWindow::on_o3_2_clicked()
{
    ui->o3_2->setStyleSheet(s2);
    orangeFace2_gui[3] = colour2;
}

// green Face Buttons
void MainWindow::on_g0_2_clicked()
{
    ui->g0_2->setStyleSheet(s2);
    greenFace2_gui[0] = colour2;
}
void MainWindow::on_g1_2_clicked()
{
    ui->g1_2->setStyleSheet(s2);
    greenFace2_gui[1] = colour2;
}
void MainWindow::on_g2_2_clicked()
{
    ui->g2_2->setStyleSheet(s2);
    greenFace2_gui[2] = colour2;
}
void MainWindow::on_g3_2_clicked()
{
    ui->g3_2->setStyleSheet(s2);
    greenFace2_gui[3] = colour2;
}

// red Face Buttons
void MainWindow::on_r0_2_clicked()
{
    ui->r0_2->setStyleSheet(s2);
    redFace2_gui[0] = colour2;
}
void MainWindow::on_r1_2_clicked()
{
    ui->r1_2->setStyleSheet(s2);
    redFace2_gui[1] = colour2;
}
void MainWindow::on_r2_2_clicked()
{
    ui->r2_2->setStyleSheet(s2);
    redFace2_gui[2] = colour2;
}
void MainWindow::on_r3_2_clicked()
{
    ui->r3_2->setStyleSheet(s2);
    redFace2_gui[3] = colour2;
}

// blue Face Buttons
void MainWindow::on_b0_2_clicked()
{
    ui->b0_2->setStyleSheet(s2);
    blueFace2_gui[0] = colour2;
}
void MainWindow::on_b1_2_clicked()
{
    ui->b1_2->setStyleSheet(s2);
    blueFace2_gui[1] = colour2;
}
void MainWindow::on_b2_2_clicked()
{
    ui->b2_2->setStyleSheet(s2);
    blueFace2_gui[2] = colour2;
}
void MainWindow::on_b3_2_clicked()
{
    ui->b3_2->setStyleSheet(s2);
    blueFace2_gui[3] = colour2;
}

// yellow Face Buttons
void MainWindow::on_y0_2_clicked()
{
    ui->y0_2->setStyleSheet(s2);
    yellowFace2_gui[0] = colour2;
}
void MainWindow::on_y1_2_clicked()
{
    ui->y1_2->setStyleSheet(s2);
    yellowFace2_gui[1] = colour2;
}
void MainWindow::on_y2_2_clicked()
{
    ui->y2_2->setStyleSheet(s2);
    yellowFace2_gui[2] = colour2;
}
void MainWindow::on_y3_2_clicked()
{
    ui->y3_2->setStyleSheet(s2);
    yellowFace2_gui[3] = colour2;
}

////////////////////////////////////// Other GUI elements //////////////////////////////////////

///// Radio Buttons /////

//stores the choice of the user as an integer
void MainWindow::on_GUIInputButton_2_clicked()
{
    radioButtonInput2 = 1;
}

void MainWindow::on_scrambleInputButton_2_clicked()
{
    radioButtonInput2 = 2;
}
////// Solve Button //////

void MainWindow::on_solveButton_2_clicked()
{
    ui->shortSolutionButton_2->setChecked(false);

    // If the scramble input radio button is selected AND the scramble is valid,
    if (radioButtonInput2 == 2 && scrambleCheck_2())
    {
        if (scramble2 == "")
        {
            solution2 = "No scramble found";
            moveCount2 = 0;
        }
        else
        {
            // restore the current state variables to a solved state
            whiteFace2 = "wwww";
            yellowFace2 = "yyyy";
            greenFace2 = "gggg";
            blueFace2 = "bbbb";
            redFace2 = "rrrr";
            orangeFace2 = "oooo";

            // scramble the cube based on the inputted scramble
            convertScramble2(scramble2);

            // and solve the cube
            solveCube2x2();
        }
    }
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
    // else if no radio button is selected, throw error
    else if (radioButtonInput2 == 0)
    {
        solution2 = "Input Method not selected";
        moveCount2 = 0;
    }
    // else if either of the two check functions return 0, display error message
    else
    {
        solution2 = "No solution possible. Please retry with proper scramble/colours.";
        moveCount2 = 0;
    }

    ui->movesLabel2->setText(solution2); // set the movesLabel to display the solution
    ui->movesLabel2->setWordWrap(true); // enable word wrap for the movesLabel
    ui->moveCountLabel2->setText(QString::number(moveCount2)); // display the move count as an integer

    // if a shorter solution exists (determined by solveCube function)
    if (moveCount2_short < moveCount2)
    {
        // change the text of the shortSolution check box
        QString shortSolutionButtonText = "View " + QString::number(moveCount2_short) + " move solution";
        // set the movesLabel text to the shorter solution
        ui->shortSolutionButton_2->setText(shortSolutionButtonText);
        // make the shortSolution checkbox visible
        ui->shortSolutionButton_2->setVisible(true);
    }
    // else if no shorter solution exists
    else
        // make the shortSolution check box invisible
        ui->shortSolutionButton_2->setVisible(false);
}

/////////////// Clear Button //////////////////

//sets all GUI elements to default position
void MainWindow::on_clearButton_2_clicked()
{
    // set stylesheet string to initial gray colour
    s2 = ("background-color: rgba(0, 0, 0, 50);");

    // set all the cube buttons to this stylesheet
    ui->w0_2->setStyleSheet(s2);
    ui->w1_2->setStyleSheet(s2);
    ui->w2_2->setStyleSheet(s2);
    ui->w3_2->setStyleSheet(s2);

    ui->o0_2->setStyleSheet(s2);
    ui->o1_2->setStyleSheet(s2);
    ui->o2_2->setStyleSheet(s2);
    ui->o3_2->setStyleSheet(s2);

    ui->g0_2->setStyleSheet(s2);
    ui->g1_2->setStyleSheet(s2);
    ui->g2_2->setStyleSheet(s2);
    ui->g3_2->setStyleSheet(s2);

    ui->r0_2->setStyleSheet(s2);
    ui->r1_2->setStyleSheet(s2);
    ui->r2_2->setStyleSheet(s2);
    ui->r3_2->setStyleSheet(s2);

    ui->b0_2->setStyleSheet(s2);
    ui->b1_2->setStyleSheet(s2);
    ui->b2_2->setStyleSheet(s2);
    ui->b3_2->setStyleSheet(s2);

    ui->y0_2->setStyleSheet(s2);
    ui->y1_2->setStyleSheet(s2);
    ui->y2_2->setStyleSheet(s2);
    ui->y3_2->setStyleSheet(s2);

    // re-initialize all internal variables
    whiteFace2_gui = "wwww", yellowFace2_gui = "yyyy", greenFace2_gui = "gggg",
                blueFace2_gui = "bbbb", redFace2_gui = "rrrr", orangeFace2_gui = "oooo";

    radioButtonInput2 = 0;
    colour2 = 'x';
    scramble2 = "";

    // set all labels and text field to display nothing
    ui->scrambleLineEdit_2->setText("");
    ui->movesLabel2->setText("");
    ui->moveCountLabel2->setText("");

    // set autoexclusivity to false so that the radio butons can be un-checked
    ui->scrambleInputButton_2->setAutoExclusive(false);
    ui->GUIInputButton_2->setAutoExclusive(false);

    // uncheck both radio buttons
    ui->scrambleInputButton_2->setChecked(false);
    ui->GUIInputButton_2->setChecked(false);

    // set autoexclusivity back to true
    ui->scrambleInputButton_2->setAutoExclusive(true);
    ui->GUIInputButton_2->setAutoExclusive(true);

    // make the shortSolution check box invisible
    ui->shortSolutionButton_2->setVisible(false);
}

//////////////// Scramble Field ///////////////////////

// if the position of the cursor changes, "scramble" variable stores the string in the field
void MainWindow::on_scrambleLineEdit_2_cursorPositionChanged()
{
    scramble2 = ui->scrambleLineEdit_2->text();
}

// if "return" key is pressed when cursor is focused on the scramble field
void MainWindow::on_scrambleLineEdit_2_returnPressed()
{
    // "Scramble Input" radio button click is simulated
    MainWindow::on_scrambleInputButton_2_clicked();

    // "Scramble Input" radio button is checked
    ui->scrambleInputButton_2->setChecked(true);

    // "Solve Button" click is simulated
    MainWindow::on_solveButton_2_clicked();
}

//////////////////// shortSolution Button //////////////////////

void MainWindow::on_shortSolutionButton_2_toggled(bool checked)
{
    if (checked)
    {
        ui->movesLabel2->setText(solution2_short); // sets movesLabel to the shorter solution
        ui->movesLabel2->setWordWrap(true);
        ui->moveCountLabel2->setText(QString::number(moveCount2_short)); // sets moveCountLabel to the shorter move count
        QString shortSolutionButtonText = "View " + QString::number(moveCount2) + " move solution";
        ui->shortSolutionButton_2->setText(shortSolutionButtonText); // alters button text to the above QString
    }
    else
    {
        ui->movesLabel2->setText(solution2); // sets movesLabel to the original solution
        ui->movesLabel2->setWordWrap(true);
        ui->moveCountLabel2->setText(QString::number(moveCount2)); // sets moveCountLabel to the original move count
        QString shortSolutionButtonText = "View " + QString::number(moveCount2_short) + " move solution";
        ui->shortSolutionButton_2->setText(shortSolutionButtonText); // alters button text to the above QString
    }
}

////////////////////////// View Scramble Button /////////////////////////////////

void MainWindow::on_viewScrambleButton_2_clicked()
{
    // if "Scramble" field has some text AND if the text is a valid scramble,
    if (ui->scrambleLineEdit_2->text() != "" && scrambleCheck_2())
    {
        // restore the current state variables to solved state
        whiteFace2 = "wwww";
        yellowFace2 = "yyyy";
        greenFace2 = "gggg";
        blueFace2 = "bbbb";
        redFace2 = "rrrr";
        orangeFace2 = "oooo";

        // scramble the cube according to the string in the "Scramble" field
        convertScramble2(scramble2);

        // creates a new dialog from scrambleDialog class and opens it
        scrambleDialog2x2 scrambledialog2x2;
        scrambledialog2x2.setModal(true); // Modal approach denies the user to interact with both windows at the same time
        scrambledialog2x2.exec(); // executes the scrambleDialog which is defined in scrambledialog.cpp

    }
    // else if there is no text in the field or if the text is an invalid scramble
    else
        // throw error
        ui->movesLabel2->setText("Invalid Scramble");
}

//////////////////////// Provide Scramble Button //////////////////////////////////

QString scrambleString_2()
{
    QStringList set, mod;
    QString s;
    set << "R" << "F" << "U";
    mod << "" << "'" << "2";

    int low = 0, high1 = 2, high2 = 2, m, n, checker;

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
    return s;
}

void MainWindow::on_provideScrambleButton_2_clicked()
{
    ui->scrambleLineEdit_2->setText(scrambleString_2());
}
