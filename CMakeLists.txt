cmake_minimum_required(VERSION 3.30)
project(fm_24_squad_analyser C)

set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(src/roles)

add_executable(
	fm_24_squad_analyser
	src/analyse.c
	src/date-time.c
	src/player.c
	src/strings.c
	src/watch-list.c
	src/wonderkid.c
	src/roles/roles.c
	main.c
)
