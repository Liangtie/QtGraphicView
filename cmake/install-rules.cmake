if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_INSTALL_INCLUDEDIR include/QtGraphicView CACHE PATH "")
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package QtGraphicView)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT QtGraphicView_Development
)

install(
    TARGETS QtGraphicView
    EXPORT QtGraphicViewTargets
    RUNTIME #
    COMPONENT QtGraphicView_Runtime
    LIBRARY #
    COMPONENT QtGraphicView_Runtime
    NAMELINK_COMPONENT QtGraphicView_Development
    ARCHIVE #
    COMPONENT QtGraphicView_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    QtGraphicView_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(QtGraphicView_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${QtGraphicView_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT QtGraphicView_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${QtGraphicView_INSTALL_CMAKEDIR}"
    COMPONENT QtGraphicView_Development
)

install(
    EXPORT QtGraphicViewTargets
    NAMESPACE QtGraphicView::
    DESTINATION "${QtGraphicView_INSTALL_CMAKEDIR}"
    COMPONENT QtGraphicView_Development
)

if(PROJECT_IS_TOP_LEVEL)
    include(CPack)
endif()
