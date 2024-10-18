#include "snake.h"

pos *create_list(int x, int y)
{
    pos *list = malloc(sizeof(*list));
    list->next = NULL;
    list->pos_x = x;
    list->pos_y = y;

    return list;
}


void add_to_list(pos **list, int x, int y)
{
    pos *tmp = *list;

    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }

    pos *item = malloc(sizeof(*item));
    item->next = NULL;
    item->pos_x = x;
    item->pos_y = y;
    tmp->next = item;
}


int mouvement(char **board, char coup, pos *snake, pos *box) {
    int prev_x = snake->pos_x;
    int prev_y = snake->pos_y;

    int new_x = snake->pos_x;
    int new_y = snake->pos_y;

    if (coup == 'w') {
        new_x++;
    } else if (coup == 's') {
        new_x--;
    } else if (coup == 'a') {
        new_y++;
    } else if (coup == 'd') {
        new_y--;
    }

    if (board[new_x][new_y] == '1' || board[new_x][new_y] == '0') {
        printf("C'est perdu");
        return 1;
    }

    if (board[new_x][new_y] == ' ') {
        pos *current = snake;

        while (current != NULL) {
            board[current->pos_x][current->pos_y] = ' ';
            current = current->next;
        }

        snake->pos_x = new_x;
        snake->pos_y = new_y;

        prev_x = snake->pos_x;
        prev_y = snake->pos_y;

        current = snake->next;
        while (current != NULL) {
            int temp_x = current->pos_x;
            int temp_y = current->pos_y;

            current->pos_x = prev_x;
            current->pos_y = prev_y;

            prev_x = temp_x;
            prev_y = temp_y;

            current = current->next;
        }

        current = snake;
        pos *prev = NULL;

        while (current->next != NULL) {
            prev = current;
            current = current->next;
        }

        current = snake;
        while (current != NULL) {
            board[current->pos_x][current->pos_y] = '0';
            current = current->next;
        }
    } else if (board[new_x][new_y] == '2') {
        add_to_list(&snake, box->pos_x, box->pos_y);

        int new_fruit_x = rand() % 20;
        int new_fruit_y = rand() % 20;
        while (board[new_fruit_x][new_fruit_y] != ' ')
        {
            new_fruit_x = rand() % 20;
            new_fruit_y = rand() % 20;
        }
        board[box->pos_x][box->pos_y] = ' ';
        box->pos_x = new_fruit_x;
        box->pos_y = new_fruit_y;
        board[box->pos_x][box->pos_y] = '2';
    }
    return 0;
}

void insert_after(pos **link, int x, int y)
{
    pos *tmp = *link;
    pos *item = malloc(sizeof(*item));
    item->next = tmp->next;
    item->pos_x = x;
    item->pos_y = y;
    tmp->next = item;
}

void delete_list(pos **list)
{
    pos *tmp = *list;

    while (tmp != NULL)
    {
        pos *to_remove = tmp;
        tmp = tmp->next;
        free(to_remove);
    }
}
