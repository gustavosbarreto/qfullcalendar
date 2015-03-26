#include "qfullcalendar.h"

#include <QDateTime>
#include <QLocale>
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QWebView>
#include <QWebFrame>
#include <QDesktopServices>
#include <QInputDialog>

QFullCalendarFileStorage::QFullCalendarFileStorage(QObject *parent):
    EventFactory(parent)
{
    m_fileName = QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "qfullcalendar.dat";

    QFile file(m_fileName);
    file.open(QFile::ReadOnly);
    
    while (!file.atEnd())
    {
        QDataStream s(&file);
        QFullCalendar::Event e;
        s >> e;
        m_events[e.id] = e;
    }
}

QFullCalendar::Event QFullCalendarFileStorage::event(int id)
{
    return m_events[id];
}

QList<QFullCalendar::Event> QFullCalendarFileStorage::events(uint start, uint end)
{
    QList<QFullCalendar::Event> list;
    foreach (const QFullCalendar::Event &e, m_events)
    {
        if (QDateTime::fromString(e.start, Qt::ISODate).toTime_t() >= start &&
            QDateTime::fromString(e.end, Qt::ISODate).toTime_t() <= end)
        {
            list << e;
        }
    }

    return list;
}

void QFullCalendarFileStorage::save(const QFullCalendar::Event &e)
{
    QFile file(m_fileName);
    file.open(QFile::ReadWrite | QIODevice::Append);

    QByteArray ba;
    QDataStream s(&ba, QIODevice::ReadWrite);
    s << e;

    file.write(ba);
}

class MemoryEventFactory: public QFullCalendar::EventFactory
{
public:
    MemoryEventFactory(QObject *parent): EventFactory(parent)
    {
    }

    virtual QFullCalendar::Event event(int id)
    {
        return mappedEvents[id];
    }

    virtual QList<QFullCalendar::Event> events(uint start, uint end)
    {
        QList<QFullCalendar::Event> list;
        foreach (const QFullCalendar::Event &e, mappedEvents)
        {
            if (QDateTime::fromString(e.start, Qt::ISODate).toTime_t() >= start &&
                QDateTime::fromString(e.end, Qt::ISODate).toTime_t() <= end)
            {
                list << e;
            }
        }

        return list;
    }

    virtual void save(const QFullCalendar::Event &e)
    {
        mappedEvents[e.id] = e;
    }

    QMap<int, QFullCalendar::Event> mappedEvents;
};

class JavaScriptBridge: public QObject
{
    Q_OBJECT

    QFullCalendar *q;

public:
    JavaScriptBridge(QFullCalendar *parent): QObject(), q(parent) { }

public slots:
    QString defaultView() const
    {
        if (q->defaultView() == QFullCalendar::MonthView) return "month";
        if (q->defaultView() == QFullCalendar::BasicWeekView) return "basicWeek";
        if (q->defaultView() == QFullCalendar::BasicDayView) return "basicDay";
        if (q->defaultView() == QFullCalendar::AgendaWeekView) return "agendaWeek";
        if (q->defaultView() == QFullCalendar::AgendaDayView) return "agendaDay";
    }

    QStringList dayNamesShort()
    {
        QStringList list;
        QLocale locale = QLocale::system();
        for (int i = 1; i <= 7; ++i)
            list << locale.dayName(i, QLocale::ShortFormat);
        list.prepend(list.takeLast());
        return list;
    }

    QStringList dayNames()
    {
        QStringList list;
        QLocale locale = QLocale::system();
        for (int i = 1; i <= 7; ++i)
            list << locale.dayName(i);
        list.prepend(list.takeLast());
        return list;
    }

    QStringList monthNamesShort()
    {
        QStringList list;
        QLocale locale = QLocale::system();
        for (int i = 1; i <= 12; ++i)
            list << locale.monthName(i);
        return list;
    }

    QStringList monthNames()
    {
        QStringList list;
        QLocale locale = QLocale::system();
        for (int i = 1; i <= 12; ++i)
            list << locale.monthName(i, QLocale::ShortFormat);
        return list;
    }

    QVariantList events(uint start, uint end)
    {
        QVariantList list;

        QList<QFullCalendar::Event> events = q->eventFactory()->events(start, end);
        foreach (const QFullCalendar::Event &e, events)
        {
            if (QDateTime::fromString(e.start, Qt::ISODate).toTime_t() >= start &&
                QDateTime::fromString(e.end, Qt::ISODate).toTime_t() <= end)
            {
                QVariantMap map;
                map["id"] = e.id;
                map["title"] = e.title;
                map["start"] = e.start;
                map["end"] =  e.end;
                map["allDay"] = e.allDay;
                list << map;
            }
        }

        return list;
    }

    void emitEventClicked(int id)
    {
        QFullCalendar::Event e = q->eventFactory()->event(id);
        emit q->eventClicked(e);
    }

    void emitEventDropped(int id)
    {
        QFullCalendar::Event e = q->eventFactory()->event(id);
        emit q->eventDropped(e);
    }

    void emitEventResized(int id)
    {
    }

protected:
    friend class QFullCalendar;

private:
    QMap<int, QFullCalendar::Event> m_events;
};

QFullCalendar::QFullCalendar(QWebView *parent)
 : QObject(parent)
 , m_parent(parent)
 , m_defaultView(MonthView)
{
    m_eventFactory = new MemoryEventFactory(this);
    m_javaScriptBridge = new JavaScriptBridge(this);

    connect(parent->page(), SIGNAL(loadStarted()), SLOT(addJavaScriptBridge()));
}

void QFullCalendar::setEventFactory(EventFactory *factory)
{
    m_eventFactory = factory;
    m_parent->reload();
}

bool QFullCalendar::saveEvent(const Event &e)
{
    m_eventFactory->save(e);
}


void QFullCalendar::undoDropEvent()
{
    m_parent->page()->currentFrame()->evaluateJavaScript("undoDropEvent()");
}

void QFullCalendar::undoResizeEvent()
{
    m_parent->page()->currentFrame()->evaluateJavaScript("undoResizeEvent()");
}

void QFullCalendar::addJavaScriptBridge()
{
    m_parent->page()->currentFrame()->addToJavaScriptWindowObject("QFullCalendar", m_javaScriptBridge);
}

QDataStream &operator>>(QDataStream &in, QFullCalendar::Event &e)
{
    in >> e.id;
    in >> e.title;
    in >> e.start;
    in >> e.end;
    in >> e.allDay;
    return in;
}

QDataStream &operator<<(QDataStream &out, const QFullCalendar::Event &e)
{
    out << e.id;
    out << e.title;
    out << e.start;
    out << e.end;
    out << e.allDay;
    return out;
}

#include "qfullcalendar.moc"
