#include "snake.h"


int main(){
    char ** str_tab = malloc(21 * sizeof(*str_tab)); // Création du plateau
    for (int i = 0; i < 21; i++) {
        str_tab[i] = malloc(21 * sizeof(*str_tab));
    }

    for (int i = 0; i < 21; i++) // Ajout des cases (vides, murs, ...)
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
    int counterMouvement = (rand()%(400 - 60 + 1) + 60); // initialise un nombre aléatoire au bout du quel l'aliment magique apparait
    int counter = 0;

    pos *snake = create_list(3, 6); // Initialisation des positions initiales du serpent
    add_to_list(&snake, 3, 5);
    add_to_list(&snake, 3, 4);
    add_to_list(&snake, 3, 3);

    fruits *fruit = malloc(sizeof(*fruit)); // Initialisation du fruit
    fruit->pos_x = 5;
    fruit->pos_y = 3;
    fruit->type = 1;


    pos *current = snake;
    
    while(current->next != NULL){
        str_tab[current->pos_x][current->pos_y] = '0';
        current = current->next;
    }

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
    char current_direction = 'a'; // Par défaut le serpent va à gauche
    int move_timer = 0;
    SDL_FreeSurface(surface);  
    int isRunning = 1;
    
    while (isRunning) {
        if (isWinning(str_tab) == 0){
            isRunning = 0;
            printf("C'est gagné !\n");
            return 0;
        } 

        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                isRunning = 0;
            } else if (e.type == SDL_KEYDOWN) { // En fonction de la touche alors le mouvement va s’effectuer
                if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT){
                    if(mouvement(str_tab, 'a', snake, fruit) == 1) {
                        return 0;
                    }
                    counter ++;
                    current_direction = 'a';
                } else if (e.key.keysym.scancode == SDL_SCANCODE_LEFT){
                    if(mouvement(str_tab, 'd', snake, fruit) == 1) {
                        return 0;
                    }
                    counter++;
                    current_direction = 'd';
                } else if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
                    if (mouvement(str_tab, 's', snake, fruit) == 1) {
                        return 0;
                    }
                    counter++;
                    current_direction = 's';
                } else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN){
                    if (mouvement(str_tab, 'w', snake, fruit) == 1){
                        return 0;
                    }
                    counter++;
                    current_direction = 'w';
                }
            }
        }
        
        if ((counter < counterMouvement) || isCollectingSpecial(str_tab, fruit) != 0) // Si le fruit spécial est collecté ou si le compteur est inférieur au nombre aléatoire alors le serpent avance automatiquement 
        {
            move_timer++;
            if (move_timer >= 300) {
                if (mouvement(str_tab, current_direction, snake, fruit) == 1) {
                    return 0;
                }
                move_timer = 0;
                counter++;
            }
        }
        
        SDL_RenderClear(renderer);

        if (counter == counterMouvement) {  // Si le nombre d’action est égal au nombre aléatoire d’apparition du carré alors le nombre du carré change pour changer ensuite dans l’affichage
            fruit->type = 2;
            str_tab[fruit->pos_x][fruit->pos_y] = '3';
        }

        for (int i = 0; i < 21; i++){ // Affichage des couleurs en fonction du nombre stocké dans str_tab 
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
                }
            }
        }
        SDL_RenderPresent(renderer);
    }
    SDL_Quit();
    for (int i = 0; i < 21; i++) { // Libération de la mémoire
        free(str_tab[i]);
    }
    free(str_tab);

    free(snake);
    free(fruit);

    return 0;
}
