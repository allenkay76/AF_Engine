#pragma once
#include <SDL2/SDL.h>

struct SDLRenderData{
        SDL_Window* sdlWindowPtr;  //pointer to sdlWindow
        SDL_Renderer* sdlRendererPtr;  //pointer to sdlRenderer

        //can only load 1 image for now. replace with method to load multiple images
        SDL_Surface* sdlSurfacePtr;  //pointer to sdlSurface

        SDL_Surface* sdlImageSurface; //pointer to sdlImageSurface

        ImageData* imagePtr; //pointer to image

    };