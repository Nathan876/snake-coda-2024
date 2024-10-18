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

pos *create_list(int x, int y);
void sort_in_list(pos **list, int x, int y);
int mouvement(char **board, char coup, pos *snake, pos *box);
void add_to_list(pos **list, int x, int y);
void insert_after(pos **link, int x, int y);
void delete_list(pos **list);

#endif
