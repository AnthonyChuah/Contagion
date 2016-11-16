TEMPLATE = app
TARGET = Contagion

QT = core gui

greaterThan(QT_MAJOR_VERSION,4): QT += widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    city.cpp \
    contplanner.cpp \
    dispatcher.cpp \
    hero.cpp \
    icard.cpp \
    medic.cpp \
    opexpert.cpp \
    pcard.cpp \
    qspecialist.cpp \
    researcher.cpp \
    scientist.cpp \
    #test.cpp \
    world.cpp \
    handwindow.cpp \
    specialwindow.cpp \
    movewindow.cpp \
    confirmwindow.cpp


HEADERS += \
    mainwindow.h \
    transpbutton.h \
    handwindow.h \
    specialwindow.h \
    movewindow.h \
    confirmwindow.h \
    city.h \
    contplanner.h \
    dispatcher.h \
    hero.h \
    icard.h \
    medic.h \
    opexpert.h \
    pcard.h \
    qspecialist.h \
    researcher.h \
    scientist.h \
    world.h

RESOURCES +=

FORMS +=
