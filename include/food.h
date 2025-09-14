#ifndef food_h_
#define food_h_
#include <SDL2/SDL_render.h>
#include <stdbool.h>
typedef struct food Food;

Food *spawnFood(SDL_Renderer *pRenderer, int posX, int posY);
void drawFood(Food *pFood);
int getFoodPosX(Food *pFood);
int getFoodPosY(Food *pFood);
void setNewPos(Food *pFood, int x, int y);
#endif
