
#include "graphics.h"
#include "defs.h"
#include "characters.h"
#include "func.cpp"
using namespace std;

    void update(vector<vector<int>>& positions,int time,int x,int y,int move,int &last) {
    int now = SDL_GetTicks();

    x = rand() % x + x ;

    if (now - last >= time) {
        last = now;
        positions.push_back({x, y}); // Thêm một con enemy mới tại vị trí (x, y)
    }

    for (auto& position : positions) {
        position[0] -= move; // Di chuyển con enemy sang trái
    }

    positions.erase(remove_if(positions.begin(), positions.end(), [](const vector<int>& position) {
        return position[0] < -32; // Loại bỏ con enemy nếu đã đi qua khỏi màn hình
    }), positions.end());
}

    void ve(Graphics& graphic , Threats& threat , vector<vector<int>>& positions) {
        for (const auto& position : positions) {
            graphic.render3(position[0], position[1], threat); // Vẽ con slime lên màn hình
        }
    }
    // Hàm kiểm tra va chạm giữa hai hình chữ nhật
   bool checkCollision(const SDL_Rect& rectA, const SDL_Rect& rectB) {
        bool collisionX = (rectA.x + rectA.w >= rectB.x) && (rectB.x + rectB.w >= rectA.x);
        bool collisionY = (rectA.y + rectA.h >= rectB.y) && (rectB.y + rectB.h >= rectA.y);
        return collisionX && collisionY;
}
//     Hàm xử lí va chạm giữa nhân vật và con slime
void handleCollision(const vector<vector<int>>& pos, Sprite& die, Graphics& graphic, int threatWidth, int threatHeight, SDL_Rect playerRect) {
    for (const auto& position : pos) {
        SDL_Rect threatRect = { position[0], position[1], threatWidth, threatHeight };

        if (checkCollision(playerRect, threatRect)) {
            isdie = true;
            isCrouching= false;
            isJumping = false;
            break;
        }
    }
}
bool isMouseOverButton(const SDL_Rect& button, int mouseX, int mouseY) {
    return (mouseX >= button.x && mouseX <= button.x + button.w &&
            mouseY >= button.y && mouseY <= button.y + button.h);
}


int main(int argc, char *argv[]) {

    Graphics graphics;
    graphics.init();

    ScrollingBackground background;
    ScrollingBackground background2;
    background.setTexture(graphics.loadTexture(BACKGROUND_IMG));
    background2.setTexture(graphics.loadTexture(BACKGROUND2));

    SDL_Texture* menuTexture = graphics.loadTexture("image\\menu.png");
    SDL_Texture* gameoverTexture = graphics.loadTexture("image\\gameover.png");
    SDL_Texture* helpTexture = graphics.loadTexture ("image\\help.png");
    SDL_Texture* news = graphics.loadTexture ("image\\new.png");
    SDL_Texture* hlp = graphics.loadTexture ("image\\hlp.png");
    SDL_Texture* qitt = graphics.loadTexture ("image\\quitt.png");
    SDL_Texture* bienh = graphics.loadTexture ("image\\bh.png");
    SDL_Texture* bh2 = graphics.loadTexture ("image\\bh2.png");

    Sprite saitama;
    SDL_Texture* saitamaTexture = graphics.loadTexture(SAITAMA_SPRITE_FILE);
    saitama.init(saitamaTexture, saitama_FRAMES, run_CLIPS);

    Sprite jump;
    SDL_Texture* jumpTexture = graphics.loadTexture(JUMP_SPRITE_FILE);
    jump.init(jumpTexture, JUMP_FRAMES, JUMP_CLIPS);

    Sprite crouch;
    SDL_Texture* crouchTexture = graphics.loadTexture(CROUCH_SPRITE_FILE);
    crouch.init(crouchTexture, CROUCH_FRAMES, CROUCH_CLIPS);

    Sprite die;
    SDL_Texture* dieTexture = graphics.loadTexture(DIE_SPRITE_FILE);
    die.init(dieTexture, DIE_FRAMES, DIE_CLIPS);

    Sprite goku;
    SDL_Texture* gokuTexture = graphics.loadTexture(GOKU_SPRITE_FILE);
    goku.init(gokuTexture, GOKU_FRAMES, GOKU_CLIPS);

    Threats stone;
    SDL_Texture* stoneTexture = graphics.loadTexture(STONE_SPRITE_FILE);
    stone.init(stoneTexture, STONE_FRAMES, STONE_CLIPS);

    Threats slime;
    SDL_Texture* slimeTexture = graphics.loadTexture(SLIME_SPRITE_FILE);
    slime.init(slimeTexture, SLIME_FRAMES, SLIME_CLIPS);

    Threats buu;
    SDL_Texture* buuTexture = graphics.loadTexture(BUU_SPRITE_FILE);
    buu.init(buuTexture, BUU_FRAMES, BUU_CLIPS);

    TTF_Font* font= graphics.loadFont("assets\\Bungee-Regular.ttf",110);
    TTF_Font* minifont= graphics.loadFont ("assets\\Sansita-Regular.ttf",30);
    Mix_Music* soundtrack= graphics.loadMusic ("assets\\soundtrack.mp3");
    Mix_Chunk* click=graphics.loadSound ("assets\\Click.wav");
    Mix_Chunk* jucr= graphics.loadSound ("assets\\Jump.wav");
    Mix_Chunk* bonk= graphics.loadSound ("assets\\sfx_bonk.wav");
    graphics.play(soundtrack);
    vector<vector<int>> po1; // Lưu trữ vị trí của các con slime
    vector<vector<int>> po2;
    vector<vector<int>> po3;

    int lastSlime = SDL_GetTicks(); // Khởi tạo biến last cho con slime
    int lastStone = SDL_GetTicks();
    int lastBuu = SDL_GetTicks();

    srand(time(0));

    while (!quit) {

        int bh=score-diem;
        if(bh>=200){
            ssbh=true;
            diem=score;
        }
        SDL_Event event;
        if (!gameover) {
            graphics.renderTexture(menuTexture, 0, 0); }
            else {
                graphics.renderTexture (gameoverTexture,0,0);
                string x=to_string(score);
                graphics.renderTexture(gameoverTexture,0,0);
                SDL_Texture* scoretext = graphics.renderText(x,font,color);
                graphics.renderTexture(scoretext,470,10);

            }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_UP && !isJumping) {
                    graphics.play(jucr);
                    if (!isCrouching && !isdie) {isJumping = true;}
                    jumpHeight = 0; // Đặt lại chiều cao nhảy
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_DOWN && !isCrouching) {
                    graphics.play(jucr);
                    if(!isJumping && !isdie) {isCrouching = true;}
                    crouchDuration = crouchDurationMax; // Đặt thời gian cúi xuống về giá trị tối đa
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                    graphics.play(jucr);
                    if(ssbh) {
                        bienhinh = true;
                        gktime=1000;
                    }
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_X) {
                    if (offvl) {
                        Mix_VolumeMusic(MIX_MAX_VOLUME); // Bật lại âm thanh với âm lượng ban đầu
                        offvl = false; // Đặt offvl thành false
                    } else {
                        Mix_VolumeMusic(0); // Tắt âm thanh
                        offvl = true; // Đặt offvl thành true
                    }
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                      graphics.play(jucr);
                    if(bienhinh) {
                        bienhinh = false;
                        ssbh=false;
                    }
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN ){
                    graphics.play(click);
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                        // Kiểm tra xem chuột có nằm trong vị trí của các nút không
                        if (isMouseOverButton(PLAY_BUTTON, mouseX, mouseY) && !isplaying && !help) {
                            // Người dùng nhấn vào nút "Play Game"
                            gameover = false;
                            isplaying = true;
                            // Reset tất cả các biến và trạng thái của trò chơi về giá trị ban đầu

                                    lastSlime = SDL_GetTicks();
                                    lastStone = SDL_GetTicks();
                                    lastBuu = SDL_GetTicks();
                                    isJumping = false;
                                    isCrouching = false;
                                    jumpHeight = 0;
                                    crouchDuration = crouchDurationMax;
                                    score=0;
                                    dietime=200;
                                    diem=0;
                                    bienhinh=0;
                                    ssbh=true;
                                    // Xóa các vị trí của nhân vật và các mục tiêu khác
                                    po1.clear();
                                    po2.clear();
                                    po3.clear();

                        } else if (isMouseOverButton(HELP_BUTTON, mouseX, mouseY) && !isplaying  ) {
                            // Người dùng nhấn vào nút "Help"
                            help=1;
                        } else if (isMouseOverButton(QUIT_BUTTON, mouseX, mouseY) && !isplaying && !help) {
                            // Người dùng nhấn vào nút "Quit"
                            quit=1;
                        } else if (isMouseOverButton (X_BUTTON,mouseX,mouseY)) {
                            help=0;
                        }

                }
            else if (event.type == SDL_MOUSEMOTION) {
                int X, Y;
                SDL_GetMouseState(&X, &Y);

                        // Kiểm tra xem chuột có nằm trong vị trí của các nút không
                        if (isMouseOverButton(PLAY_BUTTON, X, Y)&& !isplaying && !help) {
                                newss=1;
                                hlps=0;qitts=0;
                        } else if (isMouseOverButton(HELP_BUTTON, X, Y) && !isplaying  ) {
                                hlps=1;
                                newss=0;qitts=0;
                        } else if (isMouseOverButton(QUIT_BUTTON, X, Y) && !isplaying && !help) {
                                qitts=1;
                                newss=0;hlps=0;
                        } else {
                            newss=0;
                            hlps =0;
                            qitts=0;
                        }
            }
        }
    if (newss) graphics.renderTexture(news,0,0);
    if (hlps) graphics.renderTexture (hlp,0,0);
    if (qitts) graphics.renderTexture (qitt,0,0);
    if(help) {
        graphics.renderTexture(helpTexture,0,0);
    }
    if(isplaying) {
             a=score/100+ 1;
            update(po1,8000,801,328,8+a,lastSlime);
            update(po2,2500,801,343,8+a,lastStone);
            update(po3,20000,801,330,15+a,lastBuu);
        if (isCrouching && !bienhinh) {
            // Xử lý khi nhân vật đang cúi xuống
            crouch.tick(); // Cập nhật frame nhân vật
            background2.scroll(8+a);
            graphics.prepareScene();
            graphics.render(background);
            graphics.render(background2);
            SDL_Rect playerRect = { 150,398, 40, 2 };

            if (crouchDuration>=190)   graphics.render2(150, 335, crouch, 0); // Sử dụng frame của nhân vật khi cúi
            else if (crouchDuration>=180) graphics.render2(150, 335, crouch, 1);
            else if (crouchDuration>=160) graphics.render2(150, 335, crouch, 2);
            else if (crouchDuration>=0) graphics.render2(150, 335, crouch, 3);

            // Giảm thời gian cúi xuống
            crouchDuration-=10;

            // Khi thời gian cúi xuống kết thúc, đặt lại trạng thái của biến isCrouching
            if (crouchDuration <= 0) {
                isCrouching = false;
            }
            handleCollision(po1,die,graphics,25,30,playerRect);
            handleCollision(po2,die,graphics,45,60,playerRect);
            handleCollision(po3,die,graphics,90,93,playerRect);

        }
        // Xử lý khi nhân vật đang ở trạng thái nhảy
        else if (isJumping && !bienhinh ) {
            // Xử lý khi nhân vật đang nhảy lên
            jumpHeight += jumpSpeed;
            jump.tick(); // Cập nhật frame nhân vật
            background2.scroll(8+a);
            graphics.prepareScene();
            graphics.render(background);
            graphics.render(background2);

//            playerRect.y = 395 - jumpHeight;
            SDL_Rect playerRect = { 150, 343-jumpHeight, 30, 30 };
            // Vẽ nhân vật ở vị trí hiện tại và nhảy lên từ từ
            if (jumpHeight < maxJumpHeight) {
                // Sử dụng frame đầu tiên của sprite nhảy
                graphics.render2(150, 343 - jumpHeight, jump, 0);
            } else if (jumpHeight <= 2 * maxJumpHeight) {
                // Sử dụng frame thứ hai của sprite nhảy
                graphics.render2(150, 343 - maxJumpHeight, jump, 1);
            } else {
                // Sử dụng frame thứ ba của sprite nhảy
                graphics.render2(150, 343 - (3 * maxJumpHeight - jumpHeight), jump, 2);
            }

            // Khi nhảy đạt đến độ cao tối đa, bắt đầu giảm chiều cao nhảy
            if (jumpHeight >= 3 * maxJumpHeight) {
                jumpHeight = 0;
                isJumping = false;
            }
            handleCollision(po1,die,graphics,25,30,playerRect);
            handleCollision(po2,die,graphics,45,60,playerRect);
            handleCollision(po3,die,graphics,90,93,playerRect);
        }
        else if (bienhinh && !isdie){
            goku.tick();
            background2.scroll(8+a);
            graphics.prepareScene();
            graphics.render(background);
            graphics.render(background2);
            if (gktime >= 950) graphics.render2(150, 320, goku, 0);
            else if (gktime >= 900) graphics.render2(150, 320, goku, 1);
            else if (gktime >= 850) graphics.render2(150, 320, goku, 2);
            else if (gktime >= 800) graphics.render2(150, 320, goku, 3);
            else graphics.render2(150, 320, goku, 4);

            gktime -= 5;

            if (gktime <= 0) {
                bienhinh = false;
                ssbh=false;
                gktime=1000;
            }
        }
        else if (isdie ) {
            if (dietime>185) graphics.play(bonk);
            die.tick();
//            background.scroll(5);
            graphics.prepareScene();
            graphics.render(background);
            graphics.render(background2);
            if (dietime >= 180) graphics.render2(140, 308, die, 0); // Vẽ các frame chết liên tục
            else if (dietime >= 160) graphics.render2(100, 328, die, 1);
            else if (dietime >= 140) graphics.render2(70, 338, die, 2);
            else graphics.render2(70, 338, die, 3);

            dietime -= 5;

            if (dietime <= 0) {
                isdie = false;
                isplaying=0;
                gameover=1;

            }
    }

        else {
            // Xử lý khi nhân vật đang ở trạng thái bình thường

            saitama.tick(); // Cập nhật frame nhân vật
            background2.scroll(8+a);
            graphics.prepareScene();
            graphics.render(background);
            graphics.render(background2);
            graphics.render2(150, 343, saitama); // Vẽ nhân vật ở vị trí bình thường
            SDL_Rect playerRect = { 150, 343, 30, 55 };
            handleCollision(po1,die,graphics,25,30,playerRect);
            handleCollision(po2,die,graphics,45,60,playerRect);
            handleCollision(po3,die,graphics,90,93,playerRect);
        }

//         Cập nhật frame của con slime
       if(isplaying){
        graphics.renderTexture(bh2,20,18);
        if(ssbh) {graphics.renderTexture(bienh,20,18);}


        slime.tick();
        stone.tick();
        buu.tick();

        ve(graphics,stone,po2);
        ve(graphics,slime,po1);
        ve(graphics,buu,po3);

        SDL_Texture* sc = graphics.renderText("Score: ",minifont,minicolor);
        SDL_Texture* hsc = graphics.renderText("Highest Score: ",minifont,minicolor);
        graphics.renderTexture(sc,600,30);
        graphics.renderTexture(hsc,500,70);
        int now= SDL_GetTicks();
        string m=to_string(score);
        string h=to_string(highest_score);
        SDL_Texture* minscotext = graphics.renderText(m,minifont,minicolor);
        SDL_Texture* hightext = graphics.renderText(h,minifont,minicolor);
        if (now-last>=150){
            score+=1;
            last=now;
        }

        ifstream infile("max_score.txt");
            if (infile) {
                infile >> highest_score;
                infile.close();
            }
        if (score>=highest_score) {
                highest_score=score;
                ofstream outfile("max_score.txt");
                if (outfile) {
                    outfile << score;
                    outfile.close();
                }
        }
            graphics.renderTexture(minscotext,700,30);
            graphics.renderTexture(hightext,700,70);
            SDL_DestroyTexture(minscotext);
            SDL_DestroyTexture (hightext);
       }
    }
        graphics.presentScene();
        SDL_Delay(30);
    }

    // Giải phóng bộ nhớ và thoát
    SDL_DestroyTexture(jumpTexture);
    SDL_DestroyTexture(crouchTexture);
    SDL_DestroyTexture(slimeTexture);
    SDL_DestroyTexture(saitamaTexture);
    SDL_DestroyTexture(stoneTexture);
    SDL_DestroyTexture (buuTexture);
    SDL_DestroyTexture (dieTexture);
    SDL_DestroyTexture (gokuTexture);
    SDL_DestroyTexture (bh2);
    SDL_DestroyTexture (bienh);
    SDL_DestroyTexture(background.texture);
    SDL_DestroyTexture (gameoverTexture);
    SDL_DestroyTexture (helpTexture);
    SDL_DestroyTexture (news);
    SDL_DestroyTexture (hlp);
    SDL_DestroyTexture (qitt);
    TTF_CloseFont(font);
    Mix_FreeMusic(soundtrack);
    Mix_FreeChunk(jucr);
    Mix_FreeChunk(click);
    graphics.quit();

    return 0;
}
