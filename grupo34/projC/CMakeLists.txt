cmake_minimum_required(VERSION 3.15)
project(LI3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(include)
include_directories(src)
FILE(GLOB MyCIncludes include/*.h)
FILE(GLOB MyCSources src/*.c)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

add_executable(LI3
        ${MyCIncludes}
        ${MyCSources} include/types.h src/main.c src/month.c include/month.h src/filialID.c include/filialID.h src/navegador.c include/navegador.h include/colors.h)

add_definitions(${GLIB_CFLAGS_OTHER})
target_link_libraries(LI3 ${GLIB_LIBRARIES})