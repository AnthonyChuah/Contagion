TEMPLATE = app
TARGET = Contagion

QT = core gui

greaterThan(QT_MAJOR_VERSION,4): QT += widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    #city.cpp \
    #contPlanner.cpp \
    #Dispatcher.cpp \
    #hero.cpp \
    #icard.cpp \
    #Medic.cpp \
    #OpExpert.cpp \
    #pcard.cpp \
    #QSpecialist.cpp \
    #Researcher.cpp \
    #Scientist.cpp \
    #test.cpp \
    #world.cpp
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
    confirmwindow.h
    #city.h \
    #contPlanner.h \
    #Dispatcher.h \
    #hero.h \
    #icard.h \
    #Medic.h \
    #OpExpert.h \
    #pcard.h \
    #QSpecialist.h \
    #Researcher.h \
    #Scientist.h \
    #world.h

RESOURCES +=

FORMS +=
