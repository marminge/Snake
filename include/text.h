#ifndef text_h_
#define text_h_

#include <SDL2/SDL_render.h>

typedef struct text Text;

Text *createText(int posX, int posY, SDL_Renderer *pRenderer, char *string);

void drawText(Text *pText);
void destroyText(Text *pText);

#endif
