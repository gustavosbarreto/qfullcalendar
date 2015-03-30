#include "mainwindow.h"
#include "agendadatabase.h"
#include "qfullcalendarwidget.h"

MainWindow::MainWindow(): QMainWindow()
{
    ui.setupUi(this);

    m_fullCalendar = new QFullCalendarWidget(this);
    m_fullCalendar->qFullCalendar()->setEventFactory(new AgendaDatabase(this));
    m_fullCalendar->qFullCalendar()->setDefaultView(QFullCalendar::AgendaWeekView);

    centralWidget()->layout()->addWidget(m_fullCalendar);

    connect(m_fullCalendar->qFullCalendar(), SIGNAL(eventClicked(const QFullCalendar::Event &)),
            SLOT(showEventDialog(const QFullCalendar::Event &e)));
}
