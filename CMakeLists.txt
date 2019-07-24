project(cppreference-pdf)
cmake_minimum_required(VERSION 3.7)

if( CMAKE_CXX_COMPILER MATCHES "clang")
	add_compile_options(-std=c++17 -stdlib=libc++ -lc++fs -lc++abi)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld-8 -lc++abi -stdlib=libc++ -lc++fs")
endif()

add_subdirectory(src)

#unit test
add_subdirectory(test)

add_custom_target(test COMMAND ${CMAKE_BINARY_DIR}/test/unit_test)
add_custom_target(time COMMAND ${CMAKE_BINARY_DIR}/test/unit_test --log_level=all)
