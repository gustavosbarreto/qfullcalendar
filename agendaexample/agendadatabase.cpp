#include "agendadatabase.h"

#include <QDesktopServices>
#include <QDateTime>
#include <QFile>

AgendaDatabase::AgendaDatabase(QObject *parent):
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

QFullCalendar::Event AgendaDatabase::event(int id)
{
    return m_events[id];
}

QList<QFullCalendar::Event> AgendaDatabase::events(uint start, uint end)
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

void AgendaDatabase::save(const QFullCalendar::Event &e)
{
    QFile file(m_fileName);
    file.open(QFile::ReadWrite | QIODevice::Append);

    QByteArray ba;
    QDataStream s(&ba, QIODevice::ReadWrite);
    s << e;

    file.write(ba);
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
