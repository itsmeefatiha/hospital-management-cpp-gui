cmake_minimum_required(VERSION 3.16)

project(hospital-management-cpp-gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------------------------------------
# FIX 1: Add 'Sql' to the required components here
# ----------------------------------------------------------------------
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql PrintSupport)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        admindashboard.cpp
        admindashboard.h
        admindashboard.ui
        receptiondashboard.cpp
        receptiondashboard.h
        receptiondashboard.ui
        doctordashboard.cpp
        doctordashboard.h
        doctordashboard.ui
        patientdashboard.cpp
        patientdashboard.h
        patientdashboard.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(hospital-management-cpp-gui
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        loginwindow.h loginwindow.cpp loginwindow.ui
        database.h database.cpp
        pagepatients.h pagepatients.cpp pagepatients.ui
        pagerdv.h pagerdv.cpp pagerdv.ui
        pageadmissions.h pageadmissions.cpp pageadmissions.ui
        pagepatientsearch.h pagepatientsearch.cpp pagepatientsearch.ui
        pagemedicalrecord.h pagemedicalrecord.cpp pagemedicalrecord.ui
        pageusers.h pageusers.cpp pageusers.ui
        pageservices.h pageservices.cpp pageservices.ui
        pagerooms.h pagerooms.cpp pagerooms.ui
        pagepatientappointments.h pagepatientappointments.cpp pagepatientappointments.ui
        pagepatientrecord.h pagepatientrecord.cpp pagepatientrecord.ui

        pagepatientprescriptions.h pagepatientprescriptions.cpp pagepatientprescriptions.ui
        resources.qrc
    )
else()
    if(ANDROID)
        add_library(hospital-management-cpp-gui SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(hospital-management-cpp-gui
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# ----------------------------------------------------------------------
# FIX 2: Link the Qt Sql library to your ACTUAL target name
# ----------------------------------------------------------------------
target_link_libraries(hospital-management-cpp-gui PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::PrintSupport
)

# Qt for iOS setup (standard boilerplate)
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.hospital-management-cpp-gui)
endif()

set_target_properties(hospital-management-cpp-gui PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS hospital-management-cpp-gui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(hospital-management-cpp-gui)
endif()
