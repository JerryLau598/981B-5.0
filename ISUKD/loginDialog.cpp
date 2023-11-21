#include "loginDialog.h"
#include "ui_loginDialog.h"
#include "timeutils.h"
#include "calculation.h"
#include "dataProcessing1.h"
#include "dataprocessing2.h"
#include "dataprocessing3.h"

#include <QMessageBox>
#include <QDateTime>
#include <QKeyEvent>
#include <unordered_map>
#include <iostream>
#include <iomanip>

using namespace std;

std::unordered_map<int, quint64> lastPressedMap;

FILE *filePre;
FILE *fileBtw;

quint64 lastTime = 0;

quint64 onceDataPre [15];
quint64 onceDataBtw [15];

quint64 pressingTime_1 [20] [15];
quint64 timeBtwTwoKeysPress_1 [20] [15];
int pressingIndex_1 = 0;
int pressBtwIndex_1 = 0;

quint64 pressingTime_2 [20] [15];
quint64 timeBtwTwoKeysPress_2 [20] [15];
int pressingIndex_2 = 0;
int pressBtwIndex_2 = 0;

quint64 pressingTime_3 [20] [15];
quint64 timeBtwTwoKeysPress_3 [20] [15];
int pressingIndex_3 = 0;
int pressBtwIndex_3 = 0;

int numberOfPasswordDigitP = 0;
int numberOfPasswordDigitR = 0;

int userIndex = 0;

myDialog::myDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    // Create new input boxes for Username and Password
    lineEditUsername = new LineEdit(this);
    lineEditPassword = new LineEdit(this);

    // Receive the key press event of Username
    connect(
        lineEditUsername, &LineEdit::onKeyPressEvent,
        this, &myDialog::onUserKeyPressEvent
        );

    // Receive the key press event of Password
    connect(
        lineEditPassword, &LineEdit::onKeyPressEvent,
        this, &myDialog::onPwdKeyPressEvent
        );

    // Receive the key release event of Username
    connect(
        lineEditUsername, &LineEdit::onKeyReleaseEvent,
        this, &myDialog::onUserKeyReleaseEvent
        );

    // Receive the key release event of Password
    connect(
        lineEditPassword, &LineEdit::onKeyReleaseEvent,
        this, &myDialog::onPwdKeyReleaseEvent
        );

    // Place the two input boxes in the corresponding layout
    ui->userLayout->addWidget(lineEditUsername);
    ui->pwdLayout->addWidget(lineEditPassword);

    read_data();
}

myDialog::~myDialog()
{
    delete ui;
}


void myDialog::on_exitButton_clicked()
{

}

void myDialog::on_loginButton_clicked()

{
    /* Set userName and password, three conditions.
     * User1's input data with using his commonly used passwords:       test1 ==> zpx,19931110
     * User2’s input data with using User1’s commonly used password:    test2 ==> zpx,19931110
     * User2's input data with using his commonly used passwords:       test3 ==> 229403
     */

    //Determine whether the password is correct
    if(lineEditUsername->text().trimmed() == tr("test1") && lineEditPassword->text() == tr("zpx,19931110"))
    {
        userIndex = 1;

        read_data();

        dataProcessing1 *d1 = new dataProcessing1(this);

        if (pressingTime_1 [19] [0] == 0 || timeBtwTwoKeysPress_1 [19] [0] == 0)
        {
            QMessageBox::warning(this, tr("Warning"), tr("Insufficient data storage!"),QMessageBox::Yes);
            d1 -> open();
        }
        else
        {
            //determine by mathematical
            bool passMath = mathematical(pressingTime_1, timeBtwTwoKeysPress_1, onceDataPre, onceDataBtw);

            if (passMath)
            {
                d1 -> open();
            }
            else
            {
                QMessageBox::warning(this, tr("Warning"), tr("Input habits are incondidtent!"),QMessageBox::Yes);
            }

            //determine by machine learning
            read_data(2);
            bool passML = machineLearning(pressingTime_1, timeBtwTwoKeysPress_1, onceDataPre, onceDataBtw, pressingTime_2, timeBtwTwoKeysPress_2);
            cout << "Result of machine Learning method is: " << (passML? "Pass": "Not Pass") << ". \n";
        }
    }
    else if (lineEditUsername->text().trimmed() == tr("test2") && lineEditPassword->text() == tr("zpx,19931110"))
    {
        userIndex = 2;

        read_data();

        dataProcessing2 *d2 = new dataProcessing2(this);

        if (pressingTime_2 [19] [0] == 0 || timeBtwTwoKeysPress_2 [19] [0] == 0)
        {
            QMessageBox::warning(this, tr("Warning"), tr("Insufficient data storage!"),QMessageBox::Yes);
            d2 -> open();
        }
        else
        {
            //determine by mathematical
            bool passMath = mathematical(pressingTime_2, timeBtwTwoKeysPress_2, onceDataPre, onceDataBtw);
            if (passMath)
            {
                d2 -> open();
            }
            else
            {
                QMessageBox::warning(this, tr("Warning"), tr("Input habits are incondidtent!"),QMessageBox::Yes);
            }

            //determine by machine learning
            read_data(1);
            bool passML = machineLearning(pressingTime_2, timeBtwTwoKeysPress_2, onceDataPre, onceDataBtw, pressingTime_3, timeBtwTwoKeysPress_3);
            cout << "Result of machine Learning method is: " << (passML? "Pass": "Not Pass") << ". \n";
        }
    }
    else if (lineEditUsername->text().trimmed() == tr("test3") && lineEditPassword->text() == tr("229403"))
    {
        userIndex = 3;

        read_data();

        dataProcessing3 *d3 = new dataProcessing3(this); 

        if (pressingTime_3 [19] [0] == 0 || timeBtwTwoKeysPress_3 [19] [0] == 0)
        {
            QMessageBox::warning(this, tr("Warning"), tr("Insufficient data storage!"),QMessageBox::Yes);
            d3 -> open();
        }
        else
        {
            //determine by mathematical
            bool passMath = mathematical(pressingTime_3, timeBtwTwoKeysPress_3, onceDataPre, onceDataBtw);
            if (passMath)
            {
                d3 -> open();
            }
            else
            {
                QMessageBox::warning(this, tr("Warning"), tr("Input habits are incondidtent!"),QMessageBox::Yes);
            }
        }
    }

    /* wrong userName or password */
    else
    {
        userIndex = 0;

        QMessageBox::warning(this, tr("Warning"), tr("User name or password error!"),QMessageBox::Yes);

        for (int j=0; j<15; j++)
        {
            onceDataPre [j] = 0;
            onceDataBtw [j] = 0;
        }
    }

    times_1 = 1;
    times_2 = 1;
    times_3 = 1;

    //lineEditUsername->clear();
    lineEditPassword->clear();
    //lineEditUsername->setFocus();
    lineEditPassword->setFocus();

    numberOfPasswordDigitP = 0;
    numberOfPasswordDigitR = 0;
    lastTime = 0;

    // debug
    cout << "onceData: \n";

    for (int j=0; j<15; j++)
    {
        cout << setw(10) << onceDataPre[j];
    }
    cout << endl;

    for (int j=0; j<15; j++)
    {
        cout << setw(10) << onceDataBtw[j];
    }
    cout << endl;

}

QString myDialog::getCurrentTime()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
}

void myDialog::onUserKeyPressEvent(QKeyEvent* event)
{

}

void myDialog::onUserKeyReleaseEvent(QKeyEvent* event)
{

}

void myDialog::onPwdKeyPressEvent(QKeyEvent* event)
{
    // Enter to login
    if (event->key() == 16777220)
    {
        on_loginButton_clicked();
        event->setAccepted(true);
        return;
    }

    quint64 nano;
    if (event->key() >=0 && event->key() <= 127 || event->key() == 16777248)
    {
        if (numberOfPasswordDigitP < 15)
        {
            lastPressedMap[event->key()] = TimeUtils::getCurrentNanoSinceEpoch();

            if (lastTime != 0)
                onceDataBtw [numberOfPasswordDigitP-1] = TimeUtils::getCurrentNanoSinceEpoch() - lastTime;

            lastTime = TimeUtils::getCurrentNanoSinceEpoch();

            numberOfPasswordDigitP ++;
        }
    }

    else if (numberOfPasswordDigitP > 0 && event->key() == 16777219)
    {
        if (numberOfPasswordDigitP < 15)
        {
            lastPressedMap[event->key()] = TimeUtils::getCurrentNanoSinceEpoch();

            numberOfPasswordDigitP --;
        }
    }
}

void myDialog::onPwdKeyReleaseEvent(QKeyEvent* event)
{
    quint64 nano;
    if (event->key() >=0 && event->key() <= 127 || event->key() == 16777248)
    {
        quint64 lastPressed = lastPressedMap[event->key()];

        nano = TimeUtils::getCurrentNanoSinceEpoch() - lastPressed;
        onceDataPre [numberOfPasswordDigitR] = nano;

        numberOfPasswordDigitR ++;
    }
    else if (numberOfPasswordDigitR >= 1 && event->key() == 16777219)
    {
        quint64 lastPressed = lastPressedMap[event->key()];

        nano = TimeUtils::getCurrentNanoSinceEpoch() - lastPressed;

        numberOfPasswordDigitR --;
    }
}

void myDialog::read_data(int userid)
{
    //determine which user is logging in
    if(userid == 1)
    {
        //clear container to read data
        for (int i=0; i<20; i++)
        {
            for (int j=0; j<15; j++)
            {
                pressingTime_1 [i] [j] = 0;
                timeBtwTwoKeysPress_1 [i] [j] = 0;
                pressingIndex_1 = 0;
                pressBtwIndex_1 = 0;
            }
        }

        //open file
        filePre = fopen("dataPre_1.txt", "rb");
        fileBtw = fopen("dataBtw_1.txt", "rb");

        //read data
        if (filePre && fileBtw)
        {
            fread(&pressingIndex_1, sizeof(pressingIndex_1), 1, filePre);
            fread(pressingTime_1, sizeof(pressingTime_1), 1, filePre);

            fread(&pressBtwIndex_1, sizeof(pressBtwIndex_1), 1, fileBtw);
            fread(timeBtwTwoKeysPress_1, sizeof(timeBtwTwoKeysPress_1), 1, fileBtw);

            fclose(filePre);
            fclose(fileBtw);
        }
        else
        {
            QMessageBox::warning(this,tr("message"),tr("open failed"),QMessageBox::Yes);
        }
    }

    else if (userid == 2)
    {
        //clear container to read data
        for (int i=0; i<20; i++)
        {
            for (int j=0; j<15; j++)
            {
                pressingTime_2 [i] [j] = 0;
                timeBtwTwoKeysPress_2 [i] [j] = 0;
                pressingIndex_2 = 0;
                pressBtwIndex_2 = 0;
            }
        }

        //open file
        filePre = fopen("dataPre_2.txt", "rb");
        fileBtw = fopen("dataBtw_2.txt", "rb");

        //read data
        if (filePre && fileBtw)
        {
            fread(&pressingIndex_2, sizeof(pressingIndex_2), 1, filePre);
            fread(pressingTime_2, sizeof(pressingTime_2), 1, filePre);

            fread(&pressBtwIndex_2, sizeof(pressBtwIndex_2), 1, fileBtw);
            fread(timeBtwTwoKeysPress_2, sizeof(timeBtwTwoKeysPress_2), 1, fileBtw);

            fclose(filePre);
            fclose(fileBtw);
        }
        else
        {
            QMessageBox::warning(this,tr("message"),tr("open failed"),QMessageBox::Yes);
        }
    }

    else if (userid == 3)
    {
        //clear container to read data
        for (int i=0; i<20; i++)
        {
            for (int j=0; j<15; j++)
            {
                pressingTime_3 [i] [j] = 0;
                timeBtwTwoKeysPress_3 [i] [j] = 0;
                pressingIndex_3 = 0;
                pressBtwIndex_3 = 0;
            }
        }

        //open file
        filePre = fopen("dataPre_3.txt", "rb");
        fileBtw = fopen("dataBtw_3.txt", "rb");

        //read data
        if (filePre && fileBtw)
        {
            fread(&pressingIndex_3, sizeof(pressingIndex_3), 1, filePre);
            fread(pressingTime_3, sizeof(pressingTime_3), 1, filePre);

            fread(&pressBtwIndex_3, sizeof(pressBtwIndex_3), 1, fileBtw);
            fread(timeBtwTwoKeysPress_3, sizeof(timeBtwTwoKeysPress_3), 1, fileBtw);

            fclose(filePre);
            fclose(fileBtw);
        }
        else
        {
            QMessageBox::warning(this,tr("message"),tr("open failed"),QMessageBox::Yes);
        }
    }

    cout << "userIndex: " << userIndex << "\n";
}

void myDialog::read_data()
{
    //clear container to read data
    for (int i=0; i<20; i++)
    {
        for (int j=0; j<15; j++)
        {
            pressingTime_1 [i] [j] = 0;
            timeBtwTwoKeysPress_1 [i] [j] = 0;
            pressingIndex_1 = 0;
            pressBtwIndex_1 = 0;

            pressingTime_2 [i] [j] = 0;
            timeBtwTwoKeysPress_2 [i] [j] = 0;
            pressingIndex_2 = 0;
            pressBtwIndex_2 = 0;

            pressingTime_3 [i] [j] = 0;
            timeBtwTwoKeysPress_3 [i] [j] = 0;
            pressingIndex_3 = 0;
            pressBtwIndex_3 = 0;
        }
    }

    //determine which user is logging in
    if(userIndex == 1)
    {
        //open file
        filePre = fopen("dataPre_1.txt", "rb");
        fileBtw = fopen("dataBtw_1.txt", "rb");

        //read data
        if (filePre && fileBtw)
        {
            fread(&pressingIndex_1, sizeof(pressingIndex_1), 1, filePre);
            fread(pressingTime_1, sizeof(pressingTime_1), 1, filePre);

            fread(&pressBtwIndex_1, sizeof(pressBtwIndex_1), 1, fileBtw);
            fread(timeBtwTwoKeysPress_1, sizeof(timeBtwTwoKeysPress_1), 1, fileBtw);

            fclose(filePre);
            fclose(fileBtw);
        }
        else
        {
            QMessageBox::warning(this,tr("message"),tr("open failed"),QMessageBox::Yes);
        }
    }

    else if (userIndex == 2)
    {
        //open file
        filePre = fopen("dataPre_2.txt", "rb");
        fileBtw = fopen("dataBtw_2.txt", "rb");

        //read data
        if (filePre && fileBtw)
        {
            fread(&pressingIndex_2, sizeof(pressingIndex_2), 1, filePre);
            fread(pressingTime_2, sizeof(pressingTime_2), 1, filePre);

            fread(&pressBtwIndex_2, sizeof(pressBtwIndex_2), 1, fileBtw);
            fread(timeBtwTwoKeysPress_2, sizeof(timeBtwTwoKeysPress_2), 1, fileBtw);

            fclose(filePre);
            fclose(fileBtw);
        }
        else
        {
            QMessageBox::warning(this,tr("message"),tr("open failed"),QMessageBox::Yes);
        }
    }

    else if (userIndex == 3)
    {
        //open file
        filePre = fopen("dataPre_3.txt", "rb");
        fileBtw = fopen("dataBtw_3.txt", "rb");

        //read data
        if (filePre && fileBtw)
        {
            fread(&pressingIndex_3, sizeof(pressingIndex_3), 1, filePre);
            fread(pressingTime_3, sizeof(pressingTime_3), 1, filePre);

            fread(&pressBtwIndex_3, sizeof(pressBtwIndex_3), 1, fileBtw);
            fread(timeBtwTwoKeysPress_3, sizeof(timeBtwTwoKeysPress_3), 1, fileBtw);

            fclose(filePre);
            fclose(fileBtw);
        }
        else
        {
            QMessageBox::warning(this,tr("message"),tr("open failed"),QMessageBox::Yes);
        }
    }
}
