TEMPLATE = app
CONFIG -= qt
CONFIG -= app_bundle
CONFIG += console
CONFIG += c++17
DESTDIR = .
isEmpty(BOOST_INCLUDE_DIR): BOOST_INCLUDE_DIR=$$(BOOST_INCLUDE_DIR)
!isEmpty(BOOST_INCLUDE_DIR): INCLUDEPATH *= $${BOOST_INCLUDE_DIR}

isEmpty(BOOST_INCLUDE_DIR): {
    message("BOOST_INCLUDE_DIR is not set, assuming Boost can be found automatically in your system")
}

SOURCES += \
        environment.cpp \
        interpreter.cpp \
        lexer.cpp \
        main.cpp \
        parser.cpp \
        reader.cpp \ #\
        syntax_objects/addoperation.cpp \
        syntax_objects/argument.cpp \
        syntax_objects/assignment.cpp \
        syntax_objects/expression.cpp \
        syntax_objects/factor.cpp \
        syntax_objects/functioncall.cpp \
        syntax_objects/functiondef.cpp \
        syntax_objects/ifelse.cpp \
        syntax_objects/inode.cpp \
        syntax_objects/instruction.cpp \
        syntax_objects/logicalexpression.cpp \
        syntax_objects/multioperation.cpp \
        syntax_objects/parameters.cpp \
        syntax_objects/primaryexpression.cpp \
        syntax_objects/program.cpp \
        syntax_objects/return.cpp \
        syntax_objects/statementblock.cpp \
        syntax_objects/vardeclaration.cpp \
        syntax_objects/whileloop.cpp
  #      test.cpp

HEADERS += \
    Token.h \
    TokenTypes.h \
    Tokens.h \
    environment.h \
    interpreter.h \
    lexer.h \
    parser.h \
    reader.h \
    syntax_objects/addoperation.h \
    syntax_objects/argument.h \
    syntax_objects/assignment.h \
    syntax_objects/expression.h \
    syntax_objects/factor.h \
    syntax_objects/functioncall.h \
    syntax_objects/functiondef.h \
    syntax_objects/ifelse.h \
    syntax_objects/inode.h \
    syntax_objects/instruction.h \
    syntax_objects/logicalexpression.h \
    syntax_objects/multioperation.h \
    syntax_objects/parameters.h \
    syntax_objects/primaryexpression.h \
    syntax_objects/program.h \
    syntax_objects/return.h \
    syntax_objects/statementblock.h \
    syntax_objects/vardeclaration.h \
    syntax_objects/whileloop.h
