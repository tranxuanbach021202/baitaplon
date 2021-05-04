
#ifndef LOAD_TEXTURE_H_
#define LOAD_TEXTURE_H_


#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <algorithm>


class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path, SDL_Renderer* gRenderer );



		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor, SDL_Renderer* gRenderer ,TTF_Font *gFont);
		#endif



		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( double x, double y, SDL_Rect* clip = NULL, SDL_Renderer* gRenderer = NULL );

		//Gets image dimensions
		double getWidth();
		double getHeight();




	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		double mWidth;
		double mHeight;
};
#endif // LOAD_TEXTURE_H_
