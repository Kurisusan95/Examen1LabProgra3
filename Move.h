#ifndef MOVE_H
#define MOVE_H

#include<SDL.h>
#include<SDL_image.h>

#include <iostream>
#include <vector>
#include "Sprite.h"
using namespace std;

class Move
{
    public:
        vector<Sprite*> sprites;
        SDL_Renderer* renderer;
        int frame;
        int current_sprite_frame;

        string input;
        vector<string>cancels;

        Move(SDL_Renderer* renderer,vector<Sprite*>sprites,vector<string>cancels);
        virtual ~Move();
        void draw(int current_sprite,int character_x, int character_y);
        bool canCancel(string move_name);
    protected:
    private:
};

#endif // MOVE_H
