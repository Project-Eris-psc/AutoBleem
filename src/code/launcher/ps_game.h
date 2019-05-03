//
// Created by screemer on 2/12/19.
//

#ifndef AUTOBLEEM_GUI_PS_GAME_H
#define AUTOBLEEM_GUI_PS_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "ps_carousel.h"
#include <string>
#include <memory>

using namespace std;

class PsGame {
public:
    int gameId = 0;
    string title = "";
    string publisher = "";
    int year = 0;
    int players = 0;


    string memcard = "";
    string folder = "";
    string ssFolder = "";

    string base = "";
    SDL_Texture *coverPng = nullptr;

    bool internal = false;
    bool hd = false;
    bool locked = false;
    int cds = 1;
    bool favorite = false;

    void loadTex(SDL_Renderer *renderer);
    void freeTex();

    std::shared_ptr<PsGame> clone();

    void setMemCard(string name);
    string findResumePicture();
    bool isResumeSlotActive(int slot);
    string findResumePicture(int slot);
    void storeResumePicture(int slot);
    bool isCleanExit();
    void removeResumePoint(int slot);


    PsScreenpoint current;
    PsScreenpoint destination;
    PsScreenpoint actual;
    int screenPointIndex = -1;
    int nextPointIndex = -1;
    long animationStart = 0;
    long animationDuration = 0;
    bool visible = false;

};


#endif //AUTOBLEEM_GUI_PS_GAME_H
