#ifndef snake_h_
#define snake_h_
#include <SDL2/SDL_render.h>
#include <stdbool.h>
typedef struct snake Snake;
Snake *createSnake(SDL_Renderer *pRenderer, int *totalSnakes, int posX,
                   int posY);
Snake *createTail(SDL_Renderer *pRenderer, Snake *snakes[50], int *totalSnakes);
void drawSnake(SDL_Renderer *pRenderer, Snake *snakes[50], int i);
void getInput(Snake *snakes[50], int xSpeed, int ySpeed);
void updateSnake(Snake *snakes[50], int *totalSnakes);
void eatFood(Snake *snakes[50], int *totalSnakes, SDL_Renderer *pRenderer);
bool hitWall(Snake *pSnake);
bool hitItself(Snake *snakes[50], int *totalSnakes);
int getSnakePosX(Snake *snakes[50], int i);
int getSnakePosY(Snake *snakes[50], int i);
#endif
