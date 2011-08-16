#include <QApplication>
#include <QDebug>

#include "qfullcalendarwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qDebug() << QFile::exists("qrc:/fullcalendar/index.html");

    (new QFullCalendarWidget)->show();

    return app.exec();
}
