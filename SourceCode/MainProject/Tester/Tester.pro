QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app



MODELDIR = ../GLR/ReflexiveParser
INCLUDEPATH  += $$MODELDIR

HEADERS += $$MODELDIR/Grammar.h \
    $$MODELDIR/elementlr1.h \
    $$MODELDIR/lexer.h \
    $$MODELDIR/lrparser.h \
    $$MODELDIR/node.h \
    $$MODELDIR/parsertable.h \
    $$MODELDIR/rule.h \
    $$MODELDIR/token.h


SOURCES += $$MODELDIR/elementlr1.cpp \
    $$MODELDIR/grammar.cpp \
    $$MODELDIR/lexer.cpp \
    $$MODELDIR/lrparser.cpp \
    $$MODELDIR/node.cpp \
    $$MODELDIR/parsertable.cpp \
    $$MODELDIR/rule.cpp \
    $$MODELDIR/token.cpp

SOURCES +=  tst_tester.cpp
