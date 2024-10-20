#ifndef __SOKOBAN_H__
#define __SOKOBAN_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct s_pos pos;

struct s_pos {
	int pos_x;
	int pos_y;
    pos *next;
};

typedef struct fruits fruits;

struct fruits {
	int pos_x;
	int pos_y;
	int type;
	pos *next;
};

pos *create_list(int x, int y);
int isWinning(char **list);
int isCollectingSpecial(char **board, fruits *fruit);
int mouvement(char **board, char coup, pos *snake, fruits *fruit);
void add_to_list(pos **list, int x, int y);
void delete_list(pos **list);

#endif
