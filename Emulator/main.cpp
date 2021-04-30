#include <stdio.h>
#include <SDL2/SDL.h>
#include "cpu.h"
int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Texture *texture = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "MicroKime",             // window title
        SDL_WINDOWPOS_UNDEFINED, // initial x position
        SDL_WINDOWPOS_UNDEFINED, // initial y position
        640,                     // width, in pixels
        480,                     // height, in pixels
        SDL_WINDOW_OPENGL        // flags - see below
    );

    if (window == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    int fake = 0;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA4444, SDL_TEXTUREACCESS_STREAMING, 640, 480);
    SDL_Event e;
    CPU cpu;
    while (true)
    {
        cpu.emulate_cycle();
        cpu.pc += 4;
        fake++;
        if (fake == 6000)
        {
            //update_gpu(cpu);
            fake = 0;
            SDL_UpdateTexture(texture, NULL, &cpu.mem->vram, 480 * 4);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);

            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT)
            {
                SDL_Log("Program quit after %i ticks", e.quit.timestamp);
                break;
            }
        }

        /* code */
    }

    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();
    return 0;
}