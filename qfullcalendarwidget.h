#ifndef _QFULLCALENDARWIDGET_H
#define _QFULLCALENDARWIDGET_H

#include <QWebView>

#include "qfullcalendar.h"

class QFullCalendarWidget: public QWebView
{
    Q_OBJECT

public:
    QFullCalendarWidget(QWidget *parent = 0);

private slots:
    void onDrop(const QFullCalendar::Event &e);

private:
    QFullCalendar *qFullCalendar;
};

#endif
