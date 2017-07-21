#pragma once
#include "SFML\Graphics.hpp"
#include <string>
#include "Texturecodex.h"
class Animation
{
public:
	
	/////////////////////////////////////////////////////////////////////
	/// Constructor : 
	/// 1st is for x coordinate , 
	/// 2nd is for y coordinate
	/// 3rd, 4rth x,y is the square dimension of the texture.
	/// 5th is hold time
	/// 6th is the number of frames
	/// The last param is for filename, in "path/XYZ"'s CARE: '/'
	/////////////////////////////////////////////////////////////////////
	Animation(int, int, int,int, float, int, std::string);

	/// Default
	Animation();

	///////////////////////////////////////////////////////////////////////
	// 3 arguments: RenderTarget for passing the mother window for drawing
	// X ccordinate
	// Y coordinate
	///////////////////////////////////////////////////////////////////////
	void Animation::draw(sf::RenderTarget &window, int x, int y);
	
	////////////////////////////////////////////
	///Used to skip to the next animation frame
	///The passed variable is a float variable
	///containing the timeelapsed
	///dt must be in SECONDS
	////////////////////////////////////////////
	void Animation::update(float dt);
	int sizex, sizey;

	////////////////////////////////////////////
	/// Applies the texture pointer to a sprite
	////////////////////////////////////////////
	void ApplyToSprite( sf::Sprite& s );

	//////////////////////////////////////////
	/// Used to reset the frame to the first
	/// As in looping to the start, cause ani
	///-mation
	/////////////////////////////////////////
	void resetframe();

private:
	int frame, currentframe;
	std::shared_ptr<sf::Texture> pTex;
	sf::IntRect bounds, frames[10];
	float holdtime, time;
	
};

