# generate debug version:
# mkdir debug; cd debug; cmake -DCMAKE_BUILD_TYPE=Debug ..
# generate release version:
# mkdir release; cd release; cmake -DCMAKE_BUILD_TYPE=Release ..

CMAKE_MINIMUM_REQUIRED(VERSION 3.0...3.20)
PROJECT(TDengine)

SET(CMAKE_C_STANDARD 11)

ADD_SUBDIRECTORY(examples/c)
ADD_SUBDIRECTORY(tsim)
ADD_SUBDIRECTORY(test/c)
ADD_SUBDIRECTORY(comparisonTest/tdengine)
