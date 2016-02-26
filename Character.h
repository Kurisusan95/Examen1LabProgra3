#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <map>
#include <fstream>
#include "Move.h"
using namespace std;

class Character
{
    public:
        map<string,Move*>moves;
        string current_move;
        int current_sprite;
        int current_sprite_frame;
        int x;
        int y;
        bool pausa;
        int poder;
        Character(SDL_Renderer* renderer, int x, int y, bool pausa, int poder);
        virtual ~Character();
        void logic();
        void draw();
        Move* getMove(SDL_Renderer *renderer, string name, int sprite_amount);
    protected:
    private:
};

#endif // CHARACTER_H
