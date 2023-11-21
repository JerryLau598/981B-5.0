#ifndef DATAPROCESSING2_H
#define DATAPROCESSING2_H

#include <QDialog>

namespace Ui {
class dataProcessing2;
}

class dataProcessing2 : public QDialog
{
    Q_OBJECT

public:
    explicit dataProcessing2(QWidget *parent = nullptr);
    ~dataProcessing2();
    QWidget* parent;

private slots:
    void on_record_clicked();

    void on_reset_clicked();

    void on_exit_clicked();

    void on_refersh_clicked();


private:
    Ui::dataProcessing2 *ui;
};

extern int times_2;

#endif // DATAPROCESSING2_H
