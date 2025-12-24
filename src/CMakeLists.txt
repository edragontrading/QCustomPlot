cmake_minimum_required(VERSION 3.16)
project(QCustomPlot LANGUAGES CXX VERSION ${VERSION_SHORT})

include(GNUInstallDirs)

if (${QT_VERSION_MAJOR})
  message(STATUS "Forced to use Qt version ${QT_VERSION_MAJOR}")
  find_package(QT NAMES Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
else()
  find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
endif()


find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets OpenGL PrintSupport REQUIRED)
if (UNIX AND NOT APPLE)
    include_directories(${Qt${QT_VERSION_MAJOR}Gui_PRIVATE_INCLUDE_DIRS})
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
if(BUILD_STATIC)
    set(CMAKE_STATIC_LIBRARY_SUFFIX "_static${CMAKE_STATIC_LIBRARY_SUFFIX}")
endif()


set(qcustomplot_SRCS
    qcp/painter.cpp
    qcp/paintbuffer.cpp
    qcp/layer.cpp
    qcp/axis/range.cpp
    qcp/axis/labelpainter.cpp
    qcp/axis/axis.cpp
    qcp/axis/axisticker.cpp
    qcp/plottable.cpp
    qcp/item.cpp
    qcp/lineending.cpp
    qcp/core.cpp
    qcp/layout.cpp
    qcp/plottables/plottable-graph.cpp
    qcp/plottables/plottable-curve.cpp
    qcp/plottables/plottable-bars.cpp
    qcp/plottables/plottable-statisticalbox.cpp
    qcp/plottables/plottable-colormap.cpp
    qcp/plottables/plottable-financial.cpp
    qcp/plottables/plottable-errorbar.cpp
    qcp/items/item-straightline.cpp
    qcp/items/item-line.cpp
    qcp/items/item-curve.cpp
    qcp/items/item-rect.cpp
    qcp/items/item-triangle.cpp
    qcp/items/item-parallel.cpp
    qcp/items/item-angle.cpp
    qcp/items/item-text.cpp
    qcp/items/item-ellipse.cpp
    qcp/items/item-pixmap.cpp
    qcp/items/item-tracer.cpp
    qcp/items/item-bracket.cpp
    qcp/layoutelements/layoutelement-axisrect.cpp
    qcp/layoutelements/layoutelement-legend.cpp
    qcp/layoutelements/layoutelement-textelement.cpp
    qcp/layoutelements/layoutelement-colorscale.cpp
    qcp/colorgradient.cpp
    qcp/vector2d.cpp
    qcp/axis/axistickerdatetime.cpp
    qcp/axis/axistickertime.cpp
    qcp/axis/axistickerfixed.cpp
    qcp/axis/axistickertext.cpp
    qcp/axis/axistickerpi.cpp
    qcp/axis/axistickerlog.cpp
    qcp/selection.cpp
    qcp/selectionrect.cpp
    qcp/scatterstyle.cpp
    qcp/selectiondecorator-bracket.cpp
    qcp/polar/radialaxis.cpp
    qcp/polar/layoutelement-angularaxis.cpp
    qcp/polar/polargrid.cpp
    qcp/polar/polargraph.cpp
)

set(qcustomplot_HEADERS
    qcp/global.h
    qcp/painter.h
    qcp/paintbuffer.h
    qcp/layer.h
    qcp/axis/range.h
    qcp/axis/labelpainter.h
    qcp/axis/axis.h
    qcp/axis/axisticker.h
    qcp/plottable.h
    qcp/item.h
    qcp/lineending.h
    qcp/core.h
    qcp/layout.h
    qcp/plottables/plottable-graph.h
    qcp/plottables/plottable-curve.h
    qcp/plottables/plottable-bars.h
    qcp/plottables/plottable-statisticalbox.h
    qcp/plottables/plottable-colormap.h
    qcp/plottables/plottable-financial.h
    qcp/plottables/plottable-errorbar.h
    qcp/items/item-straightline.h
    qcp/items/item-line.h
    qcp/items/item-curve.h
    qcp/items/item-rect.h
    qcp/items/item-triangle.h
    qcp/items/item-parallel.h
    qcp/items/item-angle.h
    qcp/items/item-text.h
    qcp/items/item-ellipse.h
    qcp/items/item-pixmap.h
    qcp/items/item-tracer.h
    qcp/items/item-bracket.h
    qcp/layoutelements/layoutelement-axisrect.h
    qcp/layoutelements/layoutelement-legend.h
    qcp/layoutelements/layoutelement-textelement.h
    qcp/layoutelements/layoutelement-colorscale.h
    qcp/colorgradient.h
    qcp/vector2d.h
    qcp/axis/axistickerdatetime.h
    qcp/axis/axistickertime.h
    qcp/axis/axistickerfixed.h
    qcp/axis/axistickertext.h
    qcp/axis/axistickerpi.h
    qcp/axis/axistickerlog.h
    qcp/datacontainer.h
    qcp/selection.h
    qcp/selectionrect.h
    qcp/plottable1d.h
    qcp/scatterstyle.h
    qcp/selectiondecorator-bracket.h
    qcp/polar/radialaxis.h
    qcp/polar/layoutelement-angularaxis.h
    qcp/polar/polargrid.h
    qcp/polar/polargraph.h
)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(LIBRARY_NAME "qt${QT_VERSION_MAJOR}-qcustomplot")

if(BUILD_STATIC)
    add_library(${LIBRARY_NAME} STATIC ${qcustomplot_SRCS} ${qcustomplot_HEADERS})
    target_compile_definitions( ${LIBRARY_NAME} PUBLIC QT_STATIC_BUILD)
else()
    add_library( ${LIBRARY_NAME} SHARED  ${qcustomplot_SRCS} ${qcustomplot_HEADERS})
    target_compile_definitions( ${LIBRARY_NAME} PRIVATE QCUSTOMPLOT_COMPILE_LIBRARY)
endif()

if(BUILD_USE_OPENGL)
    target_compile_definitions( ${LIBRARY_NAME} PUBLIC QCUSTOMPLOT_USE_OPENGL)
endif()

add_library(qcp::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_link_libraries(${LIBRARY_NAME} PUBLIC 
    Qt${QT_VERSION_MAJOR}::Core 
    Qt${QT_VERSION_MAJOR}::Gui 
    Qt${QT_VERSION_MAJOR}::Widgets    
    Qt${QT_VERSION_MAJOR}::OpenGL
    Qt${QT_VERSION_MAJOR}::PrintSupport
)

target_include_directories(${LIBRARY_NAME} PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

if (UNIX AND NOT APPLE)
    if (${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
        find_package(X11 REQUIRED)
        target_link_libraries(${LIBRARY_NAME} PUBLIC X11::xcb)
    else()
        target_link_libraries(${LIBRARY_NAME} PUBLIC xcb)
    endif()
endif()

set_target_properties(${LIBRARY_NAME} PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    CXX_EXTENSIONS OFF
    VERSION ${VERSION_SHORT}
    EXPORT_NAME ${LIBRARY_NAME}
    DEBUG_POSTFIX "d"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if(QT_VERSION_MAJOR STREQUAL "5")
    set_target_properties(${LIBRARY_NAME} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON)
elseif(QT_VERSION_MAJOR STREQUAL "6")
    set_target_properties(${LIBRARY_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)
endif()

install(FILES ${qcustomplot_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_NAME}/qcp
    COMPONENT headers
)
install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/../GPL.txt"
    DESTINATION license/qcp
    COMPONENT license
)

# Export targets for find_package
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${LIBRARY_NAME}ConfigVersion.cmake"
    VERSION ${VERSION_SHORT}
    COMPATIBILITY SameMajorVersion
)

install(TARGETS ${LIBRARY_NAME}
    EXPORT qcustomplotTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_NAME}
)

install(EXPORT qcustomplotTargets
    FILE qcustomplotTargets.cmake
    NAMESPACE qcp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBRARY_NAME}
)

install(FILES cmake/qcustomplotConfig.cmake RENAME ${LIBRARY_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBRARY_NAME}
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBRARY_NAME}
)