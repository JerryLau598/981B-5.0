#ifndef dataProcessing3_H
#define dataProcessing3_H

#include <QDialog>

namespace Ui {
class dataProcessing3;
}

class dataProcessing3 : public QDialog
{
    Q_OBJECT

public:
    explicit dataProcessing3(QWidget *parent = nullptr);
    ~dataProcessing3();
    QWidget* parent;

private slots:
    void on_record_clicked();

    void on_reset_clicked();

    void on_exit_clicked();

    void on_refersh_clicked();


private:
    Ui::dataProcessing3 *ui;
};

extern int times_3;

#endif // dataProcessing3_H
