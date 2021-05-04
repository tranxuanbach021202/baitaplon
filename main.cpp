#include "Commonfunction.h"
#include "Load_Texture.h"
#include "Planes.h"
#include "Bullet_Planes.h"
#include "Planes_Enemy.h"
#include "Load_Button.h"
#include <iostream>
#include <ctime>


LTexture bkg;
LTexture gPlanes;
LTexture gEnemy;
LTexture Game_Over;
LTexture Menu_Game;
LTexture Menu_Game_Over;
LButton gButton [4];
int score =0;
int score_max = 0;
bool game_over = false;
bool game_over1 = false;

//frame
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
LTexture gSpriteSheetTexture;

//man hinh
SDL_Window* gWindow =NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont = NULL;
TTF_Font *gFont1 = NULL;


//Scene textures
LTexture gPromptTextTexture;
LTexture gScoreMax;
LTexture gScore_max;
LTexture gPlay_text;
LTexture gExit_text;
LTexture gScore;

// am thanh
Mix_Music *gMusic = NULL;
Mix_Music *gMusic_game = NULL;



//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

void CleanUp();

int Game();


int main( int argc, char* args[] )
{

    Game();
    return 0;
}
int Game () {
    srand(time(0));
    float bkg_X =0;

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;
            bool play =false;
            bool exit = false;
            bool button_play = false;
            bool button_exit = false;
            int id =4;

			//Event handler
			SDL_Event e;

            Planes gPlanes_Object;
            Planes_Enemy gEnemy_Object[Number_of_aircraft];
            SDL_Rect rect_enemy[Number_of_aircraft];

            for (int i= 0; i < Number_of_aircraft ;i++)
            {
               Bullet_Enemy* p_bullet =new Bullet_Enemy();
               gEnemy_Object[i].Creat_Bullet(p_bullet,gRenderer);
               float y = rand()% 400;
               if ( y > SCREEN_HEIGHT -150)
               {
                   y = SCREEN_HEIGHT* 0.3;
               }

               gEnemy_Object[i].Set_Pos(SCREEN_WIDTH + i*300,y);
            }

            gFont1 = TTF_OpenFont( "font//abc.ttf",30 );
            if (gFont1 == NULL)
            {
                quit =true;
            }
            SDL_Color textColor = { 0, 0, 0, 0xFF };
            gPlay_text.loadFromRenderedText("Play Game",textColor,gRenderer,gFont1);
            gExit_text.loadFromRenderedText("Exit",textColor,gRenderer,gFont1);
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );

            if (!play && !game_over)
            {
                Menu_Game.render(0,0,NULL,gRenderer);

                gExit_text.render(70,325,NULL,gRenderer);
                gPlay_text.render(70,235,NULL,gRenderer);

            }
            else if (game_over && !play )
            {
                Menu_Game_Over.render(0,0,NULL,gRenderer);

            }



            SDL_RenderPresent( gRenderer );


            //doc diem lon nhat
            std::ifstream filein("Score_max.txt");
            filein>> score_max;

            filein.close();
            std::cout<<score_max<<std::endl;

			while( (! quit)  )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{

				    //The rerender text flag
				    bool renderText = false;


					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					 if (play)
					{
					    gPlanes_Object.handInput(e,3,gRenderer);

					} else
                    if (game_over)
                    {
                        gButton[2].handleEvent(&e,play,button_play,70,27);
					    gButton[3].handleEvent(&e,exit,button_exit,56,27);
                    }
					else if (!exit && !play)
					{
                          gButton[0].handleEvent(&e,play,button_play,280,35);
					      if (button_play)
                         {
                            SDL_Color textColor = { 255, 255, 0, 0xFF };
                            gPlay_text.loadFromRenderedText("Play Game",textColor,gRenderer,gFont1);
                            gPlay_text.render(70,235,NULL,gRenderer);
                            SDL_RenderPresent( gRenderer );


                         } else
                         {
                            SDL_Color textColor = { 0, 0, 0, 0xFF };
                            gPlay_text.loadFromRenderedText("Play Game",textColor,gRenderer,gFont1);
                            gPlay_text.render(70,235,NULL,gRenderer);
                            SDL_RenderPresent( gRenderer );
                         }
                         gButton[1].handleEvent(&e,exit,button_exit,120,32);
                         if (button_exit)
                         {
                            SDL_Color textColor = { 255, 255, 0, 0xFF };
                            gExit_text.loadFromRenderedText("Exit",textColor,gRenderer,gFont1);
                            gExit_text.render(70,325,NULL,gRenderer);
                            SDL_RenderPresent( gRenderer );

                         } else
                         {
                            SDL_Color textColor = { 0, 0, 0, 0xFF };
                            gExit_text.loadFromRenderedText("Exit",textColor,gRenderer,gFont1);
                            gExit_text.render(70,325,NULL,gRenderer);
                            SDL_RenderPresent( gRenderer );
                         }



					}





				}
             if (!play)
            {
              if( Mix_PlayingMusic() == 0 )
							{
								//Play the music
								Mix_PlayMusic( gMusic, -1 );
							}
							//If music is being played
							else
							{
								//If the music is paused
								if( Mix_PausedMusic() == 1 )
								{
									//Resume the music
									Mix_ResumeMusic();
								}
								//If the music is playing
								else
								{
									//Pause the music

								}
							}
            } else
            {
              Mix_PauseMusic();
            }
            if (exit )
            {
                quit= true;
            }
            if (play)
            {
                game_over = false;

                //chay background
                if (bkg_X== -SCREEN_WIDTH)
                {
                    bkg_X =0;
                }
                bkg_X -=1;
				bkg.render(bkg_X,0,NULL,gRenderer);
				bkg.render(bkg_X+SCREEN_WIDTH,0,NULL,gRenderer);

                //render điểm số
                //Render text textures
                SDL_Color textColor = { 255, 255, 0, 0xFF };
                gPromptTextTexture.render(0,5,NULL,gRenderer);
                std::string s = std::to_string(score);
                gScore.loadFromRenderedText(s,textColor,gRenderer,gFont);
                gScore.render(185,5,NULL,gRenderer);
                gScoreMax.render(300,5,NULL,gRenderer);
                SDL_Color textColor1 = { 200, 200, 0, 0xFF };
                std::string ss = std::to_string(score_max);
                gScore_max.loadFromRenderedText(ss,textColor1,gRenderer,gFont);
                gScore_max.render(480,5,NULL,gRenderer);

                 //Quản lý nhân vật
                gPlanes_Object.Move();
                gPlanes_Object.Render(gPlanes,gRenderer);
                //Check_Collision giữa đạn nhân vật và máy bay địch và update đạn cho nhân vật
                gPlanes_Object.Update_bullet(gRenderer,rect_enemy,id);

                //chạy các máy bay địch
                for (int i=0; i< Number_of_aircraft ; i++)
                {

                     gEnemy_Object[i].Move();

                     //Check_Collision giữa đạn máy bay địch và nhân vật trong update_bullet
                     gEnemy_Object[i].Update_bullet(gRenderer,gPlanes_Object.Get_Rect(),game_over);
                     if (game_over)
                     {   Mix_PlayChannel(-1,gExplosion,0);
                         break;
                     }
                     gEnemy_Object[i].Render(gEnemy, gRenderer);
                     rect_enemy[i] = gEnemy_Object[i].Get_Rect();

                     //kiểm tra va chạm giữa nhân vật và máy bay địch
                     if (Check_Collision(gPlanes_Object.Get_Rect(),gEnemy_Object[i].Get_Rect()))
                     {
                           game_over= true;
                           Mix_PlayChannel(-1,gExplosion,0);
                           for (int t =0 ;t< WALKING_ANIMATION_FRAMES ; t++)
                           {
                            SDL_Rect* currentClip = &gSpriteClips[ t ];
                            gSpriteSheetTexture.render( gPlanes_Object.X()+40,gPlanes_Object.Y()+40 , currentClip,gRenderer);
                           }
                           SDL_Delay(500);
                           break;
                     }
                     //kiểm tra đạn bắn trúng máy bay địch nào thì sẽ reset lại máy bay đó
                     if (id<Number_of_aircraft)
                     {
                       for (int t =0 ;t< WALKING_ANIMATION_FRAMES ; t++)
                       {
                         SDL_Rect* currentClip = &gSpriteClips[ t ];
                         gSpriteSheetTexture.render( gEnemy_Object[id].X(),gEnemy_Object[id].Y() , currentClip,gRenderer);
                       }
                        Mix_PlayChannel(-1,gExplosion,0);
                        gEnemy_Object[id].delete_enemy();
                        //tăng điểm lên
                        score++;

                     }

                     id = 10;
                }
                // kiểm tra game đã over chưa
                if (game_over)
                {   //xóa bộ nhớ
                    close();
                    //chạy lại game
                    Game();
                    //Update screen
                    SDL_RenderPresent( gRenderer );

                }




               SDL_Delay(10);

                //Update screen
              SDL_RenderPresent( gRenderer );

            }



			}
			std::ofstream fileout("Score_max.txt");
			if (score> score_max)
            {
                score_max = score;
                fileout<< score_max;
                fileout.close();
            } else
              {
                  fileout<< score_max;
                  fileout.close();

              }

			}

		}




	//Free resources and close SDL
	close();
    return 0;

}






bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Xuân Bách <3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				 //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
				 //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}
	SDL_Surface* icon = IMG_Load("img//icon.png");
    SDL_SetWindowIcon(gWindow, icon);

	return success;
}
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if (!bkg.loadFromFile("img//bk1.png", gRenderer))
    {
        printf("Loi background");
        success = false;

    }
    if (!gPlanes.loadFromFile("img//planes.png", gRenderer))
    {
        printf ("loi load planes");
        success = false;
    }
    if (!gEnemy.loadFromFile("img//enemy2.png",gRenderer))
    {
        printf("Loi load Enemy");
        success = false;
    }
    if (!Menu_Game.loadFromFile("img//Menu_Game.png",gRenderer))
    {
        printf("Loi load menu gaame");
        success = false;
    }
    else
    {
        gButton[0].setPosition(70,235);
        gButton[1].setPosition(70,325);
    }
    if (!Menu_Game_Over.loadFromFile("img//Game_Over.png",gRenderer))
    {
        printf("Loi load game over");
        success = false;
    }
    else
    {
        gButton[2].setPosition(377,521);
        gButton[3].setPosition(548,521);
    }
     if (!gSpriteSheetTexture.loadFromFile("img//exp_main.png",gRenderer))
    {
        success = false;
    }
    else
    {
        gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w =  120;
		gSpriteClips[ 0 ].h = 165;

		gSpriteClips[ 1 ].x =  200;
		gSpriteClips[ 1 ].y =   0;
		gSpriteClips[ 1 ].w =  100;
		gSpriteClips[ 1 ].h = 165;

		gSpriteClips[ 2 ].x = 340;
		gSpriteClips[ 2 ].y =   0;
		gSpriteClips[ 2 ].w =  150;
		gSpriteClips[ 2 ].h = 165;

		gSpriteClips[ 3 ].x = 490;
		gSpriteClips[ 3 ].y =   0;
		gSpriteClips[ 3 ].w =  170;
		gSpriteClips[ 3 ].h = 165;
    }

    //am thanh
    gMusic = Mix_LoadMUS( "sound//music_bkg.mp3" );
	if(gMusic == NULL)
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}


	gExplosion = Mix_LoadWAV("sound//explosion.mp3");
	if (gExplosion==NULL)
	{
	    printf( "Failed to load gExplosion sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

   gFont = TTF_OpenFont( "font//abc.ttf",21 );
   if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	} else
	{
	    SDL_Color textColor = { 0, 0, 0, 0xFF };
	    if(!gPromptTextTexture.loadFromRenderedText("Your score:",textColor,gRenderer,gFont))
        {
            printf("loi render tff");
            success = false;
        }
        if (!gScoreMax.loadFromRenderedText("High Score:",textColor,gRenderer,gFont))
        {
            printf("loi render tfff");
            success = false;
        }

	}

	return success;
}
void close()
{
	//Free loaded images
	bkg.free();
    //Free loaded images
	gPromptTextTexture.free();
	gPlanes.free();
	gScore.free();
	gPlay_text.free();
	gEnemy.free();
    gScoreMax.free();
    gScore_max.free();
    Menu_Game.free();




	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();

}

