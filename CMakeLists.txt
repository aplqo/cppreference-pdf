project(cppreference-pdf)
cmake_minimum_required(VERSION 3.7)

aux_source_directory(src/ src)
list(FILTER src EXCLUDE REGEX "main.cpp")

if(CMAKE_BUILD_TYPE EQUAL "Debug")
	aux_source_directory(debug/ debug)
	add_definitions(-DDEBUG)
endif()

function(is_found lib lib_name)
	if(lib MATCHES "NOTFOUND")
		message(FATAL_ERROR "Can't find ${lib_name}")
	else()
		message(STATUS "Found ${lib_name} at ${lib}")
	endif()
endfunction()

find_library(gumbo gumbo)
is_found(${gumbo} "libgumbo")
find_library(gq gq)
is_found(${gq} "libgq")
find_library(wkhtmltopdf wkhtmltox)
is_found(${wkhtmltopdf} "wkhtmltox")

if( CMAKE_CXX_COMPILER MATCHES "clang")
	add_compile_options(-std=c++17 -stdlib=libc++ -lc++fs -lc++abi)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld-8 -lc++abi -stdlib=libc++ -lc++fs")
endif()

add_library(util STATIC ${src})
target_link_libraries(util ${gq})
target_link_libraries(util ${gumbo})
target_link_libraries(util ${wkhtmltopdf})

if(CMAKE_BUILD_TYPE EQUAL "Debug")
	add_executable(doc src/main.cpp ${debug})
else()
	add_executable(doc src/main.cpp)
endif()
target_link_libraries(doc util)

#unit test
add_subdirectory(test)

add_custom_target(test COMMAND ${CMAKE_BINARY_DIR}/test/unit_test)
add_custom_target(time COMMAND ${CMAKE_BINARY_DIR}/test/unit_test --log_level=all)
