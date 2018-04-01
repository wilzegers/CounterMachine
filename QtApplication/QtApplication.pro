QT       += core gui
CONFIG   += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtApplication
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG(debug, debug|release) {
    LIBS += -L../CounterMachine/Debug -lCounterMachine
}

CONFIG(release, debug|release) {
    LIBS += -L../CounterMachine/Release -lCounterMachine
}

INCLUDEPATH += "C:/boost/boost_1_61_0"

INCLUDEPATH += ../CounterMachine/Source \
    ../CounterMachine/Source/Shared

SOURCES += \
        main.cpp \
        MainWindow.cpp \
        Model.cpp \
        ComputationHolder.cpp

HEADERS += \
        MainWindow.h \
        Model.h \
        ComputationHolder.h \
        ../CounterMachine/Source/Descriptors/Computation.h \
        ../CounterMachine/Source/Descriptors/Instruction.h \
        ../CounterMachine/Source/Execution/Computation.h \
        ../CounterMachine/Source/Execution/Instruction.h \
        ../CounterMachine/Source/Execution/State.h \
        ../CounterMachine/Source/Processing/InputParser.h \
        ../CounterMachine/Source/Processing/ComputationBuilder.h \
        ../CounterMachine/Source/Processing/Lexer.h \
        ../CounterMachine/Source/Processing/Parser.h \
        ../CounterMachine/Source/Processing/ParserBase.h \
        ../CounterMachine/Source/Processing/Symbol.h \
        ../CounterMachine/Source/Shared/BoostIncludes.h \
        ../CounterMachine/Source/Shared/Constants.h \
        ../CounterMachine/Source/Shared/Exceptions.h \
        ../CounterMachine/Source/Shared/Utility.h \
        ../CounterMachine/Source/Transformation/MachineTransformer.h \
        ../CounterMachine/Source/Transformation/TransformationRules.h \
        ../CounterMachine/Source/Transformation/TransformationRuleService.h \
        ../CounterMachine/Source/Transformation/TransformedComputation.h

FORMS += \
        MainWindow.ui
