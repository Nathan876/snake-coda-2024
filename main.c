#include "snake.h"

int main(){
    char ** str_tab = malloc(21 * sizeof(*str_tab));
    for (int i = 0; i < 21; i++) {
        str_tab[i] = malloc(21 * sizeof(*str_tab));
    }

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (i == 0) {
                str_tab[i][j] = '1';
            } else if (i == 20) {
                str_tab[i][j] = '1';
            } else if (j == 0 || j == 20) {
                str_tab[i][j] = '1';
            } else if (i == 5 && j == 3) {
                str_tab[i][j] = '2';
            } else {
                str_tab[i][j] = ' ';
            }
        }
        
    }

    pos *snake = create_list(3, 6);
    add_to_list(&snake, 3, 5);
    add_to_list(&snake, 3, 4);
    add_to_list(&snake, 3, 3);

    pos *fruit = malloc(sizeof(*fruit));
    fruit->pos_x = 5;
    fruit->pos_y = 3;

    pos *current = snake;
    while(current->next != NULL){
        str_tab[current->pos_x][current->pos_y] = '0';
        current = current->next;
    }
 
    for (int i = 0; i < 21; i++)
    {
        printf("%c %c %c %c %c %c %c %c %c %c\n", str_tab[i][0], str_tab[i][1], str_tab[i][2], str_tab[i][3], str_tab[i][4], str_tab[i][5], str_tab[i][6], str_tab[i][7], str_tab[i][8], str_tab[i][9]);
    }


    int tile_size = 16;
    int grid_width = 20;
    int grid_height = 20;
    int window_width = tile_size * grid_width;
    int window_height = tile_size * grid_height;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        printf("Error SDL2 Init : %s\n", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("Erreur d'initialisation de la SDL_Image\n");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 340, 340, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        printf("Error while creating a window : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur à la création du renderer\n");
        return 1;
    }

    SDL_Surface* surface = IMG_Load("levels.png");
    if (surface == NULL) 
    {
        printf("Error loading image %s\n", IMG_GetError());
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) 
    {
        printf("Error creating texture\n");
        return 1;
    }
    char current_direction = 'a';
    int move_timer = 0;
    SDL_FreeSurface(surface);  
    int isRunning = 1;
    
    while (isRunning) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                isRunning = 0;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT){
                    if(mouvement(str_tab, 'a', snake, fruit) == 1) {
                        return 0;
                    }
                    current_direction = 'a';
                } else if (e.key.keysym.scancode == SDL_SCANCODE_LEFT){
                    if(mouvement(str_tab, 'd', snake, fruit) == 1) {
                        return 0;
                    }
                    current_direction = 'd';
                } else if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
                    if (mouvement(str_tab, 's', snake, fruit) == 1) {
                        return 0;
                    }
                    current_direction = 's';
                } else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN){
                    if (mouvement(str_tab, 'w', snake, fruit) == 1){
                        return 0;
                    }
                    current_direction = 'w';
                }
            }
        }
        
        move_timer++;
        if (move_timer >= 300) {
            if (mouvement(str_tab, current_direction, snake, fruit) == 1) {
                return 0;
            }
            move_timer = 0;
        }
        SDL_RenderClear(renderer);

        for (int i = 0; i < 21; i++){
            for (int j = 0; j < 21; j++){
                if(str_tab[i][j] == '0'){
                    SDL_Rect rect = {j * 16, i * 16, 16, 16};
                    SDL_Rect rect_img = {0,0, 16, 16};
                    SDL_RenderCopy(renderer, texture, &rect_img, &rect);
                } else if(str_tab[i][j] == '1') {
                    SDL_Rect rect = {j * 16, i * 16, 16, 16};
                    SDL_Rect rect_img = {16,0, 16, 16};
                    SDL_RenderCopy(renderer, texture, &rect_img, &rect);
                } else if(str_tab[i][j] == '2') {
                    SDL_Rect rect = {j * 16, i * 16, 16, 16};
                    SDL_Rect rect_img = {32,0, 16, 16};
                    SDL_RenderCopy(renderer, texture, &rect_img, &rect);
                } else if(str_tab[i][j] == '3') {
                    SDL_Rect rect = {j * 16, i * 16, 16, 16};
                    SDL_Rect rect_img = {48,0, 16, 16};
                    SDL_RenderCopy(renderer, texture, &rect_img, &rect);
                } else if(str_tab[i][j] == '4') {
                    SDL_Rect rect = {j * 16, i * 16, 16, 16};
                    SDL_Rect rect_img = {64,0, 16, 16};
                    SDL_RenderCopy(renderer, texture, &rect_img, &rect);
                }
            }
        }
        SDL_RenderPresent(renderer);
    }
    SDL_Quit();
    for (int i = 0; i < 21; i++) {
        free(str_tab[i]);
    }
    free(str_tab);
    delete_list(snake);
    free(fruit);
  
    return 0;
}
