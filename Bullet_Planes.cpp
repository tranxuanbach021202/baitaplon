
#include "Bullet_Planes.h"
#include "Commonfunction.h"
Bullet_Planes::Bullet_Planes()
{
    mPosX =0;
    mPosY = 0;

    mCollider.h = HEIGHT_BULLET;
    mCollider.w = WEDTH_BULLET;

    status_bullet = false;


}
Bullet_Planes::~Bullet_Planes()
{

}
void Bullet_Planes::Move()
{
    if (status_bullet==true)
    {
        mPosX += SPEED_BULLET;

        if (mPosX > SCREEN_WIDTH)
        {
           status_bullet = false;
        }
    }
    mCollider.x=mPosX;
    mCollider.y=mPosY;
}
