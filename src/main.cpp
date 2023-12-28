#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "../modules/Core/include/GameBaseEntity.h"
#include "events/CloseEvent.h"
#include <EventManager.h>
#include <ResourcesManager.h>

int main() {

    Mix_Music* music = NULL;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture1 = NULL;
    SDL_Texture *texture2 = NULL;
    auto* entity1 = new GameBaseEntity();
    auto* closeEvent = new CloseEvent();
    auto* eventManager = new EventManager();
    auto* diskManager = new ResourcesManager();

    SDL_AudioSpec spec;
    spec.freq = MIX_DEFAULT_FREQUENCY;
    spec.format = MIX_DEFAULT_FORMAT;
    spec.channels = MIX_DEFAULT_CHANNELS;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Couldn't initialize SDL: %s\n",SDL_GetError());
        return(255);
    }

    diskManager->load3DModels();

    eventManager->init();

    eventManager->addQuitEventListener(closeEvent);
    //eventManager->addMouseEventListener(closeEvent);

    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL Image could not be initialized! Error: %s", SDL_GetError());
    }

    SDL_Surface* surface1 = IMG_Load("assets/image2.jpg");
    SDL_Surface* surface2 = IMG_Load("assets/image1.png");

    SDL_Log("%s loaded image 1 x: %d y: %d", "Everything worked!", surface1->w, surface1->h);
    SDL_Log("%s loaded image 2 x: %d y: %d", "Everything worked!", surface2->w, surface2->h);

    if (Mix_OpenAudio(0, &spec) < 0) {
        SDL_Log("Couldn't open audio: %s\n", SDL_GetError());
        return(2);
    } else {
        Mix_QuerySpec(&spec.freq, &spec.format, &spec.channels);
        SDL_Log("Opened audio at %d Hz %d bit%s %s audio buffer\n", spec.freq,
                (spec.format&0xFF),
                (SDL_AUDIO_ISFLOAT(spec.format) ? " (float)" : ""),
                (spec.channels > 2) ? "surround" : (spec.channels > 1) ? "stereo" : "mono");
    }

    window = SDL_CreateWindow("Otro titulo", 1024, 720, 0);
    renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);

    music = Mix_LoadMUS("assets/bata.ogg");
    if(music != NULL) {
        Mix_FadeInMusic(music, 5, 2000);
    } else {
        SDL_Log("Couldn't open audio: %s\n", SDL_GetError());
    }

    texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
    texture2 = SDL_CreateTextureFromSurface(renderer, surface2);

    SDL_DestroySurface(surface1);
    SDL_DestroySurface(surface2);

    SDL_FRect *rect1 = new SDL_FRect();
    rect1->w = 300;
    rect1->h = 300;

    SDL_FRect *rect2 = new SDL_FRect();
    rect2->w = 450;
    rect2->h = 250;
    rect2->x = 500;
    rect2->y = 100;

    while (!closeEvent->getExitLoop()) {
        eventManager->checkEventQueue();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderTexture(renderer, texture1, NULL, rect1);
        SDL_RenderTexture(renderer, texture2, NULL, rect2);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
