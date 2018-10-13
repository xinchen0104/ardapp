//
//  main.cpp
//  Ardapp
//
//  Created by xinchen on 2018/9/18.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <SDL.h>
#include "core/Color.hpp"
#include "renderer/Renderer.hpp"
#include "geometry/Transform.hpp"
#include "resource/Mesh.hpp"
#include "loader/ObjectLoader.hpp"

SDL_Renderer*       mainRenderer;
SDL_Texture*        defaultTexture;
SDL_Window*         mainWindow;
int32_t             mainWindowHeight;
int32_t             mainWindowWidth;
Scene*              s;
Camera*             camera;
ObjectLoader*       loader;
Mesh*               mesh;
Renderer*           renderer;
Renderer3D*         renderer3d;
Renderer2D*         renderer2d;




int GameInit();
int GameMain();
int GameShutdown();
int ResourceInit();
int ResourceDestroy();
void CalcuFPS();
void RenderMain();

int main(int argc, char** argv) {
    GameInit();
    bool quit = false;
    SDL_Event e;
    while(!quit){
        if(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_ESCAPE :
                        quit = true;
                        break;
                    case SDLK_UP:
                        camera->Translate(*(camera->N) * 0.1);
                        break;
                    case SDLK_DOWN:
                        camera->Translate(*(camera->N) * 0.1 * (-1));
                        break;
                    case SDLK_LEFT:
                        camera->RotateEuler(Vector4f(0.0, -3.1415/180, 0.0, 1.0));
                        break;
                    case SDLK_RIGHT:
                        camera->RotateEuler(Vector4f(0.0, 3.1415/180, 0.0, 1.0));
                        break;
                    default:
                        break;
                }
            }
        }
        GameMain();
    }
    GameShutdown();
    return 0;
}
int GameInit(){
    int flag = 0;
    //SDL INIT
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }
    
    //CREATE MAIN WINDOW
//    mainWindow = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mainWindowWidth, mainWindowHeight, SDL_WINDOW_SHOWN);
    mainWindow = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mainWindowWidth, mainWindowHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(mainWindow == NULL){
        SDL_Log("Unable to create the mainWindow: %s", SDL_GetError());
        flag = -1;
    }
    SDL_GetWindowSize(mainWindow, &mainWindowWidth, &mainWindowHeight);
    
    mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(mainRenderer == NULL){
        SDL_Log("Unable to Create the main renderer: %s", SDL_GetError());
        flag = -1;
    }
    
    defaultTexture = SDL_CreateTexture(mainRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, mainWindowWidth, mainWindowHeight);
    if(defaultTexture == NULL){
        SDL_Log("Unable to Create the default texture: %s", SDL_GetError());
        flag = -1;
    }
    if(flag == 0){
        flag = ResourceInit();
    }
    return flag;
}
int GameShutdown(){
    ResourceDestroy();
    return 0;
}
int GameMain(){
    CalcuFPS();
    RenderMain();
    return 0;
}
void CalcuFPS(){
    static uint32_t lastTime = 0, currentTime = 0;
    static uint32_t frames = 0;
    currentTime = SDL_GetTicks();
    frames ++;
    if(currentTime - lastTime > 1000){
        SDL_Log("%f frames", (float) frames / (currentTime - lastTime) * 1000);
        lastTime = currentTime;
        frames = 0;
    }
}

void RenderMain(){
    (*(s->object_list.begin()))->rotateEuler(Vector4f(0.0, 3.14/60, 0.0, 1.0));
    SDL_LockTexture(defaultTexture, NULL, (void**)&(renderer2d->buffer), &(renderer2d->lpitch_byte));    
    renderer->renderer3D->render(&(renderer->render_triangle_list));
    renderer->renderer2D->render(&(renderer->render_triangle_list));
    SDL_UnlockTexture(defaultTexture);
    SDL_RenderClear(mainRenderer);
    SDL_RenderCopy(mainRenderer, defaultTexture, NULL, NULL);
    SDL_RenderPresent(mainRenderer);
}

int ResourceInit(){
    s = new Scene();
    camera = new Camera();
    renderer = new Renderer();
    renderer3d = new Renderer3D();
    renderer2d = new Renderer2D(mainWindowWidth, mainWindowHeight);
    loader = new ObjectLoader();
    mesh = new Mesh();
    loader->load("T3DIICHAP07/tank1.plg", mesh, true);
    Object* obj[3];
    for(int i = 0; i < 1; i++){
        obj[i] = new Object(mesh, 0.02);
        obj[i]->setPosition(Vector4f(0.0, 0.0, 6.0, 1.0));
        s->object_list.push_back(obj[i]);
    }
    renderer3d->camera = camera;
    renderer3d->scene = s;
    renderer->renderer3D = renderer3d;
    renderer->renderer2D = renderer2d;
    return 0;
}
int ResourceDestroy(){
    delete loader;
    delete mesh;
    delete s;
    delete camera;
    delete renderer3d;
    delete renderer2d;
    delete renderer;
    return 0;
}


