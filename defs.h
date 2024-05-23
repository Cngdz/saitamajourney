#ifndef _DEFS__H
#define _DEFS__H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const char* WINDOW_TITLE = "Adventure Time!";
#define BACKGROUND_IMG "image\\bground.png"
const SDL_Rect PLAY_BUTTON = { 195, 166, 400, 60 };
const SDL_Rect HELP_BUTTON = { 195, 260, 400, 60 };
const SDL_Rect QUIT_BUTTON = { 195, 344, 400, 60 };
const SDL_Rect X_BUTTON = { 360, 0, 55, 50};
    SDL_Rect playerRect = { 150, 395, 30, 55 };
    SDL_Color color= {255,222,89};
    SDL_Color minicolor= {255, 255, 255};

    bool quit = false;
    bool isJumping = false;
    int jumpHeight = 0; // Chiều cao nhảy
    const int maxJumpHeight = 100; // Chiều cao tối đa nhảy
    const int jumpSpeed = 15; // Tốc độ nhảy
    bool isCrouching = false; // Biến để kiểm tra xem nhân vật có đang cúi xuống không
    int crouchDuration = 0;
    const int crouchDurationMax = 200; // Độ dài tối đa thời gian cúi xuống
     int dietime = 200;
     int gktime = 1000;
     bool gameover=0;
    bool isdie=0;
    bool het=0;
    bool isplaying = 0;
    int score=0;
    static int highest_score=0;
    int last =0;
    bool help=0;
    int a=1;
    int diem=0;
    bool bienhinh=0;
    bool ssbh=false;
    bool offvl=0;
    bool newss=0, hlps=0, qitts=0;
const char*  SAITAMA_SPRITE_FILE = "image\\shaolin_running_strip.png";
const char*  JUMP_SPRITE_FILE = "image\\shaolin_jump_strip.png";
const char*  CROUCH_SPRITE_FILE = "image\\shaolin_slide_strip.png";
const char*  SLIME_SPRITE_FILE = "image\\slime-Sheet.png";
const char*  STONE_SPRITE_FILE = "image\\stone.png";
const char*  BUU_SPRITE_FILE = "image\\buuu.png";
const char*  DIE_SPRITE_FILE = "image\\dies.png";
const char*  BACKGROUND2 = "image\\bground2.png";
const char*  GOKU_SPRITE_FILE = "image\\goku.png";

const int run_CLIPS[][4] = {
    {0, 0, 45, 61},
    {45, 0, 45, 61},
    {90, 0, 45, 61},
    {135, 0, 45, 61},
    {180, 0, 45, 61},
};
const int JUMP_CLIPS[][4] = {
    {0, 0, 36, 59},
    {36, 0, 36, 59},
    {72, 0, 36, 59},

};
const int CROUCH_CLIPS[][4] = {
    {0, 0, 51, 59},
    {51, 0, 51, 59},
    {102, 0, 51, 59},
    {153, 0, 51, 59},
};
const int SLIME_CLIPS[][4] = {
    {0, 0, 32, 25},
    {32, 0, 32, 25},
    {64, 0, 32, 25},
    {96, 0, 32, 25},
    {128, 0, 32, 25},
};
const int STONE_CLIPS[][4] = {
    {0, 0, 58, 70},
};
const int BUU_CLIPS[][4] = {
    {0, 0, 90, 93},
    {90, 0, 90, 93},
    {180, 0, 90, 93},
    {270, 0, 90, 93},
    {360, 0, 90, 93},
    {450, 0, 90, 93}
};
const int DIE_CLIPS[][4] = {
    {0, 0, 70, 74},
    {70, 0, 70, 74},
    {140, 0, 70, 74},
    {210, 0, 70, 74},
};
const int GOKU_CLIPS[][4] = {
    {0, 0, 74, 77},
    {75, 0, 74, 77},
    {166, 0, 74, 77},
    {228, 0, 74, 77},
    {309, 0, 74, 77},
    {393, 0, 74, 77}
};

const int saitama_FRAMES = sizeof(run_CLIPS)/sizeof(int)/4;
const int JUMP_FRAMES = sizeof(JUMP_CLIPS)/sizeof(int)/4;
const int CROUCH_FRAMES = sizeof(CROUCH_CLIPS)/sizeof(int)/4;
const int SLIME_FRAMES = sizeof(SLIME_CLIPS)/sizeof(int)/4;
const int STONE_FRAMES = sizeof(STONE_CLIPS)/sizeof(int)/4;
const int BUU_FRAMES = sizeof(BUU_CLIPS)/sizeof(int)/4;
const int DIE_FRAMES = sizeof(DIE_CLIPS)/sizeof(int)/4;
const int GOKU_FRAMES = sizeof(GOKU_CLIPS)/sizeof(int)/4;

#endif
