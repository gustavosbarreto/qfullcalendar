#ifndef _QFULLCALENDAR_H
#define _QFULLCALENDAR_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QVariant>
#include <QVariantList>
#include <QStringList>
#include <QMap>

class QWebView;
class QDialog;
class JavaScriptBridge;

class QFullCalendar: public QObject
{
    Q_OBJECT

public:
    struct Event
    {
        int id;
        QString title;
        QString start;
        QString end;
        bool allDay;
        
        Event() { }
        Event(int id, const QString &title, const QString &start, const QString &end, bool allDay):
            id(id), title(title), start(start), end(end), allDay(allDay) { }
    };

    class EventFactory: public QObject
    {
    public:
        EventFactory(QObject *parent): QObject(parent) { }

        virtual QFullCalendar::Event event(int id) = 0;
        virtual QList<QFullCalendar::Event> events(uint start, uint end) = 0;
        virtual void save(const QFullCalendar::Event &e) = 0;
    };

    enum DefaultView
    {
        MonthView,
        BasicWeekView,
        BasicDayView,
        AgendaWeekView,
        AgendaDayView
    };

    QFullCalendar(QWebView *parent);

    inline EventFactory *eventFactory() const { return m_eventFactory; }
    void setEventFactory(EventFactory *factory);

    inline DefaultView defaultView() const { return m_defaultView; }
    inline void setDefaultView(DefaultView view) { m_defaultView = view; }

    bool saveEvent(const Event &e);

signals:
    friend class JavaScriptBridge;

    /**
     * This signal is emitted when the user clicks on an event
     *
     * \param e The event
     */
    void eventClicked(const QFullCalendar::Event &e);

    /**
     * This signal is emitted when the user drops an event
     *
     * \param e The event
     */
    void eventDropped(const QFullCalendar::Event &e);

    /**
     * This signal is emitted when the user resizes an event
     *
     * \param e The event
     */
    void eventResized(const QFullCalendar::Event &e);

public slots:
    /**
     * Undo the last drop event action
     */
    void undoDropEvent();

    /**
     * Undo the last resize event action
     */
    void undoResizeEvent();

private slots:
    void addJavaScriptBridge();

private:
    QWebView *m_parent;
    EventFactory *m_eventFactory;
    DefaultView m_defaultView;
    JavaScriptBridge *m_javaScriptBridge;
};

class QFullCalendarFileStorage: public QFullCalendar::EventFactory
{
public:
    QFullCalendarFileStorage(QObject *parent);

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
