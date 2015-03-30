#ifndef _QFULLCALENDARWIDGET_H
#define _QFULLCALENDARWIDGET_H

#include <QWebView>

#include "qfullcalendar.h"

class QFullCalendarWidget: public QWebView
{
    Q_OBJECT

public:
    QFullCalendarWidget(QWidget *parent = 0);

    inline QFullCalendar *qFullCalendar() const { return m_qFullCalendar; }

private:
    QFullCalendar *m_qFullCalendar;
};

#endif
