cmake_minimum_required(VERSION 3.16)

project(axis-tags-example VERSION ${VERSION_SHORT}) 

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} 5.5 COMPONENTS Core Gui Widgets REQUIRED)

set(SOURCES
    mainwindow.cpp
    axistag.cpp
    main.cpp
    mainwindow.ui
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_executable(axis-tags-example WIN32 
    ${SOURCES}
)


find_package(qt${QT_VERSION_MAJOR}-qcustomplot CONFIG QUIET)
if(qt${QT_VERSION_MAJOR}-qcustomplot_FOUND)
    get_target_property(QCUSTOMPLOT_INCLUDES  qcp::qt${QT_VERSION_MAJOR}-qcustomplot INTERFACE_INCLUDE_DIRECTORIES)
    get_target_property(QCUSTOMPLOT_LIBRARIES qcp::qt${QT_VERSION_MAJOR}-qcustomplot INTERFACE_LINK_LIBRARIES)
    message(STATUS "QCUSTOMPLOT Found: ${QCUSTOMPLOT_LIBRARIES}, ${QCUSTOMPLOT_INCLUDES}")
    
    target_link_libraries(axis-tags-example PUBLIC qcp::qt${QT_VERSION_MAJOR}-qcustomplot)

    target_include_directories(axis-tags-example PUBLIC
        ${QCUSTOMPLOT_INCLUDES}
    )
else()
    target_link_libraries(axis-tags-example PRIVATE qcp::qt${QT_VERSION_MAJOR}-qcustomplot)
    message(STATUS "QCUSTOMPLOT Not Found: Use private instead")
endif()

target_link_libraries(axis-tags-example PUBLIC 
    Qt${QT_VERSION_MAJOR}::Core 
    Qt${QT_VERSION_MAJOR}::Gui 
    Qt${QT_VERSION_MAJOR}::Widgets
)

set_target_properties(axis-tags-example PROPERTIES 
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION ${VERSION_SHORT}
    EXPORT_NAME "Qt Custom Plot Example"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
