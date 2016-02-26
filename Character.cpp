#include "Character.h"


std::string toString(int number)
{
    if (number == 0)
        return "0";

    if(number < 0)
        return "-"+toString(-number);

    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<(int)temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

Character::Character(SDL_Renderer* renderer, int x, int y, bool pausa, int poder)
{
    this->x=x;
    this->y=y;

    moves["idle"]=getMove(renderer,"idle",4);
    moves["kick"]=getMove(renderer,"kick",6);
    moves["punch"]=getMove(renderer,"punch",3);
    moves["walk"]=getMove(renderer,"walk",5);
    moves["shoryuken"]=getMove(renderer,"shoryuken",5);
    moves["jump"]=getMove(renderer,"jump",8);
    moves["air_kick"]=getMove(renderer,"air_kick",3);


    this->current_move = "idle";
    this->current_sprite = 0;
    this->current_sprite_frame = 0;
}

Move* Character::getMove(SDL_Renderer *renderer, string name, int sprite_amount)
{
    //Sprites load
    vector<Sprite*>sprites;
    string align_file_path = "assets/" + name + "/align.txt";
    ifstream align_file(align_file_path.c_str());
    for(int i=1;i<=sprite_amount;i++)
    {
        string path="assets/" + name + "/" + toString(i) + ".png";
        int align_x;
        int align_y;
        align_file>>align_x;
        align_file>>align_y;

        sprites.push_back(new Sprite(renderer,path,40,align_x,align_y));
    }

    //Cancel load
    string cancels_file_path = "assets/" + name + "/cancel.txt";
    ifstream cancels_file(cancels_file_path.c_str());
    vector<string>cancels;
    string cancel_temp;
    while(cancels_file>>cancel_temp)
    {
        cancels.push_back(cancel_temp);
    }

    return new Move(renderer,sprites,cancels);
}

Character::~Character()
{
    //dtor
}

void Character::logic()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    if( currentKeyStates[ SDL_SCANCODE_P ] )
    {
            this->pausa = true;
            cout<<"En pausa"<<endl;
    }
    if( currentKeyStates[ SDL_SCANCODE_KP_ENTER ] )
    {
            this->pausa = false;
            cout<<"Reanudado"<<endl;
    }
    if(!this->pausa){
        if( currentKeyStates[ SDL_SCANCODE_Q ] )
        {
            this->current_move = "idle";
            this->current_sprite = 0;
        }
        else if( currentKeyStates[ SDL_SCANCODE_E ] )
        {
            if(moves["shoryuken"]->canCancel(this->current_move))
            {
                this->current_move = "shoryuken";
                this->current_sprite = 0;
            }
        }
        else if( currentKeyStates[ SDL_SCANCODE_R ] )
        {
            if(moves["punch"]->canCancel(this->current_move))
            {
                this->current_move = "punch";
                this->current_sprite = 0;
            }
        }
        else if( currentKeyStates[ SDL_SCANCODE_T ] )
        {
            if(moves["kick"]->canCancel(this->current_move))
            {
                this->current_move = "kick";
                this->current_sprite = 0;
            }
        }
        else if( currentKeyStates[ SDL_SCANCODE_SPACE ] )
        {
            if(moves["air_kick"]->canCancel(this->current_move))
            {
                if(poder<3){
                    this->current_move = "air_kick";
                    this->current_sprite = 0;
                    poder++;
                }

            }
        }
        else if( currentKeyStates[ SDL_SCANCODE_W ] )
        {
            if(moves["jump"]->canCancel(this->current_move))
            {
                this->current_move = "jump";
                this->current_sprite = 0;
            }
        }
        else if( currentKeyStates[ SDL_SCANCODE_A ] )
        {
            if(moves["walk"]->canCancel(this->current_move))
            {
                if(this->current_move!="walk")
                {
                    this->current_sprite = 0;
                }
                this->current_move = "walk";
                if(this->x > 0)
                    this->x-=2;
            }
        }
        else if( currentKeyStates[ SDL_SCANCODE_D ] )
        {
            if(this->current_move=="idle"
               || this->current_move=="walk")
           {
                if(this->current_move!="walk")
                {
                    this->current_sprite = 0;
                }
                this->current_move = "walk";
                if(this->x < 1000)
                    this->x+=2;
           }

        }else
        {
            if(this->current_move=="walk")
            {
                this->current_move = "idle";
                this->current_sprite = 0;
            }
        }

        current_sprite_frame++;
        if(current_sprite_frame>=moves[current_move]->sprites[current_sprite]->frames)
        {
            current_sprite++;
            if(current_sprite>=moves[current_move]->sprites.size())
            {
                current_move= "idle";
                current_sprite=0;
            }
            current_sprite_frame=0;
        }
    }

}

void Character::draw()
{
    moves[current_move]->draw(current_sprite,x,y);
}
