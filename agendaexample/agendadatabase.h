#ifndef _AGENDADATABASE_H
#define _AGENDADATABASE_H

#include "qfullcalendar.h"

class AgendaDatabase: public QFullCalendar::EventFactory
{
public:
    AgendaDatabase(QObject *parent);

    inline const QString &fileName() const { return m_fileName; }
    inline void setFileName(const QString &fileName) { m_fileName = fileName; }

    virtual QFullCalendar::Event event(int id);
    virtual QList<QFullCalendar::Event> events(uint start, uint end);
    virtual void save(const QFullCalendar::Event &e);

private:
    QString m_fileName;
    QMap<int, QFullCalendar::Event> m_events;
};

inline QDataStream &operator>>(QDataStream &in, QFullCalendar::Event &e);
inline QDataStream &operator<<(QDataStream &out, const QFullCalendar::Event &e);

#endif
