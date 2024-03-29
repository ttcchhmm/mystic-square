cmake_minimum_required(VERSION 3.18)
project(MysticSquare)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(.)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        LinguistTools
        REQUIRED)

set(TS_FILES MysticSquare-fr_FR.ts MysticSquare-en_US.ts)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

add_executable(MysticSquare ${QM_FILES} resources.qrc main.cpp mainwindow.cpp mainwindow.hh mainwindow.ui gamewidget.cpp gamewidget.hh newgamedialog.cpp newgamedialog.hh newgamedialog.ui Stub.hh Game.cpp Game.hh BackgroundEnum.hh)
target_link_libraries(MysticSquare
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

