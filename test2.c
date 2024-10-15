#include <stdio.h>
#include <stdbool.h>

#include "SDL.h" 

#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


//game objects

struct player
{
    int y;
};

struct computer
{
    int y;
    int speed;
};

void draw_game();
void gameloop();

int main(int argc, char* argv[])
{
    // Unused argc, argv
    (void) argc;
    (void) argv;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialized!\n"
               "SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    #if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
        // Disable compositor bypass
        if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
        {
            printf("SDL can not disable compositor bypass!\n");
            return 0;
        }
    #endif

        // Create window
        SDL_Window *window = SDL_CreateWindow("Pong",
                                              SDL_WINDOWPOS_UNDEFINED,
                                              SDL_WINDOWPOS_UNDEFINED,
                                              SCREEN_WIDTH, SCREEN_HEIGHT,
                                              SDL_WINDOW_SHOWN);
        if(!window)
        {
            printf("Window could not be created!\n"
                   "SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // Create renderer
            SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(!ren)
            {
                printf("Renderer could not be created!\n"
                       "SDL_Error: %s\n", SDL_GetError());
            }
            else
            {


                    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // White color

    // Clear the window
    SDL_RenderClear(ren);

    // Set the draw color to red and draw a line
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255); // Red color
    SDL_RenderDrawLine(ren, 100, 100, 200, 200);

    // Set the draw color to green and draw a rectangle outline
    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255); // Green color
    SDL_Rect rectOutline = { 300, 200, 200, 150 };
    SDL_RenderDrawRect(ren, &rectOutline);

    // Set the draw color to blue and draw a filled rectangle
    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255); // Blue color
    SDL_Rect rectFilled = { 550, 100, 100, 100 };
    SDL_RenderFillRect(ren, &rectFilled);

    // Present the renderer
    SDL_RenderPresent(ren);


                // Event loop exit flag
                bool quit = false;

                // Event loop
                while(!quit)
                {
                    SDL_Event e;

                    // Wait indefinitely for the next available event
                    SDL_WaitEvent(&e);

                    // User requests quit
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }

  
                }

                // Destroy renderer
                SDL_DestroyRenderer(ren);
            }

            // Destroy window
            SDL_DestroyWindow(window);
        }

        // Quit SDL
        SDL_Quit();

        return 0;
}