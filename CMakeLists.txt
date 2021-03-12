cmake_minimum_required(VERSION 3.5)

if (PROJECT_NAME)
  set(IS_SUBPROJECT TRUE)
endif ()

set(BPSTD_CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(BPSTD_CMAKE_TEMPLATE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/templates")

set(CMAKE_MODULE_PATH "${BPSTD_CMAKE_MODULE_PATH}" "${CMAKE_MODULE_PATH}")

option(BPSTD_COMPILE_UNIT_TESTS "Compile and run the unit tests for this library" OFF)

if (NOT CMAKE_TESTING_ENABLED AND BPSTD_COMPILE_UNIT_TESTS)
  enable_testing()
endif ()

project(string_view_standalone
  VERSION "1.1.0"
  LANGUAGES CXX
)

# If using conan, only set the find paths. This project is trying to be
# fully CMake
if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake")
  include("${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake")
  conan_set_find_paths()
endif ()

##############################################################################
# Targets
##############################################################################

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(header_files
  "include/bpstd/string_view.hpp"
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(BPSTD::${PROJECT_NAME} ALIAS string_view_standalone)

target_include_directories(${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  INTERFACE $<INSTALL_INTERFACE:include>
)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" AND
    "${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
  # clang-cl does not appear to implement '-pedantic' or 'pedantic-errors',
  # so this case needs to be handled specifically
  add_compile_options(-Wall -Werror -Wextra)

  # Disable the ridiculous compatibility warnings, since it fails on files not
  # ending in newlines
  add_compile_options(-Wno-c++98-compat -Wno-c++98-compat-pedantic)

  # This gives an unbelievable amount of false-positives spuriously. Ignore it.
  add_compile_options(-Wno-unneeded-member-function)
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR
        "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
  add_compile_options(-Wall -Werror -Wextra -pedantic -pedantic-errors)
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
  add_compile_options(/W4 /WX)
endif ()

# Header Self-Containment Tests

include(AddSelfContainmentTest)

if (BPSTD_COMPILE_UNIT_TESTS)
  add_self_containment_test(${PROJECT_NAME}.SelfContainmentTest
    TARGET ${PROJECT_NAME}
    HEADERS ${header_files}
  )

  add_subdirectory("tests")
endif ()

##############################################################################
# Installation
##############################################################################

if (IS_SUBPROJECT)
  return()
endif ()

include(CMakePackageConfigHelpers)

# The generated ConfigVersion is tied to the architecture it's generated on,
# denoted by the size of the pointer. Since this is a header-only library,
# this is an unnecessary and constricting check -- but CMake does not allow us
# to customize it.
#
# A simple workaround is to simply set the CMAKE_SIZEOF_VOID_P to an empty
# string in CMake so that the generated file does not fail to work on different
# architectures. This gets reset after we generate the file
set(TEMP_CMAKE_SIZEOF_VOID_P ${CMAKE_SIZEOF_VOID_P})
set(CMAKE_SIZEOF_VOID_P "")
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  COMPATIBILITY
    SameMajorVersion
)
set(CMAKE_SIZEOF_VOID_P ${TEMP_CMAKE_SIZEOF_VOID_P})

configure_file(
  "${BPSTD_CMAKE_TEMPLATE_PATH}/PackageConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  @ONLY
)

#-----------------------------------------------------------------------------

include(GNUInstallDirs)

set(BPSTD_CMAKE_CONFIG_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

# Includes
install(
  DIRECTORY "single_include/"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Targets
install(
  TARGETS "string_view_standalone"
  EXPORT "string_view_standalone_targets"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
install(
  EXPORT "string_view_standalone_targets"
  NAMESPACE "BPSTD::"
  DESTINATION "${BPSTD_CMAKE_CONFIG_DESTINATION}"
)
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  DESTINATION "${BPSTD_CMAKE_CONFIG_DESTINATION}"
)
