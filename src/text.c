#include "../include/text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

typedef struct text {
  TTF_Font *pFont;
  SDL_Texture *pTexture;
  SDL_Renderer *pRenderer;
  SDL_Rect textRect;
} Text;

Text *createText(int posX, int posY, SDL_Renderer *pRenderer, char *string) {
  Text *pText = malloc(sizeof(struct text));
  pText->pRenderer = pRenderer;
  SDL_Color textColor = {230, 230, 230};
  pText->pFont = TTF_OpenFont("Montserrat-Regular.ttf", 64);
  if (pText->pFont == 0) {
    fprintf(stderr, "Error opening font: %s", SDL_GetError());
  }
  SDL_Surface *pSurface = TTF_RenderText_Solid(pText->pFont, string, textColor);
  pText->pTexture = SDL_CreateTextureFromSurface(pText->pRenderer, pSurface);
  pText->textRect.w = pSurface->w;
  pText->textRect.h = pSurface->h;
  pText->textRect.x = posX;
  pText->textRect.y = posY;
  SDL_FreeSurface(pSurface);
  return pText;
}

void drawText(Text *pText) {
  SDL_RenderCopy(pText->pRenderer, pText->pTexture, NULL, &(pText->textRect));
}

void destroyText(Text *pText) { SDL_DestroyTexture(pText->pTexture); }
