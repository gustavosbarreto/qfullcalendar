#include "qfullcalendarwidget.h"
#include "qfullcalendar.h"

#include <QWebFrame>

QFullCalendarWidget::QFullCalendarWidget(QWidget *parent):
    QWebView(parent)
{
    qFullCalendar = new QFullCalendar(this);
    qFullCalendar->setDefaultView(QFullCalendar::AgendaWeekView);
    qFullCalendar->setEventFactory(new QFullCalendarFileStorage(this));
    connect(qFullCalendar, SIGNAL(eventDropped(const QFullCalendar::Event &)), SLOT(onDrop(const QFullCalendar::Event &)));
    load(QUrl("qrc:/qfullcalendar.html"));
}

void QFullCalendarWidget::onDrop(const QFullCalendar::Event &e)
{
    qFullCalendar->undoDropEvent();
}
