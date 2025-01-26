cmake_minimum_required(VERSION 3.30)
project(fm_24_squad_analyser C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wno-pointer-sign")

if (CMAKE_BUILD_TYPE EQUAL "Debug")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
else ()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
endif ()

include_directories(src)
include_directories(src/roles)

add_executable(
	fm_24_squad_analyser
	src/analyse.c
	src/club.c
	src/date-time.c
	src/player.c
	src/sort.c
	src/strings.c
	src/watch-list.c
	src/wonderkid.c
	src/roles/roles.c
	main.c
)
