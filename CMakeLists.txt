cmake_minimum_required(VERSION 3.5)

project(tsp_solution VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core)

set(SOURCES
    main.cpp
    mainwindow.cpp
    genome.cpp
    tspwindow.cpp
    citycoordinates.cpp
    tspholder.cpp
    tspcalculator.cpp
)

set(HEADERS
        mainwindow.h
        mainwindow.ui
        genome.h
        tspwindow.h
        citycoordinates.h
        mapconstants.h
        tspholder.h
        tspcalculator.h
)

set(UI
        mainwindow.ui
        tspwindow.ui
)

add_executable(tsp-solution ${SOURCES} ${HEADERS} ${UI})

target_link_libraries(tsp-solution PRIVATE Qt5::Widgets Qt5::Core)
