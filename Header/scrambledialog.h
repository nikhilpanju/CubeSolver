#ifndef SCRAMBLEDIALOG_H
#define SCRAMBLEDIALOG_H

#include <QDialog>

namespace Ui {
class scrambleDialog;
}

class scrambleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit scrambleDialog(QWidget *parent = 0);
    ~scrambleDialog();

private:
    Ui::scrambleDialog *ui;

};

// converts a character (which stores a colour code) to a stylesheet which can be applied to the buttons
QString convertToStyleSheet(QChar s);

#endif // SCRAMBLEDIALOG_H
