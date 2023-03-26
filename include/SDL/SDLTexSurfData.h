#pragma once
#include <memory>
#include <SDL2/SDL.h>
using namespace std;
struct SDLTexSurfData {
    unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texturePtr{nullptr, &SDL_DestroyTexture};
    unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surfacePtr{nullptr, &SDL_FreeSurface};
};
