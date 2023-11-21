#include "dataprocessing1.h"
#include "ui_dataprocessing1.h"
#include "loginDialog.h"

#include <iostream>
#include <iomanip>
#include <QMessageBox>
#include <QTextBrowser>
#include <stdio.h>

using namespace std;

dataProcessing1::dataProcessing1(QWidget *parent) :
    QDialog(parent),
    parent(parent),
    ui(new Ui::dataProcessing1)
{
    ui->setupUi(this);
    on_refersh_clicked();
}

dataProcessing1::~dataProcessing1()
{
    delete ui;
}

int times_1 = 1;

void dataProcessing1::on_record_clicked()
{
    //determine whether the first time to record
    if (times_1 == 1)
    {
        //store data to full data
        for (int j=0; j<15; j++)
        {
            pressingTime_1 [pressingIndex_1] [j] = onceDataPre [j];
            timeBtwTwoKeysPress_1 [pressBtwIndex_1] [j] = onceDataBtw [j];
        }

        //open file
        filePre = fopen("dataPre_1.txt", "wb");
        fileBtw = fopen("dataBtw_1.txt", "wb");

        //Record full data to file
        if (filePre && fileBtw)
        {
            //store index
            int preIndex = (pressingIndex_1 + 1) % 20;
            fwrite(&preIndex, sizeof(preIndex), 1, filePre);

            //store data
            fwrite(pressingTime_1, sizeof(pressingTime_1) , 1, filePre );

            //store index
            int btwIndex = (pressBtwIndex_1 + 1) % 20;
            fwrite(&btwIndex, sizeof(btwIndex), 1, fileBtw);

            //store data
            fwrite(timeBtwTwoKeysPress_1, sizeof(timeBtwTwoKeysPress_1) , 1, fileBtw );
        }
        else
        {
            QMessageBox::warning(this,tr("message"),tr("open failed"),QMessageBox::Yes);
        }

        fclose(filePre);
        fclose(fileBtw);

        times_1 ++;

        QMessageBox::warning(this, tr("Message"), tr("Record success!"),QMessageBox::Yes);
    }
    else
    {
        QMessageBox::warning(this, tr("Warning"), tr("Already recorded!"),QMessageBox::Yes);
    }

    on_refersh_clicked();

    //Debug
    cout << "index: ";
    cout << setw(2) << pressingIndex_1;
    cout << setw(2) << pressBtwIndex_1 << endl;
}


void dataProcessing1::on_reset_clicked()
{
    times_1 = 1;

    //delete data
    filePre = fopen("dataPre_1.txt", "w+");
    fileBtw = fopen("dataBtw_1.txt", "w+");
    fclose(filePre);
    fclose(fileBtw);

    //refresh QMessageBox
    on_refersh_clicked();

    QMessageBox::warning(this, tr("Message"), tr("Reset successful!"),QMessageBox::Yes);

    //Debug
    cout << "index: ";
    cout << setw(2) << pressingIndex_1;
    cout << setw(2) << pressBtwIndex_1 << endl;
}


void dataProcessing1::on_exit_clicked()
{
    times_1 = 1;
}

void dataProcessing1::on_refersh_clicked()
{
    //read data
    ((myDialog*)parent)->read_data();

    //Show data in QTextBrowser
    ui->pressingData->clear();
    ui->pressingData->append("Data on the time between press and release of one key (ms): \n");

    ui->pressedData->clear();
    ui->pressedData->append("Data on the time between two key presses (ms): \n");

    ui->onceData->clear();
    ui->onceData->append("Data of this time (ms): ");

    //show stored data
    for (int i=0; i<20; i++)
    {
        for (int j=0; j<15; j++)
        {
            if (pressingTime_1 [i] [j] != 0)
            {
                ui->pressingData->insertPlainText(tr("%1").arg(pressingTime_1 [i] [j] / 1000000, 5, 10, QLatin1Char(' ')));
                ui->pressingData->moveCursor(QTextCursor::End);
            }

            if (timeBtwTwoKeysPress_1 [i] [j] != 0)
            {
                ui->pressedData->insertPlainText(tr("%1").arg(timeBtwTwoKeysPress_1 [i] [j]/ 1000000, 5, 10, QLatin1Char(' ')));
                ui->pressedData->moveCursor(QTextCursor::End);
            }
        }
        ui->pressingData->append("\n");
        ui->pressedData->append("\n");
    }

    //show onceData
    ui->onceData->append("Data on the time between press and release of one key: \n");
    for (int j=0; j<15; j++)
    {
        if (onceDataPre [j] != 0)
        {
            ui->onceData->insertPlainText(tr("%1").arg(onceDataPre [j] / 1000000, 5, 10, QLatin1Char(' ')));
            ui->onceData->moveCursor(QTextCursor::End);
        }
    }

    ui->onceData->append("Data on the time between two key presses: \n");
    for (int j=0; j<15; j++)
    {
        if (onceDataBtw [j] != 0)
        {
            ui->onceData->insertPlainText(tr("%1").arg(onceDataBtw [j] / 1000000, 5, 10, QLatin1Char(' ')));
            ui->onceData->moveCursor(QTextCursor::End);
        }
    }
}
