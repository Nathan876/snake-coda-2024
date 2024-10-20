#include "snake.h"

pos *create_list(int x, int y) // La fonction permet de créer une liste de position
{
    pos *list = malloc(sizeof(*list));
    list->next = NULL;
    list->pos_x = x;
    list->pos_y = y;

    return list;
}

int isWinning(char **list){ // La fonction permet de vérifier si le joueur a gagné
    int isTrue = 0;
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (list[i][j] ==  ' ' || list[i][j] == '2'){ // Si il n'y a plus de case de libre et il n'y a pas d'aliment alors le joueur a gagné
                isTrue = 1;
                return isTrue;
            }
        }
    }
    return isTrue;
}


void add_to_list(pos **list, int x, int y) // La fonction ajoute à la fin de la liste une nouvelle position
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

int isCollectingSpecial(char **board, fruits *fruit){ // La fonction permet de savoir si le joueur a collecté le fruit spécial
    if (board[fruit->pos_x][fruit->pos_y] == '3') {
        return 1;
    }
    return 0;
}

int mouvement(char **board, char coup, pos *snake, fruits *fruit) { // La fonction mouvement gère le déplacement du serpent
    int prev_x = snake->pos_x; // Stocke les positions actuelles du serpent
    int prev_y = snake->pos_y;

    int new_x = snake->pos_x; // Stocke les positions actuelles du serpent
    int new_y = snake->pos_y;

    if (coup == 'w') { // En fonction de la lettre passée en paramètre le code modifie le paramètre du sens
        new_x++;
    } else if (coup == 's') {
        new_x--;
    } else if (coup == 'a') {
        new_y++;
    } else if (coup == 'd') {
        new_y--;
    }

    if (board[new_x][new_y] == '1' || board[new_x][new_y] == '0') { // Si le joueur touche un mur ou que le serpent se mord c'est perdu
        printf("C'est perdu !\n");
        return 1;
    }

    if (board[new_x][new_y] == ' ') { // Si la nouvelle position est libre alors le serpent se déplace sans s'agrandir
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

    } else if (board[new_x][new_y] == '2' || board[new_x][new_y] == '3') { // Si sur la nouvelle position se trouve un fruit alors le serpent le mange et s'agrandit
        add_to_list(&snake, fruit->pos_x, fruit->pos_y);

        int new_fruit_x = rand() % 20;
        int new_fruit_y = rand() % 20;
        while (board[new_fruit_x][new_fruit_y] != ' ') // Une nouvelle position aléatoire est définie pour le fruit
        {
            new_fruit_x = rand() % 20;
            new_fruit_y = rand() % 20;
        }
        board[fruit->pos_x][fruit->pos_y] = ' ';
        fruit->pos_x = new_fruit_x;
        fruit->pos_y = new_fruit_y;
        board[fruit->pos_x][fruit->pos_y] = '2';
    }
    return 0;
}


void delete_list(pos **list) // Permet d'effacer la mémoire allouer pour le plateau
{
    pos *tmp = *list;

    while (tmp != NULL)
    {
        pos *to_remove = tmp;
        tmp = tmp->next;
        free(to_remove);
    }
}
