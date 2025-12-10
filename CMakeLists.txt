cmake_minimum_required(VERSION 3.16)

project(hospital-management-cpp-gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql PrintSupport Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql PrintSupport Charts)

# --- DÉFINITION DES SOURCES (Tout est dans PROJECT_SOURCES) ---
set(PROJECT_SOURCES
    # Main & MainWindow
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui

    # Auth
    src/auth/loginwindow.cpp
    src/auth/loginwindow.h
    src/auth/loginwindow.ui

    # Database
    src/db/database.cpp
    src/db/database.h

    # Admin Module
    src/admin/admindashboard.cpp
    src/admin/admindashboard.h
    src/admin/admindashboard.ui
    src/admin/pageusers.cpp
    src/admin/pageusers.h
    src/admin/pageusers.ui
    src/admin/pageservices.cpp
    src/admin/pageservices.h
    src/admin/pageservices.ui
    src/admin/pagerooms.cpp
    src/admin/pagerooms.h
    src/admin/pagerooms.ui

    # Reception Module
    src/reception/receptiondashboard.cpp
    src/reception/receptiondashboard.h
    src/reception/receptiondashboard.ui
    src/reception/pagepatients.cpp
    src/reception/pagepatients.h
    src/reception/pagepatients.ui
    src/reception/pagerdv.cpp
    src/reception/pagerdv.h
    src/reception/pagerdv.ui
    src/reception/pageadmissions.cpp
    src/reception/pageadmissions.h
    src/reception/pageadmissions.ui


    # Doctor Module
    src/doctor/doctordashboard.cpp
    src/doctor/doctordashboard.h
    src/doctor/doctordashboard.ui
    src/doctor/pagemedicalrecord.cpp
    src/doctor/pagemedicalrecord.h
    src/doctor/pagemedicalrecord.ui
    src/doctor/pagepatientsearch.cpp
    src/doctor/pagepatientsearch.h
    src/doctor/pagepatientsearch.ui

    # Patient Module
    src/patient/patientdashboard.cpp
    src/patient/patientdashboard.h
    src/patient/patientdashboard.ui
    src/patient/pagepatientappointments.cpp
    src/patient/pagepatientappointments.h
    src/patient/pagepatientappointments.ui
    src/patient/pagepatientrecord.cpp
    src/patient/pagepatientrecord.h
    src/patient/pagepatientrecord.ui
    src/patient/pagepatientprescriptions.cpp
    src/patient/pagepatientprescriptions.h
    src/patient/pagepatientprescriptions.ui

    # Resources
    resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(hospital-management-cpp-gui
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES} # <--- On utilise uniquement la liste définie ci-dessus
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

# --- GESTION DES INCLUDES ---
# Permet de trouver les fichiers header (.h) sans changer vos #include
target_include_directories(hospital-management-cpp-gui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/auth
    ${CMAKE_CURRENT_SOURCE_DIR}/src/db
    ${CMAKE_CURRENT_SOURCE_DIR}/src/admin
    ${CMAKE_CURRENT_SOURCE_DIR}/src/doctor
    ${CMAKE_CURRENT_SOURCE_DIR}/src/reception
    ${CMAKE_CURRENT_SOURCE_DIR}/src/patient
)

target_link_libraries(hospital-management-cpp-gui PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::PrintSupport
    Qt${QT_VERSION_MAJOR}::Charts
)

# ... (Le reste de votre fichier pour iOS/Install reste identique) ...
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
