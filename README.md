# QFullCalendar

A Qt event calendar widget built on top of jQuery FullCalendar

# Installing

You obviously need Qt5 to build the library. There are two ways to install the library, see as follow:

## Installing into system

You can install the library into your linux system running the following:

```shell
qmake PREFIX=/usr
make
make install
```

If you are using a qmake project add to your project file:

```
CONFIG += link_pkgconfig
PKGCONFIG += qfullcalendar
```

> ### You must have to initialize the QFullCalendar resources in your application's main function:

```c++
Q_INIT_RESOURCE(qfullcalendar);
```

## Embedding into your project

To embed the library into your project without installing into the system, add the following to your qmake project file:

```
include(path/to/qfullcalendar.pri)
```

# API

## ```class QFullCalendar```

This is the main class.

```c++
QFullCalendar::DefaultView defaultView()
  ```

Get the default view.

```c++
void setDefaultView(QFullCalendar::DefaultView view)
```

Set the default view.

```c++
QFullCalendar::EventFactory *eventFactory()
```

Get the current event factory.

```c++
void setEventFactory(QFullCalendar::EventFactory *factory)
```

Set the current event factory.

```c++
void undoDropEvent()
```

Undo the last drop event.

```c++
void undoResizeEvent()
```

Undo the last resize event.

```c++
signal eventClicked(QFullCalendar::Event event)
```

This signal is emitted when an event is clicked.

```c++
signal eventDropped(QFullCalendar::Event event)
```

This signal is emitted when dragging stops and the **event** has moved to a different day/time.

```c++
signal eventResized(QFullCalendar::Event event)
```

This signal is emitted when resizing stops and the **event** has changed in duration.

## ```enum QFullCalendar::DefaultView```

* MonthView
* BasicWeekView
* BasicDayView
* AgendaWeekView
* AgendaDayView

## ```struct QFullCalendar::Event```

This struct represents an event.

| Property Type    | Name   | Description          |
|------------------|--------|----------------------|
| int              | id     | Identificator        |
| QString          | title  | Title of event       |
| QString          | start  | Start time of event  |
| QString          | end    | End time of event    |
| bool             | allDay | All day event        |

## ```class QFullCalendar::EventFactory```

This is an abstract class that should be implemented to provide a factory of events to be used in the calendar. By default the QFullCalendar has in-memory event factory.

```c++
QFullCalendar::Event event(int id)
```

Get an event.

```c++
QList<QFullCalendar::Event> events(uint start, uint end)
```

Get the events between **start** and **end**.

```c++
void save(const QFullCalendar::Event &e)
```

Save an event.


[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/gustavosbarreto/qfullcalendar/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

