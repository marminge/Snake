#include "../include/food.h"
#include "../include/snake.h"
#include "../include/text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WINDOW_WIDTH 820
#define WINDOW_HEIGHT 820

typedef struct game {
  SDL_Window *pWindow;
  SDL_Renderer *pRenderer;
  Snake *pSnake;
  Snake *snakes[50];
  int totalSnakes;
  Food *pFood;
  Text *pText;
} Game;

bool init(Game *pGame);
void run(Game *pGame);
void handleInput(Game *pGame, bool *quitGame);
void gameCleanup(Game *pGame);
int generateNum();
bool collideWithFood(Game *pGame);

int main(int argc, char *argv[]) {
  Game game;
  init(&game);
  run(&game);
  gameCleanup(&game);
  return 0;
}

void run(Game *pGame) {
  bool quitGame = false;
  while (!quitGame) {
    handleInput(pGame, &quitGame);
    SDL_Delay(150);
    SDL_SetRenderDrawColor(pGame->pRenderer, 0, 0, 0, 0);
    SDL_RenderClear(pGame->pRenderer);
    updateSnake(pGame->snakes, &(pGame->totalSnakes));

    if (hitWall(pGame->snakes[0]) ||
        hitItself(pGame->snakes, &(pGame->totalSnakes))) {
      SDL_SetRenderDrawColor(pGame->pRenderer, 0, 0, 0, 0);
      drawText(pGame->pText);
      SDL_RenderPresent(pGame->pRenderer);
      SDL_Delay(3000);
      quitGame = true;
    }

    if (collideWithFood(pGame)) {
      setNewPos(pGame->pFood, generateNum(), generateNum());
      eatFood(pGame->snakes, &(pGame->totalSnakes), pGame->pRenderer);
    }

    SDL_SetRenderDrawColor(pGame->pRenderer, 230, 0, 0, 0);
    drawFood(pGame->pFood);
    SDL_SetRenderDrawColor(pGame->pRenderer, 0, 230, 0, 0);
    for (int i = 0; i < pGame->totalSnakes; i++) {
      drawSnake(pGame->pRenderer, pGame->snakes, i);
    }
    SDL_RenderPresent(pGame->pRenderer);
  }
}

bool init(Game *pGame) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    return false;
  }

  if (TTF_Init() == -1) {
    fprintf(stderr, "Error initializing TTF: %s\n", SDL_GetError());
    return false;
  }

  pGame->pWindow = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                    WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
  if (pGame->pWindow == NULL) {
    fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
    return false;
  }
  pGame->pRenderer =
      SDL_CreateRenderer(pGame->pWindow, -1, SDL_RENDERER_ACCELERATED);
  if (pGame->pRenderer == NULL) {
    fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
    return false;
  }
  SDL_SetRenderDrawColor(pGame->pRenderer, 0, 0, 0, 255);
  SDL_RenderClear(pGame->pRenderer);

  srand(time(NULL));
  pGame->pFood = spawnFood(pGame->pRenderer, generateNum(), generateNum());
  pGame->totalSnakes = 0;
  pGame->snakes[pGame->totalSnakes] =
      createSnake(pGame->pRenderer, &(pGame->totalSnakes),
                  WINDOW_WIDTH / 2 + 10, WINDOW_HEIGHT / 2 + 10);
  pGame->pText = createText(200, 200, pGame->pRenderer, "Game Over!");
  return true;
}

void handleInput(Game *pGame, bool *quitGame) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      *quitGame = true;
      break;
    case SDL_KEYDOWN:
      switch (e.key.keysym.scancode) {
      case SDL_SCANCODE_ESCAPE:
        *quitGame = true;
        break;
      case SDL_SCANCODE_UP:
        getInput(&(pGame->snakes[0]), 0, -1);
        break;
      case SDL_SCANCODE_DOWN:
        getInput(&(pGame->snakes[0]), 0, 1);
        break;
      case SDL_SCANCODE_LEFT:
        getInput(&(pGame->snakes[0]), -1, 0);
        break;
      case SDL_SCANCODE_RIGHT:
        getInput(&(pGame->snakes[0]), 1, 0);
        break;
      case SDL_SCANCODE_SPACE:
        eatFood(pGame->snakes, &(pGame->totalSnakes), pGame->pRenderer);
      default:
        break;
      }
    default:
      break;
    }
  }
}

int generateNum() { return (rand() % (40 + 1) * 20); }

bool collideWithFood(Game *pGame) {
  return (getSnakePosX(pGame->snakes, 0) == getFoodPosX(pGame->pFood) &&
          getSnakePosY(pGame->snakes, 0) == getFoodPosY(pGame->pFood));
}

void gameCleanup(Game *pGame) {
  SDL_DestroyRenderer(pGame->pRenderer);
  destroyText(pGame->pText);
  TTF_Quit();
  SDL_DestroyWindow(pGame->pWindow);
  SDL_Quit();
}
