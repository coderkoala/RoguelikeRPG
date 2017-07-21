#pragma once
#include "SFML\Graphics.hpp"
#include "texturecodex.h"
class World
{
public:
	
	/////////////////////////////////////////////////////////////////////
	/// Constructor : left is for x coordinate , 
	/// top is for y coordinate
	/// size is the square dimension of the texture.
	/////////////////////////////////////////////////////////////////////
	World(std::string);

	/////////////////////////////////////////////
	///Destroys the texture, the vector container
	/////////////////////////////////////////////
	~World(void);
	

	///////////////////////////////////////////////////////////////////////
	/// 7 arguments:  
	///   Renderwindow, 
	///	  left, file ko, top file ko,
	///   sizeofx file ko, sizeofy file ko, 
	///   positionX screen ko, positionY screen ko
	///////////////////////////////////////////////////////////////////////
	void World::draw(sf::RenderTarget &window, int, int, int, int ,  int , int );

private:

	//shared pointer, from the TextureCodex class, for managing
	//and easily getting the texture for drawing stuff
	std::shared_ptr<sf::Texture> tex;
	
	//stores the bounds, has 4 elements to it. Easy ;)
	sf::IntRect bounds;
};

