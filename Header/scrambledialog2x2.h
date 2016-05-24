#ifndef SCRAMBLEDIALOG2X2_H
#define SCRAMBLEDIALOG2X2_H

#include <QDialog>

namespace Ui {
class scrambleDialog2x2;
}

class scrambleDialog2x2 : public QDialog
{
    Q_OBJECT

public:
    explicit scrambleDialog2x2(QWidget *parent = 0);
    ~scrambleDialog2x2();

private:
    Ui::scrambleDialog2x2 *ui;
};

// converts a character (which stores a colour code) to a stylesheet which can be applied to the buttons
QString convertToStyleSheet2(QChar s);

#endif // SCRAMBLEDIALOG2X2_H
