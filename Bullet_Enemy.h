#ifndef BULLET_ENEMY_H_
#define BULLET_ENEMY_H_

#include "Commonfunction.h"
#include "Load_Texture.h"
static const int SPEED_BULLET_ENEMY = 5;
static const int WEDTH_BULLET_ENEMY = 15;
static const int HEIGHT_BULLET_ENEMY =15;
class Bullet_Enemy :public LTexture
{
public:
   Bullet_Enemy();
   void Move();

   void STATUS(bool status_) {status = status_;}
   bool GET_STATUS(){return status;}
   void Set_Pos( const float& x, const float& y) {mPosX= x; mPosY = y ;}
    float X()const {return mPosX;}
    float Y() const {return mPosY;}

    SDL_Rect Get_Rect() {return mCollider;}


private:
    bool status;
    float mPosX, mPosY;
    SDL_Rect mCollider;
};



#endif // BULLET_ENEMY_H_
