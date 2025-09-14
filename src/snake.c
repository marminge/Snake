#include "../include/snake.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdlib.h>
#define WINDOW_WIDTH 820
#define WINDOW_HEIGHT 820

typedef struct snake {
  int xSpeed, ySpeed;
  SDL_Renderer *pRenderer;
  SDL_Rect snakeRect;
} Snake;

Snake *createSnake(SDL_Renderer *pRenderer, int *totalSnakes, int posX,
                   int posY) {
  Snake *pSnake = malloc(sizeof(struct snake));
  pSnake->pRenderer = pRenderer;
  SDL_Rect snakeRect;
  snakeRect.h = 20;
  snakeRect.w = 20;
  snakeRect.x = posX;
  snakeRect.y = posY;
  pSnake->snakeRect = snakeRect;
  pSnake->xSpeed = 0;
  pSnake->ySpeed = 0;
  *totalSnakes = *totalSnakes + 1;
  return pSnake;
}

Snake *createTail(SDL_Renderer *pRenderer, Snake *snakes[50],
                  int *totalSnakes) {
  Snake *pTail = malloc(sizeof(struct snake));
  pTail->pRenderer = pRenderer;
  SDL_Rect snakeRect;
  snakeRect.h = 20;
  snakeRect.w = 20;
  snakeRect.x = snakes[*totalSnakes - 1]->snakeRect.x;
  snakeRect.y = snakes[*totalSnakes - 1]->snakeRect.y;
  pTail->snakeRect = snakeRect;
  *totalSnakes = *totalSnakes + 1;
  return pTail;
}

int getSnakePosX(Snake *snakes[50], int i) { return snakes[i]->snakeRect.x; }
int getSnakePosY(Snake *snakes[50], int i) { return snakes[i]->snakeRect.y; }

void drawSnake(SDL_Renderer *pRenderer, Snake *snakes[50], int i) {
  SDL_RenderFillRect(pRenderer, &(snakes[i]->snakeRect));
}

void getInput(Snake *snakes[50], int xSpeed, int ySpeed) {
  if (snakes[0]->xSpeed * -1 != xSpeed || snakes[0]->ySpeed * -1 != ySpeed) {
    snakes[0]->xSpeed = xSpeed;
    snakes[0]->ySpeed = ySpeed;
  }
}

void updateSnake(Snake *snakes[50], int *totalSnakes) {
  if (*totalSnakes > 0) {
    for (int i = *totalSnakes - 1; i >= 1; i--) {
      snakes[i]->snakeRect.x = snakes[i - 1]->snakeRect.x;
      snakes[i]->snakeRect.y = snakes[i - 1]->snakeRect.y;
    }
  }
  snakes[0]->snakeRect.x = snakes[0]->snakeRect.x + snakes[0]->xSpeed * 20;
  snakes[0]->snakeRect.y = snakes[0]->snakeRect.y + snakes[0]->ySpeed * 20;
}

void eatFood(Snake *snakes[50], int *totalSnakes, SDL_Renderer *pRenderer) {
  snakes[*totalSnakes] = createTail(pRenderer, snakes, totalSnakes);
}

bool hitItself(Snake *snakes[50], int *totalSnakes) {
  if (*totalSnakes > 1) {
    for (int i = 1; i < *totalSnakes; i++) {
      if (snakes[0]->snakeRect.x == snakes[i]->snakeRect.x &&
          snakes[0]->snakeRect.y == snakes[i]->snakeRect.y) {
        return true;
      }
    }
  }
  return false;
}

bool hitWall(Snake *pSnake) {
  return (pSnake->snakeRect.x >= WINDOW_WIDTH || pSnake->snakeRect.x < 0 ||
          pSnake->snakeRect.y >= WINDOW_HEIGHT || pSnake->snakeRect.y < 0);
}
