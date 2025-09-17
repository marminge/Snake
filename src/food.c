#include "../include/food.h"
#include <SDL2/SDL_render.h>
#include <stdbool.h>

typedef struct food {
  SDL_Renderer *pRenderer;
  SDL_Rect foodRect;
} Food;

Food *spawnFood(SDL_Renderer *pRenderer, int posX, int posY) {
  Food *pFood = malloc(sizeof(struct food));
  pFood->pRenderer = pRenderer;
  pFood->foodRect.h = 20;
  pFood->foodRect.w = 20;
  pFood->foodRect.x = posX;
  pFood->foodRect.y = posY;
  return pFood;
}

int getFoodPosX(Food *pFood) { return pFood->foodRect.x; }
int getFoodPosY(Food *pFood) { return pFood->foodRect.y; }

void setNewPos(Food *pFood, int x, int y) {
  pFood->foodRect.x = x;
  pFood->foodRect.y = y;
}

void drawFood(Food *pFood) {
  SDL_RenderFillRect(pFood->pRenderer, &(pFood->foodRect));
}
