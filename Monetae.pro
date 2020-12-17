TEMPLATE = app
CONFIG += c++17 console
CONFIG -= app_bundle
#LIBS+= -lboost_unit_test_framework-mt
QT -= gui
CONFIG -= qt
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
        lexer.cpp \
        main.cpp \
        reader.cpp #\
  #      test.cpp

HEADERS += \
    Token.h \
    TokenTypes.h \
    Tokens.h \
    lexer.h \
    reader.h
