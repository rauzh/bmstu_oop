cmake_minimum_required(VERSION 3.17)
project(lab_01)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

set(UI_DOMAIN ./ui)
set(PROC_DOMAIN ./core)
set(FIGURE_DOMAIN ./core/figure)
set(BIND_DOMAIN ./core/bindings)
set(POINTS_DOMAIN ./core/points)

include_directories(${UI_DOMAIN})
include_directories(${PROC_DOMAIN})
include_directories(${FIGURE_DOMAIN})
include_directories(${BIND_DOMAIN})
include_directories(${POINTS_DOMAIN})

add_executable(
        ${PROJECT_NAME}
        ${UI_DOMAIN}/main.cpp
        ${UI_DOMAIN}/mainwindow.cpp
        ${UI_DOMAIN}/mainwindow.h
        ${UI_DOMAIN}/draw.cpp
        ${UI_DOMAIN}/draw.h
        ${PROC_DOMAIN}/errors.cpp
        ${PROC_DOMAIN}/errors.h
        ${PROC_DOMAIN}/figure/figure.cpp
        ${PROC_DOMAIN}/figure/figure.h
        ${PROC_DOMAIN}/figure/figure_actions.h
        ${PROC_DOMAIN}/bindings/binding.cpp
        ${PROC_DOMAIN}/bindings/binding.h
        ${PROC_DOMAIN}/bindings/bindings.h
        ${PROC_DOMAIN}/bindings/bindings.cpp
        ${PROC_DOMAIN}/points/points.cpp
        ${PROC_DOMAIN}/points/point.cpp
        ${PROC_DOMAIN}/points/points.h
        ${PROC_DOMAIN}/points/point.h
        ${PROC_DOMAIN}/tasks.cpp
        ${PROC_DOMAIN}/tasks.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
