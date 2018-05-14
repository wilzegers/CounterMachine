CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

PROJECT(CounterMachine-release)

SET(CMAKE_CXX_FLAGS "-O3")
SET(CMAKE_CXX_STANDARD 14)

SET(Boost_USE_STATIC_LIBS OFF) 
SET(Boost_USE_MULTITHREADED ON)  
SET(Boost_USE_STATIC_RUNTIME OFF) 
FIND_PACKAGE(Boost)

SET(SOURCES CounterMachine/Source/Descriptors/Computation.cpp
        CounterMachine/Source/Execution/Computation.cpp
        CounterMachine/Source/Execution/State.cpp
        CounterMachine/Source/Processing/ComputationBuilder.cpp
        CounterMachine/Source/Processing/InputParser.cpp
        CounterMachine/Source/Processing/Lexer.cpp
        CounterMachine/Source/Processing/Parser.cpp
        CounterMachine/Source/Transformation/MachineTransformer.cpp
        CounterMachine/Source/Transformation/TransformationRules.cpp
        CounterMachine/Source/Transformation/TransformedComputation.cpp)

SET(HEADERS CounterMachine/Source/Descriptors/Computation.h
        CounterMachine/Source/Descriptors/Instruction.h
        CounterMachine/Source/Execution/Instruction.h
        CounterMachine/Source/Execution/Computation.h
        CounterMachine/Source/Execution/State.h
        CounterMachine/Source/Processing/ComputationBuilder.h
        CounterMachine/Source/Processing/InputParser.h
        CounterMachine/Source/Processing/Lexer.h
        CounterMachine/Source/Processing/Parser.h
        CounterMachine/Source/Processing/ParserBase.h
        CounterMachine/Source/Processing/Symbol.h
        CounterMachine/Source/Shared/BoostIncludes.h
        CounterMachine/Source/Shared/Constants.h
        CounterMachine/Source/Shared/Exceptions.h
        CounterMachine/Source/Shared/Utility.h
        CounterMachine/Source/Transformation/MachineTransformer.h
        CounterMachine/Source/Transformation/TransformationRules.h
        CounterMachine/Source/Transformation/TransformationRuleService.h
        CounterMachine/Source/Transformation/TransformedComputation.h)

INCLUDE_DIRECTORIES(CounterMachine/Source CounterMachine/Source/Shared)

ADD_LIBRARY(CounterMachine STATIC ${SOURCES})

TARGET_LINK_LIBRARIES(CounterMachine Boost::boost)
