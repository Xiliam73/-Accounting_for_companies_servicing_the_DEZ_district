QT       += core gui
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogaddline.cpp \
    main.cpp \
    mainwindow.cpp \
    maskdelegate.cpp \
    mytablemodel.cpp \
    searchdialog.cpp \
    spinboxdelegate.cpp

HEADERS += \
    dialogaddline.h \
    mainwindow.h \
    maskdelegate.h \
    mytablemodel.h \
    searchdialog.h \
    spinboxdelegate.h

FORMS += \
    dialogaddline.ui \
    mainwindow.ui \
    searchdialog.ui

TRANSLATIONS += \
    translations\Accounting_for_companies_servicing_the_DEZ_district_ru_RU.ts \
    translations\Accounting_for_companies_servicing_the_DEZ_district_en_US.ts \
    translations\Accounting_for_companies_servicing_the_DEZ_district_de_DE.ts


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons/icon.qrc

DISTFILES += \
    DataBaseEn \
    DataBaseRu \
    TestDataBase
