TEMPLATE = app
TARGET = Contagion

#DESTDIR = $$_PRO_FILE_PWD_

QT = core gui

CONFIG += debug_and_release

greaterThan(QT_MAJOR_VERSION,4): QT += widgets

SOURCES += \
    src/gui/main.cpp \
    #src/game_logic/city.cpp \
    #src/game_logic/contplanner.cpp \
    #src/game_logic/dispatcher.cpp \
    #src/game_logic/hero.cpp \
    #src/game_logic/icard.cpp \
    #src/game_logic/medic.cpp \
    #src/game_logic/opexpert.cpp \
    #src/game_logic/pcard.cpp \
    #src/game_logic/qspecialist.cpp \
    #src/game_logic/researcher.cpp \
    #src/game_logic/scientist.cpp \
    ##src/game_logic/test.cpp \
    #src/game_logic/world.cpp \
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
    src/gui/mainwindow.cpp \
    src/gui/handwindow.cpp \
    src/gui/specialwindow.cpp \
    src/gui/movewindow.cpp \
    src/gui/confirmwindow.cpp \
    src/gui/endturnwindow.cpp \
    src/gui/actioncounter.cpp \
    src/gui/meeplesprite.cpp \
    src/gui/disinfectwindow.cpp \
    src/gui/diseasecube.cpp \
    src/gui/cardwindow.cpp \
    src/gui/flywindow.cpp
    #src/gui/movebuttons.cpp


HEADERS += \
    #src/game_logic/city.h \
    #src/game_logic/contplanner.h \
    #src/game_logic/dispatcher.h \
    #src/game_logic/hero.h \
    #src/game_logic/icard.h \
    #src/game_logic/medic.h \
    #src/game_logic/opexpert.h \
    #src/game_logic/pcard.h \
    #src/game_logic/qspecialist.h \
    #src/game_logic/researcher.h \
    #src/game_logic/scientist.h \
    #src/game_logic/world.h \
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
    world.h \
    src/gui/mainwindow.h \
    src/gui/transpbutton.h \
    src/gui/handwindow.h \
    src/gui/specialwindow.h \
    src/gui/movewindow.h \
    src/gui/confirmwindow.h \
    src/gui/endturnwindow.h \
    src/gui/actioncounter.h \
    src/gui/meeplesprite.h \
    src/gui/disinfectwindow.h \
    src/gui/diseasecube.h \
    src/gui/cardwindow.h \
    src/gui/flywindow.h
    #src/gui/movebuttons.h

RESOURCES += \
    resources.qrc

FORMS +=
