
cmake_minimum_required(VERSION 3.12)
project(CuteMPL
  VERSION 0.0.1
  LANGUAGES CXX
)

################################################################################

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

################################################################################

option(CUTEMPL_ENABLE_TESTS "Enable tests." Off)

################################################################################

set(CMAKE_CXX_STANDARD 20)

################################################################################

add_library(cutempl INTERFACE)
add_library(std::cutempl ALIAS cutempl)

target_include_directories(cutempl INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

################################################################################

install(TARGETS cutempl EXPORT cutemplTargets
  INCLUDES DESTINATION cutempl
)

install(EXPORT cutemplTargets
    FILE cutemplTargets.cmake
    NAMESPACE std::
    DESTINATION cmake
)

export(TARGETS cutempl
    NAMESPACE std::
    FILE cutemplTargets.cmake
)

install(DIRECTORY include/cutempl DESTINATION include)

include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/CuteMPLConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/CuteMPLConfig.cmake
  INSTALL_DESTINATION cmake
)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/CuteMPLConfigVersion.cmake
  COMPATIBILITY SameMajorVersion
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/CuteMPLConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/CuteMPLConfigVersion.cmake
    DESTINATION cmake
)

################################################################################

if(CUTEMPL_ENABLE_TESTS)
  add_subdirectory(tests)
endif()
