project(cppreference-pdf)
cmake_minimum_required(VERSION 3.7)

aux_source_directory(src/ src)

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

add_executable(doc ${src})
target_link_libraries(doc ${gq})
target_link_libraries(doc ${gumbo})
target_link_libraries(doc ${wkhtmltopdf})
