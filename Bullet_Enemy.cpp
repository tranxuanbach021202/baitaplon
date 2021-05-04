
#include "Bullet_Enemy.h"

Bullet_Enemy::Bullet_Enemy()
{
   mPosX =0;
   mPosY =0;

   mCollider.w = WEDTH_BULLET_ENEMY;
   mCollider.h = HEIGHT_BULLET_ENEMY;

   status = false;
}
void Bullet_Enemy::Move()
{
    if (status ==true)
    {
        mPosX -= SPEED_BULLET_ENEMY;
        if (mPosX < 20)
        {
            status =false;
        }
        mCollider.x = mPosX;
        mCollider.y = mPosY;
    }
}
