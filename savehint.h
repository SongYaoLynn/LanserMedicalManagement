#ifndef SAVEHINT_H
#define SAVEHINT_H

#include <QDialog>

namespace Ui {
class SaveHint;
}

class SaveHint : public QDialog
{
    Q_OBJECT

public:
    explicit SaveHint(QWidget *parent = 0);
    ~SaveHint();
    void saveHintShow(QString repetitiveName);
signals:
    void saveHintSignal(QString, bool);
private slots:
    void on_submitBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::SaveHint *ui;
    QString repetitiveName;
};

#endif // SAVEHINT_H
