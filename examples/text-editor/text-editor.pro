TEMPLATE = app

DEPENDPATH += .
INCLUDEPATH += . ../../lib

LIBS += -L ../../lib -ldeclarativewidgets

QT += declarative

# Input
SOURCES += \
    main.cpp \
    editor.cpp

HEADERS += \
    editor.h

RESOURCES += \
    text-editor.qrc

OTHER_FILES += \
    main.qml
