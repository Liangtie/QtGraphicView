cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
  QtGraphicView
  VERSION 0.1.0
  DESCRIPTION "Short description"
  HOMEPAGE_URL "https://example.com/"
  LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)
include(cmake/link_qt.cmake)

# ---- Declare library ----
add_library(
  QtGraphicView
  source/QtGraphicView.cpp
  source/FlowStyleCollection.cpp
)

target_link_libraries(QtGraphicView ${QT_LIBRARIES})
add_library(QtGraphicView::QtGraphicView ALIAS QtGraphicView)

include(GenerateExportHeader)
generate_export_header(
  QtGraphicView
  BASE_NAME QtGraphicView
  EXPORT_FILE_NAME export/QtGraphicView/QtGraphicView_export.hpp
  CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(QtGraphicView PUBLIC QTGRAPHICVIEW_STATIC_DEFINE)
endif()

set_target_properties(
  QtGraphicView PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN YES
  VERSION "${PROJECT_VERSION}"
  SOVERSION "${PROJECT_VERSION_MAJOR}"
  EXPORT_NAME QtGraphicView
  OUTPUT_NAME QtGraphicView
)

target_include_directories(
  QtGraphicView ${warning_guard}
  PUBLIC
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
  QtGraphicView SYSTEM
  PUBLIC
  "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(QtGraphicView PUBLIC cxx_std_17)

# ---- Install rules ----
if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

add_subdirectory(test)

# ---- Developer mode ----
if(NOT QtGraphicView_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
    AUTHOR_WARNING
    "Developer mode is intended for developers of QtGraphicView"
  )
endif()

include(cmake/dev-mode.cmake)
