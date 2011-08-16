#include "mainwindow.h"
#include "agendadatabase.h"
#include "qfullcalendar.h"

#include <QWebView>

MainWindow::MainWindow(): QMainWindow()
{
    ui.setupUi(this);

    QWebView *webView = new QWebView(this);

    centralWidget()->layout()->addWidget(webView);

    m_fullCalendar = new QFullCalendar(webView);
    m_fullCalendar->setEventFactory(new AgendaDatabase(this));
    m_fullCalendar->setDefaultView(QFullCalendar::AgendaWeekView);

    connect(m_fullCalendar, SIGNAL(eventClicked(const QFullCalendar::Event &)),
            SLOT(showEventDialog(const QFullCalendar::Event &e)));

    webView->load(QUrl("qrc:/qfullcalendar/index.html"));
}
