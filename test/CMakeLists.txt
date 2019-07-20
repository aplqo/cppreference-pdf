find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

aux_source_directory(. test)
file(TO_NATIVE_PATH ${CMAKE_SOURCE_DIR} data)
add_compile_definitions(SOURCE=${data})

add_executable(unit_test ${test})
target_link_libraries(unit_test ${Boost_LIBRARIES})
target_link_libraries(unit_test util)
