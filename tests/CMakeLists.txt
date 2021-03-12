# The unit test executable.
set(UNITTEST_TARGET_NAME "unit_tests")

find_package(Catch2 REQUIRED)

set(source_files
    "main.test.cpp"
    "bpstd/string_view.test.cpp"
)

add_executable(unit_tests ${source_files})

target_link_libraries(unit_tests
  PRIVATE ${PROJECT_NAME}
  PRIVATE Catch2::Catch2
)

set_target_properties(${UNITTEST_TARGET_NAME} PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
  COMPILE_DEFINITIONS "$<$<CXX_COMPILER_ID:MSVC>:_SCL_SECURE_NO_WARNINGS>"
  COMPILE_OPTIONS "$<$<CXX_COMPILER_ID:MSVC>:/EHsc;$<$<CONFIG:Release>:/Od>>"
)

add_test(NAME "${UNITTEST_TARGET_NAME}_default"
         COMMAND ${UNITTEST_TARGET_NAME}
         WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
add_test(NAME "${UNITTEST_TARGET_NAME}_all"
         COMMAND ${UNITTEST_TARGET_NAME} "*"
         WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
