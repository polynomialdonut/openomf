#include "video/video.h"
#include "utils/log.h"
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#include <SDL2/SDL.h>

SDL_Window *window;
SDL_GLContext glctx;

int video_init(int window_w, int window_h, int fullscreen, int vsync) {
    // Settings
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,     8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,   24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);                                               
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);   

    // Open window
    window = SDL_CreateWindow(
        "OpenOMF",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_w,
        window_h,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );
    if(!window) {
        PERROR("Could not create window: %s", SDL_GetError());
        return 1;
    }
    
    // Set fullscreen if needed
    if(fullscreen) {
        if(SDL_SetWindowFullscreen(window, 1) != 0) {
            PERROR("Could not set fullscreen mode!");
        } else {
            DEBUG("Fullscreen enabled!");
        }
    }
    
    // Create context
    glctx = SDL_GL_CreateContext(window);
    if(!glctx) {
        PERROR("Could not create GL context: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        return 1;
    }
    
    // Set VSync
    if(vsync) {
        if(SDL_GL_SetSwapInterval(1) != 0) {
            PERROR("Could not enable VSync!");
        } else {
            DEBUG("VSync enabled!");
        }
    }
    
    // Show some info
    DEBUG("Video Init OK");
    DEBUG(" * SDL2 Driver: %s", SDL_GetCurrentVideoDriver());
    DEBUG(" * Vendor:      %s", glGetString(GL_VENDOR));
    DEBUG(" * Renderer:    %s", glGetString(GL_RENDERER));
    DEBUG(" * Version:     %s", glGetString(GL_VERSION));
    
    return 0;
}

void video_render() {
    SDL_GL_SwapWindow(window);
}

void video_close() {
    SDL_GL_DeleteContext(glctx);  
    SDL_DestroyWindow(window);
    DEBUG("Video deinit.");
}
