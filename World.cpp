#include "World.h"


World::World(std::string texname)

{
	tex=Texturecodex::Acquire(texname);
}


void World::draw(sf::RenderTarget &window, int left, int top, int sizex, int sizey ,  int x, int y)
{
	sf::Sprite sprite(*tex);
	bounds.height = sizex;
	bounds.width = sizey;
	bounds.left=left;
	bounds.top=top;
	sprite.setTextureRect(bounds);
	sprite.setPosition((float)x,(float)y);
	window.draw(sprite);
}

World::~World()
{
	Texturecodex::MurderOrphans();
}