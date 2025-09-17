#include "../include/snake.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
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

Snake *createSnake(int *totalSnakes, int posX, int posY) {
  Snake *pSnake = malloc(sizeof(struct snake));
  pSnake->snakeRect.h = 20;
  pSnake->snakeRect.w = 20;
  pSnake->snakeRect.x = posX;
  pSnake->snakeRect.y = posY;
  pSnake->xSpeed = 0;
  pSnake->ySpeed = 0;
  *totalSnakes += 1;
  return pSnake;
}

Snake *createTail(Snake *snakes[50], int *totalSnakes) {
  Snake *pTail = malloc(sizeof(struct snake));
  pTail->snakeRect.h = 20;
  pTail->snakeRect.w = 20;
  pTail->snakeRect.x = snakes[*totalSnakes - 1]->snakeRect.x;
  pTail->snakeRect.y = snakes[*totalSnakes - 1]->snakeRect.y;
  *totalSnakes += 1;
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
  move(snakes);
}

void move(Snake *snakes[50]) {
  snakes[0]->snakeRect.x = snakes[0]->snakeRect.x + snakes[0]->xSpeed * 20;
  snakes[0]->snakeRect.y = snakes[0]->snakeRect.y + snakes[0]->ySpeed * 20;
}

void eatFood(Snake *snakes[50], int *totalSnakes) {
  snakes[*totalSnakes] = createTail(snakes, totalSnakes);
}

bool hitItself(Snake *snakes[50], int *totalSnakes) {
  if (*totalSnakes > 1) {
    for (int i = 1; i < *totalSnakes; i++) {
      if (SDL_HasIntersection(&(snakes[0]->snakeRect),
                              &(snakes[i]->snakeRect))) {
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
