#pragma once

#ifdef _WIN32
    #include <windows.h>
#endif
#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <debugbreak/debugbreak.h>
#include "core/constants.hpp"

namespace imac {
SDL_Window* init() {
    /* Init logger */
    //spdlog::set_pattern("[%l] %^ %v %$");
    
    /* Init SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        printf("[SDL2] Unable to initialize SDL: ");
        debug_break();
        return nullptr;
    }

    /* Init OpenGL */
    SDL_GL_LoadLibrary(NULL); // Use 4.4 to get debug infos
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_GL_SetSwapInterval(1);

    /* Create Window */
    SDL_Window* window = SDL_CreateWindow(
        "Garden watchers",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        printf("[SDL2] Window is null: ");
        debug_break();
        return nullptr;
    }

    /* Create OpenGl context */
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        printf("[SDL2] OpenGL context is null");
        debug_break();
        return nullptr;
    }

    /* Init Glad once the OpenGL context is valid */
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        printf("[Glad] Glad not init");
        debug_break();
        return nullptr;
    }

    /* Enable OpenGL debugging 
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(gllog::messageCallback, 0);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
    */

    return window;
}
}
