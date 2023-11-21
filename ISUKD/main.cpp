#include "loginDialog.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <fstream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ISUKD_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QDialog q;
    myDialog login;

    if(login.exec() == QDialog::Accepted)
    {
        q.show();
        return a.exec();
    }
    else return 0;
}
