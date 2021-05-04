
#ifndef PLANES_ENEMY_H_
#define PLANES_ENEMY_H_
#include "Commonfunction.h"
#include "Load_Texture.h"
#include "Bullet_Enemy.h"
#include "CheckCollision.h"

static const int SPEED_ENEMY =4;
static const int WIDTH_PLANES_ENEMY =150;
static const int HEIGHT_PLANES_ENEMY =55;
class Planes_Enemy
{
public:
    Planes_Enemy();
    void Move();
    void Render(LTexture &gEnemy, SDL_Renderer* gRenderer);
    //vi tri
    void Set_Pos( const float& x, const float& y) {mPosX= x; mPosY = y ;}
    float X()const {return mPosX;}
    float Y() const {return mPosY;}

    //Bullet
    void Creat_Bullet(Bullet_Enemy* p_bullet ,SDL_Renderer* gRenderer);
    void Update_bullet(SDL_Renderer* gRenderer,SDL_Rect rect_planes,bool& game_over);
      void SET_BULLET(std::vector<Bullet_Enemy*> p_bullet)
    {
        p_bullet_enemy = p_bullet;
    }
    std::vector<Bullet_Enemy*> GET_BULLET() const
    {
        return p_bullet_enemy;
    }
    SDL_Rect Get_Rect() {return mCollider;}
    void delete_enemy();
private:
    float mPosX, mPosY;
    std::vector <Bullet_Enemy*> p_bullet_enemy;
    SDL_Rect mCollider;


};
#endif // PLANES_ENEMY_H_
