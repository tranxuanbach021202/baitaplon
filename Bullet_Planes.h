
#include "Load_Texture.h"
#ifndef BULLET_PLANES_H_
#define BULLET_PLANES_H_
const int SPEED_BULLET =8;
static const int WEDTH_BULLET = 15;
static const int HEIGHT_BULLET =15;
class Bullet_Planes :public LTexture
{
public:
    Bullet_Planes();
    ~Bullet_Planes();
    enum BULLET_TYPE
    {
        BULLET1= 0,
        BULLET2=0,
    };
    void Move();
    //duoc phep ban khong
    void STATUS(const bool status_) {status_bullet = status_;}
    bool GET_STATUS() {return status_bullet;}
    //vi tri
    void Set_Pos( const float& x, const float& y) {mPosX= x; mPosY = y ;}
    float X()const {return mPosX;}
    float Y() const {return mPosY;}


    SDL_Rect Get_Rect(){return mCollider;}

   private:
    bool status_bullet;
    float mPosX, mPosY;
    SDL_Rect mCollider;
};
#endif // BULLET_PLANES_H_
