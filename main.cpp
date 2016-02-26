#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include "Character.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*gameover,*title,*title2,*cloud,*cloud2;
SDL_Rect rect_background,rect_game_over,rect_cloud,rect_cloud2,rect_character,rect_title,rect_title2;
bool pausa=false;
int vida=1;
int poder=1;
void loopJuego()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = 1200;
    rect_background.h = 600;

    cloud = IMG_LoadTexture(renderer, "cloud.png");
    SDL_QueryTexture(cloud, NULL, NULL, &w, &h);
    rect_cloud.x = -100; rect_cloud.y = 150; rect_cloud.w = 146; rect_cloud.h = 72;

    cloud2 = IMG_LoadTexture(renderer, "cloud.png");
    SDL_QueryTexture(cloud2, NULL, NULL, &w, &h);
    rect_cloud2.x = -100; rect_cloud2.y = 30; rect_cloud2.w = 146; rect_cloud2.h = 72;

    title = IMG_LoadTexture(renderer, "Shanghai_University_title.png");
    SDL_QueryTexture(title, NULL, NULL, &w, &h);
    rect_title.x = 30; rect_title.y = 30; rect_title.w = 475; rect_title.h = 110;

    title2 = IMG_LoadTexture(renderer, "Mario_Title.png");
    SDL_QueryTexture(title2, NULL, NULL, &w, &h);
    rect_title2.x = 650; rect_title2.y = 30; rect_title2.w = 504; rect_title2.h = 188;

    vida = 1;
    SDL_Texture *barra_vida[6];
    SDL_Texture *barra_poder[4];
    barra_vida[0] = IMG_LoadTexture(renderer,"ProgressBar1.png");
    barra_vida[1] = IMG_LoadTexture(renderer,"ProgressBar2.png");
    barra_vida[2] = IMG_LoadTexture(renderer,"ProgressBar3.png");
    barra_vida[3] = IMG_LoadTexture(renderer,"ProgressBar4.png");
    barra_vida[4] = IMG_LoadTexture(renderer,"ProgressBar5.png");
    barra_vida[5] = IMG_LoadTexture(renderer,"ProgressBar6.png");
    SDL_Rect vida_rect;
    SDL_QueryTexture(barra_vida[0], NULL, NULL, &vida_rect.w, &vida_rect.h);
    vida_rect.x = 30;
    vida_rect.y = 30;
    vida_rect.w = 250;
    vida_rect.h = 47;

    poder=1;
    barra_poder[0] = IMG_LoadTexture(renderer,"PowerBar1.png");
    barra_poder[1] = IMG_LoadTexture(renderer,"PowerBar2.png");
    barra_poder[2] = IMG_LoadTexture(renderer,"PowerBar3.png");
    barra_poder[3] = IMG_LoadTexture(renderer,"PowerBar4.png");
    SDL_Rect power_rect;
    SDL_QueryTexture(barra_poder[0], NULL, NULL, &power_rect.w, &power_rect.h);
    power_rect.x = 300;
    power_rect.y = 30;
    power_rect.w = 250;
    power_rect.h = 47;

    Character* character = new Character(renderer,200,210,false,1);

    //Main Loop
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return;
                }
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_SPACE)
                {
                    if(poder<5){
                        if(poder<4){
                            poder++;
                        }
                        SDL_RenderCopy(renderer,barra_poder[poder-1],NULL,&power_rect);
                    }
                }
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_s)
                {
                    vida++;
                    if(vida<6)
                        SDL_RenderCopy(renderer,barra_vida[vida-1],NULL,&vida_rect);
                    else
                        return;


                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderCopy(renderer, cloud, NULL, &rect_cloud);
        SDL_RenderCopy(renderer, cloud2, NULL, &rect_cloud2);
        SDL_RenderCopy(renderer, title, NULL, &rect_title);
        SDL_RenderCopy(renderer, title2, NULL, &rect_title2);
        SDL_RenderCopy(renderer,barra_vida[vida-1],NULL,&vida_rect);
        SDL_RenderCopy(renderer,barra_poder[poder-1],NULL,&power_rect);


        if( currentKeyStates[ SDL_SCANCODE_P ] )
        {
                pausa = true;
                cout<<"En pausa"<<endl;
        }
        if( currentKeyStates[ SDL_SCANCODE_KP_ENTER ] )
        {
                pausa = false;
                cout<<"Reanudado"<<endl;
        }

        if(rect_cloud.x<1500 && !pausa)
            rect_cloud.x = rect_cloud.x+1;
        if(rect_cloud.x>1320)
            rect_cloud.x = -125;


        if(rect_cloud2.x<1500 && !pausa){
            if(rect_cloud.x%2==0){
                rect_cloud2.x = rect_cloud2.x+1;
            }
        }
        if(rect_cloud2.x>1320)
            rect_cloud2.x = -125;

        character->logic();
        character->draw();

        SDL_RenderPresent(renderer);

    }

	return;
}
void mainMenu()
{
    int opcion = 1;
    SDL_Texture *menu_fondo[3];
    menu_fondo[0] = IMG_LoadTexture(renderer,"strootFighter_fondo1.png");
    menu_fondo[1] = IMG_LoadTexture(renderer,"strootFighter_fondo2.png");
    menu_fondo[2] = IMG_LoadTexture(renderer,"strootFighter_fondo3.png");
    SDL_Rect menu_rect;
    SDL_QueryTexture(menu_fondo[0], NULL, NULL, &menu_rect.w, &menu_rect.h);
    menu_rect.x = 0;
    menu_rect.y = 0;

    gameover = IMG_LoadTexture(renderer,"game_Over.png");
    rect_game_over.x = 0;
    rect_game_over.y = 0;
    rect_game_over.w = 1200;
    rect_game_over.h = 600;

    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_2)
                {
                    return;
                }
                if(Event.key.keysym.sym == SDLK_1)
                {
                    loopJuego();
                }
                if(Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return;
                }
                if(Event.key.keysym.sym == SDLK_DOWN)
                {
                    opcion++;
                    if(opcion > 3)
                        opcion = 3;
                }
                if(Event.key.keysym.sym == SDLK_UP)
                {
                    opcion--;
                    if(opcion < 1)
                        opcion = 1;
                }
                if(Event.key.keysym.sym == SDLK_RETURN)
                {
                    switch(opcion)
                    {
                        case 1:
                            if(vida<6)
                                loopJuego();
                        break;
                        case 2:

                        break;
                        case 3:
                            return;
                        break;
                    }
                }
            }
        }

        SDL_RenderCopy(renderer,menu_fondo[opcion-1],NULL,&menu_rect);
        if(vida==6)
            SDL_RenderCopy(renderer, gameover, NULL, &rect_game_over);

        SDL_RenderPresent(renderer);

    }
}

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1200/*WIDTH*/, 600/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    mainMenu();

	return 0;
}
