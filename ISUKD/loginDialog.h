#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "lineedit.h"
#include <QKeyEvent>
#include <QDialog>

namespace Ui {
class loginDialog;
}

class myDialog : public QDialog
{
    Q_OBJECT

public:
    explicit myDialog(QWidget *parent = nullptr);

    ~myDialog();

    void read_data(int userid);

    void read_data();




private slots:
    void on_loginButton_clicked();

    void on_exitButton_clicked();

    void onUserKeyPressEvent(QKeyEvent* event);

    void onUserKeyReleaseEvent(QKeyEvent* event);

    void onPwdKeyPressEvent(QKeyEvent* event);

    void onPwdKeyReleaseEvent(QKeyEvent* event);



private:
    Ui::loginDialog *ui;
    LineEdit* lineEditUsername;
    LineEdit* lineEditPassword;
    QString getCurrentTime();
};

//store data
extern quint64 pressingTime_1 [20] [15];
extern quint64 timeBtwTwoKeysPress_1 [20] [15];
extern quint64 pressingTime_2 [20] [15];
extern quint64 timeBtwTwoKeysPress_2 [20] [15];
extern quint64 pressingTime_3 [20] [15];
extern quint64 timeBtwTwoKeysPress_3 [20] [15];

extern quint64 onceDataPre [15];
extern quint64 onceDataBtw [15];

extern int pressingIndex_1;
extern int pressBtwIndex_1;
extern int pressingIndex_2;
extern int pressBtwIndex_2;
extern int pressingIndex_3;
extern int pressBtwIndex_3;

extern FILE *filePre;
extern FILE *fileBtw;

#endif // LOGINDIALOG_H
