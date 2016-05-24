#include "ui_mainwindow.h"
#include "solversq.h"
#include "mainwindow.h"

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
extern QString solutionSQ_short;
extern QString solutionSQ;
extern int moveCountSQ;
extern int moveCountSQ_short;
extern bool trialSQ;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Internal Variables //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

// "_gui" variables contain the state of the cube as defined by the user in the GUI
QStringList uF_gui, dF_gui;

// stores the scramble provided by the user in the "Scramble" field
QString scrambleSQ = "";

// stores the stylesheet string used to modify the colours of the cube layout
//QString s = ("background-color: rgba(0, 0, 0, 50);");

// stores the colour specified by the stylesheet choice. Used to modify "_gui" variables
//char colour = 'x';

// stores the choice of the user for the radio button, 1 for GUI, 2 for scramble
int radioButtonInputSQ = 0;

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

    if (scrambleCheck_SQ())
    {
        convertString(scrambleSQ, 1);
        initSQ1();
    }
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

