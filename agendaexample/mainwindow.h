#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include "ui_mainwindow.h"

class QFullCalendar;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    Ui::MainWindow ui;
    QFullCalendar *m_fullCalendar;
};

#endif
