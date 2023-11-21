#ifndef DATAPROCESSING1_H
#define DATAPROCESSING1_H

#include <QDialog>

namespace Ui {
class dataProcessing1;
}

class dataProcessing1 : public QDialog
{
    Q_OBJECT

public:
    explicit dataProcessing1(QWidget *parent = nullptr);
    ~dataProcessing1();
    QWidget* parent;

private slots:
    void on_record_clicked();

    void on_reset_clicked();

    void on_exit_clicked();

    void on_refersh_clicked();


private:
    Ui::dataProcessing1 *ui;
};

extern int times_1;

#endif // DATAPROCESSING1_H
