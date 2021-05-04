
#include "Planes.h"

Planes::Planes()
{
    mPosX = 100;
    mPosY = 100;

    mCollider.w = WIDTH_PLANES;
    mCollider.h =HEIGHT_PLANES;

    mVelX = 0;
    mVelY = 0;



}
Planes::~Planes()
{

}
void Planes::handInput(SDL_Event e , int speed , SDL_Renderer* gRenderer)
{
   //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
    else if (e.type== SDL_MOUSEBUTTONDOWN)
    {

        Bullet_Planes* p_bullet = new Bullet_Planes();
        if (e.button.button== SDL_BUTTON_LEFT)
        {    p_bullet->loadFromFile("img//bullet1.png",gRenderer);
             // am thanh ban dan
             gMusic_Bullet = Mix_LoadWAV("sound//bullet.wav");
             Mix_PlayChannel(-1,gMusic_Bullet,0);

        }
        p_bullet->Set_Pos(this->mPosX+80, this->mPosY +20);
        p_bullet->STATUS(true);
        p_bullet_planes.push_back(p_bullet);

    }
}
void Planes::Update_bullet(SDL_Renderer* gRenderer,SDL_Rect rect_enemy[],int& idd)
{
    for (int i=0; i< p_bullet_planes.size();i++)
    {
        Bullet_Planes* p_bullet_ = p_bullet_planes.at(i);
        if (p_bullet_ != NULL)
        {
            if (p_bullet_->GET_STATUS())
            {
                p_bullet_->Move();
                float x= p_bullet_->X();
                float y = p_bullet_->Y();
                p_bullet_->render(x,y,NULL,gRenderer);
               for (int ii =0; ii< Number_of_aircraft ; ii++)
               {
                    if (Check_Collision(p_bullet_->Get_Rect(),rect_enemy[ii]))
                   {

                    // std::cout<<"va cham"<<ii<<std::endl;
                      idd = ii;
                      for (int k=0 ; k<p_bullet_planes.size();k++)
                      {

                          if (p_bullet_planes.size()> 0 && p_bullet_planes.size() > i)
                          {
                              Bullet_Planes* p_bullet = p_bullet_planes.at(i);
                              p_bullet_planes.erase(p_bullet_planes.begin()+i);
                              if (p_bullet != NULL)
                              {
                                  delete p_bullet;

                                  p_bullet =NULL;
                              }
                          }
                          break;
                      }

                   }


              }
            }
            // vuot qua man hinh
            else
            {
                if (p_bullet_!= NULL)
                {
                    p_bullet_planes.erase(p_bullet_planes.begin()+i);
                    delete p_bullet_;
                    p_bullet_= NULL;
                }
            }
        }
    }

}
void Planes::Move()
{

    mPosX += mVelX;
    mCollider.x = mPosX;

    if( ( mPosX < 20 ) || ( mPosX + WIDTH_PLANES > SCREEN_WIDTH-300 ) )
    {
        //Move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }


    mPosY += mVelY;
    mCollider.y = mPosY;

    if( ( mPosY < 5 ) || ( mPosY + HEIGHT_PLANES > SCREEN_HEIGHT-100 ) )
    {
        //Move back
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }
}
void Planes::Render(LTexture &planes ,SDL_Renderer* gRenderer)
{
    planes.render(mPosX,mPosY,NULL,gRenderer);
}


