#include "qfullcalendarwidget.h"
#include "qfullcalendar.h"

#include <QWebFrame>

QFullCalendarWidget::QFullCalendarWidget(QWidget *parent):
    QWebView(parent)
{
    m_qFullCalendar = new QFullCalendar(this);
    load(QUrl("qrc:/qfullcalendar/index.html"));
}
