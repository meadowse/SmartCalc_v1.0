QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#    ../s21_credit.c \
#    ../s21_deposit.c \
#    ../s21_smartcalc.c \
    CException.c \
    graph.c \
    RPN.c \
    structs.c \
    calc.c \
#    credit.cpp \
#    deposit.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
#    ../s21_credit.h \
#    ../s21_deposit.h \
#    ../s21_smartcalc.h \
#    ../s21_smartcalc.h \
    CException.h \
    graph.h \
    defines.h \
    calc.h \
    structs.h \
    RPN.h \
#    credit.h \
#    deposit.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
#    credit.ui \
#    deposit.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
