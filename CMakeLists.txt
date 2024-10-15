cmake_minimum_required(VERSION 3.20)

project(courier-service-modeling VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    Frontend/CompanySetSizeWindow/CompanySetSizeWindow.h
    Frontend/CompanySetSizeWindow/CompanySetSizeWindow.cpp
    Branch/Branch.cpp
    Courier/Courier.cpp
    service/Service.cpp
    Frontend/SetTimeWindow/SetTimeWindow.h
    Frontend/SetTimeWindow/SetTimeWindow.cpp
    Time/Time.h
    Time/Time.cpp
    Frontend/MainDispetcherWindow/MainDispetcherWindow.h
    Frontend/MainDispetcherWindow/MainDispetcherWindow.cpp
    Frontend/OfficePriorityWindow/OfficePriorityWindow.h
    Frontend/OfficePriorityWindow/OfficePriorityWindow.cpp
    Generator/Generator.cpp
    Events/AbstacstEvent/AbsractEvent.h
    Events/LastEvent/LastEvent.h
    Events/LastEvent/LastEvent.cpp
    Events/AbstacstEvent/AbstractEvent.cpp
    Events/LetterMovingEvent/LetterMovingEvent.cpp
    Events/OfficeVisitEvent/OfficeVisitEvent.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(courier-service-modeling
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

    )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET courier-service-modeling APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(courier-service-modeling SHARED
            ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(courier-service-modeling
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(courier-service-modeling PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.courier-service-modeling)
endif()
set_target_properties(courier-service-modeling PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS courier-service-modeling
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(courier-service-modeling)
endif()
ADD_COMPILE_DEFINITIONS(DEBUG)
