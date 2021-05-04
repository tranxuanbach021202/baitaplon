#ifndef LOAD_BUTTON_H_
#define LOAD_BUTTON_H_

#include "Load_Texture.h"
#include "Commonfunction.h"


//The mouse button
class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handleEvent( SDL_Event* e, bool & button,bool & button1, int button_width , int button_height  );



	private:
		//Top left position
		SDL_Point mPosition;


};
#endif // LOAD_BUTTON_H_
