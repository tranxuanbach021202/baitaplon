
#include "Planes_Enemy.h"

#include <iostream>
Planes_Enemy::Planes_Enemy()
{
   mPosX = SCREEN_WIDTH;
   mPosY = SCREEN_HEIGHT*0.5;


   mCollider.w= WIDTH_PLANES_ENEMY;
   mCollider.h = HEIGHT_PLANES_ENEMY;


}
void Planes_Enemy::Move()
{
    mPosX -= SPEED_ENEMY;

    if (mPosX < 0)
    {
        mPosX = SCREEN_WIDTH;
    }
    mCollider.x= mPosX;
    mCollider.y= mPosY;


 }
void Planes_Enemy::Creat_Bullet(Bullet_Enemy* p_bullet, SDL_Renderer* gRenderer)
{
    std::cout<<mPosX<<std::endl;
    if (p_bullet )
    {
          if (p_bullet->loadFromFile("img//bullet2.png",gRenderer))
          {
              p_bullet->STATUS(true);
              p_bullet_enemy.push_back(p_bullet);

          }

    }
}
void Planes_Enemy::Update_bullet(SDL_Renderer* gRenderer,SDL_Rect rect_planes,bool& game_over)
{
    for ( int i=0; i< p_bullet_enemy.size();i++)
    {
        Bullet_Enemy* p_bullet_e =  p_bullet_enemy[i] ;
        if (p_bullet_e!=NULL)
        {
            if (p_bullet_e->GET_STATUS())
            {
                p_bullet_e->Move();
                float x = p_bullet_e->X();
                float y = p_bullet_e->Y();
                p_bullet_e->render(x,y,NULL,gRenderer);

               if (Check_Collision(p_bullet_e->Get_Rect(),rect_planes))
               {

                   game_over = true;
               }

            }
            else
            {

                float x = mPosX;
                float y = mPosY;
                p_bullet_e->STATUS(true);
                p_bullet_e->Set_Pos(x-80,y+40);

            }
        }
    }
}
void Planes_Enemy::delete_enemy()
{
    mPosX = SCREEN_WIDTH;
    float y =rand()%300+100;
    mPosY = y;
}
void Planes_Enemy::Render(LTexture &gEnemy, SDL_Renderer* gRenderer)
{
    gEnemy.render(mPosX, mPosY, NULL,gRenderer);
}

