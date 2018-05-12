#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>

namespace Ui {
class Instruction;
}

class Instruction : public QWidget
{
    Q_OBJECT

public:
    explicit Instruction(QWidget *parent = 0);
    ~Instruction();

private slots:
    void on_instructionBtn1_clicked();

private:
    Ui::Instruction *ui;
};

#endif // INSTRUCTION_H
