
#include "Load_Button.h"
#include <iostream>
LButton::LButton()
{
    mPosition.x = 0;
	mPosition.y = 0;

}
void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}
void LButton::handleEvent( SDL_Event* e, bool &button_down,bool & button_tion ,int BUTTON_WIDTH, int BUTTON_HEIGHT)
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( inside )
		{
            //Set mouse over sprite
			switch( e->type )
			{

				case SDL_MOUSEBUTTONDOWN:

				  button_down =true;
				  break;

				case SDL_MOUSEMOTION :
                  button_tion = true;
                   break;
			}
		} else
		 {
		     button_tion = false;
		 }




	}
}
