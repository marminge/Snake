#include "../include/text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

typedef struct text {
  TTF_Font *pFont;
  SDL_Surface *pSurface;
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
  pText->pSurface = TTF_RenderText_Solid(pText->pFont, string, textColor);
  pText->pTexture =
      SDL_CreateTextureFromSurface(pText->pRenderer, pText->pSurface);
  pText->textRect.w = pText->pSurface->w;
  pText->textRect.h = pText->pSurface->h;
  pText->textRect.x = posX;
  pText->textRect.y = posY;
  return pText;
}

void drawText(Text *pText) {
  SDL_RenderCopy(pText->pRenderer, pText->pTexture, NULL, &(pText->textRect));
}

void destroyText(Text *pText) { SDL_DestroyTexture(pText->pTexture); }
