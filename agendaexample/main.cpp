#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Q_INIT_RESOURCE(qfullcalendar);

    MainWindow *mw = new MainWindow;
    mw->show();
    mw->resize(900, 600);

    return app.exec();
}
