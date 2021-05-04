
#ifndef PLANES_H_
#define PLANES_H_

#include "Commonfunction.h"
#include "Load_Texture.h"
#include "Bullet_Planes.h"
#include "CheckCollision.h"
#include <SDL_mixer.h>
#include <iostream>

static const int WIDTH_PLANES =80;
static const int HEIGHT_PLANES = 40;
static const int DOT_VEL = 10;

class Planes
{
public:

    Planes();
    ~Planes();
    //Loads image at specified path
    bool loadFromFile( std::string path, SDL_Renderer* gRenderer );
    void handInput(SDL_Event e, int speed , SDL_Renderer* gRenderer);
    void Move();
    void Render(LTexture &planes,SDL_Renderer* gRenderer);
    void Set_Pos( const float& x, const float& y) {mPosX= x; mPosY = y ;}
    void Update_bullet (SDL_Renderer* gRenderer,SDL_Rect rect_enemy[],int &idd);
    float X()const {return mPosX;}
    float Y() const {return mPosY;}
    SDL_Rect Get_Rect() {return mCollider;}
    //Bullet creat
    void SET_BULLET(std::vector<Bullet_Planes*> p_bullet)
    {
        p_bullet_planes = p_bullet;
    }
    std::vector<Bullet_Planes*> GET_BULLET() const
    {
        return p_bullet_planes;
    }
    void delete_bullet(const int id);

private:
    float mPosX, mPosY;
    float mVelX, mVelY;
    std::vector <Bullet_Planes*> p_bullet_planes;
    SDL_Rect mCollider;

};
#endif // PLANES_H_
