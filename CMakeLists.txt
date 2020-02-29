cmake_minimum_required(VERSION 3.5)

if (PROJECT_NAME)
  set(IS_SUBPROJECT TRUE)
endif ()

set(BPSTD_CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(BPSTD_CMAKE_TEMPLATE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(CMAKE_MODULE_PATH "${BPSTD_CMAKE_MODULE_PATH}" "${CMAKE_MODULE_PATH}")

option(BPSTD_COMPILE_UNIT_TESTS "Compile and run the unit tests for this library" OFF)

if (NOT CMAKE_TESTING_ENABLED AND BPSTD_COMPILE_UNIT_TESTS)
  enable_testing()
endif ()

project(string_view_standalone
  VERSION "1.0.0"
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

if ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR
     "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
  add_compile_options(-Wall -Werror -Wextra -pedantic -pedantic-errors)
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
  # TODO: Determine MSVC necessary compiler flags
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
