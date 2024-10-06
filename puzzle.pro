QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
requires(qtConfig(listview))

HEADERS += \
    mainwindow.h \
    piecesmodel.h \
    puzzlewidget.h

RESOURCES += \
    puzzle.qrc

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    piecesmodel.cpp \
    puzzlewidget.cpp

DISTFILES += \

FORMS += \
