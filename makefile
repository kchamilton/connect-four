all:
	gcc -Wall -std=c11 main.c endmenu.c game.c gameboard.c gamestats.c graph.c inputkeys.c mainmenu.c -o play -lncurses