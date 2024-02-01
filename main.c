/* A simple program that uses SDL2 and C to fill the background with a gradient animation */

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <stdio.h>
#include <math.h>

/* The screen width and height */
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

/* The color range for the gradient */
#define MIN_COLOR 0
#define MAX_COLOR 255

/* The speed of the animation */
#define SPEED 0.00025

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Create a window */
    SDL_Window *window = SDL_CreateWindow(
            "Gradient Animation",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Create a renderer */
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /* Create a rectangle that covers the whole screen */
    SDL_Rect rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    /* The main loop */
    int quit = 0;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        /* Get the current time in milliseconds */
        Uint32 time = SDL_GetTicks();

        /* Calculate the color values based on the time and the speed */
        Uint8 r = (Uint8) ((MAX_COLOR - MIN_COLOR) * (0.5 + (0.5 * sin(SPEED * time))) + MIN_COLOR);
        Uint8 g = (Uint8) ((MAX_COLOR - MIN_COLOR) * (0.5 + (0.5 * sin(SPEED * time + 2 * M_PI / 3))) + MIN_COLOR);
        Uint8 b = (Uint8) ((MAX_COLOR - MIN_COLOR) * (0.5 + (0.5 * sin(SPEED * time + 4 * M_PI / 3))) + MIN_COLOR);

        /* Set the render draw color to the calculated color and draw it to the screen */
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);

        /* Delay the execution to control the frame rate of the animation */
        SDL_Delay(16);
    }

    /* Destroy the renderer and the window */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    /* Quit SDL */
    SDL_Quit();

    return EXIT_SUCCESS;
}
