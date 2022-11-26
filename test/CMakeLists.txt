cmake_minimum_required(VERSION 3.14)

project(QtGraphicViewTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)
include(../cmake/windows-set-path.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(QtGraphicView REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(QtGraphicView_test source/QtGraphicView_test.cpp)
target_link_libraries(QtGraphicView_test PRIVATE QtGraphicView::QtGraphicView)
target_compile_features(QtGraphicView_test PRIVATE cxx_std_17)

add_test(NAME QtGraphicView_test COMMAND QtGraphicView_test)
windows_set_path(QtGraphicView_test QtGraphicView::QtGraphicView)

# ---- End-of-file commands ----

add_folders(Test)
