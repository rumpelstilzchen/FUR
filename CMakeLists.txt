cmake_minimum_required (VERSION 2.8)
project (FUR)
include_directories (libtcod-1.5.0/include)
include_directories (include)
link_directories (${LINK_DIRECTORIES} libtcod-1.5.0)
add_executable (fur src/main src/util src/wall
	       	    src/player src/level src/inputmgr src/gamemgr src/direction
		    src/objfact
		    src/door src/button src/enemy src/filetostrings src/solution)
target_link_libraries (fur tcodxx tcod)
