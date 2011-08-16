QT += webkit

DEPENDPATH += ../
INCLUDEPATH += ../
LIBS += ../libqfullcalendar.a

HEADERS += mainwindow.h agendatabase.h
FORMS += mainwindow.ui
SOURCES += main.cpp mainwindow.cpp agendadatabase.cpp
RESOURCES += resources.qrc
