project(cppreference-pdf)
add_compile_options(-stdlib=libc++)
add_executable(doc filelist.cpp filelist.h link.cpp link.h list.cpp link.h main.cpp parse.cpp parse.h pdf.cpp pdf.h)
target_link_libraries(doc libgumbo libgq libwkhtmltox)
