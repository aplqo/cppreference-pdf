project(cppreference-pdf)
cmake_minimum_required(VERSION 3.7)

if( CMAKE_CXX_COMPILER MATCHES "clang")
	add_compile_options(-stdlib=libc++)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld-8 -stdlib=libc++ -lc++fs")
endif()

option(UNIT_TEST OFF)
option(RUN OFF)

add_subdirectory(src)

#unit test
if(UNIT_TEST)
	add_subdirectory(test)

	add_custom_target(test COMMAND ${CMAKE_BINARY_DIR}/test/unit_test)
	add_custom_target(time COMMAND ${CMAKE_BINARY_DIR}/test/unit_test --log_level=all)
endif()

if(RUN)
	add_custom_target(run COMMAND ${CMAKE_BINARY_DIR}/src/doc ${RUN_HTML} ${RUN_PDF})
endif()
